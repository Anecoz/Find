#pragma once
#include <glm\glm.hpp>

class Camera
{
public:
	Camera(); // Default constructor
	Camera(const glm::vec3 initPos);
	~Camera() = default;

    // Needed for listening to mouse movements. glutPassiveMotionFunc must be set from a global context
	void handleMouseMovement(int, int);

	// Should be called once every frame
	void update();

	// Returns a camera matrix to be used in shaders
	glm::mat4 getCameraMatrix() const;
	glm::mat4 getProj() const;
	glm::mat4 getCombined() const;

	// Where mouse is warped every warp
	static const int MOUSE_WARP_X = 200;
	static const int MOUSE_WARP_Y = 200;
	// Refresh rate for warping
	static const int WARP_REFRESH_RATE = 50;

	void updateTSinceLast();
	glm::vec2 getCurrMousePos();

	glm::vec3 getPos();

private:
	glm::mat4 _projMatrix;
	bool _shouldMoveCamera = true;
	float _sensitivity = 1.0; // Higher value -> lower sensitivty....

	glm::vec2 _currMousePos;

	glm::vec3 _pos; // Position of the camera
	float _tSinceLast; // Elapsed time since last time update was called

	// We need an up vector as well as a "look"-vector
	glm::vec3 _up{ 0.0, 1.0, 0.0 };
	glm::vec3 _look; // This one needs to be defined once we know the camera position, i.e. in constructor

	void init();
};

