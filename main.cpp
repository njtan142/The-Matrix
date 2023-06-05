#include "imgui-SFML.h"
#include "Application.h"
#include "EnergyConservationScene.h"
#include "EnergyConservationBilliard.h"


int main()
{
	sf::View* view = Application::InitializeWindow();
	Scene* sceneEnCon = new EnergyConservationSceneBilliard(view);
	Application::scene = sceneEnCon;

	Application::scene->InitializeObjects();
	Application::scene->Run();
	ImGui::SFML::Shutdown();
	return 0;

}