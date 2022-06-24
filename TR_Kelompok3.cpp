#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

#define FPS 120
#define TO_RADIANS 3.14/180.0

//  Anggota Kelompok 3
//  Michael Rio Aditya (672020188)
//  Caroluce Ricky Harkris Nowo (672020191)
//  Hutami Jane Antonia .M (672020205)
//  Violita Eka Putri (672020210)
//  Nama (NIM) (cuma empat orang)

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
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f(-1000.0, 0, -1000.0);

    glColor3f(0.6f, 0.6f, 0.6f);
    glVertex3f(1000.0, 0, -1000.0);

    glColor3f(0.6f, 0.6f, 0.6f);
    glVertex3f(1000.0, 0, 1000.0);

    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f(-1000.0, 0, 1000.0);
    glEnd();
}

void tanah2(int x, float y, int z) //tanah lantai 2
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.26, 0, 0);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glColor3f(0.26, 0, 0);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glColor3f(0.26, 0, 0);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.26, 0, 0);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void bangunan2(int x, float y, int z) //bangunan lantai 2
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.7, 0.7, 0.7);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.7, 0.7, 0.7);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.7, 0.7, 0.7);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.7, 0.7, 0.7);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glColor3f(0.7, 0.7, 0.7);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glColor3f(0.7, 0.7, 0.7);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.7, 0.7, 0.7);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glColor3f(0.7, 0.7, 0.7);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.7, 0.7, 0.7);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glColor3f(0.7, 0.7, 0.7);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.7, 0.7, 0.7);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.7, 0.7, 0.7);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.7, 0.7, 0.7);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void ataplantai2(int x, float y, int z) {
    glBegin(GL_QUADS);



    glColor3f(0.21, 0.21, 0.21);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.21, 0.21, 0.21);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.2f, 0.2f, 0.2f);
    glVertex3f(-0.2f, 0.2f, 0.2f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.2f, 0.2f, -0.2f);
    glColor3f(0.21, 0.21, 0.21);
    glVertex3f(0.2f, 0.2f, -0.2f);
    glVertex3f(0.5f, -0.5f, -0.5f);

    glColor3f(0.21, 0.21, 0.21);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.2f, 0.2f, 0.2f);
    glColor3f(0.21, 0.21, 0.21);
    glVertex3f(-0.2f, 0.2f, -0.2f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.2f, 0.2f, -0.2f);
    glColor3f(0.21, 0.21, 0.21);
    glVertex3f(0.2f, 0.2f, 0.2f);
    glVertex3f(0.5f, -0.5f, 0.5f);


    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.21, 0.21, 0.21);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();


}

void pipe(float rbase, float rtop, float height, int resolusi)
{
    /*float i;
    glPushMatrix();
    glColor3f(1, 0.06, 0.06);
    glTranslatef(0.0, 0.0, -rbase / 4);
    for (i = 0; i <= height; i += rbase / 8)
    {
        glTranslatef(0.0, 0.0, rbase / 8);
        glutSolidTorus(rbase / 4, rbase - ((i * (rbase - rtop)) / height), 4, resolusi);
    }
    glTranslatef(0.0, 0.0, rbase / 4);
    glPopMatrix();
   */


}

void pagar(int x, float y, int z) //pagar
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.94, 0, 0);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.94, 0, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.94, 0, 0);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.94, 0, 0);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glColor3f(0.94, 0, 0);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glColor3f(0.94, 0, 0);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.94, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glColor3f(0.94, 0, 0);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.94, 0, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glColor3f(0.94, 0, 0);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.94, 0, 0);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.94, 0, 0);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.94, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void tiangpintu(int x, float y, int z) //pintu
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.21, 0.21, 0.21);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.21, 0.21, 0.21);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.21, 0.21, 0.21);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.21, 0.21, 0.21);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glColor3f(0.21, 0.21, 0.21);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glColor3f(0.21, 0.21, 0.21);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.21, 0.21, 0.21);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glColor3f(0.21, 0.21, 0.21);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.21, 0.21, 0.21);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glColor3f(0.21, 0.21, 0.21);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.21, 0.21, 0.21);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.21, 0.21, 0.21);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.21, 0.21, 0.21);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();

}

void pintu(int x, float y, int z) //pintu
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.21, 0.21, 0.21);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.21, 0.21, 0.21);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.21, 0.21, 0.21);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.21, 0.21, 0.21);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glColor3f(0.21, 0.21, 0.21);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glColor3f(0.21, 0.21, 0.21);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.21, 0.21, 0.21);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glColor3f(0.21, 0.21, 0.21);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.21, 0.21, 0.21);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glColor3f(0.21, 0.21, 0.21);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.21, 0.21, 0.21);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.21, 0.21, 0.21);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.21, 0.21, 0.21);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();

}

void jendela(int x, float y, int z) //jendela
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.8, 0.88);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.6, 0.8, 0.88);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.6, 0.8, 0.88);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.6, 0.8, 0.88);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glColor3f(0.6, 0.8, 0.88);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glColor3f(0.6, 0.8, 0.88);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.6, 0.8, 0.88);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glColor3f(0.6, 0.8, 0.88);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.6, 0.8, 0.88);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glColor3f(0.6, 0.8, 0.88);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.6, 0.8, 0.88);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.6, 0.8, 0.88);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.6, 0.8, 0.88);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();

}

void garistengah(int x, float y, int z) //garistengah pintu
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glColor3f(1, 0, 0);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glColor3f(1, 0, 0);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(1, 0, 0);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();

}

void jendeladalam(int x, float y, int z) //jendela pintu
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glColor3f(1, 0, 0);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glColor3f(1, 0, 0);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(1, 0, 0);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(1, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();

}

void pohon() {
    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
      // Front
    glColor3f(0.06, 0.64, 0.02);     // Red
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.06, 0.64, 0.02);     // Green
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glColor3f(0.06, 0.64, 0.02);     // Blue
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Right
    glColor3f(0.06, 0.64, 0.02);     // Red
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.06, 0.64, 0.02);     // Blue
    glVertex3f(1.0f, -1.0f, 1.0f);
    glColor3f(0.06, 0.64, 0.02);     // Green
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Back
    glColor3f(0.06, 0.64, 0.02);     // Red
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.06, 0.64, 0.02);     // Green
    glVertex3f(1.0f, -1.0f, -1.0f);
    glColor3f(0.06, 0.64, 0.02);     // Blue
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // Left
    glColor3f(0.06, 0.64, 0.02);       // Red
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.06, 0.64, 0.02);       // Blue
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glColor3f(0.06, 0.64, 0.02);       // Green
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glEnd();   // Done drawing the pyramid
}

void batangR(int x, float y, int z) //bangunan lantai 2
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.68, 0.15, 0.15);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.68, 0.15, 0.15);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.68, 0.15, 0.15);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.68, 0.15, 0.15);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glColor3f(0.68, 0.15, 0.15);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glColor3f(0.68, 0.15, 0.15);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.68, 0.15, 0.15);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glColor3f(0.68, 0.15, 0.15);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.68, 0.15, 0.15);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glColor3f(0.68, 0.15, 0.15);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.68, 0.15, 0.15);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.68, 0.15, 0.15);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.68, 0.15, 0.15);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void potpohon(int x, float y, int z) //bangunan lantai 2
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.49, 0.49, 0.49);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.49, 0.49, 0.49);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.49, 0.49, 0.49);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.49, 0.49, 0.49);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glColor3f(0.49, 0.49, 0.49);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glColor3f(0.49, 0.49, 0.49);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.49, 0.49, 0.49);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glColor3f(0.49, 0.49, 0.49);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.49, 0.49, 0.49);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glColor3f(0.49, 0.49, 0.49);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.49, 0.49, 0.49);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.49, 0.49, 0.49);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.49, 0.49, 0.49);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void matahari() {
    glColor3f(1, 0.78, 0);
    glutSolidSphere(60.0, 70, 70);
}

void lampu() {
    glColor3f(1, 0.78, 0);
    glutSolidSphere(5.0, 20, 20);
}

