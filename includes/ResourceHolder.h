//
// Created by maverick on 16/2/19.
//

#pragma once

#include <SFML/Graphics.hpp>

template <typename Resource, typename Identifier>
class ResourceHolder
{
private:
    Resource* resources;
public:
    ResourceHolder(unsigned count);
    void loadTexture(Identifier id, const char* filename, sf::IntRect area = sf::IntRect());
    void load(Identifier id, const char* filename);
    Resource& get(Identifier id);
    ~ResourceHolder();
};




