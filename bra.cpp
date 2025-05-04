#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;
int x_start, y_start, x_end, y_end; // Renamed variables to avoid conflicts

void bra(){
    float dx,dy,x,y,p;
    dx=x_end-x_start;
    dy=y_end-y_start;
    x= x_start;
    y= y_start;
    p=(2*dy)-dx;

    //plot the first point
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0); // Set color to white
    glVertex2i(x, y); // Plot the initial point
    glEnd();

    while (x < x_end) {
        if (p < 0) {
            p = p + (2 * dy);  // Move horizontally
            x++;
        } else {
            p = p + (2 * (dy - dx)); // Move diagonally
            x++;
            y++;
        }

        // Plot the point at (x, y)
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
    }    


}

void display() {

    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2.0); // Set point size for visibility
    glFlush();
    glutSwapBuffers();
}

// Initialize OpenGL
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    glMatrixMode(GL_PROJECTION);// Set projection matrix, determine how to project 3D to 2D
    glLoadIdentity();//clear previous transformation
    gluOrtho2D(0, 500, 0, 500);
     // Set coordinate system (0,0) to (500,500)
}


int main(int argc, char** argv) {
    // Get user input for endpoints
    cout << "Enter x1";
    cin>>x_start;
    cout << "Enter x2";
    cin>>x_end;
    
    cout << "Enter y1";
    cin>>y_start;
    cout << "Enter y2";
    cin>>y_end;

    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("bresanhams Line Drawing Algorithm");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}