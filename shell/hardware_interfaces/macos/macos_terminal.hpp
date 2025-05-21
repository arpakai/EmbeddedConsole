#pragma once

#include "hardware_interfaces.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

namespace console::shell::hardware {

	class MacOSTerminal : public HardwareInterface {

	public:
		MacOSTerminal() = default;
		virtual ~MacOSTerminal() = default;

		HardwareStatus init() override;
		HardwareStatus start_rx() override;
		HardwareStatus stop_rx() override;
		HardwareStatus start_tx() override;
		HardwareStatus stop_tx() override;

	private:
		HardwareStatus read(std::span<uint8_t> buffer, size_t &bytes_read) override;
		HardwareStatus write(std::span<const uint8_t> buffer, size_t &bytes_written) override;
	};
} // namespace console::shell::hardware