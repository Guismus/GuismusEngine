/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** Utils
*/

#pragma once

#include <functional>
#include <iostream>
#include <vector>
#include <bitset>
#include <utility>
#include <string>
#include <any>
#include <queue>

#define MAX_COMPONENTS 300

namespace Engine
{
    class Component {
        public:
            Component() = default;
            template <typename T>
            Component(const T& data) : _data(data) {}
            template <typename T>
            void setData(const T& data) {
                _data = data;
            }
            template <typename T>
            T& getData() {
                if (_data.has_value()) {
                    return std::any_cast<T&>(_data);
                } else {
                    throw std::bad_any_cast();
                }
            }
        private:
            std::any _data;
    };

    class Signature {
        public:
            Signature() {};
            std::bitset<MAX_COMPONENTS> getBits(void) {return _bits;};
            void setBits(std::bitset<MAX_COMPONENTS> bits) {_bits = bits;};
            ~Signature() {};
        private:
            std::bitset<MAX_COMPONENTS> _bits;
    };

    class Event {
        public:
            Event(std::string eventType = "", std::string eventValue = "", int eventEntity = 0): _type(eventType), _value(eventValue), _entity(eventEntity) {};
            std::string getType() {return _type;};
            void setType(std::string eventType) {_type = eventType;};
            std::string getValue() {return _value;};
            void setValue(std::string eventValue) {_value = eventValue;};
            int getEntity() {return _entity;};
            void setEntity(int eventEntity) {_entity = eventEntity;};
            ~Event() {};
        private:
            std::string _type;
            std::string _value;
            int _entity;
    };

    typedef std::vector<Component> Entity;
    typedef std::queue<Event> eventQueue;
    typedef std::pair<std::function<void (Entity*, eventQueue *)>, Signature> System;
    typedef std::pair<std::function<void (std::vector<Entity>*, int)>, Signature> ColisionSystem;
}
