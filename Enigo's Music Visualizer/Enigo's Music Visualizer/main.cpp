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
    
    sfg::SFGUI GUI;
    sfg::Desktop desktop;

    sf::RenderWindow window;
    window.create(sf::VideoMode(1600, 900), "Enigo's Music Visualizer");

    sf::InputSoundFile mySound;
    mySound.openFromFile("puzzle_loop.wav");
    std::vector<sf::Int16> sampleStorage;
    
    //Loading the by seconds sound information
    for (float i = 0; i < mySound.getDuration().asSeconds(); i++) {
        mySound.seek(sf::Time(sf::seconds(1+i)));
        sf::Int16 sample;
        if (mySound.read(&sample, 1) < 1) {
            std::fprintf(stderr,"Did not read the correct sample size\n");
            
            //return -1;
        }
        sampleStorage.push_back(sample);
    }

    //Playing music information
    sf::Music sound;
    sound.openFromFile("puzzle_loop.wav");
    sound.play();
    sound.setLoop(true);

    //Line information to draw from audio
    sf::VertexArray mySeconds(sf::LineStrip);
    for (int i = 0; i < sampleStorage.size(); i++) {

        sf::Vertex mySecond;
        mySecond.position = sf::Vector2f(i * (window.getSize().x / sampleStorage.size()), (window.getSize().y / 2.0) + ((sampleStorage.at(i) - -(window.getSize().y / 2.0)) / window.getSize().y));
        if (std::floor(sound.getPlayingOffset().asSeconds()) == i) {
            mySecond.color = (sf::Color::Red);
        }
        else {
            mySecond.color = (sf::Color::White);
        }

        mySeconds.append(mySecond);
    }

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
        
        int currentVerxtex = std::floor(sound.getPlayingOffset().asSeconds());
        mySeconds[currentVerxtex].color = sf::Color::Red;
       
        window.draw(mySeconds);

        mySeconds[currentVerxtex].color = sf::Color::White;
        window.display();

    }
    return 0;
}