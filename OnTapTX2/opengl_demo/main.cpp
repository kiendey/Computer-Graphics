
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <Vector_Matrix.h>


using namespace std;

typedef struct
{
	float xyzw[4];
	float rgba[4];
	float normal[4];
} Vertex;
//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3
	// Mảng dữ liệu
Vertex Vertices[] =
{
	// v0-v1-v2 (front)
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0, 0, 1, 0 } },
	{ { -0.5f,	 0.5f,	0.5f, 1.0 },{ 0.0f, 1.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 1.0f, 1.0f },{ 0, 0, 1, 0 } },
	// v2-v3-v0
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },
	{ {  0.5f,	-0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0, 1, 0 } },

	// v0-v3-v4 (right)
	{ { 0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
	{ { 0.5f,	-0.5f,   0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
	{ { 0.5f,	-0.5f,  -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
	// v4-v5-v0
	{ { 0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
	{ { 0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
	{ { 0.5f,	 0.5f,   0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },

	// v0-v5-v6 (top)
	{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
	{ {  0.5f,	0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
	{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
	// v6-v1-v0
	{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
	{ { -0.5f,	0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },
	{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 1, 0, 0 } },

	// v1-v6-v7 (left)
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
	// v7-v2-v1
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },

	// v7-v4-v3 (bottom)
	{ { -0.5f,	 -0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
	// v3-v2-v7
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },

	// v4-v7-v6 (back)
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
	// v6-v5-v4
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
	{ {  0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } }
};
// ----------------------------------------

const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].xyzw);
const size_t NormalOffset = sizeof(Vertices[0].xyzw) + sizeof(Vertices[1].rgba);

int CurrentWidth = 700,
CurrentHeight = 700;

GLuint
VaoId,
VboId,
VertexShaderId,
FragmentShaderId,
ProgramId;

float tran = 0.0;
float theta = 0.0;

mat4
model_mat_cpp,
view_mat_cpp,
projection_mat_cpp;

int
model_mat_location,
view_mat_location,
projection_mat_location;

float
r[] = { 0.0f, 0.0f, 0.0f },
s[] = { 1.0f, 1.0f, 1.0f },
t[] = { 0.0f, 0.0f, 0.0f };

// định nghĩa stack cho ma trận
class MatrixStack {
	int    index;
	int    size;
	mat4* matrices;

public:
	MatrixStack(int numMatrices = 32) :index(0), size(numMatrices)
	{
		matrices = new mat4[numMatrices];
	}

	~MatrixStack()
	{
		delete[]matrices;
	}

	// phép toán đẩy vào
	mat4& push(const mat4& m) {
		assert(index + 1 < size);
		matrices[index++] = m;
		return matrices[index];
	}

	// phép toán lấy ra
	mat4& pop(void) {
		assert(index - 1 >= 0);
		index--;
		return matrices[index];
	}
};

MatrixStack  mvstack;

bool
translated = false,
rotated = false,
scaled = false;


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

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);	// position
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset); //color
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)NormalOffset); //normal

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
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

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}


// ------------------------------------------

void base()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(0.8, 0.8, 0.2));
	mat4 model_base = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();

}
void gioKHONG()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(0.1f, 0.3f, 0.01f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();

}

void gioCHIN()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(0.1f, 0.3f, 0.01f));
	mat4 model_base = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();

}

void gioSAU()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(0.1f, 0.3f, 0.01f));
	mat4 model_base = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();

}

void gioBA()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(0.1f, 0.3f, 0.01f));
	mat4 model_base = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();

}

void kim()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = scale(vec3(0.1f, 0.5f, 0.01f));

	mat4 model_MS = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_MS.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();

}


