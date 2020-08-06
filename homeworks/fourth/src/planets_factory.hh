#ifndef __PLANETS_FACTORY__HH__
#define __PLANETS_FACTORY__HH__

/* -------------------------------------------------------------------------- */
#include "particles_factory_interface.hh"
#include "planet.hh"
/* -------------------------------------------------------------------------- */

//! Factory for planet simulations
class PlanetsFactory : public ParticlesFactoryInterface {
  /* ------------------------------------------------------------------------ */
  /* Constructors/Destructors                                                 */
  /* ------------------------------------------------------------------------ */
private:
  PlanetsFactory() = default;

  /* ------------------------------------------------------------------------ */
  /* Methods                                                                  */
  /* ------------------------------------------------------------------------ */

public:
  SystemEvolution& createSimulation(const std::string& fname,
                                    Real timestep) override;

  std::shared_ptr<Particle> createParticle() override;

  static ParticlesFactoryInterface& getInstance();
};

/* -------------------------------------------------------------------------- */
#endif  //__PLANETS_FACTORY__HH__
