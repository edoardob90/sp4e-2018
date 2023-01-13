#include "my_types.hh"

#include "material_point.hh"
#include "material_points_factory.hh"

#include "ping_pong_ball.hh"
#include "ping_pong_balls_factory.hh"

#include "planet.hh"
#include "planets_factory.hh"

#include "compute_boundary.hh"
#include "compute_contact.hh"
#include "compute_energy.hh"
#include "compute_gravity.hh"
#include "compute_interaction.hh"
#include "compute_kinetic_energy.hh"
#include "compute_potential_energy.hh"
#include "compute_temperature.hh"
#include "compute_verlet_integration.hh"

#include "system_evolution.hh"

#include "csv_reader.hh"
#include "csv_writer.hh"

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

// Need this because we access createSimulation in Python,
// which comes from the ParticlesFactoryInterface,
// so we must overload the pure virtual functions
// Helper class for abstract particles factory class
class PyParticlesFactoryInterface : public ParticlesFactoryInterface {
public:
    using ParticlesFactoryInterface::ParticlesFactoryInterface;

    SystemEvolution& createSimulation(const std::string& fname, 
                                      Real timestep) override {
        PYBIND11_OVERLOAD_PURE(SystemEvolution&, ParticlesFactoryInterface,
                             createSimulation, fname, timestep);
    }

    std::shared_ptr<Particle> createParticle() override {
        PYBIND11_OVERLOAD_PURE(std::shared_ptr<Particle>, 
                             ParticlesFactoryInterface, createParticle, );
    }
};

// Python Binding Module

PYBIND11_MODULE(pypart, m) {

    m.doc() = "Pybind module for the particles code";

    // Particles Factory Interface
    py::class_<ParticlesFactoryInterface, 
               PyParticlesFactoryInterface>(m, "ParticlesFactoryInterface")
        .def("createSimulation", &ParticlesFactoryInterface::createSimulation,
             py::return_value_policy::reference)
        .def("getInstance", &ParticlesFactoryInterface::getInstance,
             py::return_value_policy::reference)
        .def_property_readonly("system_evolution", 
                               &ParticlesFactoryInterface::getSystemEvolution)
        ;

    // Planets Factory
    py::class_<PlanetsFactory, ParticlesFactoryInterface>(m, "PlanetsFactory")
        .def("createSimulation", &PlanetsFactory::createSimulation,
             py::return_value_policy::reference)
        .def("getInstance", &PlanetsFactory::getInstance,
             py::return_value_policy::reference)
        ;

    // Ping Pong Ball Factory
    py::class_<PingPongBallsFactory, ParticlesFactoryInterface>(m, "PingPongBallsFactory")
        .def("createSimulation", &PingPongBallsFactory::createSimulation,
             py::return_value_policy::reference)
        .def("getInstance", &PingPongBallsFactory::getInstance,
             py::return_value_policy::reference)
        ;

    // Material Points Factory
    py::class_<MaterialPointsFactory, 
               ParticlesFactoryInterface>(m, "MaterialPointsFactory")
        .def("createSimulation", 
             (SystemEvolution& (MaterialPointsFactory::*)
              (const std::string &, Real)) 
             &MaterialPointsFactory::createSimulation,
             py::return_value_policy::reference)
        .def("createSimulation", 
             (SystemEvolution& (MaterialPointsFactory::*)
              (const std::string &, Real, 
               std::function<void(MaterialPointsFactory&, Real)>)) 
             &MaterialPointsFactory::createSimulation,
             py::return_value_policy::reference)
        .def("getInstance", &MaterialPointsFactory::getInstance,
                py::return_value_policy::reference)
        .def_property_readonly("system_evolution", 
                               &MaterialPointsFactory::getSystemEvolution)
        ;

    // Compute
    // Must template Compute objects with std::shared_ptr
    // because addCompute uses shared pointers to objects of type Compute
    py::class_<Compute, std::shared_ptr<Compute>>(m, "Compute");
    
    // Compute Temperature
    py::class_<ComputeTemperature, Compute, std::shared_ptr<ComputeTemperature>>(m, "ComputeTemperature")
        .def(py::init<>())
        .def_property("conductivity", &ComputeTemperature::getConductivity, 
                      &ComputeTemperature::setConductivity)
        .def_property("L", &ComputeTemperature::getL,
                      &ComputeTemperature::setL)
        .def_property("capacity", &ComputeTemperature::getCapacity,
                      &ComputeTemperature::setCapacity)
        .def_property("density", &ComputeTemperature::getDensity,
                      &ComputeTemperature::setDensity)
        .def_property("delta_t", &ComputeTemperature::getDeltat,
                      &ComputeTemperature::setDeltat)
        ;
    
    // CSV Writer
    py::class_<CsvWriter, Compute, std::shared_ptr<CsvWriter>>(m, "CsvWriter")
        .def(py::init<const std::string &>())
        .def("write", &CsvWriter::write)
        ;

    // System Evolution
    py::class_<SystemEvolution>(m, "SystemEvolution")
        .def("evolve", &SystemEvolution::evolve)
        .def("addCompute", &SystemEvolution::addCompute)
        .def("getSystem", &SystemEvolution::getSystem)
        .def("setNSteps", &SystemEvolution::setNSteps)
        .def("setDumpFreq", &SystemEvolution::setDumpFreq)
        ;

    // System
    py::class_<System>(m, "System");
    
}
