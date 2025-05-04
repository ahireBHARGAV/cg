#include <GL/gl.h>   // Include OpenGL header for core graphics functions
#include <GL/glut.h> // Include GLUT for window and event handling

// Triangle vertices and scaling factors (individual variables, y renamed to avoid math.h conflicts)
float x1 = 100, y1_coord = 100; // Vertex 1: bottom-left
float x2 = 150, y2_coord = 200; // Vertex 2: top-center
float x3 = 200, y3_coord = 100; // Vertex 3: bottom-right
float sx = 1.5, sy = 1.5;       // Scaling factors for x and y

// Function to draw a triangle given 3 vertices' coordinates
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);      // Start drawing a filled triangle
    glVertex2f(x1, y1);         // Specify vertex 1
    glVertex2f(x2, y2);         // Specify vertex 2
    glVertex2f(x3, y3);         // Specify vertex 3
    glEnd();                    // End drawing
}

// Function to compute scaled triangle vertices
void scaling(float *sx1, float *sy1, float *sx2, float *sy2, float *sx3, float *sy3) {
    *sx1 = x1 * sx;             // Scale x-coordinate of vertex 1
    *sy1 = y1_coord * sy;       // Scale y-coordinate of vertex 1
    *sx2 = x2 * sx;             // Scale x-coordinate of vertex 2
    *sy2 = y2_coord * sy;       // Scale y-coordinate of vertex 2
    *sx3 = x3 * sx;             // Scale x-coordinate of vertex 3
    *sy3 = y3_coord * sy;       // Scale y-coordinate of vertex 3
}

// Display function to render the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT);            // Clear screen to background color (white)
    // Draw original triangle in red
    glColor3f(1.0, 0.0, 0.0);               // Set color to red (R=1, G=0, B=0)
    drawTriangle(x1, y1_coord, x2, y2_coord, x3, y3_coord); // Draw original triangle
    // Draw scaled triangle in blue
    glColor3f(0.0, 0.0, 1.0);               // Set color to blue (R=0, G=0, B=1)
    float sx1, sy1_coord, sx2, sy2_coord, sx3, sy3_coord; // Scaled vertices
    scaling(&sx1, &sy1_coord, &sx2, &sy2_coord, &sx3, &sy3_coord); // Compute scaled vertices
    drawTriangle(sx1, sy1_coord, sx2, sy2_coord, sx3, sy3_coord); // Draw scaled triangle
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
    glutCreateWindow("Scaling");            // Create window with accurate title
    myinit();                               // Initialize OpenGL settings
    glutDisplayFunc(display);               // Register display callback function
    glutMainLoop();                         // Start GLUT event loop
    return 0;                               // Exit (never reached due to glutMainLoop)
}