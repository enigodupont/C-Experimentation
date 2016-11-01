/**
@author Juan Carlos Ramirez

Music Visualizer, it utilizes SFML and SFGUI to play music with a visualization.
*/
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>

sf::Vector2f recursiveSTriangle(sf::Vector2f startPoint, sf::VertexArray &triStorage, sf::Vector2u max, float triangleSize = 10, bool drawLeft = true,bool drawRight = true);

int main() {

    sf::RenderWindow window;
    window.create(sf::VideoMode(1600, 900), "Enigo's Sierpinski Triangle");



    sf::VertexArray myTriangles(sf::Triangles);
    sf::Vector2f start(window.getSize().x / 2, 0);

    recursiveSTriangle(start,myTriangles,window.getSize(),100);
    

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
        window.draw(myTriangles);
        window.display();

    }
    return 0;
}

void chaosGame(sf::VertexArray startTriangle, sf::VertexArray toDraw, sf::VertexArray &triStorage) {

    
    sf::Vector2f currentPoint(startTriangle[0].position.x,startTriangle[0].position.y + 10);

    for (int i = 0; i < 100000000; i++) {
        std::srand(std::time(nullptr));
        sf::Vertex endPoint = startTriangle[std::rand() % 3];


        //Update currentPosition with midpoint

        //Add to draw array
        toDraw.append(currentPoint);
    }

    
}

sf::Vector2f recursiveSTriangle(sf::Vector2f startPoint, sf::VertexArray &triStorage, sf::Vector2u max, float triangleSize, bool drawLeft, bool drawRight) {
    
    if (std::ceil(startPoint.y) > max.y | std::ceil(startPoint.x) < 0 | std::ceil(startPoint.x) > max.x) {
        return startPoint;
    }
    sf::Vector2f leftPoint;
    if (drawLeft) {
        leftPoint = recursiveSTriangle(sf::Vector2f(startPoint.x - (triangleSize / 2), startPoint.y + triangleSize), triStorage, max, triangleSize, drawLeft, !drawRight);

    }else{
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