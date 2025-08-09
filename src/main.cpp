#include <SFML/Graphics.hpp>

#include "SAT_Collision.hpp"

#define PI 3.14159265359

int main() {
	sf::RenderWindow window(sf::VideoMode(500, 500), "SAT Collision");
	sf::Event event;

	SAT sat;

	sf::ConvexShape polygonA;

	polygonA.setPointCount(3);

	polygonA.setPoint(0.f, { 0.f, 0.f });
	polygonA.setPoint(1.f, { 100.f, 0.f });
	polygonA.setPoint(2.f, { 50.f, 100.f });

	sf::FloatRect boundsA = polygonA.getLocalBounds();
	polygonA.setOrigin(boundsA.left + boundsA.width / 2.f, boundsA.top + boundsA.height / 2.f);

	polygonA.setPosition(100.f, 120.f);
	polygonA.setFillColor(sf::Color::Transparent);

	polygonA.setOutlineColor(sf::Color::Green);
	polygonA.setOutlineThickness(1);

	sf::ConvexShape polygonB;

	polygonB.setPointCount(3);

	polygonB.setPoint(0, { 0.f, 0.f });
	polygonB.setPoint(1, { 100.f, 0.f });
	polygonB.setPoint(2, { 50.f, 100.f });

	sf::FloatRect boundsB = polygonB.getLocalBounds();
	polygonB.setOrigin(boundsB.left + boundsB.width / 2.f, boundsB.top + boundsB.height / 2.f);

	polygonB.setPosition(250.f, 250.f);
	polygonB.setFillColor(sf::Color::Transparent);

	polygonB.setOutlineColor(sf::Color::Green);
	polygonB.setOutlineThickness(1);

	float polygonARotationSpeed = 50.f;
	float polygonBRotationSpeed = 50.f;

	float polygonAMoveSpeed = 0.1f;

	sf::Font In1Font;
	In1Font.loadFromFile("Basic.ttf");

	sf::Text In1;
	In1.setString("Press 'F' to rotate the triangle A");
	In1.setFillColor(sf::Color::White);
	In1.setFont(In1Font);
	In1.setPosition(0.f, 0.f);
	In1.setCharacterSize(15.f);

	sf::Font In2Font;
	In2Font.loadFromFile("Basic.ttf");

	sf::Text In2;
	In2.setString("Press 'J' to rotate triangle B");
	In2.setFillColor(sf::Color::White);
	In2.setFont(In1Font);
	In2.setPosition(0.f, 20.f);
	In2.setCharacterSize(15.f);

	sf::Font In3Font;
	In3Font.loadFromFile("Basic.ttf");

	sf::Text In3;
	In3.setString("Press WASD to move triangle A");
	In3.setFillColor(sf::Color::White);
	In3.setFont(In1Font);
	In3.setPosition(0.f, 40.f);
	In3.setCharacterSize(15.f);

	sf::Clock clock;
	float dt;

	while (window.isOpen()) {
		dt = clock.restart().asSeconds();

		while (window.pollEvent(event)) {
			if (event.type == event.Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			polygonA.rotate(polygonARotationSpeed * dt);
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
			polygonB.rotate(polygonBRotationSpeed * dt);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			polygonA.move(0, -polygonAMoveSpeed);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			polygonA.move(0, polygonAMoveSpeed);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			polygonA.move(-polygonAMoveSpeed, 0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			polygonA.move(polygonAMoveSpeed, 0);

		sat.checkSATCollision(polygonA, polygonB);

		window.clear();

		window.draw(polygonA);
		window.draw(polygonB);

		window.draw(In1);
		window.draw(In2);
		window.draw(In3);

		window.display();
	}
}