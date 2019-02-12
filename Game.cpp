//
// Created by maverick on 12/2/19.
//

#include "Game.h"
#include "Controller/remainTime.h"
#include <iostream>
Game::Game()
    : mWindow(sf::VideoMode(640, 480), "SFML Application"),
    mIsMovingUp(false),
    mIsMovingDown(false),
    mIsMovingLeft(false),
    mIsMovingRight(false)
    {
        mWindow.setVerticalSyncEnabled(true);
        if (not mTexture.loadFromFile("../Eagle.gif")) {
            std::cerr<<"Couldn't load texture from the file";
            exit(1);
        }
        if(!font.loadFromFile("../DejaVuSans.ttf"))
        {
            std::cerr<<"Couldn't load fonts from the file";
            exit(1);
        }
        mTexture.setSmooth(true);
        mSprite.setTexture(mTexture);
        mSprite.setPosition(100.f, 100.f);
        time.setFont(font);
        time.setPosition(100.f,100.f);
        time.setCharacterSize(24);
    time.setFillColor(sf::Color::Red);
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
        switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                mWindow.close();
                break;
        }
    }
}

void Game::update() {
    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingUp)
        movement.y -= 1.f;
    if (mIsMovingDown)
        movement.y += 1.f;
    if (mIsMovingLeft)
        movement.x -= 1.f;
    if (mIsMovingRight)
        movement.x += 1.f;
    mSprite.move(movement);
}

void Game::render() {
    mWindow.clear();
    mWindow.draw(mSprite);
    mWindow.draw(time);
    mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    switch (key)
    {
        case sf::Keyboard::W:
            mIsMovingUp = isPressed;
            break;
        case sf::Keyboard::A:
            mIsMovingLeft = isPressed;
            break;
        case sf::Keyboard::S:
            mIsMovingDown = isPressed;
            break;
        case sf::Keyboard::D:
            mIsMovingRight = isPressed;
            break;
    }
}
