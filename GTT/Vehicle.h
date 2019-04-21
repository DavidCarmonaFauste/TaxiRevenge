#include "ControlType.h"
#include "Car.h"
#include "TaxiSoundManagerCP.h"

#pragma once

using namespace std;

class Turret;
class ReloadInputComponent;
class ShootIC;

class Vehicle : public Car
{
	static const int MAXTURRETS = 4;

	//hide copyBuilder and 	assignment operator
	Vehicle(Vehicle &) = delete;
	Vehicle & operator=(const Vehicle &) = delete;

	static unique_ptr<Vehicle > instance_; //ptr instance class


public:
	//builder
	Vehicle();
	virtual ~Vehicle();

	//init singleton class
	inline static void initInstance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new Vehicle());
		}
	}
	//get singleton class
	inline static Vehicle* getInstance() {
		//SDL_assert(instance_.get() != nullptr); //lanza una mensaje con la primera llamada a getInstance, porque devuelve null
		return instance_.get();
	}

	void initAtributtes(VehicleInfo r, KeysScheme k);


	float32 GetMaxBackwardSpeed();	
	float32 GetAcceleration();
	

	virtual ReloadInputComponent* GetReloadIC();
	virtual ShootIC* GetShootIC();
	virtual TaxiSoundManagerCP* GetTxSoundManager();
	virtual void EquipTurret(Turret* turret);
	virtual void ChangeTurret();
	Turret* getCurrentTurret();

	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void render(Uint32 time);
	virtual void update(Uint32 time);

	virtual bool receiveEvent(Event& e);
	

	private:

	int currentTurret_ = 0;

	float32 maxBackwardSpeed_;
	float32 acceleration_;

	ControlType* control_;
	ReloadInputComponent* reIC_;
	ShootIC* shIC_;
	Turret* turrets_[MAXTURRETS];

	TaxiSoundManagerCP* smLC_;
	
};
