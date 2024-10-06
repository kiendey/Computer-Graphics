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
CurrentWidth = 700,
CurrentHeight = 700;

GLuint
VaoId,
VboId,
ColorBufferId,
VertexShaderId,
FragmentShaderId,
ProgramId;

mat4 model_mat_cpp;
int model_location;

float Alpha = 0.0f;

// ------------------------------------------
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
	model_mat_cpp = rotate_z(Alpha);

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
void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(EXIT_SUCCESS); break;

		// nhấn phím z hoặc Z để quay
	case 'z':
		Alpha -= 10.0f; break;
	case 'Z':
		Alpha += 10.0f; break;
	}
}
// ------------------------------------------
void MouseFunc(int button, int state, int x, int y)
{
	// nhấn phím trái hoặc phím phải chuột để quay
	if (state == GLUT_DOWN) {
		switch (button) {
		case GLUT_LEFT_BUTTON:    Alpha -= 10.0f;  break;
		case GLUT_RIGHT_BUTTON:   Alpha += 10.0f;  break;
		}
	}
}

// ------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("RotationZ Keyboard Mouse");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutMouseFunc(MouseFunc);
	glutCloseFunc(CloseFunc);

	glutMainLoop();

	return 0;
}
