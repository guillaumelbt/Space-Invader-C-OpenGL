#include "Bullet.h"
#include "glew.h" 
#include "freeglut.h"
#include "Input.h"
#include <iostream>
#include "Time.h"
#include "GameState.h"



Bullet::Bullet() 
{
	position = glm::vec3(0, 0, 0);
	angle = 0;
	scale = glm::vec2(1, 1);
	sprite = NULL;
	shader = 0;
	this->active = false;
}

Bullet::Bullet(const Bullet& obj)
{
	this->position = obj.position;
	this->angle = obj.angle;
	this->scale = obj.scale;
	this->sprite = obj.sprite;
	this->shader = obj.shader;
	this->active = false;
}

Bullet::Bullet(glm::vec3 pos, float angle, glm::vec2 scale, Image* sprite, int shader) 
{
	this->position = pos;
	this->angle = angle;
	this->scale = scale;
	this->sprite = sprite;
	this->shader = shader;
	this->active = false;
}


Bullet::Bullet(glm::vec3 pos, float angle, glm::vec2 scale, Image* sprite)
{
	this->position = pos;
	this->angle = angle;
	this->scale = scale;
	this->sprite = sprite;
	this->active = false;
}


void Bullet::init(glm::vec3 pos) {
	
	position = pos;

	active = true;
	
}

void Bullet::update()
{
	position.y += move_speed * Time::dt;
	if (position.y >= 1) active = false;
	for (Enemy* enemy : GameState::enemies)
	{
		if (enemy->active) {
			

			if (position.x > enemy->position.x - enemy->scale.x &&
				position.x < enemy->position.x + enemy->scale.x &&
				position.y > enemy->position.y - enemy->scale.y &&
				position.y < enemy->position.y + enemy->scale.y) {
				GameState::depopBullet(this);
				GameState::depopEnemy(enemy);
			}

		}
	}
	
}

void Bullet::render()
{
	if (!active || !sprite) return; 

	glPushMatrix();

	glTranslatef(position.x, position.y, position.z);
	glRotatef(angle, 0, 0, 1);
	glScalef(scale.x, scale.y, 1);

	glUseProgram(shader);
	glUniform1i(glGetUniformLocation(shader, "ourTexture"), sprite->texture_slot);


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

