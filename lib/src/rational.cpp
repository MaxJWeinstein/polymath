#include "polymath/core/rational.hpp"

#include <boost/multiprecision/cpp_int.hpp>

namespace polymath::core
{
    namespace
    {
        using boost::multiprecision::cpp_int;
    } // namespace

    Rational Rational::operator+(const Rational &rhs) const
    {
        // a/b + c/d = (ad + bc)/bd
        RationalInt newNum = num_ * rhs.den_ + den_ * rhs.num_;
        RationalInt newDen = den_ * rhs.den_;
        return Rational(newNum, newDen);
    }

    Rational Rational::operator-(const Rational &rhs) const
    {
        return *this + (-rhs);
    }

    Rational Rational::operator*(const Rational &rhs) const
    {
        return Rational(num_ * rhs.num_, den_ * rhs.den_);
    }

    Rational Rational::operator/(const Rational &rhs) const
    {
        if (rhs.num_ == 0)
        {
            throw std::domain_error("Rational: division by zero");
        }
        return Rational(num_ * rhs.den_, den_ * rhs.num_);
    }

    double Rational::toDouble() const
    {
        return (num_.convert_to<double>()) / (den_.convert_to<double>());
    }

    std::string Rational::toString() const
    {
        if (den_ == 1)
        {
            return num_.str();
        }
        return num_.str() + "/" + den_.str();
    }

    void Rational::reduce()
    {
        // Ensure denominator is positive
        if (den_ < 0)
        {
            num_ = -num_;
            den_ = -den_;
        }
        RationalInt d = boost::multiprecision::gcd(num_, den_);
        if (d != 0)
        {
            num_ /= d;
            den_ /= d;
        }
    }

} // namespace polymath::core
