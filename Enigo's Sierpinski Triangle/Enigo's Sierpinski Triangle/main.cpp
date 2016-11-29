/**
@author Juan Carlos Ramirez

Sierpinski Triangle, utilizes chaotic number generation to create the triangle.
*/
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>

sf::Vector2f recursiveSTriangle(sf::Vector2f startPoint, sf::VertexArray &triStorage, sf::Vector2u max, float triangleSize = 10, bool drawLeft = true, bool drawRight = true);
void chaosGame(sf::VertexArray startTriangle, sf::VertexArray &toDraw);
int main() {

    sf::RenderWindow window;
    window.create(sf::VideoMode(300, 300), "Enigo's Sierpinski Triangle");



    sf::VertexArray myTriangles(sf::Lines);
    sf::Vector2f start(window.getSize().x / 2, 0);

    //recursiveSTriangle(start,myTriangles,window.getSize(),100);

    sf::VertexArray startTriangle;

    startTriangle.append(sf::Vector2f(window.getSize().x / 2, 0));
    startTriangle.append(sf::Vector2f(0, window.getSize().y));
    startTriangle.append(sf::Vector2f(window.getSize().x, window.getSize().y));

    chaosGame(startTriangle, myTriangles);

    //Render loop
    while (window.isOpen()) {
        sf::Event e;
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
                }
            }
        }

        window.clear();

        for (int i = 0; i < myTriangles.getVertexCount(); i++) {
            sf::RectangleShape currentSquare;
            currentSquare.setPosition(myTriangles[i].position);
            currentSquare.setFillColor(myTriangles[i].color);
            currentSquare.setSize(sf::Vector2f(10, 10));
            window.draw(currentSquare);
        }
        //window.draw(myTriangles);
        window.display();

    }
    return 0;
}

void chaosGame(sf::VertexArray startTriangle, sf::VertexArray &toDraw) {

    sf::Vector2f currentPoint(startTriangle[0].position.x, startTriangle[0].position.y + 50);

    for (int i = 0; i < 10000; i++) {
        std::srand(std::time(nullptr) + i + currentPoint.x * currentPoint.y);
        sf::Vertex endPoint = startTriangle[(std::rand() + i) % 3];


        //Update currentPosition with midpoint
        currentPoint = sf::Vector2f((currentPoint.x + endPoint.position.x) / 2, (currentPoint.y + endPoint.position.y) / 2);

        sf::Vertex toAdd(currentPoint);
        toAdd.color = sf::Color::Red;
        //Add to draw array
        toDraw.append(toAdd);
    }


}

sf::Vector2f recursiveSTriangle(sf::Vector2f startPoint, sf::VertexArray &triStorage, sf::Vector2u max, float triangleSize, bool drawLeft, bool drawRight) {

    if (std::ceil(startPoint.y) > max.y | std::ceil(startPoint.x) < 0 | std::ceil(startPoint.x) > max.x) {
        return startPoint;
    }
    sf::Vector2f leftPoint;
    if (drawLeft) {
        leftPoint = recursiveSTriangle(sf::Vector2f(startPoint.x - (triangleSize / 2), startPoint.y + triangleSize), triStorage, max, triangleSize, drawLeft, !drawRight);

    }
    else {
        leftPoint = sf::Vector2f(startPoint.x - (triangleSize / 2), startPoint.y + triangleSize);
    }
    sf::Vector2f rightPoint;
    if (drawRight) {
        rightPoint = recursiveSTriangle(sf::Vector2f(startPoint.x + (triangleSize / 2), startPoint.y + triangleSize), triStorage, max, triangleSize, !drawLeft, drawRight);
    }
    else {
        rightPoint = sf::Vector2f(startPoint.x + (triangleSize / 2), startPoint.y + triangleSize);
    }


    triStorage.append(startPoint);
    triStorage.append(leftPoint);
    triStorage.append(rightPoint);

    return startPoint;

}