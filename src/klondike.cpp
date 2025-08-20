#include "headers/klondike.hpp"

#include <cassert>
#include <ctime>
#include <algorithm>

using std::vector;

static bool oppositeColor(const Card& a, const Card& b) {
	return a.isRed() != b.isRed();
}

KlondikeGame::KlondikeGame() {
	newGame(static_cast<unsigned int>(time(nullptr)));
}

void KlondikeGame::newGame(unsigned int seed) {
	// reset all
	stock.reset();
	stock.shuffle(seed);
	waste.clear();
	for (auto& f : foundation) f.cards.clear();
	for (auto& t : tableau) t.cards.clear();

	// deal tableau
	// pile i gets i face-down then 1 face-up
	for (int i = 0; i < NumTableau; ++i) {
		for (int j = 0; j < i; ++j) {
			Card c = stock.draw();
			c.faceUp = false;
			tableau[i].push(c);
		}
		Card c = stock.draw();
		c.faceUp = true;
		tableau[i].push(c);
	}
	// remaining cards to stock (already there)
	for (auto& c : stock.cards) c.faceUp = false;
}

bool KlondikeGame::drawFromStock() {
	if (!stock.empty()) {
		Card c = stock.draw();
		c.faceUp = true;
		waste.push_back(c);
		return true;
	} else {
		// recycle waste back to stock (face-down) if stock empty
		if (waste.empty()) return false;
		// move all waste back in reverse order
		for (int i = (int)waste.size() - 1; i >= 0; --i) {
			Card c = waste[i];
			c.faceUp = false;
			stock.cards.push_back(c);
		}
		waste.clear();
		return true;
	}
}

bool KlondikeGame::moveWasteToTableau(int tIdx) {
	if (tIdx < 0 || tIdx >= NumTableau) return false;
	if (waste.empty()) return false;
	Card c = waste.back();
	Card* top = tableau[tIdx].top();
	if (top) {
		if (!top->faceUp) return false;
		if (oppositeColor(c, *top) && rankValue(c.rank) + 1 == rankValue(top->rank)) {
			tableau[tIdx].push(c);
			waste.pop_back();
			return true;
		}
		return false;
	} else {
		if (c.rank == Rank::King) {
			tableau[tIdx].push(c);
			waste.pop_back();
			return true;
		}
		return false;
	}
}

bool KlondikeGame::moveWasteToFoundation() {
	if (waste.empty()) return false;
	Card c = waste.back();
	int s = static_cast<int>(c.suit);
	Card* top = foundation[s].top();
	if (!top) {
		if (c.rank == Rank::Ace) {
			foundation[s].push(c);
			waste.pop_back();
			return true;
		}
		return false;
	}
	if (rankValue(c.rank) == rankValue(top->rank) + 1 && c.suit == top->suit) {
		foundation[s].push(c);
		waste.pop_back();
		return true;
	}
	return false;
}

bool KlondikeGame::moveTableauToTableau(int fromIdx, int toIdx, int count) {
	if (fromIdx < 0 || fromIdx >= NumTableau || toIdx < 0 || toIdx >= NumTableau) return false;
	if (fromIdx == toIdx) return false;
	auto& from = tableau[fromIdx].cards;
	auto& to = tableau[toIdx].cards;
	if ((int)from.size() < count) return false;
	// ensure moving sequence is face-up and descending alternating colors
	int start = (int)from.size() - count;
	if (!from[start].faceUp) return false;
	for (int i = start; i < (int)from.size() - 1; ++i) {
		const Card& a = from[i];
		const Card& b = from[i+1];
		if (!(a.faceUp && b.faceUp)) return false;
		if (!(oppositeColor(a, b) && rankValue(a.rank) == rankValue(b.rank) + 1)) return false;
	}
	// check destination
	if (to.empty()) {
		if (from[start].rank != Rank::King) return false;
	} else {
		const Card& dest = to.back();
		if (!dest.faceUp) return false;
		if (!(oppositeColor(from[start], dest) && rankValue(from[start].rank) + 1 == rankValue(dest.rank))) return false;
	}
	// move
	vector<Card> moved;
	moved.reserve(count);
	for (int i = 0; i < count; ++i) {
		moved.push_back(from[from.size() - count + i]);
	}
	from.resize(from.size() - count);
	to.insert(to.end(), moved.begin(), moved.end());
	// flip source top if needed
	if (!tableau[fromIdx].cards.empty() && !tableau[fromIdx].cards.back().faceUp) {
		tableau[fromIdx].cards.back().faceUp = true;
	}
	return true;
}

bool KlondikeGame::moveTableauToFoundation(int fromIdx) {
	if (fromIdx < 0 || fromIdx >= NumTableau) return false;
	auto& from = tableau[fromIdx];
	Card* c = from.top();
	if (!c || !c->faceUp) return false;
	int s = static_cast<int>(c->suit);
	Card* top = foundation[s].top();
	if (!top) {
		if (c->rank == Rank::Ace) {
			foundation[s].push(*c);
			from.cards.pop_back();
			from.flipLastIfNeeded();
			return true;
		}
		return false;
	}
	if (rankValue(c->rank) == rankValue(top->rank) + 1 && c->suit == top->suit) {
		foundation[s].push(*c);
		from.cards.pop_back();
		from.flipLastIfNeeded();
		return true;
	}
	return false;
}

bool KlondikeGame::moveFoundationToTableau(int fIdx, int toIdx) {
	if (fIdx < 0 || fIdx >= NumFoundation || toIdx < 0 || toIdx >= NumTableau) return false;
	auto& from = foundation[fIdx];
	if (from.empty()) return false;
	Card c = from.pop();
	auto& to = tableau[toIdx];
	if (to.empty()) {
		if (c.rank == Rank::King) { to.push(c); return true; }
		from.push(c); return false;
	}
	Card* dest = to.top();
	if (dest && dest->faceUp && oppositeColor(c, *dest) && rankValue(c.rank) + 1 == rankValue(dest->rank)) {
		to.push(c);
		return true;
	}
	from.push(c);
	return false;
}

bool KlondikeGame::isWon() const {
	for (const auto& f : foundation) {
		if (f.cards.size() != 13) return false;
	}
	return true;
}


