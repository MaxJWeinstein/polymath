/*
 * @file rational.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-07-05
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <stdexcept>
#include <string>

namespace polymath::core
{
    // The integer type backing Rational. Currently set to arbitrary precision
    using RationalInt = boost::multiprecision::cpp_int;

    class Rational
    {
    public:
        Rational() : num_(0), den_(1) {}
        // RationalInt should implicitly convert other int types
        Rational(RationalInt numerator) : num_(std::move(numerator)), den_(1) {}
        Rational(RationalInt numerator, RationalInt denominator) : num_(std::move(numerator)), den_(std::move(denominator))
        {
            if (den_ == 0)
            {
                throw std::domain_error("Rational: zero denominator");
            }
        }

        const RationalInt &numerator() { return num_; }
        const RationalInt &denominator() { return den_; }

        Rational operator+(const Rational &rhs) const;
        Rational operator-(const Rational &rhs) const;
        Rational operator*(const Rational &rhs) const;
        Rational operator/(const Rational &rhs) const;
        Rational operator-() const { return Rational(-num_, den_); }

        bool operator==(const Rational &rhs) const
        {
            return (num_ == rhs.num_) && (den_ == rhs.den_); // Relies on reduction invariant
        }

        bool isInteger() const { return den_ == 1; }

        double toDouble() const;
        std::string toString() const;

    private:
        RationalInt num_;
        RationalInt den_; // Invariant: always > 0 after reducing

        // Divide out common factors, leave denominator positive
        void reduce();
    };
} // namespace polymath::core
