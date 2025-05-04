#include <GL/gl.h>   // Include OpenGL header for core graphics functions
#include <GL/glut.h> // Include GLUT for window and event handling

// Triangle vertices (individual variables, renamed to avoid math.h conflicts)
float x1 = 100, y1_coord = 100; // Vertex 1: bottom-left
float x2 = 150, y2_coord = 200; // Vertex 2: top-center
float x3 = 200, y3_coord = 100; // Vertex 3: bottom-right

// Function to draw a triangle given 3 vertices' coordinates
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);      // Start drawing a filled triangle
    glVertex2f(x1, y1);         // Specify vertex 1
    glVertex2f(x2, y2);         // Specify vertex 2
    glVertex2f(x3, y3);         // Specify vertex 3
    glEnd();                    // End drawing
}

// Function to compute reflected triangle vertices (over y = 150)
void reflection(float *rx1, float *ry1, float *rx2, float *ry2, float *rx3, float *ry3) {
    *rx1 = x1;                  // Keep x-coordinate of vertex 1
    *ry1 = -y1_coord + 300;     // Reflect y: y' = -y + 300
    *rx2 = x2;                  // Keep x-coordinate of vertex 2
    *ry2 = -y2_coord + 300;     // Reflect y
    *rx3 = x3;                  // Keep x-coordinate of vertex 3
    *ry3 = -y3_coord + 300;     // Reflect y
}

// Display function to render the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT);            // Clear screen to background color (white)
    // Draw original triangle in red
    glColor3f(1.0, 0.0, 0.0);               // Set color to red (R=1, G=0, B=0)
    drawTriangle(x1, y1_coord, x2, y2_coord, x3, y3_coord); // Draw original triangle
    // Draw reflected triangle in cyan
    glColor3f(0.0, 1.0, 1.0);               // Set color to cyan (R=0, G=1, B=1)
    float rx1, ry1_coord, rx2, ry2_coord, rx3, ry3_coord; // Reflected vertices
    reflection(&rx1, &ry1_coord, &rx2, &ry2_coord, &rx3, &ry3_coord); // Compute reflected vertices
    drawTriangle(rx1, ry1_coord, rx2, ry2_coord, rx3, ry3_coord); // Draw reflected triangle
    glFlush();                              // Force rendering to display
}

// Initialize OpenGL settings
void myinit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);      // Set background to white (R=1, G=1, B=1, A=1)
    glMatrixMode(GL_PROJECTION);            // Set matrix mode to projection
    gluOrtho2D(0, 640, 0, 480);            // Set 2D orthographic projection (x: 0-640, y: 0-480)
}

// Program entry point
int main(int argc, char **argv) {
    glutInit(&argc, argv);                  // Initialize GLUT with command-line arguments
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Single buffering, RGB color mode
    glutInitWindowSize(640, 480);           // Set window size to 640x480 pixels
    glutCreateWindow("Reflection");         // Create window with accurate title
    myinit();                               // Initialize OpenGL settings
    glutDisplayFunc(display);               // Register display callback function
    glutMainLoop();                         // Start GLUT event loop
    return 0;                               // Exit (never reached due to glutMainLoop)
}