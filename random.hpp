// MIT License Copyright (c) 2021 Raphaël Thériault
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice (including the next
// paragraph) shall be included in all copies or substantial portions of the
// Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef _RAND_HPP
#define _RAND_HPP

#include <limits>
#include <random>
#include <type_traits>

namespace random {
template <typename T>
concept Integer = std::is_integral<T>::value&& requires(T n1, T n2) {
    std::uniform_int_distribution<T>(n1, n2);
};

template <typename T>
concept Real = std::is_floating_point<T>::value&& requires(T n1, T n2) {
    std::uniform_real_distribution<T>(n1, n2);
};

template <typename T> concept Engine = requires(T engine) {
    typename T::result_type;
    T(std::random_device{}());
    std::uniform_int_distribution<int>{}(engine);
    std::uniform_real_distribution<float>{}(engine);
    engine.seed(std::random_device{}());
};

/// Convenience wrapper around a C++11 random engine
template <Engine E = std::default_random_engine> class Rng {
    E engine;

  public:
    /// Type of seed this `Rng` requires
    typedef typename E::result_type Seed;

    /// Constructs a new `Rng` seeded randomly
    Rng() : engine(std::random_device{}()) {}
    /// Constructs a new `Rng` seeded with the provided value
    Rng(Seed seed) : engine(seed) {}
    /// Constructs a new `Rng` by wrapping an existing random engine
    Rng(const E& engine_) : engine(engine_) {}

    /// Seeds this `Rng` with the provided value, or a random one by default
    void seed(Seed seed = std::random_device{}()) { this->engine.seed(seed); }

    /// Generates an integer of the specified type bounded to [min, max], or the
    /// possible values of the type by default
    template <Integer T>
    T integer(T min = std::numeric_limits<T>::min(),
              T max = std::numeric_limits<T>::max()) {
        std::uniform_int_distribution<T> d(min, max);
        return d(this->engine);
    }

    /// Generates a floating point number of the specified type bounded to [min,
    /// max), or [0.0, 1.0) by default
    template <Real T> T real(T min = 0.0, T max = 1.0) {
        std::uniform_real_distribution<T> d(min, max);
        return d(this->engine);
    }

    /// Generates a boolean with probability `p` of being true, or an even
    /// probability by default
    bool boolean(double p = 0.5) {
        std::bernoulli_distribution d(p);
        return d(this->engine);
    }
};
} // namespace random

#endif
