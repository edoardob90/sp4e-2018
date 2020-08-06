cmake_minimum_required (VERSION 3.1)
cmake_policy(VERSION 3.3)
set(CMAKE_CXX_STANDARD 14)

################################################################
# libpart
################################################################

message(STATUS "FFTW3 library include path is ${FFTW_INCLUDE_DIRS}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(part STATIC
  compute_boundary.cc
  compute_verlet_integration.cc 
  particle.cc 
  planet.cc
  compute_gravity.cc 
  csv_reader.cc 
  particles_factory_interface.cc 
  planets_factory.cc 
  compute_contact.cc 
  compute_kinetic_energy.cc 
  csv_writer.cc 
  system.cc 
  compute_energy.cc 
  compute_potential_energy.cc 
  ping_pong_ball.cc
  material_point.cc 
  system_evolution.cc 
  ping_pong_balls_factory.cc 
  compute_interaction.cc
  compute_temperature.cc
  material_points_factory.cc 
)
