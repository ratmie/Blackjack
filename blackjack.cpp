#include <array>
#include <iostream>
#include <string>
#include <list>
using namespace std;
class Card {
	private:
    std::string suits;
	int	value;

    public:
    int getValue(){ return value; };
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
        sum += card.getValue();
        if (card.getValue()){}
    }
    score = sum;
}




int main() {
    std::cout << "test" << std::endl;
    Game game;
    game.start();
    return 0;
}