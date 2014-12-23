#pragma once

#include "cinder/gl/gl.h"
#include "Parameters.h"

using namespace ci;

namespace Cinoid {
	class Ball
	{
	private:
		std::unique_ptr<std::pair<Vec2f, float>> shape;
		Color color = Color(BallColorRed, BallColorGreen, BallColorBlue);

	public:
		float speed = 0.f;
		Vec2f velocity{ -speed, -speed };

		Ball(const float& X, const float& Y, const float& InitialSpeed, const unsigned int& WindowHeight, const unsigned int& WindowWidth) {
			shape = std::make_unique<std::pair<Vec2f, float>>(std::make_pair(Vec2f{ X - initialBallRadius/2.f, Y }, initialBallRadius));
			speed = InitialSpeed;
			velocity.x = -speed;
			velocity.y = -speed;
		}

		std::pair<Vec2f, float> getShape();

		Color getColor();

		void resetBall(const float& X, const float& Y, const float& InitialSpeed);

		void update();

		float x();
		float y();
		float left();
		float right();
		float top();
		float bottom();

	};
}
