#pragma once

#include "Tile.h"
#include "Parameters.h"

namespace Cinoid {
	
	class Level
	{

	private:

		std::string name;
		std::string backdropImage;
		std::vector<Tile> tiles;

	public:

		Level() {}
		
		void loadLevel(const std::string& Level);

		std::vector<Tile>& getTiles();
		std::string& getName();
		std::string& getBackdropImage();
	};

}