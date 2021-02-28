//
//Pelin Durak
//assignment 2 - Rubik's Cube
//
//when you start the application, press 'H' for help

#include "Angel.h"
#include  "mat.h"
#include <sstream>
#include <string>
#include <fstream>

using std::cout;
using std::endl;

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

const int NumPoints = 972;		// (27 cubes) * (6 faces) * (6 vertices/face)
const int NumVertices = 64;		// (4 points/axis) ^ (3 axes)

float size = 0.15;			// Sub-cube size

int width, height;
GLuint Projection;

mat3 posOfSub[6] = {
	mat3(0,1,2,
	3,4,5,
	6,7,8),			// Front
	mat3(18,19,20,
	9,10,11,
	0,1,2),			// Left
	mat3(2,11,20,
	5,14,23,
	8,17,26),		// Bottom
	mat3(6,7,8,
	15,16,17,
	24,25,26),		// Right
	mat3(18,9,0,
	21,12,3,
	24,15,6),		// Top
	mat3(24,25,26,
	21,22,23,
	18,19,20),		// Behind
};

int animate = 0;
int numRot = 0;
int randRot = 0;
int randSub = 0;

bool allowInput = true;

point4 points[NumPoints];
color4 colors[NumPoints];

point4 vertices[NumVertices] = {
	point4(-3.0 * size,  3.0 * size,  -3.0 * size, 1.0),
	point4(-3.0 * size,  1.0 * size,  -3.0 * size, 1.0),
	point4(-3.0 * size,  -1.0 * size,  -3.0 * size, 1.0),
	point4(-3.0 * size,  -3.0 * size,  -3.0 * size, 1.0),
	point4(-1.0 * size,  3.0 * size,  -3.0 * size, 1.0),
	point4(-1.0 * size,  1.0 * size,  -3.0 * size, 1.0),
	point4(-1.0 * size,  -1.0 * size,  -3.0 * size, 1.0),
	point4(-1.0 * size,  -3.0 * size,  -3.0 * size, 1.0),
	point4(1.0 * size,  3.0 * size,  -3.0 * size, 1.0),
	point4(1.0 * size,  1.0 * size,  -3.0 * size, 1.0),
	point4(1.0 * size,  -1.0 * size,  -3.0 * size, 1.0),
	point4(1.0 * size,  -3.0 * size,  -3.0 * size, 1.0),
	point4(3.0 * size,  3.0 * size,  -3.0 * size, 1.0),
	point4(3.0 * size,  1.0 * size,  -3.0 * size, 1.0),
	point4(3.0 * size,  -1.0 * size,  -3.0 * size, 1.0),
	point4(3.0 * size,  -3.0 * size,  -3.0 * size, 1.0),
	point4(-3.0 * size,  3.0 * size,  -1.0 * size, 1.0),
	point4(-3.0 * size,  1.0 * size,  -1.0 * size, 1.0),
	point4(-3.0 * size,  -1.0 * size,  -1.0 * size, 1.0),
	point4(-3.0 * size,  -3.0 * size,  -1.0 * size, 1.0),
	point4(-1.0 * size,  3.0 * size,  -1.0 * size, 1.0),
	point4(-1.0 * size,  1.0 * size,  -1.0 * size, 1.0),
	point4(-1.0 * size,  -1.0 * size,  -1.0 * size, 1.0),
	point4(-1.0 * size,  -3.0 * size,  -1.0 * size, 1.0),
	point4(1.0 * size,  3.0 * size,  -1.0 * size, 1.0),
	point4(1.0 * size,  1.0 * size,  -1.0 * size, 1.0),
	point4(1.0 * size,  -1.0 * size,  -1.0 * size, 1.0),
	point4(1.0 * size,  -3.0 * size,  -1.0 * size, 1.0),
	point4(3.0 * size,  3.0 * size,  -1.0 * size, 1.0),
	point4(3.0 * size,  1.0 * size,  -1.0 * size, 1.0),
	point4(3.0 * size,  -1.0 * size,  -1.0 * size, 1.0),
	point4(3.0 * size,  -3.0 * size,  -1.0 * size, 1.0),
	point4(-3.0 * size,  3.0 * size,  1.0 * size, 1.0),
	point4(-3.0 * size,  1.0 * size,  1.0 * size, 1.0),
	point4(-3.0 * size,  -1.0 * size,  1.0 * size, 1.0),
	point4(-3.0 * size,  -3.0 * size,  1.0 * size, 1.0),
	point4(-1.0 * size,  3.0 * size,  1.0 * size, 1.0),
	point4(-1.0 * size,  1.0 * size,  1.0 * size, 1.0),
	point4(-1.0 * size,  -1.0 * size,  1.0 * size, 1.0),
	point4(-1.0 * size,  -3.0 * size,  1.0 * size, 1.0),
	point4(1.0 * size,  3.0 * size,  1.0 * size, 1.0),
	point4(1.0 * size,  1.0 * size,  1.0 * size, 1.0),
	point4(1.0 * size,  -1.0 * size,  1.0 * size, 1.0),
	point4(1.0 * size,  -3.0 * size,  1.0 * size, 1.0),
	point4(3.0 * size,  3.0 * size,  1.0 * size, 1.0),
	point4(3.0 * size,  1.0 * size,  1.0 * size, 1.0),
	point4(3.0 * size,  -1.0 * size,  1.0 * size, 1.0),
	point4(3.0 * size,  -3.0 * size,  1.0 * size, 1.0),
	point4(-3.0 * size,  3.0 * size,  3.0 * size, 1.0),
	point4(-3.0 * size,  1.0 * size,  3.0 * size, 1.0),
	point4(-3.0 * size,  -1.0 * size,  3.0 * size, 1.0),
	point4(-3.0 * size,  -3.0 * size,  3.0 * size, 1.0),
	point4(-1.0 * size,  3.0 * size,  3.0 * size, 1.0),
	point4(-1.0 * size,  1.0 * size,  3.0 * size, 1.0),
	point4(-1.0 * size,  -1.0 * size,  3.0 * size, 1.0),
	point4(-1.0 * size,  -3.0 * size,  3.0 * size, 1.0),
	point4(1.0 * size,  3.0 * size,  3.0 * size, 1.0),
	point4(1.0 * size,  1.0 * size,  3.0 * size, 1.0),
	point4(1.0 * size,  -1.0 * size,  3.0 * size, 1.0),
	point4(1.0 * size,  -3.0 * size,  3.0 * size, 1.0),
	point4(3.0 * size,  3.0 * size,  3.0 * size, 1.0),
	point4(3.0 * size,  1.0 * size,  3.0 * size, 1.0),
	point4(3.0 * size,  -1.0 * size,  3.0 * size, 1.0),
	point4(3.0 * size,  -3.0 * size,  3.0 * size, 1.0),

};

enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
GLfloat  Theta[NumAxes] = { 0.0, 0.0, 0.0 };
enum { x_offset = 1, y_offset = 4, z_offset = 16 };


mat4  transformZ = (RotateX(0) *
	RotateY(0) *
	RotateZ(9.0));

mat4  transformZNeg = (RotateX(0) *
	RotateY(0) *
	RotateZ(-9.0));

mat4  transformY = (RotateX(0) *
	RotateY(9.0) *
	RotateZ(0));

mat4  transformYNeg = (RotateX(0) *
	RotateY(-9.0) *
	RotateZ(0));

mat4  transformX = (RotateX(9.0) *
	RotateY(0) *
	RotateZ(0));

mat4  transformXNeg = (RotateX(-9.0) *
	RotateY(0) *
	RotateZ(0));

int index = 0;
//generating a square (one side of a subcube)
void quad(int a, int b, int c, int d, color4 color) {
	colors[index] = color; points[index] = vertices[a]; index++;
	colors[index] = color; points[index] = vertices[b]; index++;
	colors[index] = color; points[index] = vertices[c]; index++;
	colors[index] = color; points[index] = vertices[b]; index++;
	colors[index] = color; points[index] = vertices[d]; index++;
	colors[index] = color; points[index] = vertices[c]; index++;
}


