cmake_minimum_required(VERSION 3.12)
project(week8)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(week8
        src/CMakeLists.txt
        src/compute.hh
        src/compute_boundary.cc
        src/compute_boundary.hh
        src/compute_contact.cc
        src/compute_contact.hh
        src/compute_energy.cc
        src/compute_energy.hh
        src/compute_gravity.cc
        src/compute_gravity.hh
        src/compute_interaction.cc
        src/compute_interaction.hh
        src/compute_kinetic_energy.cc
        src/compute_kinetic_energy.hh
        src/compute_potential_energy.cc
        src/compute_potential_energy.hh
        src/compute_verlet_integration.cc
        src/compute_verlet_integration.hh
        src/csv_reader.cc
        src/csv_reader.hh
        src/csv_writer.cc
        src/csv_writer.hh
        src/main.cc
        src/my_types.hh
        src/particle.cc
        src/particle.hh
        src/particles_factory_interface.cc
        src/particles_factory_interface.hh
        src/ping_pong_ball.cc
        src/ping_pong_ball.hh
        src/ping_pong_balls_factory.cc
        src/ping_pong_balls_factory.hh
        src/planet.cc
        src/planet.hh
        src/planets_factory.cc
        src/planets_factory.hh
        src/system.cc
        src/system.hh
        src/system_evolution.cc
        src/system_evolution.hh
        src/vector.cc
        src/vector.hh)
