#pragma once

#include <iostream>
#include <vector>

using UInt = uint64_t;
using UIntVec = std::vector<UInt>;

void RecursiveNtt(UIntVec &vec, UInt g, UInt mod);
void InverseNtt(UIntVec &vec, UInt gi, UInt mod);
