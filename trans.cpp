#include <GL/gl.h>   // Include OpenGL header for core graphics functions
#include <GL/glut.h> // Include GLUT for window, event, and menu handling
#include <math.h>    // Include math.h for sin, cos, and PI

// Define PI for rotation calculations
#define PI 3.14159265358979323846

// Triangle vertices and transformation parameters
float x1 = 100, y1_coord = 100; // Vertex 1: bottom-left
float x2 = 150, y2_coord = 200; // Vertex 2: top-center
float x3 = 200, y3_coord = 100; // Vertex 3: bottom-right
float sx = 1.5, sy = 1.5;       // Scaling factors
float tx = 50, ty = 50;         // Translation offsets
float theta = 45.0;             // Rotation angle (degrees)
float sh = 0.5;                 // Shear parameter
int operation = 0;              // Current operation: 0=original, 1=scale, 2=rotate, 3=translate, 4=x-shear, 5=y-shear

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

// Function to compute rotated triangle vertices (2D, around origin)
void rotation(float *rx1, float *ry1, float *rx2, float *ry2, float *rx3, float *ry3) {
    float rad = theta * PI / 180.0; // Convert degrees to radians
    *rx1 = x1 * cos(rad) - y1_coord * sin(rad); // Rotate x: x' = x*cos(θ) - y*sin(θ)
    *ry1 = x1 * sin(rad) + y1_coord * cos(rad); // Rotate y: y' = x*sin(θ) + y*cos(θ)
    *rx2 = x2 * cos(rad) - y2_coord * sin(rad); // Rotate x for vertex 2
    *ry2 = x2 * sin(rad) + y2_coord * cos(rad); // Rotate y for vertex 2
    *rx3 = x3 * cos(rad) - y3_coord * sin(rad); // Rotate x for vertex 3
    *ry3 = x3 * sin(rad) + y3_coord * cos(rad); // Rotate y for vertex 3
}

// Function to compute translated triangle vertices
void translation(float *tx1, float *ty1, float *tx2, float *ty2, float *tx3, float *ty3) {
    *tx1 = x1 + tx;             // Translate x: x' = x + tx
    *ty1 = y1_coord + ty;       // Translate y: y' = y + ty
    *tx2 = x2 + tx;             // Translate x for vertex 2
    *ty2 = y2_coord + ty;       // Translate y for vertex 2
    *tx3 = x3 + tx;             // Translate x for vertex 3
    *ty3 = y3_coord + ty;       // Translate y for vertex 3
}

// Function to compute x-axis sheared triangle vertices
void shearX(float *sx1, float *sy1, float *sx2, float *sy2, float *sx3, float *sy3) {
    *sx1 = x1 + sh * y1_coord;  // Shear x: x' = x + sh*y
    *sy1 = y1_coord;            // Keep y unchanged
    *sx2 = x2 + sh * y2_coord;  // Shear x for vertex 2
    *sy2 = y2_coord;            // Keep y unchanged
    *sx3 = x3 + sh * y3_coord;  // Shear x for vertex 3
    *sy3 = y3_coord;            // Keep y unchanged
}

// Function to compute y-axis sheared triangle vertices
void shearY(float *sx1, float *sy1, float *sx2, float *sy2, float *sx3, float *sy3) {
    *sx1 = x1;                  // Keep x unchanged
    *sy1 = y1_coord + sh * x1;  // Shear y: y' = y + sh*x
    *sx2 = x2;                  // Keep x unchanged
    *sy2 = y2_coord + sh * x2;  // Shear y for vertex 2
    *sx3 = x3;                  // Keep x unchanged
    *sy3 = y3_coord + sh * x3;  // Shear y for vertex 3
}

// Menu callback function to select operation
void menu(int value) {
    operation = value;          // Set the selected operation (0=original, 1=scale, 2=rotate, 3=translate, 4=x-shear, 5=y-shear)
    glutPostRedisplay();        // Request redraw to update the display
}

// Display function to render the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT);            // Clear screen to background color (white)
    // Draw original triangle in red
    glColor3f(1.0, 0.0, 0.0);               // Set color to red
    drawTriangle(x1, y1_coord, x2, y2_coord, x3, y3_coord); // Draw original triangle
    // Draw transformed triangle in blue (based on selected operation)
    glColor3f(0.0, 0.0, 1.0);               // Set color to blue
    float tx1, ty1_coord, tx2, ty2_coord, tx3, ty3_coord; // Transformed vertices
    if (operation == 1) {                   // Scaling
        scaling(&tx1, &ty1_coord, &tx2, &ty2_coord, &tx3, &ty3_coord);
    } else if (operation == 2) {            // Rotation
        rotation(&tx1, &ty1_coord, &tx2, &ty2_coord, &tx3, &ty3_coord);
    } else if (operation == 3) {            // Translation
        translation(&tx1, &ty1_coord, &tx2, &ty2_coord, &tx3, &ty3_coord);
    } else if (operation == 4) {            // X-axis shear
        shearX(&tx1, &ty1_coord, &tx2, &ty2_coord, &tx3, &ty3_coord);
    } else if (operation == 5) {            // Y-axis shear
        shearY(&tx1, &ty1_coord, &tx2, &ty2_coord, &tx3, &ty3_coord);
    }
    if (operation != 0) {                   // Draw transformed triangle if not original
        drawTriangle(tx1, ty1_coord, tx2, ty2_coord, tx3, ty3_coord);
    }
    glFlush();                              // Force rendering to display
}

// Initialize OpenGL settings
void myinit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);      // Set background to white
    glMatrixMode(GL_PROJECTION);            // Set matrix mode to projection
    gluOrtho2D(0, 640, 0, 480);            // Set 2D orthographic projection (x: 0-640, y: 0-480)
}

// Program entry point
int main(int argc, char **argv) {
    glutInit(&argc, argv);                  // Initialize GLUT with command-line arguments
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Single buffering, RGB color mode
    glutInitWindowSize(640, 480);           // Set window size to 640x480 pixels
    glutCreateWindow("Triangle Transformations"); // Create window with descriptive title
    myinit();                               // Initialize OpenGL settings
    // Create right-click menu
    glutCreateMenu(menu);                   // Create menu with callback function
    glutAddMenuEntry("Original Triangle", 0); // Option 0: Show only original triangle
    glutAddMenuEntry("Scale", 1);           // Option 1: Show scaled triangle
    glutAddMenuEntry("Rotate", 2);          // Option 2: Show rotated triangle
    glutAddMenuEntry("Translate", 3);       // Option 3: Show translated triangle
    glutAddMenuEntry("Shear X-axis", 4);    // Option 4: Show x-axis sheared triangle
    glutAddMenuEntry("Shear Y-axis", 5);    // Option 5: Show y-axis sheared triangle
    glutAttachMenu(GLUT_RIGHT_BUTTON);      // Attach menu to right mouse button
    glutDisplayFunc(display);               // Register display callback function
    glutMainLoop();                         // Start GLUT event loop
    return 0;                               // Exit (never reached)
}