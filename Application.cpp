#include "Application.h"
#include "Shape.h"
#include "imgui.h"
#include "EnergyConservationScene.h"
#include "EnergyConservationBilliard.h"
#include "BounceSimulationScene.h"
#include "GravitySimulationScene.h"
#include "PendulumScene.h"
#include "AccellerationScene.h"
#include <iostream>
#include "imgui-SFML.h"



namespace Application {
	sf::Vector2i previousMousePos;
	sf::RenderWindow window(sf::VideoMode(800, 800), "The Matrix", sf::Style::Default);
	bool running = true;
	Scene* scene;
	Scenes selectedScene = Scenes::BilliardEG;


	void OnResize(sf::RenderWindow& window, sf::View* view, const sf::Event& event) {
		view->setSize(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
		window.setView(*view);
	}

	void ListenEvent(sf::View* view, std::list<Object*>* objectsList) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed) {
				running = false;
				//window.close();
			}
			else if (event.type == sf::Event::Resized) {
				OnResize(window, view, event);
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				OnMousePress(event, objectsList);
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				OnMouseMove(window, view);
			}
			break;
		}
	}


	void OnMousePress(sf::Event& event, std::list<Object*>* objectsList) {
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			DetectObjectPress(event, objectsList);
		}

	}

	void DetectObjectPress(const sf::Event& event, const std::list<Object*>* objectsList) {
		for (Object* object : *objectsList) {

			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			Shape* objectShape = object->GetComponent<Shape>();

			if (objectShape) {
				sf::FloatRect bounds = objectShape->Get()->getGlobalBounds();

				if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
					object->OpenEditor();
				}
			}

		}
	}

	void OnMouseMove(sf::RenderWindow& window, sf::View* view) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			sf::Vector2i mouseDelta = sf::Mouse::getPosition(window) - previousMousePos;
			view->move(static_cast<float>(-mouseDelta.x), static_cast<float>(-mouseDelta.y));
			window.setView(*view);

			std::cout << "X: " << view->getCenter().x << " | " << "Y: " << view->getCenter().y << std::endl;
		}
	}



	void RenderGameControls(sf::View& view) {
		if (!window.isOpen() || !running) {
			running = false;
			return;
		}

		ImGui::Begin("Controls");
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20.0f, 20.0f));
		ImGui::SetWindowFontScale(2.0f);
		ImGui::Text("Zoom");
		ImGui::SameLine();
		if (ImGui::Button("+"))
		{
			view.setSize(view.getSize() * (1 - 0.1f));
			window.setView(view);
		}
		ImGui::SameLine();
		if (ImGui::Button("-")) {
			view.setSize(view.getSize() * (1 + 0.1f));
			window.setView(view);
		}



		ImGui::PopStyleVar();

		// SCENE DROPDOWN

		if (
			ImGui::BeginCombo(
				"Current Scene",
				(selectedScene == Scenes::BoxEG) ?
				"1D Object Collission Energy Conservation" : //1
				(selectedScene == Scenes::BilliardEG) ?
				"2D Object Collission Energy Conservation" : //2
				(selectedScene == Scenes::Bouncy) ?
				"Bounce Simulation" :						 //3
				(selectedScene == Scenes::Gravity) ?
				"Gravity Simulation" :						 //4
				(selectedScene == Scenes::PendulumSimulation) ?
				"Pendulum Simulation" :
				"Acceleration Simulation"					 //5

			)
			)
		{
			for (int i = 0; i < Scenes::none; i++)
			{
				Scenes option = Scenes(i);
				bool is_selected = (selectedScene == option);
				if (!window.isOpen() || !running) {
					running = false;
					return;
				}

				if (ImGui::Selectable(
					(option == Scenes::BoxEG) ?
					"1D Object Collission Energy Conservation" : //1
					(option == Scenes::BilliardEG) ?
					"2D Object Collission Energy Conservation" : //2
					(option == Scenes::Bouncy) ?
					"Bounce Simulation" :						 //3
					(option == Scenes::Gravity) ?
					"Gravity Simulation" :						 //4
					(option == Scenes::PendulumSimulation) ?
					"Pendulum Simulation" :
					"Acceleration Simulation"					 //5
				)
					)
				{
					selectedScene = option;
					OnSceneChange();
				}
				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			if (!window.isOpen() || !running) {
				running = false;
				return;
			}
			else {
				ImGui::EndCombo();
			}
		}

		ImGui::End();
	}


	void OnSceneChange() {
		Scene* sceneEnCon = nullptr;
		if (selectedScene == Scenes::BoxEG) {
			sceneEnCon = new EnergyConservationScene(scene->view);
		}
		else if (selectedScene == Scenes::BilliardEG) {
			sceneEnCon = new EnergyConservationSceneBilliard(scene->view);

		}
		else if (selectedScene == Scenes::Bouncy) {
			sceneEnCon = new BounceSimulationScene(scene->view);
		}
		else if (selectedScene == Scenes::Gravity) {
			sceneEnCon = new GravitySimulationScene(scene->view);
		}
		else if (selectedScene == Scenes::PendulumSimulation) {
			sceneEnCon = new PendulumScene(scene->view);
		}
		else {
			sceneEnCon = new AccellerationScene(scene->view);

		}
		if (!sceneEnCon) {
			return;
		}
		Application::scene = sceneEnCon;
		Application::scene->InitializeObjects();
		scene->Run();
	}


	sf::View* InitializeWindow() {
		ImGui::SFML::Init(window);
		SetImGuiGlobalSize(1.5f, 1.75f);

		sf::View* view = new sf::View(
			sf::FloatRect(
				0,
				0,
				static_cast<float>(window.getSize().x),
				static_cast<float>(window.getSize().y)
			)
		);

		window.setView(*view);
		return view;
	}

	void SetImGuiGlobalSize(float scale, float fontSize) {
		float globalScale = scale;
		ImGui::GetStyle().ScaleAllSizes(globalScale);
		ImGui::GetIO().FontGlobalScale = fontSize;
	}

};