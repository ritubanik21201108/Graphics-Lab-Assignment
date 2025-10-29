#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int x1_, y1_, x2_, y2_;
int width = 1;
int mode = 1;  // 1 = single line, 2 = thick line

// Draw one pixel
void draw_pixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Draw thick pixel cluster for line-width
void draw_thick_pixel(int x, int y, int w, int dx, int dy) {
    float length = sqrt(dx*dx + dy*dy);
    if (length == 0) length = 1; // avoid divide by zero
    float px = -dy / length;  // perpendicular X
    float py = dx / length;   // perpendicular Y

    for(int i = -w/2; i <= w/2; i++) {
        int xx = x + px * i;
        int yy = y + py * i;
        draw_pixel(xx, yy);
    }
}

// Bresenham Line Algorithm (with optional thickness)
void draw_line(int x1, int y1, int x2, int y2, int w, int thick_mode) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while(1) {
        if (thick_mode == 1)
            draw_pixel(x1, y1);
        else
            draw_thick_pixel(x1, y1, w, x2 - x1, y2 - y1);

        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}

void myInit() {
    glClearColor(0, 0, 0, 1); // Black background
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 0, 0); // 🔴 Red color line
    glPointSize(1.0);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    draw_line(x1_, y1_, x2_, y2_, width, mode);
    glFlush();
}

int main(int argc, char **argv) {
    printf("=== Bresenham Line Drawing Simulator ===\n");
    printf("1. Single Line\n");
    printf("2. Thick Line\n");
    printf("Choose option (1 or 2): ");
    scanf("%d", &mode);

    printf("Enter coordinates (x1, y1, x2, y2): ");
    scanf("%d %d %d %d", &x1_, &y1_, &x2_, &y2_);

    if (mode == 2) {
        printf("Enter line width: ");
        scanf("%d", &width);
    } else {
        width = 1;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Line Drawing Simulator (Red Line)");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();
}

