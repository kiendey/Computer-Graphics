
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
	{ { -0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	// v7-v2-v1
	{ { -0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },

	// v7-v4-v3 (bottom)
	{ { -0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { 0.5f,	-0.5f,	 0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	// v3-v2-v7
	{ { 0.5f,	-0.5f,	 0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { -0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },

	// v4-v7-v6 (back)
	{ { 0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { -0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { -0.5f,	0.5f,	 -0.5f,1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	// v6-v5-v4
	{ { -0.5f,	 0.5f,	 -0.5f,1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { 0.5f,	0.5f,	 -0.5f,1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { 0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } }
};

const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].XYZW);

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

int
CurrentWidth = 800,
CurrentHeight = 600;

GLuint
VaoId,
VboId,
VertexShaderId,
FragmentShaderId,
ProgramId;

MatrixStack  mvstack;

mat4  model_mat_cpp;

GLuint
model_mat_location,
projection_mat_location;

// kích thước các bộ phận robot
#define TORSO_HEIGHT 5.0f
#define TORSO_WIDTH 1.0f

#define HEAD_HEIGHT 1.5f
#define HEAD_WIDTH 0.8f


#define UPPER_ARM_HEIGHT 3.0f
#define UPPER_ARM_WIDTH  1.0f

#define LOWER_ARM_HEIGHT 2.0f
#define LOWER_ARM_WIDTH  0.5f

#define UPPER_LEG_HEIGHT 3.0f
#define UPPER_LEG_WIDTH  1.0f

#define LOWER_LEG_HEIGHT 2.0f
#define LOWER_LEG_WIDTH  0.5f

	// thiết lập chỉ mục cho menu, 
	// sử dụng các chỉ số này cho các joint angles
enum {
	Torso,			//0
	Head1,			//1
	Head2,			//2
	RightUpperArm,	//3
	RightLowerArm,	//4
	LeftUpperArm,	//5
	LeftLowerArm,	//6
	RightUpperLeg,	//7
	RightLowerLeg,	//8
	LeftUpperLeg,	//9
	LeftLowerLeg,	//10
	NumJointAngles,	//11
	Quit			//12
};

// giá trị ban đầu của các Joint angles
GLfloat
theta[NumJointAngles] = {
	0.0,    // Torso
	0.0,    // Head1
	0.0,    // Head2
	0.0,    // RightUpperArm
	0.0,    // RightLowerArm
	0.0,    // LeftUpperArm
	0.0,    // LeftLowerArm
	180.0,  // RightUpperLeg
	0.0,    // RightLowerLeg
	180.0,  // LeftUpperLeg
	0.0     // LeftLowerLeg
};

// khởi tạo đối tượng quay
GLint angle = Torso;

// ------------------------------------------
	// thân
void torso()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, TORSO_HEIGHT / 2.0f, 0.0)) *
		scale(vec3(TORSO_WIDTH, TORSO_HEIGHT, TORSO_WIDTH));

	mat4 model_torso = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
// ------------------------------------------
	// đầu
void head()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, HEAD_HEIGHT / 2.0f, 0.0)) *
		scale(vec3(HEAD_WIDTH, HEAD_HEIGHT, HEAD_WIDTH));

	mat4 model_head = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_head.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
// ------------------------------------------
	// tay trái trên
void left_upper_arm()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, UPPER_ARM_HEIGHT / 2.0f, 0.0)) *
		scale(vec3(UPPER_ARM_WIDTH, UPPER_ARM_HEIGHT, UPPER_ARM_WIDTH));

	mat4 model_left_upper_arm = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_left_upper_arm.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
// ------------------------------------------
	// tay trái dưới
void left_lower_arm()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, LOWER_ARM_HEIGHT / 2.0f, 0.0)) *
		scale(vec3(LOWER_ARM_WIDTH, LOWER_ARM_HEIGHT, LOWER_ARM_WIDTH));

	mat4 model_left_lower_arm = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_left_lower_arm.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
// ------------------------------------------
	// tay phải trên
void right_upper_arm()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, UPPER_ARM_HEIGHT / 2.0f, 0.0)) *
		scale(vec3(UPPER_ARM_WIDTH, UPPER_ARM_HEIGHT, UPPER_ARM_WIDTH));

	mat4 model_right_upper_arm = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_right_upper_arm.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
// ------------------------------------------
	// tay phải dưới
void right_lower_arm()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, LOWER_ARM_HEIGHT / 2.0f, 0.0)) *
		scale(vec3(LOWER_ARM_WIDTH, LOWER_ARM_HEIGHT, LOWER_ARM_WIDTH));

	mat4 model_right_lower_arm = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_right_lower_arm.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
// ------------------------------------------
	// chân trái trên
void left_upper_leg()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, UPPER_LEG_HEIGHT / 2.0f, 0.0)) *
		scale(vec3(UPPER_LEG_WIDTH, UPPER_LEG_HEIGHT, UPPER_LEG_WIDTH));

	mat4 model_left_upper_leg = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_left_upper_leg.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
// ------------------------------------------
	// chân trái dưới
void left_lower_leg()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, LOWER_LEG_HEIGHT / 2.0f, 0.0)) *
		scale(vec3(LOWER_LEG_WIDTH, LOWER_LEG_HEIGHT, LOWER_LEG_WIDTH));

	mat4 model_left_lower_leg = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_left_lower_leg.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
// ------------------------------------------
	// chân phải trên
