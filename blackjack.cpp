#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <numeric>
#include <iterator>
using namespace std;
enum Side {
	frot,
	back
};

class Card {
private:
	string suit;
	string	rank;
	Side side;
public:
	Card(string s, int r) {
		suit = s;
		switch (r) {
		case 1: rank = 'A'; break;
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10: rank = to_string(r); break;
		case 11: rank = 'J'; break;
		case 12: rank = 'Q'; break;
		case 13: rank = 'K'; break;
		}
	};
	string getSuit() { return suit; };
	string getRank() { return rank; };
	Side getSide() { return side; };
	void setSide(Side data) { side = data; };
};

class Hand {
public:
	vector<Card> cards;
	int getScore() { return score; };
	void showAll() {
		for (Card card : cards) {
			cout << card.getSuit() << " " << card.getRank() << ", ";
		}
		cout << endl;
	}
	void sum();
private:
	int score;
};

class Deck {
public:
	vector<Card> cards;
	Deck() {
		array<string, 4> suits = { {"heart", "diamond", "club", "spade"} };
		for (string suit : suits) {
			for (int rank = 1; rank <= 13; rank++) {
				cards.push_back(Card(suit, rank));
			}
		}
	}
	void show() {
		for (Card card : cards) {
			cout << card.getSuit() << card.getRank() << endl;
		}
	}
	void cut() {
		random_device seed_gen{};
		mt19937 random_engine(seed_gen());
		shuffle(begin(cards), end(cards), random_engine);
	}
};

class CardHolder {
private:
	Hand hand;
protected:
	string name = "";
public:
	string getName() { return name; };
	Hand getHand() { return hand; };
	void hit(Deck& deck);
};

class Player : public CardHolder {
public:
	Player() { this->name = "Player"; }

};

class Dealer : public CardHolder {
public:
	Dealer() { this->name = "Dealer"; }
};

class Game {
private:
	Player player;
	Dealer dealer;
	Deck    deck;

	void judge();
public:
	bool checkBust(CardHolder holder);

	void start() {
		cout << "game start" << endl;
		deck.cut();

		dealer.hit(deck);
		cout << "Dealer:";
		dealer.getHand().showAll();

		dealer.hit(deck);

		player.hit(deck);
		player.hit(deck);
		player.getHand().showAll();
		cout << "yourScore" << player.getHand().getScore() << endl;

		cout << "\"hit\" or \"stand\"" << endl;
		string key;

		while (cin >> key) {
			if (key == "h") {
				player.hit(deck);
				player.getHand().showAll();
				cout << player.getHand().getScore() << endl;
				if (checkBust(player)) {
					break;
				}
			}
			else if (key == "s") {
				while (dealer.getHand().getScore() < 17) {
					dealer.hit(deck);
					if (checkBust(dealer)) {
						break;
					}
				}
				judge();
				break;
			}
			else {
				break;
			}
		}
	};
};

void Game::judge() {
	int playerScore = player.getHand().getScore();
	int dealerScore = dealer.getHand().getScore();
	cout << "Dealer Cards :" << endl;
	dealer.getHand().showAll();
	cout << "Dealer Score :" << dealerScore << endl;

	if (playerScore > dealerScore) {
		cout << "You win!" << endl;
	}
	else if (playerScore == dealerScore) {
		cout << "Draw." << endl;
	}
	else {
		cout << "You lose." << endl;
	}
}

void Hand::sum() {
	int sum = 0;
	int numberOfA = 0;
	for (Card card : cards) {
		string rank = card.getRank();
		sum += atoi(rank.data());

		if (rank == "A" || rank == "J" || rank == "Q" || rank == "K") {
			sum += 10;
		}
		if (rank == "A") {
			numberOfA++;
		}
	}
	while (numberOfA > 0) {
		if (sum > 21) {
			sum -= 9;
		}
		numberOfA--;
	}
	score = sum;
	//cout << "score:" << score << endl;
}


void CardHolder::hit(Deck& deck) {
	hand.cards.push_back(deck.cards.back());
	deck.cards.pop_back();
	hand.sum();

};

bool Game::checkBust(CardHolder holder) {
	if (holder.getHand().getScore() > 21) {
		cout << holder.getName() << " Bust" << endl;
		holder.getHand().showAll();
		return true;
	}
	return false;
}
bool askContinue() {
	char gameContinue;
	cout << "Next game ? press Y or N" << endl;
	cin >> gameContinue;
	return gameContinue == 'y';
}
int main() {
	std::cout << "test" << std::endl;

	for (bool gameContinue = true; gameContinue; gameContinue = askContinue()) {
		Game game;
		game.start();
	}
	return 0;
}