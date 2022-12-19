#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#define GRID_SIZE 32
#define TIME_PER_FRAME sf::seconds(1.f / 2.f)
#define PATH '0'
#define WALL '1'
#define START '2'
#define END '3'

enum Direction {LEFT, DOWN, RIGHT, UP};
const int DIR[5] = {-1, 0, 1, 0, -1};
