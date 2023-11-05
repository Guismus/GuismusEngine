# guismusEngine Documentation

## Requirement:
guismusEngine uses several features from c++20, you must use C+++20 or later.

## Introduction
The guismusEngine is a flexible Entity-Component-System (ECS) based game engine designed to provide developers with the tools needed to create highly modular and scalable games. The engine prioritizes flexibility, allowing developers to define their own entities, systems, and events, with minimal limitations. This documentation provides an overview of how to use the engine and outlines the principles to follow when designing games.

## Getting Started
To start using the guismusEngine, follow these steps:

Include the GameEngine header file:
#include "GameEngine"

Create an instance of the GameEngine class to get started:
Engine::GameEngine engine;

## Entities and Components
In the guismusEngine, entities are collections of components. Components are created using templated functions to match any data type, providing flexibility in defining component data. Here's how to work with entities and components:

You must first define diverse component types as an enum. For example:

    enum ComponentTypes {
    EntityType          = 1,
    VelocityComponent   = 1 << 1,
    DrawableComponent   = 1 << 2,
    SizeComponent       = 1 << 3,
    PositionComponent   = 1 << 4,
    };

the bitshifting will help later for constructing the entities signatures.

note that there is a limit of 300 different Component types, due to a limitation in bitsets. 

then, you must create your components.
It is recommanded to use a factory, as such:

    class ComponentsFactory
    {
    public:
        static Engine::Component entityType(EntityList entityType)                  { return Engine::Component(entityType, "EntityType"); }
        static Engine::Component velocityComponent(int velocity)                    { return Engine::Component(velocity, "Velocity"); };
        static Engine::Component drawableComponent()                                { return Engine::Component(true, "Drawable"); };
        static Engine::Component sizeComponent(std::pair<int, int> widthHeightSize) { return Engine::Component(widthHeightSize, "Size"); };
        static Engine::Component positionComponent(std::pair<int, int> XYPosition)  { return Engine::Component(XYPosition, "Position"); };
    };
Note that you may use any type to construct a component, even custom ones (here, entityList is an enum of possible entity types).

Once you have defined and created Components, you may create entities using the Entity class, which is essentially a vector of components. For example:

      Engine::Entity spaceship;
      spaceship.push_back(ComponentsFactory::entityType(SPACESHIP));
      spaceship.push_back(ComponentsFactory::velocityComponent(10));
      spaceship.push_back(ComponentsFactory::drawableComponent());
      spaceship.push_back(ComponentsFactory::sizeComponent(std::pair<int, int>(100, 100)));
      spaceship.push_back(ComponentsFactory::controllerComponent(controllerId));
      spaceship.push_back(ComponentsFactory::positionComponent(position));

You might want to also create a factory for your Entities.


## Systems
Register systems along with their corresponding signatures before running the engine. Systems are functions that operate on entities with specific signatures. Register systems like this:

    engine.getSystems()->push_back(RenderSystemFunction, renderSystemSignature);

Replace RenderSystemFunction with the actual function that defines your system's behavior. to do so, you must use a

    std::function<void (std::vector<Entity>*, int, eventQueue*, std::vector<Signature>*)>

that function must return void, and take in pointers to the entity vector, an int, a pointer to the event queue and entity signature list.
* The int represent the index of the entity that the system was called on.
* The full vector of entities is needed for function that might need to have an effect or check on other entities (for example, collisions)
* The event queue may also carry such information, or you may use it for I/O operations, like networking.
* The signatures are needed for if you need to erase or create an entity (or, possibly, change its components)

In systems, you may access an entity's component using
    
    Engine::Component::FindComponentByType
and then access the data using

    component->getData<T>();
    
for example: 

    Engine::Component *positioncmp = Engine::Component::FindComponentByType("Position", entity);
    positioncmp->getData<std::pair<int, int>>();

