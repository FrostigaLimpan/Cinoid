#include "BaseBlock.h"

namespace Cinoid {
	

	RectT<float> BaseBlock::getShape() { 
		return shape; 
	}

	float BaseBlock::x() {
		return (shape).x1;
	}

	float BaseBlock::y()
	{
		return (shape).y1;
	}

	float BaseBlock::left()
	{
		return (shape).x1;
	}

	float BaseBlock::right()
	{
		return (shape).x2;
	}

	float BaseBlock::top()
	{
		return (shape).y1;
	}

	float BaseBlock::bottom()
	{
		return (shape).y2;
	}

}