void meja(int x, float y, int z) //tanah lantai 2
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.26, 0, 0);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glColor3f(0.26, 0, 0);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glColor3f(0.26, 0, 0);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.26, 0, 0);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void bantalan(int x, float y, int z) //tanah lantai 2
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.26, 0, 0);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glColor3f(0.26, 0, 0);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glColor3f(0.26, 0, 0);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.26, 0, 0);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.26, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void teko() {
    glColor3f(0.78, 0.75, 0.75);
    glutSolidTeapot(5.0);
}

void bintang(int x, float y, int z) {//menampilkan objek 3d
    glTranslatef(x, y, z);
    glColor3f(0.5, 1, 1);
    glBegin(GL_TRIANGLES);//berhubungan 1 sma lain
    glColor3f(0, 0.5, 1);
    glVertex3f(-0.4517712270093, -0.0423179642227, 0.0f); //c //titik sumbu
    glColor3f(0, 0.5, 1);// warna sumbu
    glVertex3f(-0.2550466112371, -0.2358175862938, 0.0f); //l ngarep
    glColor3f(0.5, 1, 1);
    glVertex3f(-0.0599344923155, -0.1632552280171, 0.1f); //m

    glColor3f(0.5, 1, 1);
    glVertex3f(-0.4517712270093, -0.0423179642227, 0.0f); //c
    glColor3f(0.5, 1, 1);
    glVertex3f(-0.2550466112371, -0.2358175862938, 0.0f); //l mburi
    glColor3f(0, 0.5, 1);
    glVertex3f(-0.0599344923155, -0.1632552280171, -0.1f); //m

    glColor3f(0.5, 1, 1);
    glVertex3f(-0.4517712270093, -0.0423179642227, 0.0f); //c
    glColor3f(0.5, 1, 1);
    glVertex3f(-0.1824842529605, -0.0020055429579, 0.0f); //d ngarep
    glColor3f(0, 0.5, 1);
    glVertex3f(-0.0599344923155, -0.1632552280171, 0.1f); //m

    glColor3f(0.5, 1, 1);
    glVertex3f(-0.4517712270093, -0.0423179642227, 0.0f); //c
    glColor3f(0.5, 1, 1);
    glVertex3f(-0.1824842529605, -0.0020055429579, 0.0f); //d mburi
    glColor3f(0, 0.5, 1);
    glVertex3f(-0.0599344923155, -0.1632552280171, -0.1f); //m

    glColor3f(0.5, 1, 1);
    glVertex3f(-0.3, -0.5, 0.0f); //k
    glColor3f(0.5, 1, 1);
    glVertex3f(-0.0663844797178, -0.3761048122953, 0.0f); //j ngarep
    glColor3f(0, 0.5, 1);
    glVertex3f(-0.0599344923155, -0.1632552280171, 0.1f); //m

    glColor3f(0.5, 1, 1);
    glVertex3f(-0.3, -0.5, 0.0f); //k
    glColor3f(0.5, 1, 1);
    glVertex3f(-0.0663844797178, -0.3761048122953, 0.0f); //j mburi
    glColor3f(0, 0.5, 1);
    glVertex3f(-0.0599344923155, -0.1632552280171, -0.1f); //m

    glColor3f(0.5, 1, 1);
    glVertex3f(-0.3, -0.5, 0.0f); //k
    glColor3f(0.5, 1, 1);
    glVertex3f(-0.2550466112371, -0.2358175862938, 0.0f); //l ngarep
    glColor3f(0, 0.5, 1);
    glVertex3f(-0.0599344923155, -0.1632552280171, 0.1f); //m

    glColor3f(0.5, 1, 1);
    glVertex3f(-0.3, -0.5, 0.0f); //k
    glColor3f(0.5, 1, 1);
    glVertex3f(-0.2550466112371, -0.2358175862938, 0.0f); //l mburi
    glColor3f(0, 0.5, 1);
    glVertex3f(-0.0599344923155, -0.1632552280171, -0.1f); //m

    glColor3f(0.5, 1, 1);
    glVertex3f(0.1771025447216, -0.4986545729403, 0.0f); //l
    glColor3f(0.5, 1, 1);
    glVertex3f(-0.0663844797178, -0.3761048122953, 0.0f); //j ngarep
    glColor3f(0, 0.5, 1);
    glVertex3f(-0.0599344923155, -0.1632552280171, 0.1f); //m

    glColor3f(0.5, 1, 1);
    glVertex3f(0.1771025447216, -0.4986545729403, 0.0f); //l
    glColor3f(0.5, 1, 1);
    glVertex3f(-0.0663844797178, -0.3761048122953, 0.0f); //j mburi
    glColor3f(0, 0.5, 1);
    glVertex3f(-0.0599344923155, -0.1632552280171, -0.1f); //m

    glColor3f(0.5, 1, 1);
    glVertex3f(0.1771025447216, -0.4986545729403, 0.0f); //l
    glColor3f(0.5, 1, 1);
    glVertex3f(0.1335651297556, -0.239042579995, 0.0f); //h ngarep
    glColor3f(0, 0.5, 1);
    glVertex3f(-0.0599344923155, -0.1632552280171, 0.1f); //m

    glColor3f(0, 0.5, 1);
    glVertex3f(0.1771025447216, -0.4986545729403, 0.0f); //l
    glColor3f(0, 0.5, 1);
    glVertex3f(0.1335651297556, -0.239042579995, 0.0f); //h mburi
    glColor3f(0, 0.5, 1);
    glVertex3f(-0.0599344923155, -0.1632552280171, -0.1f); //m

    glColor3f(0.5, 1, 1);
    glVertex3f(0.3254522549761, -0.0471554547745, 0.0f); //g
    glColor3f(0.5, 1, 1);
    glVertex3f(0.1335651297556, -0.239042579995, 0.0f); //h ngarep
    glColor3f(0, 0.5, 1);
    glVertex3f(-0.0599344923155, -0.1632552280171, 0.1f); //m

    glColor3f(0.5, 1, 1);
    glVertex3f(0.3254522549761, -0.0471554547745, 0.0f); //g
    glColor3f(0.5, 1, 1);
    glVertex3f(0.1335651297556, -0.239042579995, 0.0f); //h mburi
    glColor3f(0, 0.5, 1);
    glVertex3f(-0.0599344923155, -0.1632552280171, -0.1f); //m

    glColor3f(0.5, 1, 1);
    glVertex3f(0.3254522549761, -0.0471554547745, 0.0f); //g
    glColor3f(0.5, 1, 1);
    glVertex3f(0.061002771479, 0.0044444444444, 0.0f); //f ngarep
    glColor3f(0, 0.5, 1);
    glVertex3f(-0.0599344923155, -0.1632552280171, 0.1f); //m

    glColor3f(0.5, 1, 1);
    glVertex3f(0.3254522549761, -0.0471554547745, 0.0f); //g
    glColor3f(0.5, 1, 1);
    glVertex3f(0.061002771479, 0.0044444444444, 0.0f); //f mburi
    glColor3f(0, 0.5, 1);
    glVertex3f(-0.0599344923155, -0.1632552280171, -0.1f); //m

    glColor3f(0.5, 1, 1);
    glVertex3f(-0.061546989166, 0.2495439657344, 0.0f); //e
    glColor3f(0.5, 1, 1);
    glVertex3f(0.061002771479, 0.0044444444444, 0.0f); //f ngarep
    glVertex3f(-0.0599344923155, -0.1632552280171, 0.1f); //m
    glColor3f(0, 0.5, 1);
    glVertex3f(-0.061546989166, 0.2495439657344, 0.0f); //e
    glVertex3f(0.061002771479, 0.0044444444444, 0.0f); //f mburi
    glVertex3f(-0.0599344923155, -0.1632552280171, -0.1f); //m

    glColor3f(0.5, 1, 1);
    glVertex3f(-0.061546989166, 0.2495439657344, 0.0f); //e
    glColor3f(0.5, 1, 1);
    glVertex3f(-0.1824842529605, -0.0020055429579, 0.0f); //d ngarep
    glColor3f(0, 0.5, 1);
    glVertex3f(-0.0599344923155, -0.1632552280171, 0.1f); //m

    glColor3f(0.5, 1, 1);
    glVertex3f(-0.061546989166, 0.2495439657344, 0.0f); //e
    glColor3f(0.5, 1, 1);
    glVertex3f(-0.1824842529605, -0.0020055429579, 0.0f); //d mburi
    glColor3f(0, 0.5, 1);
    glVertex3f(-0.0599344923155, -0.1632552280171, -0.1f); //m
    glEnd();
}

