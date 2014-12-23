#pragma once

#include "cinder/gl/gl.h"

using namespace ci;

namespace Cinoid {

	class BaseBlock
	{

	private:

		float width{ 0.f };
		float height{ 0.f };

	protected:
		//std::unique_ptr<RectT<float>> shape;
		RectT<float> shape;

	public:

		BaseBlock(const float& X, const float & Y, const float& Width, const float& Height)
		{
			width = Width;
			height = Height;
			//shape = std::make_unique<RectT<float>>(X, Y, X + Width, Y + Height);
			shape = RectT<float>(X, Y, X + Width, Y + Height);
		}

		~BaseBlock() {}

		RectT<float> getShape();
		
		//{ return *shape;  }
		
		float BaseBlock::x();
		float BaseBlock::y();
		float BaseBlock::left();
		float BaseBlock::right();
		float BaseBlock::top();
		float BaseBlock::bottom();
		
	};

}