/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** GameEngine
*/

#include "GameEngine.hpp"

Engine::GameEngine::GameEngine() {
    this->_entities = new std::vector<Engine::Entity>;
    this->_entitySignatures = new std::vector<Engine::Signature>;
    this->_systems = new std::vector<Engine::System>;
    this->_events = new eventQueue;
}

void Engine::GameEngine::run()
{
    for (int i = 0; i < this->_systems->size(); i++) {
        for (int j = 0; j < this->_entities->size(); j++) {
            if ((this->_systems->at(i).second.getBits() | this->_entitySignatures->at(j).getBits()) == this->_entitySignatures->at(j).getBits())
                this->_systems->at(i).first(this->_entities, j, this->_events);
        }
    }
    while(_events->size()) {
        std::cerr << _events->back().getValue();
        _events->pop_back();
    }
}

Engine::GameEngine::~GameEngine() {}
