#pragma once
#include <glm\glm.hpp>

class Camera
{
public:
	Camera();
	Camera(const glm::vec3 initPos);
	~Camera() = default;

	void handleMouseMovement(int, int);

	void update(double deltaTime);

	glm::mat4 getCameraMatrix() const;
	glm::mat4 getProj() const;
	glm::mat4 getCombined() const;

	static const int MOUSE_WARP_X = 200;
	static const int MOUSE_WARP_Y = 200;

	glm::vec3 getPos();

private:
	glm::mat4 _projMatrix;
	bool _shouldMoveCamera = true;
	float _sensitivity = 1.0; // Higher value -> lower sensitivty....

	glm::vec3 _pos;

	glm::vec3 _up{ 0.0, 1.0, 0.0 };
	glm::vec3 _look;

	void init();
};

