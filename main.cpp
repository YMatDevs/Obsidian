#include <SFML/Window.hpp>


#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "CoreFunctions/CoreFunctions.h"
#include "Screens/Screen.h"


int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Creating Window
    sf::RenderWindow window;
    initWindow(window);

    // Creating a Screen Pointer
    Screen* screen = new MainMenuScreen(windowSize);

    // Creating a Clock
    sf::Clock clock;
    clock.restart();

    // Main Application Loop
    while (window.isOpen()) {

        // Handle Events
        sf::Event event{};
        while (window.pollEvent(event)) { if (event.type == sf::Event::Closed) { window.close(); } }

        float dt = clock.restart().asSeconds();
        screen->update(dt, windowSize, screen);  // <-- New version
        screen->render(window, screen);

        window.display();
    }

    delete screen; // Don't forget to free memory allocated with new
    return 0;
}
