#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "Framework/GameObject.h"

#include <iostream>

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

class TextureManager
{

private:
    std::unordered_map<std::string, sf::Texture> textures;

public:
    TextureManager();

    sf::Vector2u getDimensions(std::string filePath);

    float getProportions(std::string filePath);

    // Load texture from file and store it in the manager
    bool loadTexture(const std::string& name, const std::string& filename);

    sf::Texture& getTexture(const std::string& name);

    bool textureExists(const std::string& name);

    void allTextures();

    void animate(GameObject* gameObject, const std::string& texture, float time);

    void addTexture(const std::string& name, int x, int y, int width, int height);


};

#endif // TEXTURE_MANAGER_H


