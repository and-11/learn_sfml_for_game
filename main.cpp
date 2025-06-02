#include <SFML/Graphics.hpp>
#include <iostream>

// Function to display a button and return true if clicked
bool displayButton(sf::RenderWindow& window, const sf::Vector2f& position, const std::string& text, sf::Font& font) {
    static bool isHeld = false;

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool isHovered = false;
    bool isClicked = false;

    sf::RectangleShape button(sf::Vector2f(150.f, 50.f));
    button.setPosition(position);

    if (button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
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

    if (isClicked) button.setFillColor(sf::Color::Green);
    else if (isHovered) button.setFillColor(sf::Color::Red);
    else button.setFillColor(sf::Color::Blue);

    sf::Text buttonText(text, font, 20);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(
        position.x + 25,
        position.y + 10
    );

    window.draw(button);
    window.draw(buttonText);

    return isClicked;
}


bool displayImageButton(sf::RenderWindow& window, const sf::Vector2f& position, sf::Sprite& sprite) {
    static bool isHeld = false;

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool isHovered = false;
    bool isClicked = false;

    sf::RectangleShape button(sf::Vector2f(150.f, 50.f));
    button.setPosition(position);

    if (button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
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

    if (isClicked) button.setFillColor(sf::Color::Green);
    else if (isHovered) button.setFillColor(sf::Color::Red);
    else button.setFillColor(sf::Color::Blue);

    // Draw background
    window.draw(button);

    // Set sprite position and scale to fit the button
    sprite.setPosition(position);
    sprite.setScale(
        button.getSize().x / sprite.getTexture()->getSize().x,
        button.getSize().y / sprite.getTexture()->getSize().y
    );

    // Draw image on top
    window.draw(sprite);

    return isClicked;
}





int main() {
    std::cout <<" cacaca";
    sf::RenderWindow window(sf::VideoMode(1200, 900), "SFML Multiple Buttons");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        return -1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Draw 3 buttons
        if (displayButton(window, sf::Vector2f(325.f, 150.f), "Button 1", font))
            std::cout << "Button 1 clicked!\n";

        if (displayButton(window, sf::Vector2f(600.f, 250.f), "Button 2", font))
            std::cout << "Button 2 clicked!\n";

        if (displayButton(window, sf::Vector2f(400.f, 350.f), "Button 3", font))
            std::cout << "Button 3 clicked!\n";

        
        sf::Texture texture;
        if (!texture.loadFromFile("button_icon.png"))
            return -1;
        sf::Sprite sprite(texture);

        if (displayImageButton(window, sf::Vector2f(325.f, 250.f), sprite))
            std::cout << "Image button clicked!\n";

        window.display();
    }

    return 0;
}
