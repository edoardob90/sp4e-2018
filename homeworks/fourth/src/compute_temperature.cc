#include "compute_temperature.hh"
#include "material_point.hh"
#include <cmath>

/* -------------------------------------------------------------------------- */
void ComputeTemperature::setFrequencies(int side) {
    Matrix<complex> qq = FFT::computeFrequencies(side);
    this->q.resize(side);
    for (UInt i = 0; i < side; ++i) {
        for (UInt j = 0; j < side; ++j) {
            this->q(i, j) = pow(qq(i, j).real(), 2) + pow(qq(i, j).imag(), 2);
        }
    }
    // normalize frequencies
    this->q /= (side*side);
}

void ComputeTemperature::compute(System& system) {
    // Build matrix from our list of particles
    UInt N = sqrt(system.getNbParticles());

    // On first step, set frequencies.
    // Ideally, we would want to avoid an if statement
    // in this function which will be used multiple times,
    // but I don't see any way around this with the new
    // "createComputes" infrastructure, since
    // this is set up before we build the simulation
    // and read the input file to know how many particles
    // there are. For the same reason the frequencies
    // can't really be set in the constructor
    if (implicit) {
        setFrequencies(N);
        implicit = false;
    }

    // Matrices for FFT
    Matrix<complex> m(N);
    Matrix<complex> m_fft(N);
    Matrix<complex> hv(N);
    Matrix<complex> hv_fft(N);

    // Loop over particles and extract temperature and 
    // heat flux into matrices
    UInt np = 0;
    for (UInt i = 0; i < N; ++i) {
        for (UInt j = 0; j < N; ++j) {
            auto& p = static_cast<MaterialPoint&>( system.getParticle(np) );
            m(i, j) = p.getTemperature();
            hv(i, j) = p.getHeatRate();
            np += 1;
        }
    }


    // Perform FFT
    m_fft = FFT::transform(m);
    hv_fft = FFT::transform(hv);

    // Loop over particles and compute derivative
    np = 0;
    for (UInt i = 0; i < N; ++i) {
        for (UInt j = 0; j < N; ++j) {
            auto& p = static_cast<MaterialPoint&>( system.getParticle(np) );
            m_fft(i, j) = 1.0/(density*capacity)*(hv_fft(i, j)-conductivity*m_fft(i, j)*q(i, j));
            np += 1;
        }
    }

    // Perform inverse FFT
    m = FFT::itransform(m_fft);

    // Loop over particles and perform the Euler integration
    // Don't update the temperature of "boundary" points
    np = 0;
    for (UInt i = 0; i < N; ++i) {
        for (UInt j = 0; j < N; ++j) {
            auto& p = static_cast<MaterialPoint&>( system.getParticle(np) );
            if ( p.isBoundary() ) p.setTemperature(0.0);
            else p.setTemperature( p.getTemperature() + delta_t * m(i,j).real() );
            np += 1;
        }
    }

}

/* -------------------------------------------------------------------------- */
