#include <GL/freeglut.h>
#include <cmath>

// (cx, cy)를 중심으로 반지름이 radius인 원을 그리는 함수
void drawCircle(float cx, float cy, float radius) {
    const int numSegments = 100;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numSegments; ++i) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawSon() {

    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.55f, 0.15f); // 'ㅅ'의 왼쪽 아래 시작점
    glVertex2f(-0.5f, 0.2f);   // 'ㅅ'의 위쪽 꼭짓점
    glVertex2f(-0.45f, 0.15f); // 'ㅅ'의 오른쪽 아래 끝점
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(-0.55f, 0.0f);   // 'ㅗ'의 왼쪽 시작점
    glVertex2f(-0.45f, 0.0f);  // 'ㅗ'의 오른쪽 끝점 
    glVertex2f(-0.5f, 0.0f); // 'ㅗ'의 중앙 아래쪽 시작점 0.5
    glVertex2f(-0.5f, 0.05f); // 'ㅗ'의 중앙 아래쪽 끝점 0.5
    glEnd();
    glBegin(GL_LINES); // 'ㄴ'의 수직선과 수평선을 각각 그리기
    glVertex2f(-0.525f, -0.1f); // 'ㄴ'의 왼쪽 아래 시작점
    glVertex2f(-0.525f, -0.2f); // 'ㄴ'의 왼쪽 위 끝점
    glVertex2f(-0.525f, -0.2f); // 'ㄴ'의 위쪽 시작점
    glVertex2f(-0.475f, -0.2f);  // 'ㄴ'의 오른쪽 끝점
    glEnd();
}

void drawDong() {

    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.2f, 0.2f);   // 오른쪽 위 모서리
    glVertex2f(-0.3f, 0.2f);   // 왼쪽 위 모서리
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.3f, 0.2f);   // 왼쪽 위 모서리
    glVertex2f(-0.3f, 0.1f);   // 왼쪽 아래 모서리
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.3f, 0.1f);   // 왼쪽 아래 모서리
    glVertex2f(-0.2f, 0.1f);   // 오른쪽 아래 모서리
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-0.3f, 0.0f);   // 'ㅗ'의 왼쪽 시작점
    glVertex2f(-0.2f, 0.0f);  // 'ㅗ'의 오른쪽 끝점 
    glVertex2f(-0.25f, 0.0f); // 'ㅗ'의 중앙 아래쪽 시작점 0.5
    glVertex2f(-0.25f, 0.05f); // 'ㅗ'의 중앙 아래쪽 끝점 0.5
    glEnd();

    drawCircle(-0.25f, -0.15f, 0.05f);
}

void drawEun()
{
    drawCircle(0.0f, 0.15f, 0.05f);
    
    glBegin(GL_LINES);
    glVertex2f(-0.05f, 0.0f);   // 'ㅗ'의 왼쪽 시작점
    glVertex2f(0.05f, 0.0f);  // 'ㅗ'의 오른쪽 끝점
    glEnd();

    glBegin(GL_LINES); // 'ㄴ'의 수직선과 수평선을 각각 그리기
    glVertex2f(-0.025f, -0.1f); // 'ㄴ'의 왼쪽 아래 시작점
    glVertex2f(-0.025f, -0.2f); // 'ㄴ'의 왼쪽 위 끝점
    glVertex2f(-0.025f, -0.2f); // 'ㄴ'의 위쪽 시작점
    glVertex2f(0.025f, -0.2f);  // 'ㄴ'의 오른쪽 끝점
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 0.0f);
    drawSon();
    drawDong();
    drawEun();

    glutSwapBuffers();
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Korean Character with Lines");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
