#pragma once
#include "Container.h"
#include"FollowGameObject.h"
#include "Vehicle.h"
#include "ProyectilePool.h"
#include <stack>

class Animation;
class ShootComponent;
class AimComponent;


//clase abstracta, padre de los diferentes tipos de torreta
class Turret : public Container
{
public:
	Turret();
	virtual void update(Uint32 deltaTime);
	virtual void AttachToVehicle(Vehicle* car);
	proyectileType GetProyectileType();
	virtual void Shoot();
	virtual void Reload();
	virtual void PerfectReload();
	virtual void CancelReload();
	virtual void InitiateReload();
	virtual int GetSpeed();
	virtual double GetDamage();
	virtual int GetCadence();
	virtual int GetAmmo();
	virtual int GetMaxAmmo();
	virtual double GetReloadPercentage();
	virtual double GetPerfReloadSeg();
	virtual double GetPerfReloadIni();
	virtual double GetLifeTime();
	virtual string GetReticule();
	virtual bool isReloading();
	virtual ~Turret();
protected:
	stack <double>* magazine_;//cargador representado como una pila
	int maxAmmo_;//capacidad del cargador
	int cadence_;//cadencia de disparo
	int reloadTime_;//tiempo de recarga al vaciar el cargador
	int speed_;//velocidad del proyectil
	int reloadpressedTime_;//momento en el que se pulso el boton de recarga
	int lastTimeShot_;//momento en el que se disparo la ultima bala
	double perfRelSeg_;//segmento del tiempo de recarga en el que entra en accion la recarga perfecta (en tanto por 1)
	double perfRelIni_;//momento dentro del tiempo de recarga en el que empieza el segmento de recarga perfecta (en tanto por 1)
	double damage_;//da�o de cada proyectil
	double lifeTime_; //tiempo de vida del proyectil
	bool reloading_;//indica si se esta recargando en el momento
	proyectileType prType_;//tipo de proyectil
	string path_;//direccion del sprite de la torreta
	string animationpath_;
	string reticulesprite_="";
	AimComponent* aimC_;//forma de apuntado, se lo pasa el vehiculo al equiparse
	ShootComponent* shC_;//codigo de disparo (en que forma dispara)
	FollowGameObject* followC_;
	Animation* animC_;
	Vehicle* car_;//coche al que esta pegada la torreta

};
