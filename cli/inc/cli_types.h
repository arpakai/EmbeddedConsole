#pragma once

#include <cstddef>
#include <cstdint>

namespace console::cli {

	enum class ButtonType
	{

		kNotDefined = -1,
		kNormal,
		kBackspace,
		kDelete,
		kEnter,
		kTAB,
		kEscapeSequence,
		kArrowUp,
		kArrowDown,
		kArrowLeft,
		kArrowRight,
		kHome,
		kEnd,
	};

} // namespace console::cli