#pragma once

#include <cstdio>

bool FilterBuffered(std::FILE* input, std::FILE* output, bool* filtered);
bool FilterNoBuffer(std::FILE* input, std::FILE* output, bool* filtered);