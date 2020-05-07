#include <iostream>
#include <glut.h>
#include<math.h>
using namespace std;
#include <Windows.h>
#include <mmsystem.h>
bool playing = true;
int health1 = 21;
int health2 = 21;
float smaller1 = 1;
float smaller2 = 1;
bool turn1 = true;
bool shooting = false;
int power = 0;  //3 LEVELS 7,14,21
int px;
int py;
int px1;
int py1;
int p0[2];
int p1[2];
int p2[2];
int p3[2];
float t = 0;
void drawPower();
void drawHealth(int health);
void Key(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);
int* bezier(float t, int* p0, int* p1, int* p2, int* p3);
void drawBanana();
void drawBanana1();
void Animate(void);
void DrawBird();
void DrawDefender();
void drawMonkey();
#define pi 3.142857 
double movestep = 0;
double movestep1 = 0;
bool forward2 = true;
std::string text3;
void drawText(const char* text, int length, int x, int y);
void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	//wall
	if (!playing) {
		playing = false;
		glPushMatrix();
		glTranslated(140, 150, 0);
		glColor3f(1, 1, 1);
		GLUquadric* win1 = gluNewQuadric();
		gluDisk(win1, 0, 50, 50, 50);//slices w loop
		glColor3f(0, 0, 0);
		drawText(text3.data(), text3.size(), 310, 220);
		glPopMatrix();

	}

	glBegin(GL_QUADS); //tree base
	glColor3f(0.533, 0.298, 0.086);
	glVertex3f(151.0f, 0, 0.0f);
	glVertex3f(160.0f, 0, 0.0f);
	glVertex3f(160.0f, 59, 0.0f);
	glVertex3f(151.0f, 59, 0.0f);
	glEnd();

	glPushMatrix();//tree green part 1
	glTranslated(158, 84, 0);
	glColor3f(0.101, 0.678, 0.294);
	GLUquadric* c = gluNewQuadric();
	gluDisk(c, 0, 15, 50, 50);//slices w loop
	glPopMatrix();

	glPushMatrix();//tree green part 2
	glTranslated(150, 60, 0);
	glColor3f(0.101, 0.678, 0.294);
	GLUquadric* c2 = gluNewQuadric();
	gluDisk(c2, 0, 19, 50, 50);//slices w loop
	glPopMatrix();

