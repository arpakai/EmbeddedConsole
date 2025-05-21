#pragma once

#include <cstdint>

namespace console::cli::character_encodings {
	// UTF-8 encoding
	static constexpr char sc_space_char = ' ';
	static constexpr char sc_new_line_char = '\r';
	static constexpr char sc_backspace_hex = 0x7F;
	static constexpr char sc_tab_hex = 0x09;
	static constexpr char sc_escape_char = 0x1B;
	static constexpr char sc_delete_str[] = {sc_escape_char, 0X5B, '3', '~'};
	static constexpr char sc_up_arrow[] = {sc_escape_char, 0x5B, 'A'};
	static constexpr char sc_down_arrow[] = {sc_escape_char, 0x5B, 'B'};
	static constexpr char sc_left_arrow[] = {sc_escape_char, 0x5B, 'D'};
	static constexpr char sc_right_arrow[] = {sc_escape_char, 0x5B, 'C'};
	static constexpr char sc_ctrl_left_arrow[] = {sc_escape_char, 0x5B, '1', ';', '5'};
	static constexpr char sc_home_button[] = {sc_escape_char, 0x5B, 'H'};
	static constexpr char sc_end_button[] = {sc_escape_char, 0x5B, 'F'};
	static constexpr char sc_new_line_str[] = "\r\n";
	static constexpr char sc_terminal_clear[] = "\033[2J";
	static constexpr char sc_terminal_clear_string[] = "clear";
	static constexpr char sc_move_cursor_home[] = "\033[H";
	static constexpr char sc_backspace_str[] = "\b \b";
} // namespace console::cli::character_encodings