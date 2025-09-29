#include <cstdio>
#include <cstdlib>
#include <chrono>

#include "parser.h"
#include "process.h"

using timer = std::chrono::high_resolution_clock;

int main(int argc, char** argv) {
  CLIArgs data;
  if (!ParseCLI(argc - 1, argv + 1, &data)) {
    std::fputs("Invalid arguments", stderr);
    return EXIT_FAILURE;
  }

  std::FILE* input = std::fopen(data.input_path, "r");
  if (input == nullptr) {
    std::fputs("Error while opening input file", stderr);
    return EXIT_FAILURE;
  }

  std::FILE* output = std::fopen(data.output_path, "w");
  if (output == nullptr) {
    std::fclose(input);
    std::fputs("Error while opening output file", stderr);
    return EXIT_FAILURE;
  }

  timer::time_point start = timer::now();
  bool ok = FilterNoBuffer(input, output, data.filtered);
  timer::time_point end = timer::now();
  if (!ok) {
    std::fputs("Error when processing", stderr);
  }
  std::chrono::duration elapsed = end - start;
  std::fprintf(stdout, "Required time: %lli", elapsed.count());

  if (std::fclose(input) == EOF) {
    std::fputs("Error while closing input file", stderr);
    return EXIT_FAILURE;
  }
  if (std::fclose(output) == EOF) {
    std::fputs("Error while closing output file", stderr);
    return EXIT_FAILURE;
  }
  return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}