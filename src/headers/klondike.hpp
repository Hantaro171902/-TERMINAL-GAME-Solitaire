#pragma once

#include <array>
#include <vector>
#include "deck.hpp"
#include "pile.hpp"

// Simple terminal Klondike solitaire (draw-1) rules
class KlondikeGame {
public:
	static constexpr int NumTableau = 7;
	static constexpr int NumFoundation = 4;

	Deck stock;          // face-down deck to draw from
	std::vector<Card> waste; // face-up waste pile
	std::array<Pile, NumFoundation> foundation; // suit piles (ascending A->K)
	std::array<Pile, NumTableau> tableau;       // tableau piles

	KlondikeGame();
	void newGame(unsigned int seed);

	// Moves
	bool drawFromStock();
	bool moveWasteToTableau(int tIdx);
	bool moveWasteToFoundation();
	bool moveTableauToTableau(int fromIdx, int toIdx, int count);
	bool moveTableauToFoundation(int fromIdx);
	bool moveFoundationToTableau(int fIdx, int toIdx);

	bool isWon() const;
};


