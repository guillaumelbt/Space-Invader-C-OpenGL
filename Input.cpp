#include "Input.h"
#include "freeglut.h"
#include "Window.h"

bool Input::getkey[256] = { false }; // https://stackoverflow.com/questions/2570235/initialize-a-static-member-an-array-in-c
bool Input::getkeydown[256] = { false };
bool Input::cursor_locked = false;

void Input::setupInputFuncs()
{
	glutKeyboardFunc(key_down);
	glutKeyboardUpFunc(key_up); 
	glutSpecialFunc(special_key_down);
	glutSpecialUpFunc(special_key_up);

	glutMouseFunc(mouse_button); 
	glutMotionFunc(track_mouse_pressed); 
	glutPassiveMotionFunc(track_mouse);	
}
bool Input::getKey(int key)
{
	return getkey[key];
}

bool Input::getKeyDown(int key)
{
	return getkeydown[key];
}

void Input::ResetKeysDown()
{
	for (int i = 0; i < 256; i++)
	{
		getkeydown[i] = false;
	}
}


void Input::key_down(unsigned char key, int x, int y)
{
	if (!getkey[key]) getkeydown[key] = true;
	getkey[key] = true;

	if (key == 27)
		cursor_locked = false;
}

void Input::key_up(unsigned char key, int x, int y)
{
	getkey[key] = false;
}

void Input::special_key_down(int key, int x, int y)
{

}

void Input::special_key_up(int key, int x, int y)
{

}

void Input::mouse_button(int button, int state, int x, int y)
{
	bool left_button_down = (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN);
	if (left_button_down)
		cursor_locked = true;
}

void Input::track_mouse(int x, int y)
{
	if (!cursor_locked) return;

	if (cursor_locked && (x != Window::width / 2 || y != Window::height / 2))
		glutWarpPointer(Window::width / 2, Window::height / 2);
}

void Input::track_mouse_pressed(int x, int y)
{
	track_mouse(x, y);
}






