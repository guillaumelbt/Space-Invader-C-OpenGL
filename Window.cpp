#include "Window.h"
#include "freeglut.h" 

int Window::width = 800;
int Window::height = 600;

void Window::reshape(int w, int h)
{
    if (h == 0)
        h = 1;

    Window::width = w;
    Window::height = h;

    {
        glViewport(0, 0, (GLsizei)w, (GLsizei)h);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glTranslatef(0, 0, 1);
        float aspect = (GLfloat)w / (GLfloat)h;
        glOrtho(-aspect * 0.5, aspect * 0.5, -0.5, +0.5, 0.1, 1000.0); 

        glMatrixMode(GL_MODELVIEW);
    }

    glutPostRedisplay();
}