glPushMatrix();//tree green part 3
	glTranslated(163, 60, 0);
	glColor3f(0.101, 0.678, 0.294);
	GLUquadric* c1 = gluNewQuadric();
	gluDisk(c1, 0, 19, 50, 50);//slices w loop
	glPopMatrix();
	//end wall

	glPushMatrix();
	glTranslatef(0, 50, 0);
	DrawBird();
	glPopMatrix();

	glPushMatrix();
	DrawDefender();
	glPopMatrix();

	glPushMatrix();
	glScalef(1, smaller1, 1);
	drawMonkey();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(295, 0, 0);
	glScalef(-1, smaller2, 1);
	drawMonkey();
	glPopMatrix();
	//cloud

	glPushMatrix();
	glTranslated(57, 267, 0);
	glColor3f(1, 1, 1);
	GLUquadric* w = gluNewQuadric();
	gluDisk(w, 0, 10, 50, 50);//slices w loop
	glPopMatrix();

	glBegin(GL_QUADS); // body of cloud
	glColor3f(1, 1, 1);
	glVertex3f(40, 245, 0.0f);
	glVertex3f(75, 245, 0.0f);
	glVertex3f(75, 265, 0.0f);
	glVertex3f(40, 265, 0.0f);
	glEnd();

	glPushMatrix();
	glTranslated(35, 260, 0);
	glColor3f(1, 1, 1);
	GLUquadric* w2 = gluNewQuadric();
	gluDisk(w2, 0, 15, 50, 50);//slices w loop
	glPopMatrix();


	glPushMatrix();
	glTranslated(80, 260, 0);
	glColor3f(1, 1, 1);
	GLUquadric* w1 = gluNewQuadric();
	gluDisk(w1, 0, 15, 50, 50);//slices w loop
	glPopMatrix();
	//end cloud
		//cloud2

	glPushMatrix();
	glTranslated(192, 267, 0);
	glColor3f(1, 1, 1);
	GLUquadric* a = gluNewQuadric();
	gluDisk(a, 0, 10, 50, 50);//slices w loop
	glPopMatrix();

	glBegin(GL_QUADS); // body of cloud
	glColor3f(1, 1, 1);
	glVertex3f(175, 245, 0.0f);
	glVertex3f(210, 245, 0.0f);
	glVertex3f(210, 265, 0.0f);
	glVertex3f(175, 265, 0.0f);
	glEnd();

	glPushMatrix();
	glTranslated(170, 260, 0);
	glColor3f(1, 1, 1);
	GLUquadric* a2 = gluNewQuadric();
	gluDisk(a2, 0, 15, 50, 50);//slices w loop
	glPopMatrix();


	glPushMatrix();
	glTranslated(215, 260, 0);
	glColor3f(1, 1, 1);
	GLUquadric* a1 = gluNewQuadric();
	gluDisk(a1, 0, 15, 50, 50);//slices w loop
	glPopMatrix();
	//end cloud
	//sun
	glPushMatrix();
	glTranslated(290, 290, 0);
	glColor3f(1.0, 0.9, 0.0);
	GLUquadric* sun = gluNewQuadric();
	gluDisk(sun, 0, 25, 50, 50);//slices w loop
	glPopMatrix();

	glBegin(GL_LINES);
	float x, y, i;

	// iterate y up to 2*pi, i.e., 360 degree 
	// with small increment in angle
	for (i = 0; i < (2 * pi); i += 0.09)
	{
		// 25 is radius of circle 
		// circle is defined as x=r*cos(i) and y=r*sin(i) 
		x = 25 * cos(i) + 290;
		y = 25 * sin(i) + 290;

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(x, y, 0.0f);
		glVertex3f(x - 8, y - 9, 0.0f);
	}
	glEnd();
	//end sun


	//TREE 2
	glBegin(GL_POLYGON);
	glVertex3f(18, 75, 0.0f);
	glVertex3f(18, 85, 0.0f);
	glVertex3f(28, 85, 0.0f);
	glVertex3f(28, 75, 0.0f);
	glEnd();
	glPushMatrix();
	glScaled(4, 4, 1);
	glTranslated(-50, -80, 0);
	for (double i = 0; i < 10; i += 3) {
		glBegin(GL_TRIANGLES);
		glColor3f(0.101, 0.678, 0.294);
		glVertex3f(52, 100 + i, 0.0f);
		glVertex3f(55, 106 + i, 0.0f);
		glVertex3f(60, 100 + i, 0.0f);
		glEnd();
	}
	glPopMatrix();
	//END TREE 2
	if (px > 235 || px1 > 235) {
		if (!shooting) {
			sndPlaySound(TEXT("pain100_2"), SND_ASYNC);
		}
	}

	std::string text;
	text = "Ouch!";
	//MAKE METHOD FOR MESSAGES
	if (px1 > 240 && !shooting) {
		px1 = 0;
		health1 -= 7;
		smaller1 -= 0.25;
		if (health1 <= 0) {
			playing = false;
			text3 = "PLAYER 2 WINS!";
		}
		glPushMatrix();
		glTranslated(50, 70, 0);
		glColor3f(1, 1, 1);
		GLUquadric* message1 = gluNewQuadric();
		gluDisk(message1, 0, 9, 50, 50);//slices w loop
		glColor3f(0, 0, 0);
	
		drawText(text.data(), text.size(), 120, 130);
	
		glPopMatrix();
		
	}

	///moved this!
	if (px > 240 && !shooting) {
		px = 0;
		health2 -= 7;
		smaller2 -= 0.25;
		if (health2 <= 0) {
			playing = false;
			text3 = "PLAYER 1 WINS!";
		}
		glPushMatrix();
		glTranslated(260, 70, 0);
		glColor3f(1, 1, 1);
		GLUquadric* message2 = gluNewQuadric();
		gluDisk(message2, 0, 9, 50, 50);//slices w loop

		glColor3f(0, 0, 0);
		drawText(text.data(), text.size(), 675, 130);
		glPopMatrix();

	}

	//END MESSAGES
