#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <SDL.h>
#include "../Game.h"
#include "../EntityManager.h"
#include "../Components/TransformComponent.h"


class ColliderComponent : public Component {
	public:
		std::string colliderTag;
		SDL_Rect collider;
		SDL_Rect sourceRectangle;
		SDL_Rect destinationRectangle;
		TransformComponent* transform;

		ColliderComponent(std::string colliderTag, int x, int y, int width, int height) {
			this->colliderTag = colliderTag;
			this->collider = { x, y, width,height };
		}

		void Initialize() override {
			if (owner->HasComponent<TransformComponent>()) {
				transform = owner->GetComponent<TransformComponent>();
				sourceRectangle = { 0, 0, transform->width, transform->height };
				destinationRectangle = { collider.x, collider.y, collider.w, collider.h };
			}
		}

		void Update(float deltaTime) override {
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = static_cast<int>(transform->width * transform->scale);
			collider.h = static_cast<int>(transform->height * transform->scale);

			destinationRectangle.x = collider.x - Game::camera.x;
			destinationRectangle.y = collider.y - Game::camera.y;
		}

		

		void Render() override {			
			if (Game::debug == true) {
				SDL_Rect outline = { collider.x - Game::camera.x, collider.y - Game::camera.y, collider.w, collider.h };
				SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
				SDL_RenderDrawRect(Game::renderer, &outline);
			}
		}

};

#endif // !COLLIDERCOMPONENT_H