void lampugantung() {
    glColor3f(1, 0.78, 0);
    glutSolidSphere(10.0, 20, 20);
}

void tianggantung(int x, float y, int z) //tanah lantai 2
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0, 0, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0, 0, 0);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0, 0, 0);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glColor3f(0, 0, 0);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glColor3f(0, 0, 0);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glColor3f(0, 0, 0);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0, 0, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glColor3f(0, 0, 0);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0, 0, 0);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0, 0, 0);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void kotaklampu(int x, float y, int z) //tanah lantai 2
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0, 0, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0, 0, 0);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0, 0, 0);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glColor3f(0, 0, 0);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glColor3f(0, 0, 0);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glColor3f(0, 0, 0);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0, 0, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glColor3f(0, 0, 0);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0, 0, 0);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0, 0, 0);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

//VIO PART
void bangunanvio(int x, float y, int z)
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.7, 0.7, 0.7);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);


    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    // BOTTOM
    glColor3f(0.87, 0.62, 0.26);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void alasvio(int x, float y, int z)
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.26, 0, 0);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void pipevio(float rbase, float rtop, float height, int resolusi)
{
    /*float i;
    glColor3f(0.5, 0.25, 0.25);
    glPushMatrix();
    glTranslatef(0.0, 0.0, -rbase / 4);
    for (i = 0; i <= height; i += rbase / 8)
    {
        glTranslatef(0.0, 0.0, rbase / 8);
        glutSolidTorus(rbase / 4, rbase - ((i * (rbase - rtop)) / height), 4, resolusi);
    }
    glTranslatef(0.0, 0.0, rbase / 4);
    glPopMatrix();
    */
}

void jalan(int x, float y, int z) {
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.56, 0.55, 0.0);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    // BOTTOM
    glColor3f(0, 0, 0);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void pot(int x, float y, int z) {
    glTranslatef(x, y, z);
    glColor3f(0.0, 0.0, 0.0);
    glutSolidCube(20);
}

void batang(int x, float y, int z) {
    glTranslatef(x, y, z);
    glColor3f(0.48, 0.29, 0.0);
    glutSolidCube(20);
}

void lingkaran(int x, float y, int z) {
    glTranslatef(x, y, z);
    glColor3f(0.31, 0.48, 0.15);
    glutSolidSphere(20.0, 30, 30);
}

void gerbang(int x, float y, int z) {
    glTranslatef(x, y, z);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(10);
}


//RICKY PART
void atapR(int x, float y, int z)
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);

    glColor3f(0.21, 0.21, 0.21);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.1f, 0.1f, 0.1f);
    glVertex3f(-0.1f, 0.1f, 0.1f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.1f, 0.1f, -0.1f);
    glVertex3f(0.1f, 0.1f, -0.1f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.1f, 0.1f, 0.1f);
    glVertex3f(-0.1f, 0.1f, -0.1f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.1f, 0.1f, -0.1f);
    glVertex3f(0.1f, 0.1f, 0.1f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    // TOP

    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void tempatsampah(int x, float y, int z)
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);

    glColor3f(0.21, 0.21, 0.21);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.8f, 0.8f, 0.8f);
    glVertex3f(-0.8f, 0.8f, 0.8f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.8f, 0.8f, -0.8f);
    glVertex3f(0.8f, 0.8f, -0.8f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.8f, 0.8f, 0.8f);
    glVertex3f(-0.8f, 0.8f, -0.8f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.8f, 0.8f, -0.8f);
    glVertex3f(0.8f, 0.8f, 0.8f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    // TOP

    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}
void bangunan3R(int x, float y, int z)
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.79, 0, 0);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void bangunanfixR(int x, float y, int z)
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.7, 0.7, 0.7);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void bangunanpintuR(int x, float y, int z)
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.26, 0, 0);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void alasR(int x, float y, int z)
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.26, 0, 0);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void pipeR(float rbase, float rtop, float height, int resolusi)
{
    float i;
    glColor3f(0.5, 0.25, 0.25);
    glPushMatrix();
    glTranslatef(0.0, 0.0, -rbase / 4);
    for (i = 0; i <= height; i += rbase / 8)
    {
        glTranslatef(0.0, 0.0, rbase / 8);
        glutSolidTorus(rbase / 4, rbase - ((i * (rbase - rtop)) / height), 4, resolusi);
    }
    glTranslatef(0.0, 0.0, rbase / 4);
    glPopMatrix();


}

void pipex(float rbase, float rtop, float height, int resolusi)
{
    /*float i;
    glColor3f(0.26, 0, 0);
    glPushMatrix();
    glTranslatef(0.0, 0.0, -rbase / 4);
    for (i = 0; i <= height; i += rbase / 8)
    {
        glTranslatef(0.0, 0.0, rbase / 8);
        glutSolidTorus(rbase / 4, rbase - ((i * (rbase - rtop)) / height), 4, resolusi);
    }
    glTranslatef(0.0, 0.0, rbase / 4);
    glPopMatrix();
    */
}

void alas(int x, float y, int z)
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.26, 0, 0);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void alasxx(int x, float y, int z)
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.1, 0.1, 0.1);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void alasxy(int x, float y, int z)
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.2, 0.2);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void alasxyz(int x, float y, int z)
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0, 1, 0);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void bangunanfixRR(int x, float y, int z)
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.26, 0, 0);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void batang1R(int x, float y, int z) {
    glTranslatef(x, y, z);
    glColor3f(0.26, 0, 0);
    glutSolidCube(15);
}

//TAMI PART
void atapT(int x, float y, int z)
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);

    glColor3f(0.21, 0.21, 0.21);

    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    //glColor3f(0.14, 0.36, 0.15);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.2f, 0.2f, 0.2f);
    glVertex3f(-0.2f, 0.2f, 0.2f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.2f, 0.2f, -0.2f);
    //glColor3f(0.14, 0.36, 0.15);
    glVertex3f(0.2f, 0.2f, -0.2f);
    glVertex3f(0.5f, -0.5f, -0.5f);

    //glColor3f(0.14, 0.36, 0.15);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.2f, 0.2f, 0.2f);
    //glColor3f(0.14, 0.36, 0.15);
    glVertex3f(-0.2f, 0.2f, -0.2f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.2f, 0.2f, -0.2f);
    //glColor3f(0.14, 0.36, 0.15);
    glVertex3f(0.2f, 0.2f, 0.2f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    // TOP

    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    //glColor3f(0.14, 0.36, 0.15);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

//////////////////BANGUNAN TAMI//////////////////

void bangunan3T(int x, float y, int z)
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.7, 0.7, 0.7);


    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glColor3f(0.7, 0.7, 0.7);

    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glColor3f(0.7, 0.7, 0.7);

    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.7, 0.7, 0.7);
    glVertex3f(-0.5f, -0.5f, -0.5f);

    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glColor3f(0.7, 0.7, 0.7);

    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.7, 0.7, 0.7);

    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.7, 0.7, 0.7);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();

}

void alasT(int x, float y, int z) {
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.26, 0, 0);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void batang1(int x, float y, int z) {
    glTranslatef(x, y, z);
    glColor3f(0.48, 0.29, 0.0);
    glutSolidCube(15);
}

//////////////////PAGAR TAMI///////////////

