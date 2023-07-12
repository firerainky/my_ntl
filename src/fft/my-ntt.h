#pragma once

#include <vector>
#include <iostream>

int64_t FastPower(int64_t n, int64_t power, int64_t mod);
void MyNtt(int64_t *vec, size_t len, int64_t g, int64_t gi, int64_t mod, bool inv = false);
