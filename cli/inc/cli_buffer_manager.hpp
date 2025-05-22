#pragma once

#include "cli_config.h"
#include "cli_types.h"
#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>

namespace console::cli {

	class CliBufferManager {

	public:
		CliBufferManager() {
			m_buffer.fill(0);
		}

		void add_to_buffer(std::uint8_t character) {
			if (m_buffer_position >= config::sc_buffer_size) {
				m_buffer_position = 0;
			}
			m_buffer[m_buffer_position++] = character;
		}

		const std::array<const char *, config::sc_max_token_count> &get_tokens() {

			m_tokens.fill(nullptr);
			std::size_t token_count = 0;
			m_tokens[token_count++] = m_buffer.data();

			for (std::size_t i = 0; i < m_buffer_position; ++i) {

				if (m_buffer[i] == ' ') {

					m_buffer[i] = '\0';
					if (token_count < config::sc_max_token_count) {

						m_tokens[token_count++] = m_buffer.data() + i + 1;
					}
				}
				else if (m_buffer[i] == '\n') {

					m_buffer[i] = '\0';
				}
			}

			m_token_count = token_count;
			return m_tokens;
		}

		std::size_t get_token_count() const {

			return m_token_count;
		}

		void delete_last_character() {

			if (m_buffer_position > 0) {

				m_buffer[--m_buffer_position] = 0;
			}
		}

		void clear_buffer() {

			m_buffer_position = 0;
			m_token_count = 0;
			m_buffer.fill(0);
		}

		std::size_t get_buffer_position() const {
			return m_buffer_position;
		}

		const std::array<char, config::sc_buffer_size> &get_buffer() const {
			return m_buffer;
		}

	private:
		std::size_t m_buffer_position{0};
		std::size_t m_token_count{0};
		std::array<char, config::sc_buffer_size> m_buffer;
		std::array<const char *, config::sc_max_token_count> m_tokens;
	};
} // namespace console::cli