void pagarT(int x, float y, int z) //pagar
{
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(0.94, 0, 0);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.94, 0, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.94, 0, 0);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.94, 0, 0);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glColor3f(0.94, 0, 0);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glColor3f(0.94, 0, 0);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.94, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glColor3f(0.94, 0, 0);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.94, 0, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glColor3f(0.94, 0, 0);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glColor3f(0.94, 0, 0);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glColor3f(0.94, 0, 0);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glColor3f(0.94, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void pipeT(float rbase, float rtop, float height, int resolusi)
{
    /*float i;
    glColor3f(0.5, 0.25, 0.25);
    glPushMatrix();
    glTranslatef(0.0, 0.0, -rbase / 4);
    for (i = 0; i <= height; i += rbase / 8)
    {
        glTranslatef(0.0, 0.0, rbase / 8);
        glutSolidTorus(rbase / 4, rbase - ((i * (rbase - rtop)) / height), 4, resolusi);
    }
    glTranslatef(0.0, 0.0, rbase / 4);
    glPopMatrix();
    */
}



void draw() {
    // Mulai tuliskan isi pikiranmu disini

    //---------------------------------------- Vio Lita----------------------------------------
    // alas
    glPushMatrix();
    glScalef(500, 50, 500);
    alasvio(0, 0, 0);
    glPopMatrix();
    //balok
    glPushMatrix();
    glScalef(290, 130, 290);
    bangunanvio(0, 0.7, 0);
    glPopMatrix();
    //pagar
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glTranslatef(220, 60, 0);
    pipevio(2, 2, 160, 100);
    glPopMatrix();
    //2
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glTranslatef(-220, -220, 0);
    pipevio(2, 2, 160, 100);
    glPopMatrix();
    //3
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glTranslatef(220, -60, 0);
    pipevio(2, 2, 160, 100);
    glPopMatrix();
    //4
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glTranslatef(-220, 220, 0);
    pipevio(2, 2, 160, 100);
    glPopMatrix();
    //pondasi 1
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glTranslatef(145, 145, 0.8);
    pipevio(10, 10, 150, 100);
    glPopMatrix();
    //pondasi 2
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glTranslatef(-145, -145, 0.8);
    pipevio(10, 10, 150, 100);
    glPopMatrix();
    //pondasi 3
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glTranslatef(145, -145, 0.8);
    pipevio(10, 10, 150, 100);
    glPopMatrix();
    //pondasi 4
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glTranslatef(-145, 145, 0.8);
    pipevio(10, 10, 150, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(974.5, -3, -600.5);
    glScalef(500, 10, 200);
    jalan(-1.5, 0, 3);
    glPopMatrix();

    glPushMatrix();
    glScalef(2, 0.5, 2);
    pot(354.5, 5, -66); // balok 1 - sisi kanan
    glPopMatrix();

    glPushMatrix();
    glScalef(2, 0.5, 2);
    pot(256, 5, -66); // balok 2 - sisi kanan
    glPopMatrix();

    glPushMatrix();
    glScalef(2, 0.5, 2);
    pot(142, 5, -66);// balok 3 - sisi kanan
    glPopMatrix();

    glPushMatrix();
    glScalef(2, 0.5, 2);
    pot(354.5, 5, 66); // balok 1 - sisi kiri
    glPopMatrix();

    glPushMatrix();
    glScalef(2, 0.5, 2);
    pot(256, 0, 66); // balok 2 -  sisi kiri
    glPopMatrix();

    glPushMatrix();
    glScalef(2, 0.5, 2);
    pot(142, 0, 66); // balok 1 - sisi kiri
    glPopMatrix();

    glPushMatrix();
    glScalef(0.7, 4, 0.6);
    batang(407.5, 9.5, -221); //btg 3 - sisi kanan
    glPopMatrix();

    glPushMatrix();
    glScalef(0.7, 4, 0.6);
    batang(730.5, 9.5, -221); //btg 2 - sisi kanan
    glPopMatrix();

    glPushMatrix();
    glScalef(0.7, 4, 0.6);
    batang(1011.5, 9.5, -221); //btg 3 - sisi kanan
    glPopMatrix();

    glPushMatrix();
    glScalef(0.7, 4, 0.6);
    batang(1011.5, 9.5, 221); //btg 3 - sisi kanan
    glPopMatrix();

    glPushMatrix();
    glScalef(0.7, 4, 0.6);
    batang(730.5, 9.5, 221); //btg 2 - sisi kanan
    glPopMatrix();

    glPushMatrix();
    glScalef(0.7, 4, 0.6);
    batang(407.5, 9.5, 221); //btg 1 - sisi kanan
    glPopMatrix();

    glPushMatrix();
    glScalef(0.9, 0.9, 0.9);
    lingkaran(315, 82.5, -148.5); //daun gede kanan 
    glPopMatrix();

    glPushMatrix();
    glScalef(0.7, 0.7, 0.7);
    lingkaran(400, 139, -190);// daun med - kanan 
    glPopMatrix();

    glPushMatrix();
    glScalef(0.4, 0.4, 0.4);
    lingkaran(699.5, 289, -328.5);// daun kecil - kanan 
    glPopMatrix();

    glPushMatrix();
    glScalef(0.9, 0.9, 0.9);
    lingkaran(568.5, 82.5, -148.5); // daun gede - kanan 
    glPopMatrix();

    glPushMatrix();
    glScalef(0.7, 0.7, 0.7);
    lingkaran(730.5, 143.5, -190); // daun med - kanan 
    glPopMatrix();

    glPushMatrix();
    glScalef(0.4, 0.4, 0.4);
    lingkaran(1278, 289, -328.5); // daun kecil - kanan 
    glPopMatrix();

    glPushMatrix();
    glScalef(0.9, 0.9, 0.9);
    lingkaran(787, 82.5, -148.5); // daun gede - kanan 
    glPopMatrix();

    glPushMatrix();
    glScalef(0.7, 0.7, 0.7);
    lingkaran(1012, 143.5, -190); // daun med - kanan 
    glPopMatrix();

    glPushMatrix();
    glScalef(0.4, 0.4, 0.4);
    lingkaran(1779.5, 292.5, -333.5); // daun kecil - kanan 
    glPopMatrix();


    glPushMatrix();
    glScalef(0.9, 0.9, 0.9);
    lingkaran(315, 82.5, 148.5); //daun gede kiri 
    glPopMatrix();

    glPushMatrix();
    glScalef(0.7, 0.7, 0.7);
    lingkaran(400, 139, 190);// daun med - kiri
    glPopMatrix();

    glPushMatrix();
    glScalef(0.4, 0.4, 0.4);
    lingkaran(699.5, 289, 328.5);// daun kecil - kiri
    glPopMatrix();

    glPushMatrix();
    glScalef(0.9, 0.9, 0.9);
    lingkaran(568.5, 82.5, 148.5); // daun gede - kiri
    glPopMatrix();

    glPushMatrix();
    glScalef(0.7, 0.7, 0.7);
    lingkaran(730.5, 143.5, 190); // daun med - kiri
    glPopMatrix();

    glPushMatrix();
    glScalef(0.4, 0.4, 0.4);
    lingkaran(1278, 289, 328.5); // daun kecil - kiri
    glPopMatrix();

    glPushMatrix();
    glScalef(0.9, 0.9, 0.9);
    lingkaran(787, 82.5, 148.5); // daun gede - kiri 
    glPopMatrix();

    glPushMatrix();
    glScalef(0.7, 0.7, 0.7);
    lingkaran(1012, 143.5, 190); // daun med - kiri
    glPopMatrix();

    glPushMatrix();
    glScalef(0.4, 0.4, 0.4);
    lingkaran(1779.5, 292.5, 333.5); // daun kecil - kiri
    glPopMatrix();


    glPushMatrix();
    glScalef(1, 1, 15);
    gerbang(716, 163.5, 0.5);
    glPopMatrix();

    glPushMatrix();
    glScalef(1, 1, 15);
    gerbang(716, 150, 0.5);
    glPopMatrix();

    glPushMatrix();
    glScalef(1, 15, 1);
    gerbang(715, 5, -57);
    glPopMatrix();

    glPushMatrix();
    glScalef(1, 15, 1);
    gerbang(715, 5, 55.5);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.4, 8, 0.4);
    gerbang(1536.5, 4, -237);// tiang lampu kanan
    glPopMatrix();

    glPushMatrix();
    glScalef(0.1, 0.1, 2);
    gerbang(3911, 725, -45);// gantungan lampu kanan
    glPopMatrix();

    glPushMatrix();
    glScalef(0.1, 0.8, 0.1);
    gerbang(6159, 85.5, -829.5);// gantungan kecil lampu kanan
    glPopMatrix();

    glPushMatrix();
    glScalef(0.4, 8, 0.4);
    gerbang(978.5, 4, -237);// tiang lampu kanan
    glPopMatrix();

    glPushMatrix();
    glScalef(0.1, 0.1, 2);
    gerbang(6169, 725, -45);// gantungan lampu kanan
    glPopMatrix();

    glPushMatrix();
    glScalef(0.1, 0.8, 0.1);
    gerbang(3916.5, 86.5, -834);// gantungan kecil lampu kanan
    glPopMatrix();

    glPushMatrix();
    glScalef(0.4, 8, 0.4);
    gerbang(1536.5, 4, 237);// tiang lampu kiri
    glPopMatrix();

    glPushMatrix();
    glScalef(0.1, 0.1, 2);
    gerbang(3911, 725, 45);// gantungan lampu kiri
    glPopMatrix();

    glPushMatrix();
    glScalef(0.1, 0.8, 0.1);
    gerbang(3916.5, 86.5, 834);// gantungan kecil lampu kanan
    glPopMatrix();

    glPushMatrix();
    glScalef(0.4, 8, 0.4);
    gerbang(978.5, 4, 237);// tiang lampu kiri
    glPopMatrix();

    glPushMatrix();
    glScalef(0.1, 0.1, 2);
    gerbang(6169, 725, 45);// gantungan lampu kiri
    glPopMatrix();

    glPushMatrix();
    glScalef(0.1, 0.8, 0.1);
    gerbang(6159, 85.5, 829.5);// gantungan kecil lampu kanan
    glPopMatrix();

    glPushMatrix(); //lampu kiri belakang
    glTranslatef(392, 61, 83.5);
    lampu();
    glPopMatrix();

    glPushMatrix(); //lampu kanan belakang
    glTranslatef(392, 61, -83.5);
    lampu();
    glPopMatrix();

    glPushMatrix(); //lampu kiri depan
    glTranslatef(616, 61, 83.5);
    lampu();
    glPopMatrix();

    glPushMatrix(); //lampu kiri depan
    glTranslatef(616, 61, -83.5);
    lampu();
    glPopMatrix();



    //||||||||||||||||||||||||||||||||||| VIO End ||||||||||||||||||||||||||||||||






    //---------------------------------------- Rio ----------------------------------------
    //tiang cokelat

    //1 
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(740, 82.2, -363); //geser
    glPopMatrix();

    //2
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(23.5, 82.2, -363); //geser
    glPopMatrix();

    //3
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(-740, 82.2, -363); //geser
    glPopMatrix();

    //4 tengah depan
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(-23.5, 82.2, 363); //geser
    glPopMatrix();

    //5 kiri depan
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(-740, 82.2, 363); //geser
    glPopMatrix();

    //5 kanan depan
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(740, 82.2, 363); //geser
    glPopMatrix();

    //5 
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(-740, 82.2, -9); //geser
    glPopMatrix();


    glPushMatrix(); //bangunan lt2
    glScalef(270, 150, 270);
    bangunan2(0, 1.6, 0);
    glPopMatrix();

    glPushMatrix(); //atap lt2
    glScalef(440, 70, 440);
    glTranslatef(0.0, 5, 0.0f);
    ataplantai2(0, 0, 0);
    glPopMatrix();

    glPushMatrix(); //tanah lt2
    glScalef(450, 20, 450);
    tanah2(0, 8.1, 0);
    glPopMatrix();

    //PAGAR MERAH 

    //sisi atas 
    glPushMatrix();
    glScalef(450, 5, 5);
    pagar(0, 39, 45);
    glPopMatrix();

    glPushMatrix();
    glScalef(450, 5, 5);
    pagar(0, 39, -45);
    glPopMatrix();

    glPushMatrix();
    glScalef(5, 5, 450);
    pagar(45, 39, 0);
    glPopMatrix();

    glPushMatrix();
    glScalef(5, 5, 450);
    pagar(-45, 39, 0);
    glPopMatrix();

    //SISI BAWAH PAGAR MERAH

    glPushMatrix();
    glScalef(450, 5, 5);
    pagar(0, 36.1, 45);
    glPopMatrix();

    glPushMatrix();
    glScalef(450, 5, 5);
    pagar(0, 36.1, -45);
    glPopMatrix();

    glPushMatrix();
    glScalef(5, 5, 450);
    pagar(45, 36.1, 0);
    glPopMatrix();

    glPushMatrix();
    glScalef(5, 5, 450);
    pagar(-45, 36.1, 0);
    glPopMatrix();

    glPushMatrix(); //pintu
    glScalef(1, 100, 60);
    pintu(135, 2.2, 0);
    glPopMatrix();

    glPushMatrix(); //pintu
    glScalef(1, 100, 60);
    pintu(135, 2.2, 0);
    glPopMatrix();

    glPushMatrix(); //tiang pintu kiri
    glScalef(0.3, 10, 0.6);
    batang1(632.5, 24, -109.5); //geser
    glPopMatrix();

    glPushMatrix(); //tiang pintu kanan
    glScalef(0.3, 10, 0.6);
    batang1(632.5, 24, 109.5); //geser
    glPopMatrix();

    glPushMatrix(); //jendela kiri
    glScalef(1, 80, 40);
    jendela(135, 3, 2.0);
    glPopMatrix();

    glPushMatrix(); //jendela kanan
    glScalef(1, 80, -40);
    jendela(135, 3, 2.0);
    glPopMatrix();

    glPushMatrix(); //garistengah vertikal
    glScalef(1, 67, 3);
    garistengah(135, 3, 0);
    glPopMatrix();

    glPushMatrix(); //garis tengah horizontal
    glScalef(1, 3, 60);
    garistengah(135, 73, 0);
    glPopMatrix();

    glPushMatrix(); //garistengah dalam kanan
    glScalef(1, 50, 3);
    garistengah(135, 4.9, -5);
    glPopMatrix();

    glPushMatrix(); //garistengah dalam kiri
    glScalef(1, 50, 3);
    garistengah(135, 4.9, 5);
    glPopMatrix();

    glPushMatrix(); //garis tengah horizontal
    glScalef(1, 3, 60);
    garistengah(135, 82, 0);
    glPopMatrix();

    glPushMatrix(); //pohon daun kanan
    glScalef(40, 56.8, 40);
    glTranslatef(0, 1.8, 15);
    pohon();
    glPopMatrix();

    glPushMatrix(); //pohon batang kanan
    glScalef(40, 80, 30);
    batangR(0, 0.4, 20);
    glPopMatrix();

    glPushMatrix(); //pohon daun kiri
    glScalef(40, 56.8, 40);
    glTranslatef(0, 1.8, -15);
    pohon();
    glPopMatrix();

    glPushMatrix(); //pohon batang kiri
    glScalef(40, 80, 30);
    batangR(0, 0.4, -20);
    glPopMatrix();

    glPushMatrix(); //pohon daun kanan depan
    glScalef(40, 56.8, 40);
    glTranslatef(10, 1.8, 15);
    pohon();
    glPopMatrix();

    glPushMatrix(); //pohon batang kanan depan
    glScalef(40, 80, 30);
    batangR(10, 0.4, 20);
    glPopMatrix();

    glPushMatrix(); //pohon daun kanan belakang
    glScalef(40, 56.8, 40);
    glTranslatef(-10, 1.8, 15);
    pohon();
    glPopMatrix();

    glPushMatrix(); //pohon batang kanan belakang
    glScalef(40, 80, 30);
    batangR(-10, 0.4, 20);
    glPopMatrix();

    glPushMatrix(); //pohon daun kiri depan
    glScalef(40, 56.8, 40);
    glTranslatef(10, 1.8, -15);
    pohon();
    glPopMatrix();

    glPushMatrix(); //pohon batang kiri depan
    glScalef(40, 80, 30);
    batangR(10, 0.4, -20);
    glPopMatrix();

    glPushMatrix(); //pohon daun kiri belakang
    glScalef(40, 56.8, 40);
    glTranslatef(-10, 1.8, -15);
    pohon();
    glPopMatrix();

    glPushMatrix(); //pohon batang kiri belakang
    glScalef(40, 80, 30);
    batangR(-10, 0.4, -20);
    glPopMatrix();

    glPushMatrix(); //pohon daun belakang
    glScalef(40, 56.8, 40);
    glTranslatef(-10, 1.8, 0);
    pohon();
    glPopMatrix();

    glPushMatrix(); //pohon batang belakang
    glScalef(40, 80, 30);
    batangR(-10, 0.4, 0);
    glPopMatrix();

    glPushMatrix(); //pot pohon belakang
    glScalef(50, 10, 40);
    potpohon(-8, 0.4, 0);
    glPopMatrix();

    glPushMatrix(); //pot pohon belakang kiri
    glScalef(50, 10, 40);
    potpohon(-8, 0.4, -15.5);
    glPopMatrix();

    glPushMatrix(); //pot pohon belakang kanan
    glScalef(50, 10, 40);
    potpohon(-8, 0.4, 15.5);
    glPopMatrix();

    glPushMatrix(); //pot pohon belakang kanan tengah
    glScalef(50, 10, 40);
    potpohon(0.8, 0.4, 15.5);
    glPopMatrix();

    glPushMatrix(); //pot pohon belakang kanan depan
    glScalef(50, 10, 40);
    potpohon(8, 0.4, 15.5);
    glPopMatrix();

    glPushMatrix(); //pot pohon belakang kiri
    glScalef(50, 10, 40);
    potpohon(0.8, 0.4, -15.5);
    glPopMatrix();

    glPushMatrix(); //pot pohon belakang kiri
    glScalef(50, 10, 40);
    potpohon(8.8, 0.4, -15.5);
    glPopMatrix();

    glPushMatrix(); //matahari
    glTranslatef(-735, 1016, 591);
    matahari();
    glPopMatrix();

    glPushMatrix(); //meja
    glScalef(100, 5, 100);
    meja(0, 8.1, 0);
    glPopMatrix();

    glPushMatrix(); //kaki meja 1
    glScalef(5, 20, 5);
    meja(-9, 1.5, -9);
    glPopMatrix();

    glPushMatrix(); //kaki meja 2
    glScalef(5, 20, 5);
    meja(9, 1.5, 9);
    glPopMatrix();

    glPushMatrix(); //kaki meja 3
    glScalef(5, 20, 5);
    meja(-9, 1.5, 9);
    glPopMatrix();

    glPushMatrix(); //kaki meja 2
    glScalef(5, 20, 5);
    meja(9, 1.5, -9.5);
    glPopMatrix();

    glPushMatrix(); //bantalan 1
    glScalef(50, 5, 50);
    bantalan(0, 5.5, -2);
    glPopMatrix();

    glPushMatrix(); //bantalan 2
    glScalef(50, 5, 50);
    bantalan(0, 5.5, 2);
    glPopMatrix();

    glPushMatrix(); //bantalan 3
    glScalef(50, 5, 50);
    bantalan(2, 5.5, 0);
    glPopMatrix();

    glPushMatrix(); //bantalan 4
    glScalef(50, 5, 50);
    bantalan(-2, 5.5, 0);
    glPopMatrix();

    glPushMatrix(); //teko
    glTranslatef(-15.5, 46.5, 23);
    teko();
    glPopMatrix();

    glPushMatrix(); //pintu bawah
    glScalef(1, 100, 60);
    pintu(145, 0.7, 0);
    glPopMatrix();

    glPushMatrix(); //garistengah vertikal 2
    glScalef(1, 67, 3);
    garistengah(145, 0.8, 0);
    glPopMatrix();

    glPushMatrix(); //garis tengah horizontal 2
    glScalef(1, 3, 60);
    garistengah(145, 23, 0);
    glPopMatrix();

    glPushMatrix(); //garistengah dalam kanan 2
    glScalef(1, 50, 3);
    garistengah(145, 1.9, -5);
    glPopMatrix();

    glPushMatrix(); //garistengah dalam kiri 2
    glScalef(1, 50, 3);
    garistengah(145, 1.9, 5);
    glPopMatrix();

    glPushMatrix(); //garis tengah horizontal 2
    glScalef(1, 3, 60);
    garistengah(145, 32.7, 0);
    glPopMatrix();

    glPushMatrix(); //jendela kiri 2
    glScalef(1, 80, 40);
    jendela(145, 1.1, 2.0);
    glPopMatrix();

    glPushMatrix(); //jendela kanan 2
    glScalef(1, 80, -40);
    jendela(145, 1.1, 2.0);
    glPopMatrix();

    glPushMatrix(); //tiang gantung
    glScalef(5, 20, 5);
    tianggantung(0, 7.5, 0);
    glPopMatrix();

    glPushMatrix(); //lampu gantung
    glTranslatef(0, 130.5, 0);
    lampugantung();
    glPopMatrix();

    glPushMatrix(); //kotak lampu dasar
    glScalef(20, 5, 20);
    kotaklampu(0, 30.5, 0);
    glPopMatrix();





    glPushMatrix(); //kotak lampu kanan tengah2
    glScalef(20, 1, 1);
    kotaklampu(0, 123, -12.5);
    glPopMatrix();

    glPushMatrix(); //kotak lampu kiri tengah2
    glScalef(20, 1, 1);
    kotaklampu(0, 123, 12.5);
    glPopMatrix();

    glPushMatrix(); //kotak lampu kanan tengah3
    glScalef(20, 1, 1);
    kotaklampu(0, 126, -12.5);
    glPopMatrix();

    glPushMatrix(); //kotak lampu kiri tengah3
    glScalef(20, 1, 1);
    kotaklampu(0, 126, 12.5);
    glPopMatrix();

    glPushMatrix(); //kotak lampu kanan tengah4
    glScalef(20, 1, 1);
    kotaklampu(0, 129, -12.5);
    glPopMatrix();

    glPushMatrix(); //kotak lampu kanan tengah4
    glScalef(20, 1, 1);
    kotaklampu(0, 129, 12.5);
    glPopMatrix();

    glPushMatrix(); //kotak lampu kanan tengah5
    glScalef(20, 1, 1);
    kotaklampu(0, 132, -12.5);
    glPopMatrix();

    glPushMatrix(); //kotak lampu kanan tengah5
    glScalef(20, 1, 1);
    kotaklampu(0, 132, 12.5);
    glPopMatrix();

    glPushMatrix(); //kotak lampu kanan tengah6
    glScalef(20, 1, 1);
    kotaklampu(0, 135, -12.5);
    glPopMatrix();

    glPushMatrix(); //kotak lampu kiri tengah6
    glScalef(20, 1, 1);
    kotaklampu(0, 135, 12.5);
    glPopMatrix();

    glPushMatrix(); //kotak lampu kiri tengah7
    glScalef(20, 1, 1);
    kotaklampu(0, 138, -12.5);
    glPopMatrix();

    glPushMatrix(); //kotak lampu kanan tengah7
    glScalef(20, 1, 1);
    kotaklampu(0, 138, 12.5);
    glPopMatrix();

    glPushMatrix(); //kotak lampu depan tengah8
    glScalef(1, 1, 24);
    kotaklampu(10.9, 123, 0);
    glPopMatrix();

    glPushMatrix(); //kotak lampu depan tengah9
    glScalef(1, 1, 24);
    kotaklampu(10.9, 126, 0);
    glPopMatrix();

    glPushMatrix(); //kotak lampu depan tengah10
    glScalef(1, 1, 24);
    kotaklampu(10.9, 129, 0);
    glPopMatrix();

    glPushMatrix(); //kotak lampu depan tengah11
    glScalef(1, 1, 24);
    kotaklampu(10.9, 132, 0);
    glPopMatrix();

    glPushMatrix(); //kotak lampu depan tengah12
    glScalef(1, 1, 24);
    kotaklampu(10.9, 135, 0);
    glPopMatrix();

    glPushMatrix(); //kotak lampu depan tengah13
    glScalef(1, 1, 24);
    kotaklampu(10.9, 138, 0);
    glPopMatrix();

    glPushMatrix(); //kotak lampu blkg tengah8
    glScalef(1, 1, 24);
    kotaklampu(-10.9, 123, 0);
    glPopMatrix();

    glPushMatrix(); //kotak lampu blkg tengah9
    glScalef(1, 1, 24);
    kotaklampu(-10.9, 126, 0);
    glPopMatrix();

    glPushMatrix(); //kotak lampu blkg tengah10
    glScalef(1, 1, 24);
    kotaklampu(-10.9, 129, 0);
    glPopMatrix();

    glPushMatrix(); //kotak lampu blkg tengah11
    glScalef(1, 1, 24);
    kotaklampu(-10.9, 132, 0);
    glPopMatrix();

    glPushMatrix(); //kotak lampu blkg tengah12
    glScalef(1, 1, 24);
    kotaklampu(-10.9, 135, 0);
    glPopMatrix();

    glPushMatrix(); //kotak lampu blkg tengah13
    glScalef(1, 1, 24);
    kotaklampu(-10.9, 138, 0);
    glPopMatrix();

    ///pagar vio

    //tiang cokelat

    //1 
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(740, 18.2, -363); //geser
    glPopMatrix();

    //2
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(23.5, 18.2, -363); //geser
    glPopMatrix();

    //3
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(-740, 18.2, -363); //geser
    glPopMatrix();

    //4 tengah depan
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(-23.5, 18.2, 363); //geser
    glPopMatrix();

    //5 kiri depan
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(-740, 18.2, 363); //geser
    glPopMatrix();

    //5 kanan depan
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(740, 18.2, 363); //geser
    glPopMatrix();

    //5 
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(-740, 18.2, -9); //geser
    glPopMatrix();

    //PAGAR MERAH 

    //sisi atas 
    glPushMatrix();
    glScalef(450, 5, 5);
    pagar(0, 10, 45);
    glPopMatrix();

    glPushMatrix();
    glScalef(450, 5, 5);
    pagar(0, 10, -45);
    glPopMatrix();

    glPushMatrix();
    glScalef(5, 5, 450);
    pagar(-45, 10, 0);
    glPopMatrix();

    //SISI BAWAH PAGAR MERAH

    glPushMatrix();
    glScalef(450, 5, 5);
    pagar(0, 7.5, 45);
    glPopMatrix();

    glPushMatrix();
    glScalef(450, 5, 5);
    pagar(0, 7.5, -45);
    glPopMatrix();


    glPushMatrix();
    glScalef(5, 5, 450);
    pagar(-45, 7.5, 0);
    glPopMatrix();




    //||||||||||||||||||||||||||||||||||| Rio End ||||||||||||||||||||||||||||||||

    //------------------------------------ Ricky -------------------------------------------
    //alas

    glPushMatrix();
    glScalef(280, 20, 280);
    alasR(0, 24.6, 0);
    glPopMatrix();
    //Badan
    glPushMatrix();
    glScalef(140, 110, 140);
    bangunanfixR(0, 5, 0);
    glPopMatrix();
    //atap
    glPushMatrix();
    glScalef(280, 100, 280);
    atapR(0, 6.4, 0);
    glPopMatrix();
    //pagar 1
    glPushMatrix();
    glScalef(280, 5, 5);
    bangunan3R(0, 102.2, 28);
    glPopMatrix();
    //pagar 1b
    glPushMatrix();
    glScalef(280, 5, 5);
    bangunan3R(0, 104.5, 28);
    glPopMatrix();
    //pagar 2
    glPushMatrix();
    glScalef(280, 5, 5);
    bangunan3R(0, 102.2, -28);
    glPopMatrix();
    //pagar 2b
    glPushMatrix();
    glScalef(280, 5, 5);
    bangunan3R(0, 104.5, -28);
    glPopMatrix();
    //pagar 3
    glPushMatrix();
    glScalef(5, 5, 280);
    bangunan3R(28, 102.2, 0);
    glPopMatrix();
    //pagar 3b
    glPushMatrix();
    glScalef(5, 5, 280);
    bangunan3R(28, 104.5, 0);
    glPopMatrix();
    //pagar 4
    glPushMatrix();
    glScalef(5, 5, 280);
    bangunan3R(-28, 102.2, 0);
    glPopMatrix();
    //pagar 4b
    glPushMatrix();
    glScalef(5, 5, 280);
    bangunan3R(-28, 104.5, 0);
    glPopMatrix();
    //pucuk
    glPushMatrix();
    glScalef(50, 30, 50);
    bangunanfixR(0, 21.8, 0);
    glPopMatrix();
    //puncak
    glPushMatrix();
    glScalef(10, 80, 10);
    bangunan3R(0, 8.8, 0);
    glPopMatrix();
    //tabung puncak
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glTranslatef(0, 0, 682.6);
    pipeR(10, 10, 10, 100);
    glPopMatrix();
    //tabung puncak 2
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glTranslatef(0, 0, 702.6);
    pipeR(10, 10, 10, 100);
    glPopMatrix();
    //tabung puncak 3
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glTranslatef(0, 0, 720.6);
    pipeR(10, 10, 10, 100);
    glPopMatrix();
    //tabung puncak 4
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glTranslatef(0, 0, 750.6);
    pipeR(20, 1, 10, 100);
    glPopMatrix();
    /////////////////////PAGAR RICKY ////////////////////

    //1 
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(450.5, 226, -221); //geser
    glPopMatrix();

    //2
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(13.5, 226, -221); //geser
    glPopMatrix();

    //3
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(-450.5, 226, -221); //geser
    glPopMatrix();

    //4 tengah depan
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(-13.5, 226, 221); //geser
    glPopMatrix();

    //5 kiri depan
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(-450.5, 226, 221); //geser
    glPopMatrix();

    //5 kanan depan
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(450.5, 226, 221); //geser
    glPopMatrix();

    //5 
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(-450, 226, -9); //geser
    glPopMatrix();

    //5 
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(450, 226, -9); //geser
    glPopMatrix();

    ////gapuraamiring
    glPushMatrix();
    glScalef(140, 5, 5);
    bangunanpintuR(0, 114.6, 14);
    glPopMatrix();
    ////x22
    glPushMatrix();
    glScalef(140, 5, 5);
    bangunanpintuR(0, 114.6, -14);
    glPopMatrix();

    glPushMatrix();
    glScalef(200, 200, 300);
    bintang(3.5, 6, -2.5);
    glPopMatrix();

    //patung
    glPushMatrix();
    glScalef(10, 150, 30);
    alas(-11, 0.5, 0);
    glPopMatrix();
    //face
    glPushMatrix();
    glScalef(10, 13, 30);
    alasxx(-10, 9.5, 0);
    glPopMatrix();
    //face2
    glPushMatrix();
    glScalef(10, 2, 30);
    alasxx(-10, 56, 0);
    glPopMatrix();
    //patung
    glPushMatrix();
    glScalef(10, 5, 3);
    alasxx(-10.6, 23, -5);
    glPopMatrix();
    //patung
    glPushMatrix();
    glScalef(10, 5, 3);
    alasxx(-10.6, 23, +5);
    glPopMatrix();
    //face3
    glPushMatrix();
    glScalef(10, 30, 30);
    alasxx(-10, 5, 0);
    glPopMatrix();

    //face
    glPushMatrix();
    glScalef(10, 10, 10);
    alasxx(-10, 13, 0);
    glPopMatrix();
    //face
    glPushMatrix();
    glScalef(9, 10, 30);
    alasxy(-10, 14, 0);
    glPopMatrix();
    //facehidung
    glPushMatrix();
    glScalef(10, 30, 10);
    alasxy(-9.5, 3.7, 0);
    glPopMatrix();

    //face
    glPushMatrix();
    glScalef(8, 8, 8);
    alasxyz(-13, 16.5, -1.5);
    glPopMatrix();
    //face
    glPushMatrix();
    glScalef(8, 8, 8);
    alasxyz(-13, 16.5, 1.5);
    glPopMatrix();


    //1 
    glPushMatrix();
    glScalef(0.3, 6, 0.6);
    batang1R(-233, 91, 35); //geser
    glPopMatrix();
    //1a
    glPushMatrix();
    glScalef(0.3, 6, 0.6);
    batang1R(-233, 91, -35); //geser
    glPopMatrix();

    //2
    glPushMatrix();
    glScalef(0.3, 6, 0.6);
    batang1R(233, 91, 35); //geser
    glPopMatrix();
    //2b
    glPushMatrix();
    glScalef(0.3, 6, 0.6);
    batang1R(233, 91, -35); //geser
    glPopMatrix();

    //3
    glPushMatrix();
    glScalef(0.3, 6, 0.6);
    batang1R(35, 91, 110); //geser
    glPopMatrix();
    //3b
    glPushMatrix();
    glScalef(0.3, 6, 0.6);
    batang1R(-35, 91, 110); //geser
    glPopMatrix();

    //4
    glPushMatrix();
    glScalef(0.3, 6, 0.6);
    batang1R(35, 91, -110); //geser
    glPopMatrix();
    //4
    glPushMatrix();
    glScalef(0.3, 6, 0.6);
    batang1R(-35, 91, -110); //geser
    glPopMatrix();


    // tempat sampah
    glPushMatrix();
    glScalef(25, 25, 25);
    tempatsampah(23.5, 0.5, 5.5);
    glPopMatrix();
    // tempat sampah2
    glPushMatrix();
    glScalef(25, 25, 25);
    tempatsampah(23.5, 0.5, -5.5);
    glPopMatrix();
    // tempat sampah3
    glPushMatrix();
    glScalef(25, 25, 25);
    tempatsampah(15, 0.5, 5.5);
    glPopMatrix();
    // tempat sampah4
    glPushMatrix();
    glScalef(25, 25, 25);
    tempatsampah(15, 0.5, -5.5);
    glPopMatrix();

    //pondasi1
    glPushMatrix();
    glScalef(10, 110, 10);
    bangunanfixRR(-7, 5, -7);
    glPopMatrix();
    //pondasi2
    glPushMatrix();
    glScalef(10, 110, 10);
    bangunanfixRR(7, 5, 7);
    glPopMatrix();
    //pondasi3
    glPushMatrix();
    glScalef(10, 110, 10);
    bangunanfixRR(-7, 5, 7);
    glPopMatrix();
    //pondasi4
    glPushMatrix();
    glScalef(10, 110, 10);
    bangunanfixRR(7, 5, -7);
    glPopMatrix();

    ///pondasi tami
    //pondasi1
    glPushMatrix();
    glScalef(10, 90, 10);
    bangunanfixRR(10, 4.6, -10);
    glPopMatrix();
    //pondasi2
    glPushMatrix();
    glScalef(10, 90, 10);
    bangunanfixRR(-10, 4.6, 10);
    glPopMatrix();
    //pondasi3
    glPushMatrix();
    glScalef(10, 90, 10);
    bangunanfixRR(-10, 4.6, -10);
    glPopMatrix();
    //pondasi4
    glPushMatrix();
    glScalef(10, 90, 10);
    bangunanfixRR(10, 4.6, 10);
    glPopMatrix();

    //pondasi rio
    //pondasi1
    glPushMatrix();
    glScalef(10, 150, 10);
    bangunanfixRR(14, 1.6, 14);
    glPopMatrix();
    //pondasi2
    glPushMatrix();
    glScalef(10, 150, 10);
    bangunanfixRR(-14, 1.6, -14);
    glPopMatrix();
    //pondasi3
    glPushMatrix();
    glScalef(10, 150, 10);
    bangunanfixRR(-14, 1.6, 14);
    glPopMatrix();
    //pondasi4
    glPushMatrix();
    glScalef(10, 150, 10);
    bangunanfixRR(14, 1.6, -14);
    glPopMatrix();

    //pondasivio
    //pondasi 1
    glPushMatrix();
    glScalef(10, 130, 10);
    bangunanfixRR(-15, 0.65, -15);
    glPopMatrix();
    //pondasi 2
    glPushMatrix();
    glScalef(10, 130, 10);
    bangunanfixRR(-15, 0.65, 15);
    glPopMatrix();
    //pondasi 3
    glPushMatrix();
    glScalef(10, 130, 10);
    bangunanfixRR(15, 0.65, -15);
    glPopMatrix();
    //pondasi 4
    glPushMatrix();
    glScalef(10, 130, 10);
    bangunanfixRR(15, 0.65, 15);
    glPopMatrix();

    //--------------------------------------------- Ricky END--------------------------------------

    //--------------------------------------------- Tami ------------------------------------------
// BANGUNAN TAMI

    glPushMatrix();
    glScalef(200, 90, 200);
    bangunan3T(0, 4.6, 0);
    glPopMatrix();

    ////gapuraamiring
    glPushMatrix();
    glScalef(200, 5, 5);
    bangunanpintuR(0, 87, -20);
    glPopMatrix();
    ////x22
    glPushMatrix();
    glScalef(200, 5, 5);
    bangunanpintuR(0, 87, 20);
    glPopMatrix();



    // ALAS TAMI 

    glPushMatrix();
    glScalef(280, 10, 280);
    glColor3f(0.14, 0.36, 0.15);
    alasT(0, 37, 0);
    glPopMatrix();


    //ATAP TAMI 
    glPushMatrix();
    glRotatef(0, 0, 0, 0);
    glScalef(300, 35, 300);
    atapT(0, 13.6, 0);
    glPopMatrix();


    /////////////////// PAGAR BERDIRI //////////////////

      //1 
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(450.5, 170, -221); //geser
    glPopMatrix();

    //2
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(13.5, 170, -221); //geser
    glPopMatrix();

    //3
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(-450.5, 170, -221); //geser
    glPopMatrix();

    //4 tengah depan
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(-13.5, 170, 221); //geser
    glPopMatrix();

    //5 kiri depan
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(-450.5, 170, 221); //geser
    glPopMatrix();

    //5 kanan depan
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(450.5, 170, 221); //geser
    glPopMatrix();

    //5 
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(-450, 170, -9); //geser
    glPopMatrix();

    //5 
    glPushMatrix();
    glScalef(0.3, 2.3, 0.6);
    batang1(450, 170, -9); //geser
    glPopMatrix();

    /// PAGAR BOBO /////////

    //pagar 1
    glPushMatrix();
    glScalef(280, 5, 5);
    pagarT(0, 76.8, 28);
    glPopMatrix();

    //pagar 1B
    glPushMatrix();
    glScalef(280, 5, 5);
    pagarT(0, 80, 28);
    glPopMatrix();

    //pagar 2
    glPushMatrix();
    glScalef(280, 5, 5);
    pagarT(0, 76.8, -28);
    glPopMatrix();

    //pagar 2b
    glPushMatrix();
    glScalef(280, 5, 5);
    pagarT(0, 80, -28);
    glPopMatrix();
    //pagar 3
    glPushMatrix();
    glScalef(5, 5, 280);
    pagarT(28, 76.8, 0);
    glPopMatrix();


    //pagar 3b
    glPushMatrix();
    glScalef(5, 5, 280);
    pagarT(28, 80, 0);
    glPopMatrix();
    //pagar 4
    glPushMatrix();
    glScalef(5, 5, 280);
    pagarT(-28, 76.8, 0);
    glPopMatrix();


    //pagar 4b
    glPushMatrix();
    glScalef(5, 5, 280);
    pagarT(-28, 80, 0);
    glPopMatrix();

    //------------------------------------------------ Tami END ----------------------------------------



    ground();
    cout << x_geser << " | X |" << y_geser << " | Y|" << z_geser << " | Z|" << "\n";
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
    case '6':
        x_geser += 5.5;
        break;
    case '4':
        x_geser -= 0.1;
        break;
    case '8':
        y_geser += 0.5;
        break;
    case '2':
        y_geser -= 0.5;
        break;
    case '9':
        z_geser -= 0.5;
        break;
    case '1':
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
    glutCreateWindow("TR GRAFKOM KELOMPOK 3");

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