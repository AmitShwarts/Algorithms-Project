#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "DataStructures/header/AdjacentList.h"
#include "DataStructures/header/MinHeap.h"
#include "DataStructures/header/ArrayPriorityQueue.h"

class Graph;

constexpr float MAX_WEIGHT = -1;

namespace Error
{
  const std::string OUT_OF_RANGE_VERTEX_INDEX = "Invalid vertex index";
  const std::string CONSTRUCTOR_INPUT_NON_POSITIVE = "Size must be positive int";
  const std::string NEGATIVE_CYCLE = "There is a negative cycle";
  const std::string INVALID_INPUT = "Input is not valid";
}
