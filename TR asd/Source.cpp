#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

#define FPS 120
#define TO_RADIANS 3.14/180.0

//  Anggota Kelompok 6
//  Lindan Prastyan S (672020024)
//  Ferdynand S (672020028)
//  Vico Marcellino J M (672020196)
//  Timothy Aurelliano Y H (672020248)

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
    glColor3f(0.2, 0.68, 0);
    glVertex3f(-1000.0, 0, -1000.0);

    glColor3f(0.17, 0.58, 0);
    glVertex3f(1000.0, 0, -1000.0);

    glColor3f(0.17, 0.58, 0);
    glVertex3f(1000.0, 0, 1000.0);

    glColor3f(0.2, 0.68, 0);
    glVertex3f(-1000.0, 0, 1000.0);
    glEnd();
}

void lantaidasar() {
    //dasar gedung
    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-300.0, 0.0, 300);
    glVertex3f(-300.0, 40.0, 300);
    glVertex3f(300.0, 40.0, 300);
    glVertex3f(300.0, 0.0, 300);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-300.0, 0.0, -300);
    glVertex3f(-300.0, 40.0, -300);
    glVertex3f(300.0, 40.0, -300);
    glVertex3f(300.0, 0.0, -300);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-300.0, 0.0, -300);
    glVertex3f(-300.0, 40.0, -300);
    glVertex3f(-300.0, 40.0, 300);
    glVertex3f(-300.0, 0.0, 300);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(300.0, 0.0, -300);
    glVertex3f(300.0, 40.0, -300);
    glVertex3f(300.0, 40.0, 300);
    glVertex3f(300.0, 00.0, 300);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-300.0, 40.0, -300);
    glVertex3f(-300.0, 40.0, 300);
    glVertex3f(300.0, 40.0, 300);
    glVertex3f(300.0, 40.0, -300);
    glEnd();
    //batas dasar gedung

    //batas dasar jalanan depan
    glBegin(GL_POLYGON); //depan
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-145.0, 0.0, 900);
    glVertex3f(-145.0, 5.0, 900);
    glVertex3f(145.0, 5.0, 900);
    glVertex3f(145.0, 0.0, 900);
    glEnd();
    glBegin(GL_POLYGON); //belakang
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-145.0, 0.0, 895);
    glVertex3f(-145.0, 5.0, 895);
    glVertex3f(145.0, 5.0, 895);
    glVertex3f(145.0, 0.0, 895);
    glEnd();
    glBegin(GL_POLYGON); //atas
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-140.0, 5.0, 895);
    glVertex3f(-140.0, 5.0, 900);
    glVertex3f(140.0, 5.0, 900);
    glVertex3f(140.0, 5.0, 895);
    glEnd();

    //batas dasar jalanan kiri
    glBegin(GL_POLYGON); //depan
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-145.0, 0.0, 300);
    glVertex3f(-145.0, 5.0, 300);
    glVertex3f(-145.0, 5.0, 900);
    glVertex3f(-145.0, 0.0, 900);
    glEnd();
    glBegin(GL_POLYGON); //belakang
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-140.0, 0.0, 300);
    glVertex3f(-140.0, 5.0, 300);
    glVertex3f(-140.0, 5.0, 900);
    glVertex3f(-140.0, 0.0, 900);
    glEnd();
    glBegin(GL_POLYGON); //atas
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-140.0, 5.0, 300);
    glVertex3f(-145.0, 5.0, 300);
    glVertex3f(-145.0, 5.0, 900);
    glVertex3f(-140.0, 5.0, 900);
    glEnd();

    //batas dasar jalanan kanan
    glBegin(GL_POLYGON); //depan
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(145.0, 0.0, 300);
    glVertex3f(145.0, 5.0, 300);
    glVertex3f(145.0, 5.0, 900);
    glVertex3f(145.0, 0.0, 900);
    glEnd();
    glBegin(GL_POLYGON); //belakang
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(140.0, 0.0, 300);
    glVertex3f(140.0, 5.0, 300);
    glVertex3f(140.0, 5.0, 900);
    glVertex3f(140.0, 0.0, 900);
    glEnd();
    glBegin(GL_POLYGON); //atas
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(140.0, 5.0, 300);
    glVertex3f(145.0, 5.0, 300);
    glVertex3f(145.0, 5.0, 900);
    glVertex3f(140.0, 5.0, 900);
    glEnd();

    //garis batas jalan
    glBegin(GL_LINE_LOOP); //depan
    glColor3f(0, 0, 0);
    glVertex3f(-145.0, 0.0, 900);
    glVertex3f(-145.0, 5.0, 900);
    glVertex3f(145.0, 5.0, 900);
    glVertex3f(145.0, 0.0, 900);
    glEnd();
    glBegin(GL_LINE_LOOP); //depan-belakang
    glColor3f(0, 0, 0);
    glVertex3f(-140.0, 0.0, 895);
    glVertex3f(-140.0, 5.0, 895);
    glVertex3f(140.0, 5.0, 895);
    glVertex3f(140.0, 0.0, 895);
    glEnd();
    glBegin(GL_LINE_LOOP); //kiri
    glColor3f(0, 0, 0);
    glVertex3f(-145.0, 0.0, 300);
    glVertex3f(-145.0, 5.0, 300);
    glVertex3f(-145.0, 5.0, 900);
    glVertex3f(-145.0, 0.0, 900);
    glEnd();
    glBegin(GL_LINE_LOOP); //kiri-belakang
    glColor3f(0, 0, 0);
    glVertex3f(-140.0, 0.0, 300);
    glVertex3f(-140.0, 5.0, 300);
    glVertex3f(-140.0, 5.0, 895);
    glVertex3f(-140.0, 0.0, 895);
    glEnd();
    glBegin(GL_LINE_LOOP); //kanan
    glColor3f(0, 0, 0);
    glVertex3f(145.0, 0.0, 300);
    glVertex3f(145.0, 5.0, 300);
    glVertex3f(145.0, 5.0, 900);
    glVertex3f(145.0, 0.0, 900);
    glEnd();
    glBegin(GL_LINE_LOOP); //kanan-belakang
    glColor3f(0, 0, 0);
    glVertex3f(140.0, 0.0, 300);
    glVertex3f(140.0, 5.0, 300);
    glVertex3f(140.0, 5.0, 895);
    glVertex3f(140.0, 0.0, 895);
    glEnd();

    //jalan
    glBegin(GL_POLYGON); 
    glColor3f(0.82, 0.82, 0.82);
    glVertex3f(-140.0, 0.2, 300);
    glVertex3f(-140.0, 0.2, 900);
    glVertex3f(140.0, 0.2, 900);
    glVertex3f(140.0, 0.2, 300);
    glEnd();

    //garis dasar gedung
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-300.0, 0.0, 300);
    glVertex3f(-300.0, 40.0, 300);
    glVertex3f(300.0, 40.0, 300);
    glVertex3f(300.0, 0.0, 300);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-300.0, 0.0, -300);
    glVertex3f(-300.0, 40.0, -300);
    glVertex3f(300.0, 40.0, -300);
    glVertex3f(300.0, 0.0, -300);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-300.0, 0.0, -300);
    glVertex3f(-300.0, 40.0, -300);
    glVertex3f(-300.0, 40.0, 300);
    glVertex3f(-300.0, 0.0, 300);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(300.0, 0.0, -300);
    glVertex3f(300.0, 40.0, -300);
    glVertex3f(300.0, 40.0, 300);
    glVertex3f(300.0, 00.0, 300);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-300.0, 40.0, -300);
    glVertex3f(-300.0, 40.0, 300);
    glVertex3f(300.0, 40.0, 300);
    glVertex3f(300.0, 40.0, -300);
    glEnd();
}

void lantai1() {
    //dinding 1
    glBegin(GL_POLYGON);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(-150.0, 40.0, 150);
    glVertex3f(-150.0, 250.0, 150);
    glVertex3f(150.0, 250.0, 150);
    glVertex3f(150.0, 40.0, 150);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(-150.0, 40.0, -150);
    glVertex3f(-150.0, 250.0, -150);
    glVertex3f(150.0, 250.0, -150);
    glVertex3f(150.0, 40.0, -150);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(-150.0, 40.0, -150);
    glVertex3f(-150.0, 250.0, -150);
    glVertex3f(-150.0, 250.0, 150);
    glVertex3f(-150.0, 40.0, 150);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(150.0, 40.0, -150);
    glVertex3f(150.0, 250.0, -150);
    glVertex3f(150.0, 250.0, 150);
    glVertex3f(150.0, 40.0, 150);
    glEnd();
    //dinding 1 akhir

    // - - - - - GARIS DINDING - - - - //
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-150.0, 40.0, 150);
    glVertex3f(-150.0, 250.0, 150);
    glVertex3f(150.0, 250.0, 150);
    glVertex3f(150.0, 40.0, 150);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-150.0, 40.0, -150);
    glVertex3f(-150.0, 250.0, -150);
    glVertex3f(150.0, 250.0, -150);
    glVertex3f(150.0, 40.0, -150);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-150.0, 40.0, -150);
    glVertex3f(-150.0, 250.0, -150);
    glVertex3f(-150.0, 250.0, 150);
    glVertex3f(-150.0, 40.0, 150);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(150.0, 40.0, -150);
    glVertex3f(150.0, 250.0, -150);
    glVertex3f(150.0, 250.0, 150);
    glVertex3f(150.0, 40.0, 150);
    glEnd();
    //dinding 1 akhir

    //hiasan garis merah depan
    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-150.0, 40.0, 151);
    glVertex3f(-150.0, 250.0, 151);
    glVertex3f(-130.0, 250.0, 151);
    glVertex3f(-130.0, 40.0, 151);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-110.0, 40.0, 151);
    glVertex3f(-110.0, 250.0, 151);
    glVertex3f(-90.0, 250.0, 151);
    glVertex3f(-90.0, 40.0, 151);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-60.0, 40.0, 151);
    glVertex3f(-60.0, 250.0, 151);
    glVertex3f(-40.0, 250.0, 151);
    glVertex3f(-40.0, 40.0, 151);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(150.0, 40.0, 151);
    glVertex3f(150.0, 250.0, 151);
    glVertex3f(130.0, 250.0, 151);
    glVertex3f(130.0, 40.0, 151);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(110.0, 40.0, 151);
    glVertex3f(110.0, 250.0, 151);
    glVertex3f(90.0, 250.0, 151);
    glVertex3f(90.0, 40.0, 151);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(60.0, 40.0, 151);
    glVertex3f(60.0, 250.0, 151);
    glVertex3f(40.0, 250.0, 151);
    glVertex3f(40.0, 40.0, 151);
    glEnd();
    //hiasan garis merah akhir

    //hiasan garis merah belakang
    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-150.0, 40.0, -151);
    glVertex3f(-150.0, 250.0, -151);
    glVertex3f(-130.0, 250.0, -151);
    glVertex3f(-130.0, 40.0, -151);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-110.0, 40.0, -151);
    glVertex3f(-110.0, 250.0, -151);
    glVertex3f(-90.0, 250.0, -151);
    glVertex3f(-90.0, 40.0, -151);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-60.0, 40.0, -151);
    glVertex3f(-60.0, 250.0, -151);
    glVertex3f(-40.0, 250.0, -151);
    glVertex3f(-40.0, 40.0, -151);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-10.0, 40.0, -151);
    glVertex3f(-10.0, 250.0, -151);
    glVertex3f(10.0, 250.0, -151);
    glVertex3f(10.0, 40.0, -151);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(150.0, 40.0, -151);
    glVertex3f(150.0, 250.0, -151);
    glVertex3f(130.0, 250.0, -151);
    glVertex3f(130.0, 40.0, -151);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(110.0, 40.0, -151);
    glVertex3f(110.0, 250.0, -151);
    glVertex3f(90.0, 250.0, -151);
    glVertex3f(90.0, 40.0, -151);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(60.0, 40.0, -151);
    glVertex3f(60.0, 250.0, -151);
    glVertex3f(40.0, 250.0, -151);
    glVertex3f(40.0, 40.0, -151);
    glEnd();

    //hiasan garis merah kanan
    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-151.0, 40.0, -150);
    glVertex3f(-151.0, 250.0, -150);
    glVertex3f(-151.0, 250.0, -130);
    glVertex3f(-151.0, 40.0, -130);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-151.0, 40.0, -110);
    glVertex3f(-151.0, 250.0, -110);
    glVertex3f(-151.0, 250.0, -90);
    glVertex3f(-151.0, 40.0, -90);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-151.0, 40.0, -60);
    glVertex3f(-151.0, 250.0, -60);
    glVertex3f(-151.0, 250.0, -40);
    glVertex3f(-151.0, 40.0, -40);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-151.0, 40.0, -10);
    glVertex3f(-151.0, 250.0, -10);
    glVertex3f(-151.0, 250.0, 10);
    glVertex3f(-151.0, 40.0, 10);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-151.0, 40.0, 150);
    glVertex3f(-151.0, 250.0, 150);
    glVertex3f(-151.0, 250.0, 130);
    glVertex3f(-151.0, 40.0, 130);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-151.0, 40.0, 110);
    glVertex3f(-151.0, 250.0, 110);
    glVertex3f(-151.0, 250.0, 90);
    glVertex3f(-151.0, 40.0, 90);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-151.0, 40.0, 60);
    glVertex3f(-151.0, 250.0, 60);
    glVertex3f(-151.0, 250.0, 40);
    glVertex3f(-151.0, 40.0, 40);
    glEnd();

    //hiasan garis merah kanan
    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(151.0, 40.0, -150);
    glVertex3f(151.0, 250.0, -150);
    glVertex3f(151.0, 250.0, -130);
    glVertex3f(151.0, 40.0, -130);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(151.0, 40.0, -110);
    glVertex3f(151.0, 250.0, -110);
    glVertex3f(151.0, 250.0, -90);
    glVertex3f(151.0, 40.0, -90);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(151.0, 40.0, -60);
    glVertex3f(151.0, 250.0, -60);
    glVertex3f(151.0, 250.0, -40);
    glVertex3f(151.0, 40.0, -40);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(151.0, 40.0, -10);
    glVertex3f(151.0, 250.0, -10);
    glVertex3f(151.0, 250.0, 10);
    glVertex3f(151.0, 40.0, 10);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(151.0, 40.0, 150);
    glVertex3f(151.0, 250.0, 150);
    glVertex3f(151.0, 250.0, 130);
    glVertex3f(151.0, 40.0, 130);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(151.0, 40.0, 110);
    glVertex3f(151.0, 250.0, 110);
    glVertex3f(151.0, 250.0, 90);
    glVertex3f(151.0, 40.0, 90);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(151.0, 40.0, 60);
    glVertex3f(151.0, 250.0, 60);
    glVertex3f(151.0, 250.0, 40);
    glVertex3f(151.0, 40.0, 40);
    glEnd();

    //atap 1 merah
    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-150.0, 250.0, 150);
    glVertex3f(-200.0, 270.0, 200);
    glVertex3f(200.0, 270.0, 200);
    glVertex3f(150.0, 250.0, 150);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-150.0, 250.0, -150);
    glVertex3f(-200.0, 270.0, -200);
    glVertex3f(200.0, 270.0, -200);
    glVertex3f(150.0, 250.0, -150);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-150.0, 250.0, -150);
    glVertex3f(-200.0, 270.0, -200);
    glVertex3f(-200.0, 270.0, 200);
    glVertex3f(-150.0, 250.0, 150);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(150.0, 250.0, -150);
    glVertex3f(200.0, 270.0, -200);
    glVertex3f(200.0, 270.0, 200);
    glVertex3f(150.0, 250.0, 150);
    glEnd();

    //garis atap merah
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-150.0, 250.0, 150);
    glVertex3f(-200.0, 270.0, 200);
    glVertex3f(200.0, 270.0, 200);
    glVertex3f(150.0, 250.0, 150);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-150.0, 250.0, -150);
    glVertex3f(-200.0, 270.0, -200);
    glVertex3f(200.0, 270.0, -200);
    glVertex3f(150.0, 250.0, -150);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-150.0, 250.0, -150);
    glVertex3f(-200.0, 270.0, -200);
    glVertex3f(-200.0, 270.0, 200);
    glVertex3f(-150.0, 250.0, 150);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(150.0, 250.0, -150);
    glVertex3f(200.0, 270.0, -200);
    glVertex3f(200.0, 270.0, 200);
    glVertex3f(150.0, 250.0, 150);
    glEnd();
}

