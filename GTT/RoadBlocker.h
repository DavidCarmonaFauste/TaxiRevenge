#pragma once
#include "Container.h"
#include "PhysicObject.h"
#include "Sprite.h"

class RoadBlocker : public Container {
public:
	RoadBlocker ();
	virtual ~RoadBlocker ();

	void removeBlocker ();
private:
	PhysicObject* phyO_ = nullptr;
	Sprite *sprite_ = nullptr;
};

