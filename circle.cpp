#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#define PI 3.14159

// Center of the circle = (320, 240)
int xc = 320, yc = 240;

void plot_point(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc - y, yc - x);
    glEnd();
}

// Function to draw a circle using DDA algorithm
void dda_circle(int r) {
    float theta = 0;
    float step = PI / (4 * r); // Small angle step for smooth circle
    while (theta <= PI / 4) { // Iterate over first octant, use symmetry
        int x = r * cos(theta);
        int y = r * sin(theta);
        plot_point(x, y);
        theta += step;
    }
}

// Function to draw a circle using Bresenham's algorithm
void bresenham_circle(int r) {
    int x = 0, y = r;
    float d = 1 - r;

    plot_point(x, y); // Plot first point
    while (x < y) {
        x++;
        if (d < 0) {
            d = d + 2 * x + 1;
        } else {
            y--;
            d = d + 2 * (x - y) + 1;
        }
        plot_point(x, y);
    }
}

// Function to draw two concentric circles
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    int radius1 = 100, radius2 = 200;
    dda_circle(radius1); // Inner circle (DDA)
    bresenham_circle(radius2); // Outer circle (Bresenham)
    glFlush();
}

void Init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Yellow background
    glColor3f(0.0, 0.0, 0.0); // Red pixels
    glPointSize(2.0); // Increase point size for visibility
    gluOrtho2D(0, 640, 0, 480); // Set orthographic projection
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Concentric Circles");
    Init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}