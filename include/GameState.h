#pragma once

namespace Cinoid {
	
	enum State : int {
		NOTINITIALIZED = 0,
		RUNNING = 1,
		STARTSCREEN = 2,
		SCORESCREEN = 3,
		ENDGAME = 4,
		PAUSED = 5
	};
	
	struct GameState {
		int currentState = State::NOTINITIALIZED;
	};
}