////testing bezier
	glPushMatrix();

	glTranslatef(px, py, 0);
	drawBanana();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-px1, py1, 0);
	drawBanana1();
	glPopMatrix();






	glBegin(GL_QUADS);
	glVertex3f(130, 100, 0);
	glVertex3f(140, 100, 0);

	glVertex3f(140, 80, 0);
	glVertex3f(130, 80, 0);

	glEnd();
	glPushMatrix();
	glTranslatef(130, 80, 0);
	drawPower();
	glPopMatrix();

	//health of first player
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(70, 150, 0);
	glVertex3f(80, 150, 0);

	glVertex3f(80, 130, 0);
	glVertex3f(70, 130, 0);

	glEnd();
	glPushMatrix();
	glTranslatef(70, 130, 0);
	drawHealth(health1);

	glPopMatrix();
	//health of second player
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(220, 150, 0);
	glVertex3f(210, 150, 0);

	glVertex3f(210, 130, 0);
	glVertex3f(220, 130, 0);

	glEnd();
	glPushMatrix();
	glTranslatef(210, 130, 0);
	drawHealth(health2);

	glPopMatrix();

	glFlush();

}
void DrawDefender() {
	//bird
	//face
	glPushMatrix();
	glTranslated(42 + movestep1, 180, 0);
	glColor3f(0.870, 0.850, 0.329);
	GLUquadric* b = gluNewQuadric();
	gluDisk(b, 0, 9, 50, 50);//slices w loop
	glPopMatrix();

	
		//beak
		glTranslatef(85, 0, 0);
		glScalef(-1, 1, 1);
		glBegin(GL_TRIANGLES);
		glColor3f(1, 0.701, 0.058);
		glVertex3f(36 - movestep1, 177, 0.0f);
		glVertex3f(36 - movestep1, 182, 0.0f);
		glVertex3f(33 - movestep1, 179.5, 0.0f);
		glEnd();
		//end beak
			//wing
		glBegin(GL_LINE_STRIP);
		glColor3f(0, 0, 0);
		glVertex3f(43.0f - movestep1, 175.0f, 0.0f);
		glVertex3f(46.0f - movestep1, 175.0f, 0.0f);
		glVertex3f(43.0f - movestep1, 180.0f, 0.0f);
		glEnd();//end wing
		////////
		glPushMatrix();
		glTranslated(40 - movestep1, 183, 0);
		glColor3f(1, 1, 1);
		GLUquadric* b1 = gluNewQuadric();
		gluDisk(b1, 0, 2, 50, 50);//slices w loop
		glPopMatrix();
		glPushMatrix();
		glTranslated(40 - movestep1, 182, 0);
		glColor3f(0, 0, 0);
		GLUquadric* b12 = gluNewQuadric();
		gluDisk(b12, 0, 1.2, 150, 150);//slices w loop
		glPopMatrix();

		//front eye
		glPushMatrix();
		glTranslated(37 - movestep1, 183, 0);
		glColor3f(1, 1, 1);
		GLUquadric* e = gluNewQuadric();
		gluDisk(e, 0, 2, 50, 50);//slices w loop
		glPopMatrix();
		glPushMatrix();
		glTranslated(37 - movestep1, 182, 0);
		glColor3f(0, 0, 0);
		GLUquadric* e1 = gluNewQuadric();
		gluDisk(e1, 0, 1.2, 150, 150);//slices w loop
		glPopMatrix();
	//end bird 
}

