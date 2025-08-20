#pragma once

#include <vector>
#include <optional>
#include "card.hpp"

class Pile {
public:
	std::vector<Card> cards;

	bool empty() const { return cards.empty(); }
	const Card* top() const { return cards.empty() ? nullptr : &cards.back(); }
	Card* top() { return cards.empty() ? nullptr : &cards.back(); }

	void push(const Card& c) { cards.push_back(c); }
	Card pop() { Card c = cards.back(); cards.pop_back(); return c; }

	// For tableau: flip last facedown if needed
	void flipLastIfNeeded() {
		if (!cards.empty() && !cards.back().faceUp) {
			cards.back().faceUp = true;
		}
	}
};


