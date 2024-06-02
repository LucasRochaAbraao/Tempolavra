#pragma once

#include <vector>
#include <tuple>


// a type alias for the tuples inside get_coord_hour and get_coord_minute
using IntTuple = std::tuple<int, int>;

bool flip_coin(double);

std::vector<IntTuple> get_coord_hour(int);

std::vector<IntTuple> get_coord_minute(int);
