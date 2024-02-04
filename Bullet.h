#ifndef Bullet_h 
#define Bullet_h
#include "glm/glm.hpp"
#include "Entity2D.h"
#include "Image.h"


class Bullet : public Entity2D
{
public:
	Image* sprite;
	int shader;
	float move_speed = 2;
	bool active = false;

	Bullet();
	Bullet(const Bullet& obj);
	Bullet(glm::vec3 pos, float angle, glm::vec2 scale, Image* sprite, int shader);
	Bullet(glm::vec3 pos, float angle, glm::vec2 scale, Image* sprite);
	Bullet(glm::vec3 pos, float angle, glm::vec2 scale); 
	~Bullet() = default;

	void update() override;
	void render() override;
	void init(glm::vec3 pos);
};

#endif