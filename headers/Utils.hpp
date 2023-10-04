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

#define MAX_COMPONENTS 300

namespace Engine
{
    class Component;
    typedef std::vector<Component> Entity;
    class Component {
        public:
            static Component *FindComponentByType(std::string type, Entity *entity);
            Component() = default;
            template <typename T>
            Component(const T& data, std::string type) : _data(data), _type(type) {}
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
            std::string getType() {return _type;};
        private:
            std::any _data;
            std::string _type;
    };

    class Signature {
        public:
            Signature() {};
            Signature(std::bitset<MAX_COMPONENTS> bits) { _bits = bits; };
            std::bitset<MAX_COMPONENTS> getBits(void) {return _bits;};
            void setBits(std::bitset<MAX_COMPONENTS> bits) {_bits = bits;};
            ~Signature() {};
        private:
            std::bitset<MAX_COMPONENTS> _bits;
    };

    class Event {
        public:
            Event(int eventType = -1, int eventValue = -1, int owner = -1): _type(eventType), _value(eventValue), _owner(owner) {};
            int getType()const {return _type;};
            void setType(int eventType) {_type = eventType;};
            int getValue() const {return _value;};
            void setValue(int eventValue) {_value = eventValue;};
            int getOwner() const {return _owner;};
            void setOwner(int owner) {_owner = owner;};
            bool operator==(const Event &other) {return(this->_type  == other.getType()
                                                     && this->_value == other.getValue()
                                                     && this->_owner == other.getOwner()
                                                );};
            ~Event() {};
        private:
            int _type;
            int _value;
            int _owner;
    };

    //typedef std::vector<Component> Entity;
    typedef std::vector<Event> eventQueue;
    typedef std::pair<std::function<void (std::vector<Entity>*, int, eventQueue*)>, Signature> System;
}
