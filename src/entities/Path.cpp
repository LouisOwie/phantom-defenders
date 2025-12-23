#include "Path.hpp"

Path::Path() = default;
Path::Path(const std::vector<glm::vec3>& points): points(points) {
    calculatePathPoints(points);
}

void Path::calculatePathPoints(const std::vector<glm::vec3>& points) {
    if (points.size() < 2) {
        this->points = points;
        return;
    }
    std::vector<glm::vec3> pathPoints;
    const float cornerRadius = 4.0f; // Radius of the rounding at the corners
    const int cornerSegments = 60; // Number of points per corner

    // Add the first point
    pathPoints.push_back(points[0]);

    // Process each segment
    for (size_t i = 0; i < points.size() - 1; ++i) {
        glm::vec3 current = points[i];
        glm::vec3 next = points[i + 1];
        glm::vec3 direction = glm::normalize(next - current);
        float segmentLength = glm::length(next - current);

        // If there is a next corner, round it
        if (i < points.size() - 2) {
            glm::vec3 afterNext = points[i + 2];
            glm::vec3 nextDirection = glm::normalize(afterNext - next);

            // Calculate how far before the corner the rounding should begin
            float distanceBeforeCorner = std::min(cornerRadius, segmentLength * 0.4f);
            float distanceAfterCorner = std::min(cornerRadius, glm::length(afterNext - next) * 0.4f);

            // Straight line until shortly before the corner
            glm::vec3 cornerStart = next - direction * distanceBeforeCorner;
            pathPoints.push_back(cornerStart);

            // Create the rounding at the corner with quadratic Bézier curve
            glm::vec3 cornerEnd = next + nextDirection * distanceAfterCorner;

            for (int j = 1; j <= cornerSegments; ++j) {
                float t = static_cast<float>(j) / (cornerSegments + 1);
                // Quadratic Bézier curve: B(t) = (1-t)²*P0 + 2(1-t)t*P1 + t²*P2
                glm::vec3 rounded =
                    (1.0f - t) * (1.0f - t) * cornerStart +
                    2.0f * (1.0f - t) * t * next +
                    t * t * cornerEnd;
                pathPoints.push_back(rounded);
            }
        } else {
            // Last segment: straight line to the end
            pathPoints.push_back(next);
        }
    }
    this->points = pathPoints;
}

glm::vec3 Path::getPoint() {
    if (!isEmpty()){
        return points[0];
    }
    return glm::vec3(0.0f);
}

void Path::deletePoint() {
    if (!isEmpty()) {
        points.erase(points.begin());
    }
}

bool Path::isEmpty() {
    return points.empty();
}

