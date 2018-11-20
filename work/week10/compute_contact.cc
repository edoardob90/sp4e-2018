#include "compute_contact.hh"
#include "ping_pong_ball.hh"
#include <cmath>
/* -------------------------------------------------------------------------- */
void ComputeContact::setPenalty(Real penalty) { this->penalty = penalty; }
/* -------------------------------------------------------------------------- */
void ComputeContact::computePairInteraction(Particle& par1, Particle& par2) {
    /* we need to static_cast par{1,2} to PingPongBall, otherwise getRadius() may fetch "rubbish" data
     * because the compiler wouldn't know which daughter class (Planet or PingPongBall) we are referring to
    */
    auto pball1 = static_cast<PingPongBall&>(par1);
    auto pball2 = static_cast<PingPongBall&>(par2);

    // get distance between particles
    auto dist = pball1.getPosition() - pball2.getPosition();
    auto dist_dot_dist = dist.squaredNorm(); // because it's the scalar product of dist with itself!

    // if particles are not distict, return
    if (dist_dot_dist == 0 ) return;

    // normalize distance. We need vec{r_ij}/r_ij
    auto dist_norm = sqrt(dist_dot_dist); // compute the norm
    dist /= dist_norm; // normalize

    // first evaluate the p_ij factor (compenetration/gap term)
    auto inter_contact = ( pball1.getRadius() + pball2.getRadius() ) - dist_norm;
    Real p_factor;
    ( inter_contact > 0 ) ? p_factor = inter_contact : p_factor = 0.;
    // compute force
    auto force = dist * penalty * p_factor;

    // update force
    pball1.getForce() += force;
    pball2.getForce() -= force;

}
