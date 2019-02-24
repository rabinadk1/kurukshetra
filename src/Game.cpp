//
// Created by maverick on 12/2/19.
//

#include "Game.h"
Game::Game(unsigned viewWidth, unsigned viewHeight)
    :window(sf::VideoMode(viewHeight, viewHeight), "Kurukshetra"),
    textures(Textures::textureNumber),
    viewWidth(viewWidth),
    viewHeight(viewHeight),
    baseHeight(1900.f)
    {
        window.setVerticalSyncEnabled(true);

        gameView.setCenter(sf::Vector2f(viewWidth, 1600.f));
        gameView.setSize(sf::Vector2f(viewWidth, viewHeight));
        minimapView.setSize(sf::Vector2f(200.f, 200.f));
        gameView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
        minimapView.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));


        textures.load(Textures::skyTexture, "../Media/Textures/kurukshetra.png");
//        textures.load(Textures::groundTexture, "../Media/Textures/ground.jpg");
        textures.load(Textures::rockTexture, "../Media/Textures/rockPlatform.png");
//        textures.load(Textures::grassTexture, "../Media/Textures/grass.png");
        textures.load(Textures::playerTexture, "../Media/Textures/fox.png");
        textures.load(Textures::bulletTexture, "../Media/Textures/bullet.png");

        textures.get(Textures::skyTexture).setRepeated(true);
//        textures.get(Textures::groundTexture).setRepeated(true);
        textures.get(Textures::playerTexture).setSmooth(true);
        textures.get(Textures::bulletTexture).setSmooth(true);
        textures.get(Textures::grassTexture).setSmooth(true);
        sky.setPosition(sf::Vector2f(0, 0));
        sky.setSize(sf::Vector2f(4000, 2500));
        sky.setTexture(&textures.get(Textures::skyTexture));

        player.SetData(&textures.get(Textures::playerTexture), &textures.get(Textures::bulletTexture), sf::Vector2u(3, 9), 0.3f, 150.0f, sf::Vector2f(1000.f, baseHeight));


//        ground.SetData(&textures.get(Textures::groundTexture), sf::Vector2f(1920, 80), sf::Vector2f(0, 520));


//        const sf::Vector2f grassSize = sf::Vector2f(100, 100);
//        grass.setPosition(sf::Vector2f(1200, baseHeight));
//        grass.setSize(grassSize);
//        grass.setTexture(&textures.get(Textures::grassTexture));
//        grass.setOrigin(grassSize);


        rock.setPosition(sf::Vector2f(300, baseHeight));
        rock.setSize(sf::Vector2f(300, 50));
        rock.setTexture(&textures.get(Textures::rockTexture));

        animation.SetData(&textures.get(Textures::playerTexture), sf::Vector2u(3,9), 0.3f);
    }

void Game::run() {
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event = {};
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
            break;
        }
        if (event.type == sf::Event::Resized)
        {
            // update the view to the new size of the window
//            sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
//            mWindow.setView(sf::View(visibleArea));
            ResizedWindow(window, gameView);
        }
    }
}

void Game::update() {
    window.setView(gameView);
    player.Update(clock.restart().asSeconds(), gameView, baseHeight);
}

void Game::render() {
    window.clear();
    window.draw(sky);
//    window.draw(grass);
    window.draw(rock);
    player.Draw(window);
    window.display();

}

void Game::ResizedWindow(sf::RenderWindow &window, sf::View &view) {
    float aspectratio = window.getSize().x / float(window.getSize().y);

    view.setSize(viewWidth * aspectratio, viewHeight);
}
