#pragma once

#include <cstdint>

namespace console::shell::hardware {

	enum class HardwareStatus : uint8_t {

		kSuccess = 0,
		kError,
		kTimeout,
		kNotInitialized,
		kInvalidParameter,
		kBufferOverflow,
		kBufferUnderflow,
		kDeviceNotFound,
		kNotSupported,
		kBusy,
		kPartialRead,
		kPartialWrite,
		kNotReady,
	};
}