#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace std;

typedef struct
{
	float XYZW[4];
	float RGBA[4];
} Vertex;

// tạo 3 điểm đỉnh
Vertex Vertices[] =
{
	{ {-0.5f, -0.5f, 0.0f, 1.0f },{ 0.4f, 0.3f, 0.0f, 1.0f } },
	{ { 0.5f,  -0.5f, 0.0f, 1.0f },{ 1.0f, 0.4f, 0.0f, 1.0f } },
	{ { 0.5f, 0.5f, 0.0f, 1.0f },{ 0.7f, 0.5f, 1.0f, 1.0f } },
	{ { -0.5f, 0.5f, 0.0f, 1.0f },{ 0.5f, 0.6f, 1.0f, 1.0f } }
};

const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].XYZW);

int
CurrentWidth = 800,
CurrentHeight = 600,
WindowHandle = 0;

GLuint
VaoId,
VboId,
VertexShaderId,
FragmentShaderId,
ProgramId;

// ---------------------------------------------------------------------------	
string ReadShaderSourceFile(string fileName) {
	fstream reader(fileName.c_str());
	string line;
	string code = "";
	while (getline(reader, line)) {
		code += line + "\n";
	}
	reader.close();
	return code;
}
// ---------------------------------------------------------------------------	
void CreatVaoVbo()
{
	GLenum ErrorCheckValue = glGetError();

	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(stderr, "ERROR: Could not destroy the VBO: %s \n", gluErrorString(ErrorCheckValue));
		exit(-1);
	}
}
// ---------------------------------------------------------------------------	
void CreatShaders()
{
	GLenum ErrorCheckValue = glGetError();

	string vertexSrc = ReadShaderSourceFile("./vs.shader");
	string fragmentSrc = ReadShaderSourceFile("./fs.shader");

	const GLchar* VertexShader = vertexSrc.c_str();
	const GLchar* FragmentShader = fragmentSrc.c_str();

	ErrorCheckValue = glGetError();
	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not create the shaders: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}
// ---------------------------------------------------------------------------	
void CloseFunc()
{
	GLenum ErrorCheckValue = glGetError();

	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not destroy the shaders: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(stderr, "ERROR: Could not destroy the VBO: %s \n", gluErrorString(ErrorCheckValue));
		exit(-1);
	}
}
// ---------------------------------------------------------------------------	
void DisplayFunc(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// kết xuất nguyên thủy từ mảng dữ liệu
	// GL_POINTS: là loại nguyên thủy
	// 0: là chỉ số bắt đầu trong mảng đang kích hoạt
	// 3: số lượng chỉ số sẽ được kết xuất
	glDrawArrays(GL_POINTS, 0, 4);

	glutSwapBuffers();

}
// ---------------------------------------------------------------------------	
void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;

	glViewport(0, 0, CurrentWidth, CurrentHeight);
}
// ---------------------------------------------------------------------------	
void IdleFunc(void)
{
	glutPostRedisplay();
}
// ---------------------------------------------------------------------------	
void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
	case 'q':
	case 'Q':
		exit(EXIT_SUCCESS);
		break;

	default:
		break;
	}
}
// ---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	WindowHandle = glutCreateWindow("3 Dot");
	if (WindowHandle < 1) {
		fprintf(stderr, "ERROR: Could not create a new rendering window.\n");
		exit(EXIT_FAILURE);
	}

	GLenum GlewInitResult;
	glewExperimental = GL_TRUE;
	GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult) {
		fprintf(stderr, "ERROR: %s\n", glewGetErrorString(GlewInitResult));
		exit(EXIT_FAILURE);
	}

	fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutCloseFunc(CloseFunc);

	glutMainLoop();

	return 0;
}
