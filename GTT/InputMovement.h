#pragma once
#include "Vehicle.h"

class InputMovement : public ControlType
{
public:
	InputMovement(KeysScheme k, Vehicle* v);
	virtual ~InputMovement();

	virtual void handleInput(GameObject* o, Uint32 deltaTime, const SDL_Event& event);
	virtual void update(GameObject* o, Uint32 deltaTime);

private:
	KeysScheme k_;
	Vehicle* v_;
	//Input booleans
	bool forwardPressed_;
	bool backwardPressed_;
	bool rightTurnPressed_;
	bool leftTurnPressed_;
	bool handBrakePressed_;

	float targetLateralVelocity = 0;
	float targetDamping = 1;
	float targetMaxSpeed;

	void steeringWheel();
	bool isMoving();
	Vector2D getLateralVelocity();

	void updateFriction();
};
