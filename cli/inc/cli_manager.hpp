#pragma once

#include "character_encodings/utf_8.hpp"
#include "cli_buffer_manager.hpp"
#include "cli_input_handler.hpp"

namespace console::cli {

	enum class CLIStatus
	{
		kMessageReady = 0,
		kMessageNotReady,
	};

	class CliManager {

	public:
		CLIStatus run(std::uint8_t input) {

			CLIStatus ret_val = CLIStatus::kMessageNotReady;

			if (ButtonType::kEnter == m_input_type) {

				m_buffer_manager.clear_buffer();
			}

			m_input_type = m_input_handler.handle_input(input);

			switch (m_input_type) {

				case ButtonType::kNormal: {

					m_buffer_manager.add_to_buffer(input);
					break;
				}
				case ButtonType::kBackspace: {

					m_buffer_manager.delete_last_character();
					break;
				}
				case ButtonType::kDelete: {

					break;
				}
				case ButtonType::kEnter: {

					ret_val = CLIStatus::kMessageReady;
					break;
				}
				case ButtonType::kTAB:
					// Handle tab
					break;
				case ButtonType::kEscapeSequence:
					// Handle escape sequence
					break;
				default:
					break;
			}

			return ret_val;
		}

	private:
		CLIInputHandler m_input_handler;
		CliBufferManager m_buffer_manager;
		ButtonType m_input_type{ButtonType::kNotDefined};
	};
} // namespace console::cli