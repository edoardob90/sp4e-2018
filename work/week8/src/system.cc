#include "system.hh"

Particle& System::getParticle(UInt i) {
    /** Return the particle with id i
     */
    return ParticleList.at(i);
}

/* -------------------------------------------------------------------------- */

void System::addParticle(const std::shared_ptr<Particle>& new_particle) {
    /** This adds a particle to the system
     */
    ParticleList.push_back(new_particle);
}

/* -------------------------------------------------------------------------- */

UInt System::getNbParticles() {
    /** Return the total number of particles in the system
     */
    return ParticleList.size();
}
