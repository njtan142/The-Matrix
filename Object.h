#pragma once
#include <vector>
#include <string>
#include "Transform.h"
#include "SFML/Graphics.hpp" // Include SFML/Graphics.hpp for sf::RenderWindow

class Object {
public:
    virtual ~Object() {}

    virtual void Update() {}
    virtual void RenderEditorWindow() {}
    virtual void OpenEditor();
    virtual void Draw(sf::RenderWindow& window); // Modified Draw to accept sf::RenderWindow&


    template<typename T>
    T* AddComponent() {
        // Check if the component type already exists
        for (Component*& component : components) {
            if (dynamic_cast<T*>(component)) {
                // Component type already exists, return it
                return dynamic_cast<T*>(component);
            }
        }

        // Component type does not exist, create and add it
        T* newComponent = new T(this);
        components.push_back(newComponent);
        return newComponent;
    }

    template<typename T>
    T* AddComponent(T* component) {
        // Check if the component type already exists
        for (Component*& component : components) {
            if (dynamic_cast<T*>(component)) {
                // Component type already exists, return it
                return dynamic_cast<T*>(component);
            }
        }

        components.push_back(component);
        return component;

    }


    template<typename T>
    void RemoveComponent() {
        for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it) {
            T* component = dynamic_cast<T*>(*it);
            if (component) {
                component->entity = nullptr;
                components.erase(it);
                delete component;
                return;
            }
        }
    }

    template<typename T>
    T* GetComponent() {
        for (Component*& component : components) {
            T* typedComponent = dynamic_cast<T*>(component);
            if (typedComponent) {
                return typedComponent;
            }
        }
        return nullptr;
    }



protected:
    bool edit = false;
    std::vector<Component*> components;

public:
    std::string name;
    Transform* transform = nullptr;
};
