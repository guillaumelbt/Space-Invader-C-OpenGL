#include "Entity2D.h"
#include "freeglut.h"

Entity2D::Entity2D() 
{
	position = glm::vec3(0, 0, 0);
	angle = 0;
	scale = glm::vec2(1, 1);
}

Entity2D::Entity2D(const Entity2D& obj)
{
	position = obj.position;
	angle = obj.angle;
	scale = obj.scale;
}

Entity2D::Entity2D(glm::vec3 pos, float angle, glm::vec2 scale) 
{
	this->position = pos;
	this->angle = angle;
	this->scale = scale;
}

void Entity2D::update()
{
}

void Entity2D::render()
{
	{
		glLoadIdentity();

		glRotatef(angle, 0, 0, 1); 
		glTranslatef(position.x, position.y, position.z); 
		glScalef(scale.x, scale.y, 1);
	}	
	{
		glColor3f(0, 1, 0);
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