//
// Created by maverick on 16/2/19.
//

#pragma once

#include <SFML/Graphics/Texture.hpp>

namespace Textures
{
    enum ID {skyTexture, groundTexture, rockTexture, playerTexture, grassTexture};
}


class TextureHolder {
private:
    sf::Texture textures[5];
public:
//    void load(Textures::ID id, const char* filename);
    void load(Textures::ID id, const char* filename, sf::IntRect area = sf::IntRect());
    sf::Texture& get(Textures::ID id);
};



