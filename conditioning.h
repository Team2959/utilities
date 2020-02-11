#pragma once

#include <cmath>

namespace cwtech
{
    class UniformConditioning
    {
    private:
        double m_deadband = 0.1;
        double m_power    = 1.0;
        double m_min      = 0.0;
        double m_max      = 1.0;

        double m_range    = 1.0;
        double m_mult     = 0.0;

        void Precompute () {
            m_mult = 1.0 / (1.0 - m_deadband);
            m_range = m_max - m_min;
        };
    
    public:
        UniformConditioning() {
            Precompute();
        };
        void SetDeadband (double db) {
            db = std::abs(db);
            db = std::fmin(db, 1.0);
            m_deadband = db;

            Precompute();
        };
        void SetExponent (double expo) {
            expo = std::fmax(expo, 1.0);
            m_power = expo;

            Precompute();
        };
        void SetRange (double min, double max) {
            m_min = std::fmin(min, max);
            m_max = std::fmax(min, max);

            Precompute();
        };

        double Condition (double x) {
            // Equation can be previewed here https://www.desmos.com/calculator/6f8byd00nt
            double xa = std::abs(x);
            double xs = cwtech::JSCSgn(x);
            if (xa < m_deadband) {
                return 0;
            } else {
                return xs * ((cwtech::JSCPower((xa - m_deadband) * m_mult, m_power) * m_range) + m_min);
            }
        };
    };

    class NonUniformConditioning {
    public:
        UniformConditioning Negative;
        UniformConditioning Positive;

        double Condition (double x) {
            if (x < 0) return Negative.Condition(x);
            return Positive.Condition(x);
        }
    };

    double JSCPower (double base, double power) {
        long ipart = (long)power;
        double fpart = power - ipart;

        switch (ipart) {
        case 0:
            return base;
        case 1:
            return base * (fpart*base + (1-fpart));
        case 2:
            return base*base * (fpart*base + (1-fpart));
        case 3:
            return base*base*base * (fpart*base + (1-fpart));
        default:
            double result = 1.0;
            while (--ipart) result *= base;
            return result * (fpart*base + (1-fpart));
        }
    };
    inline double JSCSgn (double num) {
        return (0.0 < num) - (num < 0.0);
    };
}
