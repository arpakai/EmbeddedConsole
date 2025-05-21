#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <span>

#include "hardware_status.h"

namespace console::common {

	template <typename T> class CommStream;

	template <typename T> using CommStreamManipulator = CommStream<T> &(*)(CommStream<T> &);

	template <typename T> CommStream<T> &endl(CommStream<T> &stream);

	template <typename T> CommStream<T> &flush(CommStream<T> &stream);

	template <typename T> class CommunicationStream {

		using namespace console::shell::hardware;

	public:
		explicit CommStream() {

			clear_buffer();
		}

		[[nodiscard]] HardwareStatus init() {

			m_stream_ready = UARTStatus::kSuccess == mp_comm.start_rx();

			if (!m_stream_ready) {

				return HardwareStatus::kError;
			}

			return HardwareStatus::kSuccess;
		}

		~CommStream() {

			flush_buffer();
		}

		HardwareStatus receive_data(std::uint8_t &character) {

			std::span<std::uint8_t> read_buf{&character, 1};

			if (0 == mp_comm.read(read_buf)) {

				return HardwareStatus::kError;
			}

			return HardwareStatus::kSuccess;
		}

		CommStream &operator<<(const char c) {

			if (!m_stream_ready) {

				return *this;
			}

			append_to_buffer(&c, sizeof(char));
			return *this;
		}

		CommStream &operator<<(const char *str) {

			if (!m_stream_ready) {

				return *this;
			}

			std::size_t length = strlen(str);
			append_to_buffer(str, length);
			return *this;
		}

		CommStream &operator<<(int number) {

			if (!m_stream_ready) {

				return *this;
			}

			snprintf(m_num_char_buffer.data(), sc_num_char_buffer, "%d", number);
			std::size_t length = strlen(m_num_char_buffer.data());
			append_to_buffer(m_num_char_buffer.data(), length);
			return *this;
		}

		CommStream &operator<<(float number) {

			if (!m_stream_ready) {

				return *this;
			}

			snprintf(m_num_char_buffer.data(), sc_num_char_buffer, "%f", number);

			std::size_t length = strlen(m_num_char_buffer.data());
			append_to_buffer(m_num_char_buffer.data(), length);
			return *this;
		}

		CommStream &operator<<(CommStreamManipulator<T> manip) {

			if (!m_stream_ready) {

				return *this;
			}

			return manip(*this);
		}

		void flush_buffer() {

			if (m_buffer_position > 0 && m_stream_ready) {

				std::span<std::uint8_t> t_span{m_buffer};

				if (UARTStatus::kSuccess != mp_comm.write(t_span.subspan(0, m_buffer_position))) {

					return;
				}

				rtos::this_thread::sleep_for(std::chrono::milliseconds(1));

				clear_buffer();
			}
		}

		void clear_buffer() {

			m_buffer_position = 0;
		}

		friend CommStream &endl<>(CommStream &stream);
		friend CommStream &flush<>(CommStream &stream);

	private:
		bool append_to_buffer(const char *str, std::size_t length) {

			if ((m_buffer_position + length) >= sc_buffer_size) {

				flush_buffer();

				if (length >= sc_buffer_size) {

					std::span<std::uint8_t> t_span{m_buffer};

					if (UARTStatus::kSuccess != mp_comm.write(t_span.subspan(0, m_buffer_position))) {

						return false;
					}
				}
			}

			std::memcpy(m_buffer.begin() + m_buffer_position, str, length);
			m_buffer_position += length;

			return true;
		}

		static constexpr std::size_t sc_buffer_size = 1024;
		static constexpr std::size_t sc_num_char_buffer = 16;

		T mp_comm;

		bool m_stream_ready{false};
		std::size_t m_buffer_position;
		std::array<char, sc_num_char_buffer> m_num_char_buffer;
		std::array<std::uint8_t, sc_buffer_size> m_buffer;
	};

	template <typename T> CommStream<T> &endl(CommStream<T> &stream) {

		stream << "\r\n";
		stream.flush_buffer();
		return stream;
	}

	template <typename T> CommStream<T> &flush(CommStream<T> &stream) {

		stream.flush_buffer();
		return stream;
	}
} // namespace console::common