void DisplayFunc(void)
{
	model_mat_cpp = identity_mat4();
	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	if (translated)
	{
		model_mat_cpp = model_mat_cpp * translate(vec3(t[0], t[1], t[2]));
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}
	if (rotated)
	{
		model_mat_cpp = model_mat_cpp * rotate_x(r[0])
			* rotate_y(r[1])
			* rotate_z(r[2]);
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}
	if (scaled)
	{
		model_mat_cpp = model_mat_cpp * scale(vec3(s[0], s[1], s[2]));
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}

	vec3	eye(-0.8f, -0.8f, 2.0f),
		at(0.0f, 0.0f, 0.0f),
		up(0.0f, 1.0f, 0.0f);

	view_mat_cpp = lookat(eye, at, up);
	view_mat_location = glGetUniformLocation(ProgramId, "view_mat_shader");
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat_cpp.m);

	float
		znear = 0.1f,
		zfar = 100.0f,
		fov = 90.0f,
		aspect = (float)CurrentWidth / CurrentHeight;
	projection_mat_cpp = perspective(fov, aspect, znear, zfar);
	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, projection_mat_cpp.m);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//mat dong ho
	model_mat_cpp = model_mat_cpp * translate(vec3(tran, 0, 0));
	base();
	
	//kim0
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0, 0.3, 0.105));
	gioKHONG();
	model_mat_cpp = mvstack.pop();

	//kim9
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.3, 0.0, 0.105)) * rotate_z(-90);
	gioCHIN();
	model_mat_cpp = mvstack.pop();

	//kim6
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0, -0.35, 0.105));
	gioSAU();
	model_mat_cpp = mvstack.pop();

	//kim3
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-0.39, 0, 0.105)) * rotate_z(-90);
	gioBA();
	model_mat_cpp = mvstack.pop();

	//Kim chinh
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp  * rotate_z(theta);
	model_mat_cpp = model_mat_cpp * translate(vec3(0, 0.2, 0.105));
	kim();
	model_mat_cpp = mvstack.pop();
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
		glutLeaveMainLoop();
		break;
	case 'x':
		r[0] -= 10.0f;
		rotated = true;
		break;
	case 'X':
		r[0] += 10.0f;
		rotated = true;
		break;

	case 'y':
		r[1] -= 10.0f;
		rotated = true;
		break;
	case 'Y':
		r[1] += 10.0f;
		rotated = true;
		break;

	case 'z':
		r[2] -= 10.0f;
		rotated = true;
		break;
	case 'Z':
		r[2] += 10.0f;
		rotated = true;
		break;

	case '=':
	case '+':
		s[0] *= 1.05f;
		s[1] *= 1.05f;
		s[2] *= 1.05f;
		scaled = true;
		break;

	case '-':
	case '_':
		s[0] /= 1.05f;
		s[1] /= 1.05f;
		s[2] /= 1.05f;
		scaled = true;
		break;

	case 'j':
		t[0] -= 0.05f;
		translated = true;
		break;
	case 'l':
		t[0] += 0.05f;
		translated = true;
		break;
	case 'i':
		t[1] += 0.05f;
		translated = true;
		break;
	case ',':
		t[1] -= 0.05f;
		translated = true;
		break;
	case 'g':
		t[2] -= 0.05f;
		translated = true;
		break;
	case 'h':
		t[2] += 0.05f;
		translated = true;
		break;
	case 't':
		tran += 0.05f;
		translated = true;
		break;
	
	case 'p':
		tran -= 0.05f;
		translated = true;
		break;
	case 's':
		theta += 30.0f;
		rotated = true;
		break;
	
}
}
// ----------------------------------------

	// Xử lý phím đặc biệt
void SpecialFunc(int key, int x, int y)
{

	switch (key)
	{
	case GLUT_KEY_LEFT:
		t[0] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_RIGHT:
		t[0] += 0.05f;
		translated = true;
		break;
	case GLUT_KEY_UP:
		t[1] += 0.05f;
		translated = true;
		break;
	case GLUT_KEY_DOWN:
		t[1] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_ALT_R:
		t[2] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_CTRL_R:
		t[2] += 0.05f;
		translated = true;
		break;
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
	glutCreateWindow("kIENDEPTRAI");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);
	glutCloseFunc(CloseFunc);

	glutMainLoop();
	return 0;
}


