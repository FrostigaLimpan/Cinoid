#include "Ball.h"

namespace Cinoid {
	void Ball::resetBall(const float& X, const float& Y, const float& InitialSpeed) {
		shape->first.x = X - initialBallRadius/2.f;
		shape->first.y = Y;
		speed = InitialSpeed;
		velocity.x = -speed;
		velocity.y = -speed;
	}

	void Ball::update()
	{
		shape->first.x = shape->first.x + velocity.x;
		shape->first.y = shape->first.y + velocity.y;

		if (left() < 0) 
			velocity.x = speed;
		else if (right() > windowWidth) 
			velocity.x = -speed;

		if (top() < 0) 
			velocity.y = speed;
		else if (bottom() > windowHeight - 20) 
			velocity.y = -speed;
	}

	std::pair<Vec2f, float> Ball::getShape()
	{
		return *shape;
	}

	Color Ball::getColor() {
		return color;
	}

	float Ball::x()
	{
		return shape->first.x;
	}

	float Ball::y()
	{
		return shape->first.y;
	}

	float Ball::left()
	{
		return x() - shape->second;
	}

	float Ball::right()
	{
		return x() + shape->second;
	}

	float Ball::top()
	{
		return y() - shape->second;
	}

	float Ball::bottom()
	{
		return y() + shape->second;
	}

}