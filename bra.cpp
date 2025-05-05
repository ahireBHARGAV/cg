#include <GL/glut.h>
#include <iostream>
#include <cstdlib> // For abs

using namespace std;
int x_start, y_start, x_end, y_end; // Line endpoints

// Bresenham's line drawing algorithm
void lineBres(int x1, int y1, int x2, int y2) {
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0); // White line

    GLint dx = abs(x2 - x1);
    GLint dy = abs(y2 - y1);
    GLint p = 2 * dy - dx;
    GLint twoDy = 2 * dy;
    GLint twoDyMinusDx = 2 * (dy - dx);
    GLint x, y;
    GLint xe = x2;

    if (x1 > x2) {
        x = x2;
        y = y2;
        x2 = x1;
    } else {
        x = x1;
        y = y1;
    }

    glVertex2i(x, y); // Plot initial point

    while (x < x2) {
        x++;
        if (p < 0)//p -ve
            p =p+ twoDy;
        else {//p +ve
            y++; // Increment y
            p =p+ twoDyMinusDx;
        }
        glVertex2i(x, y); // Plot point
    }

    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2.0); // Point size
    lineBres(x_start, y_start, x_end, y_end); // Draw line
    glutSwapBuffers();
}

// Initialize OpenGL
void myinit() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0); // Coordinate system
}

// Main function
int main(int argc, char** argv) {
    cout << "Enter x1: ";
    cin >> x_start;
    cout << "Enter y1: ";
    cin >> y_start;
    cout << "Enter x2: ";
    cin >> x_end;
    cout << "Enter y2: ";
    cin >> y_end;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Bresenham's Line");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
