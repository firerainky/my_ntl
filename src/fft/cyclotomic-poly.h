#pragma once

#include <vector>
#include <iostream>

using UInt = uint64_t;
using UIntVec = std::vector<UInt>;

std::vector<int> CyclotomicPoly(int n);

void RecursiveNtt(UIntVec &vec, UInt g, UInt mod);
