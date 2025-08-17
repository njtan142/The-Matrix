#include "imgui-SFML.h"
#include "Application.h"
#include "EnergyConservationScene.h"
#include "EnergyConservationBilliard.h"


int main()
{
    Application app; // Create an instance of the Application class
    sf::View* view = app.InitializeWindow();
    Scene* sceneEnCon = new EnergyConservationSceneBilliard(view, app); // Pass app to constructor
    app.setScene(sceneEnCon); // Use the setScene method

    app.getScene()->InitializeObjects();
    app.getScene()->Run();
    // ImGui::SFML::Shutdown() is now handled in Application's destructor
    return 0;

}