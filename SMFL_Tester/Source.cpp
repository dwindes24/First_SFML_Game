#include <iostream>
#include "Game.h"

using namespace std;
using namespace sf;

int main()
{

	//Init rand
	srand(static_cast<unsigned>(time(NULL)));
	//Init game
	Game game;


	//Game loop
	while (game.running() && !game.getEndGame())
	{
		cout << "game.running is : " << game.running() << "      " << "game.getEndGame is : " << game.getEndGame() << endl;

		//Update game
		game.update();
		
		//Draw game
		game.render();
	}

	//End App
	return 0;
}