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


#endif 
