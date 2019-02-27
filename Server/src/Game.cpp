//
// Created by maverick on 12/2/19.
//
#include <sstream>
#include "Game.h"
Game::Game(unsigned viewWidth, unsigned viewHeight)
	:window(sf::VideoMode(viewHeight, viewHeight), "Kurukshetra Server"),
	 textures(Textures::textureNumber),
	 fonts(GameFonts::fontNumber),
	 server(sf::Socket::AnyPort+7000),
	 viewWidth(viewWidth),
	 viewHeight(viewHeight),
	 baseHeight(1900),
	 leftExtremePoint(1500),
	 rightExtremePoint(5500)
{
	window.setVerticalSyncEnabled(true);

	minimapView.setSize(sf::Vector2f(200.f, 200.f));
	minimapView.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));


	textures.load(Textures::skyTexture, "../Media/Textures/kurukshetra.png");
	textures.load(Textures::groundTexture, "../Media/Textures/stoneTile.png");
	textures.load(Textures::wallTexture, "../Media/Textures/stoneTile.png");
	textures.load(Textures::rockTexture, "../Media/Textures/rockPlatform.png");
//	textures.load(Textures::grassTexture, "../Media/Textures/grass.png");
	textures.load(Textures::playerTexture, "../Media/Textures/fox.png");
	textures.load(Textures::enemyTexture, "../Media/Textures/enemy.png");
	textures.load(Textures::bulletTexture, "../Media/Textures/bullet.png");

	textures.get(Textures::skyTexture).setRepeated(true);
	textures.get(Textures::playerTexture).setSmooth(true);
	textures.get(Textures::bulletTexture).setSmooth(true);
	textures.get(Textures::grassTexture).setSmooth(true);

	sky.setPosition(sf::Vector2f(0, 0));
	sky.setSize(sf::Vector2f(7000, 2500));
	sky.setTexture(&textures.get(Textures::skyTexture));

	player.SetData(&textures.get(Textures::playerTexture), sf::Vector2u(3, 9), 0.3f, 150.0f, sf::Vector2f(leftExtremePoint + 500, baseHeight));
	enemy.SetData(&textures.get(Textures::enemyTexture), sf::Vector2u(3, 9), 0.3f, 150.0f,sf::Vector2f(leftExtremePoint + 500, baseHeight));


    gameView.SetSize(sf::Vector2f(viewWidth, viewHeight));
    gameView.SetViewPort(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    gameView.Update(player.GetBody(), window, sky);


    fonts.load(GameFonts::info, "../Media/Fonts/DejaVuSans.ttf");
	for (int i=0; i<2; i++)
		info[i].setFont(fonts.get(GameFonts::info));
//	std::ostringstream s;
//	s<<player.health;
//	info[0].setString("Health: " + s.str());
//	s.str("");
//	s<<player.mana;
//	info[1].setString("Mana: " + s.str());

	for (int i=0; i<2; i++)
	{
		info[i].setPosition(viewWidth, viewHeight/1.5f * (i+1));
		info[i].setFillColor(sf::Color::Red);
	}

	ground.SetData(&textures.get(Textures::groundTexture), sf::Vector2f(4000, 200), sf::Vector2f(leftExtremePoint, baseHeight));
	ground.SetTextureRect(sf::IntRect(0, 0, 4000, 200));
    textures.get(Textures::groundTexture).setRepeated(true);

    setWalls();

//
//	const sf::Vector2f grassSize = sf::Vector2f(100, 100);
//	grass.setPosition(sf::Vector2f(1200.f, baseHeight));
//	grass.setSize(grassSize);
//	grass.setTexture(&textures.get(Textures::grassTexture));
//	grass.setOrigin(grassSize);

	rock.setPosition(sf::Vector2f(300, baseHeight));
	rock.setSize(sf::Vector2f(300, 50));
	rock.setTexture(&textures.get(Textures::rockTexture));

	playerAnimation.SetData(&textures.get(Textures::playerTexture), sf::Vector2u(3,9), 0.3f);
	enemyAnimation.SetData(&textures.get(Textures::enemyTexture), sf::Vector2u(3,9), 0.3f);
}

void Game::run() {
	while (window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void Game::update() {
    gameView.SetView(window);
    float elapsedTime = clock.restart().asSeconds();
    if(server.getM_playersConnected()>0)
	{
    	static sf::Vector2f data=server.getRecievedData();
    	player.collisionTest(player, walls, baseHeight, leftExtremePoint, rightExtremePoint);
		player.Update( &textures.get(Textures::bulletTexture), elapsedTime, gameView, baseHeight, window,sky, server);
		enemy.Update( &textures.get(Textures::bulletTexture), elapsedTime, gameView, baseHeight, window,data);
	}
    else
    	player.Update(&textures.get(Textures::bulletTexture), elapsedTime, gameView, walls, baseHeight, leftExtremePoint, rightExtremePoint, window, sky);
   // enemy.Update( &textures.get(Textures::bulletTexture), elapsedTime,  gameView, baseHeight, window);

	std::ostringstream s;
	s<<player.health;
	info[0].setString("Health: " + s.str());
	s.str("");
	s<<player.mana;
	info[1].setString("Mana: " + s.str());
}

void Game::processEvents() {
	sf::Event event = {};
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				// update the view to the new size of the window
//            sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
//            mWindow.setView(sf::View(visibleArea));
				ResizedWindow(window, gameView);
				break;
		}
	}
}

void Game::render() {
	window.clear();
	window.draw(sky);
//	window.draw(grass);
//	window.draw(rock);
    ground.Draw(window);
    for(unsigned long i = 0; i < walls.size(); i++)
        walls[i].Draw(window);
	player.Draw(window);
	if(server.getM_playersConnected()>0)
		enemy.Draw(window);
	for (int i=0; i<2 ; i++)
		window.draw(info[i]);
	window.display();

}

void Game::ResizedWindow(sf::RenderWindow &window, Camera &view) {
	float aspectratio = window.getSize().x / float(window.getSize().y);

	view.SetSize(sf::Vector2f(viewWidth * aspectratio, viewHeight));
}

void Game::setWalls() {
	walls.push_back(Platform(&textures.get(Textures::wallTexture), sf::Vector2f(150, 250), sf::Vector2f(leftExtremePoint + 0, baseHeight - 250)));
	walls.push_back(Platform(&textures.get(Textures::wallTexture), sf::Vector2f(150, 250), sf::Vector2f(rightExtremePoint - 150, baseHeight - 250)));
}
