//
// Created by maverick on 12/2/19.
//

#include "Game.h"
Game::Game()
    :mWindow(sf::VideoMode(800, 600), "Kurukshetra")
    {
        mWindow.setVerticalSyncEnabled(true);

        gameView.setCenter(sf::Vector2f(400.f, 300.f));
        gameView.setSize(sf::Vector2f(800.f, 600.f));
        minimapView.setSize(sf::Vector2f(200.f, 200.f));
        gameView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
        minimapView.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));


        textures.load(Textures::skyTexture, "../Media/Textures/sereneBackground.png");
        textures.load(Textures::groundTexture, "../Media/Textures/ground.jpg");
        textures.load(Textures::rockTexture, "../Media/Textures/rockPlatform.png");
        textures.load(Textures::grassTexture, "../Media/Textures/grass.png");
        textures.load(Textures::playerTexture, "../Media/Textures/fox.png");
        textures.get(Textures::skyTexture).setRepeated(true);
        textures.get(Textures::groundTexture).setRepeated(true);


        sky.setPosition(sf::Vector2f(0, 0));
        sky.setSize(sf::Vector2f(1920, 600));
        sky.setTexture(&textures.get(Textures::skyTexture));

        player.SetData(&textures.get(Textures::playerTexture), sf::Vector2u(3, 9), 0.3f, 150.0f);

        ground.SetData(&textures.get(Textures::groundTexture), sf::Vector2f(1920, 80), sf::Vector2f(0, 520));

        grass.setPosition(sf::Vector2f(1200, 420));
        grass.setSize(sf::Vector2f(100, 100));
        grass.setTexture(&textures.get(Textures::grassTexture));

        rock.setPosition(sf::Vector2f(300, 420));
        rock.setSize(sf::Vector2f(300, 50));
        rock.setTexture(&textures.get(Textures::rockTexture));

        animation.SetData(&textures.get(Textures::playerTexture), sf::Vector2u(3,9), 0.3f);
    }

void Game::run() {
    while (mWindow.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event = {};
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            mWindow.close();
            break;
        }
    }
}

void Game::update() {
    mWindow.setView(gameView);
    player.Update(clock.restart().asSeconds(), gameView);
}

void Game::render() {
    mWindow.clear();
    mWindow.draw(sky);
    mWindow.draw(grass);
    mWindow.draw(rock);
    player.Draw(mWindow);
    mWindow.display();

}