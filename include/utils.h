#ifndef UTILS_H
#define UTILS_H

#include <functional>
#include <stdexcept>
#include <random>
#include <string>

inline void error(const std::string& err)
{
    throw std::runtime_error(err);
}

template <typename T>
float rand(const T& low, const T& high)
{
    std::random_device r;
    static std::default_random_engine eng{r()};
    static std::uniform_real_distribution<> dis(
            low,
            std::nextafter(high, std::numeric_limits<T>::max())
            );
    return dis(eng);
}

#endif 
