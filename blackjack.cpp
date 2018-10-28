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
		switch(r) {
			case 1: rank ='A'; break;
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
			case 12: rank ='Q'; break;
			case 13: rank ='K'; break;
		}
	};
	string getSuit(){ return suit; };
	string getRank(){ return rank; };
	Side getSide() { return side; };
	void setSide(Side data) { side = data; };
};

class Hand {
	public:
	vector<Card> cards;
	int getScore(){ return score; };
	void showAll() {
		for(Card card: cards) {
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
		for (string suit: suits) {
			for (int rank = 1; rank <= 13; rank++) {
				cards.push_back(Card(suit, rank));
			}
		}
	}
	void show() {
		for(Card card: cards) {
			cout << card.getSuit() << card.getRank() << endl;
		}
	}
	void cut() {
		random_device seed_gen{};
		mt19937 random_engine(seed_gen());
		shuffle(begin(cards), end(cards), random_engine);
	}
};
class Player {
	private:
	Hand hand;
	void choice();
	public:
	void draw();
	Hand getHand(){ return hand; };
	void hit(Deck& deck);
};

class Dealer {
	private:
	Hand hand;
	public:
	void draw();
	Hand getHand(){ return hand; };
	void hit(Deck& deck);
};

class Game {
	private:
	Player player;
	Dealer dealer;
	Deck    deck;

	void judge();
	public:
   	void start(){
		cout << "game start" << endl;
		//deck.show();
		deck.cut();
		//cout << "Cut" << endl;
		//deck.show();
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
			if (key == "c") break;
			if (key == "h") {
				player.hit(deck);
				player.getHand().showAll();
				cout << player.getHand().getScore() << endl;
			}
			if (key == "s") {
				while (dealer.getHand().getScore() < 16) {
					dealer.hit(deck);
				}
				judge();
			}
		}
	};
};

void Game::judge() {
	int playerScore = player.getHand().getScore();
	int dealerScore = dealer.getHand().getScore();
	if( playerScore > dealerScore) {
		cout << "You win!" << endl;
	} else if (playerScore == dealerScore) {
		cout << "Draw." << endl;
	} else {
		cout << "You lose." << endl;
	}
}

void Hand::sum() {
	int sum = 0;
	int numberOfA = 0;
	for (Card card:cards) {
		string rank = card.getRank();
		sum += atoi(rank.data());

		if (rank == "A" || rank == "J" || rank == "Q" || rank == "K") {
			sum += 10;
		} 
		if (rank == "A") {
			numberOfA++;
		}
	}
	while(numberOfA > 0) {
		if (sum > 21) {
			sum -= 9;
		}
		numberOfA--;
	}
	score = sum;
	//cout << "score:" << score << endl;
}

void Player::hit(Deck& deck) {
	hand.cards.push_back(deck.cards.back());
	deck.cards.pop_back();
	hand.sum();
	if(hand.getScore() > 21) {
	    cout << "You Bust" << endl;
		hand.showAll();
	}
};

void Dealer::hit(Deck& deck) {
	hand.cards.push_back(deck.cards.back());
	deck.cards.pop_back();
	hand.sum();
	if(hand.getScore() > 21) {
	    cout << "Dealer Bust" << endl;
		hand.showAll();
	}
};
int main() {
	std::cout << "test" << std::endl;
	Game game;
	game.start();
	return 0;
}