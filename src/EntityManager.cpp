#include "./EntityManager.h"
#include <iostream>
#include "./Collision.h"
#include "./Components/ColliderComponent.h"

void EntityManager::ClearData() {
	for (auto& entity : entities) {
		entity->Destroy();
	}
}

bool EntityManager::HasNoEntities() {
	return entities.size() == 0;
}

void EntityManager::Update(float deltaTime) {
	for (auto& entity : entities) {
		entity->Update(deltaTime);
	}
}

void EntityManager::Render() {
	for (int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber++) {
		for (auto& entity : GetEntitiesByLayer(static_cast<LayerType>(layerNumber)))
			entity->Render();
	}
}

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer) {
	Entity* entity = new Entity(*this, entityName, layer);
	entities.emplace_back(entity);
	return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const {
	return entities;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const {
	std::vector<Entity*> selectedEntities;
	for (auto& entity : entities) {
		if (entity->layer == layer) {
			selectedEntities.emplace_back(entity);
		}
	}
	return selectedEntities;
}

unsigned int EntityManager::GetEntityCount() {
	return entities.size();
}

void EntityManager::ListAllEntities() const {
	unsigned int i = 0;
	for (auto& entity : entities) {
		std::cout << "Entity[" << i << "]: " << entity->name << std::endl;
		entity->ListAllComponents();
		i++;
	}
}

CollisionType EntityManager::CheckCollisions() const {
	for (int i = 0; i < entities.size() - 1; i++) {
		auto& thisEntity = entities[i];
		if (thisEntity->HasComponent<ColliderComponent>()) {
			ColliderComponent* thisCollider = thisEntity->GetComponent<ColliderComponent>();
			for (int j = i + 1; j < entities.size(); j++) {
				auto& thatEntity = entities[j];
				if (thisEntity->name.compare(thatEntity->name) != 0 && thatEntity->HasComponent<ColliderComponent>()) {
					ColliderComponent* thatCollider = thatEntity->GetComponent<ColliderComponent>();
					if (Collision::CheckRectangleCollision(thisCollider->collider, thatCollider->collider)) {

						if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("ENEMY") == 0) {
							return CollisionType::PLAYER_ENEMY_COLLISION;
						}

						if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("PROJECTILE") == 0) {
							return CollisionType::PLAYER_PROJECTILE_COLLISION;
						}
						
						if (thisCollider->colliderTag.compare("ENEMY") == 0 && thatCollider->colliderTag.compare("FRIENDLY_PROJECTILE") == 0) {
							return CollisionType::ENEMY_PROJECTILE_COLLISION;
						}

						if ( (thisCollider->colliderTag.compare("PLAYER") == 0) && (thatCollider->colliderTag.compare("LEVEL_COMPLETE") == 0) ) {
							return CollisionType::PLAYER_LEVEL_COMPLETE_COLLISION;
						}
					}
				}
			}
		}
	}
	return CollisionType::NO_COLLISION;
}

/*
std::string EntityManager::CheckEntityCollisions(Entity& myEntity) const {
	ColliderComponent* myCollider = myEntity.GetComponent<ColliderComponent>();
	for (auto& entity : entities) {
		if (entity->name.compare(myEntity.name) != 0 && entity->name.compare("Tile") != 0) {
			if (entity->HasComponent<ColliderComponent>()) {
				ColliderComponent* otherCollider = entity->GetComponent<ColliderComponent>();
				if (Collision::CheckRectangleCollision(myCollider->collider, otherCollider->collider)) {
					std::cout << "\n In Collision with " << otherCollider->colliderTag;
					return otherCollider->colliderTag;
				}
			}
		}
	}
	std::cout << "\n No collision ";
	return std::string();
}
*/