//k : front=0, left=1, bottom=2, right=3, top=4, behind=5
//positive : if the face is rotated in clockwise direction
void updatePos(int k, bool positive) {

	//update the selected face
	if (positive) {
		posOfSub[k] =
			mat3(posOfSub[k][0][2], posOfSub[k][1][2], posOfSub[k][2][2],
				posOfSub[k][0][1], posOfSub[k][1][1], posOfSub[k][2][1],
				posOfSub[k][0][0], posOfSub[k][1][0], posOfSub[k][2][0]);
	}
	else {
		posOfSub[k] =
			mat3(posOfSub[k][2][0], posOfSub[k][1][0], posOfSub[k][0][0],
				posOfSub[k][2][1], posOfSub[k][1][1], posOfSub[k][0][1],
				posOfSub[k][2][2], posOfSub[k][1][2], posOfSub[k][0][2]);
	}

	//updating other faces according to the rotated face
	switch (k) {
	case 0: //if front face is rotated
		for (int i = 0; i < 3; i++) {
			posOfSub[1][2][i] = posOfSub[0][0][i];		//update left face
			posOfSub[2][i][0] = posOfSub[0][i][2];		//update bottom face
			posOfSub[3][0][i] = posOfSub[0][2][i];		//update right face	
			posOfSub[4][i][2] = posOfSub[0][i][0];		//update top face
		}
		break;

	case 1: //if left face is rotated
		for (int i = 0; i < 3; i++) {
			posOfSub[0][0][i] = posOfSub[1][2][i];		//update front face
			posOfSub[2][0][2 - i] = posOfSub[1][i][2];	//update bottom face
			posOfSub[4][0][i] = posOfSub[1][i][0];		//update top face
			posOfSub[5][2][i] = posOfSub[1][0][i];		//update behind face
		}
		break;

	case 2: //if bottom face is rotated
		for (int i = 0; i < 3; i++) {
			posOfSub[0][i][2] = posOfSub[2][0][i];		//update front face
			posOfSub[1][i][2] = posOfSub[2][0][2 - i];	//update left face
			posOfSub[3][i][2] = posOfSub[2][2][i];		//update right face
			posOfSub[5][i][2] = posOfSub[2][2 - i][2];	//update behind face
		}
		break;

	case 3: //if right face is rotated
		for (int i = 0; i < 3; i++) {
			posOfSub[0][2][i] = posOfSub[3][0][i];		//update front face
			posOfSub[2][2][i] = posOfSub[3][i][2];		//update bottom face
			posOfSub[4][2][2 - i] = posOfSub[3][0][i];	//update top face
			posOfSub[5][0][i] = posOfSub[3][2][i];		//update behind face
		}
		break;

	case 4: //if top face is rotated
		for (int i = 0; i < 3; i++) {
			posOfSub[0][i][0] = posOfSub[4][i][2];		//update front face
			posOfSub[1][i][0] = posOfSub[4][0][i];		//update left face
			posOfSub[3][0][i] = posOfSub[4][2][2 - i];	//update right face
			posOfSub[5][2 - i][0] = posOfSub[4][i][0];	//update behind face
		}
		break;

	case 5: //if behind face is rotated
		for (int i = 0; i < 3; i++) {
			posOfSub[1][0][i] = posOfSub[5][2][i];		//update left face
			posOfSub[2][2 - i][2] = posOfSub[5][i][2];	//update bottom face
			posOfSub[3][2][i] = posOfSub[5][0][i];		//update right face
			posOfSub[4][i][0] = posOfSub[5][2 - i][0];	//update top face
		}
		break;

	}
}


//pos: sub cube number
//matrix: rotation matrix to be applied to the points of the subcube 
void rotateSubCube(int pos, mat4 matrix) {
	for (int i = 36 * pos; i < 36 + 36 * pos; i++) {
		points[i] = matrix * points[i];
	}
	glutPostRedisplay();
}

//rotating the selected face of the cube
void rotateFace(int face) {
	switch (face) {
	case 0:
		//rotate front face around z, counterclockwise
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				rotateSubCube(posOfSub[0][i][j], transformZ);
			}
		}
		break;
	case 1:
		//rotate front face around z, clockwise
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				rotateSubCube(posOfSub[0][i][j], transformZNeg);
			}
		}
		break;
	case 2:
		//rotate left face around x, counterclockwise
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				rotateSubCube(posOfSub[1][i][j], transformX);
			}
		}
		break;
	case 3:
		//rotate left face around x, clockwise
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				rotateSubCube(posOfSub[1][i][j], transformXNeg);
			}
		}
		break;
	case 4:
		//rotate bottom face around y, counterclockwise
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				rotateSubCube(posOfSub[2][i][j], transformY);
			}
		}
		break;
	case 5:
		//rotate bottom face around y, clockwise
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				rotateSubCube(posOfSub[2][i][j], transformYNeg);
			}
		}
		break;
	case 6:
		//rotate right face around x, counterclockwise
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				rotateSubCube(posOfSub[3][i][j], transformXNeg);
			}
		}
		break;
	case 7:
		//rotate right face around x, clockwise
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				rotateSubCube(posOfSub[3][i][j], transformX);
			}
		}
		break;
	case 8:
		//rotate top face around y, counterclockwise
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				rotateSubCube(posOfSub[4][i][j], transformYNeg);
			}
		}
		break;
	case 9:
		//rotate top face around y, clockwise
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				rotateSubCube(posOfSub[4][i][j], transformY);
			}
		}
		break;
	case 10:
		//rotate behind face around z, counterclockwise
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				rotateSubCube(posOfSub[5][i][j], transformZNeg);
			}
		}
		break;
	case 11:
		//rotate behind face around z, clockwise
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				rotateSubCube(posOfSub[5][i][j], transformZ);
			}
		}
		break;
	}
	glutPostRedisplay();
	if (animate < 9) {
		glutTimerFunc(20, rotateFace, face);
		animate++;
		glutPostRedisplay();
	}
}


