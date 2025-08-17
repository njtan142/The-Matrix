#pragma once
#include <vector>
#include <string>
#include <memory> // For std::unique_ptr
#include "Transform.h"
#include "SFML/Graphics.hpp" // Include SFML/Graphics.hpp for sf::RenderWindow

class Object {
public:
    virtual ~Object() {
    }

    virtual void Update() {}
    virtual void RenderEditorWindow() {}
    virtual void OpenEditor();
    virtual void Draw(sf::RenderWindow& window); // Modified Draw to accept sf::RenderWindow&


    template<typename T>
    T* AddComponent() {
        // Check if the component type already exists
        for (auto& component : components) {
            if (dynamic_cast<T*>(component.get())) {
                // Component type already exists, return it
                return dynamic_cast<T*>(component.get());
            }
        }

        // Component type does not exist, create and add it
        std::unique_ptr<T> newComponent = std::make_unique<T>(this);
        T* rawPtr = newComponent.get(); // Get raw pointer before moving
        components.push_back(std::move(newComponent));
        return rawPtr;
    }

    template<typename T>
    T* AddComponent(std::unique_ptr<T> component) {
        // Check if the component type already exists
        for (auto& existingComponent : components) { // Renamed loop variable to avoid shadowing
            if (dynamic_cast<T*>(existingComponent.get())) {
                // Component type already exists, return it
                return dynamic_cast<T*>(existingComponent.get());
            }
        }

        T* rawPtr = component.get(); // Get raw pointer before moving
        components.push_back(std::move(component));
        return rawPtr;

    }


    template<typename T>
    void RemoveComponent() {
        for (auto it = components.begin(); it != components.end(); ++it) {
            T* component = dynamic_cast<T*>(it->get());
            if (component) {
                components.erase(it);
                return;
            }
        }
    }

    template<typename T>
    T* GetComponent() {
        for (auto& component : components) {
            T* typedComponent = dynamic_cast<T*>(component.get());
            if (typedComponent) {
                return typedComponent;
            }
        }
        return nullptr;
    }



protected:
    bool edit = false;
    std::vector<std::unique_ptr<Component>> components;

public:
    std::string name;
    Transform* transform = nullptr;
};
