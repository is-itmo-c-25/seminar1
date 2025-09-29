#include <cstring>

#include "parser.h"

bool ParseCLI(int size, char** args, CLIArgs* data) {
  for (int i = 0; i < size; ++i) {
    if (strcmp(args[i], "--input") == 0) {
      // '--input' should not be the last
      if (++i == size) return false;

      data->input_path = args[i];
    } else if (strcmp(args[i], "--output") == 0) {
      // '--output' should not be the last
      if (++i == size) return false;

      data->output_path = args[i];
    } else if(strcmp(args[i], "--filter") == 0) {
      // '--filter' should not be the last
      if (++i == size) return false;

      for (char* sym = args[i]; *sym != '\0'; ++sym) {
        data->filtered[(unsigned char)*sym] = true;
      }
    } else if(args[i][0] == '-' && args[i][1] == 'f') {
      if (args[i][2] == '\0') return false;
      if (args[i][3] != '\0') return false;
      data->filtered[(unsigned char)args[i][2]] = true;
    } else {
      // unknown argument
      return false;
    }
  }
  return (data->input_path != nullptr) &&
         (data->output_path != nullptr);
}