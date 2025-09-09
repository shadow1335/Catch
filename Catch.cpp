// Catch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <fstream>
#include <SFML/Audio.hpp>

// Game States
enum class GameState {HomeScreen,Instructions, Playing, GameOver, Leaderboard};

sf::Clock gameClock;


class FallingObject
{
public:
	sf::CircleShape shape;
	float speed;

	FallingObject(float x, float speed)
	{
		shape.setRadius(20.f);
		shape.setFillColor(sf::Color::Blue);
		shape.setPosition(x,0);
		this->speed = speed;
	}
	void update()
	{
		shape.move(0.f, speed);
	}
	sf::Vector2f getPosition()
	{
		return shape.getPosition();
	}
};
class Heart
{
public:
	sf::CircleShape leftCircle, rightCircle;
	sf::ConvexShape bottomTriangle;
	float speed;


	Heart(float x, float fallSpeed)
	{
		speed = fallSpeed;




		leftCircle.setRadius(10.5f);
		leftCircle.setFillColor(sf::Color::Red);
		leftCircle.setPosition(x ,0);
	


		rightCircle.setRadius(10.5f);
		rightCircle.setFillColor(sf::Color::Red);
		rightCircle.setPosition(x + 10.f, 0);
		

		bottomTriangle.setPointCount(3);
		bottomTriangle.setPoint(0, sf::Vector2f(0.f , 10.f));
		bottomTriangle.setPoint(1, sf::Vector2f(30.f, 10.f));
		bottomTriangle.setPoint(2, sf::Vector2f(15.f,30.f));
		bottomTriangle.setFillColor(sf::Color::Red);
		bottomTriangle.setPosition(x,5.f);

	}

	void update()
	{
		leftCircle.move(0, speed);
		rightCircle.move(0, speed);
		bottomTriangle.move(0, speed);


	}
	sf::Vector2f getPosition()
	{
		return leftCircle.getPosition();
	}
	void draw(sf::RenderWindow &window) const
	{
		window.draw(leftCircle);
		window.draw(rightCircle);
		window.draw(bottomTriangle);
	}
};
class Bomb
{
public:
	sf::CircleShape body;
	sf::RectangleShape fuse;

	float speed;
	

	Bomb(float x, float fallSpeed)
	{
		speed = fallSpeed;

		body.setRadius(15.f);
		body.setFillColor(sf::Color::Black);
		body.setPosition(x, 0);

		fuse.setSize(sf::Vector2f(5.f,10.f));
		fuse.setFillColor(sf::Color::Yellow);
		fuse.setPosition(x + 10.f, -10.f);


		
	}
	void update()
	{
		body.move(0, speed);
		fuse.move(0, speed);
		
	}
	sf::Vector2f getPosition()
	{
		return body.getPosition();
	}
	void draw(sf::RenderWindow& window) const
	{
		
		window.draw(body);
		window.draw(fuse);
		
	}
	


};

class FakeHeart
{
public:
	sf::CircleShape leftCircle, rightCircle;
	sf::ConvexShape bottomTriangle;
	float speed;

	FakeHeart(float x, float fallSpeed)
	{
		speed = fallSpeed;
		

		leftCircle.setRadius(10.5f);
		leftCircle.setFillColor(sf::Color(255, 192, 203));
		leftCircle.setPosition(x, 0);
		


		rightCircle.setRadius(10.5f);
		rightCircle.setFillColor(sf::Color(255, 192, 203));
		rightCircle.setPosition(x + 10.f, 0);
		

		bottomTriangle.setPointCount(3);
		bottomTriangle.setPoint(0, sf::Vector2f(0.f, 10.f));
		bottomTriangle.setPoint(1, sf::Vector2f(30.f, 10.f));
		bottomTriangle.setPoint(2, sf::Vector2f(15.f, 30.f));
		bottomTriangle.setFillColor(sf::Color(255, 192, 203));
		bottomTriangle.setPosition(x, 5.f);
	}
	void update()
	{
		
		leftCircle.move(0, speed);
		rightCircle.move(0, speed);
		bottomTriangle.move(0, speed);


	}
	sf::Vector2f getPosition()
	{
		return leftCircle.getPosition();
	}
	void draw(sf::RenderWindow& window) const
	{
		window.draw(leftCircle);
		window.draw(rightCircle);
		window.draw(bottomTriangle);
	}
};
class Shield
{
public:
	
