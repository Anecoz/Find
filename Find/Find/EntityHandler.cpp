#include "EntityHandler.h"

EntityHandler::EntityHandler()
{
	_grid = new Grid();
}

EntityHandler::~EntityHandler()
{
	delete _grid;
}

void EntityHandler::tick(Camera* cam, double deltaTime)
{
	_grid->tick(cam, deltaTime);
}

void EntityHandler::render(Camera* cam)
{
	_grid->render(cam);
}