void pintulantai1() {
    //pintu
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.3, 0.3);
    glVertex3f(-35.0, 40.0, 151.1);
    glVertex3f(-35.0, 180.0, 151.1);
    glVertex3f(35.0, 180.0, 151.1);
    glVertex3f(35.0, 40.0, 151.1);
    glEnd();
    //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-29.0, 170.0, 151.2);
    glVertex3f(-29.0, 175.0, 151.2);
    glVertex3f(-17.0, 175.0, 151.2);
    glVertex3f(-17.0, 170.0, 151.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-15.0, 170.0, 151.2);
    glVertex3f(-15.0, 175.0, 151.2);
    glVertex3f(-3.0, 175.0, 151.2);
    glVertex3f(-3.0, 170.0, 151.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(29.0, 170.0, 151.2);
    glVertex3f(29.0, 175.0, 151.2);
    glVertex3f(17.0, 175.0, 151.2);
    glVertex3f(17.0, 170.0, 151.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(15.0, 170.0, 151.2);
    glVertex3f(15.0, 175.0, 151.2);
    glVertex3f(3.0, 175.0, 151.2);
    glVertex3f(3.0, 170.0, 151.2);
    glEnd();
    // -- // -- //
   //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-29.0, 162.0, 151.2);
    glVertex3f(-29.0, 167.0, 151.2);
    glVertex3f(-17.0, 167.0, 151.2);
    glVertex3f(-17.0, 162.0, 151.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-15.0, 162.0, 151.2);
    glVertex3f(-15.0, 167.0, 151.2);
    glVertex3f(-3.0, 167.0, 151.2);
    glVertex3f(-3.0, 162.0, 151.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(29.0, 162.0, 151.2);
    glVertex3f(29.0, 167.0, 151.2);
    glVertex3f(17.0, 167.0, 151.2);
    glVertex3f(17.0, 162.0, 151.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(15.0, 162.0, 151.2);
    glVertex3f(15.0, 167.0, 151.2);
    glVertex3f(3.0, 167.0, 151.2);
    glVertex3f(3.0, 162.0, 151.2);
    glEnd();
    // -- // -- //
   //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-29.0, 154.0, 151.2);
    glVertex3f(-29.0, 159.0, 151.2);
    glVertex3f(-17.0, 159.0, 151.2);
    glVertex3f(-17.0, 154.0, 151.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-15.0, 154.0, 151.2);
    glVertex3f(-15.0, 159.0, 151.2);
    glVertex3f(-3.0, 159.0, 151.2);
    glVertex3f(-3.0, 154.0, 151.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(29.0, 154.0, 151.2);
    glVertex3f(29.0, 159.0, 151.2);
    glVertex3f(17.0, 159.0, 151.2);
    glVertex3f(17.0, 154.0, 151.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(15.0, 154.0, 151.2);
    glVertex3f(15.0, 159.0, 151.2);
    glVertex3f(3.0, 159.0, 151.2);
    glVertex3f(3.0, 154.0, 151.2);
    glEnd();
    // -- // -- //
  //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-29.0, 146.0, 151.2);
    glVertex3f(-29.0, 151.0, 151.2);
    glVertex3f(-17.0, 151.0, 151.2);
    glVertex3f(-17.0, 146.0, 151.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-15.0, 146.0, 151.2);
    glVertex3f(-15.0, 151.0, 151.2);
    glVertex3f(-3.0, 151.0, 151.2);
    glVertex3f(-3.0, 146.0, 151.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(29.0, 146.0, 151.2);
    glVertex3f(29.0, 151.0, 151.2);
    glVertex3f(17.0, 151.0, 151.2);
    glVertex3f(17.0, 146.0, 151.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(15.0, 146.0, 151.2);
    glVertex3f(15.0, 151.0, 151.2);
    glVertex3f(3.0, 151.0, 151.2);
    glVertex3f(3.0, 146.0, 151.2);
    glEnd();
    // -- // -- //
  //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-29.0, 138.0, 151.2);
    glVertex3f(-29.0, 143.0, 151.2);
    glVertex3f(-17.0, 143.0, 151.2);
    glVertex3f(-17.0, 138.0, 151.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-15.0, 138.0, 151.2);
    glVertex3f(-15.0, 143.0, 151.2);
    glVertex3f(-3.0, 143.0, 151.2);
    glVertex3f(-3.0, 138.0, 151.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(29.0, 138.0, 151.2);
    glVertex3f(29.0, 143.0, 151.2);
    glVertex3f(17.0, 143.0, 151.2);
    glVertex3f(17.0, 138.0, 151.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(15.0, 138.0, 151.2);
    glVertex3f(15.0, 143.0, 151.2);
    glVertex3f(3.0, 143.0, 151.2);
    glVertex3f(3.0, 138.0, 151.2);
    glEnd();
    // -- // -- //
  //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-29.0, 130.0, 151.2);
    glVertex3f(-29.0, 135.0, 151.2);
    glVertex3f(-17.0, 135.0, 151.2);
    glVertex3f(-17.0, 130.0, 151.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-15.0, 130.0, 151.2);
    glVertex3f(-15.0, 135.0, 151.2);
    glVertex3f(-3.0, 135.0, 151.2);
    glVertex3f(-3.0, 130.0, 151.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(29.0, 130.0, 151.2);
    glVertex3f(29.0, 135.0, 151.2);
    glVertex3f(17.0, 135.0, 151.2);
    glVertex3f(17.0, 130.0, 151.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(15.0, 130.0, 151.2);
    glVertex3f(15.0, 135.0, 151.2);
    glVertex3f(3.0, 135.0, 151.2);
    glVertex3f(3.0, 130.0, 151.2);
    glEnd();
    // -- // -- //
   //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-29.0, 122.0, 151.2);
    glVertex3f(-29.0, 127.0, 151.2);
    glVertex3f(-17.0, 127.0, 151.2);
    glVertex3f(-17.0, 122.0, 151.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-15.0, 122.0, 151.2);
    glVertex3f(-15.0, 127.0, 151.2);
    glVertex3f(-3.0, 127.0, 151.2);
    glVertex3f(-3.0, 122.0, 151.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(29.0, 122.0, 151.2);
    glVertex3f(29.0, 127.0, 151.2);
    glVertex3f(17.0, 127.0, 151.2);
    glVertex3f(17.0, 122.0, 151.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(15.0, 122.0, 151.2);
    glVertex3f(15.0, 127.0, 151.2);
    glVertex3f(3.0, 127.0, 151.2);
    glVertex3f(3.0, 122.0, 151.2);
    glEnd();
    // -- // -- //
   //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-29.0, 114.0, 151.2);
    glVertex3f(-29.0, 119.0, 151.2);
    glVertex3f(-17.0, 119.0, 151.2);
    glVertex3f(-17.0, 114.0, 151.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-15.0, 114.0, 151.2);
    glVertex3f(-15.0, 119.0, 151.2);
    glVertex3f(-3.0, 119.0, 151.2);
    glVertex3f(-3.0, 114.0, 151.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(29.0, 114.0, 151.2);
    glVertex3f(29.0, 119.0, 151.2);
    glVertex3f(17.0, 119.0, 151.2);
    glVertex3f(17.0, 114.0, 151.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(15.0, 114.0, 151.2);
    glVertex3f(15.0, 119.0, 151.2);
    glVertex3f(3.0, 119.0, 151.2);
    glVertex3f(3.0, 114.0, 151.2);
    glEnd();
    // -- // -- //
   //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-29.0, 106.0, 151.2);
    glVertex3f(-29.0, 111.0, 151.2);
    glVertex3f(-17.0, 111.0, 151.2);
    glVertex3f(-17.0, 106.0, 151.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-15.0, 106.0, 151.2);
    glVertex3f(-15.0, 111.0, 151.2);
    glVertex3f(-3.0, 111.0, 151.2);
    glVertex3f(-3.0, 106.0, 151.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(29.0, 106.0, 151.2);
    glVertex3f(29.0, 111.0, 151.2);
    glVertex3f(17.0, 111.0, 151.2);
    glVertex3f(17.0, 106.0, 151.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(15.0, 106.0, 151.2);
    glVertex3f(15.0, 111.0, 151.2);
    glVertex3f(3.0, 111.0, 151.2);
    glVertex3f(3.0, 106.0, 151.2);
    glEnd();

    // - - - - GARIS PINTU - - - - //
    //pintu
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-35.0, 40.0, 151.1);
    glVertex3f(-35.0, 180.0, 151.1);
    glVertex3f(35.0, 180.0, 151.1);
    glVertex3f(35.0, 40.0, 151.1);
    glEnd();
    //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-29.0, 170.0, 151.2);
    glVertex3f(-29.0, 175.0, 151.2);
    glVertex3f(-17.0, 175.0, 151.2);
    glVertex3f(-17.0, 170.0, 151.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-15.0, 170.0, 151.2);
    glVertex3f(-15.0, 175.0, 151.2);
    glVertex3f(-3.0, 175.0, 151.2);
    glVertex3f(-3.0, 170.0, 151.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(29.0, 170.0, 151.2);
    glVertex3f(29.0, 175.0, 151.2);
    glVertex3f(17.0, 175.0, 151.2);
    glVertex3f(17.0, 170.0, 151.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(15.0, 170.0, 151.2);
    glVertex3f(15.0, 175.0, 151.2);
    glVertex3f(3.0, 175.0, 151.2);
    glVertex3f(3.0, 170.0, 151.2);
    glEnd();
    // -- // -- //
   //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-29.0, 162.0, 151.2);
    glVertex3f(-29.0, 167.0, 151.2);
    glVertex3f(-17.0, 167.0, 151.2);
    glVertex3f(-17.0, 162.0, 151.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-15.0, 162.0, 151.2);
    glVertex3f(-15.0, 167.0, 151.2);
    glVertex3f(-3.0, 167.0, 151.2);
    glVertex3f(-3.0, 162.0, 151.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(29.0, 162.0, 151.2);
    glVertex3f(29.0, 167.0, 151.2);
    glVertex3f(17.0, 167.0, 151.2);
    glVertex3f(17.0, 162.0, 151.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(15.0, 162.0, 151.2);
    glVertex3f(15.0, 167.0, 151.2);
    glVertex3f(3.0, 167.0, 151.2);
    glVertex3f(3.0, 162.0, 151.2);
    glEnd();
    // -- // -- //
   //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-29.0, 154.0, 151.2);
    glVertex3f(-29.0, 159.0, 151.2);
    glVertex3f(-17.0, 159.0, 151.2);
    glVertex3f(-17.0, 154.0, 151.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-15.0, 154.0, 151.2);
    glVertex3f(-15.0, 159.0, 151.2);
    glVertex3f(-3.0, 159.0, 151.2);
    glVertex3f(-3.0, 154.0, 151.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(29.0, 154.0, 151.2);
    glVertex3f(29.0, 159.0, 151.2);
    glVertex3f(17.0, 159.0, 151.2);
    glVertex3f(17.0, 154.0, 151.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(15.0, 154.0, 151.2);
    glVertex3f(15.0, 159.0, 151.2);
    glVertex3f(3.0, 159.0, 151.2);
    glVertex3f(3.0, 154.0, 151.2);
    glEnd();
    // -- // -- //
  //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-29.0, 146.0, 151.2);
    glVertex3f(-29.0, 151.0, 151.2);
    glVertex3f(-17.0, 151.0, 151.2);
    glVertex3f(-17.0, 146.0, 151.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-15.0, 146.0, 151.2);
    glVertex3f(-15.0, 151.0, 151.2);
    glVertex3f(-3.0, 151.0, 151.2);
    glVertex3f(-3.0, 146.0, 151.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(29.0, 146.0, 151.2);
    glVertex3f(29.0, 151.0, 151.2);
    glVertex3f(17.0, 151.0, 151.2);
    glVertex3f(17.0, 146.0, 151.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(15.0, 146.0, 151.2);
    glVertex3f(15.0, 151.0, 151.2);
    glVertex3f(3.0, 151.0, 151.2);
    glVertex3f(3.0, 146.0, 151.2);
    glEnd();
    // -- // -- //
  //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-29.0, 138.0, 151.2);
    glVertex3f(-29.0, 143.0, 151.2);
    glVertex3f(-17.0, 143.0, 151.2);
    glVertex3f(-17.0, 138.0, 151.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-15.0, 138.0, 151.2);
    glVertex3f(-15.0, 143.0, 151.2);
    glVertex3f(-3.0, 143.0, 151.2);
    glVertex3f(-3.0, 138.0, 151.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(29.0, 138.0, 151.2);
    glVertex3f(29.0, 143.0, 151.2);
    glVertex3f(17.0, 143.0, 151.2);
    glVertex3f(17.0, 138.0, 151.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(15.0, 138.0, 151.2);
    glVertex3f(15.0, 143.0, 151.2);
    glVertex3f(3.0, 143.0, 151.2);
    glVertex3f(3.0, 138.0, 151.2);
    glEnd();
    // -- // -- //
  //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-29.0, 130.0, 151.2);
    glVertex3f(-29.0, 135.0, 151.2);
    glVertex3f(-17.0, 135.0, 151.2);
    glVertex3f(-17.0, 130.0, 151.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-15.0, 130.0, 151.2);
    glVertex3f(-15.0, 135.0, 151.2);
    glVertex3f(-3.0, 135.0, 151.2);
    glVertex3f(-3.0, 130.0, 151.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(29.0, 130.0, 151.2);
    glVertex3f(29.0, 135.0, 151.2);
    glVertex3f(17.0, 135.0, 151.2);
    glVertex3f(17.0, 130.0, 151.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(15.0, 130.0, 151.2);
    glVertex3f(15.0, 135.0, 151.2);
    glVertex3f(3.0, 135.0, 151.2);
    glVertex3f(3.0, 130.0, 151.2);
    glEnd();
    // -- // -- //
   //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-29.0, 122.0, 151.2);
    glVertex3f(-29.0, 127.0, 151.2);
    glVertex3f(-17.0, 127.0, 151.2);
    glVertex3f(-17.0, 122.0, 151.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-15.0, 122.0, 151.2);
    glVertex3f(-15.0, 127.0, 151.2);
    glVertex3f(-3.0, 127.0, 151.2);
    glVertex3f(-3.0, 122.0, 151.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(29.0, 122.0, 151.2);
    glVertex3f(29.0, 127.0, 151.2);
    glVertex3f(17.0, 127.0, 151.2);
    glVertex3f(17.0, 122.0, 151.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(15.0, 122.0, 151.2);
    glVertex3f(15.0, 127.0, 151.2);
    glVertex3f(3.0, 127.0, 151.2);
    glVertex3f(3.0, 122.0, 151.2);
    glEnd();
    // -- // -- //
   //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-29.0, 114.0, 151.2);
    glVertex3f(-29.0, 119.0, 151.2);
    glVertex3f(-17.0, 119.0, 151.2);
    glVertex3f(-17.0, 114.0, 151.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-15.0, 114.0, 151.2);
    glVertex3f(-15.0, 119.0, 151.2);
    glVertex3f(-3.0, 119.0, 151.2);
    glVertex3f(-3.0, 114.0, 151.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(29.0, 114.0, 151.2);
    glVertex3f(29.0, 119.0, 151.2);
    glVertex3f(17.0, 119.0, 151.2);
    glVertex3f(17.0, 114.0, 151.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(15.0, 114.0, 151.2);
    glVertex3f(15.0, 119.0, 151.2);
    glVertex3f(3.0, 119.0, 151.2);
    glVertex3f(3.0, 114.0, 151.2);
    glEnd();
    // -- // -- //
   //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-29.0, 106.0, 151.2);
    glVertex3f(-29.0, 111.0, 151.2);
    glVertex3f(-17.0, 111.0, 151.2);
    glVertex3f(-17.0, 106.0, 151.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-15.0, 106.0, 151.2);
    glVertex3f(-15.0, 111.0, 151.2);
    glVertex3f(-3.0, 111.0, 151.2);
    glVertex3f(-3.0, 106.0, 151.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(29.0, 106.0, 151.2);
    glVertex3f(29.0, 111.0, 151.2);
    glVertex3f(17.0, 111.0, 151.2);
    glVertex3f(17.0, 106.0, 151.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(15.0, 106.0, 151.2);
    glVertex3f(15.0, 111.0, 151.2);
    glVertex3f(3.0, 111.0, 151.2);
    glVertex3f(3.0, 106.0, 151.2);
    glEnd();
}

void lantai2() {
    //LANTAI 2 
    glBegin(GL_POLYGON);
    glColor3f(0.51, 0.46, 0.46);
    glVertex3f(-200.0, 270.0, -200);
    glVertex3f(-200.0, 270.0, 200);
    glVertex3f(200.0, 270.0, 200);
    glVertex3f(200.0, 270.0, -200);
    glEnd();
    //LANTAI2 END

    //dinding lantai 2
    glBegin(GL_POLYGON);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(-120.0, 270.0, 120);
    glVertex3f(-120.0, 500.0, 120);
    glVertex3f(120.0, 500.0, 120);
    glVertex3f(120.0, 270.0, 120);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(-120.0, 270.0, -120);
    glVertex3f(-120.0, 500.0, -120);
    glVertex3f(120.0, 500.0, -120);
    glVertex3f(120.0, 270.0, -120);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(-120.0, 270.0, -120);
    glVertex3f(-120.0, 500.0, -120);
    glVertex3f(-120.0, 500.0, 120);
    glVertex3f(-120.0, 270.0, 120);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(120.0, 270.0, -120);
    glVertex3f(120.0, 500.0, -120);
    glVertex3f(120.0, 500.0, 120);
    glVertex3f(120.0, 270.0, 120);
    glEnd();
    //end dinding lantai 2

    // - - - - - GARIS DINDING - - - - - //
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-120.0, 270.0, 120);
    glVertex3f(-120.0, 500.0, 120);
    glVertex3f(120.0, 500.0, 120);
    glVertex3f(120.0, 270.0, 120);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-120.0, 270.0, -120);
    glVertex3f(-120.0, 500.0, -120);
    glVertex3f(120.0, 500.0, -120);
    glVertex3f(120.0, 270.0, -120);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-120.0, 270.0, -120);
    glVertex3f(-120.0, 500.0, -120);
    glVertex3f(-120.0, 500.0, 120);
    glVertex3f(-120.0, 270.0, 120);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(120.0, 270.0, -120);
    glVertex3f(120.0, 500.0, -120);
    glVertex3f(120.0, 500.0, 120);
    glVertex3f(120.0, 270.0, 120);
    glEnd();

    //penutup lantai 2
    //1
    glBegin(GL_POLYGON);
    glColor3f(0.87, 0.16, 0.16);
    glVertex3f(-130.0, 500.0, -130);
    glVertex3f(-130.0, 500.0, 130);
    glVertex3f(130.0, 500.0, 130);
    glVertex3f(130.0, 500.0, -130);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-130.0, 500.0, 130);
    glVertex3f(-130.0, 505.0, 130);
    glVertex3f(130.0, 505.0, 130);
    glVertex3f(130.0, 500.0, 130);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-130.0, 500.0, -130);
    glVertex3f(-130.0, 505.0, -130);
    glVertex3f(130.0, 505.0, -130);
    glVertex3f(130.0, 500.0, -130);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-130.0, 500.0, -130);
    glVertex3f(-130.0, 505.0, -130);
    glVertex3f(-130.0, 505.0, 130);
    glVertex3f(-130.0, 500.0, 130);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(130.0, 500.0, -130);
    glVertex3f(130.0, 505.0, -130);
    glVertex3f(130.0, 505.0, 130);
    glVertex3f(130.0, 500.0, 130);
    glEnd();
    //2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.93, 0.66);
    glVertex3f(-135.0, 505.0, -135);
    glVertex3f(-135.0, 505.0, 135);
    glVertex3f(135.0, 505.0, 135);
    glVertex3f(135, 505.0, -135);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-135.0, 505.0, 135);
    glVertex3f(-135.0, 515.0, 135);
    glVertex3f(135.0, 515.0, 135);
    glVertex3f(135.0, 505.0, 135);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-135.0, 505.0, -135);
    glVertex3f(-135.0, 515.0, -135);
    glVertex3f(135.0, 515.0, -135);
    glVertex3f(135.0, 505.0, -135);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-135.0, 505.0, -135);
    glVertex3f(-135.0, 515.0, -135);
    glVertex3f(-135.0, 515.0, 135);
    glVertex3f(-135.0, 505.0, 135);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(135.0, 505.0, -135);
    glVertex3f(135.0, 515.0, -135);
    glVertex3f(135.0, 515.0, 135);
    glVertex3f(135.0, 505.0, 135);
    glEnd();
    //akhir penutup lantai 2

    //atap
    //bawah
    glBegin(GL_POLYGON);
    glColor3f(0.45, 0.45, 0.45);
    glVertex3f(-135.0, 515.0, 135);
    glVertex3f(-205.0, 520.0, 205);
    glVertex3f(205.0, 520.0, 205);
    glVertex3f(135.0, 515.0, 135);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.45, 0.45, 0.45);
    glVertex3f(-135.0, 515.0, -135);
    glVertex3f(-205.0, 520.0, -205);
    glVertex3f(205.0, 520.0, -205);
    glVertex3f(135.0, 515.0, -135);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.45, 0.45, 0.45);
    glVertex3f(-135.0, 515.0, -135);
    glVertex3f(-205.0, 520.0, -205);
    glVertex3f(-205.0, 520.0, 205);
    glVertex3f(-135.0, 515.0, 135);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.45, 0.45, 0.45);
    glVertex3f(135.0, 515.0, -135);
    glVertex3f(205.0, 520.0, -205);
    glVertex3f(205.0, 520.0, 205);
    glVertex3f(135.0, 515.0, 135);
    glEnd();

    //garis bawah
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-135.0, 515.0, 135);
    glVertex3f(-205.0, 520.0, 205);
    glVertex3f(205.0, 520.0, 205);
    glVertex3f(135.0, 515.0, 135);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-135.0, 515.0, -135);
    glVertex3f(-205.0, 520.0, -205);
    glVertex3f(205.0, 520.0, -205);
    glVertex3f(135.0, 515.0, -135);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-135.0, 515.0, -135);
    glVertex3f(-205.0, 520.0, -205);
    glVertex3f(-205.0, 520.0, 205);
    glVertex3f(-135.0, 515.0, 135);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(135.0, 515.0, -135);
    glVertex3f(205.0, 520.0, -205);
    glVertex3f(205.0, 520.0, 205);
    glVertex3f(135.0, 515.0, 135);
    glEnd();

    //tengah
    glBegin(GL_POLYGON);
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(-125.0, 540.0, 125);
    glVertex3f(-205.0, 520.0, 205);
    glVertex3f(205.0, 520.0, 205);
    glVertex3f(125.0, 540.0, 125);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(-125.0, 540.0, -125);
    glVertex3f(-205.0, 520.0, -205);
    glVertex3f(205.0, 520.0, -205);
    glVertex3f(125.0, 540.0, -125);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(-125.0, 540.0, -125);
    glVertex3f(-205.0, 520.0, -205);
    glVertex3f(-205.0, 520.0, 205);
    glVertex3f(-125.0, 540.0, 125);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(125.0, 540.0, -125);
    glVertex3f(205.0, 520.0, -205);
    glVertex3f(205.0, 520.0, 205);
    glVertex3f(125.0, 540.0, 125);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-125.0, 540.0, 125);
    glVertex3f(-205.0, 520.0, 205);
    glVertex3f(205.0, 520.0, 205);
    glVertex3f(125.0, 540.0, 125);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-125.0, 540.0, -125);
    glVertex3f(-205.0, 520.0, -205);
    glVertex3f(205.0, 520.0, -205);
    glVertex3f(125.0, 540.0, -125);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-125.0, 540.0, -125);
    glVertex3f(-205.0, 520.0, -205);
    glVertex3f(-205.0, 520.0, 205);
    glVertex3f(-125.0, 540.0, 125);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(125.0, 540.0, -125);
    glVertex3f(205.0, 520.0, -205);
    glVertex3f(205.0, 520.0, 205);
    glVertex3f(125.0, 540.0, 125);
    glEnd();
    //atas
    glBegin(GL_POLYGON);
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(-95.0, 560.0, 95);
    glVertex3f(-125.0, 540.0, 125);
    glVertex3f(125.0, 540.0, 125);
    glVertex3f(95.0, 560.0, 95);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(-95.0, 560.0, -95);
    glVertex3f(-125.0, 540.0, -125);
    glVertex3f(125.0, 540.0, -125);
    glVertex3f(95.0, 560.0, -95);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(-95.0, 560.0, -95);
    glVertex3f(-125.0, 540.0, -125);
    glVertex3f(-125.0, 540.0, 125);
    glVertex3f(-95.0, 560.0, 95);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(95.0, 560.0, -95);
    glVertex3f(125.0, 540.0, -125);
    glVertex3f(125.0, 540.0, 125);
    glVertex3f(95.0, 560.0, 95);
    glEnd();
    //GARIS DIATAS

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-95.0, 560.0, 95);
    glVertex3f(-125.0, 540.0, 125);
    glVertex3f(125.0, 540.0, 125);
    glVertex3f(95.0, 560.0, 95);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-95.0, 560.0, -95);
    glVertex3f(-125.0, 540.0, -125);
    glVertex3f(125.0, 540.0, -125);
    glVertex3f(95.0, 560.0, -95);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-95.0, 560.0, -95);
    glVertex3f(-125.0, 540.0, -125);
    glVertex3f(-125.0, 540.0, 125);
    glVertex3f(-95.0, 560.0, 95);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(95.0, 560.0, -95);
    glVertex3f(125.0, 540.0, -125);
    glVertex3f(125.0, 540.0, 125);
    glVertex3f(95.0, 560.0, 95);
    glEnd();
    //end atap lantai 2
}

void pintulantai2() {
    //pintu
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.3, 0.3);
    glVertex3f(-35.0, 270.0, 120.1);
    glVertex3f(-35.0, 400.0, 120.1);
    glVertex3f(35.0, 400.0, 120.1);
    glVertex3f(35.0, 270.0, 120.1);
    glEnd();
    //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-29.0, 390.0, 120.2);
    glVertex3f(-29.0, 395.0, 120.2);
    glVertex3f(-17.0, 395.0, 120.2);
    glVertex3f(-17.0, 390.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-15.0, 390.0, 120.2);
    glVertex3f(-15.0, 395.0, 120.2);
    glVertex3f(-3.0, 395.0, 120.2);
    glVertex3f(-3.0, 390.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(29.0, 390.0, 120.2);
    glVertex3f(29.0, 395.0, 120.2);
    glVertex3f(17.0, 395.0, 120.2);
    glVertex3f(17.0, 390.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(15.0, 390.0, 120.2);
    glVertex3f(15.0, 395.0, 120.2);
    glVertex3f(3.0, 395.0, 120.2);
    glVertex3f(3.0, 390.0, 120.2);
    glEnd();
    // // // //
    //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-29.0, 382.0, 120.2);
    glVertex3f(-29.0, 387.0, 120.2);
    glVertex3f(-17.0, 387.0, 120.2);
    glVertex3f(-17.0, 382.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-15.0, 382.0, 120.2);
    glVertex3f(-15.0, 387.0, 120.2);
    glVertex3f(-3.0, 387.0, 120.2);
    glVertex3f(-3.0, 382.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(29.0, 382.0, 120.2);
    glVertex3f(29.0, 387.0, 120.2);
    glVertex3f(17.0, 387.0, 120.2);
    glVertex3f(17.0, 382.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(15.0, 382.0, 120.2);
    glVertex3f(15.0, 387.0, 120.2);
    glVertex3f(3.0, 387.0, 120.2);
    glVertex3f(3.0, 382.0, 120.2);
    glEnd();
    // // // //
    //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-29.0, 374.0, 120.2);
    glVertex3f(-29.0, 379.0, 120.2);
    glVertex3f(-17.0, 379.0, 120.2);
    glVertex3f(-17.0, 374.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-15.0, 374.0, 120.2);
    glVertex3f(-15.0, 379.0, 120.2);
    glVertex3f(-3.0, 379.0, 120.2);
    glVertex3f(-3.0, 374.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(29.0, 374.0, 120.2);
    glVertex3f(29.0, 379.0, 120.2);
    glVertex3f(17.0, 379.0, 120.2);
    glVertex3f(17.0, 374.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(15.0, 374.0, 120.2);
    glVertex3f(15.0, 379.0, 120.2);
    glVertex3f(3.0, 379.0, 120.2);
    glVertex3f(3.0, 374.0, 120.2);
    glEnd();
    // // // //
     //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-29.0, 366.0, 120.2);
    glVertex3f(-29.0, 371.0, 120.2);
    glVertex3f(-17.0, 371.0, 120.2);
    glVertex3f(-17.0, 366.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-15.0, 366.0, 120.2);
    glVertex3f(-15.0, 371.0, 120.2);
    glVertex3f(-3.0, 371.0, 120.2);
    glVertex3f(-3.0, 366.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(29.0, 366.0, 120.2);
    glVertex3f(29.0, 371.0, 120.2);
    glVertex3f(17.0, 371.0, 120.2);
    glVertex3f(17.0, 366.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(15.0, 366.0, 120.2);
    glVertex3f(15.0, 371.0, 120.2);
    glVertex3f(3.0, 371.0, 120.2);
    glVertex3f(3.0, 366.0, 120.2);
    glEnd();
    // // // //
     //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-29.0, 358.0, 120.2);
    glVertex3f(-29.0, 363.0, 120.2);
    glVertex3f(-17.0, 363.0, 120.2);
    glVertex3f(-17.0, 358.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-15.0, 358.0, 120.2);
    glVertex3f(-15.0, 363.0, 120.2);
    glVertex3f(-3.0, 363.0, 120.2);
    glVertex3f(-3.0, 358.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(29.0, 358.0, 120.2);
    glVertex3f(29.0, 363.0, 120.2);
    glVertex3f(17.0, 363.0, 120.2);
    glVertex3f(17.0, 358.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(15.0, 358.0, 120.2);
    glVertex3f(15.0, 363.0, 120.2);
    glVertex3f(3.0, 363.0, 120.2);
    glVertex3f(3.0, 358.0, 120.2);
    glEnd();
    // // // //
     //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-29.0, 350.0, 120.2);
    glVertex3f(-29.0, 355.0, 120.2);
    glVertex3f(-17.0, 355.0, 120.2);
    glVertex3f(-17.0, 350.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-15.0, 350.0, 120.2);
    glVertex3f(-15.0, 355.0, 120.2);
    glVertex3f(-3.0, 355.0, 120.2);
    glVertex3f(-3.0, 350.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(29.0, 350.0, 120.2);
    glVertex3f(29.0, 355.0, 120.2);
    glVertex3f(17.0, 355.0, 120.2);
    glVertex3f(17.0, 350.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(15.0, 350.0, 120.2);
    glVertex3f(15.0, 355.0, 120.2);
    glVertex3f(3.0, 355.0, 120.2);
    glVertex3f(3.0, 350.0, 120.2);
    glEnd();
    // // // //
     //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-29.0, 342.0, 120.2);
    glVertex3f(-29.0, 347.0, 120.2);
    glVertex3f(-17.0, 347.0, 120.2);
    glVertex3f(-17.0, 342.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-15.0, 342.0, 120.2);
    glVertex3f(-15.0, 347.0, 120.2);
    glVertex3f(-3.0, 347.0, 120.2);
    glVertex3f(-3.0, 342.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(29.0, 342.0, 120.2);
    glVertex3f(29.0, 347.0, 120.2);
    glVertex3f(17.0, 347.0, 120.2);
    glVertex3f(17.0, 342.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(15.0, 342.0, 120.2);
    glVertex3f(15.0, 347.0, 120.2);
    glVertex3f(3.0, 347.0, 120.2);
    glVertex3f(3.0, 342.0, 120.2);
    glEnd();
    // // // //
     //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-29.0, 334.0, 120.2);
    glVertex3f(-29.0, 339.0, 120.2);
    glVertex3f(-17.0, 339.0, 120.2);
    glVertex3f(-17.0, 334.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-15.0, 334.0, 120.2);
    glVertex3f(-15.0, 339.0, 120.2);
    glVertex3f(-3.0, 339.0, 120.2);
    glVertex3f(-3.0, 334.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(29.0, 334.0, 120.2);
    glVertex3f(29.0, 339.0, 120.2);
    glVertex3f(17.0, 339.0, 120.2);
    glVertex3f(17.0, 334.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(15.0, 334.0, 120.2);
    glVertex3f(15.0, 339.0, 120.2);
    glVertex3f(3.0, 339.0, 120.2);
    glVertex3f(3.0, 334.0, 120.2);
    glEnd();
    // // // //
     //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-29.0, 326.0, 120.2);
    glVertex3f(-29.0, 331.0, 120.2);
    glVertex3f(-17.0, 331.0, 120.2);
    glVertex3f(-17.0, 326.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-15.0, 326.0, 120.2);
    glVertex3f(-15.0, 331.0, 120.2);
    glVertex3f(-3.0, 331.0, 120.2);
    glVertex3f(-3.0, 326.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(29.0, 326.0, 120.2);
    glVertex3f(29.0, 331.0, 120.2);
    glVertex3f(17.0, 331.0, 120.2);
    glVertex3f(17.0, 326.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(15.0, 326.0, 120.2);
    glVertex3f(15.0, 331.0, 120.2);
    glVertex3f(3.0, 331.0, 120.2);
    glVertex3f(3.0, 326.0, 120.2);
    glEnd();
    // // // //
     //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-29.0, 318.0, 120.2);
    glVertex3f(-29.0, 323.0, 120.2);
    glVertex3f(-17.0, 323.0, 120.2);
    glVertex3f(-17.0, 318.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-15.0, 318.0, 120.2);
    glVertex3f(-15.0, 323.0, 120.2);
    glVertex3f(-3.0, 323.0, 120.2);
    glVertex3f(-3.0, 318.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(29.0, 318.0, 120.2);
    glVertex3f(29.0, 323.0, 120.2);
    glVertex3f(17.0, 323.0, 120.2);
    glVertex3f(17.0, 318.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(15.0, 318.0, 120.2);
    glVertex3f(15.0, 323.0, 120.2);
    glVertex3f(3.0, 323.0, 120.2);
    glVertex3f(3.0, 318.0, 120.2);
    glEnd();
    // // // //
      //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-29.0, 310.0, 120.2);
    glVertex3f(-29.0, 315.0, 120.2);
    glVertex3f(-17.0, 315.0, 120.2);
    glVertex3f(-17.0, 310.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-15.0, 310.0, 120.2);
    glVertex3f(-15.0, 315.0, 120.2);
    glVertex3f(-3.0, 315.0, 120.2);
    glVertex3f(-3.0, 310.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(29.0, 310.0, 120.2);
    glVertex3f(29.0, 315.0, 120.2);
    glVertex3f(17.0, 315.0, 120.2);
    glVertex3f(17.0, 310.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(15.0, 310.0, 120.2);
    glVertex3f(15.0, 315.0, 120.2);
    glVertex3f(3.0, 315.0, 120.2);
    glVertex3f(3.0, 310.0, 120.2);
    glEnd();
    // // // //
      //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-29.0, 302.0, 120.2);
    glVertex3f(-29.0, 307.0, 120.2);
    glVertex3f(-17.0, 307.0, 120.2);
    glVertex3f(-17.0, 302.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-15.0, 302.0, 120.2);
    glVertex3f(-15.0, 307.0, 120.2);
    glVertex3f(-3.0, 307.0, 120.2);
    glVertex3f(-3.0, 302.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(29.0, 302.0, 120.2);
    glVertex3f(29.0, 307.0, 120.2);
    glVertex3f(17.0, 307.0, 120.2);
    glVertex3f(17.0, 302.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(15.0, 302.0, 120.2);
    glVertex3f(15.0, 307.0, 120.2);
    glVertex3f(3.0, 307.0, 120.2);
    glVertex3f(3.0, 302.0, 120.2);
    glEnd();
    // // // //
      //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-29.0, 294.0, 120.2);
    glVertex3f(-29.0, 299.0, 120.2);
    glVertex3f(-17.0, 299.0, 120.2);
    glVertex3f(-17.0, 294.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-15.0, 294.0, 120.2);
    glVertex3f(-15.0, 299.0, 120.2);
    glVertex3f(-3.0, 299.0, 120.2);
    glVertex3f(-3.0, 294.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(29.0, 294.0, 120.2);
    glVertex3f(29.0, 299.0, 120.2);
    glVertex3f(17.0, 299.0, 120.2);
    glVertex3f(17.0, 294.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(15.0, 294.0, 120.2);
    glVertex3f(15.0, 299.0, 120.2);
    glVertex3f(3.0, 299.0, 120.2);
    glVertex3f(3.0, 294.0, 120.2);
    glEnd();

    // - - - - - GARIS PINTU - - - - - //
    //pintu
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-35.0, 270.0, 120.1);
    glVertex3f(-35.0, 400.0, 120.1);
    glVertex3f(35.0, 400.0, 120.1);
    glVertex3f(35.0, 270.0, 120.1);
    glEnd();
    //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-29.0, 390.0, 120.2);
    glVertex3f(-29.0, 395.0, 120.2);
    glVertex3f(-17.0, 395.0, 120.2);
    glVertex3f(-17.0, 390.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-15.0, 390.0, 120.2);
    glVertex3f(-15.0, 395.0, 120.2);
    glVertex3f(-3.0, 395.0, 120.2);
    glVertex3f(-3.0, 390.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(29.0, 390.0, 120.2);
    glVertex3f(29.0, 395.0, 120.2);
    glVertex3f(17.0, 395.0, 120.2);
    glVertex3f(17.0, 390.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(15.0, 390.0, 120.2);
    glVertex3f(15.0, 395.0, 120.2);
    glVertex3f(3.0, 395.0, 120.2);
    glVertex3f(3.0, 390.0, 120.2);
    glEnd();
    // // // //
    //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-29.0, 382.0, 120.2);
    glVertex3f(-29.0, 387.0, 120.2);
    glVertex3f(-17.0, 387.0, 120.2);
    glVertex3f(-17.0, 382.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-15.0, 382.0, 120.2);
    glVertex3f(-15.0, 387.0, 120.2);
    glVertex3f(-3.0, 387.0, 120.2);
    glVertex3f(-3.0, 382.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(29.0, 382.0, 120.2);
    glVertex3f(29.0, 387.0, 120.2);
    glVertex3f(17.0, 387.0, 120.2);
    glVertex3f(17.0, 382.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(15.0, 382.0, 120.2);
    glVertex3f(15.0, 387.0, 120.2);
    glVertex3f(3.0, 387.0, 120.2);
    glVertex3f(3.0, 382.0, 120.2);
    glEnd();
    // // // //
    //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-29.0, 374.0, 120.2);
    glVertex3f(-29.0, 379.0, 120.2);
    glVertex3f(-17.0, 379.0, 120.2);
    glVertex3f(-17.0, 374.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-15.0, 374.0, 120.2);
    glVertex3f(-15.0, 379.0, 120.2);
    glVertex3f(-3.0, 379.0, 120.2);
    glVertex3f(-3.0, 374.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(29.0, 374.0, 120.2);
    glVertex3f(29.0, 379.0, 120.2);
    glVertex3f(17.0, 379.0, 120.2);
    glVertex3f(17.0, 374.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(15.0, 374.0, 120.2);
    glVertex3f(15.0, 379.0, 120.2);
    glVertex3f(3.0, 379.0, 120.2);
    glVertex3f(3.0, 374.0, 120.2);
    glEnd();
    // // // //
     //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-29.0, 366.0, 120.2);
    glVertex3f(-29.0, 371.0, 120.2);
    glVertex3f(-17.0, 371.0, 120.2);
    glVertex3f(-17.0, 366.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-15.0, 366.0, 120.2);
    glVertex3f(-15.0, 371.0, 120.2);
    glVertex3f(-3.0, 371.0, 120.2);
    glVertex3f(-3.0, 366.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(29.0, 366.0, 120.2);
    glVertex3f(29.0, 371.0, 120.2);
    glVertex3f(17.0, 371.0, 120.2);
    glVertex3f(17.0, 366.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(15.0, 366.0, 120.2);
    glVertex3f(15.0, 371.0, 120.2);
    glVertex3f(3.0, 371.0, 120.2);
    glVertex3f(3.0, 366.0, 120.2);
    glEnd();
    // // // //
     //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-29.0, 358.0, 120.2);
    glVertex3f(-29.0, 363.0, 120.2);
    glVertex3f(-17.0, 363.0, 120.2);
    glVertex3f(-17.0, 358.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-15.0, 358.0, 120.2);
    glVertex3f(-15.0, 363.0, 120.2);
    glVertex3f(-3.0, 363.0, 120.2);
    glVertex3f(-3.0, 358.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(29.0, 358.0, 120.2);
    glVertex3f(29.0, 363.0, 120.2);
    glVertex3f(17.0, 363.0, 120.2);
    glVertex3f(17.0, 358.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(15.0, 358.0, 120.2);
    glVertex3f(15.0, 363.0, 120.2);
    glVertex3f(3.0, 363.0, 120.2);
    glVertex3f(3.0, 358.0, 120.2);
    glEnd();
    // // // //
     //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-29.0, 350.0, 120.2);
    glVertex3f(-29.0, 355.0, 120.2);
    glVertex3f(-17.0, 355.0, 120.2);
    glVertex3f(-17.0, 350.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-15.0, 350.0, 120.2);
    glVertex3f(-15.0, 355.0, 120.2);
    glVertex3f(-3.0, 355.0, 120.2);
    glVertex3f(-3.0, 350.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(29.0, 350.0, 120.2);
    glVertex3f(29.0, 355.0, 120.2);
    glVertex3f(17.0, 355.0, 120.2);
    glVertex3f(17.0, 350.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(15.0, 350.0, 120.2);
    glVertex3f(15.0, 355.0, 120.2);
    glVertex3f(3.0, 355.0, 120.2);
    glVertex3f(3.0, 350.0, 120.2);
    glEnd();
    // // // //
     //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-29.0, 342.0, 120.2);
    glVertex3f(-29.0, 347.0, 120.2);
    glVertex3f(-17.0, 347.0, 120.2);
    glVertex3f(-17.0, 342.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-15.0, 342.0, 120.2);
    glVertex3f(-15.0, 347.0, 120.2);
    glVertex3f(-3.0, 347.0, 120.2);
    glVertex3f(-3.0, 342.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(29.0, 342.0, 120.2);
    glVertex3f(29.0, 347.0, 120.2);
    glVertex3f(17.0, 347.0, 120.2);
    glVertex3f(17.0, 342.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(15.0, 342.0, 120.2);
    glVertex3f(15.0, 347.0, 120.2);
    glVertex3f(3.0, 347.0, 120.2);
    glVertex3f(3.0, 342.0, 120.2);
    glEnd();
    // // // //
     //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-29.0, 334.0, 120.2);
    glVertex3f(-29.0, 339.0, 120.2);
    glVertex3f(-17.0, 339.0, 120.2);
    glVertex3f(-17.0, 334.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-15.0, 334.0, 120.2);
    glVertex3f(-15.0, 339.0, 120.2);
    glVertex3f(-3.0, 339.0, 120.2);
    glVertex3f(-3.0, 334.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(29.0, 334.0, 120.2);
    glVertex3f(29.0, 339.0, 120.2);
    glVertex3f(17.0, 339.0, 120.2);
    glVertex3f(17.0, 334.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(15.0, 334.0, 120.2);
    glVertex3f(15.0, 339.0, 120.2);
    glVertex3f(3.0, 339.0, 120.2);
    glVertex3f(3.0, 334.0, 120.2);
    glEnd();
    // // // //
     //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-29.0, 326.0, 120.2);
    glVertex3f(-29.0, 331.0, 120.2);
    glVertex3f(-17.0, 331.0, 120.2);
    glVertex3f(-17.0, 326.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-15.0, 326.0, 120.2);
    glVertex3f(-15.0, 331.0, 120.2);
    glVertex3f(-3.0, 331.0, 120.2);
    glVertex3f(-3.0, 326.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(29.0, 326.0, 120.2);
    glVertex3f(29.0, 331.0, 120.2);
    glVertex3f(17.0, 331.0, 120.2);
    glVertex3f(17.0, 326.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(15.0, 326.0, 120.2);
    glVertex3f(15.0, 331.0, 120.2);
    glVertex3f(3.0, 331.0, 120.2);
    glVertex3f(3.0, 326.0, 120.2);
    glEnd();
    // // // //
     //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-29.0, 318.0, 120.2);
    glVertex3f(-29.0, 323.0, 120.2);
    glVertex3f(-17.0, 323.0, 120.2);
    glVertex3f(-17.0, 318.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-15.0, 318.0, 120.2);
    glVertex3f(-15.0, 323.0, 120.2);
    glVertex3f(-3.0, 323.0, 120.2);
    glVertex3f(-3.0, 318.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(29.0, 318.0, 120.2);
    glVertex3f(29.0, 323.0, 120.2);
    glVertex3f(17.0, 323.0, 120.2);
    glVertex3f(17.0, 318.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(15.0, 318.0, 120.2);
    glVertex3f(15.0, 323.0, 120.2);
    glVertex3f(3.0, 323.0, 120.2);
    glVertex3f(3.0, 318.0, 120.2);
    glEnd();
    // // // //
      //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-29.0, 310.0, 120.2);
    glVertex3f(-29.0, 315.0, 120.2);
    glVertex3f(-17.0, 315.0, 120.2);
    glVertex3f(-17.0, 310.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-15.0, 310.0, 120.2);
    glVertex3f(-15.0, 315.0, 120.2);
    glVertex3f(-3.0, 315.0, 120.2);
    glVertex3f(-3.0, 310.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(29.0, 310.0, 120.2);
    glVertex3f(29.0, 315.0, 120.2);
    glVertex3f(17.0, 315.0, 120.2);
    glVertex3f(17.0, 310.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(15.0, 310.0, 120.2);
    glVertex3f(15.0, 315.0, 120.2);
    glVertex3f(3.0, 315.0, 120.2);
    glVertex3f(3.0, 310.0, 120.2);
    glEnd();
    // // // //
      //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-29.0, 302.0, 120.2);
    glVertex3f(-29.0, 307.0, 120.2);
    glVertex3f(-17.0, 307.0, 120.2);
    glVertex3f(-17.0, 302.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-15.0, 302.0, 120.2);
    glVertex3f(-15.0, 307.0, 120.2);
    glVertex3f(-3.0, 307.0, 120.2);
    glVertex3f(-3.0, 302.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(29.0, 302.0, 120.2);
    glVertex3f(29.0, 307.0, 120.2);
    glVertex3f(17.0, 307.0, 120.2);
    glVertex3f(17.0, 302.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(15.0, 302.0, 120.2);
    glVertex3f(15.0, 307.0, 120.2);
    glVertex3f(3.0, 307.0, 120.2);
    glVertex3f(3.0, 302.0, 120.2);
    glEnd();
    // // // //
    // 
      //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-29.0, 294.0, 120.2);
    glVertex3f(-29.0, 299.0, 120.2);
    glVertex3f(-17.0, 299.0, 120.2);
    glVertex3f(-17.0, 294.0, 120.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-15.0, 294.0, 120.2);
    glVertex3f(-15.0, 299.0, 120.2);
    glVertex3f(-3.0, 299.0, 120.2);
    glVertex3f(-3.0, 294.0, 120.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(29.0, 294.0, 120.2);
    glVertex3f(29.0, 299.0, 120.2);
    glVertex3f(17.0, 299.0, 120.2);
    glVertex3f(17.0, 294.0, 120.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(15.0, 294.0, 120.2);
    glVertex3f(15.0, 299.0, 120.2);
    glVertex3f(3.0, 299.0, 120.2);
    glVertex3f(3.0, 294.0, 120.2);
    glEnd();
}

void lantai3()
{
    //SEBELUM LANTAI3
    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-95.0, 560.0, 95);
    glVertex3f(-170.0, 580.0, 170);
    glVertex3f(170.0, 580.0, 170);
    glVertex3f(95.0, 560.0, 95);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-95.0, 560.0, -95);
    glVertex3f(-170.0, 580.0, -170);
    glVertex3f(170.0, 580.0, -170);
    glVertex3f(95.0, 560.0, -95);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-95.0, 560.0, -95);
    glVertex3f(-170.0, 580.0, -170);
    glVertex3f(-170.0, 580.0, 170);
    glVertex3f(-95.0, 560.0, 95);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(95.0, 560.0, -95);
    glVertex3f(170.0, 580.0, -170);
    glVertex3f(170.0, 580.0, 170);
    glVertex3f(95.0, 560.0, 95);
    glEnd();
    //END SEBELUM LANTAI 3

    //Garis SEBELUM LANTAI3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-95.0, 560.0, 95);
    glVertex3f(-170.0, 580.0, 170);
    glVertex3f(170.0, 580.0, 170);
    glVertex3f(95.0, 560.0, 95);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-95.0, 560.0, -95);
    glVertex3f(-170.0, 580.0, -170);
    glVertex3f(170.0, 580.0, -170);
    glVertex3f(95.0, 560.0, -95);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-95.0, 560.0, -95);
    glVertex3f(-170.0, 580.0, -170);
    glVertex3f(-170.0, 580.0, 170);
    glVertex3f(-95.0, 560.0, 95);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(95.0, 560.0, -95);
    glVertex3f(170.0, 580.0, -170);
    glVertex3f(170.0, 580.0, 170);
    glVertex3f(95.0, 560.0, 95);
    glEnd();
    //Garis END SEBELUM LANTAI 3

    //lantai 3
    glBegin(GL_POLYGON);
    glColor3f(0.51, 0.46, 0.45);
    glVertex3f(-170.0, 580.0, -170);
    glVertex3f(-170.0, 580.0, 170);
    glVertex3f(170.0, 580.0, 170);
    glVertex3f(170.0, 580.0, -170);
    glEnd();
    //end lantai 3

    //dinding depan
    glBegin(GL_POLYGON);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(-90.0, 580.0, 90); //270
    glVertex3f(-90.0, 710.0, 90); //500
    glVertex3f(90.0, 710.0, 90); //500
    glVertex3f(90.0, 580.0, 90); //270
    glEnd();

    //dinding belakang
    glBegin(GL_POLYGON);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(-90.0, 580.0, -90);
    glVertex3f(-90.0, 710.0, -90);
    glVertex3f(90.0, 710.0, -90);
    glVertex3f(90.0, 580.0, -90);
    glEnd();

    //dinding kiri
    glBegin(GL_POLYGON);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(-90.0, 580.0, -90);
    glVertex3f(-90.0, 710.0, -90);
    glVertex3f(-90.0, 710.0, 90);
    glVertex3f(-90.0, 580.0, 90);
    glEnd();

    //dinding kanan
    glBegin(GL_POLYGON);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(90.0, 580.0, -90);
    glVertex3f(90.0, 710.0, -90);
    glVertex3f(90.0, 710.0, 90);
    glVertex3f(90.0, 580.0, 90);
    glEnd();

    // - - - - GARIS DINDING - - - - //
    //dinding depan
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-90.0, 580.0, 90); //270
    glVertex3f(-90.0, 710.0, 90); //500
    glVertex3f(90.0, 710.0, 90); //500
    glVertex3f(90.0, 580.0, 90); //270
    glEnd();

    //dinding belakang
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-90.0, 580.0, -90);
    glVertex3f(-90.0, 710.0, -90);
    glVertex3f(90.0, 710.0, -90);
    glVertex3f(90.0, 580.0, -90);
    glEnd();

    //dinding kiri
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-90.0, 580.0, -90);
    glVertex3f(-90.0, 710.0, -90);
    glVertex3f(-90.0, 710.0, 90);
    glVertex3f(-90.0, 580.0, 90);
    glEnd();

    //dinding kanan
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(90.0, 580.0, -90);
    glVertex3f(90.0, 710.0, -90);
    glVertex3f(90.0, 710.0, 90);
    glVertex3f(90.0, 580.0, 90);
    glEnd();

    //atap dasar
    glBegin(GL_POLYGON);
    glColor3f(0.87, 0.16, 0.16);
    glVertex3f(-115.0, 710.0, -115);
    glVertex3f(-115.0, 710.0, 115);
    glVertex3f(115.0, 710.0, 115);
    glVertex3f(115.0, 710.0, -115);
    glEnd();
    glBegin(GL_POLYGON); //depan
    glColor3f(0, 0.12, 0.12);
    glVertex3f(-115.0, 710.0, 115);
    glVertex3f(-115.0, 715.0, 115);
    glVertex3f(115.0, 715.0, 115);
    glVertex3f(115.0, 710.0, 115);
    glEnd();
    glBegin(GL_POLYGON); //belakang
    glColor3f(0, 0.12, 0.12);
    glVertex3f(-115.0, 710.0, -115);
    glVertex3f(-115.0, 715.0, -115);
    glVertex3f(115.0, 715.0, -115);
    glVertex3f(115.0, 710.0, -115);
    glEnd();
    glBegin(GL_POLYGON); //kiri
    glColor3f(0, 0.12, 0.12);
    glVertex3f(-115.0, 710.0, -115);
    glVertex3f(-115.0, 715.0, -115);
    glVertex3f(-115.0, 715.0, 115);
    glVertex3f(-115.0, 710.0, 115);
    glEnd();
    glBegin(GL_POLYGON); //kanan
    glColor3f(0, 0.12, 0.12);
    glVertex3f(115.0, 710.0, -115);
    glVertex3f(115.0, 715.0, -115);
    glVertex3f(115.0, 715.0, 115);
    glVertex3f(115.0, 710.0, 115);
    glEnd();

    //atap dasar 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.93, 0.66);
    glVertex3f(-120.0, 715.0, -120);
    glVertex3f(-120.0, 715.0, 120);
    glVertex3f(120.0, 715.0, 120);
    glVertex3f(120.0, 715.0, -120);
    glEnd();
    glBegin(GL_POLYGON); //depan
    glColor3f(0, 0.12, 0.12);
    glVertex3f(-120.0, 715.0, 120);
    glVertex3f(-120.0, 720.0, 120);
    glVertex3f(120.0, 720.0, 120);
    glVertex3f(120.0, 715.0, 120);
    glEnd();
    glBegin(GL_POLYGON); //belakang
    glColor3f(0, 0.12, 0.12);
    glVertex3f(-120.0, 715.0, -120);
    glVertex3f(-120.0, 720.0, -120);
    glVertex3f(120.0, 720.0, -120);
    glVertex3f(120.0, 715.0, -120);
    glEnd();
    glBegin(GL_POLYGON); //kiri
    glColor3f(0, 0.12, 0.12);
    glVertex3f(-120.0, 715.0, -120);
    glVertex3f(-120.0, 720.0, -120);
    glVertex3f(-120.0, 720.0, 120);
    glVertex3f(-120.0, 715.0, 120);
    glEnd();
    glBegin(GL_POLYGON); //kanan
    glColor3f(0, 0.12, 0.12);
    glVertex3f(120.0, 715.0, -120);
    glVertex3f(120.0, 720.0, -120);
    glVertex3f(120.0, 720.0, 120);
    glVertex3f(120.0, 715.0, 120);
    glEnd();

    //genteng bawah
    glBegin(GL_POLYGON); //depan
    glColor3f(0.45, 0.45, 0.45);
    glVertex3f(-120.0, 720.0, 120); //135
    glVertex3f(-190.0, 725.0, 190); //205
    glVertex3f(190.0, 725.0, 190); //135
    glVertex3f(120.0, 720.0, 120); //205
    glEnd();
    glBegin(GL_POLYGON); //belakang
    glColor3f(0.45, 0.45, 0.45);
    glVertex3f(-120.0, 720.0, -120); 
    glVertex3f(-190.0, 725.0, -190); 
    glVertex3f(190.0, 725.0, -190); 
    glVertex3f(120.0, 720.0, -120); 
    glEnd();
    glBegin(GL_POLYGON); //kiri
    glColor3f(0.45, 0.45, 0.45);
    glVertex3f(-120.0, 720.0, -120); 
    glVertex3f(-190.0, 725.0, -190); 
    glVertex3f(-190.0, 725.0, 190); 
    glVertex3f(-120.0, 720.0, 120); 
    glEnd();
    glBegin(GL_POLYGON); //kanan
    glColor3f(0.45, 0.45, 0.45);
    glVertex3f(120.0, 720.0, -120); 
    glVertex3f(190.0, 725.0, -190); 
    glVertex3f(190.0, 725.0, 190); 
    glVertex3f(120.0, 720.0, 120); 
    glEnd();

    //garis genteng bawah
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-120.0, 720.0, 120); //135
    glVertex3f(-190.0, 725.0, 190); //205
    glVertex3f(190.0, 725.0, 190); //135
    glVertex3f(120.0, 720.0, 120); //205
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-120.0, 720.0, -120);
    glVertex3f(-190.0, 725.0, -190);
    glVertex3f(190.0, 725.0, -190);
    glVertex3f(120.0, 720.0, -120);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-120.0, 720.0, -120);
    glVertex3f(-190.0, 725.0, -190);
    glVertex3f(-190.0, 725.0, 190);
    glVertex3f(-120.0, 720.0, 120);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(120.0, 720.0, -120);
    glVertex3f(190.0, 725.0, -190);
    glVertex3f(190.0, 725.0, 190);
    glVertex3f(120.0, 720.0, 120);
    glEnd();

    //genteng tengah
    glBegin(GL_POLYGON); //depan
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(-110.0, 745.0, 110); // 120, 720
    glVertex3f(-190.0, 725.0, 190); // 190, 725
    glVertex3f(190.0, 725.0, 190); 
    glVertex3f(110.0, 745.0, 110); 
    glEnd();
    glBegin(GL_POLYGON); //belakang
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(-110.0, 745.0, -110);
    glVertex3f(-190.0, 725.0, -190);
    glVertex3f(190.0, 725.0, -190);
    glVertex3f(110.0, 745.0, -110);
    glEnd();
    glBegin(GL_POLYGON); //kiri
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(-110.0, 745.0, -110);
    glVertex3f(-190.0, 725.0, -190);
    glVertex3f(-190.0, 725.0, 190);
    glVertex3f(-110.0, 745.0, 110);
    glEnd();
    glBegin(GL_POLYGON); //kanan
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(110.0, 745.0, -110);
    glVertex3f(190.0, 725.0, -190);
    glVertex3f(190.0, 725.0, 190);
    glVertex3f(110.0, 745.0, 110);
    glEnd();

    //genteng atas
    glBegin(GL_POLYGON); //depan
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(-80.0, 765.0, 80);
    glVertex3f(-110.0, 745.0, 110);
    glVertex3f(110.0, 745.0, 110);
    glVertex3f(80.0, 765.0, 80);
    glEnd();
    glBegin(GL_POLYGON); //belakang
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(-80.0, 765.0, -80);
    glVertex3f(-110.0, 745.0, -110);
    glVertex3f(110.0, 745.0, -110);
    glVertex3f(80.0, 765.0, -80);
    glEnd();
    glBegin(GL_POLYGON); //kiri
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(-80.0, 765.0, -80);
    glVertex3f(-110.0, 745.0, -110);
    glVertex3f(-110.0, 745.0, 110);
    glVertex3f(-80.0, 765.0, 80);
    glEnd();
    glBegin(GL_POLYGON); //kanan
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(80.0, 765.0, -80);
    glVertex3f(110.0, 745.0, -110);
    glVertex3f(110.0, 745.0, 110);
    glVertex3f(80.0, 765.0, 80);
    glEnd();

    //atap sebelum lantai 4
    glBegin(GL_POLYGON); //depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-80.0, 765.0, 80);
    glVertex3f(-155.0, 785.0, 155);
    glVertex3f(155.0, 785.0, 155);
    glVertex3f(80.0, 765.0, 80);
    glEnd();
    glBegin(GL_POLYGON); //belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-80.0, 765.0, -80);
    glVertex3f(-155.0, 785.0, -155);
    glVertex3f(155.0, 785.0, -155);
    glVertex3f(80.0, 765.0, -80);
    glEnd();
    glBegin(GL_POLYGON); //kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-80.0, 765.0, -80);
    glVertex3f(-155.0, 785.0, -155);
    glVertex3f(-155.0, 785.0, 155);
    glVertex3f(-80.0, 765.0, 80);
    glEnd();
    glBegin(GL_POLYGON); //kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(80.0, 765.0, -80);
    glVertex3f(155.0, 785.0, -155);
    glVertex3f(155.0, 785.0, 155);
    glVertex3f(80.0, 765.0, 80);
    glEnd();

    //garis atap sebelum lantai 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-80.0, 765.0, 80);
    glVertex3f(-155.0, 785.0, 155);
    glVertex3f(155.0, 785.0, 155);
    glVertex3f(80.0, 765.0, 80);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-80.0, 765.0, -80);
    glVertex3f(-155.0, 785.0, -155);
    glVertex3f(155.0, 785.0, -155);
    glVertex3f(80.0, 765.0, -80);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-80.0, 765.0, -80);
    glVertex3f(-155.0, 785.0, -155);
    glVertex3f(-155.0, 785.0, 155);
    glVertex3f(-80.0, 765.0, 80);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(80.0, 765.0, -80);
    glVertex3f(155.0, 785.0, -155);
    glVertex3f(155.0, 785.0, 155);
    glVertex3f(80.0, 765.0, 80);
    glEnd();

    //garis atap bawah
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-110.0, 745.0, 110);
    glVertex3f(-190.0, 725.0, 190);
    glVertex3f(190.0, 725.0, 190);
    glVertex3f(110.0, 745.0, 110);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-110.0, 745.0, -110);
    glVertex3f(-190.0, 725.0, -190);
    glVertex3f(190.0, 725.0, -190);
    glVertex3f(110.0, 745.0, -110);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-110.0, 745.0, -110);
    glVertex3f(-190.0, 725.0, -190);
    glVertex3f(-190.0, 725.0, 190);
    glVertex3f(-110.0, 745.0, 110);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(110.0, 745.0, -110);
    glVertex3f(190.0, 725.0, -190);
    glVertex3f(190.0, 725.0, 190);
    glVertex3f(110.0, 745.0, 110);
    glEnd();

    //garis atap atas
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-80.0, 765.0, 80);
    glVertex3f(-110.0, 745.0, 110);
    glVertex3f(110.0, 745.0, 110);
    glVertex3f(80.0, 765.0, 80);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-80.0, 765.0, -80);
    glVertex3f(-110.0, 745.0, -110);
    glVertex3f(110.0, 745.0, -110);
    glVertex3f(80.0, 765.0, -80);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-80.0, 765.0, -80);
    glVertex3f(-110.0, 745.0, -110);
    glVertex3f(-110.0, 745.0, 110);
    glVertex3f(-80.0, 765.0, 80);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(80.0, 765.0, -80);
    glVertex3f(110.0, 745.0, -110);
    glVertex3f(110.0, 745.0, 110);
    glVertex3f(80.0, 765.0, 80);
    glEnd();

}

void pintulantai3() {
    //pintu
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.3, 0.3);
    glVertex3f(-25.0, 580.0, 90.1); //270
    glVertex3f(-25.0, 660.0, 90.1); //500
    glVertex3f(25.0, 660.0, 90.1); //500
    glVertex3f(25.0, 580.0, 90.1); //270
    glEnd();
    //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-20.0, 650.0, 90.2);
    glVertex3f(-20.0, 655.0, 90.2);
    glVertex3f(-11.0, 655.0, 90.2);
    glVertex3f(-11.0, 650.0, 90.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-9.0, 650.0, 90.2);
    glVertex3f(-9.0, 655.0, 90.2);
    glVertex3f(-2.0, 655.0, 90.2);
    glVertex3f(-2.0, 650.0, 90.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(20.0, 650.0, 90.2);
    glVertex3f(20.0, 655.0, 90.2);
    glVertex3f(11.0, 655.0, 90.2);
    glVertex3f(11.0, 650.0, 90.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(9.0, 650.0, 90.2);
    glVertex3f(9.0, 655.0, 90.2);
    glVertex3f(2.0, 655.0, 90.2);
    glVertex3f(2.0, 650.0, 90.2);
    glEnd();
    // // // //
     //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-20.0, 642.0, 90.2);
    glVertex3f(-20.0, 647.0, 90.2);
    glVertex3f(-11.0, 647.0, 90.2);
    glVertex3f(-11.0, 642.0, 90.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-9.0, 642.0, 90.2);
    glVertex3f(-9.0, 647.0, 90.2);
    glVertex3f(-2.0, 647.0, 90.2);
    glVertex3f(-2.0, 642.0, 90.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(20.0, 642.0, 90.2);
    glVertex3f(20.0, 647.0, 90.2);
    glVertex3f(11.0, 647.0, 90.2);
    glVertex3f(11.0, 642.0, 90.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(9.0, 642.0, 90.2);
    glVertex3f(9.0, 647.0, 90.2);
    glVertex3f(2.0, 647.0, 90.2);
    glVertex3f(2.0, 642.0, 90.2);
    glEnd();
    // // // // // //
     //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-20.0, 634.0, 90.2);
    glVertex3f(-20.0, 639.0, 90.2);
    glVertex3f(-11.0, 639.0, 90.2);
    glVertex3f(-11.0, 634.0, 90.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-9.0, 634.0, 90.2);
    glVertex3f(-9.0, 639.0, 90.2);
    glVertex3f(-2.0, 639.0, 90.2);
    glVertex3f(-2.0, 634.0, 90.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(20.0, 634.0, 90.2);
    glVertex3f(20.0, 639.0, 90.2);
    glVertex3f(11.0, 639.0, 90.2);
    glVertex3f(11.0, 634.0, 90.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(9.0, 634.0, 90.2);
    glVertex3f(9.0, 639.0, 90.2);
    glVertex3f(2.0, 639.0, 90.2);
    glVertex3f(2.0, 634.0, 90.2);
    glEnd();
    // // // // // //
    //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-20.0, 627.0, 90.2);
    glVertex3f(-20.0, 631.0, 90.2);
    glVertex3f(-11.0, 631.0, 90.2);
    glVertex3f(-11.0, 627.0, 90.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-9.0, 627.0, 90.2);
    glVertex3f(-9.0, 631.0, 90.2);
    glVertex3f(-2.0, 631.0, 90.2);
    glVertex3f(-2.0, 627.0, 90.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(20.0, 627.0, 90.2);
    glVertex3f(20.0, 631.0, 90.2);
    glVertex3f(11.0, 631.0, 90.2);
    glVertex3f(11.0, 627.0, 90.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(9.0, 627.0, 90.2);
    glVertex3f(9.0, 631.0, 90.2);
    glVertex3f(2.0, 631.0, 90.2);
    glVertex3f(2.0, 627.0, 90.2);
    glEnd();
    // // // // // //
     //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-20.0, 618.0, 90.2);
    glVertex3f(-20.0, 623.0, 90.2);
    glVertex3f(-11.0, 623.0, 90.2);
    glVertex3f(-11.0, 618.0, 90.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-9.0, 618.0, 90.2);
    glVertex3f(-9.0, 623.0, 90.2);
    glVertex3f(-2.0, 623.0, 90.2);
    glVertex3f(-2.0, 618.0, 90.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(20.0, 618.0, 90.2);
    glVertex3f(20.0, 623.0, 90.2);
    glVertex3f(11.0, 623.0, 90.2);
    glVertex3f(11.0, 618.0, 90.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(9.0, 618.0, 90.2);
    glVertex3f(9.0, 623.0, 90.2);
    glVertex3f(2.0, 623.0, 90.2);
    glVertex3f(2.0, 618.0, 90.2);
    glEnd();
    // // // // // //
     //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-20.0, 610.0, 90.2);
    glVertex3f(-20.0, 615.0, 90.2);
    glVertex3f(-11.0, 615.0, 90.2);
    glVertex3f(-11.0, 610.0, 90.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-9.0, 610.0, 90.2);
    glVertex3f(-9.0, 615.0, 90.2);
    glVertex3f(-2.0, 615.0, 90.2);
    glVertex3f(-2.0, 610.0, 90.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(20.0, 610.0, 90.2);
    glVertex3f(20.0, 615.0, 90.2);
    glVertex3f(11.0, 615.0, 90.2);
    glVertex3f(11.0, 610.0, 90.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(9.0, 610.0, 90.2);
    glVertex3f(9.0, 615.0, 90.2);
    glVertex3f(2.0, 615.0, 90.2);
    glVertex3f(2.0, 610.0, 90.2);
    glEnd();
    // // // // // //
    //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-20.0, 602.0, 90.2);
    glVertex3f(-20.0, 607.0, 90.2);
    glVertex3f(-11.0, 607.0, 90.2);
    glVertex3f(-11.0, 602.0, 90.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-9.0, 602.0, 90.2);
    glVertex3f(-9.0, 607.0, 90.2);
    glVertex3f(-2.0, 607.0, 90.2);
    glVertex3f(-2.0, 602.0, 90.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(20.0, 602.0, 90.2);
    glVertex3f(20.0, 607.0, 90.2);
    glVertex3f(11.0, 607.0, 90.2);
    glVertex3f(11.0, 602.0, 90.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(9.0, 602.0, 90.2);
    glVertex3f(9.0, 607.0, 90.2);
    glVertex3f(2.0, 607.0, 90.2);
    glVertex3f(2.0, 602.0, 90.2);
    glEnd();
    // // // // // //
    //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-20.0, 594.0, 90.2);
    glVertex3f(-20.0, 599.0, 90.2);
    glVertex3f(-11.0, 599.0, 90.2);
    glVertex3f(-11.0, 594.0, 90.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-9.0, 594.0, 90.2);
    glVertex3f(-9.0, 599.0, 90.2);
    glVertex3f(-2.0, 599.0, 90.2);
    glVertex3f(-2.0, 594.0, 90.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(20.0, 594.0, 90.2);
    glVertex3f(20.0, 599.0, 90.2);
    glVertex3f(11.0, 599.0, 90.2);
    glVertex3f(11.0, 594.0, 90.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(9.0, 594.0, 90.2);
    glVertex3f(9.0, 599.0, 90.2);
    glVertex3f(2.0, 599.0, 90.2);
    glVertex3f(2.0, 594.0, 90.2);
    glEnd();

    // - - - - GARIS - - - - //
    //pintu
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-25.0, 580.0, 90.1); //270
    glVertex3f(-25.0, 660.0, 90.1); //500
    glVertex3f(25.0, 660.0, 90.1); //500
    glVertex3f(25.0, 580.0, 90.1); //270
    glEnd();
    //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-20.0, 650.0, 90.2);
    glVertex3f(-20.0, 655.0, 90.2);
    glVertex3f(-11.0, 655.0, 90.2);
    glVertex3f(-11.0, 650.0, 90.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-9.0, 650.0, 90.2);
    glVertex3f(-9.0, 655.0, 90.2);
    glVertex3f(-2.0, 655.0, 90.2);
    glVertex3f(-2.0, 650.0, 90.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(20.0, 650.0, 90.2);
    glVertex3f(20.0, 655.0, 90.2);
    glVertex3f(11.0, 655.0, 90.2);
    glVertex3f(11.0, 650.0, 90.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(9.0, 650.0, 90.2);
    glVertex3f(9.0, 655.0, 90.2);
    glVertex3f(2.0, 655.0, 90.2);
    glVertex3f(2.0, 650.0, 90.2);
    glEnd();
    // // // //
     //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-20.0, 642.0, 90.2);
    glVertex3f(-20.0, 647.0, 90.2);
    glVertex3f(-11.0, 647.0, 90.2);
    glVertex3f(-11.0, 642.0, 90.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-9.0, 642.0, 90.2);
    glVertex3f(-9.0, 647.0, 90.2);
    glVertex3f(-2.0, 647.0, 90.2);
    glVertex3f(-2.0, 642.0, 90.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(20.0, 642.0, 90.2);
    glVertex3f(20.0, 647.0, 90.2);
    glVertex3f(11.0, 647.0, 90.2);
    glVertex3f(11.0, 642.0, 90.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(9.0, 642.0, 90.2);
    glVertex3f(9.0, 647.0, 90.2);
    glVertex3f(2.0, 647.0, 90.2);
    glVertex3f(2.0, 642.0, 90.2);
    glEnd();
    // // // // // //
     //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-20.0, 634.0, 90.2);
    glVertex3f(-20.0, 639.0, 90.2);
    glVertex3f(-11.0, 639.0, 90.2);
    glVertex3f(-11.0, 634.0, 90.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-9.0, 634.0, 90.2);
    glVertex3f(-9.0, 639.0, 90.2);
    glVertex3f(-2.0, 639.0, 90.2);
    glVertex3f(-2.0, 634.0, 90.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(20.0, 634.0, 90.2);
    glVertex3f(20.0, 639.0, 90.2);
    glVertex3f(11.0, 639.0, 90.2);
    glVertex3f(11.0, 634.0, 90.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(9.0, 634.0, 90.2);
    glVertex3f(9.0, 639.0, 90.2);
    glVertex3f(2.0, 639.0, 90.2);
    glVertex3f(2.0, 634.0, 90.2);
    glEnd();
    // // // // // //
    //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-20.0, 627.0, 90.2);
    glVertex3f(-20.0, 631.0, 90.2);
    glVertex3f(-11.0, 631.0, 90.2);
    glVertex3f(-11.0, 627.0, 90.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-9.0, 627.0, 90.2);
    glVertex3f(-9.0, 631.0, 90.2);
    glVertex3f(-2.0, 631.0, 90.2);
    glVertex3f(-2.0, 627.0, 90.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(20.0, 627.0, 90.2);
    glVertex3f(20.0, 631.0, 90.2);
    glVertex3f(11.0, 631.0, 90.2);
    glVertex3f(11.0, 627.0, 90.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(9.0, 627.0, 90.2);
    glVertex3f(9.0, 631.0, 90.2);
    glVertex3f(2.0, 631.0, 90.2);
    glVertex3f(2.0, 627.0, 90.2);
    glEnd();
    // // // // // //
     //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-20.0, 618.0, 90.2);
    glVertex3f(-20.0, 623.0, 90.2);
    glVertex3f(-11.0, 623.0, 90.2);
    glVertex3f(-11.0, 618.0, 90.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-9.0, 618.0, 90.2);
    glVertex3f(-9.0, 623.0, 90.2);
    glVertex3f(-2.0, 623.0, 90.2);
    glVertex3f(-2.0, 618.0, 90.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(20.0, 618.0, 90.2);
    glVertex3f(20.0, 623.0, 90.2);
    glVertex3f(11.0, 623.0, 90.2);
    glVertex3f(11.0, 618.0, 90.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(9.0, 618.0, 90.2);
    glVertex3f(9.0, 623.0, 90.2);
    glVertex3f(2.0, 623.0, 90.2);
    glVertex3f(2.0, 618.0, 90.2);
    glEnd();
    // // // // // //
     //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-20.0, 610.0, 90.2);
    glVertex3f(-20.0, 615.0, 90.2);
    glVertex3f(-11.0, 615.0, 90.2);
    glVertex3f(-11.0, 610.0, 90.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-9.0, 610.0, 90.2);
    glVertex3f(-9.0, 615.0, 90.2);
    glVertex3f(-2.0, 615.0, 90.2);
    glVertex3f(-2.0, 610.0, 90.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(20.0, 610.0, 90.2);
    glVertex3f(20.0, 615.0, 90.2);
    glVertex3f(11.0, 615.0, 90.2);
    glVertex3f(11.0, 610.0, 90.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(9.0, 610.0, 90.2);
    glVertex3f(9.0, 615.0, 90.2);
    glVertex3f(2.0, 615.0, 90.2);
    glVertex3f(2.0, 610.0, 90.2);
    glEnd();
    // // // // // //
    //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-20.0, 602.0, 90.2);
    glVertex3f(-20.0, 607.0, 90.2);
    glVertex3f(-11.0, 607.0, 90.2);
    glVertex3f(-11.0, 602.0, 90.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-9.0, 602.0, 90.2);
    glVertex3f(-9.0, 607.0, 90.2);
    glVertex3f(-2.0, 607.0, 90.2);
    glVertex3f(-2.0, 602.0, 90.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(20.0, 602.0, 90.2);
    glVertex3f(20.0, 607.0, 90.2);
    glVertex3f(11.0, 607.0, 90.2);
    glVertex3f(11.0, 602.0, 90.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(9.0, 602.0, 90.2);
    glVertex3f(9.0, 607.0, 90.2);
    glVertex3f(2.0, 607.0, 90.2);
    glVertex3f(2.0, 602.0, 90.2);
    glEnd();
    // // // // // //
    //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-20.0, 594.0, 90.2);
    glVertex3f(-20.0, 599.0, 90.2);
    glVertex3f(-11.0, 599.0, 90.2);
    glVertex3f(-11.0, 594.0, 90.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-9.0, 594.0, 90.2);
    glVertex3f(-9.0, 599.0, 90.2);
    glVertex3f(-2.0, 599.0, 90.2);
    glVertex3f(-2.0, 594.0, 90.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(20.0, 594.0, 90.2);
    glVertex3f(20.0, 599.0, 90.2);
    glVertex3f(11.0, 599.0, 90.2);
    glVertex3f(11.0, 594.0, 90.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(9.0, 594.0, 90.2);
    glVertex3f(9.0, 599.0, 90.2);
    glVertex3f(2.0, 599.0, 90.2);
    glVertex3f(2.0, 594.0, 90.2);
    glEnd();
}

void lantai4() {
    //lantai 4 dasar
    glBegin(GL_POLYGON);
    glColor3f(0.51, 0.46, 0.45);
    glVertex3f(-155.0, 785.0, -155);
    glVertex3f(-155.0, 785.0, 155);
    glVertex3f(155.0, 785.0, 155);
    glVertex3f(155.0, 785.0, -155);
    glEnd();

    //dinding depan
    glBegin(GL_POLYGON);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(-60.0, 785.0, 60); 
    glVertex3f(-60.0, 915.0, 60); 
    glVertex3f(60.0, 915.0, 60); 
    glVertex3f(60.0, 785.0, 60); 
    glEnd();

    //dinding belakang
    glBegin(GL_POLYGON);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(-60.0, 785.0, -60);
    glVertex3f(-60.0, 915.0, -60);
    glVertex3f(60.0, 915.0, -60);
    glVertex3f(60.0, 785.0, -60);
    glEnd();

    //dinding kiri
    glBegin(GL_POLYGON);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(-60.0, 785.0, -60);
    glVertex3f(-60.0, 915.0, -60);
    glVertex3f(-60.0, 915.0, 60);
    glVertex3f(-60.0, 785.0, 60);
    glEnd();

    //dinding kanan
    glBegin(GL_POLYGON);
    glColor3f(0.93, 0.93, 0.93);
    glVertex3f(60.0, 785.0, -60);
    glVertex3f(60.0, 915.0, -60);
    glVertex3f(60.0, 915.0, 60);
    glVertex3f(60.0, 785.0, 60);
    glEnd();

    // - - - - GARIS DINDING - - - - //
    //dinding depan
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-60.0, 785.0, 60);
    glVertex3f(-60.0, 915.0, 60);
    glVertex3f(60.0, 915.0, 60);
    glVertex3f(60.0, 785.0, 60);
    glEnd();

    //dinding belakang
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-60.0, 785.0, -60);
    glVertex3f(-60.0, 915.0, -60);
    glVertex3f(60.0, 915.0, -60);
    glVertex3f(60.0, 785.0, -60);
    glEnd();

    //dinding kiri
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-60.0, 785.0, -60);
    glVertex3f(-60.0, 915.0, -60);
    glVertex3f(-60.0, 915.0, 60);
    glVertex3f(-60.0, 785.0, 60);
    glEnd();

    //dinding kanan
    glBegin(GL_POLYGON);
    glColor3f(0.7, 0.66, 0.66);
    glVertex3f(60.0, 785.0, -60);
    glVertex3f(60.0, 915.0, -60);
    glVertex3f(60.0, 915.0, 60);
    glVertex3f(60.0, 785.0, 60);
    glEnd();

    //atap dasar
    glBegin(GL_POLYGON);
    glColor3f(0.87, 0.16, 0.16);
    glVertex3f(-85.0, 915.0, -85);
    glVertex3f(-85.0, 915.0, 85);
    glVertex3f(85.0, 915.0, 85);
    glVertex3f(85.0, 915.0, -85);
    glEnd();
    glBegin(GL_POLYGON); //depan
    glColor3f(0, 0.12, 0.12);
    glVertex3f(-85.0, 915.0, 85);
    glVertex3f(-85.0, 920.0, 85);
    glVertex3f(85.0, 920.0, 85);
    glVertex3f(85.0, 915.0, 85);
    glEnd();
    glBegin(GL_POLYGON); //belakang
    glColor3f(0, 0.12, 0.12);
    glVertex3f(-85.0, 915.0, -85);
    glVertex3f(-85.0, 920.0, -85);
    glVertex3f(85.0, 920.0, -85);
    glVertex3f(85.0, 915.0, -85);
    glEnd();
    glBegin(GL_POLYGON); //kiri
    glColor3f(0, 0.12, 0.12);
    glVertex3f(-85.0, 915.0, -85);
    glVertex3f(-85.0, 920.0, -85);
    glVertex3f(-85.0, 920.0, 85);
    glVertex3f(-85.0, 915.0, 85);
    glEnd();
    glBegin(GL_POLYGON); //kanan
    glColor3f(0, 0.12, 0.12);
    glVertex3f(85.0, 915.0, -85);
    glVertex3f(85.0, 920.0, -85);
    glVertex3f(85.0, 920.0, 85);
    glVertex3f(85.0, 915.0, 85);
    glEnd();

    //atap dasar 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.93, 0.66);
    glVertex3f(-90.0, 920.0, -90);
    glVertex3f(-90.0, 920.0, 90);
    glVertex3f(90.0, 920.0, 90);
    glVertex3f(90.0, 920.0, -90);
    glEnd();
    glBegin(GL_POLYGON); //depan
    glColor3f(0, 0.12, 0.12);
    glVertex3f(-90.0, 920.0, 90);
    glVertex3f(-90.0, 925.0, 90);
    glVertex3f(90.0, 925.0, 90);
    glVertex3f(90.0, 920.0, 90);
    glEnd();
    glBegin(GL_POLYGON); //belakang
    glColor3f(0, 0.12, 0.12);
    glVertex3f(-90.0, 920.0, -90);
    glVertex3f(-90.0, 925.0, -90);
    glVertex3f(90.0, 925.0, -90);
    glVertex3f(90.0, 920.0, -90);
    glEnd();
    glBegin(GL_POLYGON); //kiri
    glColor3f(0, 0.12, 0.12);
    glVertex3f(-90.0, 920.0, -90);
    glVertex3f(-90.0, 925.0, -90);
    glVertex3f(-90.0, 925.0, 90);
    glVertex3f(-90.0, 920.0, 90);
    glEnd();
    glBegin(GL_POLYGON); //kanan
    glColor3f(0, 0.12, 0.12);
    glVertex3f(90.0, 920.0, -90);
    glVertex3f(90.0, 925.0, -90);
    glVertex3f(90.0, 925.0, 90);
    glVertex3f(90.0, 920.0, 90);
    glEnd();

    //atap dasar 3
    glBegin(GL_POLYGON);
    glColor3f(0.87, 0.16, 0.16);
    glVertex3f(-95.0, 925.0, -95);
    glVertex3f(-95.0, 925.0, 95);
    glVertex3f(95.0, 925.0, 95);
    glVertex3f(95.0, 925.0, -95);
    glEnd();

    //genteng bawah
    glBegin(GL_POLYGON); //depan
    glColor3f(0.45, 0.45, 0.45);
    glVertex3f(-95.0, 925.0, 95);
    glVertex3f(-160.0, 940.0, 160);
    glVertex3f(-80, 930, 150);
    glVertex3f(0, 925, 160);
    glVertex3f(80, 930, 150);
    glVertex3f(160.0, 940.0, 160);
    glVertex3f(95.0, 925.0, 95);
    glEnd();
    glBegin(GL_POLYGON); //belakang
    glColor3f(0.45, 0.45, 0.45);
    glVertex3f(-95.0, 925.0, -95);
    glVertex3f(-160.0, 940.0, -160);
    glVertex3f(-80, 930, -150);
    glVertex3f(0, 925, -160);
    glVertex3f(80, 930, -150);
    glVertex3f(160.0, 940.0, -160);
    glVertex3f(95.0, 925.0, -95);
    glEnd();
    glBegin(GL_POLYGON); //kiri
    glColor3f(0.45, 0.45, 0.45);
    glVertex3f(-95.0, 925.0, -95);
    glVertex3f(-160.0, 940.0, -160);
    glVertex3f(-150, 930, -80);
    glVertex3f(-160, 925, 0);
    glVertex3f(-150, 930, 80);
    glVertex3f(-160.0, 940.0, 160);
    glVertex3f(-95.0, 925.0, 95);
    glEnd();
    glBegin(GL_POLYGON); //kanan
    glColor3f(0.45, 0.45, 0.45);
    glVertex3f(95.0, 925.0, -95);
    glVertex3f(160.0, 940.0, -160);
    glVertex3f(150, 930, -80);
    glVertex3f(160, 925, 0);
    glVertex3f(150, 930, 80);
    glVertex3f(160.0, 940.0, 160);
    glVertex3f(95.0, 925.0, 95);
    glEnd();

    //genteng tengah 1
    glBegin(GL_POLYGON); //depan
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(-160, 940, 160);
    glVertex3f(-80, 930, 150);
    glVertex3f(0, 925, 160);
    glVertex3f(80, 930, 150);
    glVertex3f(160, 940, 160);
    glVertex3f(100, 960, 100);
    glVertex3f(-100, 960, 100);
    glEnd();
    glBegin(GL_POLYGON); //belakang
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(-160, 940, -160);
    glVertex3f(-80, 930, -150);
    glVertex3f(0, 925, -160);
    glVertex3f(80, 930, -150);
    glVertex3f(160, 940, -160);
    glVertex3f(100, 960, -100);
    glVertex3f(-100, 960, -100);
    glEnd();
    glBegin(GL_POLYGON); //kiri
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(-100, 960, -100);
    glVertex3f(-160.0, 940.0, -160);
    glVertex3f(-150, 930, -80);
    glVertex3f(-160, 925, 0);
    glVertex3f(-150, 930, 80);
    glVertex3f(-160.0, 940.0, 160);
    glVertex3f(-100, 960, 100);
    glEnd();
    glBegin(GL_POLYGON); //kanan
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(100, 960, -100);
    glVertex3f(160.0, 940.0, -160);
    glVertex3f(150, 930, -80);
    glVertex3f(160, 925, 0);
    glVertex3f(150, 930, 80);
    glVertex3f(160.0, 940.0, 160);
    glVertex3f(100, 960, 100);
    glEnd();

    //genteng tengah 2
    glBegin(GL_POLYGON); //depan
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(-100, 960, 100);
    glVertex3f(-60, 990, 60);
    glVertex3f(60, 990, 60);
    glVertex3f(100, 960, 100);
    glEnd();
    glBegin(GL_POLYGON); //belakang
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(-100, 960, -100);
    glVertex3f(-60, 990, -60);
    glVertex3f(60, 990, -60);
    glVertex3f(100, 960, -100);
    glEnd();
    glBegin(GL_POLYGON); //kanan
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(100, 960, -100);
    glVertex3f(60, 990, -60);
    glVertex3f(60, 990, 60);
    glVertex3f(100, 960, 100);
    glEnd();
    glBegin(GL_POLYGON); //kiri
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(-100, 960, -100);
    glVertex3f(-60, 990, -60);
    glVertex3f(-60, 990, 60);
    glVertex3f(-100, 960, 100);
    glEnd();

    //genteng tengah 3
    glBegin(GL_POLYGON); //depan
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(-60, 990, 60);
    glVertex3f(-35, 1030, 35);
    glVertex3f(35,1030, 35);
    glVertex3f(60, 990, 60);
    glEnd();
    glBegin(GL_POLYGON); //belakang
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(-60, 990, -60);
    glVertex3f(-35, 1030, -35);
    glVertex3f(35, 1030, -35);
    glVertex3f(60, 990, -60);
    glEnd();
    glBegin(GL_POLYGON); //kiri
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(-60, 990, -60);
    glVertex3f(-35, 1030, -35);
    glVertex3f(-35, 1030, 35);
    glVertex3f(-60, 990, 60);
    glEnd();
    glBegin(GL_POLYGON); //kanan
    glColor3f(0.17, 0.65, 0.59);
    glVertex3f(60, 990, -60);
    glVertex3f(35, 1030, -35);
    glVertex3f(35, 1030, 35);
    glVertex3f(60, 990, 60);
    glEnd();

    //genteng atas
    glBegin(GL_POLYGON);
    glColor3f(0.50, 0.50, 0.50);
    glVertex3f(-35, 1030, -35);
    glVertex3f(-35, 1030, 35);
    glVertex3f(35, 1030, 35);
    glVertex3f(35, 1030, -35);
    glEnd();

    // - - - - garis atap - - - - -//

    //genteng bawah
    glBegin(GL_LINE_LOOP); //depan
    glColor3f(0, 0, 0);
    glVertex3f(-95.0, 925.0, 95);
    glVertex3f(-160.0, 940.0, 160);
    glVertex3f(-80, 930, 150);
    glVertex3f(0, 925, 160);
    glVertex3f(80, 930, 150);
    glVertex3f(160.0, 940.0, 160);
    glVertex3f(95.0, 925.0, 95);
    glEnd();
    glBegin(GL_LINE_LOOP); //belakang
    glColor3f(0, 0, 0);
    glVertex3f(-95.0, 925.0, -95);
    glVertex3f(-160.0, 940.0, -160);
    glVertex3f(-80, 930, -150);
    glVertex3f(0, 925, -160);
    glVertex3f(80, 930, -150);
    glVertex3f(160.0, 940.0, -160);
    glVertex3f(95.0, 925.0, -95);
    glEnd();
    glBegin(GL_LINE_LOOP); //kiri
    glColor3f(0, 0, 0);
    glVertex3f(-95.0, 925.0, -95);
    glVertex3f(-160.0, 940.0, -160);
    glVertex3f(-150, 930, -80);
    glVertex3f(-160, 925, 0);
    glVertex3f(-150, 930, 80);
    glVertex3f(-160.0, 940.0, 160);
    glVertex3f(-95.0, 925.0, 95);
    glEnd();
    glBegin(GL_LINE_LOOP); //kanan
    glColor3f(0, 0, 0);
    glVertex3f(95.0, 925.0, -95);
    glVertex3f(160.0, 940.0, -160);
    glVertex3f(150, 930, -80);
    glVertex3f(160, 925, 0);
    glVertex3f(150, 930, 80);
    glVertex3f(160.0, 940.0, 160);
    glVertex3f(95.0, 925.0, 95);
    glEnd();

    //genteng tengah 1
    glBegin(GL_LINE_LOOP); //depan
    glColor3f(0, 0, 0);
    glVertex3f(-160, 940, 160);
    glVertex3f(-80, 930, 150);
    glVertex3f(0, 925, 160);
    glVertex3f(80, 930, 150);
    glVertex3f(160, 940, 160);
    glVertex3f(100, 960, 100);
    glVertex3f(-100, 960, 100);
    glEnd();
    glBegin(GL_LINE_LOOP); //belakang
    glColor3f(0, 0, 0);
    glVertex3f(-160, 940, -160);
    glVertex3f(-80, 930, -150);
    glVertex3f(0, 925, -160);
    glVertex3f(80, 930, -150);
    glVertex3f(160, 940, -160);
    glVertex3f(100, 960, -100);
    glVertex3f(-100, 960, -100);
    glEnd();
    glBegin(GL_LINE_LOOP); //kiri
    glColor3f(0, 0, 0);
    glVertex3f(-100, 960, -100);
    glVertex3f(-160.0, 940.0, -160);
    glVertex3f(-150, 930, -80);
    glVertex3f(-160, 925, 0);
    glVertex3f(-150, 930, 80);
    glVertex3f(-160.0, 940.0, 160);
    glVertex3f(-100, 960, 100);
    glEnd();
    glBegin(GL_LINE_LOOP); //kanan
    glColor3f(0, 0, 0);
    glVertex3f(100, 960, -100);
    glVertex3f(160.0, 940.0, -160);
    glVertex3f(150, 930, -80);
    glVertex3f(160, 925, 0);
    glVertex3f(150, 930, 80);
    glVertex3f(160.0, 940.0, 160);
    glVertex3f(100, 960, 100);
    glEnd();

    //genteng tengah 2
    glBegin(GL_LINE_LOOP); //depan
    glColor3f(0, 0, 0);
    glVertex3f(-100, 960, 100);
    glVertex3f(-60, 990, 60);
    glVertex3f(60, 990, 60);
    glVertex3f(100, 960, 100);
    glEnd();
    glBegin(GL_LINE_LOOP); //belakang
    glColor3f(0, 0, 0);
    glVertex3f(-100, 960, -100);
    glVertex3f(-60, 990, -60);
    glVertex3f(60, 990, -60);
    glVertex3f(100, 960, -100);
    glEnd();
    glBegin(GL_LINE_LOOP); //kanan
    glColor3f(0, 0, 0);
    glVertex3f(100, 960, -100);
    glVertex3f(60, 990, -60);
    glVertex3f(60, 990, 60);
    glVertex3f(100, 960, 100);
    glEnd();
    glBegin(GL_LINE_LOOP); //kiri
    glColor3f(0, 0, 0);
    glVertex3f(-100, 960, -100);
    glVertex3f(-60, 990, -60);
    glVertex3f(-60, 990, 60);
    glVertex3f(-100, 960, 100);
    glEnd();

    //genteng tengah 3
    glBegin(GL_LINE_LOOP); //depan
    glColor3f(0, 0, 0);
    glVertex3f(-60, 990, 60);
    glVertex3f(-35, 1030, 35);
    glVertex3f(35, 1030, 35);
    glVertex3f(60, 990, 60);
    glEnd();
    glBegin(GL_LINE_LOOP); //belakang
    glColor3f(0, 0, 0);
    glVertex3f(-60, 990, -60);
    glVertex3f(-35, 1030, -35);
    glVertex3f(35, 1030, -35);
    glVertex3f(60, 990, -60);
    glEnd();
    glBegin(GL_LINE_LOOP); //kiri
    glColor3f(0, 0, 0);
    glVertex3f(-60, 990, -60);
    glVertex3f(-35, 1030, -35);
    glVertex3f(-35, 1030, 35);
    glVertex3f(-60, 990, 60);
    glEnd();
    glBegin(GL_LINE_LOOP); //kanan
    glColor3f(0, 0, 0);
    glVertex3f(60, 990, -60);
    glVertex3f(35, 1030, -35);
    glVertex3f(35, 1030, 35);
    glVertex3f(60, 990, 60);
    glEnd();
}

void pintulantai4() {
    //pintu
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.3, 0.3);
    glVertex3f(-22.0, 785.0, 60.1);
    glVertex3f(-22.0, 865.0, 60.1);
    glVertex3f(22.0, 865.0, 60.1);
    glVertex3f(22.0, 785.0, 60.1);
    glEnd();
    //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-19.0, 855.0, 60.2);
    glVertex3f(-19.0, 860.0, 60.2);
    glVertex3f(-11.0, 860.0, 60.2);
    glVertex3f(-11.0, 855.0, 60.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-9.0, 855.0, 60.2);
    glVertex3f(-9.0, 860.0, 60.2);
    glVertex3f(-2.0, 860.0, 60.2);
    glVertex3f(-2.0, 855.0, 60.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(19.0, 855.0, 60.2);
    glVertex3f(19.0, 860.0, 60.2);
    glVertex3f(11.0, 860.0, 60.2);
    glVertex3f(11.0, 855.0, 60.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(9.0, 855.0, 60.2);
    glVertex3f(9.0, 860.0, 60.2);
    glVertex3f(2.0, 860.0, 60.2);
    glVertex3f(2.0, 855.0, 60.2);
    glEnd();
    // // // //
    //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-19.0, 847.0, 60.2);
    glVertex3f(-19.0, 852.0, 60.2);
    glVertex3f(-11.0, 852.0, 60.2);
    glVertex3f(-11.0, 847.0, 60.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-9.0, 847.0, 60.2);
    glVertex3f(-9.0, 852.0, 60.2);
    glVertex3f(-2.0, 852.0, 60.2);
    glVertex3f(-2.0, 847.0, 60.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(19.0, 847.0, 60.2);
    glVertex3f(19.0, 852.0, 60.2);
    glVertex3f(11.0, 852.0, 60.2);
    glVertex3f(11.0, 847.0, 60.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(9.0, 847.0, 60.2);
    glVertex3f(9.0, 852.0, 60.2);
    glVertex3f(2.0, 852.0, 60.2);
    glVertex3f(2.0, 847.0, 60.2);
    glEnd();
    // // // // // //
    //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-19.0, 839.0, 60.2);
    glVertex3f(-19.0, 844.0, 60.2);
    glVertex3f(-11.0, 844.0, 60.2);
    glVertex3f(-11.0, 839.0, 60.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-9.0, 839.0, 60.2);
    glVertex3f(-9.0, 844.0, 60.2);
    glVertex3f(-2.0, 844.0, 60.2);
    glVertex3f(-2.0, 839.0, 60.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(19.0, 839.0, 60.2);
    glVertex3f(19.0, 844.0, 60.2);
    glVertex3f(11.0, 844.0, 60.2);
    glVertex3f(11.0, 839.0, 60.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(9.0, 839.0, 60.2);
    glVertex3f(9.0, 844.0, 60.2);
    glVertex3f(2.0, 844.0, 60.2);
    glVertex3f(2.0, 839.0, 60.2);
    glEnd();
    // // // // // //
    //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-19.0, 831.0, 60.2);
    glVertex3f(-19.0, 836.0, 60.2);
    glVertex3f(-11.0, 836.0, 60.2);
    glVertex3f(-11.0, 831.0, 60.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-9.0, 831.0, 60.2);
    glVertex3f(-9.0, 836.0, 60.2);
    glVertex3f(-2.0, 836.0, 60.2);
    glVertex3f(-2.0, 831.0, 60.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(19.0, 831.0, 60.2);
    glVertex3f(19.0, 836.0, 60.2);
    glVertex3f(11.0, 836.0, 60.2);
    glVertex3f(11.0, 831.0, 60.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(9.0, 831.0, 60.2);
    glVertex3f(9.0, 836.0, 60.2);
    glVertex3f(2.0, 836.0, 60.2);
    glVertex3f(2.0, 831.0, 60.2);
    glEnd();
    // // // // // //
    //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-19.0, 823.0, 60.2);
    glVertex3f(-19.0, 828.0, 60.2);
    glVertex3f(-11.0, 828.0, 60.2);
    glVertex3f(-11.0, 823.0, 60.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-9.0, 823.0, 60.2);
    glVertex3f(-9.0, 828.0, 60.2);
    glVertex3f(-2.0, 828.0, 60.2);
    glVertex3f(-2.0, 823.0, 60.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(19.0, 823.0, 60.2);
    glVertex3f(19.0, 828.0, 60.2);
    glVertex3f(11.0, 828.0, 60.2);
    glVertex3f(11.0, 823.0, 60.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(9.0, 823.0, 60.2);
    glVertex3f(9.0, 828.0, 60.2);
    glVertex3f(2.0, 828.0, 60.2);
    glVertex3f(2.0, 823.0, 60.2);
    glEnd();
    // // // // // //
    //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-19.0, 815.0, 60.2);
    glVertex3f(-19.0, 820.0, 60.2);
    glVertex3f(-11.0, 820.0, 60.2);
    glVertex3f(-11.0, 815.0, 60.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-9.0, 815.0, 60.2);
    glVertex3f(-9.0, 820.0, 60.2);
    glVertex3f(-2.0, 820.0, 60.2);
    glVertex3f(-2.0, 815.0, 60.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(19.0, 815.0, 60.2);
    glVertex3f(19.0, 820.0, 60.2);
    glVertex3f(11.0, 820.0, 60.2);
    glVertex3f(11.0, 815.0, 60.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(9.0, 815.0, 60.2);
    glVertex3f(9.0, 820.0, 60.2);
    glVertex3f(2.0, 820.0, 60.2);
    glVertex3f(2.0, 815.0, 60.2);
    glEnd();
    // // // // // //
    //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-19.0, 807.0, 60.2);
    glVertex3f(-19.0, 812.0, 60.2);
    glVertex3f(-11.0, 812.0, 60.2);
    glVertex3f(-11.0, 807.0, 60.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-9.0, 807.0, 60.2);
    glVertex3f(-9.0, 812.0, 60.2);
    glVertex3f(-2.0, 812.0, 60.2);
    glVertex3f(-2.0, 807.0, 60.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(19.0, 807.0, 60.2);
    glVertex3f(19.0, 812.0, 60.2);
    glVertex3f(11.0, 812.0, 60.2);
    glVertex3f(11.0, 807.0, 60.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(9.0, 807.0, 60.2);
    glVertex3f(9.0, 812.0, 60.2);
    glVertex3f(2.0, 812.0, 60.2);
    glVertex3f(2.0, 807.0, 60.2);
    glEnd();
    // // // // // //
    //pintu detail
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-19.0, 799.0, 60.2);
    glVertex3f(-19.0, 804.0, 60.2);
    glVertex3f(-11.0, 804.0, 60.2);
    glVertex3f(-11.0, 799.0, 60.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(-9.0, 799.0, 60.2);
    glVertex3f(-9.0, 804.0, 60.2);
    glVertex3f(-2.0, 804.0, 60.2);
    glVertex3f(-2.0, 799.0, 60.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(19.0, 799.0, 60.2);
    glVertex3f(19.0, 804.0, 60.2);
    glVertex3f(11.0, 804.0, 60.2);
    glVertex3f(11.0, 799.0, 60.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_POLYGON);
    glColor3f(1, 0.87, 0.68);
    glVertex3f(9.0, 799.0, 60.2);
    glVertex3f(9.0, 804.0, 60.2);
    glVertex3f(2.0, 804.0, 60.2);
    glVertex3f(2.0, 799.0, 60.2);
    glEnd();

    // - - - - GARIS - - - - //
    //pintu
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-22.0, 785.0, 60.1);
    glVertex3f(-22.0, 865.0, 60.1);
    glVertex3f(22.0, 865.0, 60.1);
    glVertex3f(22.0, 785.0, 60.1);
    glEnd();
    //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-19.0, 855.0, 60.2);
    glVertex3f(-19.0, 860.0, 60.2);
    glVertex3f(-11.0, 860.0, 60.2);
    glVertex3f(-11.0, 855.0, 60.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-9.0, 855.0, 60.2);
    glVertex3f(-9.0, 860.0, 60.2);
    glVertex3f(-2.0, 860.0, 60.2);
    glVertex3f(-2.0, 855.0, 60.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(19.0, 855.0, 60.2);
    glVertex3f(19.0, 860.0, 60.2);
    glVertex3f(11.0, 860.0, 60.2);
    glVertex3f(11.0, 855.0, 60.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(9.0, 855.0, 60.2);
    glVertex3f(9.0, 860.0, 60.2);
    glVertex3f(2.0, 860.0, 60.2);
    glVertex3f(2.0, 855.0, 60.2);
    glEnd();
    // // // //
    //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-19.0, 847.0, 60.2);
    glVertex3f(-19.0, 852.0, 60.2);
    glVertex3f(-11.0, 852.0, 60.2);
    glVertex3f(-11.0, 847.0, 60.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-9.0, 847.0, 60.2);
    glVertex3f(-9.0, 852.0, 60.2);
    glVertex3f(-2.0, 852.0, 60.2);
    glVertex3f(-2.0, 847.0, 60.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(19.0, 847.0, 60.2);
    glVertex3f(19.0, 852.0, 60.2);
    glVertex3f(11.0, 852.0, 60.2);
    glVertex3f(11.0, 847.0, 60.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(9.0, 847.0, 60.2);
    glVertex3f(9.0, 852.0, 60.2);
    glVertex3f(2.0, 852.0, 60.2);
    glVertex3f(2.0, 847.0, 60.2);
    glEnd();
    // // // // // //
    //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-19.0, 839.0, 60.2);
    glVertex3f(-19.0, 844.0, 60.2);
    glVertex3f(-11.0, 844.0, 60.2);
    glVertex3f(-11.0, 839.0, 60.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-9.0, 839.0, 60.2);
    glVertex3f(-9.0, 844.0, 60.2);
    glVertex3f(-2.0, 844.0, 60.2);
    glVertex3f(-2.0, 839.0, 60.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(19.0, 839.0, 60.2);
    glVertex3f(19.0, 844.0, 60.2);
    glVertex3f(11.0, 844.0, 60.2);
    glVertex3f(11.0, 839.0, 60.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(9.0, 839.0, 60.2);
    glVertex3f(9.0, 844.0, 60.2);
    glVertex3f(2.0, 844.0, 60.2);
    glVertex3f(2.0, 839.0, 60.2);
    glEnd();
    // // // // // //
    //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-19.0, 831.0, 60.2);
    glVertex3f(-19.0, 836.0, 60.2);
    glVertex3f(-11.0, 836.0, 60.2);
    glVertex3f(-11.0, 831.0, 60.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-9.0, 831.0, 60.2);
    glVertex3f(-9.0, 836.0, 60.2);
    glVertex3f(-2.0, 836.0, 60.2);
    glVertex3f(-2.0, 831.0, 60.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(19.0, 831.0, 60.2);
    glVertex3f(19.0, 836.0, 60.2);
    glVertex3f(11.0, 836.0, 60.2);
    glVertex3f(11.0, 831.0, 60.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(9.0, 831.0, 60.2);
    glVertex3f(9.0, 836.0, 60.2);
    glVertex3f(2.0, 836.0, 60.2);
    glVertex3f(2.0, 831.0, 60.2);
    glEnd();
    // // // // // //
    //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-19.0, 823.0, 60.2);
    glVertex3f(-19.0, 828.0, 60.2);
    glVertex3f(-11.0, 828.0, 60.2);
    glVertex3f(-11.0, 823.0, 60.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-9.0, 823.0, 60.2);
    glVertex3f(-9.0, 828.0, 60.2);
    glVertex3f(-2.0, 828.0, 60.2);
    glVertex3f(-2.0, 823.0, 60.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(19.0, 823.0, 60.2);
    glVertex3f(19.0, 828.0, 60.2);
    glVertex3f(11.0, 828.0, 60.2);
    glVertex3f(11.0, 823.0, 60.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(9.0, 823.0, 60.2);
    glVertex3f(9.0, 828.0, 60.2);
    glVertex3f(2.0, 828.0, 60.2);
    glVertex3f(2.0, 823.0, 60.2);
    glEnd();
    // // // // // //
    //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-19.0, 815.0, 60.2);
    glVertex3f(-19.0, 820.0, 60.2);
    glVertex3f(-11.0, 820.0, 60.2);
    glVertex3f(-11.0, 815.0, 60.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-9.0, 815.0, 60.2);
    glVertex3f(-9.0, 820.0, 60.2);
    glVertex3f(-2.0, 820.0, 60.2);
    glVertex3f(-2.0, 815.0, 60.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(19.0, 815.0, 60.2);
    glVertex3f(19.0, 820.0, 60.2);
    glVertex3f(11.0, 820.0, 60.2);
    glVertex3f(11.0, 815.0, 60.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(9.0, 815.0, 60.2);
    glVertex3f(9.0, 820.0, 60.2);
    glVertex3f(2.0, 820.0, 60.2);
    glVertex3f(2.0, 815.0, 60.2);
    glEnd();
    // // // // // //
    //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-19.0, 807.0, 60.2);
    glVertex3f(-19.0, 812.0, 60.2);
    glVertex3f(-11.0, 812.0, 60.2);
    glVertex3f(-11.0, 807.0, 60.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-9.0, 807.0, 60.2);
    glVertex3f(-9.0, 812.0, 60.2);
    glVertex3f(-2.0, 812.0, 60.2);
    glVertex3f(-2.0, 807.0, 60.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(19.0, 807.0, 60.2);
    glVertex3f(19.0, 812.0, 60.2);
    glVertex3f(11.0, 812.0, 60.2);
    glVertex3f(11.0, 807.0, 60.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(9.0, 807.0, 60.2);
    glVertex3f(9.0, 812.0, 60.2);
    glVertex3f(2.0, 812.0, 60.2);
    glVertex3f(2.0, 807.0, 60.2);
    glEnd();
    // // // // // //
    //pintu detail
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-19.0, 799.0, 60.2);
    glVertex3f(-19.0, 804.0, 60.2);
    glVertex3f(-11.0, 804.0, 60.2);
    glVertex3f(-11.0, 799.0, 60.2);
    glEnd();
    //pintu detail 2
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-9.0, 799.0, 60.2);
    glVertex3f(-9.0, 804.0, 60.2);
    glVertex3f(-2.0, 804.0, 60.2);
    glVertex3f(-2.0, 799.0, 60.2);
    glEnd();
    //pintu detail 3
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(19.0, 799.0, 60.2);
    glVertex3f(19.0, 804.0, 60.2);
    glVertex3f(11.0, 804.0, 60.2);
    glVertex3f(11.0, 799.0, 60.2);
    glEnd();
    //pintu detail 4
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(9.0, 799.0, 60.2);
    glVertex3f(9.0, 804.0, 60.2);
    glVertex3f(2.0, 804.0, 60.2);
    glVertex3f(2.0, 799.0, 60.2);
    glEnd();
}

void matahari() {
    glPushMatrix();
    glColor3f(0.96, 1, 0.48);
    glTranslatef(800.0, 1500.0, -450.0);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(100.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glColor4f(0.96, 1, 0.48, 0.1);
    glTranslatef(800.0, 1500.0, -450.0);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidSphere(200.0, 0.0, 20);
    glEnd();
    glPopMatrix();
}

void pagarlantai1() {
    //top kanan
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(285.0, 120.0, 305);
    glVertex3f(285.0, 120.0, -305);
    glVertex3f(305.0, 120.0, -305);
    glVertex3f(305.0, 120.0, 305);
    glEnd();

    //top kiri
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(-285.0, 120.0, 305);
    glVertex3f(-285.0, 120.0, -305);
    glVertex3f(-305.0, 120.0, -305);
    glVertex3f(-305.0, 120.0, 305);
    glEnd();

    //top belakang
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(-305.0, 120.0, -285);
    glVertex3f(-305.0, 120.0, -305);
    glVertex3f(305.0, 120.0, -305);
    glVertex3f(305.0, 120.0, -285);
    glEnd();

    //top depan kiri
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(-305.0, 120.0, 285);
    glVertex3f(-305.0, 120.0, 305);
    glVertex3f(-135.0, 120.0, 305);
    glVertex3f(-135.0, 120.0, 285);
    glEnd();

    //top depan kanan
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(305.0, 120.0, 285);
    glVertex3f(305.0, 120.0, 305);
    glVertex3f(135.0, 120.0, 305);
    glVertex3f(135.0, 120.0, 285);
    glEnd();

    //bot kanan
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.15, 0.15);
    glVertex3f(285.0, 41.0, 300);
    glVertex3f(285.0, 41.0, -300);
    glVertex3f(300.0, 41.0, -300);
    glVertex3f(300.0, 41.0, 300);
    glEnd();

    //bot kiri
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.15, 0.15);
    glVertex3f(-285.0, 41.0, 300);
    glVertex3f(-285.0, 41.0, -300);
    glVertex3f(-300.0, 41.0, -300);
    glVertex3f(-300.0, 41.0, 300);
    glEnd();

    //bot belakang
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.15, 0.15);
    glVertex3f(-300.0, 41.0, -285);
    glVertex3f(-300.0, 41.0, -300);
    glVertex3f(300.0, 41.0, -300);
    glVertex3f(300.0, 41.0, -285);
    glEnd();

    //bot depan kiri
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.15, 0.15);
    glVertex3f(-300.0, 41.0, 285);
    glVertex3f(-300.0, 41.0, 300);
    glVertex3f(-135.0, 41.0, 300);
    glVertex3f(-135.0, 41.0, 285);
    glEnd();

    //bot depan kanan
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.15, 0.15);
    glVertex3f(300.0, 41.0, 285);
    glVertex3f(300.0, 41.0, 300);
    glVertex3f(135.0, 41.0, 300);
    glVertex3f(135.0, 41.0, 285);
    glEnd();

    //kanan 1
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.15, 0.15);
    glVertex3f(300.0, 40.0, 300);
    glVertex3f(300.0, 120.0, 300);
    glVertex3f(300.0, 120.0, 290);
    glVertex3f(300.0, 40.0, 290);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(290.0, 40.0, 300);
    glVertex3f(290.0, 120.0, 300);
    glVertex3f(290.0, 120.0, 290);
    glVertex3f(290.0, 40.0, 290);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, 300);
    glVertex3f(300.0, 120.0, 300);
    glVertex3f(290.0, 120.0, 300);
    glVertex3f(290.0, 40.0, 300);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, 290);
    glVertex3f(300.0, 120.0, 290);
    glVertex3f(290.0, 120.0, 290);
    glVertex3f(290.0, 40.0, 290);
    glEnd();

    //kanan 2
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, 225);
    glVertex3f(300.0, 120.0, 225);
    glVertex3f(300.0, 120.0, 215);
    glVertex3f(300.0, 40.0, 215);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(290.0, 40.0, 225);
    glVertex3f(290.0, 120.0, 225);
    glVertex3f(290.0, 120.0, 215);
    glVertex3f(290.0, 40.0, 215);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, 225);
    glVertex3f(300.0, 120.0, 225);
    glVertex3f(290.0, 120.0, 225);
    glVertex3f(290.0, 40.0, 225);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, 215);
    glVertex3f(300.0, 120.0, 215);
    glVertex3f(290.0, 120.0, 215);
    glVertex3f(290.0, 40.0, 215);
    glEnd();

    //kanan 3
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, 150);
    glVertex3f(300.0, 120.0, 150);
    glVertex3f(300.0, 120.0, 140);
    glVertex3f(300.0, 40.0, 140);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(290.0, 40.0, 150);
    glVertex3f(290.0, 120.0, 150);
    glVertex3f(290.0, 120.0, 140);
    glVertex3f(290.0, 40.0, 140);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, 150);
    glVertex3f(300.0, 120.0, 150);
    glVertex3f(290.0, 120.0, 150);
    glVertex3f(290.0, 40.0, 150);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, 140);
    glVertex3f(300.0, 120.0, 140);
    glVertex3f(290.0, 120.0, 140);
    glVertex3f(290.0, 40.0, 140);
    glEnd();


    //kanan 4
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, 75);
    glVertex3f(300.0, 120.0, 75);
    glVertex3f(300.0, 120.0, 65);
    glVertex3f(300.0, 40.0, 65);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(290.0, 40.0, 75);
    glVertex3f(290.0, 120.0, 75);
    glVertex3f(290.0, 120.0, 65);
    glVertex3f(290.0, 40.0, 65);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, 75);
    glVertex3f(300.0, 120.0, 75);
    glVertex3f(290.0, 120.0, 75);
    glVertex3f(290.0, 40.0, 75);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, 65);
    glVertex3f(300.0, 120.0, 65);
    glVertex3f(290.0, 120.0, 65);
    glVertex3f(290.0, 40.0, 65);
    glEnd();

    //kanan 5
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, -75);
    glVertex3f(300.0, 120.0, -75);
    glVertex3f(300.0, 120.0, -65);
    glVertex3f(300.0, 40.0, -65);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(290.0, 40.0, -75);
    glVertex3f(290.0, 120.0, -75);
    glVertex3f(290.0, 120.0, -65);
    glVertex3f(290.0, 40.0, -65);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, -75);
    glVertex3f(300.0, 120.0, -75);
    glVertex3f(290.0, 120.0, -75);
    glVertex3f(290.0, 40.0, -75);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, -65);
    glVertex3f(300.0, 120.0, -65);
    glVertex3f(290.0, 120.0, -65);
    glVertex3f(290.0, 40.0, -65);
    glEnd();

    //kanan tengah
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, 5);
    glVertex3f(300.0, 120.0, 5);
    glVertex3f(300.0, 120.0, -5);
    glVertex3f(300.0, 40.0, -5);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(290.0, 40.0, -5);
    glVertex3f(290.0, 120.0, -5);
    glVertex3f(290.0, 120.0, 5);
    glVertex3f(290.0, 40.0, 5);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, -5);
    glVertex3f(300.0, 120.0, -5);
    glVertex3f(290.0, 120.0, -5);
    glVertex3f(290.0, 40.0, -5);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, 5);
    glVertex3f(300.0, 120.0, 5);
    glVertex3f(290.0, 120.0, 5);
    glVertex3f(290.0, 40.0, 5);
    glEnd();


    //kanan 8
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.15, 0.15);
    glVertex3f(300.0, 40.0, -300);
    glVertex3f(300.0, 120.0, -300);
    glVertex3f(300.0, 120.0, -290);
    glVertex3f(300.0, 40.0, -290);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(290.0, 40.0, -300);
    glVertex3f(290.0, 120.0, -300);
    glVertex3f(290.0, 120.0, -290);
    glVertex3f(290.0, 40.0, -290);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, -300);
    glVertex3f(300.0, 120.0, -300);
    glVertex3f(290.0, 120.0, -300);
    glVertex3f(290.0, 40.0, -300);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, -290);
    glVertex3f(300.0, 120.0, -290);
    glVertex3f(290.0, 120.0, -290);
    glVertex3f(290.0, 40.0, -290);
    glEnd();

    //kanan 7
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, -225);
    glVertex3f(300.0, 120.0, -225);
    glVertex3f(300.0, 120.0, -215);
    glVertex3f(300.0, 40.0, -215);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(290.0, 40.0, -225);
    glVertex3f(290.0, 120.0, -225);
    glVertex3f(290.0, 120.0, -215);
    glVertex3f(290.0, 40.0, -215);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, -225);
    glVertex3f(300.0, 120.0, -225);
    glVertex3f(290.0, 120.0, -225);
    glVertex3f(290.0, 40.0, -225);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, -215);
    glVertex3f(300.0, 120.0, -215);
    glVertex3f(290.0, 120.0, -215);
    glVertex3f(290.0, 40.0, -215);
    glEnd();

    //kanan 6
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, -150);
    glVertex3f(300.0, 120.0, -150);
    glVertex3f(300.0, 120.0, -140);
    glVertex3f(300.0, 40.0, -140);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(290.0, 40.0, -150);
    glVertex3f(290.0, 120.0, -150);
    glVertex3f(290.0, 120.0, -140);
    glVertex3f(290.0, 40.0, -140);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, -150);
    glVertex3f(300.0, 120.0, -150);
    glVertex3f(290.0, 120.0, -150);
    glVertex3f(290.0, 40.0, -150);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(300.0, 40.0, -140);
    glVertex3f(300.0, 120.0, -140);
    glVertex3f(290.0, 120.0, -140);
    glVertex3f(290.0, 40.0, -140);
    glEnd();


    //KIRI  4
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, 75);
    glVertex3f(-300.0, 120.0, 75);
    glVertex3f(-300.0, 120.0, 65);
    glVertex3f(-300.0, 40.0, 65);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-290.0, 40.0, 75);
    glVertex3f(-290.0, 120.0, 75);
    glVertex3f(-290.0, 120.0, 65);
    glVertex3f(-290.0, 40.0, 65);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, 75);
    glVertex3f(-300.0, 120.0, 75);
    glVertex3f(-290.0, 120.0, 75);
    glVertex3f(-290.0, 40.0, 75);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, 65);
    glVertex3f(-300.0, 120.0, 65);
    glVertex3f(-290.0, 120.0, 65);
    glVertex3f(-290.0, 40.0, 65);
    glEnd();

    //kiri 3
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, 150);
    glVertex3f(-300.0, 120.0, 150);
    glVertex3f(-300.0, 120.0, 140);
    glVertex3f(-300.0, 40.0, 140);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-290.0, 40.0, 150);
    glVertex3f(-290.0, 120.0, 150);
    glVertex3f(-290.0, 120.0, 140);
    glVertex3f(-290.0, 40.0, 140);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, 150);
    glVertex3f(-300.0, 120.0, 150);
    glVertex3f(-290.0, 120.0, 150);
    glVertex3f(-290.0, 40.0, 150);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, 140);
    glVertex3f(-300.0, 120.0, 140);
    glVertex3f(-290.0, 120.0, 140);
    glVertex3f(-290.0, 40.0, 140);
    glEnd();


    //kiri 2
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, 225);
    glVertex3f(-300.0, 120.0, 225);
    glVertex3f(-300.0, 120.0, 215);
    glVertex3f(-300.0, 40.0, 215);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-290.0, 40.0, 225);
    glVertex3f(-290.0, 120.0, 225);
    glVertex3f(-290.0, 120.0, 215);
    glVertex3f(-290.0, 40.0, 215);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, 225);
    glVertex3f(-300.0, 120.0, 225);
    glVertex3f(-290.0, 120.0, 225);
    glVertex3f(-290.0, 40.0, 225);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, 215);
    glVertex3f(-300.0, 120.0, 215);
    glVertex3f(-290.0, 120.0, 215);
    glVertex3f(-290.0, 40.0, 215);
    glEnd();


    //kiri 1
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, 300);
    glVertex3f(-300.0, 120.0, 300);
    glVertex3f(-300.0, 120.0, 290);
    glVertex3f(-300.0, 40.0, 290);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-290.0, 40.0, 300);
    glVertex3f(-290.0, 120.0, 300);
    glVertex3f(-290.0, 120.0, 290);
    glVertex3f(-290.0, 40.0, 290);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, 300);
    glVertex3f(-300.0, 120.0, 300);
    glVertex3f(-290.0, 120.0, 300);
    glVertex3f(-290.0, 40.0, 300);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, 290);
    glVertex3f(-300.0, 120.0, 290);
    glVertex3f(-290.0, 120.0, 290);
    glVertex3f(-290.0, 40.0, 290);
    glEnd();

    //kiri tengah
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, 5);
    glVertex3f(-300.0, 120.0, 5);
    glVertex3f(-300.0, 120.0, -5);
    glVertex3f(-300.0, 40.0, -5);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-290.0, 40.0, -5);
    glVertex3f(-290.0, 120.0, -5);
    glVertex3f(-290.0, 120.0, 5);
    glVertex3f(-290.0, 40.0, 5);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, -5);
    glVertex3f(-300.0, 120.0, -5);
    glVertex3f(-290.0, 120.0, -5);
    glVertex3f(-290.0, 40.0, -5);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, 5);
    glVertex3f(-300.0, 120.0, 5);
    glVertex3f(-290.0, 120.0, 5);
    glVertex3f(-290.0, 40.0, 5);
    glEnd();


    //KIRI  5
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, -75);
    glVertex3f(-300.0, 120.0, -75);
    glVertex3f(-300.0, 120.0, -65);
    glVertex3f(-300.0, 40.0, -65);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-290.0, 40.0, -75);
    glVertex3f(-290.0, 120.0, -75);
    glVertex3f(-290.0, 120.0, -65);
    glVertex3f(-290.0, 40.0, -65);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, -75);
    glVertex3f(-300.0, 120.0, -75);
    glVertex3f(-290.0, 120.0, -75);
    glVertex3f(-290.0, 40.0, -75);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, -65);
    glVertex3f(-300.0, 120.0, -65);
    glVertex3f(-290.0, 120.0, -65);
    glVertex3f(-290.0, 40.0, -65);
    glEnd();

    //kiri 6
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, -150);
    glVertex3f(-300.0, 120.0, -150);
    glVertex3f(-300.0, 120.0, -140);
    glVertex3f(-300.0, 40.0, -140);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-290.0, 40.0, -150);
    glVertex3f(-290.0, 120.0, -150);
    glVertex3f(-290.0, 120.0, -140);
    glVertex3f(-290.0, 40.0, -140);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, -150);
    glVertex3f(-300.0, 120.0, -150);
    glVertex3f(-290.0, 120.0, -150);
    glVertex3f(-290.0, 40.0, -150);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, -140);
    glVertex3f(-300.0, 120.0, -140);
    glVertex3f(-290.0, 120.0, -140);
    glVertex3f(-290.0, 40.0, -140);
    glEnd();


    //kiri 7
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, -225);
    glVertex3f(-300.0, 120.0, -225);
    glVertex3f(-300.0, 120.0, -215);
    glVertex3f(-300.0, 40.0, -215);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-290.0, 40.0, -225);
    glVertex3f(-290.0, 120.0, -225);
    glVertex3f(-290.0, 120.0, -215);
    glVertex3f(-290.0, 40.0, -215);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, -225);
    glVertex3f(-300.0, 120.0, -225);
    glVertex3f(-290.0, 120.0, -225);
    glVertex3f(-290.0, 40.0, -225);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, -215);
    glVertex3f(-300.0, 120.0, -215);
    glVertex3f(-290.0, 120.0, -215);
    glVertex3f(-290.0, 40.0, -215);
    glEnd();


    //kiri 8
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, -300);
    glVertex3f(-300.0, 120.0, -300);
    glVertex3f(-300.0, 120.0, -290);
    glVertex3f(-300.0, 40.0, -290);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-290.0, 40.0, -300);
    glVertex3f(-290.0, 120.0, -300);
    glVertex3f(-290.0, 120.0, -290);
    glVertex3f(-290.0, 40.0, -290);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, -300);
    glVertex3f(-300.0, 120.0, -300);
    glVertex3f(-290.0, 120.0, -300);
    glVertex3f(-290.0, 40.0, -300);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-300.0, 40.0, -290);
    glVertex3f(-300.0, 120.0, -290);
    glVertex3f(-290.0, 120.0, -290);
    glVertex3f(-290.0, 40.0, -290);
    glEnd();



    //belakang 1
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-225.0, 40.0, -300);
    glVertex3f(-225.0, 120.0, -300);
    glVertex3f(-215.0, 120.0, -300);
    glVertex3f(-215.0, 40.0, -300);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-225.0, 40.0, -290);
    glVertex3f(-225.0, 120.0, -290);
    glVertex3f(-215.0, 120.0, -290);
    glVertex3f(-215.0, 40.0, -290);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-225.0, 40.0, -300);
    glVertex3f(-225.0, 120.0, -300);
    glVertex3f(-225.0, 120.0, -290);
    glVertex3f(-225.0, 40.0, -290);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-215.0, 40.0, -300);
    glVertex3f(-215.0, 120.0, -300);
    glVertex3f(-215.0, 120.0, -290);
    glVertex3f(-215.0, 40.0, -290);
    glEnd();

    //belakang 2
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-150.0, 40.0, -300);
    glVertex3f(-150.0, 120.0, -300);
    glVertex3f(-140.0, 120.0, -300);
    glVertex3f(-140.0, 40.0, -300);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-150.0, 40.0, -290);
    glVertex3f(-150.0, 120.0, -290);
    glVertex3f(-140.0, 120.0, -290);
    glVertex3f(-140.0, 40.0, -290);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-150.0, 40.0, -300);
    glVertex3f(-150.0, 120.0, -300);
    glVertex3f(-150.0, 120.0, -290);
    glVertex3f(-150.0, 40.0, -290);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-140.0, 40.0, -300);
    glVertex3f(-140.0, 120.0, -300);
    glVertex3f(-140.0, 120.0, -290);
    glVertex3f(-140.0, 40.0, -290);
    glEnd();

    //belakang 3
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-75.0, 40.0, -300);
    glVertex3f(-75.0, 120.0, -300);
    glVertex3f(-65.0, 120.0, -300);
    glVertex3f(-65.0, 40.0, -300);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-75.0, 40.0, -290);
    glVertex3f(-75.0, 120.0, -290);
    glVertex3f(-65.0, 120.0, -290);
    glVertex3f(-65.0, 40.0, -290);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-75.0, 40.0, -300);
    glVertex3f(-75.0, 120.0, -300);
    glVertex3f(-75.0, 120.0, -290);
    glVertex3f(-75.0, 40.0, -290);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-65.0, 40.0, -300);
    glVertex3f(-65.0, 120.0, -300);
    glVertex3f(-65.0, 120.0, -290);
    glVertex3f(-65.0, 40.0, -290);
    glEnd();

    //belakang tengah
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-5.0, 40.0, -300);
    glVertex3f(-5.0, 120.0, -300);
    glVertex3f(5.0, 120.0, -300);
    glVertex3f(5.0, 40.0, -300);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-5.0, 40.0, -290);
    glVertex3f(-5.0, 120.0, -290);
    glVertex3f(5.0, 120.0, -290);
    glVertex3f(5.0, 40.0, -290);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-5.0, 40.0, -300);
    glVertex3f(-5.0, 120.0, -300);
    glVertex3f(-5.0, 120.0, -290);
    glVertex3f(-5.0, 40.0, -290);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(5.0, 40.0, -300);
    glVertex3f(5.0, 120.0, -300);
    glVertex3f(5.0, 120.0, -290);
    glVertex3f(5.0, 40.0, -290);
    glEnd();

    //belakang 7
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(225.0, 40.0, -300);
    glVertex3f(225.0, 120.0, -300);
    glVertex3f(215.0, 120.0, -300);
    glVertex3f(215.0, 40.0, -300);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(225.0, 40.0, -290);
    glVertex3f(225.0, 120.0, -290);
    glVertex3f(215.0, 120.0, -290);
    glVertex3f(215.0, 40.0, -290);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(225.0, 40.0, -300);
    glVertex3f(225.0, 120.0, -300);
    glVertex3f(225.0, 120.0, -290);
    glVertex3f(225.0, 40.0, -290);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(215.0, 40.0, -300);
    glVertex3f(215.0, 120.0, -300);
    glVertex3f(215.0, 120.0, -290);
    glVertex3f(215.0, 40.0, -290);
    glEnd();

    //belakang 6
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(150.0, 40.0, -300);
    glVertex3f(150.0, 120.0, -300);
    glVertex3f(140.0, 120.0, -300);
    glVertex3f(140.0, 40.0, -300);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(150.0, 40.0, -290);
    glVertex3f(150.0, 120.0, -290);
    glVertex3f(140.0, 120.0, -290);
    glVertex3f(140.0, 40.0, -290);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(150.0, 40.0, -300);
    glVertex3f(150.0, 120.0, -300);
    glVertex3f(150.0, 120.0, -290);
    glVertex3f(150.0, 40.0, -290);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(140.0, 40.0, -300);
    glVertex3f(140.0, 120.0, -300);
    glVertex3f(140.0, 120.0, -290);
    glVertex3f(140.0, 40.0, -290);
    glEnd();

    //belakang 5
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(75.0, 40.0, -300);
    glVertex3f(75.0, 120.0, -300);
    glVertex3f(65.0, 120.0, -300);
    glVertex3f(65.0, 40.0, -300);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(75.0, 40.0, -290);
    glVertex3f(75.0, 120.0, -290);
    glVertex3f(65.0, 120.0, -290);
    glVertex3f(65.0, 40.0, -290);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(75.0, 40.0, -300);
    glVertex3f(75.0, 120.0, -300);
    glVertex3f(75.0, 120.0, -290);
    glVertex3f(75.0, 40.0, -290);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(65.0, 40.0, -300);
    glVertex3f(65.0, 120.0, -300);
    glVertex3f(65.0, 120.0, -290);
    glVertex3f(65.0, 40.0, -290);
    glEnd();


    //depan 1
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(225.0, 40.0, 300);
    glVertex3f(225.0, 120.0, 300);
    glVertex3f(215.0, 120.0, 300);
    glVertex3f(215.0, 40.0, 300);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(225.0, 40.0, 290);
    glVertex3f(225.0, 120.0, 290);
    glVertex3f(215.0, 120.0, 290);
    glVertex3f(215.0, 40.0, 290);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(225.0, 40.0, 300);
    glVertex3f(225.0, 120.0, 300);
    glVertex3f(225.0, 120.0, 290);
    glVertex3f(225.0, 40.0, 290);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(215.0, 40.0, 300);
    glVertex3f(215.0, 120.0, 300);
    glVertex3f(215.0, 120.0, 290);
    glVertex3f(215.0, 40.0, 290);
    glEnd();

    //depan 2
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(150.0, 40.0, 300);
    glVertex3f(150.0, 120.0, 300);
    glVertex3f(140.0, 120.0, 300);
    glVertex3f(140.0, 40.0, 300);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(150.0, 40.0, 290);
    glVertex3f(150.0, 120.0, 290);
    glVertex3f(140.0, 120.0, 290);
    glVertex3f(140.0, 40.0, 290);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(150.0, 40.0, 300);
    glVertex3f(150.0, 120.0, 300);
    glVertex3f(150.0, 120.0, 290);
    glVertex3f(150.0, 40.0, 290);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(140.0, 40.0, 300);
    glVertex3f(140.0, 120.0, 300);
    glVertex3f(140.0, 120.0, 290);
    glVertex3f(140.0, 40.0, 290);
    glEnd();

    //depan kiri 1
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-225.0, 40.0, 300);
    glVertex3f(-225.0, 120.0, 300);
    glVertex3f(-215.0, 120.0, 300);
    glVertex3f(-215.0, 40.0, 300);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-225.0, 40.0, 290);
    glVertex3f(-225.0, 120.0, 290);
    glVertex3f(-215.0, 120.0, 290);
    glVertex3f(-215.0, 40.0, 290);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-225.0, 40.0, 300);
    glVertex3f(-225.0, 120.0, 300);
    glVertex3f(-225.0, 120.0, 290);
    glVertex3f(-225.0, 40.0, 290);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-215.0, 40.0, 300);
    glVertex3f(-215.0, 120.0, 300);
    glVertex3f(-215.0, 120.0, 290);
    glVertex3f(-215.0, 40.0, 290);
    glEnd();

    //depan kiri 2
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-150.0, 40.0, 300);
    glVertex3f(-150.0, 120.0, 300);
    glVertex3f(-140.0, 120.0, 300);
    glVertex3f(-140.0, 40.0, 300);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-150.0, 40.0, 290);
    glVertex3f(-150.0, 120.0, 290);
    glVertex3f(-140.0, 120.0, 290);
    glVertex3f(-140.0, 40.0, 290);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-150.0, 40.0, 300);
    glVertex3f(-150.0, 120.0, 300);
    glVertex3f(-150.0, 120.0, 290);
    glVertex3f(-150.0, 40.0, 290);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-140.0, 40.0, 300);
    glVertex3f(-140.0, 120.0, 300);
    glVertex3f(-140.0, 120.0, 290);
    glVertex3f(-140.0, 40.0, 290);
    glEnd();
    //batas bawah lantai
}

void pagarlantai2() {
    //top kanan
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(185.0, 330.0, 205);
    glVertex3f(188.0, 330.0, -205);
    glVertex3f(205.0, 330.0, -205);
    glVertex3f(205.0, 330.0, 205);
    glEnd();

    //top kiri
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(-185.0, 330.0, 205);
    glVertex3f(-188.0, 330.0, -205);
    glVertex3f(-205.0, 330.0, -205);
    glVertex3f(-205.0, 330.0, 205);
    glEnd();

    //top belakang
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(-205.0, 330.0, -185);
    glVertex3f(-205.0, 330.0, -205);
    glVertex3f(205.0, 330.0, -205);
    glVertex3f(205.0, 330.0, -185);
    glEnd();

    //top depan
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(-205.0, 330.0, 185);
    glVertex3f(-205.0, 330.0, 205);
    glVertex3f(205.0, 330.0, 205);
    glVertex3f(205.0, 330.0, 185);
    glEnd();


    //kanan 1
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(200.0, 270.0, 200);
    glVertex3f(200.0, 330.0, 200);
    glVertex3f(200.0, 330.0, 190);
    glVertex3f(200.0, 270.0, 190);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(190.0, 270.0, 200);
    glVertex3f(190.0, 330.0, 200);
    glVertex3f(190.0, 330.0, 190);
    glVertex3f(190.0, 270.0, 190);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(200.0, 270.0, 200);
    glVertex3f(200.0, 330.0, 200);
    glVertex3f(190.0, 330.0, 200);
    glVertex3f(190.0, 270.0, 200);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(200.0, 270.0, 190);
    glVertex3f(200.0, 330.0, 190);
    glVertex3f(190.0, 330.0, 190);
    glVertex3f(190.0, 270.0, 190);
    glEnd();

    //kanan 2
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(200.0, 270.0, 140);
    glVertex3f(200.0, 330.0, 140);
    glVertex3f(200.0, 330.0, 130);
    glVertex3f(200.0, 270.0, 130);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(190.0, 270.0, 140);
    glVertex3f(190.0, 330.0, 140);
    glVertex3f(190.0, 330.0, 130);
    glVertex3f(190.0, 270.0, 130);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(200.0, 270.0, 140);
    glVertex3f(200.0, 330.0, 140);
    glVertex3f(190.0, 330.0, 140);
    glVertex3f(190.0, 270.0, 140);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(200.0, 270.0, 130);
    glVertex3f(200.0, 330.0, 130);
    glVertex3f(190.0, 330.0, 130);
    glVertex3f(190.0, 270.0, 130);
    glEnd();

    //kanan 3
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(200.0, 270.0, 80);
    glVertex3f(200.0, 330.0, 80);
    glVertex3f(200.0, 330.0, 70);
    glVertex3f(200.0, 270.0, 70);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(190.0, 270.0, 80);
    glVertex3f(190.0, 330.0, 80);
    glVertex3f(190.0, 330.0, 70);
    glVertex3f(190.0, 270.0, 70);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(200.0, 270.0, 80);
    glVertex3f(200.0, 330.0, 80);
    glVertex3f(190.0, 330.0, 80);
    glVertex3f(190.0, 270.0, 80);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(200.0, 270.0, 70);
    glVertex3f(200.0, 330.0, 70);
    glVertex3f(190.0, 330.0, 70);
    glVertex3f(190.0, 270.0, 70);
    glEnd();

    //kanan 4
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(200.0, 270.0, 5);
    glVertex3f(200.0, 330.0, 5);
    glVertex3f(200.0, 330.0, -5);
    glVertex3f(200.0, 270.0, -5);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(190.0, 270.0, 5);
    glVertex3f(190.0, 330.0, 5);
    glVertex3f(190.0, 330.0, -5);
    glVertex3f(190.0, 270.0, -5);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(200.0, 270.0, 5);
    glVertex3f(200.0, 330.0, 5);
    glVertex3f(190.0, 330.0, 5);
    glVertex3f(190.0, 270.0, 5);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(200.0, 270.0, -5);
    glVertex3f(200.0, 330.0, -5);
    glVertex3f(190.0, 330.0, -5);
    glVertex3f(190.0, 270.0, -5);
    glEnd();

    //kanan 7
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(200.0, 270.0, -200);
    glVertex3f(200.0, 330.0, -200);
    glVertex3f(200.0, 330.0, -190);
    glVertex3f(200.0, 270.0, -190);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(190.0, 270.0, -200);
    glVertex3f(190.0, 330.0, -200);
    glVertex3f(190.0, 330.0, -190);
    glVertex3f(190.0, 270.0, -190);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(200.0, 270.0, -200);
    glVertex3f(200.0, 330.0, -200);
    glVertex3f(190.0, 330.0, -200);
    glVertex3f(190.0, 270.0, -200);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(200.0, 270.0, -190);
    glVertex3f(200.0, 330.0, -190);
    glVertex3f(190.0, 330.0, -190);
    glVertex3f(190.0, 270.0, -190);
    glEnd();

    //kanan 6
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(200.0, 270.0, -140);
    glVertex3f(200.0, 330.0, -140);
    glVertex3f(200.0, 330.0, -130);
    glVertex3f(200.0, 270.0, -130);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(190.0, 270.0, -140);
    glVertex3f(190.0, 330.0, -140);
    glVertex3f(190.0, 330.0, -130);
    glVertex3f(190.0, 270.0, -130);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(200.0, 270.0, -140);
    glVertex3f(200.0, 330.0, -140);
    glVertex3f(190.0, 330.0, -140);
    glVertex3f(190.0, 270.0, -140);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(200.0, 270.0, -130);
    glVertex3f(200.0, 330.0, -130);
    glVertex3f(190.0, 330.0, -130);
    glVertex3f(190.0, 270.0, -130);
    glEnd();

    //kanan 5
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(200.0, 270.0, -80);
    glVertex3f(200.0, 330.0, -80);
    glVertex3f(200.0, 330.0, -70);
    glVertex3f(200.0, 270.0, -70);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(190.0, 270.0, -80);
    glVertex3f(190.0, 330.0, -80);
    glVertex3f(190.0, 330.0, -70);
    glVertex3f(190.0, 270.0, -70);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(200.0, 270.0, -80);
    glVertex3f(200.0, 330.0, -80);
    glVertex3f(190.0, 330.0, -80);
    glVertex3f(190.0, 270.0, -80);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(200.0, 270.0, -70);
    glVertex3f(200.0, 330.0, -70);
    glVertex3f(190.0, 330.0, -70);
    glVertex3f(190.0, 270.0, -70);
    glEnd();

    //belakang
    //belakang 1
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, -200);
    glVertex3f(-200.0, 330.0, -200);
    glVertex3f(-190.0, 330.0, -200);
    glVertex3f(-190.0, 270.0, -200);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, -190);
    glVertex3f(-200.0, 330.0, -190);
    glVertex3f(-190.0, 330.0, -190);
    glVertex3f(-190.0, 270.0, -190);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, -200);
    glVertex3f(-200.0, 330.0, -200);
    glVertex3f(-190.0, 330.0, -200);
    glVertex3f(-190.0, 270.0, -200);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, 190);
    glVertex3f(-200.0, 330.0, 190);
    glVertex3f(-190.0, 330.0, 190);
    glVertex3f(-190.0, 270.0, 190);
    glEnd();

    //kanan 2
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, 140);
    glVertex3f(-200.0, 330.0, 140);
    glVertex3f(-200.0, 330.0, 130);
    glVertex3f(-200.0, 270.0, 130);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-190.0, 270.0, 140);
    glVertex3f(-190.0, 330.0, 140);
    glVertex3f(-190.0, 330.0, 130);
    glVertex3f(-190.0, 270.0, 130);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, 140);
    glVertex3f(-200.0, 330.0, 140);
    glVertex3f(-190.0, 330.0, 140);
    glVertex3f(-190.0, 270.0, 140);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, 130);
    glVertex3f(-200.0, 330.0, 130);
    glVertex3f(-190.0, 330.0, 130);
    glVertex3f(-190.0, 270.0, 130);
    glEnd();

    //kanan 3
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, 80);
    glVertex3f(-200.0, 330.0, 80);
    glVertex3f(-200.0, 330.0, 70);
    glVertex3f(-200.0, 270.0, 70);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-190.0, 270.0, 80);
    glVertex3f(-190.0, 330.0, 80);
    glVertex3f(-190.0, 330.0, 70);
    glVertex3f(-190.0, 270.0, 70);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, 80);
    glVertex3f(-200.0, 330.0, 80);
    glVertex3f(-190.0, 330.0, 80);
    glVertex3f(-190.0, 270.0, 80);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, 70);
    glVertex3f(-200.0, 330.0, 70);
    glVertex3f(-190.0, 330.0, 70);
    glVertex3f(-190.0, 270.0, 70);
    glEnd();

    //kanan 4
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, 5);
    glVertex3f(-200.0, 330.0, 5);
    glVertex3f(-200.0, 330.0, -5);
    glVertex3f(-200.0, 270.0, -5);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-190.0, 270.0, 5);
    glVertex3f(-190.0, 330.0, 5);
    glVertex3f(-190.0, 330.0, -5);
    glVertex3f(-190.0, 270.0, -5);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, 5);
    glVertex3f(-200.0, 330.0, 5);
    glVertex3f(-190.0, 330.0, 5);
    glVertex3f(-190.0, 270.0, 5);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, -5);
    glVertex3f(-200.0, 330.0, -5);
    glVertex3f(-190.0, 330.0, -5);
    glVertex3f(-190.0, 270.0, -5);
    glEnd();

    //kanan 7
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, -200);
    glVertex3f(-200.0, 330.0, -200);
    glVertex3f(-200.0, 330.0, -190);
    glVertex3f(-200.0, 270.0, -190);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-190.0, 270.0, -200);
    glVertex3f(-190.0, 330.0, -200);
    glVertex3f(-190.0, 330.0, -190);
    glVertex3f(-190.0, 270.0, -190);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, -200);
    glVertex3f(-200.0, 330.0, -200);
    glVertex3f(-190.0, 330.0, -200);
    glVertex3f(-190.0, 270.0, -200);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, -190);
    glVertex3f(-200.0, 330.0, -190);
    glVertex3f(-190.0, 330.0, -190);
    glVertex3f(-190.0, 270.0, -190);
    glEnd();

    //kanan 6
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, -140);
    glVertex3f(-200.0, 330.0, -140);
    glVertex3f(-200.0, 330.0, -130);
    glVertex3f(-200.0, 270.0, -130);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-190.0, 270.0, -140);
    glVertex3f(-190.0, 330.0, -140);
    glVertex3f(-190.0, 330.0, -130);
    glVertex3f(-190.0, 270.0, -130);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, -140);
    glVertex3f(-200.0, 330.0, -140);
    glVertex3f(-190.0, 330.0, -140);
    glVertex3f(-190.0, 270.0, -140);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, -130);
    glVertex3f(-200.0, 330.0, -130);
    glVertex3f(-190.0, 330.0, -130);
    glVertex3f(-190.0, 270.0, -130);
    glEnd();

    //kanan 5
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, -80);
    glVertex3f(-200.0, 330.0, -80);
    glVertex3f(-200.0, 330.0, -70);
    glVertex3f(-200.0, 270.0, -70);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-190.0, 270.0, -80);
    glVertex3f(-190.0, 330.0, -80);
    glVertex3f(-190.0, 330.0, -70);
    glVertex3f(-190.0, 270.0, -70);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, -80);
    glVertex3f(-200.0, 330.0, -80);
    glVertex3f(-190.0, 330.0, -80);
    glVertex3f(-190.0, 270.0, -80);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, -70);
    glVertex3f(-200.0, 330.0, -70);
    glVertex3f(-190.0, 330.0, -70);
    glVertex3f(-190.0, 270.0, -70);
    glEnd();

    //kiri 1
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, 200);
    glVertex3f(-200.0, 330.0, 200);
    glVertex3f(-200.0, 330.0, 190);
    glVertex3f(-200.0, 270.0, 190);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-190.0, 270.0, 200);
    glVertex3f(-190.0, 330.0, 200);
    glVertex3f(-190.0, 330.0, 190);
    glVertex3f(-190.0, 270.0, 190);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, 200);
    glVertex3f(-200.0, 330.0, 200);
    glVertex3f(-190.0, 330.0, 200);
    glVertex3f(-190.0, 270.0, 200);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, 190);
    glVertex3f(-200.0, 330.0, 190);
    glVertex3f(-190.0, 330.0, 190);
    glVertex3f(-190.0, 270.0, 190);
    glEnd();

    //kanan 2
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, 140);
    glVertex3f(-200.0, 330.0, 140);
    glVertex3f(-200.0, 330.0, 130);
    glVertex3f(-200.0, 270.0, 130);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-190.0, 270.0, 140);
    glVertex3f(-190.0, 330.0, 140);
    glVertex3f(-190.0, 330.0, 130);
    glVertex3f(-190.0, 270.0, 130);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, 140);
    glVertex3f(-200.0, 330.0, 140);
    glVertex3f(-190.0, 330.0, 140);
    glVertex3f(-190.0, 270.0, 140);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, 130);
    glVertex3f(-200.0, 330.0, 130);
    glVertex3f(-190.0, 330.0, 130);
    glVertex3f(-190.0, 270.0, 130);
    glEnd();

    //kanan 3
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, 80);
    glVertex3f(-200.0, 330.0, 80);
    glVertex3f(-200.0, 330.0, 70);
    glVertex3f(-200.0, 270.0, 70);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-190.0, 270.0, 80);
    glVertex3f(-190.0, 330.0, 80);
    glVertex3f(-190.0, 330.0, 70);
    glVertex3f(-190.0, 270.0, 70);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, 80);
    glVertex3f(-200.0, 330.0, 80);
    glVertex3f(-190.0, 330.0, 80);
    glVertex3f(-190.0, 270.0, 80);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, 70);
    glVertex3f(-200.0, 330.0, 70);
    glVertex3f(-190.0, 330.0, 70);
    glVertex3f(-190.0, 270.0, 70);
    glEnd();

    //kanan 4
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, 5);
    glVertex3f(-200.0, 330.0, 5);
    glVertex3f(-200.0, 330.0, -5);
    glVertex3f(-200.0, 270.0, -5);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-190.0, 270.0, 5);
    glVertex3f(-190.0, 330.0, 5);
    glVertex3f(-190.0, 330.0, -5);
    glVertex3f(-190.0, 270.0, -5);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, 5);
    glVertex3f(-200.0, 330.0, 5);
    glVertex3f(-190.0, 330.0, 5);
    glVertex3f(-190.0, 270.0, 5);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, -5);
    glVertex3f(-200.0, 330.0, -5);
    glVertex3f(-190.0, 330.0, -5);
    glVertex3f(-190.0, 270.0, -5);
    glEnd();

    //kanan 7
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, -200);
    glVertex3f(-200.0, 330.0, -200);
    glVertex3f(-200.0, 330.0, -190);
    glVertex3f(-200.0, 270.0, -190);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-190.0, 270.0, -200);
    glVertex3f(-190.0, 330.0, -200);
    glVertex3f(-190.0, 330.0, -190);
    glVertex3f(-190.0, 270.0, -190);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, -200);
    glVertex3f(-200.0, 330.0, -200);
    glVertex3f(-190.0, 330.0, -200);
    glVertex3f(-190.0, 270.0, -200);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, -190);
    glVertex3f(-200.0, 330.0, -190);
    glVertex3f(-190.0, 330.0, -190);
    glVertex3f(-190.0, 270.0, -190);
    glEnd();

    //kanan 6
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, -140);
    glVertex3f(-200.0, 330.0, -140);
    glVertex3f(-200.0, 330.0, -130);
    glVertex3f(-200.0, 270.0, -130);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-190.0, 270.0, -140);
    glVertex3f(-190.0, 330.0, -140);
    glVertex3f(-190.0, 330.0, -130);
    glVertex3f(-190.0, 270.0, -130);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, -140);
    glVertex3f(-200.0, 330.0, -140);
    glVertex3f(-190.0, 330.0, -140);
    glVertex3f(-190.0, 270.0, -140);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, -130);
    glVertex3f(-200.0, 330.0, -130);
    glVertex3f(-190.0, 330.0, -130);
    glVertex3f(-190.0, 270.0, -130);
    glEnd();

    //kanan 5
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, -80);
    glVertex3f(-200.0, 330.0, -80);
    glVertex3f(-200.0, 330.0, -70);
    glVertex3f(-200.0, 270.0, -70);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-190.0, 270.0, -80);
    glVertex3f(-190.0, 330.0, -80);
    glVertex3f(-190.0, 330.0, -70);
    glVertex3f(-190.0, 270.0, -70);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, -80);
    glVertex3f(-200.0, 330.0, -80);
    glVertex3f(-190.0, 330.0, -80);
    glVertex3f(-190.0, 270.0, -80);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-200.0, 270.0, -70);
    glVertex3f(-200.0, 330.0, -70);
    glVertex3f(-190.0, 330.0, -70);
    glVertex3f(-190.0, 270.0, -70);
    glEnd();



    //belakang 1
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-140.0, 270.0, -200);
    glVertex3f(-140.0, 330.0, -200);
    glVertex3f(-130.0, 330.0, -200);
    glVertex3f(-130.0, 270.0, -200);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-140.0, 270.0, -190);
    glVertex3f(-140.0, 330.0, -190);
    glVertex3f(-130.0, 330.0, -190);
    glVertex3f(-130.0, 270.0, -190);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-140.0, 270.0, -200);
    glVertex3f(-140.0, 330.0, -200);
    glVertex3f(-140.0, 330.0, -190);
    glVertex3f(-140.0, 270.0, -190);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-130.0, 270.0, -200);
    glVertex3f(-130.0, 330.0, -200);
    glVertex3f(-130.0, 330.0, -190);
    glVertex3f(-130.0, 270.0, -190);
    glEnd();

    //belakang 2
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-80.0, 270.0, -200);
    glVertex3f(-80.0, 330.0, -200);
    glVertex3f(-70.0, 330.0, -200);
    glVertex3f(-70.0, 270.0, -200);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-80.0, 270.0, -190);
    glVertex3f(-80.0, 330.0, -190);
    glVertex3f(-70.0, 330.0, -190);
    glVertex3f(-70.0, 270.0, -190);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-80.0, 270.0, -200);
    glVertex3f(-80.0, 330.0, -200);
    glVertex3f(-80.0, 330.0, -190);
    glVertex3f(-80.0, 270.0, -190);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-70.0, 270.0, -200);
    glVertex3f(-70.0, 330.0, -200);
    glVertex3f(-70.0, 330.0, -190);
    glVertex3f(-70.0, 270.0, -190);
    glEnd();

    //belakang 3
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(5.0, 270.0, -200);
    glVertex3f(5.0, 330.0, -200);
    glVertex3f(-5.0, 330.0, -200);
    glVertex3f(-5.0, 270.0, -200);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(5.0, 270.0, -190);
    glVertex3f(5.0, 330.0, -190);
    glVertex3f(-5.0, 330.0, -190);
    glVertex3f(-5.0, 270.0, -190);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(5.0, 270.0, -200);
    glVertex3f(5.0, 330.0, -200);
    glVertex3f(5.0, 330.0, -190);
    glVertex3f(5.0, 270.0, -190);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-5.0, 270.0, -200);
    glVertex3f(-5.0, 330.0, -200);
    glVertex3f(-5.0, 330.0, -190);
    glVertex3f(-5.0, 270.0, -190);
    glEnd();

    //belakang 3
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(5.0, 270.0, 200);
    glVertex3f(5.0, 330.0, 200);
    glVertex3f(-5.0, 330.0, 200);
    glVertex3f(-5.0, 270.0, 200);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(5.0, 270.0, 190);
    glVertex3f(5.0, 330.0, 190);
    glVertex3f(-5.0, 330.0, 190);
    glVertex3f(-5.0, 270.0, 190);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(5.0, 270.0, 200);
    glVertex3f(5.0, 330.0, 200);
    glVertex3f(5.0, 330.0, 190);
    glVertex3f(5.0, 270.0, 190);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-5.0, 270.0, 200);
    glVertex3f(-5.0, 330.0, 200);
    glVertex3f(-5.0, 330.0, 190);
    glVertex3f(-5.0, 270.0, 190);
    glEnd();


    //belakang 1
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(140.0, 270.0, -200);
    glVertex3f(140.0, 330.0, -200);
    glVertex3f(130.0, 330.0, -200);
    glVertex3f(130.0, 270.0, -200);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(140.0, 270.0, -190);
    glVertex3f(140.0, 330.0, -190);
    glVertex3f(130.0, 330.0, -190);
    glVertex3f(130.0, 270.0, -190);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(140.0, 270.0, -200);
    glVertex3f(140.0, 330.0, -200);
    glVertex3f(140.0, 330.0, -190);
    glVertex3f(140.0, 270.0, -190);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(130.0, 270.0, -200);
    glVertex3f(130.0, 330.0, -200);
    glVertex3f(130.0, 330.0, -190);
    glVertex3f(130.0, 270.0, -190);
    glEnd();

    //belakang 2
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(80.0, 270.0, -200);
    glVertex3f(80.0, 330.0, -200);
    glVertex3f(70.0, 330.0, -200);
    glVertex3f(70.0, 270.0, -200);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(80.0, 270.0, -190);
    glVertex3f(80.0, 330.0, -190);
    glVertex3f(70.0, 330.0, -190);
    glVertex3f(70.0, 270.0, -190);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(80.0, 270.0, -200);
    glVertex3f(80.0, 330.0, -200);
    glVertex3f(80.0, 330.0, -190);
    glVertex3f(80.0, 270.0, -190);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(70.0, 270.0, -200);
    glVertex3f(70.0, 330.0, -200);
    glVertex3f(70.0, 330.0, -190);
    glVertex3f(70.0, 270.0, -190);
    glEnd();

    //depan 1
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-140.0, 270.0, 200);
    glVertex3f(-140.0, 330.0, 200);
    glVertex3f(-130.0, 330.0, 200);
    glVertex3f(-130.0, 270.0, 200);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-140.0, 270.0, 190);
    glVertex3f(-140.0, 330.0, 190);
    glVertex3f(-130.0, 330.0, 190);
    glVertex3f(-130.0, 270.0, 190);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-140.0, 270.0, 200);
    glVertex3f(-140.0, 330.0, 200);
    glVertex3f(-140.0, 330.0, 190);
    glVertex3f(-140.0, 270.0, 190);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-130.0, 270.0, 200);
    glVertex3f(-130.0, 330.0, 200);
    glVertex3f(-130.0, 330.0, 190);
    glVertex3f(-130.0, 270.0, 190);
    glEnd();

    //belakang 2
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-80.0, 270.0, 200);
    glVertex3f(-80.0, 330.0, 200);
    glVertex3f(-70.0, 330.0, 200);
    glVertex3f(-70.0, 270.0, 200);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-80.0, 270.0, 190);
    glVertex3f(-80.0, 330.0, 190);
    glVertex3f(-70.0, 330.0, 190);
    glVertex3f(-70.0, 270.0, 190);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-80.0, 270.0, 200);
    glVertex3f(-80.0, 330.0, 200);
    glVertex3f(-80.0, 330.0, 190);
    glVertex3f(-80.0, 270.0, 190);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-70.0, 270.0, 200);
    glVertex3f(-70.0, 330.0, 200);
    glVertex3f(-70.0, 330.0, 190);
    glVertex3f(-70.0, 270.0, 190);
    glEnd();

    //depan 1
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(140.0, 270.0, 200);
    glVertex3f(140.0, 330.0, 200);
    glVertex3f(130.0, 330.0, 200);
    glVertex3f(130.0, 270.0, 200);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(140.0, 270.0, 190);
    glVertex3f(140.0, 330.0, 190);
    glVertex3f(130.0, 330.0, 190);
    glVertex3f(130.0, 270.0, 190);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(140.0, 270.0, 200);
    glVertex3f(140.0, 330.0, 200);
    glVertex3f(140.0, 330.0, 190);
    glVertex3f(140.0, 270.0, 190);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(130.0, 270.0, 200);
    glVertex3f(130.0, 330.0, 200);
    glVertex3f(130.0, 330.0, 190);
    glVertex3f(130.0, 270.0, 190);
    glEnd();

    //belakang 2
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(80.0, 270.0, 200);
    glVertex3f(80.0, 330.0, 200);
    glVertex3f(70.0, 330.0, 200);
    glVertex3f(70.0, 270.0, 200);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(80.0, 270.0, 190);
    glVertex3f(80.0, 330.0, 190);
    glVertex3f(70.0, 330.0, 190);
    glVertex3f(70.0, 270.0, 190);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(80.0, 270.0, 200);
    glVertex3f(80.0, 330.0, 200);
    glVertex3f(80.0, 330.0, 190);
    glVertex3f(80.0, 270.0, 190);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(70.0, 270.0, 200);
    glVertex3f(70.0, 330.0, 200);
    glVertex3f(70.0, 330.0, 190);
    glVertex3f(70.0, 270.0, 190);
    glEnd();

    //belakang 3
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(5.0, 270.0, -200);
    glVertex3f(5.0, 330.0, -200);
    glVertex3f(-5.0, 330.0, -200);
    glVertex3f(-5.0, 270.0, -200);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(5.0, 270.0, -190);
    glVertex3f(5.0, 330.0, -190);
    glVertex3f(-5.0, 330.0, -190);
    glVertex3f(-5.0, 270.0, -190);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(5.0, 270.0, -200);
    glVertex3f(5.0, 330.0, -200);
    glVertex3f(5.0, 330.0, -190);
    glVertex3f(5.0, 270.0, -190);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.6, 0.12, 0.12);
    glVertex3f(-5.0, 270.0, -200);
    glVertex3f(-5.0, 330.0, -200);
    glVertex3f(-5.0, 330.0, -190);
    glVertex3f(-5.0, 270.0, -190);
    glEnd();
}

