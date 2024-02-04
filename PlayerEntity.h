#ifndef PlayerEntity_h 
#define PlayerEntity_h 

#include "Entity2D.h"
#include "Image.h"

class PlayerEntity : public Entity2D 
{
public:
	Image* sprite;
	int shader;
	float move_speed = 0.5f;

	PlayerEntity();
	PlayerEntity(const PlayerEntity& obj);
	PlayerEntity(glm::vec3 pos, float angle, glm::vec2 scale, Image* sprite, int shader);
	~PlayerEntity();

	void render() override;
	void update() override;
};

#endif