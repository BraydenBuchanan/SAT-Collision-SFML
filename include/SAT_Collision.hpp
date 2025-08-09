#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class SAT {
public:
	bool checkSATCollision(sf::ConvexShape& a, sf::ConvexShape& b);

private:
	float dotProduct(const sf::Vector2f& a, const sf::Vector2f& b) { return a.x * b.x + a.y * b.y; }

	sf::Vector2f normalize(const sf::Vector2f& vector);
	std::vector<sf::Vector2f> getVertices(const sf::ConvexShape& polygon);
	std::vector<sf::Vector2f> getEdges(const std::vector<sf::Vector2f>& vertices);
	void project(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& axis, float& min, float& max);

private:
	sf::Vector2f mtv;
};