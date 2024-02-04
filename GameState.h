#include "Entity2D.h"
#include <vector> 
#include "PlayerEntity.h"*
#include "Bullet.h"
#include "Enemy.h"

class GameState 
{
public:
	static PlayerEntity* player;
	static std::vector<Enemy*> enemies; 
	static std::vector<Bullet*> bullets;
	
	static void update_all();
	static void render_all();
	static Bullet* popBullet();
	static Enemy* popEnemy();
	static void startGame();
	static void depopBullet(Bullet* bullet);
	static void depopEnemy(Enemy* enemy);
	static int getEnemyCount();
};