void DrawBird() {
	//bird
	//face
	glPushMatrix();
	glTranslated(42 + movestep, 180, 0);
	glColor3f(0.835, 0.819, 0.784);
	GLUquadric* b = gluNewQuadric();
	gluDisk(b, 0, 9, 50, 50);//slices w loop
	glPopMatrix();

	if (forward2) {
		//beak
		glTranslatef(85, 0, 0);
		glScalef(-1, 1, 1);
		glBegin(GL_TRIANGLES);
		glColor3f(1, 0.701, 0.058);
		glVertex3f(36 - movestep, 177, 0.0f);
		glVertex3f(36 - movestep, 182, 0.0f);
		glVertex3f(33 - movestep, 179.5, 0.0f);
		glEnd();
		//end beak
			//wing
		glBegin(GL_LINE_STRIP);
		glColor3f(0, 0, 0);
		glVertex3f(43.0f - movestep, 175.0f, 0.0f);
		glVertex3f(46.0f - movestep, 175.0f, 0.0f);
		glVertex3f(43.0f - movestep, 180.0f, 0.0f);
		glEnd();//end wing
		////////
		glPushMatrix();
		glTranslated(40 - movestep, 183, 0);
		glColor3f(1, 1, 1);
		GLUquadric* b1 = gluNewQuadric();
		gluDisk(b1, 0, 2, 50, 50);//slices w loop
		glPopMatrix();
		glPushMatrix();
		glTranslated(40 - movestep, 182, 0);
		glColor3f(0, 0, 0);
		GLUquadric* b12 = gluNewQuadric();
		gluDisk(b12, 0, 1.2, 150, 150);//slices w loop
		glPopMatrix();

		//front eye
		glPushMatrix();
		glTranslated(37 - movestep, 183, 0);
		glColor3f(1, 1, 1);
		GLUquadric* e = gluNewQuadric();
		gluDisk(e, 0, 2, 50, 50);//slices w loop
		glPopMatrix();
		glPushMatrix();
		glTranslated(37 - movestep, 182, 0);
		glColor3f(0, 0, 0);
		GLUquadric* e1 = gluNewQuadric();
		gluDisk(e1, 0, 1.2, 150, 150);//slices w loop
		glPopMatrix();



		/////

	}
	else {
		//beak
		glBegin(GL_TRIANGLES);
		glColor3f(1, 0.701, 0.058);
		glVertex3f(36 + movestep, 177, 0.0f);
		glVertex3f(36 + movestep, 182, 0.0f);
		glVertex3f(33 + movestep, 179.5, 0.0f);
		glEnd();//end beak
		//wing
		glBegin(GL_LINE_STRIP);
		glColor3f(0, 0, 0);
		glVertex3f(43.0f + movestep, 175.0f, 0.0f);
		glVertex3f(46.0f + movestep, 175.0f, 0.0f);
		glVertex3f(43.0f + movestep, 180.0f, 0.0f);
		glEnd();//end wing
		glPushMatrix();
		glTranslated(40 + movestep, 183, 0);
		glColor3f(1, 1, 1);
		GLUquadric* b1 = gluNewQuadric();
		gluDisk(b1, 0, 2, 50, 50);//slices w loop
		glPopMatrix();
		glPushMatrix();
		glTranslated(40 + movestep, 182, 0);
		glColor3f(0, 0, 0);
		GLUquadric* b12 = gluNewQuadric();
		gluDisk(b12, 0, 1.2, 150, 150);//slices w loop
		glPopMatrix();

		//front eye
		glPushMatrix();
		glTranslated(37 + movestep, 183, 0);
		glColor3f(1, 1, 1);
		GLUquadric* e = gluNewQuadric();
		gluDisk(e, 0, 2, 50, 50);//slices w loop
		glPopMatrix();
		glPushMatrix();
		glTranslated(37 + movestep, 182, 0);
		glColor3f(0, 0, 0);
		GLUquadric* e1 = gluNewQuadric();
		gluDisk(e1, 0, 1.2, 150, 150);//slices w loop
		glPopMatrix();
	}
	//end bird 

}
void main(int argc, char** argr) {
	glutInit(&argc, argr);

	glutInitWindowSize(1000, 600);


	glutInitWindowPosition(150, 150);

	glutCreateWindow("Rise Of the Planet of The Apes");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Key);
	glutKeyboardUpFunc(KeyUp);
	//


	sndPlaySound(TEXT("birds"), SND_LOOP | SND_ASYNC);

	//
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutIdleFunc(Animate);
	glClearColor(0.784f, 0.913f, 0.937f, 0.0f);
	gluOrtho2D(0.0, 300, 0.0, 300);

	glutMainLoop();
}