//random initialization
void randomInit(int randSub) {
	animate = 0;
	switch (randSub) {
	case 0:
		rotateFace(0);
		updatePos(0, false);
		break;
	case 1:
		rotateFace(1);
		updatePos(0, true);
		break;
	case 2:
		rotateFace(2);
		updatePos(1, false);
		break;
	case 3:
		rotateFace(3);
		updatePos(1, true);
		break;
	case 4:
		rotateFace(4);
		updatePos(2, false);
		break;
	case 5:
		rotateFace(5);
		updatePos(2, true);
		break;
	case 6:
		rotateFace(6);
		updatePos(3, false);
		break;
	case 7:
		rotateFace(7);
		updatePos(3, true);
		break;
	case 8:
		rotateFace(8);
		updatePos(4, false);
		break;
	case 9:
		rotateFace(9);
		updatePos(4, true);
		break;
	case 10:
		rotateFace(10);
		updatePos(5, false);
		break;
	case 11:
		rotateFace(11);
		updatePos(5, true);
		break;
	}
	if (numRot < randRot) {
		glutTimerFunc(500, randomInit, rand() % 12);
		numRot++;
		glutPostRedisplay();
	}
}


//generating a subcube from 6 squares
void subcube(int x, int y, int z) {
	int index = x * x_offset + y * y_offset + z * z_offset;
	quad(index, index + x_offset, index + y_offset, index + x_offset + y_offset, color4(0.9, 0.0, 0.0, 1.0));
	quad(index, index + x_offset, index + z_offset, index + x_offset + z_offset, color4(0.9, 0.9, 0.9, 1.0));
	quad(index, index + z_offset, index + y_offset, index + z_offset + y_offset, color4(0.0, 0.9, 0.0, 1.0));
	quad(index + x_offset, index + x_offset + z_offset, index + x_offset + y_offset, index + x_offset + y_offset + z_offset, color4(0.0, 0.0, 0.9, 1.0));
	quad(index + y_offset, index + x_offset + y_offset, index + y_offset + z_offset, index + x_offset + y_offset + z_offset, color4(0.9, 0.9, 0.0, 1.0));
	quad(index + z_offset, index + x_offset + z_offset, index + y_offset + z_offset, index + x_offset + y_offset + z_offset, color4(0.9, 0.0, 0.9, 1.0));
}

//displaying the position matrix
void displayPos() {
	cout << "\nFront" << posOfSub[0] << "\nLeft" <<
		posOfSub[1] << "\nBottom" << posOfSub[2] << "\nRight" <<
		posOfSub[3] << "\nTop" << posOfSub[4] << "\nBehind" << posOfSub[5] << endl;
}


void rubikscube() {
	for (int z = 0; z < 3; z++) {
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				subcube(x, y, z);
			}
		}
	}
}


