#include "particle.hh"

void Particle::printself(std::ostream& stream) const {
    // This behaves identically to Particle::initself below
    stream << this->position << this->velocity << this->force << this->mass;
}

/* -------------------------------------------------------------------------- */

void Particle::initself(std::istream& sstr) {
    /* Here we should initialize the values of the vectors: position, velocity, forces
     * from the input values found in filename
     * The read should be smth like:
     * sstr >> position >> velocity >> forces
     * but the '>>' should be able to deal with triplets of real numbers
     */
    sstr >> this->position >> this->velocity >> this->force >> this->mass;
}