void drawMonkey() {

	//body
	/*glBegin(GL_TRIANGLES);
	glColor3f(0.494, 0.239, 0.007);
	glVertex3f(42, 0, 0.0f);
	glVertex3f(52, 40, 0.0f);
	glVertex3f(32, 40, 0.0f);
	glEnd();
	//end body*/
	//tail
	glBegin(GL_LINE_STRIP);
	glColor3f(0.494, 0.239, 0.007);
	glVertex3f(16, 26.0f, 0.0f);
	glVertex3f(21.0f, 31.0f, 0.0f);
	glVertex3f(28, 21.0f, 0.0f);
	glVertex3f(38, 28, 0.0f);
	glEnd();
	//end tail

	glBegin(GL_QUADS);

	glColor3f(0.494, 0.239, 0.007);
	glVertex3f(40.0f, 20, 0.0f);
	glVertex3f(36.0f, 20.0f, 0.0f);
	glVertex3f(36.0f, 3.0f, 0.0f);
	glVertex3f(40, 3, 0);
	glEnd();

	glBegin(GL_QUADS);

	glColor3f(0.494, 0.239, 0.007);
	glVertex3f(49.0f, 20, 0.0f);
	glVertex3f(45.0f, 20.0f, 0.0f);
	glVertex3f(45.0f, 3.0f, 0.0f);
	glVertex3f(49, 3, 0);
	glEnd();

	glPushMatrix();
	glTranslated(42, 30, 0);
	glColor3f(0.494, 0.239, 0.007);
	GLUquadric* body = gluNewQuadric();
	gluDisk(body, 0, 12, 50, 50);//slices w loop
	glPopMatrix();
	glPushMatrix();
	glTranslated(42, 25, 0);
	glColor3f(0.494, 0.239, 0.007);
	GLUquadric* body2 = gluNewQuadric();
	gluDisk(body2, 0, 12, 50, 50);//slices w loop
	glPopMatrix();
	/////////////
	glPushMatrix();

	glTranslated(42, 28, 0);
	
	glColor3f(0.913, 0.647, 0.403);
	GLUquadric* body3 = gluNewQuadric();
	gluDisk(body3, 0, 10, 50, 50);//slices w loop
	glPopMatrix();



	//arms
	glPushMatrix();

	glRotated(45, 0, 0, 1);
	glTranslatef(35, -50, 0);

	glBegin(GL_QUADS);

	glColor3f(0.494, 0.239, 0.007);
	glVertex3f(30.0f, 40, 0.0f);
	glVertex3f(26.0f, 40.0f, 0.0f);
	glVertex3f(26.0f, 28.0f, 0.0f);
	glVertex3f(30, 28, 0);
	glEnd();
	glPopMatrix();
	glPushMatrix();

	glRotated(80, 0, 0, 1);
	glTranslatef(15, -55, 0);

	glBegin(GL_QUADS);

	glColor3f(0.494, 0.239, 0.007);
	glVertex3f(30.0f, 40, 0.0f);
	glVertex3f(26.0f, 40.0f, 0.0f);
	glVertex3f(26.0f, 28.0f, 0.0f);
	glVertex3f(30, 28, 0);
	glEnd();
	glPopMatrix();
	//end arms


	//head
	glPushMatrix();
	glTranslated(42, 49, 0);
	glColor3f(0.494, 0.239, 0.007);
	GLUquadric* b = gluNewQuadric();
	gluDisk(b, 0, 10, 50, 50);//slices w loop
	glPopMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.913, 0.647, 0.403);
	glVertex3f(35.0f, 42.0f, 0.0f);
	glVertex3f(49.0f, 42.0f, 0.0f);
	glVertex3f(49.0f, 56.0f, 0.0f);
	glVertex3f(44, 56, 0);
	glVertex3f(43.2, 49, 0);
	glVertex3f(40, 56, 0);
	glVertex3f(35, 56, 0);
	glVertex3f(35, 42, 0);

	glEnd();

	glPushMatrix();
	glTranslated(46, 50, 0);
	glColor3f(1, 1, 1);
	GLUquadric* b1 = gluNewQuadric();
	gluDisk(b1, 0, 2, 50, 50);//slices w loop
	glPopMatrix();
	glPushMatrix();
	glTranslated(46, 50, 0);
	glColor3f(0, 0, 0);
	GLUquadric* b12 = gluNewQuadric();
	gluDisk(b12, 0, 1.2, 150, 150);//slices w loop
	glPopMatrix();

	//front eye
	glPushMatrix();
	glTranslated(38, 50, 0);
	glColor3f(1, 1, 1);
	GLUquadric* e = gluNewQuadric();
	gluDisk(e, 0, 2, 50, 50);//slices w loop
	glPopMatrix();
	glPushMatrix();
	glTranslated(38, 50, 0);
	glColor3f(0, 0, 0);
	GLUquadric* e1 = gluNewQuadric();
	gluDisk(e1, 0, 1.2, 150, 150);//slices w loop
	glPopMatrix();




	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(40.0f, 44.0f, 0.0f);
	glVertex3f(42.0f, 44.0f, 0.0f);
	glEnd();
	//end head

	//ears
	glPushMatrix();
	glTranslated(35, 56, 0);
	glColor3f(0.494, 0.239, 0.007);
	GLUquadric* ear1 = gluNewQuadric();
	gluDisk(ear1, 0, 3, 50, 50);//slices w loop
	glPopMatrix();
	glPushMatrix();
	glTranslated(49, 56, 0);
	glColor3f(0.494, 0.239, 0.007);
	GLUquadric* ear2 = gluNewQuadric();
	gluDisk(ear2, 0, 3, 150, 150);//slices w loop
	glPopMatrix();
	glPushMatrix();
	glTranslated(35, 56, 0);
	glColor3f(0.913, 0.647, 0.403);
	GLUquadric* ear11 = gluNewQuadric();
	gluDisk(ear11, 0, 1.25, 50, 50);//slices w loop
	glPopMatrix();
	glPushMatrix();
	glTranslated(49, 56, 0);
	glColor3f(0.913, 0.647, 0.403);;
	GLUquadric* ear21 = gluNewQuadric();
	gluDisk(ear2, 0, 1.25, 150, 150);//slices w loop
	glPopMatrix();
	//end ears

}


