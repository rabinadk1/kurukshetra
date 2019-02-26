//
// Created by safal on 25/2/19.
//

#include <Camera.h>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Camera.h"

Camera::Camera() {
}



void Camera::SetCenter(sf::Vector2f center) {
    view.setCenter(center);
}

void Camera::SetSize(sf::Vector2f size) {
    view.setSize(size);
}

void Camera::SetViewPort(sf::FloatRect rect) {
    view.setViewport(rect);
}

void Camera::SetData(sf::Vector2f center, sf::Vector2f size, sf::FloatRect rect) {
    this -> SetCenter(center);
    this -> SetSize(size);
    this -> SetViewPort(rect);
}

void Camera::SetView(sf::RenderWindow &window) {
    window.setView(view);
}

void Camera::Move(sf::Vector2f newCameraPosition) {
    view.move(newCameraPosition);
}

void Camera::Zoom(float factor) {
    view.zoom(factor);
}

void Camera::Update(sf::RectangleShape &player, sf::RenderWindow &window, sf::RectangleShape &sky) {
    sf::FloatRect playerBounds = player.getGlobalBounds();
//    view.setCenter(player.getPosition().x, player.getPosition().y - 300);
    if(player.getPosition().x >= sky.getSize().x -player.getSize().x)
        player.setPosition(sky.getSize().x - player.getSize().x, player.getPosition().y);
    if(sky.getTexture()->getSize().x - player.getPosition().x >= 0)
        view.setCenter(player.getPosition().x, player.getPosition().y - 300);
    else
        view.setCenter(sky.getTexture()->getSize().x + (sky.getTexture()->getSize().x + player.getPosition().x)/1000, player.getPosition().y -300);

    std::cout << sky.getSize().x - player.getPosition().x << std::endl;

}

sf::IntRect Camera::GetViewport(sf::RenderWindow& window) {
    return static_cast<sf::IntRect>(window.getViewport(view));
}

sf::FloatRect Camera::getViewBounds(const sf::View &view) {
    sf::FloatRect rt;
    rt.left = view.getCenter().x - view.getSize().x/2.f;
    rt.top  = view.getCenter().y - view.getSize().y/2.f;
    rt.width  = view.getSize().x;
    rt.height = view.getSize().y;
    return rt;
}
