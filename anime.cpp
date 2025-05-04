#include <GL/glut.h>
#include <iostream>

float vehicleX = -0.8f; // Initial x-position of the vehicle
float speed = 0.005f;   // Speed of vehicle movement

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();// resets privious transformation
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // 2D orthographic projection
}

void drawVehicle() {
    glBegin(GL_QUADS);
    // Vehicle body (rectangle)
    glColor3f(1.0, 0.0, 0.0); // Red color
    glVertex2f(vehicleX, -0.2);
    glVertex2f(vehicleX + 0.3, -0.2);
    glVertex2f(vehicleX + 0.3, 0.0);
    glVertex2f(vehicleX, 0.0);

    // Wheels (two smaller rectangles)
    glColor3f(0.0, 1.0, 0.0); // green color
    // Left wheel
    glVertex2f(vehicleX + 0.05, -0.25);
    glVertex2f(vehicleX + 0.1, -0.25);
    glVertex2f(vehicleX + 0.1, -0.2);
    glVertex2f(vehicleX + 0.05, -0.2);
    // Right wheel
    glVertex2f(vehicleX + 0.2, -0.25);
    glVertex2f(vehicleX + 0.25, -0.25);
    glVertex2f(vehicleX + 0.25, -0.2);
    glVertex2f(vehicleX + 0.2, -0.2);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawVehicle();
    glutSwapBuffers();
}

void update(int value) {
    vehicleX += speed; // Move vehicle to the right

    // Reset position when vehicle reaches the right edge
    if (vehicleX > 1.0) {
        vehicleX = -0.8;
    }

    glutPostRedisplay(); // Request redraw
    glutTimerFunc(16, update, 0); // ~60 FPS (1000ms / 60 = ~16ms)
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("2D Vehicle Animation");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0); // Start animation
    glutMainLoop();
    return 0;
}