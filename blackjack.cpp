#include <array>
#include <iostream>
#include <string>
#include <list>
#include <cstdlib>
using namespace std;
class Card {
	private:
    string suit;
	string	rank;
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
};

class Hand {
	public:
    list<Card> cards;
    int getScore(){ return score; };
    private:
    int score;
    void sum();
};

class Player {
    private:
	Hand hand;
	void choice();
	public:
    void draw();
    Hand getHand(){ return hand; };
};

class Dealer {
    private:
	Hand hand;
	public:
    void draw();
    Hand getHand(){ return hand; };
};

class Deck {
	public: 
    list<Card> cards;
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
           deck.show();
       };
};

void Game::judge() {
    int playerScore = player.getHand().getScore();
    int dealerScore = dealer.getHand().getScore();
    if( playerScore > dealerScore) {
        cout << "You win!";
    } else if (playerScore > dealerScore) {
        cout << "Draw.";
    } else {
        cout << "You lose.";
    }
}

void Hand::sum() {
    int sum = 0;
    for (Card card:cards) {
        sum += atoi(card.getRank().data());
    }
    score = sum;
    cout << score << endl;
}


int main() {
    std::cout << "test" << std::endl;
    Game game;
    game.start();
    return 0;
}