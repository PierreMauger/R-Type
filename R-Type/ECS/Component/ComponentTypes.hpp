#ifndef COMPONENTTYPES_HPP
#define COMPONENTTYPES_HPP

#include "Includes.hpp"

typedef struct {
    float x;
    float y;
    float z;
} Position;

typedef struct {
    float x;
    float y;
    float z;
} Velocity;

typedef struct {
    std::size_t id;
} ModelID;

typedef struct {
    bool con;
} Controllable;

#endif // COMPONENTTYPES_HPP
