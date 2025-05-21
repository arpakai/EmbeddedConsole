#include "streamer.hpp"

namespace console::streamer {

	auto instance() -> streamer_type & {

		static streamer_type s_streamer{};
		return s_streamer;
	}

} // namespace console::streamer
