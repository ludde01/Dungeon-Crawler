#ifndef _GAMEOBJECTMANAGER_H
#define _GAMEOBJECTMANAGER_H
#include <vector>
#include <list>
#include "Player.h"
#include "Enemies/Walker.h"
#include "Enemies/Shooter.h"
#include "Enemies/Boss.h"
#include "Powerups.h"
#include "GameObject.h"
#include "Graphics/Effects.h"
#include "Parser/Parser.h"
#include "Room.h"
#include <EnemyProjectile/ProjectileManager.h>

class Renderer;

class GameObjectManager {

public:
	GameObjectManager(Effects* effects, ProjectileManager* projectileManager);
	~GameObjectManager();


	void update(float dt);
	void addGameObject(GameObject* gameObject);
	void constructPlayerBroadPhaseBox();
	void setRendererRef(Renderer* renderer);
	Player* getPlayer() const;
	const std::vector<GameObject*>& getGameObjects() const;
	std::vector<GameObject*>* getVectorPointer();

	bool gameFinished();

	std::vector<Room*>& getClearedRooms();
	
private:
	void handlePlayerCollisionAgainstObjects(float dt, GameObject* object, glm::vec3& newVel, bool& hasCollided);
	void handlePlayerShooting(float dt, GameObject* object, const glm::vec3& rayDir, float& rayLengthUntilCollision, GameObject* &hitGameObject);
	void handleDeadEnemies(float dt);
	void handleEnemyAttacks(GameObject* object, float dt);

	
	void roomManager(GameObject* object);
	void spawner(Room* currentRoom);


private:
	int m_numberOfEnemies; //This is per room
	int m_walkerDifficulty;
	int m_shooterDifficulty;
	bool m_gameFinished;
	std::vector<GameObject*> m_gameObjects;
	Player* m_player;
	PowerUps* m_powerup;

	AABB* m_broadPhaseBox;
	glm::vec4 m_maxMinValues; 
	Effects* m_effects; 
	ProjectileManager* m_projectileManager;

	bool m_isLocked;
	std::vector<Room*> m_rooms;
	std::vector<Room*> m_roomsCleared; //these rooms are shown in the map
	int m_doorIndex;
	int m_currentRoom;

	Renderer* m_renderer;
};

#endif
