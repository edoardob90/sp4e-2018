#ifndef __COMPUTE_TEMPERATURE__HH__
#define __COMPUTE_TEMPERATURE__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"
#include "fft.hh"

//! Compute contact interaction between ping-pong balls
class ComputeTemperature : public Compute {
public:
  //! temperature evolution implementation
  void compute(System& system) override;

  //! return the heat conductivity
  Real & getConductivity(){return conductivity;};
  //! return the heat capacity
  Real & getCapacity(){return capacity;};
  //! return the heat capacity
  Real & getDensity(){return density;};
  //! return the characteristic length of the square
  Real & getL(){return L;};
  //! return the characteristic length of the square
  Real & getDeltat(){return delta_t;};

  // Also use setters for pybind
  void setConductivity(Real k) {this->conductivity = k;};
  void setCapacity(Real c) {this->capacity = c;};
  void setDensity(Real d) {this->density = d;};
  void setL(Real l) {this->L = l;};
  void setDeltat(Real dt) {this->delta_t = dt;};
  void setFrequencies(int side); // See .cc file for implementation

  // Whether or not to set frequencies
  bool implicit = true;

private:
  Matrix<Real> q; // FFT frequencies
  Real delta_t;
  Real conductivity;
  Real density;
  Real L;
  Real capacity;
};

/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_TEMPERATURE__HH__