void Animate()
{	if (px >= 30 + movestep1 && px <= 49 + movestep1 && py >= 165 && py <= 190) {
		movestep1 = 0;
		px = 0;
		py = 0;
		
		shooting = false;
		power = 0;
		turn1 = !turn1;
	}
	if (px1 >= 34 + movestep1 && px1 <= 49 + movestep1 && py1 >= 165 && py1 <= 190) {
		movestep1 = 0;
		px1 = 0;
		py1 = 0;
		shooting = false;
		power = 0;
		turn1 = !turn1;
	}
	if (px >= 100 && px <= 170 && py >= 40 && py <= 70) {
		px = 0;
		py = 0;
		shooting = false;
		power = 0;
		turn1 = !turn1;

	}
	if (px1 >= 100 && px1 <= 150 && py1 >= 40 && py1 <= 70) {
		px1 = 0;
		py1 = 0;
		shooting = false;
		power = 0;
		turn1 = !turn1;
	}
	if (playing) {
		if (shooting) {
			if (t <= 1) {

				int* p = bezier(t, p0, p1, p2, p3);
				if (turn1) {
					px = p[0];
					py = p[1];


				}
				else {
					px1 = p[0];
					py1 = p[1];




				}
				t += 0.006;
			}
			if (t > 1) {
				t = 0;
				power = 0;
				shooting = false;
				if (turn1) {
					turn1 = false;

				}
				else {
					turn1 = true;

				}
			}

		}
		if (movestep >= 0 && forward2)
		{
			movestep += 0.5;
			if (movestep == 228)
				forward2 = false;
		}
		else {
			movestep -= 0.5;
			if (movestep <= 0)
				forward2 = true;
		}

	
			movestep1 += 0.25;
			if (movestep1 >= 228)
				movestep1 = -1;
		
	

	}


	glutPostRedisplay();
}

void drawText(const char* text, int length, int x, int y) {
	glMatrixMode(GL_PROJECTION);
	double* matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0;i < length;i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);

	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}
void drawBanana1() {
	glBegin(GL_LINE_STRIP);
	float x, y, i;


	// iterate y up to 2*pi, i.e., 360 degree 
	// with small increment in angle
	for (i = 0; i < (2 * pi); i += 0.01)
	{
		// 25 is radius of circle 
		// circle is defined as x=r*cos(i) and y=r*sin(i) 
		x = 2 * cos(i) + 19;
		y = 2 * sin(i) + 19;

		glColor3f(1, 0.937, 0.058);
		glVertex3f(x + 250, y, 0.0f);
		glVertex3f(x + 250 - 8, y - 9, 0.0f);
	}
	glEnd();
	glColor3f(1, 0.937, 0.058);
	glBegin(GL_QUADS);
	glVertex3f(19 + 250, 24, 0);
	glVertex3f(22 + 250, 24, 0);
	glVertex3f(22 + 250, 19, 0);
	glVertex3f(19 + 250, 19, 0);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(19.5 + 250, 24, 0);
	glVertex3f(21.5 + 250, 24, 0);
	glVertex3f(21.5 + 250, 28, 0);
	glVertex3f(19.5 + 250, 28, 0);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(22 + 250, 20, 0);
	glVertex3f(12 + 250, 8, 0);
	glEnd();

}



