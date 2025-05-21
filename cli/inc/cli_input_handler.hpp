#pragma once

#include <cstddef>
#include <cstdint>
#include <span>

#include "character_encodings/utf_8.hpp"
#include "cli_config.h"
#include "cli_types.h"

namespace console::cli {

	/**
	 * @brief Class to handle input from the command line interface.
	 * It identifies the type of input received and handles escape sequences.
	 */
	class CLIInputHandler {

	public:
		CLIInputHandler() {

			reset();
		}

		ButtonType handle_input(std::uint8_t character) {

			char t_character = static_cast<std::uint8_t>(character);

			if (config::sc_extended_ascii_start <= character) {

				m_last_input_type = ButtonType::kNotDefined;
				return m_last_input_type;
			}

			switch (t_character) {

				case character_encodings::sc_backspace_hex:
					m_last_input_type = ButtonType::kBackspace;
					break;
				case character_encodings::sc_new_line_char:
					m_last_input_type = ButtonType::kEnter;
					reset();
					break;
				case character_encodings::sc_tab_hex:
					m_last_input_type = ButtonType::kTAB;
					break;
				case character_encodings::sc_escape_char:
					m_last_input_type = ButtonType::kEscapeSequence;
					add_to_buffer(t_character);
					break;
				default:
					m_last_input_type = handle_normal_input(t_character);
					break;
			}

			return m_last_input_type;
		}

	private:
		ButtonType handle_normal_input(char &character) {

			if (ButtonType::kEscapeSequence == m_last_input_type) {

				m_last_input_type = handle_escape_sequence(character);
			}
			else {

				m_last_input_type = ButtonType::kNormal;
			}

			return m_last_input_type;
		}

		ButtonType handle_escape_sequence(std::uint8_t character) {

			add_to_buffer(character);

			if (sc_escape_sequence_max_buffer_size == m_buffer_position) {

				m_last_input_type = ButtonType::kNotDefined;
			}
			else if (0 == strncmp(m_buffer.data() + m_buffer_position - 3, character_encodings::sc_right_arrow, 3)) {

				m_last_input_type = ButtonType::kArrowRight;
			}
			else if (0 == strncmp(m_buffer.data() + m_buffer_position - 3, character_encodings::sc_left_arrow, 3)) {

				m_last_input_type = ButtonType::kArrowLeft;
			}
			else if (0 == strncmp(m_buffer.data() + m_buffer_position - 3, character_encodings::sc_down_arrow, 3)) {

				m_last_input_type = ButtonType::kArrowDown;
			}
			else if (0 == strncmp(m_buffer.data() + m_buffer_position - 3, character_encodings::sc_up_arrow, 3)) {

				m_last_input_type = ButtonType::kArrowUp;
			}
			else if (0 == strncmp(m_buffer.data() + m_buffer_position - 3, character_encodings::sc_end_button, 3)) {

				m_last_input_type = ButtonType::kEnd;
			}
			else if (0 == strncmp(m_buffer.data() + m_buffer_position - 3, character_encodings::sc_home_button, 3)) {

				m_last_input_type = ButtonType::kHome;
			}
			else if (0 == strncmp(m_buffer.data() + m_buffer_position - 4, character_encodings::sc_delete_str, 4)) {

				m_last_input_type = ButtonType::kDelete;
			}
			else {

				m_last_input_type = ButtonType::kEscapeSequence;
			}

			if (ButtonType::kEscapeSequence != m_last_input_type) {

				reset();
			}

			return m_last_input_type;
		}

		void add_to_buffer(std::uint8_t character) {

			if (m_buffer_position >= sc_escape_sequence_max_buffer_size) {
				m_buffer_position = 0;
			}
			m_buffer[m_buffer_position++] = character;
		}

		void reset() {

			m_last_input_type = ButtonType::kNotDefined;
			m_buffer_position = 0;
			m_buffer.fill(0);
		}

		static constexpr std::size_t sc_escape_sequence_max_buffer_size = 6;

		ButtonType m_last_input_type{ButtonType::kNotDefined};
		std::size_t m_buffer_position{0};
		std::array<char, sc_escape_sequence_max_buffer_size> m_buffer{};
	};
} // namespace console::cli