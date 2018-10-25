#include <array>
#include <iostream>
#include <string>

int main() {
    std::cout << "test" << std::endl;
    return 0;
}
class Player {
    private:
	Hand hand;
	void choice()
	public:
    void draw()
}

class Dealer {
    private:
	Hand hand;
	public:
    void draw()
}

class Deck {
	public: 
    array<card> cards;
}

class Game {
    private:
    Player player;
	Dealer dealer;
	Deck    deck;

	void judge()
    puvlic:
   	void start();

}
void Game::judge() {
    int playerSum = player.getHand().sum();
    int delaerSum = dealer.getHand().sum();
    if( playerSum > dealerSum) {
        cout << "You win!";
    } else if (playerSum > dealerSum) {
        cout << "Draw.";
    } else {
        cout << "You lose.";
    }
}

int Hand::Sum() {
    int sum = 0;
    for (int card:cards) {
        sum += card.getValue;
    }
}
class Hand {
	public:
    array<card> cards;
    int sum();
}

class Card {
	private:
    std::string suits;
	int	value;

    public:
    int getvalue(){ return value; };
}