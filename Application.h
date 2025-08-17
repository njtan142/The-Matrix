#pragma once
#include "SFML/Window.hpp"
#include <list>

class Scene; // Forward declaration

#include "Scene.h" // Keep this include for full definition

class Application {
public:
    enum Scenes {
        BoxEG,
        BilliardEG,
        Bouncy,
        Gravity,
        PendulumSimulation,
        AccellerationSimulation,
        none,
    };

    Application();
    ~Application();

    sf::View* InitializeWindow();
    void SetImGuiGlobalSize(float scale, float fontSize);
    void ListenEvent(sf::View* view, std::list<Object*>* objectsList);
    void OnMousePress(sf::Event& event, std::list<Object*>* objectsList);
    void OnMouseMove(sf::View* view);
    void OnResize(sf::View* view, const sf::Event& event);
    void DetectObjectPress(const sf::Event& event, const std::list<Object*>* objectsList);
    void RenderGameControls(sf::View& view);
    void OnSceneChange();

    sf::RenderWindow& getWindow() { return window; }
    bool isRunning() const { return running; }
    void setRunning(bool value) { running = value; }
    Scene* getScene() { return scene; }
    void setScene(Scene* newScene) { scene = newScene; }
    Scenes getSelectedScene() const { return selectedScene; }
    void setSelectedScene(Scenes scene) { selectedScene = scene; }

public:
    sf::Vector2i previousMousePos;
    sf::RenderWindow window;
    bool running;
    Scene* scene;
    Scenes selectedScene;
};