	sf::ConvexShape body;
	float speed;
	

	Shield(float x, float fallSpeed)
	{
		speed = fallSpeed;

		body.setPointCount(6);
		body.setPoint(0, sf::Vector2f(20.f, 50.f)); //bottom center
		body.setPoint(1, sf::Vector2f(5.f, 20.f)); //upper left
		body.setPoint(2, sf::Vector2f(15.f, 20.f)); // upper middle left
		body.setPoint(3, sf::Vector2f(20.f, 5.f));// top center
		body.setPoint(4, sf::Vector2f(25.f, 20.f)); //upper middle right
		body.setPoint(5, sf::Vector2f(35.f, 20.f)); //upper right
		body.setPosition(x, 0);
		body.setFillColor(sf::Color(150, 75, 0, 200));
		body.setOutlineColor(sf::Color::White);
		body.setOutlineThickness(1);
		
	}
	void update()
	{
		body.move(0, speed);
	}
	sf::Vector2f getPosition()
	{
		return body.getPosition();
	}

};
class Magnet
{
public:

	sf::RectangleShape body;
	sf::CircleShape leftEnd, rightEnd;
	float speed;

	Magnet(float x, float fallSpeed)
	{
		speed = fallSpeed;

		body.setSize(sf::Vector2f(40.f, 10.f));
		body.setFillColor(sf::Color::Red);
		body.setPosition(x, 0);

		leftEnd.setRadius(8.f);
		leftEnd.setFillColor(sf::Color(220, 220, 220));
		leftEnd.setPosition(x - 8.f, 0);

		rightEnd.setRadius(8.f);
		rightEnd.setFillColor(sf::Color(220, 220, 220));
		rightEnd.setPosition(x + 32.f, 0);

	}

	void update()
	{
		body.move(0, speed);
		rightEnd.move(0, speed);
		leftEnd.move(0, speed);
	}
	sf::Vector2f getPosition()
	{
		return body.getPosition();
	}

	void draw(sf::RenderWindow& window) const
	{
		window.draw(body);
		window.draw(leftEnd);
		window.draw(rightEnd);
	}
};
void drawText(sf::RenderWindow& window, sf::Font& font, const std::string& text, float x, float y, int size, sf::Color color)
{
	sf::Text displayText;
	displayText.setFont(font);
	displayText.setString(text);
	displayText.setCharacterSize(size);
	displayText.setFillColor(color);
	displayText.setPosition(x,y);
	window.draw(displayText);
}
class SoundManager
{
private:
	std::map<std::string, sf::SoundBuffer> soundsBuffers;
	std::map<std::string, sf::Sound> sounds;
	std::map<std::string, std::shared_ptr<sf::Music>> backgroundMusics; 
	std::shared_ptr<sf::Music> currentMusic;

public:
	void loadSound(const std::string& name, const std::string& filename)
	{
		sf::SoundBuffer buffer;
		if (buffer.loadFromFile(filename))
		{
			soundsBuffers[name] = buffer;
			sounds[name].setBuffer(soundsBuffers[name]);
		}
	}

	void playSound(const std::string& name)
	{
		if (sounds.find(name) != sounds.end())
		{
			sounds[name].play();
		}
	}
	void loadMusic(const std::string& name, const std::string& filename)
	{
		std::shared_ptr<sf::Music> music = std::make_shared<sf::Music>();
		if (music->openFromFile(filename))
		{
			music->setLoop(true);
			backgroundMusics[name] = music;
		}
	}
	void playMusic(const std::string& name)
	{
		if (backgroundMusics.find(name) != backgroundMusics.end())
		{
			if (currentMusic)
			{
				currentMusic->stop();
			}
			currentMusic = backgroundMusics[name];
			currentMusic->play();
		}
	}
	void stopMusic()
	{
		if (currentMusic)
		{
			currentMusic->stop();
		}
	}
};

std::vector<int> highScores;

void loadHighScores()
{
	std::ifstream file("highscores.txt");
	if (file)
	{
		int score;
		while (file >> score)
		{
			highScores.push_back(score);
		}
		file.close();
	}
}
void saveHighScores()
{
	std::ofstream file("highscores.txt");
	for (int score : highScores) {
		file << score << std::endl;
	}
	file.close();
}
void updateHighScores(int newScore)
{
	highScores.push_back(newScore);
	std::sort(highScores.rbegin(), highScores.rend());
	if (highScores.size() > 5) highScores.pop_back();
	saveHighScores();

}

