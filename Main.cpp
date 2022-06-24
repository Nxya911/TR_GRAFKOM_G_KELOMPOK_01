#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

#define FPS 120
#define TO_RADIANS 3.14/180.0

//  Anggota Kelompok 1
//  Faisal Nuryawan(672020077)
//  Gideon Jerry Putra Perdana(672020142)
//  Gracelya Oktaviani(672020195)
//  Bertnaldy Christo Sidupa(672020176)

const int width = 1280;
const int height = 720;
int i;
float sudut;
double x_geser, y_geser, z_geser;

float pitch = 0.0, yaw = 0.0;
float camX = 0.0, camZ = 0.0, terbang = 25.0;

void display();
void reshape(int w, int h);
void timer(int);
void passive_motion(int, int);
void camera();
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);

struct Motion {
    bool Forward, Backward, Left, Right, Naik, Turun;
};
Motion motion = { false,false,false,false,false,false };

void init() {
    glClearColor(0.529, 0.807, 0.921, 0.0);
    glutSetCursor(GLUT_CURSOR_NONE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    glutWarpPointer(width / 2, height / 2);
}

void ground() {
    glBegin(GL_QUADS);
    glColor3f(0.03, 0.52, 0.1);
    glVertex3f(-1000.0, 0, -1000.0);

    glColor3f(0.02, 0.34, 0.06);
    glVertex3f(1000.0, 0, -1000.0);

    glColor3f(0.02, 0.34, 0.06);
    glVertex3f(1000.0, 0, 1000.0);

    glColor3f(0.03, 0.52, 0.1);
    glVertex3f(-1000.0, 0, 1000.0);
    glEnd();
}

void pondasidasar() {
    //kerangka pondasi dasar
    glPushMatrix();
    glTranslatef(0, -150, 0);
    glColor3f(0.24, 0.25, 0.25);
    glutWireCube(800.0);
    glPopMatrix();
    glPushMatrix();

    glTranslatef(-380, 0, 400);
    glColor3f(0.24, 0.25, 0.25);
    glBegin(GL_POLYGON);
    glVertex3f(-20.0, 0.0, 0.0);
    glVertex3f(780.0, 0.0, 0.0);
    glVertex3f(780.0, 250.0, 0.0);
    glVertex3f(-20.0, 250.0, 0.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-380, 0, -400);
    glColor3f(0.24, 0.25, 0.25);
    glBegin(GL_POLYGON);
    glVertex3f(-20.0, 0.0, 0.0);
    glVertex3f(780.0, 0.0, 0.0);
    glVertex3f(780.0, 250.0, 0.0);
    glVertex3f(-20.0, 250.0, 0.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-400, 0, 380);
    glRotatef(90, 0, 1, 0);
    glColor3f(0.24, 0.25, 0.25);
    glBegin(GL_POLYGON);
    glVertex3f(-20.0, 0.0, 0.0);
    glVertex3f(780.0, 0.0, 0.0);
    glVertex3f(780.0, 250.0, 0.0);
    glVertex3f(-20.0, 250.0, 0.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(400, 0, 380);
    glRotatef(90, 0, 1, 0);
    glColor3f(0.24, 0.25, 0.25);
    glBegin(GL_POLYGON);
    glVertex3f(-20.0, 0.0, 0.0);
    glVertex3f(780.0, 0.0, 0.0);
    glVertex3f(780.0, 250.0, 0.0);
    glVertex3f(-20.0, 250.0, 0.0);
    glEnd();
    glPopMatrix();

    //alas pondasi
    glPushMatrix();
    glTranslatef(-380, 250, -400);
    glRotatef(90, 1, 0, 0);
    glColor3f(0.54, 0.56, 0.56);
    glBegin(GL_POLYGON);
    glVertex3f(-20.0, 0.0, 0.0);
    glVertex3f(780.0, 0.0, 0.0);
    glVertex3f(780.0, 800.0, 0.0);
    glVertex3f(-20.0, 800.0, 0.0);
    glEnd();
    glPopMatrix();

    //tangga
    glPushMatrix();
    glTranslatef(400, 0, -193.5);
    glColor3f(0.24, 0.24, 0.24);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 250.0, 0.0);
    glVertex3f(250.0, 0.0, 0.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(400, 0, 198.5);
    glColor3f(0.24, 0.24, 0.24);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 250.0, 0.0);
    glVertex3f(250.0, 0.0, 0.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(400, 250, -197);
    glRotatef(90, 1, 0, 0);
    glRotatef(-45, 0, 1, 0);
    glColor3f(0.54, 0.56, 0.56);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(400.0, 0.0, 0.0);
    glVertex3f(400.0, 400.0, 0.0);
    glVertex3f(0.0, 400.0, 0.0);
    glEnd();
    glPopMatrix();
}
void lantai1() {
    //lantai1
    glPushMatrix();
    glTranslatef(-55.5, -329, 0);
    glColor3f(1, 1, 1);
    glTranslatef(0, 443.5, 2);
    glutSolidCube(600.0);
    glPopMatrix();

    //pagar hitam
    glPushMatrix();
    glTranslatef(396.5, 305, 396.5);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(396.5, 305, 304);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(396.5, 305, 205.5);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(396.5, 305, -199.5);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(396.5, 305, -300.5);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(396.5, 305, -396.5);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(258.5, 305, -396.5);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-23.5, 305, -396.5);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-23.5, 305, 397);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(258.5, 305, 396.5);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(102.5, 305, -396.5);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(102.5, 305, 396.5);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-152, 305, 396.5);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-152, 305, -396.5);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-277.5, 305, -396.5);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-277.5, 305, 397);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-396.5, 305, -396.5);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-396.5, 305, -120.5);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-396.5, 305, 138.5);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-396.5, 305, -293.5);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-396.5, 305, -227);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-396.5, 305, -23);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-396.5, 305, 43);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-396.5, 305, 233);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-396.5, 305, 303);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-396.5, 305, 397);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    //pagar hitam tidur
    glPushMatrix();
    glTranslatef(-399, 305, 397);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 0, 1, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 798.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-399, 290, 397);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 0, 1, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 798.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-399, 305, -396.5);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 0, 1, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 798.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-399, 290, -396.5);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 0, 1, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 798.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-399, 305, -396.5);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 0, 1, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 798.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-399, 290, -396.5);
    glColor3f(0.17, 0.16, 0.16);
    glRotatef(90, 0, 1, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 798.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-399, 305, -396.5);
    glColor3f(0.17, 0.16, 0.16);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 798.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-399, 290, -396.5);
    glColor3f(0.17, 0.16, 0.16);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 798.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(396.5, 305, -396.5);
    glColor3f(0.17, 0.16, 0.16);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 200.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(396.5, 290, -396.5);
    glColor3f(0.17, 0.16, 0.16);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 200.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(396.5, 305, 205.5);
    glColor3f(0.17, 0.16, 0.16);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 190.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(396.5, 290, 205.5);
    glColor3f(0.17, 0.16, 0.16);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 190.0f, 32, 32);
    glPopMatrix();

    //pintu depan
    glPushMatrix();
    glTranslatef(245, 50.5, 398.5);
    glRotatef(90.0, 0.0, 1.0, 0.0);

    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f(350, 200);
    glVertex2f(350, 300);
    glVertex2f(395, 300);
    glVertex2f(395, 200);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f(396, 200);
    glVertex2f(396, 300);
    glVertex2f(436, 300);
    glVertex2f(436, 200);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3, 50, 210.5);
    glRotatef(45.0, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.23, 0.13);
    glVertex2f(350, 200);
    glVertex2f(350, 300);
    glVertex2f(395, 300);
    glVertex2f(395, 200);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3, 50, -199);
    glRotatef(-45.0, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.23, 0.13);
    glVertex2f(350, 200);
    glVertex2f(350, 300);
    glVertex2f(395, 300);
    glVertex2f(395, 200);
    glEnd();
    glPopMatrix();

    //pondasi tembok
    glPushMatrix();
    glTranslatef(246, 415, 301);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 180.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(246, 415, 180.5);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 180.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(246, 415, 59);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 180.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(246, 415, -47.5);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 180.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(246, 415, -173.5);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 180.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(246, 415, -298);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 180.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(37, 415, -298);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 180.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(37, 415, 303);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 180.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-150, 415, -298);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 180.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-150, 415, 302.5);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 180.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-355.5, 415, -298);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 180.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-355.5, 415, -81);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 180.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-355.5, 415, 102);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 180.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-355.5, 415, 302);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 180.0f, 32, 32);
    glPopMatrix();

    //turu
    glPushMatrix();
    glTranslatef(241.5, 350, -294);
    glColor3f(0.8, 0.23, 0.13);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 600.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(241.5, 408, -294);
    glColor3f(0.8, 0.23, 0.13);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 600.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(241.5, 408, -294);
    glRotatef(-90, 0, 1, 0);
    glColor3f(0.8, 0.23, 0.13);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 600.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(241.5, 350, -294);
    glRotatef(-90, 0, 1, 0);
    glColor3f(0.8, 0.23, 0.13);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 600.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-351.5, 350, -294);
    glColor3f(0.8, 0.23, 0.13);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 600.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-351.5, 408, -294);
    glColor3f(0.8, 0.23, 0.13);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 600.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(241.5, 350, 302);
    glRotatef(-90, 0, 1, 0);
    glColor3f(0.8, 0.23, 0.13);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 600.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(241.5, 407.5, 302);
    glRotatef(-90, 0, 1, 0);
    glColor3f(0.8, 0.23, 0.13);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 600.0f, 32, 32);
    glPopMatrix();

    //tiang oren
    glPushMatrix();
    glTranslatef(-392.5, 415, 381.5);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 180.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(331.5, 415, 206);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 180.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(331.5, 415, -196);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 180.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-392, 415, -381.5);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 180.0f, 32, 32);
    glPopMatrix();

    //jendela
    glPushMatrix();
    glTranslatef(-36, 289.5, 202.5);
    glRotatef(90, 0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glColor3f(0.13, 0.42, 0.8);
    glVertex3f(0.0, 0.0, 100);
    glVertex3f(0.0, 45.0, 100);
    glVertex3f(45.0, 45.0, 100);
    glVertex3f(45.0, 0.0, 100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(164, 289.5, 202.5);
    glRotatef(90, 0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glColor3f(0.13, 0.42, 0.8);
    glVertex3f(0.0, 0.0, 100);
    glVertex3f(0.0, 45.0, 100);
    glVertex3f(45.0, 45.0, 100);
    glVertex3f(45.0, 0.0, 100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-232, 289.5, 202.5);
    glRotatef(90, 0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glColor3f(0.13, 0.42, 0.8);
    glVertex3f(0.0, 0.0, 100);
    glVertex3f(0.0, 45.0, 100);
    glVertex3f(45.0, 45.0, 100);
    glVertex3f(45.0, 0.0, 100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-232, 289.5, -398.5);
    glRotatef(90, 0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glColor3f(0.13, 0.42, 0.8);
    glVertex3f(0.0, 0.0, 100);
    glVertex3f(0.0, 45.0, 100);
    glVertex3f(45.0, 45.0, 100);
    glVertex3f(45.0, 0.0, 100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-33.5, 289.5, -398.5);
    glRotatef(90, 0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glColor3f(0.13, 0.42, 0.8);
    glVertex3f(0.0, 0.0, 100);
    glVertex3f(0.0, 45.0, 100);
    glVertex3f(45.0, 45.0, 100);
    glVertex3f(45.0, 0.0, 100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(164.5, 289.5, -398.5);
    glRotatef(90, 0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glColor3f(0.13, 0.42, 0.8);
    glVertex3f(0.0, 0.0, 100);
    glVertex3f(0.0, 45.0, 100);
    glVertex3f(45.0, 45.0, 100);
    glVertex3f(45.0, 0.0, 100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(145, 289.5, -213);
    glRotatef(90, 0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(0.13, 0.42, 0.8);
    glVertex3f(0.0, 0.0, 100);
    glVertex3f(0.0, 45.0, 100);
    glVertex3f(45.0, 45.0, 100);
    glVertex3f(45.0, 0.0, 100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(145, 289.5, -84.5);
    glRotatef(90, 0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(0.13, 0.42, 0.8);
    glVertex3f(0.0, 0.0, 100);
    glVertex3f(0.0, 45.0, 100);
    glVertex3f(45.0, 45.0, 100);
    glVertex3f(45.0, 0.0, 100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(145, 289.5, 142.5);
    glRotatef(90, 0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(0.13, 0.42, 0.8);
    glVertex3f(0.0, 0.0, 100);
    glVertex3f(0.0, 45.0, 100);
    glVertex3f(45.0, 45.0, 100);
    glVertex3f(45.0, 0.0, 100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(145, 289.5, 264);
    glRotatef(90, 0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(0.13, 0.42, 0.8);
    glVertex3f(0.0, 0.0, 100);
    glVertex3f(0.0, 45.0, 100);
    glVertex3f(45.0, 45.0, 100);
    glVertex3f(45.0, 0.0, 100);
    glEnd();
    glPopMatrix();
}

void lantai2() {
    //balkonlantai2
   //alas
    glPushMatrix();
    glTranslatef(-50, 364.5, 0);
    glRotatef(90, 0, 1, 0);
    glColor3f(0.83, 0.5, 0.29);
    glBegin(GL_POLYGON);
    glVertex3f(-385, 50, 385);
    glVertex3f(-385, 50, -385);
    glVertex3f(385, 50, -385);
    glVertex3f(385, 50, 385);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-50, 365, 0);
    glRotatef(90, 0, 1, 0);
    glColor3f(0.83, 0.5, 0.29);
    glBegin(GL_POLYGON);
    glVertex3f(-385, 50, 385);
    glVertex3f(-385, 50, -385);
    glVertex3f(385, 50, -385);
    glVertex3f(385, 50, 385);
    glEnd();
    glPopMatrix();

    //PagarLantai2Ngadek
    glPushMatrix();
    glTranslatef(-431.5, 469.5, 381.5);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-240, 469.5, 381.5);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(331.5, 469.5, 381.5);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(331.5, 469.5, 190);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-431.5, 469.5, 190);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(91.5, 469.5, 381.5);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(331.5, 469.5, -381.5);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(331.5, 469.5, -190);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-431.5, 469.5, -190);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-431.5, 469.5, -381.5);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-240, 469.5, -381.5);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(140, 469.5, -381.5);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 55.0f, 32, 32);
    glPopMatrix();

    //PagarLantai2TURU
    glPushMatrix();
    glTranslatef(-434.5, 468, -381.5);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 0, 1, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 770.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-431.5, 451.5, -381.5);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 0, 1, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 765.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-431.5, 451.5, 381.5);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 0, 1, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 765.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-434.5, 468, 381.5);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 0, 1, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 770.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-432, 451.5, -384.5);
    glColor3f(0.7, 0.12, 0.09);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 765.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-432, 468, -385);
    glColor3f(0.7, 0.12, 0.09);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 770.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(331, 451.5, -384.5);
    glColor3f(0.7, 0.12, 0.09);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 765.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(331, 468, -385);
    glColor3f(0.7, 0.12, 0.09);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 770.0f, 32, 32);
    glPopMatrix();

    //AwakLantai2
    glPushMatrix();
    glTranslatef(-55.5, -66, 0);
    glColor3f(1, 1, 1);
    glTranslatef(0, 443.5, 2);
    glutSolidCube(450.0);
    glPopMatrix();

    //LawangNgarep
    glPushMatrix();
    glColor3f(0, 0, 0);
    glRotatef(90, 0, 1, 0);
    glTranslatef(-57, 307.5, 170);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(100.0, 0.0, 0.0);
    glVertex3f(100.0, 200.0, 0.0);
    glVertex3f(00.0, 200.0, 0.0);
    glEnd();
    glPopMatrix();

    //LawangMburi
    glPushMatrix();
    glColor3f(0, 0, 0);
    glRotatef(90, 0, 1, 0);
    glTranslatef(-57, 307.5, -282);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(100.0, 0.0, 0.0);
    glVertex3f(100.0, 200.0, 0.0);
    glVertex3f(00.0, 200.0, 0.0);
    glEnd();
    glPopMatrix();

    //Cagak turu ngarep
    glPushMatrix();
    glTranslatef(171, 529, -223);
    glColor3f(0.8, 0.23, 0.13);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 450.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(171, 560, -223);
    glColor3f(0.8, 0.23, 0.13);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 450.0f, 32, 32);
    glPopMatrix();

    //Cagak turu mburi
    glPushMatrix();
    glTranslatef(-279, 529, -223);
    glColor3f(0.8, 0.23, 0.13);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 450.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-279, 560, -223);
    glColor3f(0.8, 0.23, 0.13);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 450.0f, 32, 32);
    glPopMatrix();

    //CagakTuruTengen
    glPushMatrix();
    glTranslatef(-279, 529, -223);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 0, 1, 0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 450.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-279, 560, -223);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 0, 1, 0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 450.0f, 32, 32);
    glPopMatrix();

    //CagakTuruKiwo
    glPushMatrix();
    glTranslatef(-279, 529, 227);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 0, 1, 0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 450.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-279, 560, 227);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 0, 1, 0);
    gluCylinder(gluNewQuadric(), 7.0f, 7.0f, 450.0f, 32, 32);
    glPopMatrix();

    //CagakNGadek
    glPushMatrix();
    glTranslatef(170.5, 603, 227);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 200.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-279.5, 603, 227);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 200.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-279.5, 603, -223);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 200.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(170.5, 603, -223);
    glColor3f(0.8, 0.23, 0.13);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 200.0f, 32, 32);
    glPopMatrix();

    //JendelaNgarep
    glPushMatrix();
    glTranslatef(70, 471.5, 142.5);
    glRotatef(90, 0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(0.13, 0.42, 0.8);
    glVertex3f(0.0, 0.0, 100);
    glVertex3f(0.0, 45.0, 100);
    glVertex3f(45.0, 45.0, 100);
    glVertex3f(45.0, 0.0, 100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(70, 471.5, -83.5);
    glRotatef(90, 0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(0.13, 0.42, 0.8);
    glVertex3f(0.0, 0.0, 100);
    glVertex3f(0.0, 45.0, 100);
    glVertex3f(45.0, 45.0, 100);
    glVertex3f(45.0, 0.0, 100);
    glEnd();
    glPopMatrix();

    //JendelaMburi
    glPushMatrix();
    glTranslatef(-382, 471.5, 142.5);
    glRotatef(90, 0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(0.13, 0.42, 0.8);
    glVertex3f(0.0, 0.0, 100);
    glVertex3f(0.0, 45.0, 100);
    glVertex3f(45.0, 45.0, 100);
    glVertex3f(45.0, 0.0, 100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-382, 471.5, -83.5);
    glRotatef(90, 0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(0.13, 0.42, 0.8);
    glVertex3f(0.0, 0.0, 100);
    glVertex3f(0.0, 45.0, 100);
    glVertex3f(45.0, 45.0, 100);
    glVertex3f(45.0, 0.0, 100);
    glEnd();
    glPopMatrix();
}

void lantai3() {
    //grace
        //badanbangunan2
    glPushMatrix();
    glTranslatef(-53, 928, 0.0);
    glColor3f(1, 1, 1);
    glutSolidCube(350.0);
    glPopMatrix();

    //dasar2
    glPushMatrix();
    glColor3f(0.8, 0.43, 0);
    glRotatef(90, 50, 0, 0);
    glTranslatef(-403.5, -354, -785.5);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(700.0, 0.0, 0.0);
    glVertex3f(700.0, 700.0, 0.0);
    glVertex3f(0.0, 700.0, 0.0);
    glEnd();
    glPopMatrix();
    //belakang
    glPushMatrix();
    glTranslatef(46.5, 775.5, 1);
    glRotatef(90, 0, 1, 0);
    glColor3f(1, 0.6, 0.14);
    glBegin(GL_POLYGON);
    glVertex3f(-345, 10, -450);
    glVertex3f(-345, 75, -450);
    glVertex3f(355, 75, -450);
    glVertex3f(355, 10, -450);
    glEnd();
    glPopMatrix();
    //kanan
    glPushMatrix();
    glTranslatef(-58.5, 775.5, 96);
    glColor3f(1, 0.6, 0.14);
    glBegin(GL_POLYGON);
    glVertex3f(-345, 10, -450);
    glVertex3f(-345, 75, -450);
    glVertex3f(355, 75, -450);
    glVertex3f(355, 10, -450);
    glEnd();
    glPopMatrix();
    //kiri
    glPushMatrix();
    glTranslatef(-58.5, 775.5, 796);
    glColor3f(1, 0.6, 0.14);
    glBegin(GL_POLYGON);
    glVertex3f(-345, 10, -450);
    glVertex3f(-345, 75, -450);
    glVertex3f(355, 75, -450);
    glVertex3f(355, 10, -450);
    glEnd();
    glPopMatrix();
    //depan
    glPushMatrix();
    glTranslatef(746.5, 775.5, 1);
    glRotatef(90, 0, 1, 0);
    glColor3f(1, 0.6, 0.14);
    glBegin(GL_POLYGON);
    glVertex3f(-345, 10, -450);
    glVertex3f(-345, 75, -450);
    glVertex3f(355, 75, -450);
    glVertex3f(355, 10, -450);
    glEnd();
    glPopMatrix();

    //atapkananbawah
    glPushMatrix();
    glColor3f(0.18, 0.49, 1);
    glRotatef(50, 1000, 0, 0);
    glTranslatef(-680.5, 446, -922.5);
    glBegin(GL_POLYGON);
    glVertex3f(376.0, 0.0, 0.0);
    glVertex3f(878, 0.0, 0.0);
    glVertex3f(802.0, 100.0, 0.0);
    glVertex3f(453.0, 100.0, 0.0);
    glEnd();
    glPopMatrix();
    //atap kiri
    glPushMatrix();
    glColor3f(0.18, 0.49, 1);
    glRotatef(-50, 1000, 0, 0);
    glTranslatef(-680.5, 446, 922.5);
    glBegin(GL_POLYGON);
    glVertex3f(376.0, 0.0, 0.0);
    glVertex3f(878, 0.0, 0.0);
    glVertex3f(802.0, 100.0, 0.0);
    glVertex3f(453.0, 100.0, 0.0);
    glEnd();
    glPopMatrix();
    //atapdepan
    glPushMatrix();
    glColor3f(0.18, 0.49, 1);
    glRotatef(90, 0, 1, 0);
    glRotatef(-50, 1, 0, 0);
    glTranslatef(-627, 486, 888.5);
    glBegin(GL_POLYGON);
    glVertex3f(376.0, 0.0, 0.0);
    glVertex3f(878.0, 0.0, 0.0);
    glVertex3f(802.0, 100.0, 0.0);
    glVertex3f(453.0, 100.0, 0.0);
    glEnd();
    glPopMatrix();
    //atapbelakang
    glPushMatrix();
    glColor3f(0.18, 0.49, 1);
    glRotatef(90, 0, 1, 0);
    glRotatef(50, 1, 0, 0);
    glTranslatef(-627.5, 405.5, -956.5);
    glBegin(GL_POLYGON);
    glVertex3f(376.0, 0.0, 0.0);
    glVertex3f(878.0, 0.0, 0.0);
    glVertex3f(802.0, 100.0, 0.0);
    glVertex3f(453.0, 100.0, 0.0);
    glEnd();
    glPopMatrix();

    //pintubawah
    glPushMatrix();
    glColor3f(0, 0, 0);
    glRotatef(90, 0, 1, 0);
    glTranslatef(-39.5, 786, 122.5);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(80.0, 0.0, 0.0);
    glVertex3f(80.0, 130.0, 0.0);
    glVertex3f(00.0, 130.0, 0.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.13, 0.42, 0.8);
    glRotatef(90, 0, 1, 0);
    glTranslatef(60, 804.5, 122.5);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 0.0, 0.0);
    glVertex3f(50.0, 100.0, 0.0);
    glVertex3f(00.0, 100.0, 0.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.13, 0.42, 0.8);
    glRotatef(90, 0, 1, 0);
    glTranslatef(116, 804.5, 122.5);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 0.0, 0.0);
    glVertex3f(50.0, 100.0, 0.0);
    glVertex3f(00.0, 100.0, 0.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.13, 0.42, 0.8);
    glRotatef(90, 0, 1, 0);
    glTranslatef(-108, 804.5, 122.5);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 0.0, 0.0);
    glVertex3f(50.0, 100.0, 0.0);
    glVertex3f(00.0, 100.0, 0.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.13, 0.42, 0.8);
    glRotatef(90, 0, 1, 0);
    glTranslatef(-165, 804.5, 122.5);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 0.0, 0.0);
    glVertex3f(50.0, 100.0, 0.0);
    glVertex3f(00.0, 100.0, 0.0);
    glEnd();
    glPopMatrix();

    //plafonbawah
    glPushMatrix();
    glColor3f(1, 0.6, 0.22);
    glRotatef(90, 50, 0, 0);
    glTranslatef(-278, -225, -1015);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(450.0, 0.0, 0.0);
    glVertex3f(450.0, 450.0, 0.0);
    glVertex3f(0.0, 450.0, 0.0);
    glEnd();
    glPopMatrix();
}
void lantai4() {
    //naldy

        //atapdepan
    glPushMatrix();
    glColor3f(0.18, 0.49, 1);
    glRotatef(90, 0, 1, 0);
    glRotatef(-50, 1, 0, 0);
    glTranslatef(-625, 669.5, 1304.5);
    glBegin(GL_POLYGON);
    glVertex3f(245.0, 0.0, 0.0);
    glVertex3f(1003.0, 0.0, 0.0);
    glVertex3f(850.0, 200.0, 0.0);
    glVertex3f(400.0, 200.0, 0.0);
    glEnd();
    glPopMatrix();
    //atapbelakang
    glPushMatrix();
    glColor3f(0.18, 0.49, 1);
    glRotatef(90, 0, 1, 0);
    glRotatef(50, 1, 0, 0);
    glTranslatef(-625, 588, -1372);
    glBegin(GL_POLYGON);
    glVertex3f(245.0, 0.0, 0.0);
    glVertex3f(1003.0, 0.0, 0.0);
    glVertex3f(850.0, 200.0, 0.0);
    glVertex3f(400.0, 200.0, 0.0);
    glEnd();
    glPopMatrix();

    //dasar4
    glPushMatrix();
    glColor3f(0.8, 0.43, 0);
    glRotatef(90, 50, 0, 0);
    glTranslatef(-462.5, -420.5, -1103.5);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(800.0, 0.0, 0.0);
    glVertex3f(800.0, 800.0, 0.0);
    glVertex3f(0.0, 800.0, 0.0);
    glEnd();
    glPopMatrix();
    //belakang
    glPushMatrix();
    glTranslatef(-12, 1093.5, -14.5);
    glRotatef(90, 0, 1, 0);
    glColor3f(1, 0.6, 0.14);
    glBegin(GL_POLYGON);
    glVertex3f(-394, 10, -450);
    glVertex3f(-394, 75, -450);
    glVertex3f(406, 75, -450);
    glVertex3f(406, 10, -450);
    glEnd();
    glPopMatrix();
    //kanan
    glPushMatrix();
    glTranslatef(-68.5, 1093.5, 29.5);
    glColor3f(1, 0.6, 0.14);
    glBegin(GL_POLYGON);
    glVertex3f(-394, 10, -450);
    glVertex3f(-394, 75, -450);
    glVertex3f(406, 75, -450);
    glVertex3f(406, 10, -450);
    glEnd();
    glPopMatrix();
    //kiri
    glPushMatrix();
    glTranslatef(-68.5, 1093.5, 829.5);
    glColor3f(1, 0.6, 0.14);
    glBegin(GL_POLYGON);
    glVertex3f(-394, 10, -450);
    glVertex3f(-394, 75, -450);
    glVertex3f(406, 75, -450);
    glVertex3f(406, 10, -450);
    glEnd();
    glPopMatrix();
    //depan
    glPushMatrix();
    glTranslatef(787.5, 1093.5, -14.5);
    glRotatef(90, 0, 1, 0);
    glColor3f(1, 0.6, 0.14);
    glBegin(GL_POLYGON);
    glVertex3f(-394, 10, -450);
    glVertex3f(-394, 75, -450);
    glVertex3f(406, 75, -450);
    glVertex3f(406, 10, -450);
    glEnd();
    glPopMatrix();
    //badan
    glPushMatrix();
    glTranslatef(-53, 1333, 0.0);
    glColor3f(1, 1, 1);
    glutSolidCube(450.0);
    glPopMatrix();
    //atapkanan
    glPushMatrix();
    glColor3f(0.18, 0.49, 1);
    glRotatef(50, 1000, 0, 0);
    glTranslatef(-678, 629, -1338);
    glBegin(GL_POLYGON);
    glVertex3f(247.0, 0.0, 0.0);
    glVertex3f(1003.0, 0.0, 0.0);
    glVertex3f(850.0, 200.0, 0.0);
    glVertex3f(400.0, 200.0, 0.0);
    glEnd();
    glPopMatrix();
    //atapkiri
    glPushMatrix();
    glColor3f(0.18, 0.49, 1);
    glRotatef(-50, 1000, 0, 0);
    glTranslatef(-678, 629, 1338.5);
    glBegin(GL_POLYGON);
    glVertex3f(247.0, 0.0, 0.0);
    glVertex3f(1003.0, 0.0, 0.0);
    glVertex3f(850.0, 200.0, 0.0);
    glVertex3f(400.0, 200.0, 0.0);
    glEnd();
    glPopMatrix();

    //pintu 
    glPushMatrix();
    glColor3f(0, 0, 0);
    glRotatef(90, 0, 1, 0);
    glTranslatef(-76, 1108, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(150.0, 0.0, 0.0);
    glVertex3f(150.0, 250.0, 0.0);
    glVertex3f(00.0, 250.0, 0.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.13, 0.42, 0.8);
    glRotatef(90, 0, 1, 0);
    glTranslatef(93.5, 1195, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 0.0, 0.0);
    glVertex3f(50.0, 130.0, 0.0);
    glVertex3f(00.0, 130.0, 0.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.13, 0.42, 0.8);
    glRotatef(90, 0, 1, 0);
    glTranslatef(-145.5, 1195, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 0.0, 0.0);
    glVertex3f(50.0, 130.0, 0.0);
    glVertex3f(00.0, 130.0, 0.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.13, 0.42, 0.8);
    glRotatef(90, 0, 1, 0);
    glTranslatef(159, 1195, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 0.0, 0.0);
    glVertex3f(50.0, 130.0, 0.0);
    glVertex3f(00.0, 130.0, 0.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.13, 0.42, 0.8);
    glRotatef(90, 0, 1, 0);
    glTranslatef(-209.5, 1195, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 0.0, 0.0);
    glVertex3f(50.0, 130.0, 0.0);
    glVertex3f(00.0, 130.0, 0.0);
    glEnd();
    glPopMatrix();

    //plafon
    glPushMatrix();
    glColor3f(1, 0.6, 0.22);
    glRotatef(90, 50, 0, 0);
    glTranslatef(-404, -353, -1450);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(700.0, 0.0, 0.0);
    glVertex3f(700.0, 700.0, 0.0);
    glVertex3f(0.0, 700.0, 0.0);
    glEnd();
    glPopMatrix();

    //ataskotak
    glPushMatrix();
    glTranslatef(0.0, 1572.5, 0.0);
    glColor3f(0.24, 0.25, 1.25);
    glutSolidCube(150.0);
    glPopMatrix();

    //selinder
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glTranslatef(0.0, 0.0, 1626.5);
    glColor3f(0.24, 0.25, 1.25);
    gluCylinder(gluNewQuadric(), 70.0f, 05.0f, 600.0f, 32, 62);
    glPopMatrix();
    //tiangkanan
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glRotatef(15, 0, 1, 0);
    glRotatef(-15, 1, 0, 0);
    glTranslatef(-118.5, -69, 1133.5);
    glColor3f(0.17, 0.16, 0.16);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 390.0f, 32, 32);
    glPopMatrix();
    //kiri
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glRotatef(15, 0, 1, 0);
    glRotatef(15, 1, 0, 0);
    glTranslatef(-119.5, 68, 1133.5);
    glColor3f(0.17, 0.16, 0.16);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 390.0f, 32, 32);
    glPopMatrix();
    //depan
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glRotatef(15, 0, 1, 0);
    glTranslatef(-118, 86.5, 1112);
    glColor3f(0.17, 0.16, 0.16);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 380.0f, 32, 32);
    glPopMatrix();
    //depan
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glRotatef(15, 0, 1, 0);
    glTranslatef(-116.5, -87, 1112);
    glColor3f(0.17, 0.16, 0.16);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 380.0f, 32, 32);
    glPopMatrix();
    //belakang
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glRotatef(-15, 0, 1, 0);
    glRotatef(15, 1, 0, 0);
    glTranslatef(15.5, 76, 1159.5);
    glColor3f(0.17, 0.16, 0.16);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 380.0f, 32, 32);
    glPopMatrix();
    //belakang
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glRotatef(-15, 0, 1, 0);
    glRotatef(-15, 1, 0, 0);
    glTranslatef(17.5, -74.5, 1159);
    glColor3f(0.17, 0.16, 0.16);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 380.0f, 32, 32);
    glPopMatrix();
    //kacakanan
    glPushMatrix();
    glColor4f(1, 1, 1, 0.4);
    glRotatef(-15, 1, 0, 0);
    glTranslatef(-407.5, 1260.5, 63);
    glBegin(GL_POLYGON);
    glVertex3f(92.0, 0.0, 0.0);
    glVertex3f(616.0, 0.0, 0.0);
    glVertex3f(678.0, 240.0, 0.0);
    glVertex3f(34.0, 240.0, 0.0);
    glEnd();
    glPopMatrix();
    //kiri
    glPushMatrix();
    glColor4f(1, 1, 1, 0.4);
    glRotatef(15, 1, 0, 0);
    glTranslatef(-407.5, 1263, -63.5);
    glBegin(GL_POLYGON);
    glVertex3f(92.0, 0.0, 0.0);
    glVertex3f(616.0, 0.0, 0.0);
    glVertex3f(678.0, 240.0, 0.0);
    glVertex3f(34.0, 240.0, 0.0);
    glEnd();
    glPopMatrix();
    //belakang
    glPushMatrix();
    glColor4f(1, 1, 1, 0.4);
    glRotatef(15, 0, 0, 1);
    glRotatef(90, 0, 1, 0);
    glTranslatef(-354.5, 1273.5, 17.5);
    glBegin(GL_POLYGON);
    glVertex3f(92.0, 0.0, 0.0);
    glVertex3f(616.0, 0.0, 0.0);
    glVertex3f(678.0, 240.0, 0.0);
    glVertex3f(34.0, 240.0, 0.0);
    glEnd();
    glPopMatrix();
    //depankiri
    glPushMatrix();
    glColor4f(1, 1, 1, 0.4);
    glRotatef(15, 0, 0, -1);
    glRotatef(90, 0, 1, 0);
    glTranslatef(-354.5, 1229.5, -119);
    glBegin(GL_POLYGON);
    glVertex3f(92.0, 0.0, 0.0);
    glVertex3f(270.0, 0.0, 0.0);
    glVertex3f(270.0, 240.0, 0.0);
    glVertex3f(34.0, 240.0, 0.0);
    glEnd();
    glPopMatrix();
    //depankanan
    glPushMatrix();
    glColor4f(1, 1, 1, 0.4);
    glRotatef(15, 0, 0, -1);
    glRotatef(90, 0, 1, 0);
    glTranslatef(41, 1229.5, -119);
    glBegin(GL_POLYGON);
    glVertex3f(44.0, 0.0, 0.0);
    glVertex3f(220.0, 0.0, 0.0);
    glVertex3f(278.0, 240.0, 0.0);
    glVertex3f(44.0, 240.0, 0.0);
    glEnd();
    glPopMatrix();
    //pagar
    glPushMatrix();
    glTranslatef(-458, 1203.5, 0);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-458, 1203.5, -125.5);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-458, 1203.5, -252);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-458, 1203.5, -417);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-458, 1203.5, 126);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-458, 1203.5, 248);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-458, 1203.5, 376);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-40, 1203.5, 376);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-162.5, 1203.5, 376);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-286.5, 1203.5, 376);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(115.5, 1203.5, 376);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(334, 1203.5, 376);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(334, 1203.5, -10);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(334, 1203.5, 127.5);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(334, 1203.5, -154);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(334, 1203.5, -417);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-64.5, 1203.5, -417);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-197, 1203.5, -417);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-328, 1203.5, -417);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(69, 1203.5, -417);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(193.5, 1203.5, -417);
    glColor3f(0.7, 0.12, 0.09);
    glRotatef(90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(335.5, 1204.5, -419);
    glColor3f(0.7, 0.12, 0.09);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 798.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-458, 1204.5, -419);
    glColor3f(0.7, 0.12, 0.09);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 798.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(-376, 1204, -460.5);
    glColor3f(0.7, 0.12, 0.09);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 798.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(417, 1204, -461);
    glColor3f(0.7, 0.12, 0.09);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 798.0f, 32, 32);
    glPopMatrix();

}

