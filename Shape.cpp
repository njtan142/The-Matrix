
#include "imgui-SFML.h"
#include "imgui.h"
#include "Shape.h"



Shape::Shape(Object* entity) {
	this->entity = entity;

	this->xGeometry = "X";
	this->yGeometry = "Y";

	visible = true;
}
Shape::Shape(sf::Shape* shape, Object* entity) {
	this->shape = shape;
	this->entity = entity;

	this->xGeometry = "X";
	this->yGeometry = "Y";

	visible = true;
}

Shape::Shape(sf::Shape* shape, const std::string& xGeometry, const std::string& yGeometry, const Vector2* geometry, Object* entity)
	: xGeometry(xGeometry), yGeometry(yGeometry)
{
	this->shape = shape;
	this->geometry = *geometry;
	this->entity = entity;
	visible = true;
}
sf::Shape* Shape::Get() {
	return shape;
}
bool Shape::Visible() {
	return visible;
}

void Shape::RenderEditor() {
	ImGui::Text("Shape");
	ImGui::Separator();
	ImGui::Checkbox("Visible", &visible);
	ImGui::DragFloat(xGeometry.c_str(), geometry.x);
	ImGui::DragFloat(yGeometry.c_str(), geometry.y);
	ImGui::ColorEdit4("Color", color.Array());
	ImGui::Spacing();
}