void init()
{
	rubikscube();

	// Create a vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create and initialize a buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);

	// Load shaders and use the resulting shader program
	GLuint program = InitShader("vshader32.glsl", "fshader32.glsl");
	glUseProgram(program);

	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)));


	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5, 0.5, 0.5, 1.0);
}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mat4  transform = (RotateX(Theta[Xaxis]) *
		RotateY(Theta[Yaxis]) *
		RotateZ(Theta[Zaxis]));

	point4  transformed_points[NumPoints];

	for (int i = 0; i < NumPoints; ++i) {
		transformed_points[i] = transform * points[i];
	}

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(transformed_points),
		transformed_points);


	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y)
{
	randRot = rand() % 6 + 4;
	numRot = 0;
	animate = 0;
	if (allowInput) {
		switch (key) {
		case 033: // Escape Key
		case 'q': case 'Q':
			exit(EXIT_SUCCESS);
			break;
		case 'g': case 'G':
			displayPos();
			break;
		case 'w': case 'W':
			Theta[Xaxis] -= 2;
			if (Theta[Xaxis] > 360.0) {
				Theta[Xaxis] -= 360.0;
			}
			else if (Theta[Xaxis] < 0) {
				Theta[Xaxis] += 360.0;
			}
			break;
		case 'a': case 'A':
			Theta[Yaxis] -= 2;
			if (Theta[Yaxis] >= 360.0) {
				Theta[Yaxis] -= 360.0;
			}
			else if (Theta[Yaxis] < 0) {
				Theta[Yaxis] += 360.0;
			}
			break;
		case 'd': case 'D':
			Theta[Yaxis] += 2;
			if (Theta[Yaxis] >= 360.0) {
				Theta[Yaxis] -= 360.0;
			}
			else if (Theta[Yaxis] < 0) {
				Theta[Yaxis] += 360.0;
			}
			break;
		case 's': case 'S':
			Theta[Xaxis] += 2;
			if (Theta[Xaxis] > 360.0) {
				Theta[Xaxis] -= 360.0;
			}
			else if (Theta[Xaxis] < 0) {
				Theta[Xaxis] += 360.0;
			}
			break;
		case 'r': case 'R':
			randomInit(rand() % 12);
			break;
		case 'h': case 'H':
			cout << "\n   Assignment 2 hotkeys: " << endl;
			cout << "\tW -- Rotate the cube up" << endl;
			cout << "\tS -- Rotate the cube down" << endl;
			cout << "\tA -- Rotate the cube left" << endl;
			cout << "\tD -- Rotate the cube right" << endl;
			cout << "\tQ -- Exit the application" << endl;
			cout << "\tR -- Random initialization" << endl;
			cout << "\tG -- Print indices (for debugging purposes)" << endl;

			cout << "\n\t1 -- Rotate front face around z, counterclockwise" << endl;
			cout << "\t2 -- Rotate front face around z, clockwise" << endl;
			cout << "\t3 -- Rotate left face around x, counterclockwise" << endl;
			cout << "\t4 -- Rotate left face around x, clockwise" << endl;
			cout << "\t5 -- Rotate bottom face around y, counterclockwise" << endl;
			cout << "\t6 -- Rotate bottom face around y, clockwise" << endl;
			cout << "\t7 -- Rotate right face around x, counterclockwise" << endl;
			cout << "\t8 -- Rotate right face around x, clockwise" << endl;
			cout << "\t9 -- Rotate top face around y, counterclockwise" << endl;
			cout << "\t0 -- Rotate top face around y, clockwise" << endl;
			cout << "\t* -- Rotate behind face around z, counterclockwise" << endl;
			cout << "\t- -- Rotate behind face around z, clockwise" << endl;
			break;
		case '1':
			rotateFace(0);
			updatePos(0, false);
			break;
		case '2':
			rotateFace(1);
			updatePos(0, true);
			break;
		case '3':
			rotateFace(2);
			updatePos(1, false);
			break;
		case '4':
			rotateFace(3);
			updatePos(1, true);
			break;
		case '5':
			rotateFace(4);
			updatePos(2, false);
			break;
		case '6':
			rotateFace(5);
			updatePos(2, true);
			break;
		case '7':
			rotateFace(6);
			updatePos(3, false);
			break;
		case '8':
			rotateFace(7);
			updatePos(3, true);
			break;
		case '9':
			rotateFace(8);
			updatePos(4, false);
			break;
		case '0':
			rotateFace(9);
			updatePos(4, true);
			break;
		case '*':
			rotateFace(10);
			updatePos(5, false);
			break;
		case '-':
			rotateFace(11);
			updatePos(5, true);
			break;
		}
	}
}


void idle(void)
{
	glutPostRedisplay();
}


void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	mat4 projection;
	width = w;
	height = h;
	if (w <= h)
		projection = Ortho(-1.0, 1.0, -1.0 * (GLfloat)h /
		(GLfloat)w, 1.0 * (GLfloat)h / (GLfloat)w, -1.0, 1.0);
	else projection = Ortho(-1.0* (GLfloat)w / (GLfloat)h, 1.0 *
		(GLfloat)w / (GLfloat)h, -1.0, 1.0, -1.0, 1.0);
	glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Rubik's Cube");

	glewExperimental = GL_TRUE;
	glewInit();

	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}