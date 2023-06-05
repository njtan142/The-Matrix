#pragma once

class Object;

class Component {
public:
	virtual ~Component() {}
	Component() {}
	Component(Object* entity) : entity(entity) {}
	virtual void RenderEditor() {};

public:
	Object* entity = nullptr;
};
