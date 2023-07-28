#pragma once

#include <vector>
#include <iostream>

using UInt = uint64_t;
using UIntVec = std::vector<UInt>;

void RecursiveNtt(UIntVec &vec, UInt g, UInt mod);
