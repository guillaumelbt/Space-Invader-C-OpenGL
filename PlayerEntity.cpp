#include "PlayerEntity.h"
#include "glew.h" 
#include "freeglut.h"
#include "Input.h"
#include <iostream>
#include "Time.h"
#include "Bullet.h"
#include "main.h"
#include "GameState.h"

PlayerEntity::PlayerEntity()
{
	position = glm::vec3(0, 0, 0);
	angle = 0;
	scale = glm::vec2(1, 1);
	sprite = NULL;
	shader = 0;
}

PlayerEntity::PlayerEntity(const PlayerEntity& obj)
{
	this->position = obj.position;
	this->angle = obj.angle;
	this->scale = obj.scale;
	this->sprite = obj.sprite;
	this->shader = obj.shader;
}

PlayerEntity::PlayerEntity(glm::vec3 pos, float angle, glm::vec2 scale, Image* sprite, int shader) 
{
	this->position = pos;
	this->angle = angle;
	this->scale = scale;
	this->sprite = sprite;
	this->shader = shader;
}

PlayerEntity::~PlayerEntity() 
{

}


void PlayerEntity::update()
{
	position.x += Input::getKey('q') * -move_speed * Time::dt;
	position.x += Input::getKey('d') * +move_speed * Time::dt;

	{
		if (Input::getKeyDown('j')) {
			Bullet* bullet = GameState::popBullet();
			bullet->init(position);
		}
	}
	
	
}

void PlayerEntity::render()
{
	{
		glLoadIdentity(); 

		glRotatef(angle, 0, 0, 1); 
		glTranslatef(position.x, position.y, position.z);
		glScalef(scale.x, scale.y, 1);
	}


	{
		glUseProgram(shader);
		glUniform1i(glGetUniformLocation(shader, "ourTexture"), sprite->texture_slot);
	}

	{
		glBegin(GL_QUADS);

		glTexCoord2f(0, 0);
		glVertex3f(-0.5, -0.5, 0);

		glTexCoord2f(1, 0);
		glVertex3f(0.5, -0.5, 0);

		glTexCoord2f(1, 1);
		glVertex3f(0.5, 0.5, 0);

		glTexCoord2f(0, 1);
		glVertex3f(-0.5, 0.5, 0);

		glEnd();
	}
}