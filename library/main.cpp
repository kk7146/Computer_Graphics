#include "glk.h"

static double P[12] = { 0.2,0.1,0.1,1,   0.6,0.1,0.1,1,   0.6,0.7,0.1,1 };
static double Q[12];

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

