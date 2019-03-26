#include "PhysicObject.h"


PhysicObject::PhysicObject(b2BodyType type, int w, int h, int x, int y, float32 angle, Vector2D origin) {
	visualSize_ = Vector2D(w, h);
	origin_ = origin;

	// Body definition and instantiation
	bodyDef_ = b2BodyDef();
	bodyDef_.position.Set(x * PHYSICS_SCALING_FACTOR + (w / 2 * PHYSICS_SCALING_FACTOR),
		y * PHYSICS_SCALING_FACTOR + (h / 2 * PHYSICS_SCALING_FACTOR));
	bodyDef_.type = type;
	body_ = Game::getInstance()->getWorld()->CreateBody(&bodyDef_);

	// Fixture definition and instantiation
	fixtureDef_ = b2FixtureDef();
	shape_.SetAsBox(w / 2 * PHYSICS_SCALING_FACTOR,
		h / 2 * PHYSICS_SCALING_FACTOR,
		origin_, angle);
	fixtureDef_.shape = &shape_;
	fixtureDef_.density = 1;
	body_->CreateFixture(&fixtureDef_);

}


PhysicObject::~PhysicObject() {
	Game::getInstance()->getWorld()->DestroyBody(body_); body_ = nullptr;
}

void PhysicObject::update(GameObject * o, Uint32 deltaTime) {
	Vector2D nextPos = Vector2D(body_->GetPosition().x, body_->GetPosition().y);

	nextPos.Divide(PHYSICS_SCALING_FACTOR);



	if (abs(body_->GetLinearVelocity().Length()) < 0.5) {

		body_->SetLinearVelocity(Vector2D());

	}



	if (abs(body_->GetAngularVelocity()) < 0.5) {

		body_->SetAngularVelocity(0);

	}
	o->setPosition(nextPos - (Vector2D(visualSize_.x * origin_.x, visualSize_.y * origin_.y)));

	o->setRotation(body_->GetAngle() * 180 / M_PI);
}

const b2Vec2 PhysicObject::getOrigin() {
	return origin_;
}

b2Body * PhysicObject::getBody() {
	return body_;
}
