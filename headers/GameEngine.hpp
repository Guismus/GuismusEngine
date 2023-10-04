/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** GameEngine
*/

#pragma once

#include "Utils.hpp"
#include <vector>
#include <iostream>

namespace Engine {
    class GameEngine {
        public:
            GameEngine();
            void run();
            std::vector<Engine::Signature> *getEntitySignatures() { return _entitySignatures; };
            std::vector<Engine::Entity> *getEntities() { return _entities; };
            std::vector<Engine::System> *getSystems() { return _systems; };
            Engine::eventQueue *getEvents() { return _events; };
            ~GameEngine();
        private:
            std::vector<Engine::Signature> *_entitySignatures;
            std::vector<Engine::Entity> *_entities;
            std::vector<Engine::System> *_systems;
            Engine::eventQueue *_events;
    };
};
