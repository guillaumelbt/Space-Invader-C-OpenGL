class Input 
{
public:
	static bool cursor_locked; 

	static void setupInputFuncs();
	static bool getKey(int key);
	static bool getKeyDown(int key);
	static void ResetKeysDown();

private:

	static bool getkey[256];
	static bool getkeydown[256];

	static void key_down(unsigned char key, int x, int y);
	static void key_up(unsigned char key, int x, int y);
	static void special_key_down(int key, int x, int y);
	static void special_key_up(int key, int x, int y);
	static void mouse_button(int button, int state, int x, int y);
	static void track_mouse(int x, int y);
	static void track_mouse_pressed(int x, int y);
};
