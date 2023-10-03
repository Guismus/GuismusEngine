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
            void init(
                std::vector<Engine::Signature> entitySignatures,
                std::vector<Engine::Entity> entities,
                std::vector<Engine::System> systems,
                std::vector<Engine::ColisionSystem> colSystems,
                Engine::eventQueue events
                );
            void run();
            std::vector<Engine::Signature> *getEntitySignatures() { return _entitySignatures; };
            std::vector<Engine::Entity> *getEntities() { return _entities; };
            std::vector<Engine::System> *getSystems() { return _systems; };
            std::vector<Engine::ColisionSystem> *getColSystems() { return _colSystems; };
            Engine::eventQueue *getEvents() { return _events; };
            ~GameEngine();
        private:
            std::vector<Engine::Signature> *_entitySignatures;
            std::vector<Engine::Entity> *_entities;
            std::vector<Engine::System> *_systems;
            std::vector<Engine::ColisionSystem> *_colSystems;
            Engine::eventQueue *_events;
    };
};
