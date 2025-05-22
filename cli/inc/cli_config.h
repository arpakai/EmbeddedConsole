#pragma once

#include <cstddef>
#include <cstdint>

namespace console::cli::config {

	static constexpr std::size_t sc_buffer_size = 256;
	static constexpr std::size_t sc_history_size = 10;
	static constexpr std::size_t sc_max_command_length = 32;
	static constexpr std::size_t sc_prompt_length = 10;
	static constexpr std::size_t sc_max_escape_sequence_length = 8;

	static constexpr std::size_t sc_max_token_count = 16;
	static constexpr std::size_t sc_max_token_length = 16;

	static constexpr std::size_t sc_extended_ascii_start = 0x80;

} // namespace console::cli::config