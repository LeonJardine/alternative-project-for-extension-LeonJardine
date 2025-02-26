#include "TextureManager.h"
#include <filesystem>
namespace fs = std::filesystem;

TextureManager::TextureManager()
{
    // Loads all files in gfx/ and adds to textures map.
    const std::string gfxPath = "gfx";

    for (const auto& entry : fs::directory_iterator(gfxPath))
    {
        if (entry.is_regular_file())
        {
            std::string filename = entry.path().filename().string();

            // Remove the file extension (.png)
            std::string textureName = filename.substr(0, filename.find_last_of('.'));

            // Load the texture and store it in the map
            loadTexture(textureName, gfxPath + "/" + filename);

        }
    }

    // Add individual icon textures to the manager
    addTexture("flatLight00.png", 160, 305, 96, 96);
    addTexture("flatLight01.png", 473, 461, 61, 76);
    addTexture("flatLight02.png", 0, 480, 125, 125);
    addTexture("flatLight03.png", 313, 528, 76, 61);
    addTexture("flatLight04.png", 473, 400, 75, 61);
    addTexture("flatLight05.png", 0, 160, 160, 160);
    addTexture("flatLight06.png", 0, 320, 160, 160);
    addTexture("flatLight07.png", 160, 0, 160, 160);
    addTexture("flatLight08.png", 160, 401, 61, 75);
    addTexture("flatLight09.png", 0, 0, 160, 160);
    addTexture("flatLight10.png", 496, 192, 48, 48);
    addTexture("flatLight11.png", 496, 144, 48, 48);
    addTexture("flatLight12.png", 548, 400, 48, 48);
    addTexture("flatLight13.png", 544, 240, 48, 48);
    addTexture("flatLight14.png", 544, 144, 48, 48);
    addTexture("flatLight15.png", 473, 537, 48, 48);
    addTexture("flatLight16.png", 268, 160, 48, 48);
    addTexture("flatLight17.png", 336, 320, 48, 48);
    addTexture("flatLight18.png", 480, 48, 48, 48);
    addTexture("flatLight19.png", 521, 537, 48, 48);
    addTexture("flatLight20.png", 480, 0, 48, 48);
    addTexture("flatLight21.png", 480, 96, 48, 48);
    addTexture("leftIcon", 473, 320, 80, 80);
    addTexture("rightIcon", 416, 240, 80, 80);
    addTexture("upIcon", 416, 160, 80, 80);
    addTexture("downIcon", 400, 80, 80, 80);
    addTexture("starIcon", 400, 0, 80, 80);
    addTexture("flatLight27.png", 393, 480, 80, 80);
    addTexture("flatLight28.png", 534, 461, 48, 48);
    addTexture("flatLight29.png", 496, 240, 48, 48);
    addTexture("flatLight30.png", 528, 0, 48, 48);
    addTexture("flatLight31.png", 528, 48, 48, 48);
    addTexture("flatLight32.png", 528, 96, 48, 48);
    addTexture("flatLight33.png", 544, 192, 48, 48);
    addTexture("flatLight34.png", 393, 320, 80, 80);
    addTexture("flatLight35.png", 313, 368, 80, 80);
    addTexture("flatLight36.png", 256, 288, 80, 80);
    addTexture("flatLight37.png", 256, 208, 80, 80);
    addTexture("flatLight38.png", 233, 481, 80, 80);
    addTexture("flatLight39.png", 393, 400, 80, 80);
    addTexture("flatLight40.png", 125, 480, 108, 48);
    addTexture("flatLight41.png", 125, 528, 108, 48);
    addTexture("flatLight42.png", 160, 160, 108, 48);
    addTexture("flatLight43.png", 313, 448, 80, 80);
    addTexture("flatLight44.png", 233, 401, 80, 80);
    addTexture("flatLight45.png", 320, 0, 80, 80);
    addTexture("flatLight46.png", 320, 80, 80, 80);
    addTexture("flatLight47.png", 336, 160, 80, 80);
    addTexture("flatLight48.png", 336, 240, 80, 80);
    addTexture("flatLight49.png", 160, 208, 96, 97);
}

sf::Vector2u TextureManager::getDimensions(std::string filePath)
{
    if(textures.find(filePath) != textures.end())
        return textures.at(filePath).getSize();
    return { 0, 0 };
}

void TextureManager::addTexture(const std::string & name, int x, int y, int width, int height) {
    // Check if the texture already exists in the manager
    if (textures.find(name) != textures.end()) {
        std::cout << "Texture with name " << name << " already exists." << std::endl;
        return;
    }

    // Assuming "icons.png" is the key for the combined image
    sf::Texture& combinedTexture = TextureManager::getTexture("icons");

    // Calculate the proportions of the combined texture
    float combinedProportions = TextureManager::getProportions("icons.png");

    // Calculate the source rectangle for the specified region in the combined texture
    sf::IntRect sourceRect(x, y, width, height);

    // Create a new texture for the individual image
    sf::Texture individualTexture;
    individualTexture.loadFromImage(combinedTexture.copyToImage(), sourceRect);

    // Store the individual texture in the manager
    textures[name] = individualTexture;
}

// Returns float of texture width divided by texture height.
float TextureManager::getProportions(std::string filePath)
{
    sf::Vector2u size = getDimensions(filePath);
    if (size.y == 0) return 0.f;
    return static_cast<float>(size.x) / static_cast<float>(size.y);
}

// Load texture from file and store it in the manager
bool TextureManager::loadTexture(const std::string& name, const std::string& filename)
{

    sf::Texture texture;
    if (texture.loadFromFile(filename))
    {
        textures[name] = texture;
        return true;
    }
    else
    {
        std::cout << "Failed to load texture: " << filename << std::endl;
        return false;
    }
}

// Get a reference to a texture by name
sf::Texture& TextureManager::getTexture(const std::string& name)
{
    return textures.at(name);
}

// Check if a texture with a given name exists
bool TextureManager::textureExists(const std::string& name)
{
    return textures.find(name) != textures.end();
}

void TextureManager::allTextures()
{
    for (std::pair<std::string,sf::Texture> p : textures)
    {
        std::cout << p.first << "\n";
    }
}

void TextureManager::animate(GameObject* gameObject, const std::string& texture, float time) {
   
   

    // Set which frame to show.
    int frame = 1;  // show this one.
    if (time - 0.5f < static_cast<int>(time))
    {
        // unless you don't wanna.
        frame = 0;
    }

    // Assuming "sadBearAnim" is the key for the combined image
    sf::Texture& combinedTexture = getTexture(texture + "Anim");
    // Calculate the width of each frame (assuming the frames are side by side)
    float frameWidth = combinedTexture.getSize().x / 2.0f;

    // Calculate the source rectangle for the current frame
    sf::IntRect sourceRect(frame * frameWidth, 0, static_cast<int>(frameWidth), combinedTexture.getSize().y);

    // Set the texture and source rectangle for the current frame
    gameObject->setTextureRect(sourceRect);
    gameObject->setTexture(&combinedTexture);
}