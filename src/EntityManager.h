#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "./Entity.h"
#include "./Component.h"
#include <vector>

class EntityManager {
	private:
		std::vector<Entity*> entities;

	public:
		void ClearData();
		void Update(float deltaTime);
		void Render();
		bool HasNoEntities();
		unsigned int GetEntityCount();
		void ListAllEntities() const;
		void DestroyInactiveEntities();

		Entity& AddEntity(std::string entityName, LayerType layer);
		std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const;
		std::vector<Entity*> GetEntities() const;
		CollisionType CheckCollisions() const;

};

#endif // !ENTITYMANAGER_H
