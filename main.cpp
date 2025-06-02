#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

// Custom-size text button
bool displayButton(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text, sf::Font& font) {
    static std::map<std::string, bool> holdMap;
    std::string key = std::to_string((int)position.x) + "_" + std::to_string((int)position.y);
    bool& isHeld = holdMap[key];

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool isHovered = false, isClicked = false;

    sf::RectangleShape button(size);
    button.setPosition(position);

    if (button.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y)) {
        isHovered = true;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (!isHeld) {
                isClicked = true;
                isHeld = true;
            }
        } else {
            isHeld = false;
        }
    } else {
        isHeld = false;
    }

    button.setFillColor(isClicked ? sf::Color::Green : (isHovered ? sf::Color::Red : sf::Color::Blue));

    sf::Text buttonText(text, font, 16);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(position.x + 5, position.y + 5);

    window.draw(button);
    window.draw(buttonText);

    return isClicked;
}

// Custom-size image button
bool displayImageButton(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size, sf::Sprite& sprite) {
    static std::map<std::string, bool> holdMap;
    std::string key = std::to_string((int)position.x) + "_" + std::to_string((int)position.y);
    bool& isHeld = holdMap[key];

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool isHovered = false, isClicked = false;

    sf::RectangleShape button(size);
    button.setPosition(position);

    if (button.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y)) {
        isHovered = true;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (!isHeld) {
                isClicked = true;
                isHeld = true;
            }
        } else {
            isHeld = false;
        }
    } else {
        isHeld = false;
    }

    button.setFillColor(isClicked ? sf::Color::Green : (isHovered ? sf::Color::Red : sf::Color::Blue));
    window.draw(button);

    sprite.setPosition(position);
    sprite.setScale(
        size.x / sprite.getTexture()->getSize().x,
        size.y / sprite.getTexture()->getSize().y
    );
    window.draw(sprite);

    return isClicked;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 900), "THE GAMMME");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font\n";
        return -1;
    }

    sf::Texture texture;
    if (!texture.loadFromFile("button_icon.png")) {
        std::cerr << "Failed to load button_icon.png\n";
        return -1;
    }

    sf::Sprite sprite(texture);
    sf::Sprite sprite2(texture);

    bool menuVisible = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(30, 30, 30));

        // Sizable text buttons
        if (displayButton(window, sf::Vector2f(325.f, 150.f), sf::Vector2f(200.f, 60.f), "Button 1", font))
            std::cout << "Button 1 clicked!\n";

        if (displayButton(window, sf::Vector2f(600.f, 250.f), sf::Vector2f(180.f, 50.f), "Button 2", font))
            std::cout << "Button 2 clicked!\n";

        if (displayButton(window, sf::Vector2f(400.f, 350.f), sf::Vector2f(220.f, 70.f), "Button 3", font))
            std::cout << "Button 3 clicked!\n";

        // Sizable image buttons
        if (displayImageButton(window, sf::Vector2f(325.f, 250.f), sf::Vector2f(150.f, 50.f), sprite))
            std::cout << "Image button 1 clicked!\n";

        if (displayImageButton(window, sf::Vector2f(505.f, 250.f), sf::Vector2f(120.f, 40.f), sprite2))
            std::cout << "Image button 2 clicked!\n";

        // Menu toggle button
        if (displayButton(window, sf::Vector2f(20.f, 20.f), sf::Vector2f(80.f, 30.f), "Menu", font))
            menuVisible = !menuVisible;

        // Menu options
        if (menuVisible) {
            if (displayButton(window, sf::Vector2f(20.f, 60.f), sf::Vector2f(120.f, 30.f), "Option 1", font)) {
                std::cout << "Option 1 selected\n";
                menuVisible = false;
            }

            if (displayButton(window, sf::Vector2f(20.f, 100.f), sf::Vector2f(120.f, 30.f), "Option 2", font)) {
                std::cout << "Option 2 selected\n";
                menuVisible = false;
            }
        }

        window.display();
    }

    return 0;
}
