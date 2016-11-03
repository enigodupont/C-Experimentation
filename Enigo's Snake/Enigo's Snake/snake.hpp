#ifndef SNAKE_H 
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>

extern sf::Clock worldClock;
extern sf::RectangleShape snakePiece;

enum snakeMoveTypes {
    up, down, left, right
};

class snake {
public:
    snake(sf::RenderWindow &w, sf::Vector2f startPosition, sf::Vector2f snakeSize = sf::Vector2f(10, 10), sf::Color snakeColor = sf::Color::White) {

        this->renderTo = &w;
        this->snakeBlockSize = snakeSize;
        this->snakeColor = snakeColor;
        this->lastMoveTime = worldClock.getElapsedTime();

        sf::RectangleShape snakeHead;
        snakeHead.setFillColor(this->snakeColor);
        snakeHead.setSize(this->snakeBlockSize);
        snakeHead.setPosition(startPosition);

        snakeBody.push_back(snakeHead);

    }

    void update() {

        if (worldClock.getElapsedTime().asSeconds() - this->lastMoveTime.asSeconds() > sf::seconds(1).asSeconds()) {

            if (!this->moveSnake(lastMove)) {
                std::exit(0);
            }
            this->lastMoveTime = worldClock.getElapsedTime();
        }

        for (sf::RectangleShape rs : snakeBody) {
            renderTo->draw(rs);
        }
    }

    bool moveSnake(snakeMoveTypes dir) {

        //Check to make sure next move is not in the opposite direction of head
        //If it is, return true to nullify the move
        switch (dir) {
        case up:
            if (dir == down) {
                return true;
            }
            break;
        case down:
            if (dir == up) {
                return true;
            }
            break;
        case left:
            if (dir == right) {
                return true;
            }
            break;
        case right:
            if (dir == left) {
                return true;
            }
            break;
        }

        sf::Vector2f newPosition = snakeBody.at(0).getPosition();
        switch (dir) {
        case up:
            newPosition.y -= snakeBlockSize.y;
            break;
        case down:
            newPosition.y += snakeBlockSize.y;
            break;
        case left:
            newPosition.x -= snakeBlockSize.x;
            break;
        case right:
            newPosition.x += snakeBlockSize.x;
            break;

        }


        //If we pass the snake piece, append it to the top as the new head
        if (newPosition == snakePiece.getPosition()) {
            sf::RectangleShape newPiece = snakePiece;
            snakeBody.insert(snakeBody.begin(), newPiece);

            /*
            snakeBody.push_back(snakePiece);

            for (std::vector<sf::RectangleShape>::iterator it = snakeBody.begin(); it != snakeBody.end(); it++) {
                if (it + 1 == snakeBody.end()) {
                    break;
                }
                std::iter_swap(it, it + 1);
            }
            */
            bool setNewPiece = false;
            sf::Vector2f newPiecePosition;
            while (!setNewPiece) {
                std::srand(std::time(nullptr));
                newPiecePosition = sf::Vector2f((std::rand() * 25) % this->renderTo->getSize().x, (std::rand() * 25) % this->renderTo->getSize().x);

                setNewPiece = true;

                for (int i = 0; i < this->snakeBody.size(); i++) {
                    if (snakeBody.at(i).getPosition() == newPiecePosition) {
                        setNewPiece = false;
                        break;
                    }
                }

            }

            snakePiece.setPosition(newPiecePosition);
            return true;
        }

        //MOVE the entire body
        for (int i = 1; i < snakeBody.size(); i++) {

            snakeBody.at(i).setPosition(snakeBody.at(i - 1).getPosition());
        }

        snakeBody.at(0).setPosition(newPosition);

        //Check if head intersects with the body
        for (int i = 1; i < snakeBody.size(); i++) {
            if (snakeBody.at(i).getPosition() == snakeBody.at(0).getPosition()) {
                //Intersected return false move
                return false;
            }
        }

        //Check to see if the head is beyond window boundaries
        if (snakeBody.at(0).getPosition().x < 0 | snakeBody.at(0).getPosition().y < 0 | snakeBody.at(0).getPosition().x >= renderTo->getPosition().x | snakeBody.at(0).getPosition().y >= renderTo->getPosition().y) {
            return false;
        }

        //No intersection return true
        this->lastMove = dir;
        this->lastMoveTime = worldClock.getElapsedTime();
        return true;
    }
private:
    std::vector<sf::RectangleShape> snakeBody;
    sf::Vector2f snakeBlockSize;
    sf::Color snakeColor;
    snakeMoveTypes lastMove = right;
    sf::RenderWindow* renderTo;
    sf::Time lastMoveTime;
};

#endif
