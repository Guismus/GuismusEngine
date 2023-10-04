/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** Utils
*/

#include "../headers/GameEngine.hpp"

Engine::Component *Engine::Component::FindComponentByType(std::string type, Engine::Entity *entity)
{
    for(int i = 0; i < entity->size(); i++) {
        if(entity->at(i).getType() == type)
            return(&(entity->at(i)));
    }
    return(new Engine::Component(nullptr, std::string("err")));
}