#include <stdio.h>
#include <memory.h>
#include <GL/glut.h>

#define _USE_MATH_DEFINES
#include <math.h>
#define SIN(x) sin(x*M_PI / 180.)
#define COS(x) cos(x*M_PI / 180.)

static double P[12] = { 0.2,0.1,0.1,1,   0.6,0.1,0.1,1,   0.6,0.7,0.1,1 };
static double Q[12];

inline void glkMatSet(double* m,
   double m00, double m01, double m02, double m03,
   double m10, double m11, double m12, double m13,
   double m20, double m21, double m22, double m23,
   double m30, double m31, double m32, double m33)
{
   double mat[16] = { m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33 };
   memcpy(m, mat, sizeof(double) * 16);
}
inline void glkMatMult(double* m1, double* m2) {
   double n[16];
   for (int k = 0; k < 16; k++) {
      n[k] = 0;
      double* p = m1 + (k / 4) * 4;
      double* q = m2 + (k % 4);
      for (int i = 0; i < 4; i++)
         n[k] += p[i] * q[i * 4];
   }
   memcpy(m1, n, sizeof(double) * 16);
}
inline void glkMatPrint(double* m) {
   for (int i = 0; i < 4; i++) {
      printf("\t[");
      for (int j = 0; j < 4; j++)
         printf("%6.2f", m[i * 4 + j]);
      printf("]\n");
   }
   printf("\n");
}
inline void glkMatIdentyfy(double* m) {
   glkMatSet(m, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}
inline void glkMatTrans(double* m, double tx, double ty, double tz) {
   glkMatSet(m, 1, 0, 0, tx, 0, 1, 0, ty, 0, 0, 1, tz, 0, 0, 0, 1);
}
inline void glkMatScale(double* m, double sx, double sy, double sz) {
   glkMatSet(m, sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1);
}
inline void glkMatRotateZ(double* m, double a) {
   glkMatSet(m, COS(a), -SIN(a), 0, 0, SIN(a), COS(a), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}
inline void glkMatRotateX(double* m, double a) {
   glkMatSet(m, 1, 0, 0, 0, 0, COS(a), -SIN(a), 0, 0, SIN(a), COS(a), 0, 0, 0, 0, 1);
}
inline void glkMatRotateY(double* m, double a) {
   glkMatSet(m, COS(a), 0, SIN(a), 0, 0, 1, 0, 0, -SIN(a), 0, COS(a), 0, 0, 0, 0, 1);
}
inline void glkMatShearX(double* m, double dy, double dz) {
   glkMatSet(m, 1, dy, dz, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}
inline void glkMatShearY(double* m, double dx, double dz) {
   glkMatSet(m, 1, 0, 0, 0, dx, 1, dz, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}
inline void glkMatShearZ(double* m, double dx, double dy) {
   glkMatSet(m, 1, 0, 0, 0, 0, 1, 0, 0, dx, dy, 1, 0, 0, 0, 0, 1);
}
inline void glkMatSkew(double* m, double angleX, double angleY) {
    double tX = tan(angleX * M_PI / 180.0);
    double tY = tan(angleY * M_PI / 180.0);
    glkMatSet(m, 1, tX, 0, 0,  tY, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1);
}
inline void glkMatRotateAroundPoint(double* m, double a, double cx, double cy, double cz) {
    glkMatSet(m, 1, 0, 0, -cx, 0, 1, 0, -cy, 0, 0, 1, -cz, 0, 0, 0, 1);
    glkMatRotateX(m, a);
    double temp[16];
    glkMatSet(temp, 1, 0, 0, cx, 0, 1, 0, cy, 0, 0, 1, cz, 0, 0, 0, 1);
    glkMatMult(m, temp);
}
inline void glkMatScaleAroundPoint(double* m, double sx, double sy, double sz, double cx, double cy, double cz) {
    glkMatSet(m, 1, 0, 0, -cx, 0, 1, 0, -cy, 0, 0, 1, -cz, 0, 0, 0, 1);
    glkMatScale(m, sx, sy, sz);
    double temp[16];
    glkMatSet(temp, 1, 0, 0, cx, 0, 1, 0, cy, 0, 0, 1, cz, 0, 0, 0, 1);
    glkMatMult(m, temp);
}



inline void glkTransform(double* m, double* p, double* q) {
   q[0] = q[1] = q[2] = q[3] = 0;
   for (int i = 0; i < 4; i++) {
      q[0] += m[i] * p[i];
      q[1] += m[i + 4] * p[i];
      q[2] += m[i + 8] * p[i];
      q[3] += m[i + 12] * p[i];
   }
}

inline void glkLine(double x1, double y1, double z1, double x2, double y2, double z2) {
   glBegin(GL_LINES);
   glVertex3d(x1, y1, z1);
   glVertex3d(x2, y2, z2);
   glEnd();
}
inline void glkTriangle4d(double* p) {
   glBegin(GL_TRIANGLES);
   glVertex4dv(p);
   glVertex4dv(p + 4);
   glVertex4dv(p + 8);
   glEnd();
}
inline void glkCoord() {
   glBegin(GL_LINES);
   glColor3d(1, 0, 0); glVertex3d(-0.1, 0, 0); glVertex3d(1, 0, 0);
   glColor3d(0, 1, 0); glVertex3d(0, -0.1, 0); glVertex3d(0, 1, 0);
   glColor3d(0, 0, 1); glVertex3d(0, 0, -0.1); glVertex3d(0, 0, 1);
   glEnd();
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1.0, 1.0, 0.0);
   glkTriangle4d(P);
   glColor3f(0.0, 1.0, 0.1);
   glkTriangle4d(Q);
   glkCoord();
   glFlush();
}
void transformTri(double* m, double* p, double* q) {
   glkTransform(m, p, q);
   glkTransform(m, p + 4, q + 4);
    glkTransform(m, p + 8, q + 8);
}

void keyboard(unsigned char key, int x, int y) {
    double m1[16];

    if (key == 'i') {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
    else if (key == 'q')
        exit(0);
    glutPostRedisplay();
}

static double PrevX, PrevY;
void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        PrevX = x;
        PrevY = y;
    }
}
void mouseMotion(GLint x, GLint y) {
    glMatrixMode(GL_MODELVIEW);
    glRotated(x - PrevX, 0, 1, 0);
    glRotated(y - PrevY, 1, 0, 0);
    PrevX = x;
    PrevY = y;
    glutPostRedisplay();
}

void menu(int item) {
   double m1[16];
    if (item == 1) {
        glkMatTrans(m1, -1, -0.5, 0);
        glkMatPrint(m1);
        transformTri(m1, P, Q);
    }
    else if (item == 2) {
        glkMatScale(m1, 1.5, 1.2, 1.4);
        glkMatPrint(m1);
        transformTri(m1, P, Q);
    }

    else if (item == 3) {
        glkMatRotateX(m1, 60);
        glkMatPrint(m1);
        transformTri(m1, P, Q);
    }
    else if (item == 4) {
        glkMatRotateY(m1, 60);
        glkMatPrint(m1);
        transformTri(m1, P, Q);
    }
    else if (item == 5) {
        glkMatRotateZ(m1, 60);
        glkMatPrint(m1);
        transformTri(m1, P, Q);
    }
    else if (item == 6) {
         glkMatRotateAroundPoint(m1, 60, 0.2,0.1,0.1);
         glkMatPrint(m1);
         transformTri(m1, P, Q);
    }
    else if (item == 7) {
        glkMatScaleAroundPoint(m1, 1.5, 1.2, 1.4, 0.2, 0.1, 0.1);
        glkMatPrint(m1);
        transformTri(m1, P, Q);
    }
    else if (item == 8) {
        glkMatShearZ(m1, 1.5, 1.2);
        glkMatPrint(m1);
        transformTri(m1, P, Q);
    }
    else if (item == 9) { 
        glkMatSkew(m1, 30, 15);
        glkMatPrint(m1);
        transformTri(m1, P, Q);
    }
    glutPostRedisplay();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Geometric Transform");
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMotion);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutCreateMenu(menu);
    glutAddMenuEntry("t", 1);
    glutAddMenuEntry("s", 2);
    glutAddMenuEntry("x", 3);
    glutAddMenuEntry("y", 4);
    glutAddMenuEntry("z", 5);
    glutAddMenuEntry("Z", 6);
    glutAddMenuEntry("c", 7);
    glutAddMenuEntry("h", 8);
    glutAddMenuEntry("S", 9);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
}

