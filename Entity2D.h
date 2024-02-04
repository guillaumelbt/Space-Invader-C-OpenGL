#ifndef Entity2D_h 
#define Entity2D_h
#include "glm/glm.hpp"

class Entity2D
{
public:
	glm::vec3 position; 
	float angle; 
	glm::vec2 scale;

	Entity2D(); 
	Entity2D(const Entity2D& obj); 
	Entity2D(glm::vec3 pos, float angle, glm::vec2 scale); 
	~Entity2D() = default; 

	virtual void update(); 
	virtual void render();
};

#endif