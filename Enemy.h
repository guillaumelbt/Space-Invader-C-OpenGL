#ifndef Enemy_h 
#define Enemy_h

#include "glm/glm.hpp"


#include "Entity2D.h"
#include "Image.h"


class Enemy : public Entity2D
{
public:
	Image* sprite;
	int shader;
	float move_speed = 2;
	bool active = false;

	Enemy(); 
	Enemy(const Enemy& obj); 
	Enemy(glm::vec3 pos, float angle, glm::vec2 scale, Image* sprite, int shader);
	Enemy(glm::vec3 pos, float angle, glm::vec2 scale, Image* sprite);
	Enemy(glm::vec3 pos, float angle, glm::vec2 scale); 
	~Enemy() = default; 

	void update() override;
	void render() override;
	void init(glm::vec3 pos);
	
};

#endif