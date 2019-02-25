//
// Created by safal on 25/2/19.
//

#ifndef KURUKSHETRA_CAMERA_H
#define KURUKSHETRA_CAMERA_H


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
    void Zoom(float factor);
    void Update(sf::Vector2f playerPosition, sf::RenderWindow& window);
    sf::IntRect GetViewport();
    void SetCenter(sf::Vector2f center);
    void SetViewPort(sf::FloatRect rect);

    sf::FloatRect getViewBounds(const sf::View &view);
};


#endif //KURUKSHETRA_CAMERA_H
