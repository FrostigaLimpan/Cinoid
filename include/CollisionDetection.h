#include "PlayerPaddle.h"

namespace Cinoid {

	template<class T1, class T2> bool isShapesIntersecting(T1& firstShape, T2& secondShape) {
		return firstShape.right() >= secondShape.left() &&
			firstShape.left() <= secondShape.right() &&
			firstShape.bottom() >= secondShape.top() &&
			firstShape.top() <= secondShape.bottom();
	};

	void testForPlayerCollision(PlayerPaddle& paddle, Ball& ball) {
		if (!isShapesIntersecting(paddle, ball)) return;

		ball.velocity.y = -ball.speed;
		
		if (ball.x() < paddle.x() + (paddle.right() - paddle.x())/2.f) 
			ball.velocity.x = -ball.speed;
		else 
			ball.velocity.x = ball.speed;

	}

	bool testForBottomCollision(Ball& ball) {

		if (!(ball.y() >= windowHeight - 50.f))
			return false;

		ball.velocity.y = -ball.speed;
		return true;
	};

	void testForTileCollision(Tile& tile, Ball& ball)
	{
		if (!isShapesIntersecting(tile, ball)) return;

		tile.isDestroyed = true;

		float overlapLeft{ ball.right() - tile.left() };
		float overlapRight{ tile.right() - ball.left() };
		float overlapTop{ ball.bottom() - tile.top() };
		float overlapBottom{ tile.bottom() - ball.top() };

		bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));

		bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

		float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
		float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

		if (abs(minOverlapX) < abs(minOverlapY))
			ball.velocity.x = ballFromLeft ? -ball.speed : ball.speed;
		else
			ball.velocity.y = ballFromTop ? -ball.speed : ball.speed;
	}
}