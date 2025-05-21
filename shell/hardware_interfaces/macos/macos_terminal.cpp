#include "macos_terminal.hpp"

namespace console::shell::hardware {

	HardwareStatus MacOSTerminal::init() {

		return HardwareStatus::kSuccess;
	}

	HardwareStatus MacOSTerminal::start_rx() {

		return HardwareStatus::kSuccess;
	}

	HardwareStatus MacOSTerminal::stop_rx() {

		return HardwareStatus::kSuccess;
	}

	HardwareStatus MacOSTerminal::start_tx() {

		return HardwareStatus::kSuccess;
	}

	HardwareStatus MacOSTerminal::stop_tx() {

		return HardwareStatus::kSuccess;
	}

	HardwareStatus MacOSTerminal::read(std::span<uint8_t> buffer, size_t &bytes_read) {

		if (buffer.empty() || bytes_read > buffer.size()) {
			return HardwareStatus::kInvalidParameter;
		}

		size_t actual_bytes_read = 0;

		try {
			for (size_t i = 0; i < bytes_read; ++i) {
				int input = std::cin.get();

				if (std::cin.eof()) {
					break;
				}

				if (std::cin.fail()) {
					std::cin.clear();
					return HardwareStatus::kError;
				}

				buffer[i] = static_cast<uint8_t>(input);
				actual_bytes_read++;
			}
		} catch (const std::exception &e) {
			return HardwareStatus::kError;
		}

		if (actual_bytes_read == 0) {
			return HardwareStatus::kTimeout;
		}

		if (actual_bytes_read < bytes_read) {
			return HardwareStatus::kPartialRead;
		}

		return HardwareStatus::kSuccess;
	}

	HardwareStatus write(std::span<const uint8_t> buffer, size_t &bytes_written) {

		if (buffer.empty()) {

			bytes_written = 0;
			return HardwareStatus::kSuccess;
		}

		try {
			// Bufferdaki tüm verileri yazdır
			size_t count = 0;
			for (const auto &byte : buffer) {

				std::cout.put(static_cast<char>(byte));

				if (std::cout.fail()) {

					std::cout.clear(); // Hata bayrağını temizle
					bytes_written = count;
					return HardwareStatus::kError;
				}
				++count;
			}

			// Çıktıyı hemen gönder
			std::cout.flush();

			if (std::cout.fail()) {

				std::cout.clear();
				bytes_written = count;
				return HardwareStatus::kError;
			}

			bytes_written = count;
			return HardwareStatus::kSuccess;
		} catch (const std::exception &e) {

			bytes_written = 0;
			return HardwareStatus::kError;
		}
	}
} // namespace console::shell::hardware