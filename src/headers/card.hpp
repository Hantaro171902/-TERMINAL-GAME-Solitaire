#pragma once

#include <string>

enum class Suit {
	Clubs = 0,
	Diamonds = 1,
	Hearts = 2,
	Spades = 3
};

enum class Rank {
	Ace = 1,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King
};

struct Card {
	Suit suit;
	Rank rank;
	bool faceUp;

	Card() : suit(Suit::Clubs), rank(Rank::Ace), faceUp(false) {}
	Card(Suit s, Rank r, bool up=false) : suit(s), rank(r), faceUp(up) {}

	bool isRed() const {
		return suit == Suit::Diamonds || suit == Suit::Hearts;
	}

	std::string suitSymbol() const {
		switch (suit) {
			case Suit::Clubs: return "\u2663";   // ♣
			case Suit::Diamonds: return "\u2666"; // ♦
			case Suit::Hearts: return "\u2665";   // ♥
			case Suit::Spades: return "\u2660";   // ♠
		}
		return "?";
	}

    static std::string rankToString(Rank r) {
		switch (r) {
			case Rank::Ace: return "A";
			case Rank::Two: return "2";
			case Rank::Three: return "3";
			case Rank::Four: return "4";
			case Rank::Five: return "5";
			case Rank::Six: return "6";
			case Rank::Seven: return "7";
			case Rank::Eight: return "8";
			case Rank::Nine: return "9";
			case Rank::Ten: return "10";
			case Rank::Jack: return "J";
			case Rank::Queen: return "Q";
			case Rank::King: return "K";
		}
		return "?";
	}

	std::string toString() const {
		if (!faceUp) return "[??]";
		return "[" + rankToString(rank) + suitSymbol() + "]";
	}
};

inline int rankValue(Rank r) {
	return static_cast<int>(r);
}


