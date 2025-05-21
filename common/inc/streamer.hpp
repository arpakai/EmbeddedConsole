#pragma once

#include "communication_stream.hpp"
#include "macos_terminal.hpp"

namespace console::streamer {

	using streamer_type = decltype(console::common::CommunicationStream<console::shell::hardware::MacOSTerminal>{});
	auto instance() -> streamer_type &;

} // namespace console::streamer
