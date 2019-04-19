#pragma once
#include "Container.h"

class CursorLC;
class Animation;

class Reticule :public Container
{
public:
	Reticule(Reticule&) = delete;
	Reticule& operator=(const Reticule&) = delete;

	static Reticule* GetInstance() {
		if (instance_ == nullptr) {
			instance_ = new Reticule();
		}
		return instance_;
	}
	virtual ~Reticule();
	virtual void ChangeReticule(string ret);
	virtual string GetCurrentSprite();
	virtual void update(Uint32 time);


private:
	Reticule();
	map<string, string> animations_;
	Animation* animC_;
	CursorLC* cursorC_;
	static Reticule* instance_;

};
