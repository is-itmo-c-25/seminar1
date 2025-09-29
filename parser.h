#pragma once

struct CLIArgs {
  const char* input_path = nullptr;
  const char* output_path = nullptr;
  bool filtered[256] = {};
};

bool ParseCLI(int size, char** args, CLIArgs* data);