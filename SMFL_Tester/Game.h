#pragma once

#include <iostream>
#include <Vector>
#include <ctime>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;
using namespace std;

//Class that acts as game engine
//Wrapper Class
class Game
{
private:
	//private variables
	RenderWindow* window;
	VideoMode videoMode;
	Event e;

	//Mouse Positions
	Vector2i mousePosWindow;
	Vector2f mousePosView;


	//Resources
	Font font;

	//Text
	Text uiText;

	//Game Logic
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;
	bool endGame;
	
	//Game Objects
	vector<RectangleShape> enemies;
	RectangleShape enemy1;


	//private functions
	void initVars();
	void initWindow();
	void initEnemies();
	void initFonts();
	void initText();

public:

	//Constructors/ destructors
	Game();
	virtual ~Game();

	//Getters
	const bool running() const;
	const bool getEndGame() const;

	//Functions
	void spawnEnemies();
	void pollEvents();
	void updateMousePositions();
	void updateEnemies();
	void updateText();
	void update();
	void renderEnemies(RenderTarget& target);
	void renderText(RenderTarget& target);
	void render();
};

