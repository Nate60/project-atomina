#pragma once

namespace ATMA {
	
	using AttributeType = unsigned int;

	enum class ATMA_API Attribute {
		None = 0,
		Translatable, 
		Drawable,
		Controllable,
		COUNT
	};

}
