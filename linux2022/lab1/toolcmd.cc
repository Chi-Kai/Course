#include <unistd.h>

#include <fstream>

#include "shell.h"
#include "tools.h"
using namespace std;
// grep - print lines matching a pattern
void Shell::grep() {
  print_reset();
  // pipe to grep
  cout << pipe_stream.str() << endl;
  if (pipe_stream.str().size() != 0) {
    std::string line;
    while (std::getline(pipe_stream, line)) {
      if (line.find(args[1]) != std::string::npos) {
        std::cout << line << std::endl;
      }
    }
    return;
  }
  if (args.size() == 1) {
    std::cout << "grep pattern file" << std::endl;
    return;
  }
  if (args.size() == 2) {
    std::cout << "grep pattern file" << std::endl;
    return;
  }
  std::ifstream in(args[2]);
  if (!in) {
    std::cout << "grep: cannot open '" << args[2] << "'" << std::endl;
    return;
  }
  std::string line;
  while (std::getline(in, line)) {
    if (line.find(args[1]) != std::string::npos) {
      std::cout << line << std::endl;
    }
  }
}
