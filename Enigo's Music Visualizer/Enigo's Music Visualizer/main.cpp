/**
    @author Juan Carlos Ramirez
    
    Music Visualizer, it utilizes SFML and SFGUI to play music with a visualization.
*/
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>


int main() {
    
    sf::RenderWindow window;
    window.create(sf::VideoMode(300, 300), "Enigo's Music Visualizer");

    sf::InputSoundFile mySound;
    mySound.openFromFile("test.mp3");
    std::cout << mySound.getSampleCount() << std::endl;

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            switch (e.type) {
                case sf::Event::Closed:
                window.close();
                break;

                case sf::Event::EventType::KeyPressed:
                switch(e.key.code){
                    case sf::Keyboard::Escape:
                    window.close();
                    break;
                }
            }
        }

        window.clear();
        window.display();

    }
    return 0;
}