#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define PI 3.1415926535898

// Function to draw a circle with thickness and color
void drawCircle(float cx, float cy, float radius, float thickness, float r, float g, float b)
{
    int segments = 360;
    float angle;

    glLineWidth(thickness);  // Circle thickness
    glColor3f(r, g, b);      // Circle color

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++)
    {
        angle = 2 * PI * i / segments;
        float x = cx + cos(angle) * radius;
        float y = cy + sin(angle) * radius;
        glVertex2f(x, y);
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    float cx = 0.0f, cy = 0.0f;  // Center point

    int numCircles = 20;         // Number of concentric circles
    float maxRadius = 0.5f;      // 🔻 Smaller circles
    float minRadius = 0.05f;
    float radiusStep = (maxRadius - minRadius) / numCircles;

    float baseThickness = 1.0f;  // Base thickness

    for (int i = 0; i < numCircles; i++)
    {
        float radius = minRadius + i * radiusStep;
        float thickness = baseThickness + i * 0.35f;  // Gradual thickness increase

        // 🔴 Color gradient emphasizing red tones
        float r = 0.6f + 0.4f * sin(i * 0.3f);      // dominant red variation
        float g = 0.1f + 0.3f * fabs(sin(i * 0.25f)); // mild green
        float b = 0.1f + 0.2f * cos(i * 0.2f);      // subtle blue tint

        drawCircle(cx, cy, radius, thickness, r, g, b);
    }

    glFlush();
}

void init()
{
    glClearColor(0.05, 0.05, 0.05, 1.0); // Dark background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Coordinate plane
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Concentric Circles - Red Glow Theme");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