void pagarlantai3() {
    //bawah
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(-170.0, 580.1, -170);
    glVertex3f(-170.0, 580.1, 170);
    glVertex3f(-155.0, 580.1, 170);
    glVertex3f(-155.0, 580.1, -170);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(-170.0, 580.1, 155);
    glVertex3f(170.0, 580.1, 155);
    glVertex3f(170.0, 580.1, 170);
    glVertex3f(-170.0, 580.1, 170);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(170.0, 580.1, 170);
    glVertex3f(170.0, 580.1, -170);
    glVertex3f(155.0, 580.1, -170);
    glVertex3f(155.0, 580.1, 170);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(170.0, 580.1, -155);
    glVertex3f(-170.0, 580.1, -155);
    glVertex3f(-170.0, 580.1, -170);
    glVertex3f(170.0, 580.1, -170);
    glEnd();

    //atas
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(-170.0, 625.8, -170);
    glVertex3f(-170.0, 625.8, 170);
    glVertex3f(-155.0, 625.8, 170);
    glVertex3f(-155.0, 625.8, -170);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(-170.0, 625.8, 155);
    glVertex3f(170.0, 625.8, 155);
    glVertex3f(170.0, 625.8, 170);
    glVertex3f(-170.0, 625.8, 170);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(170.0, 625.8, 170);
    glVertex3f(170.0, 625.8, -170);
    glVertex3f(155.0, 625.8, -170);
    glVertex3f(155.0, 625.8, 170);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(170.0, 625.8, -155);
    glVertex3f(-170.0, 625.8, -155);
    glVertex3f(-170.0, 625.8, -170);
    glVertex3f(170.0, 625.8, -170);
    glEnd();

    //palang
    //1----------------kiri belakang
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 583.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 590, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 596.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 603, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 609.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 616, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 622.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    //2
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 583.5, -108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 590, -108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 596.5, -108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 603, -108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 609.5, -108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 616, -108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 622.5, -108);
    glutSolidCube(6.5);
    glPopMatrix();

    //3
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 583.5, -54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 590, -54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 596.5, -54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 603, -54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 609.5, -54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 616, -54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 622.5, -54);
    glutSolidCube(6.5);
    glPopMatrix();

    //4
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 583.5, 0);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 590, 0);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 596.5, 0);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 603, 0);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 609.5, 0);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 616, 0);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 622.5, 0);
    glutSolidCube(6.5);
    glPopMatrix();

    //5
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 583.5, 54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 590, 54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 596.5, 54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 603, 54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 609.5, 54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 616, 54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 622.5, 54);
    glutSolidCube(6.5);
    glPopMatrix();

    //6
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 583.5, 108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 590, 108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 596.5, 108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 603, 108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 609.5, 108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 616, 108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 622.5, 108);
    glutSolidCube(6.5);
    glPopMatrix();

    //7
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 583.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 590, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 596.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 603, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 609.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 616, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 622.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    //1----------------kanan belakang
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 583.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 590, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 596.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 603, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 609.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 616, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 622.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    //2
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 583.5, -108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 590, -108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 596.5, -108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 603, -108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 609.5, -108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 616, -108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 622.5, -108);
    glutSolidCube(6.5);
    glPopMatrix();

    //3
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 583.5, -54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 590, -54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 596.5, -54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 603, -54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 609.5, -54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 616, -54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 622.5, -54);
    glutSolidCube(6.5);
    glPopMatrix();

    //4
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 583.5, 0);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 590, 0);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 596.5, 0);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 603, 0);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 609.5, 0);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 616, 0);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 622.5, 0);
    glutSolidCube(6.5);
    glPopMatrix();

    //5
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 583.5, 54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 590, 54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 596.5, 54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 603, 54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 609.5, 54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 616, 54);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 622.5, 54);
    glutSolidCube(6.5);
    glPopMatrix();

    //6
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 583.5, 108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 590, 108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 596.5, 108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 603, 108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 609.5, 108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 616, 108);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 622.5, 108);
    glutSolidCube(6.5);
    glPopMatrix();

    //7
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 583.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 590, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 596.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 603, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 609.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 616, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 622.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    //palang
    //1------------------------depan
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 583.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 590, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 596.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 603, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 609.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 616, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 622.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    //2
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-108, 583.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-108, 590, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-108, 596.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-108, 603, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-108, 609.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-108, 616, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-108, 622.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    //3
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-54, 583.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-54, 590, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-54, 596.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-54, 603, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-54, 609.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-54, 616, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-54, 622.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    //4
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(0, 583.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(0, 590, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(0, 596.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(0, 603, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(0, 609.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(0, 616, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(0, 622.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    //5
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(54, 583.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(54, 590, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(54, 596.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(54, 603, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(54, 609.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(54, 616, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(54, 622.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    //6
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(108, 583.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(108, 590, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(108, 596.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(108, 603, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(108, 609.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(108, 616, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(108, 622.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    //7
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 583.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 590, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 596.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 603, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 609.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 616, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 622.5, 162);
    glutSolidCube(6.5);
    glPopMatrix();

    //palang
    //1--------------------belakang
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 583.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 590, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 596.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 603, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 609.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 616, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-162, 622.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    //2
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-108, 583.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-108, 590, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-108, 596.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-108, 603, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-108, 609.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-108, 616, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-108, 622.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    //3
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-54, 583.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-54, 590, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-54, 596.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-54, 603, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-54, 609.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-54, 616, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-54, 622.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    //4
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(0, 583.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(0, 590, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(0, 596.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(0, 603, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(0, 609.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(0, 616, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(0, 622.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    //5
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(54, 583.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(54, 590, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(54, 596.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(54, 603, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(54, 609.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(54, 616, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(54, 622.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    //6
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(108, 583.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(108, 590, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(108, 596.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(108, 603, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(108, 609.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(108, 616, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(108, 622.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    //7
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 583.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 590, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 596.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 603, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 609.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 616, -162);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(162, 622.5, -162);
    glutSolidCube(6.5);
    glPopMatrix();

}

void pagarlantai4() {
    //Bawah
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(-155.0, 785.1, -155);
    glVertex3f(-155.0, 785.1, 155);
    glVertex3f(-140.0, 785.1, 155);
    glVertex3f(-140.0, 785.1, -155);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(-155.0, 785.1, 140);
    glVertex3f(155.0, 785.1, 140);
    glVertex3f(155.0, 785.1, 155);
    glVertex3f(-155.0, 785.1, 155);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(155.0, 785.1, 155);
    glVertex3f(155.0, 785.1, -155);
    glVertex3f(140.0, 785.1, -155);
    glVertex3f(140.0, 785.1, 155);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(155.0, 785.1, -140);
    glVertex3f(-155.0, 785.1, -140);
    glVertex3f(-155.0, 785.1, -155);
    glVertex3f(155.0, 785.1, -155);
    glEnd();

    //Atas
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(-155.0, 830.6, -155);
    glVertex3f(-155.0, 830.6, 155);
    glVertex3f(-140.0, 830.6, 155);
    glVertex3f(-140.0, 830.6, -155);
    glEnd();

    glBegin(GL_POLYGON);//depan
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(-155.0, 830.6, 140);
    glVertex3f(155.0, 830.6, 140);
    glVertex3f(155.0, 830.6, 155);
    glVertex3f(-155.0, 830.6, 155);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(155.0, 830.6, 155);
    glVertex3f(155.0, 830.6, -155);
    glVertex3f(140.0, 830.6, -155);
    glVertex3f(140.0, 830.6, 155);
    glEnd();

    glBegin(GL_POLYGON);//belakang
    glColor3f(0.83, 0.07, 0.07);
    glVertex3f(155.0, 830.6, -140);
    glVertex3f(-155.0, 830.6, -140);
    glVertex3f(-155.0, 830.6, -155);
    glVertex3f(155.0, 830.6, -155);
    glEnd();

    //palang
    //1----------------kiri belakang
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 788.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 794.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 801.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 807.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 814.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 820.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 827.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    //2
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 788.3, -105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 794.8, -105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 801.3, -105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 807.8, -105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 814.3, -105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 820.8, -105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 827.3, -105);
    glutSolidCube(6.5);
    glPopMatrix();

    //3
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 788.3, -63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 794.8, -63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 801.3, -63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 807.8, -63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 814.3, -63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 820.8, -63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 827.3, -63);
    glutSolidCube(6.5);
    glPopMatrix();

    //4
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 788.3, -21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 794.8, -21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 801.3, -21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 807.8, -21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 814.3, -21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 820.8, -21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 827.3, -21);
    glutSolidCube(6.5);
    glPopMatrix();

    //5
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 788.3, 21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 794.8, 21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 801.3, 21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 807.8, 21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 814.3, 21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 820.8, 21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 827.3, 21);
    glutSolidCube(6.5);
    glPopMatrix();

    //6
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 788.3, 63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 794.8, 63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 801.3, 63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 807.8, 63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 814.3, 63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 820.8, 63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 827.3, 63);
    glutSolidCube(6.5);
    glPopMatrix();

    //7
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 788.3, 105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 794.8, 105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 801.3, 105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 807.8, 105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 814.3, 105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 820.8, 105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 827.3, 105);
    glutSolidCube(6.5);
    glPopMatrix();

    //8
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 788.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 794.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 801.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 807.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 814.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 820.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-147, 827.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    //1-----------------kanan belakang
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 788.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 794.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 801.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 807.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 814.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 820.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 827.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    //2
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 788.3, -105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 794.8, -105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 801.3, -105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 807.8, -105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 814.3, -105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 820.8, -105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 827.3, -105);
    glutSolidCube(6.5);
    glPopMatrix();

    //3
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 788.3, -63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 794.8, -63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 801.3, -63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 807.8, -63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 814.3, -63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 820.8, -63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 827.3, -63);
    glutSolidCube(6.5);
    glPopMatrix();

    //4
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 788.3, -21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 794.8, -21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 801.3, -21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 807.8, -21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 814.3, -21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 820.8, -21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 827.3, -21);
    glutSolidCube(6.5);
    glPopMatrix();

    //5
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 788.3, 21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 794.8, 21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 801.3, 21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 807.8, 21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 814.3, 21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 820.8, 21);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 827.3, 21);
    glutSolidCube(6.5);
    glPopMatrix();

    //6
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 788.3, 63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 794.8, 63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 801.3, 63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 807.8, 63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 814.3, 63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 820.8, 63);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 827.3, 63);
    glutSolidCube(6.5);
    glPopMatrix();

    //7
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 788.3, 105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 794.8, 105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 801.3, 105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 807.8, 105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 814.3, 105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 820.8, 105);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 827.3, 105);
    glutSolidCube(6.5);
    glPopMatrix();

    //8
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 788.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 794.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 801.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 807.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 814.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 820.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(147, 827.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    //1----------------------depan
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-105, 788.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-105, 794.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-105, 801.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-105, 807.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-105, 814.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-105, 820.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-105, 827.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    //2
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-63, 788.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-63, 794.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-63, 801.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-63, 807.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-63, 814.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-63, 820.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-63, 827.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    //3
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-21, 788.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-21, 794.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-21, 801.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-21, 807.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-21, 814.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-21, 820.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-21, 827.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    //4
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(21, 788.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(21, 794.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(21, 801.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(21, 807.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(21, 814.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(21, 820.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(21, 827.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    //5
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(63, 788.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(63, 794.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(63, 801.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(63, 807.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(63, 814.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(63, 820.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(63, 827.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    //6
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(105, 788.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(105, 794.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(105, 801.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(105, 807.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(105, 814.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(105, 820.8, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(105, 827.3, 147);
    glutSolidCube(6.5);
    glPopMatrix();

    //1--------------------belakang
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-105, 788.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-105, 794.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-105, 801.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-105, 807.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-105, 814.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-105, 820.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-105, 827.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    //2
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-63, 788.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-63, 794.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-63, 801.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-63, 807.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-63, 814.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-63, 820.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-63, 827.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    //3
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-21, 788.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-21, 794.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-21, 801.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-21, 807.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-21, 814.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-21, 820.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(-21, 827.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    //4
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(21, 788.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(21, 794.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(21, 801.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(21, 807.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(21, 814.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(21, 820.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(21, 827.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    //5
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(63, 788.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(63, 794.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(63, 801.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(63, 807.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(63, 814.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(63, 820.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(63, 827.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    //6
    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(105, 788.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(105, 794.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(105, 801.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(105, 807.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(105, 814.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(105, 820.8, -147);
    glutSolidCube(6.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.12, 0.12);
    glTranslatef(105, 827.3, -147);
    glutSolidCube(6.5);
    glPopMatrix();

}

void pohon() {

    //pohon 1
    glPushMatrix();
    glColor3f(0.39, 0.21, 0.01);
    glRotatef(90.0, -15000, 100, -1.0);
    glTranslatef(257, -354, 0);
    glutSolidCone(20.0, 400.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.39, 0.21, 0.01);
    glRotatef(90.0, -200, 100, -1.0);
    glTranslatef(4, -396, 231);
    glutSolidCone(5.5, 100.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.39, 0.21, 0.01);
    glRotatef(140.0, -20, -10, -1.0);
    glTranslatef(437, -87, -197);
    glutSolidCone(5.5, 100.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.39, 0.21, 0.01);
    glRotatef(85.0, -20, -10, -1.0);
    glTranslatef(423, -166.5, 48);
    glutSolidCone(5.5, 110.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.39, 0.21, 0.01);
    glRotatef(50.0, -20, -10, -1.0);
    glTranslatef(391.5, -27, 306);
    glutSolidCone(6.0, 100.0, 20, 20);
    glPopMatrix();

    //daun pohon 1
    glPushMatrix();
    glColor3f(0.96, 0.44, 0.6);
    glRotatef(90.0, -20, -10, -1.0);
    glTranslatef(481.5, -127.5, 57);
    glutSolidSphere(20.0, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.96, 0.44, 0.6);
    glRotatef(90.0, -20, -10, -1.0);
    glTranslatef(463.5, -147, 27);
    glutSolidSphere(10.0, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.96, 0.44, 0.6);
    glRotatef(90.0, -20, -10, -1.0);
    glTranslatef(427.5, -94.5, 141);
    glutSolidSphere(35.0, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.96, 0.44, 0.6);
    glRotatef(90.0, -20, -10, -1.0);
    glTranslatef(438, -129, 97.5);
    glutSolidSphere(10.0, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.96, 0.44, 0.6);
    glRotatef(90.0, -20, -10, -1.0);
    glTranslatef(499.5, -124.5, 201);
    glutSolidSphere(65.0, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.96, 0.44, 0.6);
    glRotatef(90.0, -20, -10, -1.0);
    glTranslatef(496.5, -181.5, 187.5);
    glutSolidSphere(55.0, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.96, 0.44, 0.6);
    glRotatef(90.0, -20, -10, -1.0);
    glTranslatef(424.5, -172.5, 109.5);
    glutSolidSphere(35.0, 30, 30);
    glPopMatrix();

    //pohon 2
    glPushMatrix();
    glColor3f(0.39, 0.21, 0.01);
    glRotatef(90.0, -3000, 90, -1.0);
    glTranslatef(-258, -373.5, -7.5);
    glutSolidCone(20.0, 400.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.39, 0.21, 0.01);
    glRotatef(90.0, -200, 100, -1.0);
    glTranslatef(-438, -210, 60);
    glutSolidCone(8.5, 140.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.39, 0.21, 0.01);
    glRotatef(90.0, -20, 30, -1.0);
    glTranslatef(-492, 33, -61.5);
    glutSolidCone(5.0, 80.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.39, 0.21, 0.01);
    glRotatef(140.0, -20, -10, -1.0);
    glTranslatef(150, -483, -85.5);
    glutSolidCone(7.0, 120.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.39, 0.21, 0.01);
    glRotatef(50.0, -20, -10, -1.0);
    glTranslatef(-69, -171, 456);
    glutSolidCone(7.0, 120.0, 20, 20);
    glPopMatrix();

    //daun pohon 2
    glPushMatrix();
    glColor3f(0.96, 0.44, 0.6);
    glRotatef(90.0, -20, -10, -1.0);
    glTranslatef(127.5, -363, 433.5);
    glutSolidSphere(70.0, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.96, 0.44, 0.6);
    glRotatef(90.0, -20, -10, -1.0);
    glTranslatef(52.5, -325.5, 390);
    glutSolidSphere(50.0, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.96, 0.44, 0.6);
    glRotatef(90.0, -20, -10, -1.0);
    glTranslatef(174, -342, 361.5);
    glutSolidSphere(60.0, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.96, 0.44, 0.6);
    glRotatef(90.0, -20, -10, -1.0);
    glTranslatef(96, -480, 358.5);
    glutSolidSphere(50.0, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.96, 0.44, 0.6);
    glRotatef(90.0, -20, -10, -1.0);
    glTranslatef(111, -373.5, 285);
    glutSolidSphere(15.0, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.96, 0.44, 0.6);
    glRotatef(90.0, -20, -10, -1.0);
    glTranslatef(69, -441, 294);
    glutSolidSphere(10.0, 30, 30);
    glPopMatrix();

    //pohon 3
    glPushMatrix();
    glColor3f(0.39, 0.21, 0.01);
    glRotatef(90.0, -3000, 90, -1.0);
    glTranslatef(-460.5, -193.5, -10.5);
    glutSolidCone(20.0, 400.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.39, 0.21, 0.01);
    glRotatef(90.0, -200, 100, -1.0);
    glTranslatef(-525, 25.5, -37.5);
    glutSolidCone(6.0, 90.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.39, 0.21, 0.01);
    glRotatef(10.0, -200, 120, -1.0);
    glTranslatef(-469.5, 103.5, 192);
    glutSolidCone(8.5, 140.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.39, 0.21, 0.01);
    glRotatef(50.0, -200, 120, -1.0);
    glTranslatef(-534, -9, 99);
    glutSolidCone(2.5, 40.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.39, 0.21, 0.01);
    glRotatef(-100.0, 100, 120, -1.0);
    glTranslatef(109.5, -309, 408);
    glutSolidCone(8.5, 100.0, 20, 20);
    glPopMatrix();

    //daun pohon 3
    glPushMatrix();
    glColor3f(0.96, 0.44, 0.6);
    glRotatef(90.0, -20, -10, -1.0);
    glTranslatef(-138, -316.5, 496.5);
    glutSolidSphere(70.0, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.96, 0.44, 0.6);
    glRotatef(90.0, -20, -10, -1.0);
    glTranslatef(-114, -298.5, 418.5);
    glutSolidSphere(50.0, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.96, 0.44, 0.6);
    glRotatef(90.0, -20, -10, -1.0);
    glTranslatef(-235.5, -354, 439.5);
    glutSolidSphere(60.0, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.96, 0.44, 0.6);
    glRotatef(90.0, -20, -10, -1.0);
    glTranslatef(-129, -465, 319.5);
    glutSolidSphere(15.0, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.96, 0.44, 0.6);
    glRotatef(90.0, -20, -10, -1.0);
    glTranslatef(-135, -421.5, 328.5);
    glutSolidSphere(10.0, 30, 30);
    glPopMatrix();

    //pohon 4
    glPushMatrix();
    glColor3f(0.39, 0.21, 0.01);
    glRotatef(90.0, -3000, 90, -1.0);
    glTranslatef(396, -28.5, 10.5);
    glutSolidCone(25.0, 450.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.39, 0.21, 0.01);
    glRotatef(90.0, -200, 100, -1.0);
    glTranslatef(247.5, -142.5, 345);
    glutSolidCone(9.5, 160.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.39, 0.21, 0.01);
    glRotatef(140.0, -20, -10, -1.0);
    glTranslatef(396, 202.5, 28.5);
    glutSolidCone(5.0, 80.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.39, 0.21, 0.01);
    glRotatef(-100.0, 100, 120, -1.0);
    glTranslatef(312, 376.5, -124.5);
    glutSolidCone(7.0, 120.0, 20, 20);
    glPopMatrix();
}

void pucuk() {
    //kotak
    glPushMatrix();
    glColor3f(1, 0.84, 0);
    glTranslatef(0, 1010, 0);
    glutSolidCube(85.0);
    glEnd();
    glPopMatrix();

    //tiang
    glPushMatrix();
    glColor3f(1, 0.84, 0);
    glTranslatef(0, 1200, 0);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 15.0f, 400.0f, 32, 32);
    glEnd();
    glPopMatrix();


    //cincin
    glPushMatrix();
    glColor3f(0, 0, 0.1);
    glTranslatef(0, 1060, 0);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(2.0, 15.0, 10, 10);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0.1);
    glTranslatef(0, 1090, 0);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(2.0, 15.0, 10, 10);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0.1);
    glTranslatef(0, 1120, 0);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(2.0, 15.0, 10, 10);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0.1);
    glTranslatef(0, 1150, 0);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(2.0, 15.0, 10, 10);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0.1);
    glTranslatef(0, 1180, 0);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(2.0, 15.0, 10, 10);
    glEnd();
    glPopMatrix();

    //top
    glPushMatrix();
    glColor3f(0, 0, 0.1);
    glTranslatef(0, 1210, 0);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(12.0, 0, 20, 60);
    glEnd();
    glPopMatrix();
}

void lampionlantai1() {
    //1 
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(175, 270, 175);
    glVertex3f(175, 215, 175);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(175, 215, 175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(175, 215, 175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(175, 225, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(175, 210, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(175, 210, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //2
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(175, 270, -175);
    glVertex3f(175, 215, -175);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(175, 215, -175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(175, 215, -175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(175, 225, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(175, 210, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(175, 210, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //3
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(-175, 270, -175);
    glVertex3f(-175, 215, -175);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(-175, 215, -175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(-175, 215, -175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(-175, 225, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(-175, 210, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(-175, 210, -175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //4
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(-175, 270, 175);
    glVertex3f(-175, 215, 175);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(-175, 215, 175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(-175, 215, 175);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(-175, 225, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(-175, 210, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(-175, 210, 175);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();
}

void lampionlantai2() {
    //1 // y-55 . xz+10 . kuning atas y+10 . kuning bawah y-5
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(165, 520, 165);
    glVertex3f(165, 465, 165);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(165, 465, 165);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(165, 465, 165);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(165, 475, 165);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(165, 460, 165);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(165, 460, 165);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //2
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(165, 520, -165);
    glVertex3f(165, 465, -165);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(165, 465, -165);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(165, 465, -165);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(165, 475, -165);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(165, 460, -165);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(165, 460, -165);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //3
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(-165, 520, -165);
    glVertex3f(-165, 465, -165);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(-165, 465, -165);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(-165, 465, -165);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(-165, 475, -165);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(-165, 460, -165);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(-165, 460, -165);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //4
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(-165, 520, 165);
    glVertex3f(-165, 465, 165);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(-165, 465, 165);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(-165, 465, 165);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(-165, 475, 165);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(-165, 460, 165);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(-165, 460, 165);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();
}

void lampionlantai3() {

    //1 // y-55 . xz+10 . kuning atas y+10 . kuning bawah y-5
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(155, 725, 155);
    glVertex3f(155, 670, 155);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(155, 670, 155);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(155, 670, 155);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(155, 680, 155);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(155, 665, 155);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(155, 665, 155);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //2
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(155, 725, -155);
    glVertex3f(155, 670, -155);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(155, 670, -155);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(155, 670, -155);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(155, 680, -155);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(155, 665, -155);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(155, 665, -155);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //3
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(-155, 725, -155);
    glVertex3f(-155, 670, -155);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(-155, 670, -155);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(-155, 670, -155);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(-155, 680, -155);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(-155, 665, -155);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(-155, 665, -155);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //4
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(-155, 725, 155);
    glVertex3f(-155, 670, 155);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(-155, 670, 155);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(-155, 670, 155);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(-155, 680, 155);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(-155, 665, 155);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(-155, 665, 155);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();
}

void lampionlantai4() {

    //1
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(145, 940, 145);
    glVertex3f(145, 885, 145);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(145, 885, 145);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(145, 885, 145);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(145, 895, 145);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(145, 880, 145);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(145, 880, 145);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //2
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(145, 940, -145);
    glVertex3f(145, 885, -145);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(145, 885, -145);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(145, 885, -145);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(145, 895, -145);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(145, 880, -145);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(145, 880, -145);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //3
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(-145, 940, -145);
    glVertex3f(-145, 885, -145);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(-145, 885, -145);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(-145, 885, -145);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(-145, 895, -145);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(-145, 880, -145);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(-145, 880, -145);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //4
    glBegin(GL_LINE_LOOP); //tali gantungan
    glColor3f(0, 0, 0);
    glVertex3f(-145, 940, 145);
    glVertex3f(-145, 885, 145);
    glEnd();
    glPushMatrix();//bola merah
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(-145, 885, 145);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutSolidTorus(10.0, 0.0, 20, 60);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //bola hitam
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(-145, 885, 145);
    glRotatef(90.0, 100.0, 0, -1.0);
    glutWireTorus(10.05, 0.0, 20, 12);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning atas
    glColor3f(1, 1, 0);
    glTranslatef(-145, 895, 145);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah
    glColor3f(1, 1, 0);
    glTranslatef(-145, 880, 145);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 10.0f, 32, 32);
    glEnd();
    glPopMatrix();
    glPushMatrix(); //kuning bawah 2
    glColor3f(1, 1, 0);
    glTranslatef(-145, 880, 145);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 0.5f, 0.5f, 20.0f, 32, 32);
    glEnd();
    glPopMatrix();
}

void jendela() {
   
    glBegin(GL_POLYGON);
    glColor3f(0.88, 0.82, 0.72);
    glVertex3f(-35.0, 270.0, 120.1);
    glVertex3f(-35.0, 400.0, 120.1);
    glVertex3f(35.0, 400.0, 120.1);
    glVertex3f(35.0, 270.0, 120.1);
    glEnd();

    //garis
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-35.0, 270.0, 120.1);
    glVertex3f(-35.0, 400.0, 120.1);
    glVertex3f(35.0, 400.0, 120.1);
    glVertex3f(35.0, 270.0, 120.1);
    glEnd();
   
}

void torii() {
    //kanan
    glPushMatrix();
    glColor3f(0.8, 0.3, 0.3);
    glTranslatef(166.5, 227, 883.5);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 14.0f, 14.0f, 405.0f, 32, 32);
    glEnd();
    glPopMatrix();
    //kanan-bawah
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(164.8, 55.5, 883.5);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 14.1f, 14.1f, 100.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(0.8, 0.3, 0.3);
    glTranslatef(-166.5, 227, 883.5);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 14.0f, 14.0f, 405.0f, 32, 32);
    glEnd();
    glPopMatrix();
    //kiri-bawah
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-168.2, 55.5, 883.5);
    glRotatef(90, 100, 0, -1.0);
    gluCylinder(gluNewQuadric(), 14.1f, 14.1f, 100.0f, 32, 32);
    glEnd();
    glPopMatrix();

    //balok atas depan
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.3, 0.3);
    glVertex3f(-210, 224, 900);
    glVertex3f(-220, 240, 900);
    glVertex3f(220, 240, 900);
    glVertex3f(210, 224, 900);
    glVertex3f(0, 215, 900);
    glEnd(); 

    //balok atas belakang
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.3, 0.3);
    glVertex3f(-210, 224, 868);
    glVertex3f(-220, 240, 868);
    glVertex3f(220, 240, 868);
    glVertex3f(210, 224, 868);
    glVertex3f(0, 215, 868);
    glEnd();

    //balok atas kiri
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.3, 0.3);
    glVertex3f(-210, 224, 900);
    glVertex3f(-220, 240, 900);
    glVertex3f(-220, 240, 868);
    glVertex3f(-210, 224, 868);
    glEnd();

    //balok atas kanan
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.3, 0.3);
    glVertex3f(210, 224, 900);
    glVertex3f(220, 240, 900);
    glVertex3f(220, 240, 868);
    glVertex3f(210, 224, 868);
    glEnd();

    //balok atas atas
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.3, 0.3);
    glVertex3f(-220, 240, 868);
    glVertex3f(-220, 240, 900);
    glVertex3f(220, 240, 900);
    glVertex3f(220, 240, 868);
    glEnd();

    //balok atas bawah 1
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.3, 0.3);
    glVertex3f(-210, 224, 868);
    glVertex3f(-210, 224, 900);
    glVertex3f(0, 215, 900);
    glVertex3f(0, 215, 868);
    glEnd();

    //balok atas bawah 2
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.3, 0.3);
    glVertex3f(210, 224, 868);
    glVertex3f(210, 224, 900);
    glVertex3f(0, 215, 900);
    glVertex3f(0, 215, 868);
    glEnd();

    //balok atas hitam depan
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-235, 250, 900);
    glVertex3f(-235, 240, 900);
    glVertex3f(235, 240, 900);
    glVertex3f(235, 250, 900);
    glEnd();

    //balok atas hitam belakang
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-235, 250, 868);
    glVertex3f(-235, 240, 868);
    glVertex3f(235, 240, 868);
    glVertex3f(235, 250, 868);
    glEnd();

    //balok atas hitam atas
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-235, 250, 868);
    glVertex3f(-235, 250, 900);
    glVertex3f(235, 250, 900);
    glVertex3f(235, 250, 868);
    glEnd();

    //balok atas hitam bawah
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-235, 240, 868);
    glVertex3f(-235, 240, 900);
    glVertex3f(235, 240, 900);
    glVertex3f(235, 240, 868);
    glEnd();

    //balok atas hitam kiri
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(-235, 250, 868);
    glVertex3f(-235, 240, 868);
    glVertex3f(-235, 240, 900);
    glVertex3f(-235, 250, 900);
    glEnd();

    //balok atas hitam kanan
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex3f(235, 250, 868);
    glVertex3f(235, 240, 868);
    glVertex3f(235, 240, 900);
    glVertex3f(235, 250, 900);
    glEnd();

    //balok tengah depan
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.3, 0.3);
    glVertex3f(-200, 190, 900);
    glVertex3f(-200, 170, 900);
    glVertex3f(200, 170, 900);
    glVertex3f(200, 190, 900);
    glEnd();

    //balok tengah belakang
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.3, 0.3);
    glVertex3f(-200, 190, 868);
    glVertex3f(-200, 170, 868);
    glVertex3f(200, 170, 868);
    glVertex3f(200, 190, 868);
    glEnd();

    //balok tengah kiri
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.3, 0.3);
    glVertex3f(-200, 190, 868);
    glVertex3f(-200, 170, 868);
    glVertex3f(-200, 170, 900);
    glVertex3f(-200, 190, 900);
    glEnd();

    //balok tengah kanan
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.3, 0.3);
    glVertex3f(200, 190, 868);
    glVertex3f(200, 170, 868);
    glVertex3f(200, 170, 900);
    glVertex3f(200, 190, 900);
    glEnd();

    //balok tengah atas
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.3, 0.3);
    glVertex3f(-200, 190, 868);
    glVertex3f(-200, 190, 900);
    glVertex3f(200, 190, 900);
    glVertex3f(200, 190, 868);
    glEnd();

    //balok tengah bawah
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.3, 0.3);
    glVertex3f(-200, 170, 868);
    glVertex3f(-200, 170, 900);
    glVertex3f(200, 170, 900);
    glVertex3f(200, 170, 868);
    glEnd();

    //balok tengah tengah depan
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.3, 0.3);
    glVertex3f(-15, 224, 895);
    glVertex3f(-15, 190, 895);
    glVertex3f(15, 190, 895);
    glVertex3f(15, 224, 895);
    glEnd();

    //balok tengah tengah belakang
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.3, 0.3);
    glVertex3f(-15, 224, 873);
    glVertex3f(-15, 190, 873);
    glVertex3f(15, 190, 873);
    glVertex3f(15, 224, 873);
    glEnd();

    //balok tengah tengah kiri
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.3, 0.3);
    glVertex3f(-15, 224, 873);
    glVertex3f(-15, 224, 895);
    glVertex3f(-15, 190, 895);
    glVertex3f(-15, 190, 873);
    glEnd();

    //balok tengah tengah kanan
    glBegin(GL_POLYGON);
    glColor3f(0.8, 0.3, 0.3);
    glVertex3f(15, 224, 895);
    glVertex3f(15, 224, 873);
    glVertex3f(15, 190, 873);
    glVertex3f(15, 190, 895);
    glEnd();

    // - - - -garis-garis - - - -
    
    //balok atas depan
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-210, 224, 900);
    glVertex3f(-220, 240, 900);
    glVertex3f(220, 240, 900);
    glVertex3f(210, 224, 900);
    glVertex3f(0, 215, 900);
    glEnd();

    //balok atas belakang
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-210, 224, 868);
    glVertex3f(-220, 240, 868);
    glVertex3f(220, 240, 868);
    glVertex3f(210, 224, 868);
    glVertex3f(0, 215, 868);
    glEnd();

    //balok atas kiri
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-210, 224, 900);
    glVertex3f(-220, 240, 900);
    glVertex3f(-220, 240, 868);
    glVertex3f(-210, 224, 868);
    glEnd();

    //balok atas kanan
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(210, 224, 900);
    glVertex3f(220, 240, 900);
    glVertex3f(220, 240, 868);
    glVertex3f(210, 224, 868);
    glEnd();

    //balok tengah depan
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-200, 190, 900);
    glVertex3f(-200, 170, 900);
    glVertex3f(200, 170, 900);
    glVertex3f(200, 190, 900);
    glEnd();

    //balok tengah belakang
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-200, 190, 868);
    glVertex3f(-200, 170, 868);
    glVertex3f(200, 170, 868);
    glVertex3f(200, 190, 868);
    glEnd();

    //balok tengah kiri
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-200, 190, 868);
    glVertex3f(-200, 170, 868);
    glVertex3f(-200, 170, 900);
    glVertex3f(-200, 190, 900);
    glEnd();

    //balok tengah kanan
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(200, 190, 868);
    glVertex3f(200, 170, 868);
    glVertex3f(200, 170, 900);
    glVertex3f(200, 190, 900);
    glEnd();
}

void draw() {

    lantaidasar(); //lantai dasar
    torii();

    lantai1(); //lantai 1
    pintulantai1();
    pagarlantai1();
    lampionlantai1();
    
    lantai2(); //lantai 2
    pintulantai2();
    pagarlantai2();
    lampionlantai2();

    lantai3(); //lantai 3
    pintulantai3();
    pagarlantai3();
    lampionlantai3();

    lantai4(); //lantai 4
    pintulantai4();
    pagarlantai4();
    lampionlantai4();

    // - - - //

    glPushMatrix(); //JENDELA
    glTranslatef(75, 160, 0);
    glScalef(0.9, 0.7, 1);
    jendela();
    glPopMatrix();

    glPushMatrix();//JENDELA
    glTranslatef(-75, 160, 0);
    glScalef(0.9, 0.7, 1);
    jendela();
    glPopMatrix();

    glPushMatrix();//JENDELA
    glTranslatef(-60, 490, 0);
    glScalef(0.65, 0.5, 0.75);
    jendela();
    glPopMatrix();

    glPushMatrix();//JENDELA
    glTranslatef(60, 490, 0);
    glScalef(0.65, 0.5, 0.75);
    jendela();
    glPopMatrix();

    glPushMatrix();//JENDELA
    glTranslatef(-40, 730, 0);
    glScalef(0.45, 0.4, 0.5);
    jendela();
    glPopMatrix();

    glPushMatrix();//JENDELA
    glTranslatef(40, 730, 0);
    glScalef(0.45, 0.4, 0.5);
    jendela();
    glPopMatrix();

    matahari();

    pohon();

    pucuk();

    ground();
    cout << "X_GESER = " << x_geser << " Y_GESER = " << y_geser << " Z_GESER = " << z_geser << endl;

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
        x_geser += 1.5;
        break;
    case 'j':
        x_geser -= 1.5;
        break;
    case 'o':
        y_geser += 1.5;
        break;
    case 'u':
        y_geser -= 1.5;
        break;
    case 'i':
        z_geser -= 1.5;
        break;
    case 'k':
        z_geser += 1.5;
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
    glutCreateWindow("TR GRAFKOM KELOMPOK 6");

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