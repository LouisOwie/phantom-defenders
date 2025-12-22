#ifndef PHANTOM_DEFENDERS_GHOST_HPP
#define PHANTOM_DEFENDERS_GHOST_HPP
#include "Model.hpp"

class Ghost {
public:
    Ghost();
    Model getModel();
private:
    Model model;
};
#endif //PHANTOM_DEFENDERS_GHOST_HPP