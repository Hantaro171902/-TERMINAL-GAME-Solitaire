// Klondike solitaire terminal game (C++)
#include "headers/ultils.hpp"
#include "headers/color.hpp"
#include "headers/klondike.hpp"
#include "headers/renderer.hpp"

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

static void help() {
	cout << "\nControls:\n"
	        "  d       : draw from stock (or recycle waste)\n"
	        "  wN      : move waste to tableau N (1..7)\n"
	        "  wf      : move waste to foundation\n"
	        "  tABC    : move A cards from tableau B to tableau C (e.g., t312)\n"
	        "  tfN     : move top of tableau N to foundation\n"
	        "  ftNM    : move foundation M to tableau N\n"
	        "  r       : restart new game\n"
	        "  q       : quit\n";
}

int main() {
	srand((unsigned)time(nullptr));
	KlondikeGame game;
	Renderer::draw(game);
	help();
	for (;;) {
		cout << "> ";
		string cmd; if (!(cin >> cmd)) break;
		bool ok = false;
		if (cmd == "q") break;
		else if (cmd == "h") help();
		else if (cmd == "r") { game.newGame((unsigned)time(nullptr)); ok = true; }
		else if (cmd == "d") ok = game.drawFromStock();
		else if (cmd == "wf") ok = game.moveWasteToFoundation();
		else if (cmd.size()==2 && cmd[0]=='w') {
			int t = cmd[1]-'1';
			ok = game.moveWasteToTableau(t);
		}
		else if (cmd.size()==4 && cmd[0]=='t') {
			int count = cmd[1]-'0';
			int from = cmd[2]-'1';
			int to   = cmd[3]-'1';
			ok = game.moveTableauToTableau(from, to, count);
		}
		else if (cmd.size()==3 && cmd.substr(0,2)=="tf") {
			int from = cmd[2]-'1';
			ok = game.moveTableauToFoundation(from);
		}
		else if (cmd.size()==4 && cmd.substr(0,2)=="ft") {
			int t = cmd[2]-'1';
			int f = cmd[3]-'1';
			ok = game.moveFoundationToTableau(f, t);
		}

		Renderer::draw(game);
		if (!ok) Renderer::message("Invalid move");
		if (game.isWon()) {
			Renderer::message("You won! Press r for a new game or q to quit.");
		}
	}
	return 0;
}

