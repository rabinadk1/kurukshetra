//
// Created by safal on 25/2/19.
//

#include <Camera.h>

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
    view.setCenter(view.getCenter().x + (view.getCenter().x - playerPosition.x), view.getCenter().y);
}

sf::IntRect Camera::GetViewport() {
    return static_cast<sf::IntRect>(view.getViewport());
}
