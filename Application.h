#pragma once
#include "SFML/Window.hpp"
#include <list>

#include "Scene.h"

enum Scenes {
	BoxEG,
	BilliardEG,
	Bouncy,
	Gravity,
	PendulumSimulation,
	AccellerationSimulation,
	none,
};

namespace Application {
	extern sf::Vector2i previousMousePos;
	extern sf::RenderWindow window;
	extern bool running;
	extern Scene* scene;
	extern Scenes selectedScene;

	
	
	//Window Controls
	sf::View* InitializeWindow();
	void SetImGuiGlobalSize(float scale, float fontSize);

	//Event handling
	void ListenEvent(sf::View* view, std::list<Object*>* objectsList);
	void OnMousePress(sf::Event& event, std::list<Object*>* objectsList);
	void OnMouseMove(sf::RenderWindow& window, sf::View* view);
	void OnResize(sf::RenderWindow& window, sf::View* view, const sf::Event& event);
	void DetectObjectPress(const sf::Event& event, const std::list<Object*>* objectsList);

	//Game controls
	void RenderGameControls(sf::View& view);

	//Scene management
	void OnSceneChange();

}

