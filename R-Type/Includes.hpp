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

// Bonus
#define S_BONUS_SIZE 0
#define S_BONUS_SPEED 1
#define S_BONUS_TRIPLE 2
#define S_SHIELD 3
#define S_BONUS_SHIELD 4

// Enemies
#define S_MINIBOSS 5
#define S_CTHULHU_EYE 6
#define S_CTHULHU_MOUTH 7
#define S_DEVOURER_HEAD 8
#define S_DEVOURER_BODY 9
#define S_DEVOURER_TAIL 10
#define S_ENEMY 11

// Fireballs
#define S_FIREBALL_BLUE 12
#define S_REV_FIREBALL 13
#define S_FIREBALL_YELLOW 14

// GUI
#define S_IDBAR 15
#define S_BUTTON 16

// Parallax
#define S_PARALLAX_0 17
#define S_PARALLAX_3 18
#define S_PARALLAX_4 19
#define S_PARALLAX_1 20
#define S_PARALLAX_2 21

// Player
#define S_VESSEL 22

// Audio
#define A_BATTLELINEBECK 0
#define A_MUSIC 1
#define A_BONUS 2
#define A_CTHULHURAGE 3
#define A_CTHULHURAGE2 4
#define A_LEVELCOMPLETED 5
#define A_SHOOT 6

#endif // INCLUDES_HPP
