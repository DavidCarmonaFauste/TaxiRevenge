#include "Proyectile.h"


Proyectile::Proyectile()
{
	setActive(false);
}

void Proyectile::Impact()//que hacer cuando el proyectil colisiona con algo
{
	active_ = false;
}

void Proyectile::SetBirth(double birthTime)
{
	birthTime_ = birthTime;
}


void Proyectile::update(Uint32 time)
{
	if (SDL_GetTicks() - birthTime_ >= lifeTime_) {
		setActive(false);
	}
	Container::update(time);
}

void Proyectile::ChangeBulletType(ProyectileInfo p)
{
	if (phyO_ != nullptr)
		delLogicComponent(phyO_);
	if (animC_ != nullptr)
		delRenderComponent(animC_);
	
	width_ = p.width;
	height_ = p.height;
	speed_ = p.speed;
	lifeTime_ = p.lifeTime;
	damage_ = p.damage;
	animC_ = new Animation();
	addRenderComponent(animC_);
	animC_->loadAnimation(p.idlePath, "default");
	animC_->playAnimation("default");
	phyO_ = new PhysicObject(b2_dynamicBody, width_, height_, position_.x, position_.y);
	phyO_->getBody()->GetFixtureList()->SetSensor(true);
	addLogicComponent(phyO_);
}

PhysicObject * Proyectile::GetPhyO()
{
	return phyO_;
}

double Proyectile::GetSpeed()
{
	return speed_;
}
