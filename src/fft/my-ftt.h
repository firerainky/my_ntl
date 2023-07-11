#pragma once

#include <vector>
#include <iostream>
#include <complex>

using Complex = std::complex<double>;
using ComplexVec = std::vector<Complex>;

void MyFft(Complex* coeffs, size_t size);
void MyFftVec(ComplexVec &coeffs, bool inv = false);
void MyFftVecOptimize(ComplexVec &coeffs, bool inv = false);
