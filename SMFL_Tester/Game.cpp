#include "Game.h"


//Private Functions
void Game::initVars()
{
	this->window = nullptr;

	//Game Logic
	this->points = 0;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 7;
	this->mouseHeld = false;
	this->endGame = false;
	this->health = 100;
}

void Game::initWindow()
{	
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new RenderWindow(this->videoMode, "First SFML Game", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
	this->enemy1.setPosition(10.f,10.f);
	this->enemy1.setSize(Vector2f(100.0f, 100.0f));
	this->enemy1.setFillColor(Color::Cyan);
	
}

void Game::initFonts()
{
	if (!(this->font.loadFromFile("Fonts/Dosis-Light.ttf")))
		cout << "error loading font" << endl;
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(36);
	this->uiText.setFillColor(Color::White);
	this->uiText.setString("NONE YET");
}

//constructor
Game::Game()
{
	this->initVars();
	this->initWindow();
	this->initEnemies();
	this->initFonts();
	this->initText();
}
//destructor
Game::~Game()
{
	delete this->window;
}

//Getters



const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

void Game::spawnEnemies()
{
	this->enemy1.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy1.getSize().x)),
			0.f
	);
	//Random type 
	int type = rand() % 5;
	switch (type)
	{
	case 0:
		this->enemy1.setFillColor(Color::Magenta);
		this->enemy1.setSize(Vector2f(15.f, 15.f));
		break;
	case 1:
		this->enemy1.setFillColor(Color::Blue);
		this->enemy1.setSize(Vector2f(30.f, 30.f));
		break;
	case 2:
		this->enemy1.setFillColor(Color::Red);
		this->enemy1.setSize(Vector2f(50.f, 50.f));
		break;
	case 3:
		this->enemy1.setFillColor(Color::White);
		this->enemy1.setSize(Vector2f(70.f, 70.f));
		break;
	case 4:
		this->enemy1.setFillColor(Color::Green);
		this->enemy1.setSize(Vector2f(100.f, 100.f));
		break;
	default:
		break;
	}
	
	this->enemies.push_back(this->enemy1);
}

void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->e))
	{
		switch (this->e.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->e.key.code == Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updateMousePositions()
{
	this->mousePosWindow = Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{		//checking if we have enough enemies
	if (this->enemies.size() < this->maxEnemies)
	{		//checking if time to spawn enemy
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{	//spawn and reset timer
			this->spawnEnemies();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//Now move all enemies downward and delete if neccessary
	for (int i = 0; i < this->enemies.size(); i++)
	{
		//enemy move speed
		this->enemies[i].move(0.f, 5.f);
		//check if below the screen 
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{	//delete if below the screen
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
		}
	}
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		//check if mouse is being held down
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			float size;
			//look thru each enemy
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				//if mouse click is within an enemy delete it and add score
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					size = enemies[i].getSize().x;
					switch ((int)size)
					{
					case 10:
						points += 10;
						break;
					case 30:
						points += 7;
						break;
					case 50:
						points += 5;
						break;
					case 70:
						points += 3;
						break;
					default:
						points += 1;
						break;

					}

					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);

					
					
				}
			}
		}
	}
	// mouse not being held down anymore
	else
	{
		this->mouseHeld = false;
	}
}

void Game::updateText()
{
	stringstream ss;
	ss << "Points: " << this->points << "\n " << "Health: " << this->health;
	this->uiText.setString(ss.str());
}

//Functions
void Game::update()
{
	
	this->pollEvents();
	if (this->endGame == false)
	{
		this->updateMousePositions();
		this->updateText();
		this->updateEnemies();
	}
	//end condition
	if (this->health <= 0)
		this->endGame = true;
}

void Game::renderEnemies(RenderTarget& target)
{
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

void Game::renderText(RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::render()
{
	this->window->clear();
	//draw game
	this->renderEnemies(*this->window);
	this->renderText(*this->window);
	this->window->display();
}

