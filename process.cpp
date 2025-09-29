#include "process.h"

#include <cstdio>

const std::size_t kBufferSize = 16384;

bool FilterBuffered(std::FILE* input, std::FILE* output, bool* filtered) {
  char input_buffer[kBufferSize];
  char output_buffer[kBufferSize];
  std::size_t out_filled = 0;

  while (true) {
    std::size_t read = std::fread(input_buffer, sizeof(char), kBufferSize, input);

    for (std::size_t i = 0; i < read; ++i) {
      char sym = input_buffer[i];
      if (filtered[(unsigned char)sym]) continue;

      // clear filled buffer
      if (out_filled == kBufferSize) {
        std::size_t written = std::fwrite(output_buffer, sizeof(char), kBufferSize, output);
        if (written != kBufferSize) {
          std::fputs("Error when writing", stderr);
          return false;
        }

        out_filled = 0;
      }

      output_buffer[out_filled++] = sym;
    }

    if (read != kBufferSize) {
      if (std::ferror(input)) {
        std::fputs("Error when reading", stderr);
        return false;
      }
      // end of file, finish
      break;
    }
  }

  if (out_filled != 0) {
    // write remaining data
    std::size_t written = std::fwrite(output_buffer, sizeof(char), out_filled, output);
    if (written != out_filled) {
      std::fputs("Error when writing", stderr);
      return false;
    }
  }

  return true;
}

bool FilterNoBuffer(std::FILE* input, std::FILE* output, bool* filtered) {
  while (true) {
    int sym = std::fgetc(input);
    if (sym == EOF) {
      if (std::ferror(input)) {
        std::fputs("Error when reading", stderr);
        return false;
      }
      // end of file
      break;
    }

    if (filtered[(unsigned char)sym]) continue;

    int written = std::fputc(sym, output);
    if (written == EOF) {
      std::fputs("Error when writing", stderr);
      return false;
    }
  }

  return true;
}