/**
@author Juan Carlos Ramirez

Basic Snake Clone
*/
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>

static sf::Clock worldClock;
static sf::RectangleShape snakePiece;

#include "snake.hpp"

int main() {

    sf::RenderWindow window;
    window.create(sf::VideoMode(300, 300), "Enigo's Sierpinski Triangle");

    snake mySnake(window,sf::Vector2f(0,0),sf::Vector2f(25,25));

    snakePiece.setFillColor(sf::Color::White);
    snakePiece.setPosition(sf::Vector2f(100,100));
    snakePiece.setSize(sf::Vector2f(25,25));

    //Render loop
    while (window.isOpen()) {
        sf::Event e;

		srand(time(NULL));
		sf::Color newColor = sf::Color(rand() % 255, rand() % 255, rand() % 255);
        while (window.pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::EventType::KeyPressed:
				switch (e.key.code) {
				case sf::Keyboard::Escape:
					window.close();
					break;
				case sf::Keyboard::Up:
					if (!mySnake.moveSnake(up)) {
						return 0;
					}
					break;
				case sf::Keyboard::Down:
					if (!mySnake.moveSnake(down)) {
						return 0;
					}
					break;
				case sf::Keyboard::Left:
					if (!mySnake.moveSnake(left)) {
						return 0;
					}
					break;
				case sf::Keyboard::Right:
					if (!mySnake.moveSnake(right)) {
						return 0;
					}
					break;
				case sf::Keyboard::R:
					//Random Colors
					snakePiece.setFillColor(newColor);
					mySnake.setSnakeColor(newColor);
					break;
				case sf::Keyboard::Space:
					//Super Speed
					mySnake.setSnakeSpeed(.08);
					break;
				}
			}
        }

        window.clear();
        mySnake.update();
        window.draw(snakePiece);
        window.display();

    }
    return 0;
}