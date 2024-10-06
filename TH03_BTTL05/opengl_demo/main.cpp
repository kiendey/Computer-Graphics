#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <GL/vector_matrix.h>

using namespace std;

typedef struct
{
	float XYZW[4];
	float RGBA[4];
} Vertex;

Vertex Vertices[] =
{
	{ { -0.5f,	-0.5f,	 0.5f,	1.0f },{ 0.5f,	0.5f,	0.5f,	1.0f } },
	{ {  0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.5f,	0.5f,	0.5f,	1.0f } },
	{ { -0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.5f,	0.5f,	0.5f,	1.0f } },

	{ {  0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.5f,	0.5f,	0.5f,	1.0f } },
	{ { -0.5f,	-0.5f,	 0.5f,	1.0f },{ 0.5f,	0.5f,	0.5f,	1.0f } },
	{ {  0.5f,	-0.5f,	 0.5f,	1.0f },{ 0.5f,	0.5f,	0.5f,	1.0f } },

	{ {  0.0f,	 0.5f,	 0.0f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ {  0.5f,	-0.5f,  -0.5f,1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { -0.5f,	-0.5f,  -0.5f,1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },

	{ {  0.0f,	 0.5f,	 0.0f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ {  0.5f,	-0.5f,	 0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ {  0.5f,	-0.5f,  -0.5f,1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },

	{ {  0.0f,	 0.5f,	 0.0f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	-0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },

	{ {  0.0f,	 0.5f,	 0.0f,	1.0f },{ 1.0f,	1.0f,	1.0f,	1.0f } },
	{ { -0.5f,	-0.5f,	 0.5f,	1.0f },{ 1.0f,	1.0f,	1.0f,	1.0f } },
	{ {  0.5f,	-0.5f,	 0.5f,	1.0f },{ 1.0f,	1.0f,	1.0f,	1.0f } }
};

const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].XYZW);

int
CurrentWidth = 800,
CurrentHeight = 600;

GLuint
VaoId,
VboId,
ColorBufferId,
VertexShaderId,
FragmentShaderId,
ProgramId;

mat4 model_mat_cpp;
int model_location;

// mảng lưu trữ giá tỉ lệ theo các trục x, y, z
float S[3] = { 1.0f, 1.0f, 1.0f };
// ------------------------------------------
// mảng lưu giá trị tịnh tiến theo các trục x, y, z
float T[3] = { 0.0f, 0.0f, 0.0f };
// mảng lưu góc quay cho từng trục x, y, z
float R[] = { 0.0f,0.0f,0.0f };


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
// ------------------------------------------
void CreatVaoVbo()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}
// ------------------------------------------
void CreatShaders()
{
	string vertexSrc = ReadShaderSourceFile("./vs.shader");
	string fragmentSrc = ReadShaderSourceFile("./fs.shader");

	const GLchar* VertexShader = vertexSrc.c_str();
	const GLchar* FragmentShader = fragmentSrc.c_str();

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
}
// ------------------------------------------
void CloseFunc()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}
// ------------------------------------------
void DisplayFunc(void)
{
	// tạo ma trận tỉ lệ theo các trục
	model_mat_cpp = scale(vec3(S[0], S[1], S[2]));

	model_location = glGetUniformLocation(ProgramId, "model_mat_shader");
	glUniformMatrix4fv(model_location, 1, GL_FALSE, model_mat_cpp.m);

	glEnable(GL_DEPTH_TEST);
	//glFrontFace(GL_CW);	

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 18);

	glutSwapBuffers();
}
// ------------------------------------------
void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;

	glViewport(0, 0, CurrentWidth, CurrentHeight);
}
// ------------------------------------------
void IdleFunc(void)
{
	glutPostRedisplay();
}
// ------------------------------------------
void KeyboardFuncRotate(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(EXIT_SUCCESS); break;

		// quay quanh trục x
	case 'a':
		R[0] += 10.0f;
		break;
	case 'A':
		R[0] -= 10.0f;
		break;

		// quay quanh trục y
	case 'b':
		R[1] += 10.0f;
		break;
	case 'B':
		R[1] -= 10.0f;
		break;

		// quay quanh trục z
	case 'c':
		R[2] += 10.0f;
		break;
	case 'C':
		R[2] -= 10.0f;
		break;
	}
}


void KeyboardFuncScale(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(EXIT_SUCCESS); break;

		// tính hệ số tỉ lệ
	case '=':
	case '+':
		S[0] *= 1.05f;
		S[1] *= 1.05f;
		S[2] *= 1.05f;
		break;

	case '-':
	case '_':
		S[0] /= 1.05f;
		S[1] /= 1.05f;
		S[2] /= 1.05f;
		break;
	}
}
void KeyboardFuncTranslate(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(EXIT_SUCCESS); break;

		// tịnh tiến theo trục x
	case 'x':
		T[0] -= 0.05f;
		break;
	case 'X':
		T[0] += 0.05f;
		break;

		// tịnh tiến theo trục y
	case 'y':
		T[1] -= 0.05f;
		break;
	case 'Y':
		T[1] += 0.05f;
		break;

		// tịnh tiến theo trục z
	case 'z':
		T[2] -= 0.05f;
		break;
	case 'Z':
		T[2] += 0.05f;
		break;
	}
}


// ------------------------------------------
void MouseFunc(int button, int state, int x, int y)
{
	// tính hệ số tỉ lệ
	if (state == GLUT_DOWN) {
		switch (button) {
		case GLUT_LEFT_BUTTON:
			S[0] /= 1.05f;
			S[1] /= 1.05f;
			S[2] /= 1.05f;
			break;
		case GLUT_RIGHT_BUTTON:
			S[0] *= 1.05f;
			S[1] *= 1.05f;
			S[2] *= 1.05f;
			break;
		}
	}
}
// ------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("ScaleXYZ Keyboard Mouse");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(KeyboardFuncScale);
	glutKeyboardFunc(KeyboardFuncRotate);
	glutKeyboardFunc(KeyboardFuncTranslate);
	glutMouseFunc(MouseFunc);
	glutCloseFunc(CloseFunc);

	glutMainLoop();

	return 0;
}


