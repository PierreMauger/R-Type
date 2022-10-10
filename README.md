# <p align="center">👽 R-Type 🚀</p>

## <p align="center">A horizontally scrolling shooter made with ECS</p>

<p align="center">
  <img src="https://fs-prod-cdn.nintendo-europe.com/media/images/10_share_images/games_15/virtual_console_wii_u_7/H2x1_WiiUVC_RType.jpg">
</p>

## 📋 Table of Contents
<details>
<summary>Click to reveal</summary>

- [About](#-about)
- [Requirements](#-requirements)
- [Building](#-building)
- [Usage](#-usage)
- [Authors](#-authors)

</details>

## 🔍 About

[R-Type](https://en.wikipedia.org/wiki/R-Type) is a 3rd year Epitech project where a group of 4-6 students have to code an ersatz of the original horizontally scrolling shooter arcade video game from 1987 of the same name.
In the span of 2 months, the goal is to learn the [ECS](https://en.wikipedia.org/wiki/Entity_component_system) architectural pattern to code the game in C++ with an additional 2-4 players coop.

## 💻 Requirements

Supported operating systems:
- Windows (tested on Windows 10 Home 21H1 x64)
- Linux (tested on Ubuntu 2204 and Fedora 32)
- MacOS

Dependencies:
- Cmake 3.24+

## 🔧 Building

Launch r-type.sh (linux/MacOS) or r-type.bat (Windows) to start the building of the project.
It will automatically:
- Download the [SFML](https://www.sfml-dev.org/)
- Download [Boost Asio](https://think-async.com/Asio/)
- Build the r-type_client and r-type_server executables (.exe on Windows) using those libraries

## 🎮 Usage

One person has to start r-type_server to host the server and can also start r-type_client to be a player. The other player(s) just has to start r-type_client on their end aswell.

## 🤝 Authors

[Pierre HAMEL](https://github.com/pierre1754) - [Dorian AYOUL](https://github.com/NairodGH) - [Jean-Baptiste BROCHERIE](https://github.com/Parumezan) - [Pierre MAUGER](https://github.com/PierreMauger) - [Xavier TONNELLIER](https://github.com/XavTo)