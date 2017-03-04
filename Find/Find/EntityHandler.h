#pragma once
#include "Camera.h"
#include "Grid.h"

class EntityHandler {
public:
	EntityHandler();
	~EntityHandler();

	void tick(Camera* cam, double deltaTime);
	void render(Camera* cam);

private:
	Grid* _grid;
};