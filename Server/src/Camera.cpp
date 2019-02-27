//
// Created by safal on 25/2/19.
//

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
    view.move(newCameraPosition.x, 0);
}

void Camera::Zoom(float factor) {
    view.zoom(factor);
}

void Camera::Update(sf::RectangleShape &player, sf::RenderWindow &window, sf::RectangleShape &sky) {

    view.setCenter(player.getPosition().x, player.getPosition().y - 300);

    std::cout << player.getPosition().x << std::endl;

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

void Camera::showInfo(sf::Text info, sf::RectangleShape &player) {
    for (int i=0; i<1; i++)
    {
        info.setPosition(player.getPosition().x - player.getSize().x, player.getPosition().y - (3.f / 2.f) * player.getSize().y);
        info.setFillColor(sf::Color::Red);
    }
}
