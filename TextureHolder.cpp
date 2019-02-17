//
// Created by maverick on 16/2/19.
//

#include <iostream>
#include "TextureHolder.h"
//void TextureHolder::load(Textures::ID id, const char *filename) {
//    if (!textures[id].loadFromFile(filename))
//}

void TextureHolder::load(Textures::ID id, const char *filename, const sf::IntRect area) {
    if (!textures[id].loadFromFile(filename, area)) {
        std::cerr << "TextureHolder::load - Failed to load " << filename << std::endl;
        exit(1);
    }
    textures[id].setSmooth(true);
}

sf::Texture &TextureHolder::get(Textures::ID id) {
    return textures[id];
//    return *found->second;
}