void right_upper_leg()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, UPPER_LEG_HEIGHT / 2.0f, 0.0)) *
		scale(vec3(UPPER_LEG_WIDTH, UPPER_LEG_HEIGHT, UPPER_LEG_WIDTH));

	mat4 model_right_upper_leg = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_right_upper_leg.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
// ------------------------------------------
	// chân phải dưới
void right_lower_leg()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, LOWER_LEG_HEIGHT / 2.0f, 0.0)) *
		scale(vec3(LOWER_LEG_WIDTH, LOWER_LEG_HEIGHT, LOWER_LEG_WIDTH));

	mat4 model_right_lower_leg = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_right_lower_leg.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
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
	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");
	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// thân
	model_mat_cpp = rotate_y(theta[Torso]);
	torso();

	// đầu 
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp *
		translate(vec3(0.0, TORSO_HEIGHT + 0.5 * HEAD_HEIGHT, 0.0)) *
		rotate_x(theta[Head1]) *
		rotate_y(theta[Head2]) *
		translate(vec3(0.0, -0.5 * HEAD_HEIGHT, 0.0));
	head();
	model_mat_cpp = mvstack.pop();

	// tay trái
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp *
		translate(vec3(-(TORSO_WIDTH + UPPER_ARM_WIDTH), 0.9 * TORSO_HEIGHT, 0.0)) *
		rotate_x(theta[LeftUpperArm]);
	left_upper_arm();

	model_mat_cpp = model_mat_cpp *
		translate(vec3(0.0, UPPER_ARM_HEIGHT, 0.0)) *
		rotate_x(theta[LeftLowerArm]);
	left_lower_arm();
	model_mat_cpp = mvstack.pop();

	// tay phải
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp *
		translate(vec3(TORSO_WIDTH + UPPER_ARM_WIDTH, 0.9 * TORSO_HEIGHT, 0.0)) *
		rotate_x(theta[RightUpperArm]);
	right_upper_arm();

	model_mat_cpp = model_mat_cpp *
		translate(vec3(0.0, UPPER_ARM_HEIGHT, 0.0)) *
		rotate_x(theta[RightLowerArm]);
	right_lower_arm();
	model_mat_cpp = mvstack.pop();

	// chân trái
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp *
		translate(vec3(-(TORSO_WIDTH + UPPER_LEG_WIDTH), 0.1f * UPPER_LEG_HEIGHT, 0.0f)) *
		rotate_x(theta[LeftUpperLeg]);
	left_upper_leg();

	model_mat_cpp = model_mat_cpp *
		translate(vec3(0.0f, UPPER_LEG_HEIGHT, 0.0f)) *
		rotate_x(theta[LeftLowerLeg]);
	left_lower_leg();
	model_mat_cpp = mvstack.pop();

	// chân phải
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp *
		translate(vec3(TORSO_WIDTH + UPPER_LEG_WIDTH, 0.1f * UPPER_LEG_HEIGHT, 0.0f)) *
		rotate_x(theta[RightUpperLeg]);
	right_upper_leg();

	model_mat_cpp = model_mat_cpp *
		translate(vec3(0.0f, UPPER_LEG_HEIGHT, 0.0f)) *
		rotate_x(theta[RightLowerLeg]);
	right_lower_leg();
	model_mat_cpp = mvstack.pop();

	glutSwapBuffers();
}
// ------------------------------------------
void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;

	glViewport(0, 0, CurrentWidth, CurrentHeight);

	float  left = -10.0, right = 10.0;
	float  bottom = -5.0, top = 15.0;
	float  zNear = -10.0, zFar = 10.0;

	float aspect = float(CurrentWidth) / CurrentHeight;

	if (aspect > 1.0) {
		left *= aspect;
		right *= aspect;
	}
	else {
		bottom /= aspect;
		top /= aspect;
	}

	mat4 projection = ortho(left, right, bottom, top, zNear, zFar);
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, projection.m);

	model_mat_cpp = identity_mat4();
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
void MouseFunc(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		theta[angle] += 5.0;
		if (theta[angle] > 360.0) { theta[angle] -= 360.0; }
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		theta[angle] -= 5.0;
		if (theta[angle] < 0.0) { theta[angle] += 360.0; }
	}

	glutPostRedisplay();
}
// ------------------------------------------
void menu(int option)
{
	if (option == Quit) {
		exit(EXIT_SUCCESS);
	}

	angle = option;
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
	glutCreateWindow("Torso");

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

	// tạo menu
	glutCreateMenu(menu);
	glutAddMenuEntry("torso", Torso);
	glutAddMenuEntry("head1", Head1);
	glutAddMenuEntry("head2", Head2);
	glutAddMenuEntry("right_upper_arm", RightUpperArm);
	glutAddMenuEntry("right_lower_arm", RightLowerArm);
	glutAddMenuEntry("left_upper_arm", LeftUpperArm);
	glutAddMenuEntry("left_lower_arm", LeftLowerArm);
	glutAddMenuEntry("right_upper_leg", RightUpperLeg);
	glutAddMenuEntry("right_lower_leg", RightLowerLeg);
	glutAddMenuEntry("left_upper_leg", LeftUpperLeg);
	glutAddMenuEntry("left_lower_leg", LeftLowerLeg);
	glutAddMenuEntry("quit", Quit);

	// kích hoạt menu bằng nhấn nút giữa chuột
	glutAttachMenu(GLUT_MIDDLE_BUTTON);

	glutMainLoop();
	return 0;
}

