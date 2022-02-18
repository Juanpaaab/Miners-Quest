#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;


Manager manager;
auto& player(manager.addEntity());
auto& wall(manager.addEntity());

Game::Game(){
}
Game::~Game(){
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen){
    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "SDL inicio bien" << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if(window){
            std::cout << "Ventana se creo bien" << std::endl;
        }else{
            std::cout << "Ventana NO se creo bien" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer se creo bien" << std::endl;

        }
        isRunning = true;
        
    }else{
        isRunning = false;
    }
    map = new Map();

    player.addComponent<TransformComponent>(2);
    player.addComponent<SpriteComponent>("Sprites/quieto.png");
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");

    wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
    wall.addComponent<SpriteComponent>("Sprites/brick.png");
    wall.addComponent<ColliderComponent>("wall");

    
}

void Game::handleEvents(){
    
    SDL_PollEvent(&event);
    switch (event.type){
        case SDL_QUIT:
            isRunning = false;
        break;
    }
}

void Game::update(){
    manager.refresh();
    manager.update();
    if(Collision::AABB(player.getComponent<ColliderComponent>().collider, 
                       wall.getComponent<ColliderComponent>().collider))
        {   
            player.getComponent<TransformComponent>().scale = 1;
            std::cout << "Wall hit" << std::endl;
        }

}

void Game::render(){
    SDL_RenderClear(renderer);
    //Aquí se agrega cosas para renderizar
    map -> DrawMap();
    manager.draw();
    //
    SDL_RenderPresent(renderer);
}
void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}
