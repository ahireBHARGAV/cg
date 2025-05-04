#include <GL/glut.h>
#include <cmath>
#include <iostream>

int start_x, start_y, end_x, end_y;

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250, 250, -250, 250);
}

void drawDDALine(int x1, int y1, int x2, int y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps;
    
    if (abs(dx) > abs(dy)) {
        steps = abs(dx);
    } else {
        steps = abs(dy);
    }
    
    float x_increment = dx / steps;
    float y_increment = dy / steps;
    
    float x = x1;
    float y = y1;
    
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0);  // White color
    
    for (int i = 0; i <= steps; i++) {
        glVertex2i(round(x), round(y));
        x += x_increment;
        y += y_increment;
    }
    
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2.0);
    drawDDALine(start_x, start_y, end_x, end_y);
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    std::cout << "Enter starting point (x, y): ";
    std::cin >> start_x >> start_y;
    std::cout << "Enter ending point (x, y): ";
    std::cin >> end_x >> end_y;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Line Drawing Algorithm");
    
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}