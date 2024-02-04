#include "glew.h"
#pragma comment(lib, "glew32.lib")
#include "freeglut.h"
#include "glm/glm.hpp"
#include "main.h"
#include "Image.h"
#include "Window.h"
#include "Input.h"
#include "GameState.h"
#include <iostream>
#include "PlayerEntity.h"
#include "Time.h"
#include <fstream>
#include <string>
#include <vector>

#ifdef NDEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

std::string filepath = "assets/";

GLuint LoadShader(const std::string& shaderPath, GLenum shaderType) {
    std::ifstream shaderFile(shaderPath);
    if (!shaderFile.is_open()) {
        std::cerr << "Failed to open " << shaderPath << std::endl;
        return 0;
    }

    std::string shaderCode((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
    shaderFile.close();

    GLuint shaderID = glCreateShader(shaderType);
    const char* codePtr = shaderCode.c_str();
    glShaderSource(shaderID, 1, &codePtr, NULL);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        std::cerr << "Error compiling shader(" << shaderPath << "): " << infoLog << std::endl;
        return 0;
    }
    return shaderID;
}

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {
    GLuint vertexShaderID = LoadShader(vertex_file_path, GL_VERTEX_SHADER);
    GLuint fragmentShaderID = LoadShader(fragment_file_path, GL_FRAGMENT_SHADER);
    if (!vertexShaderID || !fragmentShaderID) return 0;

    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        std::cerr << "Error linking program: " << infoLog << std::endl;
        return 0;
    }

    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;
}

int setup_texture_gl(int slot_id, Image* img, int format) {
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glActiveTexture(GL_TEXTURE0 + slot_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    glTexImage2D(GL_TEXTURE_2D, 0, format, img->width, img->height, 0, format, GL_UNSIGNED_BYTE, img->pixel_data);
    glGenerateMipmap(GL_TEXTURE_2D); 
    return texture_id;
}

int main(int argc, char** argv) {

	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
		glutInitWindowSize(Window::width, Window::height);
		glutCreateWindow("Arcade2D"); 

		glewInit();

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_CULL_FACE);
	}
    GLuint unlit_shader = LoadShaders((filepath + "unlit_vert.glsl").c_str(), (filepath + "unlit_frag.glsl").c_str());

	Image img1 = Image(filepath + "img1.png", 0); 
	setup_texture_gl(0, &img1, GL_RGB);

	Image img2 = Image(filepath + "img2.png", 1);
	setup_texture_gl(1, &img2, GL_RGBA);

	GameState::player = new PlayerEntity(glm::vec3(0,-0.4,0), 0, glm::vec2(0.1,0.1), &img2, unlit_shader);
	
	for (size_t i = 0; i < 1000; i++)
	{
		GameState::bullets.push_back(new Bullet(glm::vec3(0, 0, 0), 0, glm::vec2(0.05, 0.05), &img2, unlit_shader));
		GameState::enemies.push_back(new Enemy(glm::vec3(0, 0, 0), 0, glm::vec2(0.1, 0.1), &img1, unlit_shader));
	}
	GameState::startGame();
	{
		glutReshapeFunc(Window::reshape);
		glutIdleFunc(GameState::update_all);
		glutDisplayFunc(GameState::render_all); 

		Input::setupInputFuncs(); 
	}
	
	Time::start = std::chrono::steady_clock::now();

	glutMainLoop();


	return 0;
}