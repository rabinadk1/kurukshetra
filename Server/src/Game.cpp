//
// Created by maverick on 12/2/19.
//
#include <sstream>
#include <Game.h>

#include "Game.h"
Game::Game(unsigned viewWidth, unsigned viewHeight)
	:window(sf::VideoMode(viewHeight, viewHeight), "Kurukshetra"),
	 textures(Textures::textureNumber),
	 fonts(GameFonts::fontNumber),
	 server(5000),
	 viewWidth(viewWidth),
	 viewHeight(viewHeight),
	 baseHeight(1900)
{
	window.setVerticalSyncEnabled(true);

	gameView.SetCenter(sf::Vector2f(1000.f, baseHeight - 200));
	gameView.SetSize(sf::Vector2f(viewWidth, viewHeight));
	minimapView.setSize(sf::Vector2f(200.f, 200.f));
	gameView.SetViewPort(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	minimapView.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));


	textures.load(Textures::skyTexture, "../Media/Textures/kurukshetra.png");
	textures.load(Textures::groundTexture, "../Media/Textures/stoneTile.png");
	textures.load(Textures::rockTexture, "../Media/Textures/rockPlatform.png");
//	textures.load(Textures::grassTexture, "../Media/Textures/grass.png");
	textures.load(Textures::playerTexture, "../Media/Textures/fox.png");
	textures.load(Textures::enemyTexture, "../Media/Textures/fox.png");
	textures.load(Textures::bulletTexture, "../Media/Textures/bullet.png");

	textures.get(Textures::skyTexture).setRepeated(true);
	textures.get(Textures::groundTexture).setRepeated(true);
	textures.get(Textures::playerTexture).setSmooth(true);
	textures.get(Textures::bulletTexture).setSmooth(true);
	textures.get(Textures::grassTexture).setSmooth(true);

	sky.setPosition(sf::Vector2f(0, 0));
	sky.setSize(sf::Vector2f(4000, 2500));
	sky.setTexture(&textures.get(Textures::skyTexture));

	player.SetData(&textures.get(Textures::playerTexture), sf::Vector2u(3, 9), 0.3f, 150.0f, sf::Vector2f(1000.f, baseHeight - player.getPosition().y));
	enemy.SetData(&textures.get(Textures::enemyTexture), sf::Vector2u(3, 9), 0.3f, 150.0f,sf::Vector2f(1000.f, baseHeight));

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

	ground.SetData(&textures.get(Textures::groundTexture), sf::Vector2f(4000, 100), sf::Vector2f(0, baseHeight - ground.GetSize().y));

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
    player.Update( &textures.get(Textures::bulletTexture), elapsedTime, gameView, baseHeight, window);
    enemy.Update( &textures.get(Textures::bulletTexture), elapsedTime, gameView, baseHeight, window);
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
	window.draw(grass);
	window.draw(rock);
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
