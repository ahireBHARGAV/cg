#include <GL/glut.h>
#include <math.h>

// Global variables for triangle vertices (renamed to avoid conflict with math.h)
int x1 = 200, y1_coord = 100;  // Bottom vertex
int x2 = 100, y2_coord = 300;  // Left vertex
int x3 = 300, y3_coord = 300;  // Right vertex
bool fill = false;             // Flag to fill the triangle

// Function to calculate area of triangle
float area(int x1, int y1, int x2, int y2, int x3, int y3) {
    return fabs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}

// Check if (x, y) point is inside the triangle
bool isInside(int x, int y) {
    float A = area(x1, y1_coord, x2, y2_coord, x3, y3_coord);
    float A1 = area(x, y, x2, y2_coord, x3, y3_coord);
    float A2 = area(x1, y1_coord, x, y, x3, y3_coord);
    float A3 = area(x1, y1_coord, x2, y2_coord, x, y);
    return (fabs(A - (A1 + A2 + A3)) < 1e-6); // Tolerance for floating-point
}

// Draw triangle (filled or just outline)
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (fill)
        glColor3f(0.3, 0.7, 1.0); // Fill with blue
    else
        glColor3f(0.0, 0.0, 0.0); // Outline in black

    glBegin(fill ? GL_TRIANGLES : GL_LINE_LOOP);
    glVertex2i(x1, y1_coord); // Bottom
    glVertex2i(x2, y2_coord); // Left
    glVertex2i(x3, y3_coord); // Right
    glEnd();

    glFlush();
}

// Mouse click function
void mouse(int button, int state, int mx, int my) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        my = 480 - my; // Convert Y from window to OpenGL
        if (isInside(mx, my)) {
            fill = true;
            glutPostRedisplay(); // Redraw the screen
        }
    }
}

// Setup OpenGL
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    gluOrtho2D(0, 640, 0, 480);      // 2D view
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Click Inside Triangle to Fill");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}