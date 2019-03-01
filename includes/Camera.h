//
// Created by safal on 25/2/19.
//

#pragma once
#include <SFML/Graphics.hpp>

class Camera {
private:
    sf::View view;

public:
    Camera();
    void SetData(sf::Vector2f center, sf::Vector2f size, sf::FloatRect rect);
    void SetView(sf::RenderWindow& window);
    void SetSize(sf::Vector2f size);
    void Move(sf::Vector2f newCameraPosition);
    void showInfo(sf::Text* info, sf::RectangleShape& player);
    void Zoom(float factor);
    void Update(sf::RectangleShape& player, sf::RenderWindow& window, sf::RectangleShape& sky);
    sf::IntRect GetViewport(sf::RenderWindow& window);
    void SetCenter(sf::Vector2f center);
    void SetViewPort(sf::FloatRect rect);
    sf::Vector2f GetCenter() { return view.getCenter(); }

    sf::FloatRect getViewBounds(const sf::View &view);
};

