/**
 * @file Includes.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The standard c++ includes needed for this project.
 * @copyright Epitech Rennes 2022
 */

#ifndef INCLUDES_HPP
#define INCLUDES_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <any>
#include <array>
#include <bitset>
#include <condition_variable>
#include <cstring>
#include <deque>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <typeindex>
#include <unordered_map>
#include <vector>
#ifdef _WIN32
    #include <SDKDDKVer.h>
    #define M_PI 3.141592653589793
#endif

#define S_IDBAR                 1
#define S_ENEMY                 2
// #define S_FIREBALL_BLUE         3
// #define S_FIREBALL_YELLOW       4
#define S_MINIBOSS              5
#define S_VESSEL                6

// Bonus Icons
#define S_BONUS_SPEED           7
#define S_BONUS_SHOOT_SIZE      8

// #define ???                      9
#define S_BUTTON                10

// Parallax
#define S_PARALLAX_0            11
#define S_PARALLAX_3            12
#define S_PARALLAX_4            13
#define S_PARALLAX_1            14
#define S_PARALLAX_2            15

// Devoureur
#define S_DEVOURER_HEAD         16
#define S_DEVOURER_BODY         17
#define S_DEVOURER_TAIL         18

// Cthulhu
#define S_CTHULHU_EYE           19
#define S_CTHULHU_MOUTH         20

// Bonus
#define S_SHIELD                21
#define S_BONUS_SHIELD          22


#endif // INCLUDES_HPP
