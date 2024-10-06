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


//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3

Vertex Vertices[] =
{
	// v0-v1-v2 (front)
	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { -0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	// v2-v3-v0
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { 0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },

	// v0-v3-v4 (right)
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	-0.5f,   0.5f,1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	-0.5f,  -0.5f,1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	// v4-v5-v0
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	 0.5f,	-0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	 0.5f,   0.5f,1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },

	// v0-v5-v6 (top)
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { 0.5f,	0.5f,	-0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	 -0.5f,1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	// v6-v1-v0
	{ { -0.5f,	 0.5f,	 -0.5f,1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { 0.5f,	0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },

	// v1-v6-v7 (left)
	{ { -0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	-0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	// v7-v2-v1
	{ { -0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },

	// v7-v4-v3 (bottom)
	{ { -0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { 0.5f,	-0.5f,	 0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	// v3-v2-v7
	{ { 0.5f,	-0.5f,	0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { -0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },

	// v4-v7-v6 (back)
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { -0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { -0.5f,	0.5f,	-0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	// v6-v5-v4
	{ { -0.5f,	0.5f,	 -0.5f,1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { 0.5f,	0.5f,	 -0.5f,1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { 0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },

	// mặt đáy dạng hình chữ nhật, được cấu thành bởi 2 tam giác
	// v0-v5-v6 (top)
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { 0.5f,	0.5f,	-0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	 -0.5f,1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	// v6-v1-v0
	{ { -0.5f,	 0.5f,	 -0.5f,1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { 0.5f,	0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },

	// mặt sau, màu red
	{ {  0.0f,	 0.9f,	 0.0f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { -0.5f,	0.5f,	 -0.5f,1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { 0.5f,	0.5f,	 -0.5f,1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },

	// mặt phải, màu green
	{ {  0.0f,	 0.9f,	 0.0f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	0.5f,	-0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },

	// mặt trái, màu blue
	{ {  0.0f,	 0.9f,	 0.0f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	 0.5f,	 -0.5f,1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },

	// mặt trước, màu white
	{ {  0.0f,	 0.9f,	 0.0f,	1.0f },{ 1.0f,	1.0f,	1.0f,	1.0f } },
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
};




const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].XYZW);

int CurrentWidth = 700,
CurrentHeight = 700;

GLuint
VaoId,
VboId,
ColorBufferId,
VertexShaderId,
FragmentShaderId,
ProgramId;


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

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// vẽ với 36 điểm đỉnh
	glDrawArrays(GL_TRIANGLES, 0, 54);

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
	}
}
// ------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Box + Pyramid");

	glewExperimental = GL_TRUE;
	glewInit();

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
