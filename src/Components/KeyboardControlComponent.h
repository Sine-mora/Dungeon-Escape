#ifndef KEYBOARDCONTROLCOMPONENT_H
#define KEYBOARDCONTROLCOMPONENT_H

#include "../Game.h"
#include "../EntityManager.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"

class KeyboardControlComponent: public Component {
	public:
		std::string upKey;
		std::string downKey;
		std::string rightKey;
		std::string leftKey;
		std::string shootKey;
		TransformComponent* transform;
		SpriteComponent* sprite;

		KeyboardControlComponent() {

		}

		KeyboardControlComponent(std::string upKey, std::string rightKey, std::string downKey, std::string leftKey, std::string shootKey) {
			this->upKey = GetSDLKeyStringCode(upKey);
			this->rightKey = GetSDLKeyStringCode(rightKey);
			this->downKey = GetSDLKeyStringCode(downKey);
			this->leftKey = GetSDLKeyStringCode(leftKey);
			this->shootKey = GetSDLKeyStringCode(shootKey);
		}

		std::string GetSDLKeyStringCode(std::string key) {
			if (key.compare("up") == 0) return "1073741906";
			if (key.compare("down") == 0) return "1073741905";
			if (key.compare("left") == 0) return "1073741904";
			if (key.compare("right") == 0) return "1073741903";
			if (key.compare("space") == 0) return "32";
			return std::to_string(static_cast<int>(key[0]));
		}
		
		void Initialize() override {
			transform = owner->GetComponent<TransformComponent>();
			sprite = owner->GetComponent<SpriteComponent>();
		}

		void Update(float deltaTime) override {
			if (Game::event.type == SDL_KEYDOWN) {
				std::string keyCode = std::to_string(Game::event.key.keysym.sym);
				
				if (keyCode.compare(upKey) == 0) {
					transform->velocity.y = -50;
					transform->velocity.x = 0;
					sprite->Play("UpAnimation");

					//Check for out of boundary
					if (transform->position.y <= 0) {
						transform->velocity.y = 0;
						std::cout << "\nY: " << transform->position.y;
					}

				}
				if (keyCode.compare(rightKey) == 0) {
					transform->velocity.y = 0;
					transform->velocity.x = 50;
					sprite->Play("RightAnimation");

					//Check for out of boundary
					if (transform->position.x >= 768) {
						transform->velocity.x = 0;
						std::cout << "\nX: " << transform->position.x;
					}

				}
				if (keyCode.compare(downKey) == 0) {
					transform->velocity.y = 50;
					transform->velocity.x = 0;
					sprite->Play("DownAnimation");

					//Check for out of boundary
					if (transform->position.y >= 568) {
						transform->velocity.y = 0;
						std::cout << "\nY: " << transform->position.y;
					}

				}
				if (keyCode.compare(leftKey) == 0) {
					transform->velocity.y = 0;
					transform->velocity.x = -50;
					sprite->Play("LeftAnimation");

					//Check for out of boundary
					if (transform->position.x <= 0) {
						transform->velocity.x = 0;
						std::cout << "\nX: " << transform->position.x;
					}

				}
				if (keyCode.compare(shootKey) == 0) {
					//TODO...
					//Shoot missiles when the key is pressed
				}
			}

			if (Game::event.type == SDL_KEYUP) {
				std::string keyCode = std::to_string(Game::event.key.keysym.sym);

				if (keyCode.compare(upKey) == 0) {
					transform->velocity.y = 0;
				}
				if (keyCode.compare(rightKey) == 0) {
					transform->velocity.x = 0;
				}
				if (keyCode.compare(downKey) == 0) {
					transform->velocity.y = 0;
				}
				if (keyCode.compare(leftKey) == 0) {
					transform->velocity.x = 0;
				}				
			}
			

		}
};

#endif // !KEYBOARDCONTROLCOMPONENT_H
