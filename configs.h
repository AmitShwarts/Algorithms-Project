#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <fstream>
#include "DataStructures/header/AdjacentList.h"

class Graph;

constexpr int MAX_WEIGHT = INT_MAX;
namespace Error
{
  const std::string CONSTRUCTOR_INPUT_NON_POSITIVE = "Size must be positive int";
  const std::string OUT_OF_RANGE_VERTEX_INDEX = "Invalid vertex index";
  const std::string OUT_OF_RANGE = "Out of range";
}