void draw() {
    // Mulai tuliskan isi pikiranmu disini
    pondasidasar();
    lantai1();
    lantai2();

    glPushMatrix();
    glTranslatef(0, -182, 0);
    lantai3();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -230, 0);
    lantai4();
    glPopMatrix();

    ground();
    cout << "X_GESER = " << x_geser << "  Y_GESER = " << y_geser << " Z_GESER = " << z_geser << endl;
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camera();
    draw();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 16.0 / 9.0, 2, 10000);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int) {
    glutPostRedisplay();
    glutWarpPointer(width / 2, height / 2);
    glutTimerFunc(1000 / FPS, timer, 0);
}

void passive_motion(int x, int y) {
    int dev_x, dev_y;
    dev_x = (width / 2) - x;
    dev_y = (height / 2) - y;
    yaw += (float)dev_x / 20.0;
    pitch += (float)dev_y / 20.0;
}

void camera() {
    if (motion.Forward) {
        camX += cos((yaw + 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90) * TO_RADIANS) * 2;
    }
    if (motion.Backward) {
        camX += cos((yaw + 90 + 180) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 + 180) * TO_RADIANS) * 2;
    }
    if (motion.Left) {
        camX += cos((yaw + 90 + 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 + 90) * TO_RADIANS) * 2;
    }
    if (motion.Right) {
        camX += cos((yaw + 90 - 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 - 90) * TO_RADIANS) * 2;
    }
    if (motion.Naik) {
        terbang -= 2.0;
    }
    if (motion.Turun) {
        terbang += 2.0;
    }

    if (pitch >= 70)
        pitch = 70;
    if (pitch <= -90)
        pitch = -90;


    glRotatef(-pitch, 1.0, 0.0, 0.0);
    glRotatef(-yaw, 0.0, 1.0, 0.0);

    glTranslatef(-camX, -terbang, -350 - camZ);
    if (terbang < 25)
        terbang = 24;
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'W':
    case 'w':
        motion.Forward = true;
        break;
    case 'A':
    case 'a':
        motion.Left = true;
        break;
    case 'S':
    case 's':
        motion.Backward = true;
        break;
    case 'D':
    case 'd':
        motion.Right = true;
        break;
    case 'E':
    case 'e':
        motion.Naik = true;
        break;
    case 'Q':
    case 'q':
        motion.Turun = true;
        break;
    case 'l':
        x_geser += 0.5;
        break;
    case 'j':
        x_geser -= 0.5;
        break;
    case '=':
        y_geser += 0.5;
        break;
    case '-':
        y_geser -= 0.5;
        break;
    case 'i':
        z_geser -= 0.5;
        break;
    case 'k':
        z_geser += 0.5;
        break;
    case '`': // KELUAR DARI PROGRAM
        exit(1);
    }
}

void keyboard_up(unsigned char key, int x, int y) {
    switch (key) {
    case 'W':
    case 'w':
        motion.Forward = false;
        break;
    case 'A':
    case 'a':
        motion.Left = false;
        break;
    case 'S':
    case 's':
        motion.Backward = false;
        break;
    case 'D':
    case 'd':
        motion.Right = false;
        break;
    case 'E':
    case 'e':
        motion.Naik = false;
        break;
    case 'Q':
    case 'q':
        motion.Turun = false;
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("TR GRAFKOM KELOMPOK 1");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(passive_motion);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);

    glutMainLoop();
    return 0;
}
