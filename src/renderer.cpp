#include "headers/renderer.hpp"
#include "headers/ultils.hpp"
#include "headers/color.hpp"

#include <iostream>
#include <iomanip>

using namespace std;

static void printCard(const Card* card) {
	if (!card) {
		cout << "[  ]";
		return;
	}
	if (!card->faceUp) {
		cout << "[##]";
		return;
	}
	if (card->isRed()) setTextColor(TextColor::BRIGHT_RED);
	else setTextColor(TextColor::BRIGHT_WHITE);
	cout << card->toString();
	resetTextColor();
}

void Renderer::draw(const KlondikeGame& game) {
	clearScreen();
	// Top row: Stock, Waste, Foundation
	cout << "Stock: ";
	cout << (game.stock.empty()? string("[  ]") : string("[##]"));
	cout << "    Waste: ";
	if (game.waste.empty()) cout << "[  ]"; else printCard(&game.waste.back());
	cout << "\nFoundations: ";
	for (int i = 0; i < KlondikeGame::NumFoundation; ++i) {
		const Card* top = game.foundation[i].top();
		printCard(top);
		cout << ' ';
	}
	cout << "\n\nTableau:\n";
	// Determine max height
	int maxH = 0;
	for (int i = 0; i < KlondikeGame::NumTableau; ++i) {
		maxH = max<int>(maxH, game.tableau[i].cards.size());
	}
	for (int row = 0; row < maxH; ++row) {
		for (int col = 0; col < KlondikeGame::NumTableau; ++col) {
			const auto& pile = game.tableau[col].cards;
			if (row < (int)pile.size()) printCard(&pile[row]);
			else cout << "    ";
			cout << ' ';
		}
		cout << '\n';
	}
	cout << "\nCommands: d=draw, w1..w7 move waste->tab, wf move waste->foundation,"
	        " tXY move X cards from tableau T1 to T2 (e.g., t312),"
	        " tfN move tableau N -> foundation, ftNM foundation M -> tableau N, q=quit\n";
}

void Renderer::message(const std::string& msg) {
	cout << msg << "\n";
}


