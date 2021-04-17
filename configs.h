#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "DataStructures/header/AdjacentList.h"
#include "DataStructures/header/MinHeap.h"

class Graph;

constexpr int MAX_WEIGHT = INT_MAX;

namespace Error
{
  const std::string OUT_OF_RANGE_VERTEX_INDEX = "Invalid vertex index";
  const std::string CONSTRUCTOR_INPUT_NON_POSITIVE = "Size must be positive int";
  const std::string NEGATIVE_CYCLE = "There is a negative cycle";
  const std::string INVALID_INPUT = "Input is not valid";
}