note the use of the string "Position" to determine the type, which is why you fill it out when creating a component like we did previously (this is because the engine can't compare components by types, only by strings, and then cast it from a std::any, supposing the right type has been found. using getData with the wrong template will throw std::bad_any_cast();

## Signatures
To specify which systems should operate on specific entities, use entity signatures. Signatures are bitsets that describe the required components for an entity to be processed by a specific system. 
the check for wether to call a system on an entity is as follows:

    system.signature | entity.signature == entity.signature

This means that you may call a system on all entities that have the required components, but those entities may have extraneous components.

Tip: If there is anything you need to happen exactly once per tick, but isn't really carried by any game object, you may just create matching "rules" component and system, with exactly one entity in the game whose sole purpose is to carry that component, so that it will be called by the matching system.

Since guismusEngine leaves your the responsability of looping over the GameEngine::run() function, you may also add code in between ticks. this may be removed in later versions.

### Here's how to use signatures:

* For Entities :
When you create an entity, you need to fill in the Signature vector in the engine, at the same index. In later versions, they will be handled in pairs similar to systems.
using the spaceship example, when put in a factory function:

        void EntityFactory::buildSpaceshipEntity(std::vector<Engine::Entity> *entities, std::vector<Engine::Signature> *signatures, std::pair<int,int> position)
        {
        Engine::Signature signature;
        Engine::Entity spaceship;
        spaceship.push_back(ComponentsFactory::entityType(SPACESHIP));
        spaceship.push_back(ComponentsFactory::velocityComponent(10));
        spaceship.push_back(ComponentsFactory::drawableComponent());
        spaceship.push_back(ComponentsFactory::sizeComponent(std::pair<int, int>(100, 100)));
        spaceship.push_back(ComponentsFactory::positionComponent(position));
        signature.setBits(EntityType | VelocityComponent | DrawableComponent | SizeComponent | PositionComponent);
        signatures->push_back(signature);
        entities->push_back(spaceship);
        }

* For Systems :
Define system signatures using the Signature class. A signature is a bitmask where each bit corresponds to a component type.

Systems are a pair of their function and their signature. 
For example, for a System that will handle rendering, you will need entities that are drawable, and have a position:

    Engine::Signature renderSystemSignature;
    renderSystemSignature.setBits(DrawableComponent | PositionComponent); // Set the bits based on the required components

## Running the Engine
The guismusEngine's run function executes one tick of the engine. It is up to the developer to create a game loop and manage how many ticks the engine processes. The developer retains control to perform any necessary tasks between ticks.

for example:

    while (!endCondition) {
        engine.run();
        // Perform other game-related tasks between the engine's ticks
    }

By structuring the game loop this way, developers can add their own game logic, rendering, and input handling code as needed.

## Events
The guismusEngine provide an eventQueue to manage diverse event types, mostly intended for I/O events. it is a simple class of three ints, for event types, values and owners.
It is intended that the Developper creates enums to fill those fields.

here is a simple example:

    enum Players {
      PLAYER1,
      PLAYER2,
      PLAYER3,
      PLAYER4
    };

    enum EventType{
      MOVE,
      SHOOT,
      PLAYERQUIT,
      PICKUPBONUS
    };

    enum MovementValues {
      UP,
      DOWN,
      LEFT,
      RIGHT
    };

    enum BonusType {
      HEALTH,
      DMG_UP,
      FIRE_RATE_UP
    }

After defining those enums, you may create events as such:

    _engine->getEvents()->push_back(Engine::Event(MOVE, UP, PLAYER3))
    _engine->getEvents()->push_back(Engine::Event(SHOOT, 0, PLAYER1))
    _engine->getEvents()->push_back(Engine::Event(PICKUPBONUS, DMG_UP, PLAYER2))

Implement systems that react to specific events. When running the engine, systems can access the event queue and respond to events based on their event type and value.

## Conclusion
The guismusEngine is a versatile game engine that empowers developers to create games with freedom and flexibility. By defining components using templated functions, customizing entities, creating unique system signatures, and managing the game loop, developers can create games that suit their specific needs. Additionally, developers can use custom event enumerations to handle in-game events. This documentation serves as a starting point for using the engine and encourages developers to explore the full range of possibilities for game development.
