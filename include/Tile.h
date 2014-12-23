#pragma once

#include "BaseBlock.h"
#include "Parameters.h"

namespace Cinoid {
	class Tile : public BaseBlock
	{
	private:

		Color color = Color(TileColorRed, TileColorGreen, TileColorBlue);
	public:

		bool isDestroyed{ false };
		int score;

		Tile(const float& X, const float& Y, const float& Width, const float& Height, const int& Score) : BaseBlock(X, Y, Width, Height)
		{
			score = Score;
		}
		
		Color getColor();

	};

}