#include "planet.hh"

void Planet::initself(std::istream &stream) {
    stream << this->position << this->velocity << this->force << this->mass << this->name;
}

/* -------------------------------------------------------------------------- */

void Planet::printself(std::ostream &stream) const {
    sstr >> this->position >> this->velocity >> this->force >> this->mass >> this->name;
}
