#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include "header/AdjacentList.h"

struct ListNode
{
	int vertex, weight;
	ListNode *next, *prev;
};

class AdjacentList;

constexpr int MAX_WEIGHT = INT_MAX;
