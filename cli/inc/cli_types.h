#pragma once

#include <cstddef>
#include <cstdint>

namespace console::cli {

	enum class CLIStatus {

		kOk = 0,
		kError,
		kTimeout,
		kBufferFull,
		kInvalidInput
	};

	enum class Direction {

		kUp = 0,
		kDown,
		kLeft,
		kRight
	};

	enum class ButtonType {

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