#pragma once

#include <vector>
#include <random>
#include <algorithm>
#include "card.hpp"

class Deck {
public:
	std::vector<Card> cards;

	Deck() { reset(); }

	void reset() {
		cards.clear();
		for (int s = 0; s < 4; ++s) {
			for (int r = 1; r <= 13; ++r) {
				cards.emplace_back(static_cast<Suit>(s), static_cast<Rank>(r), true);
			}
		}
	}

	void shuffle(unsigned int seed) {
		std::mt19937 rng(seed);
		std::shuffle(cards.begin(), cards.end(), rng);
	}

	bool empty() const { return cards.empty(); }
	Card draw() { Card c = cards.back(); cards.pop_back(); return c; }
};


