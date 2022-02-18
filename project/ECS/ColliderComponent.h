#pragma once
#include <string>
#include "SDL2/SDL.h"
#include "Components.h"

class ColliderComponent : public Component{
    public:
        SDL_Rect collider;
        std::string tag;

        TransformComponent* transform;

        ColliderComponent(std::string t)
        {
            tag = t;
        }

        void init() override{
            if(!entity -> hasComponent<TransformComponent>()){
                entity -> addComponent<TransformComponent>();
            }
            transform = &entity -> getComponent<TransformComponent>();
        }

        void update() override{
            collider.x = static_cast<int>(transform -> position.x);
            collider.y = static_cast<int>(transform -> position.y);

            collider.h = transform -> height * transform -> scale;
            collider.w = transform -> width * transform -> scale;
        }
};