#ifndef SJTU_COMPLEX_HPP
#define SJTU_COMPLEX_HPP

#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace sjtu {

class divided_by_zero final : public std::exception {
public:
  divided_by_zero() = default;
  ~divided_by_zero() = default;
  const char *what() const noexcept override {
    return "complex divided by zero!";
  }
};

inline int sign(double x) {
  const double eps = 1e-6;
  return (x > eps) - (x < -eps);
}

class complex {
private:
  double a, b; // a + bi

public:
  // Constructors
  complex() : a(0.0), b(0.0) {}
  complex(double ra) : a(ra), b(0.0) {}
  complex(double ra, double ib) : a(ra), b(ib) {}

  // Accessors returning references
  double &real() { return a; }
  double &imag() { return b; }

  // Unary operators
  complex operator-() const { return complex(-a, -b); }
  complex operator~() const { return complex(a, -b); }

  // Binary arithmetic operators
  complex operator+(const complex &rhs) const { return complex(a + rhs.a, b + rhs.b); }
  complex operator-(const complex &rhs) const { return complex(a - rhs.a, b - rhs.b); }
  complex operator*(const complex &rhs) const { return complex(a * rhs.a - b * rhs.b, a * rhs.b + b * rhs.a); }
  complex operator/(const complex &rhs) const {
    if (sign(rhs.a) == 0 && sign(rhs.b) == 0) {
      throw divided_by_zero();
    }
    double denom = rhs.a * rhs.a + rhs.b * rhs.b;
    return complex((a * rhs.a + b * rhs.b) / denom, (b * rhs.a - a * rhs.b) / denom);
  }

  // Compound assignment operators
  complex &operator+=(const complex &rhs) {
    a += rhs.a;
    b += rhs.b;
    return *this;
  }
  complex &operator-=(const complex &rhs) {
    a -= rhs.a;
    b -= rhs.b;
    return *this;
  }
  complex &operator*=(const complex &rhs) {
    double na = a * rhs.a - b * rhs.b;
    double nb = a * rhs.b + b * rhs.a;
    a = na;
    b = nb;
    return *this;
  }
  complex &operator/=(const complex &rhs) {
    if (sign(rhs.a) == 0 && sign(rhs.b) == 0) {
      throw divided_by_zero();
    }
    double denom = rhs.a * rhs.a + rhs.b * rhs.b;
    double na = (a * rhs.a + b * rhs.b) / denom;
    double nb = (b * rhs.a - a * rhs.b) / denom;
    a = na;
    b = nb;
    return *this;
  }

  // Equality with epsilon tolerance
  bool operator==(const complex &rhs) const {
    return std::fabs(a - rhs.a) < 1e-6 && std::fabs(b - rhs.b) < 1e-6;
  }

  // Bool conversion: false only when both are approximately zero
  explicit operator bool() const { return !(sign(a) == 0 && sign(b) == 0); }

  // Output format: [/-]real[+/-]imagi with 6 decimals
  friend std::ostream &operator<<(std::ostream &os, const complex &x) {
    os.setf(std::ios::fixed, std::ios::floatfield);
    std::streamsize old_prec = os.precision();
    os.precision(6);

    // Real part
    if (sign(x.a) == 0) {
      os << 0.0;
    } else {
      os << x.a;
    }

    // Imaginary sign
    if (sign(x.b) < 0) {
      os << '-';
    } else {
      os << '+';
    }

    // Imaginary magnitude
    double imag_mag = (sign(x.b) == 0) ? 0.0 : std::fabs(x.b);
    os << imag_mag << 'i';

    os.precision(old_prec);
    return os;
  }
};

} // namespace sjtu

#endif

