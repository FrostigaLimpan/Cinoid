#include "PlayerPaddle.h"

namespace Cinoid {

	void PlayerPaddle::moveLeft() {
		update();
		if (shape.x1 > 0)
			paddleVelocity.x = -speed;
		else
			paddleVelocity.x = 0;
	}

	void PlayerPaddle::moveRight() {
		update();
		if (shape.x2 < windowWidth)
			paddleVelocity.x = speed;
		else paddleVelocity.x = 0;
	}

	void PlayerPaddle::resetPaddle(const float& X, const float& Y)
	{
		shape.set(X - initialPlayerPaddleWidth / 2.f, Y, (X - initialPlayerPaddleWidth / 2.f) + initialPlayerPaddleWidth, Y + initialPlayerPaddleHeight);
		//shape.set(windowWidth / 2.0f - initialPaddleWidth / 2.f, windowHeight - 50.0f, X + initialPaddleWidth, Y + initialPaddleHeight);
	}

	void PlayerPaddle::update()
	{
		shape.offset(paddleVelocity);
	}

	Color PlayerPaddle::getColor() {
		return color;
	}

}
