#include "ping_pong_balls_factory.hh"
#include "compute_contact.hh"
#include "compute_verlet_integration.hh"
#include "csv_reader.hh"
#include "csv_writer.hh"
#include "ping_pong_ball.hh"
#include <cmath>
#include <iostream>
/* -------------------------------------------------------------------------- */

std::unique_ptr<Particle> PingPongBallsFactory::createParticle() {
    return std::make_unique<PingPongBall>();
}

/* -------------------------------------------------------------------------- */

SystemEvolution&
PingPongBallsFactory::createSimulation(const std::string& fname,
                                       Real timestep) {
    // Instantiate a SystemEvolution object
    // the constructor takes as input argument a System object
    this->system_evolution = std::make_unique<SystemEvolution>(std::make_unique<System>());

    // Read input
    CsvReader reader(fname);
    reader.read(this->system_evolution->getSystem());

    // Setup interactions & VVerlet algorhitm
    auto verlet = std::make_shared<ComputeVerletIntegration>(timestep);
    auto contact = std::make_shared<ComputeContact>();

    return *this->system_evolution;
}

/* -------------------------------------------------------------------------- */

ParticlesFactoryInterface& PingPongBallsFactory::getInstance() {

  if (not ParticlesFactoryInterface::factory)
    ParticlesFactoryInterface::factory = new PingPongBallsFactory;

  return *factory;
}

/* -------------------------------------------------------------------------- */
