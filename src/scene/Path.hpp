#ifndef PHANTOM_DEFENDERS_PATH_HPP
#define PHANTOM_DEFENDERS_PATH_HPP
#include <glm/glm.hpp>
#include <vector>

class Path {
public:
    Path();
    Path(const std::vector<glm::vec3>& points);
    glm::vec3 getPoint();
    void deletePoint();
    bool isEmpty();
private:
    std::vector<glm::vec3> points;
    void calculatePathPoints(std::vector<glm::vec3> points);
};
#endif //PHANTOM_DEFENDERS_PATH_HPP