#pragma once

#include <string>
#include "klondike.hpp"

class Renderer {
public:
	static void draw(const KlondikeGame& game);
	static void message(const std::string& msg);
};


