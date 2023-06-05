#include "shapes.h"
#include "Transform.h"
#include "Vector2.h"
#include "imgui.h"


Transform::Transform() {
	position = Vector2();
	rotation = 0.0f;
}

Transform::Transform(float x, float y, float rotation, Object* entity) {
	position = *new Vector2(x, y);
	scale = *new Vector2(1, 1);
	this->rotation = rotation;
	this->entity = entity;
}

Transform::Transform(Object* entity){
	this->entity = entity;
	rotation = 0.f;
}

void Transform::RenderEditor() {
	ImGui::Text("Transform");
	ImGui::Separator();
	ImGui::DragFloat2("Position", position.Array());
	ImGui::DragFloat2("Scale", scale.Array());
	ImGui::DragFloat("Rotation", &rotation);
	ImGui::Spacing();

}