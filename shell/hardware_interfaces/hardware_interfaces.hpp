#pragma once

#include "hardware_status.h"
#include <span>

namespace console::shell::hardware {

	class HardwareInterface {

	protected:
		HardwareInterface() = default;
		virtual ~HardwareInterface() = default;

		virtual HardwareStatus init() = 0;
		virtual HardwareStatus start_rx() = 0;
		virtual HardwareStatus stop_rx() = 0;
		virtual HardwareStatus start_tx() = 0;
		virtual HardwareStatus stop_tx() = 0;
		virtual HardwareStatus read(std::span<uint8_t> buffer, size_t &bytes_read) = 0;
		virtual HardwareStatus write(std::span<const uint8_t> buffer, size_t &bytes_written) = 0;
	};
} // namespace console::shell::hardware
