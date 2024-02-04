#include "GameState.h"
#include "freeglut.h"
#include "Input.h"
#include "Time.h"
#include "Bullet.h"
#include "Enemy.h"
#include <iostream>
#include <vector>
#include <algorithm> 

PlayerEntity* GameState::player;

std::vector<Enemy*> GameState::enemies; 
std::vector<Bullet*> GameState::bullets; 

void GameState::update_all() {
    using namespace std::chrono;

    double now = duration_cast<duration<double>>(steady_clock::now() - Time::start).count();
    Time::dt = now - Time::time;
    Time::time = now;

    player->update();

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Enemy* enemy) {
        return !(enemy->active ? enemy->update(), true : false);
        }), enemies.end());

    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet* bullet) {
        return !(bullet->active ? bullet->update(), true : false);
        }), bullets.end());

    if (getEnemyCount() == 0) startGame();
    render_all();
    Input::ResetKeysDown();
}

int GameState::getEnemyCount() {
    return std::count_if(enemies.begin(), enemies.end(), [](Enemy* enemy) {
        return enemy->active;
        });
}

void GameState::render_all() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);

    glutSetCursor(Input::cursor_locked ? GLUT_CURSOR_NONE : GLUT_CURSOR_INHERIT);
    player->render();
    for (Enemy* enemy : enemies) {
        if (enemy->active) enemy->render();
    }
    for (Bullet* bullet : bullets) {
        if (bullet->active) bullet->render();
    }
    glFinish();
}

Bullet* GameState::popBullet() {
    for (Bullet* bullet : bullets) {
        if (!bullet->active) {
            bullet->active = true; 
            return bullet;
        }
    }
    Bullet* newBullet = new Bullet();
    bullets.push_back(newBullet);
    return newBullet;
}

Enemy* GameState::popEnemy() {
    for (Enemy* enemy : enemies) {
        if (!enemy->active) {
            enemy->active = true; 
            return enemy;
        }
    }
    Enemy* newEnemy = new Enemy();
    enemies.push_back(newEnemy);
    return newEnemy;
}

void GameState::startGame() {
    std::cout << "Game started" << std::endl;
    for (size_t i = 0; i < 8; i++) {
        for (size_t j = 0; j < 4; j++) {
            Enemy* enemy = popEnemy();
            enemy->init(glm::vec3(-0.55 + i * 0.15, 0.6 + j * 0.15, 0));
        }
    }
}

void GameState::depopBullet(Bullet* bullet) {
    bullet->active = false;
}

void GameState::depopEnemy(Enemy* enemy) {
    enemy->active = false;
}