sf::Color getBackgroundColor(float elapsedTime)
{
	sf::Color dayColor(135, 206, 235);
	sf::Color nightColor(25, 25, 112);

	float cycleTime = 60.0f;
	float t = (std::sin(elapsedTime / cycleTime));

	return sf::Color(static_cast<sf::Uint8>(dayColor.r * t + nightColor.r * (1-t)), 
		static_cast<sf::Uint8>(dayColor.g * t + nightColor.g * (1 - t)),
		static_cast<sf::Uint8>(dayColor.b * t + nightColor.b * (1 - t)));

}




int main()
{
	
	// Create the Window
	sf::RenderWindow window(sf::VideoMode(800,600), "Catch the Falling Object");
	window.setFramerateLimit(60);


	window.setVerticalSyncEnabled(true);
	float gameStartTime = 0.f;

	// Create the Window
	sf::RectangleShape player(sf::Vector2f(100.f, 20.f));
	player.setFillColor(sf::Color::Green);
	player.setPosition(360.f, 550.f); // Start position
	float playerSpeed = 5.0f;
	loadHighScores();

	float elapsedTime = gameClock.getElapsedTime().asSeconds();
	float sunTime = elapsedTime - gameStartTime;
	sf::Color bgColor = getBackgroundColor(elapsedTime);

	//Load font for score display
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cerr << "Error loading font!" << std::endl;
		return -1;
	}


	int score = 0;
	float lives = 10.0f;
	std::vector<FallingObject> fallingObjects;
	std::vector<Heart> hearts; //List of heart objects
	std::vector<Bomb> bombs;
	std::vector<FakeHeart> fakeHearts;
	std::vector<Shield> shields;
	std::vector<Magnet> magnets;

	int level = 1;

	//Falling objects setup

	float objectSpeed = 1.0f;
	int maxObjects = 2; // Initial max number of objects
	int spawnCooldown = 100; // Lower value means more frequent spawns
	int frameCounter = 0;
	float lastSpawnX = 400.f; // Store last spawn x position

	
	sf::Clock heartClock;
	float heartSpawnInterval = 10.0f;
	
	sf::Clock bombClock;
	float bombSpawnInterval = 10.0f;

	sf::Clock fakeHeartClock;
	float fakeHeartSpawnInterval = 10.0f;

	sf::Clock shieldClock;
	bool shieldActive = false;
	float shieldDuration = 13.0f;

	sf::Clock shieldSpawnClock;
	float shieldSpawnInterval = 10.0f;

	float baseSpeed = 0.8f;
	float adjustSpeed = 1.0f;

	int streakCounter = 0;
	float multiplier = 1.0f;

	


	bool magnetActive = false;
	sf::Clock magnetClock;
	float magRange = 200.0f;
	float magSpawnInterval = 10.0f;
	float magDuration = 5.0f;

	

	SoundManager soundManager;
	soundManager.loadSound("catch","object.wav");
	soundManager.loadSound("bomb", "explosion.wav");
	soundManager.loadSound("fake", "fakeHeart.wav");
	soundManager.loadSound("lives", "gainLives.wav");
	soundManager.loadSound("shield", "shield.wav"); 
	soundManager.loadSound("hurt", "hitHurt.wav");

	soundManager.loadMusic("Home", "homeScreen.ogg");
	soundManager.loadMusic("Play","gamePlaying.ogg");

	// set up RNG
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	//Start home screen
	GameState gameState = GameState::HomeScreen;
	soundManager.playMusic("Home");
	// Game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		window.clear(bgColor);

		if (gameState == GameState::HomeScreen)
		{
			drawText(window, font, "Catch the Falling Objects!", 200, 200, 40, sf::Color::White);
			drawText(window, font, "Press ENTER to Start", 250, 300, 30, sf::Color::Green);
			drawText(window, font, "Press I for Instructions", 250, 350, 30, sf::Color::Yellow);
			drawText(window, font, "Press L for Leaderboard", 250, 400, 30, sf::Color::Cyan);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				gameState = GameState::Playing;
				score = 0;
				lives = 10.0f;
				level = 1;
				baseSpeed = 0.8f;
				adjustSpeed = 1.0f;
				fallingObjects.clear();
				hearts.clear();
				soundManager.stopMusic();
				soundManager.playMusic("Play");

				gameStartTime = gameClock.getElapsedTime().asSeconds();
				

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
			{
				gameState = GameState::Instructions;
				
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			{
				gameState = GameState::Leaderboard;

			}
		}
		else if (gameState == GameState::Instructions)
		{
			drawText(window, font, "How to Play:", 250, 150, 40, sf::Color::White);
			drawText(window, font, "- Move with Left/Right arrows", 200, 220, 30, sf::Color::Green);
			drawText(window, font, "- Catch blue objects to gain points", 200, 260, 30, sf::Color::Blue);
			drawText(window, font, "- Avoid bombs", 200, 300, 30, sf::Color::Magenta);
			drawText(window, font, "- Catch hearts to regain health", 200, 340, 30, sf::Color::Red);
			drawText(window, font, "Press BACKSPACE to return", 250, 400, 30, sf::Color::Yellow);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
			{
				gameState = GameState::HomeScreen;
			}
		}
		else if (gameState == GameState::Playing)
		{
			//move player with arrow keys
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.getPosition().x > 0)
				player.move(-playerSpeed, 0.f);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player.getPosition().x < 720.f)
				player.move(playerSpeed, 0.f);

			//Increase difficulty based on level
			objectSpeed = 0.1f + (level * 0.5f); // Tiny increase every point
			objectSpeed = std::min(5.0f, objectSpeed); // Cap speed at 1.0f
			maxObjects = 1 + (level); // Slowly increase object count
			maxObjects = std::min(5, maxObjects); // Cap at 5 objects max
			spawnCooldown = std::max(50, 100 - (level * 10)); // Gradually reduce spawn time
			adjustSpeed = 1.0f + (level * 0.1f); //Speed for Items
			fakeHeartSpawnInterval = 10.0f - (level / 5.0f);
			fakeHeartSpawnInterval = std::min(4.0f, fakeHeartSpawnInterval);
			bombSpawnInterval = 10.0f - (level / 5.0f);
			bombSpawnInterval = std::min(4.0f, bombSpawnInterval);
			heartSpawnInterval = 10.0f - (level / 5.0f);
			heartSpawnInterval = std::min(6.0f, heartSpawnInterval);

			//Spawn Object
			frameCounter++;
			if (frameCounter >= spawnCooldown)
			{
				if (fallingObjects.size() < maxObjects)
				{
					float x;
					int spawnZone = std::rand() % 3;
					if (spawnZone == 0)
					{
						x = static_cast<float>(std::rand() % 250);
					}
					else if (spawnZone == 1)
					{
						x = 275 + static_cast<float>((std::rand() % 250));
					}
					else
					{
						x = 550.0f + static_cast<float>((std::rand() % 250));
					}

					if (std::abs(x - lastSpawnX > 100.f) || fallingObjects.empty())
					{
						fallingObjects.push_back((FallingObject(x, objectSpeed)));
						lastSpawnX = x;

						frameCounter = 0;
					}
				}
			}
			//Spawn Hearts
			if (lives < 6.5f && heartClock.getElapsedTime().asSeconds() >= heartSpawnInterval)
			{
				float x = 50 + static_cast<float>(std::rand() % (window.getSize().x - 100));
				hearts.push_back(Heart(x, baseSpeed * adjustSpeed));
				heartClock.restart();
			}

			if (level >= 5 && bombClock.getElapsedTime().asSeconds() >= bombSpawnInterval)
			{
				float x = 50 + static_cast<float>(std::rand() % (window.getSize().x - 100));
				bombs.push_back(Bomb(x, baseSpeed * adjustSpeed));
				bombClock.restart();
			}

			if (level >= 5 && fakeHeartClock.getElapsedTime().asSeconds() >= fakeHeartSpawnInterval)
			{
				float x = 50 + static_cast<float>(std::rand() % (window.getSize().x - 100));
				fakeHearts.push_back(FakeHeart(x, baseSpeed * adjustSpeed));
				fakeHeartClock.restart();
			}
			if (!shieldActive)
			{
				if (level >= 5 && shieldSpawnClock.getElapsedTime().asSeconds() >= shieldSpawnInterval)
				{
					float x = 50 + static_cast<float>(std::rand() % (window.getSize().x - 100));
					shields.push_back(Shield(x, baseSpeed * adjustSpeed));
					shieldSpawnClock.restart();
				}
			}
			if (!magnetActive)
			{
				if (level >= 2 && magnetClock.getElapsedTime().asSeconds() >= magSpawnInterval)
				{
					float x = 50 + static_cast<float>(std::rand() % (window.getSize().x - 100));
					magnets.push_back(Magnet(x, baseSpeed * adjustSpeed));
					magnetClock.restart();
				}
			}
			// Update falling objects (if player catches an object)
			sf::Vector2f playerPos = player.getPosition();
			for (auto it = fallingObjects.begin(); it != fallingObjects.end();)
			{
				it->update();
				if (magnetActive)
				{
					sf::Vector2f objectPos = it->getPosition();
					sf::Vector2f direction = playerPos - objectPos;


					float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
					if (length < magRange)
					{
						if (length > 0)
						{
							direction /= length;
						}

						float magnetPullSpeed = 3.0f;
						it->shape.move(direction * magnetPullSpeed);
					}
				}

				if (player.getGlobalBounds().intersects(it->shape.getGlobalBounds()))
				{
					soundManager.playSound("catch");

					streakCounter++;
					if (streakCounter >= 5)
					{
						multiplier = 2.0f;
					}

					score += (1 * multiplier);
				

					level = (score / 10) + 1;
					it = fallingObjects.erase(it);
				}
				else if (it->shape.getPosition().y > window.getSize().y)
				{
					soundManager.playSound("hurt");
					lives -= 0.5f;
					streakCounter = 0;
					multiplier = 1.0f;
					it = fallingObjects.erase(it);
				}
				else
				{
					++it;
				}
			}
			for (auto it = hearts.begin(); it != hearts.end();)
			{
				it->update();
				if (magnetActive)
				{
					sf::Vector2f heartPos = it->getPosition();
					sf::Vector2f direction = playerPos - heartPos;


					float length = std::sqrt(direction.x * direction.x + direction.y * direction.y );
					if (length < magRange)
					{
						if (length > 0)
						{
							direction /= length;
						}

						float magnetPullSpeed = 3.0f;
						it->leftCircle.move(direction * magnetPullSpeed);
						it->rightCircle.move(direction* magnetPullSpeed);
						it->bottomTriangle.move(direction* magnetPullSpeed);
					}
				}


				if (player.getGlobalBounds().intersects(it->leftCircle.getGlobalBounds()) || 
					player.getGlobalBounds().intersects(it->rightCircle.getGlobalBounds())||
					player.getGlobalBounds().intersects(it->bottomTriangle.getGlobalBounds()))
				{
					lives = std::min(lives + 0.25f, 10.0f);
					soundManager.playSound("lives");
					it = hearts.erase(it);
				}
				else if (it->getPosition().y > window.getSize().y)
				{
					it = hearts.erase(it);
				}
				else {
					++it;
				}
			}
			for (auto it = bombs.begin(); it != bombs.end();)
			{
				it->update();

				if (player.getGlobalBounds().intersects(it->body.getGlobalBounds()) || 
					player.getGlobalBounds().intersects(it->fuse.getGlobalBounds()))
				{
					if (!shieldActive)
					{
						lives -= 1.0f;
						soundManager.playSound("bomb");

						streakCounter = 0;
						multiplier = 1.0f;
					}
					it = bombs.erase(it);
				}
				else if (it->getPosition().y > window.getSize().y)
				{
					it = bombs.erase(it);
				}
				else {
					++it;
				}
			}
			for (auto it = fakeHearts.begin(); it != fakeHearts.end();)
			{
				it->update();
				if (player.getGlobalBounds().intersects(it->leftCircle.getGlobalBounds()) ||
					player.getGlobalBounds().intersects(it->rightCircle.getGlobalBounds()) ||
					player.getGlobalBounds().intersects(it->bottomTriangle.getGlobalBounds()))
				{
					if (!shieldActive)
					{
						lives = std::max(lives - 1.0f, 0.0f);
						soundManager.playSound("fake");

						streakCounter = 0;
						multiplier = 1.0f;
					}
					it = fakeHearts.erase(it);
				}
				else if (it->getPosition().y > window.getSize().y)
				{
					it = fakeHearts.erase(it);
				}
				else
				{
					it++;
				}
			}
			for (auto it = shields.begin(); it != shields.end();)
			{
				it->update();
				if (player.getGlobalBounds().intersects(it->body.getGlobalBounds()))
				{
					shieldActive = true;
					soundManager.playSound("shield");
					shieldClock.restart();
					it = shields.erase(it);
				}
				else if (it->getPosition().y > window.getSize().y)
				{
					it = shields.erase(it);
				}
				else
				{
					it++;
				}
			}
			for (auto it = magnets.begin(); it != magnets.end();)
			{
				it->update();
				if (player.getGlobalBounds().intersects(it->body.getGlobalBounds()) ||
					player.getGlobalBounds().intersects(it->leftEnd.getGlobalBounds()) ||
					player.getGlobalBounds().intersects(it->rightEnd.getGlobalBounds()))
				{
					magnetActive = true;
					magnetClock.restart();
					it = magnets.erase(it);

				}
				else if (it->getPosition().y > window.getSize().y)
				{
					it = magnets.erase(it);
				}
				else
				{
					it++;
				}
			}
			if (shieldActive && magnetActive)
			{
				player.setOutlineThickness(5.f);
				player.setOutlineColor(sf::Color(182, 210, 128));
			}
			else if (magnetActive)
			{
				player.setOutlineThickness(5.f);
				player.setOutlineColor(sf::Color(255, 165, 0));
			}
			else if (shieldActive)
			{
				player.setOutlineThickness(5.f);
				player.setOutlineColor(sf::Color::Cyan);
			}
			else
			{
				player.setOutlineThickness(0.f);
			}
			if (shieldActive && shieldClock.getElapsedTime().asSeconds() >= shieldDuration)
			{
				shieldActive = false;
			}
			if (magnetActive && magnetClock.getElapsedTime().asSeconds() >= magDuration)
			{
				magnetActive = false;
			}
			if (lives <= 0.0f)
			{
				gameState = GameState::GameOver;
				soundManager.stopMusic();
			}
			

			drawText(window, font, "Score: " + std::to_string(score), 10, 10, 24, sf::Color::White);
			drawText(window, font, "Lives: " + std::to_string(lives).substr(0, 4), 10, 50, 24, sf::Color::Red);
			drawText(window, font, "Level: " + std::to_string(level), 10, 90, 24, sf::Color::Green);
			window.draw(player);

			for (auto& object : fallingObjects)
			{
				window.draw(object.shape);
			}
			for (const auto& heart : hearts)
			{
				heart.draw(window);
			}
			for (const auto& bombObject : bombs)
			{
				bombObject.draw(window);
			}
			for (const auto& fakeHeartObject : fakeHearts)
			{
				fakeHeartObject.draw(window);
			}
			for (const auto& shieldObject : shields)
			{
				window.draw(shieldObject.body);
			}
			for (const auto& magnet : magnets)
			{
				magnet.draw(window);
			}
		

		}
		else if (gameState == GameState::GameOver)
		{
			drawText(window, font, "Game Over!", 300, 200, 50, sf::Color::Red);
			drawText(window, font, "Final Score: " + std::to_string(score), 300, 300, 30, sf::Color::White);
			drawText(window, font, "Press H for Home Screen", 250, 400, 30, sf::Color::Green);
			drawText(window, font, "Press L for Leaderboard", 250, 450, 30, sf::Color::Yellow);


			static bool scoreSaved = false;

			if (!scoreSaved)
			{
				updateHighScores(score);
				scoreSaved = true;
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
			{
				gameState = GameState::HomeScreen;
				soundManager.playMusic("Home");
				scoreSaved = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			{
				gameState = GameState::Leaderboard;
				scoreSaved = false;
			}
		}
		else if (gameState == GameState::Leaderboard)
		{
			drawText(window, font, "Leaderboard", 300, 150, 40, sf::Color::White);

			for (size_t i = 0; i < highScores.size(); i++)
			{
				drawText(window, font, std::to_string(i + 1) + ". " + std::to_string(highScores[i]), 300, 200 + (static_cast<float>(i) * 40), 30, sf::Color::Green);
			}

			drawText(window, font, "Press BACKSPACE to return", 250, 450, 30, sf::Color::Green);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
			{
				gameState = GameState::HomeScreen;
				soundManager.playMusic("Home");
			}

		}
		window.display();
	}
	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file