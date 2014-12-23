#include "Level.h"

namespace Cinoid {

	void Level::loadLevel(const std::string& Level) {
		for (int iX{ 0 }; iX < TilesXCount; ++iX)
			for (int iY{ 0 }; iY < TilesYCount; ++iY)
				tiles.emplace_back(
				((iX + 1) * (TileWidth + 3) + 22) - initialTileWidth / 2.f,
				(iY + 2) * (TileHeight + 3),
				initialTileWidth,
				initialTileHeight,
				initialScore
				);
		name = Level;
		backdropImage = levelBackdropImage;
	}

	std::vector<Tile>& Level::getTiles()
	{
		return tiles;
	}

	std::string& Level::getName()
	{
		return name;
	}

	std::string& Level::getBackdropImage()
	{
		return backdropImage;
	}

}