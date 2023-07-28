#pragma once

#include <iostream>
#include <vector>

using UInt = uint64_t;
using UIntVec = std::vector<UInt>;

void Ntt(UIntVec &vec, UInt g, UInt mod);
void InvNtt(UIntVec &vec, UInt gi, UInt mod);

void NttOverARing(UIntVec &vec, UInt g, UInt mod);
void InvNttOverARing(UIntVec &vec, UInt gi, UInt mod);
