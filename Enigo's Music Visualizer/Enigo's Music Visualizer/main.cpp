/**
    @author Juan Carlos Ramirez
    
    Music Visualizer, it utilizes SFML and SFGUI to play music with a visualization.
*/
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>

#include <vector>

int main() {
    
    sf::RenderWindow window;
    window.create(sf::VideoMode(1600, 900), "Enigo's Music Visualizer");

    sf::InputSoundFile mySound;
    mySound.openFromFile("puzzle_loop.wav");
    std::vector<sf::Int16> sampleStorage;

    //Loading the by seconds sound information
    for (float i = 0; i < mySound.getDuration().asSeconds(); i++) {
        mySound.seek(sf::Time(sf::seconds(1+i)));
        sf::Int16 sample;
        mySound.read(&sample, 1);
        sampleStorage.push_back(sample);
    }

    //Playing music information
    sf::Music sound;
    sound.openFromFile("puzzle_loop.wav");
    sound.play();
    sound.setLoop(false);

    //Render loop
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

        //Line information to draw from audio
         for(int i = 0; i < sampleStorage.size(); i++){

            sf::RectangleShape myLine;
            myLine.setSize(sf::Vector2f(window.getSize().x / sampleStorage.size(),sampleStorage.at(i)));
            myLine.setFillColor(sf::Color::Red);
            myLine.setPosition(i + (window.getSize().x / sampleStorage.size()), (window.getSize().y / 2));
            window.draw(myLine);
        }
        window.display();

    }
    return 0;
}