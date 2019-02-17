//
// Created by maverick on 12/2/19.
//

#include "Game.h"
Game::Game()
    :mWindow(sf::VideoMode(800, 600), "Kurukshetra")
//    mIsMovingUp(false),
//    mIsMovingDown(false),
//    mIsMovingLeft(false),
//    mIsMovingRight(false),
//    mIsParabolic(false),
//    clear(false)
    {
        mWindow.setVerticalSyncEnabled(true);
        textures.load(Textures::skyTexture, "../Media/Textures/redSky.jpg", sf::IntRect(100, 100, 300, 300));
        textures.load(Textures::groundTexture, "../Media/Textures/ground.jpg");
        textures.load(Textures::grassTexture, "../Media/Textures/grass.png");
        textures.load(Textures::playerTexture, "../Media/Textures/fox.png");
        textures.get(Textures::skyTexture).setRepeated(true);
        textures.get(Textures::groundTexture).setRepeated(true);


        sky.setPosition(sf::Vector2f(0, 0));
        sky.setSize(sf::Vector2f(1920, 600));
        sky.setTexture(&textures.get(Textures::skyTexture));
        sky.setFillColor(sf::Color(102, 0, 0));

        ground.setPosition(sf::Vector2f(0, 520));
        ground.setSize(sf::Vector2f(1920, 80));
        ground.setFillColor(sf::Color(255, 255, 255, 255)); //128 is half transparency
        ground.setTexture(&textures.get(Textures::groundTexture));
        ground.setFillColor(sf::Color(255, 174, 0, 128));

        grass.setPosition(sf::Vector2f(1200, 420));
        grass.setSize(sf::Vector2f(100, 100));
        grass.setTexture(&textures.get(Textures::grassTexture));

        player.SetData(&textures.get(Textures::playerTexture), sf::Vector2u(3, 9), 0.3f, 150.0f);
        animation.SetData(&textures.get(Textures::playerTexture), sf::Vector2u(3,9), 0.3f);
//        speed.x = 1.f;
//        speed.y = 0.f;
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
//        switch (event.type) {
//            case sf::Event::KeyPressed:
//                handlePlayerInput(event.key.code, true);
//                break;
//            case sf::Event::KeyReleased:
//                handlePlayerInput(event.key.code, false);
//                break;
//            case sf::Event::Closed:
//                mWindow.close();
//                break;
//        }
        if (event.type == sf::Event::Closed)
        {
            mWindow.close();
            break;
        }
    }
}

void Game::update() {
    player.Update(clock.restart().asSeconds());

}

void Game::render() {
    mWindow.clear();
    mWindow.draw(sky);
    mWindow.draw(grass);
    mWindow.draw(ground);
    player.Draw(mWindow);
    mWindow.display();

}

//void Game::handlePlayerInput(sf::Keyboard::Key& key, bool isPressed) {
//    switch (key)
//    {
//        case sf::Keyboard::W:
//            mIsMovingUp = isPressed;
//            break;
//        case sf::Keyboard::A:
//            mIsMovingLeft = isPressed;
//            break;
//        case sf::Keyboard::S:
//            mIsMovingDown = isPressed;
//            break;
//        case sf::Keyboard::D:
//            mIsMovingRight = isPressed;
//            break;
//        case sf::Keyboard::F:
//            mIsParabolic = isPressed;
//            break;
//        case sf::Keyboard::LShift:
//            clear = isPressed;
//            break;
//    }
//}
