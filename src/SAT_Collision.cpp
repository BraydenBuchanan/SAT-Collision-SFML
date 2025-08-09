#include "SAT_Collision.hpp"

// Normalize the vector
sf::Vector2f SAT::normalize(const sf::Vector2f& vector) {
	float length = sqrt(vector.x * vector.x + vector.y * vector.y);
	return vector / length;
}

// Find the verticies of a rotated polygon
std::vector<sf::Vector2f> SAT::getVertices(const sf::ConvexShape& polygon) {
	std::vector<sf::Vector2f> vertices;
	const sf::Transform& transform = polygon.getTransform();
	sf::FloatRect bounds = polygon.getLocalBounds();

	vertices.push_back(transform.transformPoint(polygon.getPoint(0)));
	vertices.push_back(transform.transformPoint(polygon.getPoint(1)));
	vertices.push_back(transform.transformPoint(polygon.getPoint(2)));

	return vertices;
}

// Find the edge of a polygon
std::vector<sf::Vector2f> SAT::getEdges(const std::vector<sf::Vector2f>& vertices) {
	std::vector<sf::Vector2f> edges;

	for (int i = 0; i < vertices.size(); i++) {
		sf::Vector2f edge = vertices[(i + 1) % vertices.size()] - vertices[i];
		edges.push_back(edge);
	}

	return edges;
}

// Project the polygon onto an axis
void SAT::project(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& axis, float& min, float& max) {
	min = max = dotProduct(vertices[0], axis);

	for (int i = 0; i < vertices.size(); i++) {
		float projection = dotProduct(vertices[i], axis);

		if (projection < min)
			min = projection;

		if (projection > max)
			max = projection;
	}
}
// Collision
bool SAT::checkSATCollision(sf::ConvexShape& a, sf::ConvexShape& b) {
	float Inf = std::numeric_limits<float>::infinity();
	sf::Vector2f minAxis;

	auto verticesA = getVertices(a);
	auto verticesB = getVertices(b);

	auto edgesA = getEdges(verticesA);
	auto edgesB = getEdges(verticesB);

	std::vector<sf::Vector2f> axes;

	for (const auto& edge : edgesA)
		axes.push_back(normalize(sf::Vector2f(edge.y, edge.x)));

	for (const auto& edge : edgesB)
		axes.push_back(normalize(sf::Vector2f(-edge.y, edge.x)));

	for (const auto& axis : axes) {
		float minA, minB;
		float maxA, maxB;

		project(verticesA, axis, minA, maxA);
		project(verticesB, axis, minB, maxB);

		float overlap = std::min(maxA, maxB) - std::max(minA, minB);

		if (overlap <= 0.f)
			return false;

		if (overlap < Inf) {
			Inf = overlap;
			minAxis = axis;

			if (minB < minA) minAxis = -minAxis;
		}
	}

	mtv = minAxis * Inf;

	a.move(-(mtv));
	b.move((mtv * float(1E-100)));

	return true;
}