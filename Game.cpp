//
// Created by maverick on 12/2/19.
//

#include "Game.h"
#include <iostream>

Game::Game()
    : mWindow(sf::VideoMode(640, 480), "SFML Application"),
    mIsMovingUp(false),
    mIsMovingDown(false),
    mIsMovingLeft(false),
    mIsMovingRight(false),
    mIsParabolic(false),
    clear(false),
    time(1.f)
    {
        mWindow.setVerticalSyncEnabled(true);
        if (not mTexture.loadFromFile("../Eagle.gif")) {
            std::cerr<<"Couldn't load texture from the file";
            exit(1);
        }
        mTexture.setSmooth(true);
        mSprite.setTexture(mTexture);
//        mSprite.setPosition(100.f, 100.f);
        speed.x = 1.f;
        speed.y = 0.f;
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
    if (clear) {
        mSprite.setPosition(0.f, 0.f);
        return;
    }
    if (mIsParabolic) {
        speed.y = speed.y*time +  0.5f * 0.01f * time * time;
        time *= 1.7;
        movement += speed;
        mSprite.move(movement);
        return;
    }
    time = 1;
    speed.y = 0;
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
    mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key& key, bool isPressed) {
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
        case sf::Keyboard::F:
            mIsParabolic = isPressed;
            break;
        case sf::Keyboard::LShift:
            clear = isPressed;
            break;
    }
}
