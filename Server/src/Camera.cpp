//
// Created by safal on 25/2/19.
//

#include <Camera.h>
#include <iostream>
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

void Camera::Update(sf::Vector2f playerPosition, sf::RenderWindow &window) {
    sf::FloatRect viewBound = getViewBounds(view);
    if(4000 - viewBound.left >= viewBound.width)
        view.setCenter(playerPosition.x, playerPosition.y - 300);
    else
        view.setCenter((4000 - viewBound.width)/2, playerPosition.y - 300);
    std::cout << viewBound.left << std::endl;
    std::cout <<"width: " <<  viewBound.width << std::endl;

}

sf::IntRect Camera::GetViewport() {
    return static_cast<sf::IntRect>(view.getViewport());
}

sf::FloatRect Camera::getViewBounds(const sf::View &view) {
    sf::FloatRect rt;
    rt.left = view.getCenter().x - view.getSize().x/2.f;
    rt.top  = view.getCenter().y - view.getSize().y/2.f;
    rt.width  = view.getSize().x;
    rt.height = view.getSize().y;
    return rt;
}