void drawBanana() {
	glBegin(GL_LINE_STRIP);
	float x, y, i;


	// iterate y up to 2*pi, i.e., 360 degree 
	// with small increment in angle
	for (i = 0; i < (2 * pi); i += 0.01)
	{
		// 25 is radius of circle 
		// circle is defined as x=r*cos(i) and y=r*sin(i) 
		x = 2 * cos(i) + 19;
		y = 2 * sin(i) + 19;

		glColor3f(1, 0.937, 0.058);
		glVertex3f(x, y, 0.0f);
		glVertex3f(x - 8, y - 9, 0.0f);
	}
	glEnd();
	glColor3f(1, 0.937, 0.058);
	glBegin(GL_QUADS);
	glVertex3f(19, 24, 0);
	glVertex3f(22, 24, 0);
	glVertex3f(22, 19, 0);
	glVertex3f(19, 19, 0);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(19.5, 24, 0);
	glVertex3f(21.5, 24, 0);
	glVertex3f(21.5, 28, 0);
	glVertex3f(19.5, 28, 0);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(22, 20, 0);
	glVertex3f(12, 8, 0);
	glEnd();

}
int* bezier(float t, int* p0, int* p1, int* p2, int* p3)
{
	int res[2];
	res[0] = pow((1 - t), 3) * p0[0] + 3 * t * pow((1 - t), 2) * p1[0] + 3 * pow(t, 2) * (1 - t) * p2[0] + pow(t, 3) * p3[0];
	res[1] = pow((1 - t), 3) * p0[1] + 3 * t * pow((1 - t), 2) * p1[1] + 3 * pow(t, 2) * (1 - t) * p2[1] + pow(t, 3) * p3[1];
	return res;
}


void Key(unsigned char key, int x, int y) {
	//if the left button has been clicked then translate the square to the mouse position
	if (playing) {
		power += 7;
		if (power >= 21) {
			power = 21;
		}
	}
}

void KeyUp(unsigned char key, int x, int y)//mouse function takes 4 parameters: button: which button has been clicked (GLUT_RIGHT_BUTTON or GLUT_LEFT_BUTTON),
											//state wether the button is clicked or released (GLUT_UP or GLUT_DOWN)
											// x and y are the position of the mouse cursor
{

	if (key == 'a') {
		shooting = true;
		if (power == 7) {
			//testing out bezier
			p0[0] = 12.5;
			p0[1] = 12.5;

			p1[0] = 12.5;
			p1[1] = 62;

			p2[0] = 62;
			p2[1] = 62;

			p3[0] = 50;
			p3[1] = 12.5;

			////

		}
		else if (power == 14) {
			//testing out bezier
			p0[0] = 25;
			p0[1] = 25;

			p1[0] = 25;
			p1[1] = 125;

			p2[0] = 125;
			p2[1] = 125;

			p3[0] = 125;
			p3[1] = 25;



			////
		}
		else if (power == 21) {
			//testing out bezier
			p0[0] = 50;
			p0[1] = 50;

			p1[0] = 50;
			p1[1] = 250;

			p2[0] = 250;
			p2[1] = 250;

			p3[0] = 260;
			p3[1] = 5;



			////
		}

	}


	glutPostRedisplay();//redisplay to update the screen with the new paraeters
}
void drawPower() {
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f(0, 0);
	glVertex2f(10, 0);
	glVertex2f(10, power);
	glVertex2f(0, power);
	glEnd();
}
void drawHealth(int health) {
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f(0, 0);
	glVertex2f(10, 0);
	glVertex2f(10, health);
	glVertex2f(0, health);
	glEnd();
}
