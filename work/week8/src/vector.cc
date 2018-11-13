#include "vector.hh"

Real& Vector::operator[](UInt i) {
    return values.at(i);
}
const Real& Vector::operator[](UInt i) const {
    return values.at(i);
}

Real Vector::squaredNorm() const {
    Real norm = 0.;
    for (const Real& elem : values) norm += elem*elem;
    return norm;
}

/* -------------------------------------------------------------------------- */

Vector& Vector::operator+=(const Vector& vec) {
    for (UInt i=0; i<Vector::dim; ++i) (*this)[i] += vec[i];
    return *this;
}

Vector& Vector::operator-=(const Vector& vec) {
    for (UInt i=0; i<Vector::dim; ++i) (*this)[i] -= vec[i];
  return *this;
}

Vector& Vector::operator*=(Real val) {
    for (UInt i=0; i<Vector::dim; ++i) (*this)[i] *= val;
  return *this;
}

Vector& Vector::operator/=(Real val) {
    for (UInt i=0; i<Vector::dim; ++i) (*this)[i] /= val;
  return *this;
}

/* -------------------------------------------------------------------------- */

Vector& Vector::operator=(const Vector& vec) {
    for (UInt i=0; i<Vector::dim; ++i) (*this)[i] = vec[i];
    return *this;
}

Vector& Vector::operator=(Real val) {
    for (UInt i=0; i<Vector::dim; ++i) (*this)[i] = val;
    return *this;
}

/* -------------------------------------------------------------------------- */
/* All these methods should whether the two vectors have the same shape. Two notes:
 * 1) maybe it's better to raise an exception?
 * 2) we could build a unit test for this?
 */
Vector operator+(const Vector& a, const Vector& b) {
    Vector result;
    for (UInt i=0; i<Vector::dim; ++i) result[i] = a[i] + b[i];
    return result;
}

Vector operator-(const Vector& a, const Vector& b) {
    Vector result;
    for (UInt i=0; i<Vector::dim; ++i) result[i] = a[i] - b[i];
    return result;
}

Vector operator*(const Vector& a, Real val) {
    Vector result;
    for (UInt i=0; i<Vector::dim; ++i) result[i] = a[i] * val;
    return result;
}

Vector operator*(Real val, const Vector& a) {
    Vector result;
    for (UInt i=0; i<Vector::dim; ++i) result[i] = a[i] * val;
    return result;
}

Vector operator/(const Vector& a, Real val) {
    Vector result;
    for (UInt i=0; i<Vector::dim; ++i) result[i] = a[i] / val;
    return result;
}

/* -------------------------------------------------------------------------- */

/// standard output stream operator
std::ostream& operator<<(std::ostream& stream, const Vector& _this) {
    for (UInt i = 0; i<_this.dim; ++i) stream << _this[i];
    return stream;
}

/* -------------------------------------------------------------------------- */
/// standard input stream operator
std::istream& operator>>(std::istream& stream, Vector& _this) {
    for (UInt i = 0; i<_this.dim; ++i) stream >> _this[i];
    return stream;
}
