#pragma once
#include "BaseBlock.h"
#include "Parameters.h"

namespace Cinoid {

	class PlayerPaddle : public BaseBlock
	{
	private:
		void update();
		Color color = Color(PlayerColorRed, PlayerColorGreen, PlayerColorBlue);
	public:

		const float speed{ initialPlayerPaddleSpeed };

		Vec2f paddleVelocity;

		PlayerPaddle(const float& X, const float& Y, const float& PaddleWidth, const float& PaddleHeight) :BaseBlock(X, Y, PaddleWidth, PaddleHeight) {
		}

		void resetPaddle(const float& X, const float& Y);
		Color getColor();

		void moveLeft();
		void moveRight();

	};

}