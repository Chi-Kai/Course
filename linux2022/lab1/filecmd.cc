/* some commands about the file system
 * rm - remove a file
 * mkdir - make a directory
 * cd - change directory
 * pwd - print the current directory
 * cat - concatenate files
 * ls - list files in a directory
 * wc - count lines, words, and characters in a file
 * cp - copy file
 * touch - create a file
 */
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include "shell.h"
using namespace std;
// remove files
void Shell::rm() {
  print_reset();
  for (int i = 1; i < args.size(); i++) {
    if (std::remove(args[i].c_str()) != 0)
      std::cout << "rm: cannot remove '" << args[i] << "'" << std::endl;
  }
}

// make a directory by c++ 17
void Shell::mkdir() {
  print_reset();
  for (int i = 1; i < args.size(); i++) {
    if (!std::filesystem::create_directory(args[i]))
      std::cout << "mkdir: cannot create '" << args[i] << "'" << std::endl;
  }
}

// show the current directory
void Shell::pwd() {
  print_reset();
  std::cout << std::filesystem::current_path().string() << std::endl;
}

// change the current directory
void Shell::cd() {
  print_reset();
  // if redirect flag is set, redirect the output to the file
  // if (re
  if (args.size() == 1) {
    std::cout << "cd dir" << std::endl;
    return;
  }
  try {
    std::filesystem::current_path(args[1]);
  } catch (std::filesystem::filesystem_error &e) {
    std::cout << "cd: cannot change directory to '" << args[1] << "'"
              << std::endl;
  }
}
// ls - list the files in the current directory
void Shell::ls() {
  print_reset();
  // ls
  if (args.size() == 1) {
    for (auto &p : std::filesystem::directory_iterator(".")) {
      std::cout << p.path().filename().string() << endl;
    }
  }
  // ls -l

  // ls -a
  else if (args.size() == 2 && args[1] == "-a") {
    for (auto &p : std::filesystem::directory_iterator(".")) {
      std::cout << p.path().filename().string() << std::endl;
    }
  }
  // ls dir
  else if (args.size() == 2) {
    try {
      for (auto &p : std::filesystem::directory_iterator(args[1])) {
        std::cout << p.path().filename().string() << std::endl;
      }
    } catch (std::filesystem::filesystem_error &e) {
      std::cout << "ls: invalid option" << std::endl;
    }
  }
}

// wc - count the lines, words and characters in a file
void Shell::wc() {
  print_reset();
  // wc no args
  if (pipe_stream.str().size() != 0) {
    std::string line;
    int lines = 0;
    int words = 0;
    int chars = 0;
    while (std::getline(pipe_stream, line)) {
      lines++;
      int word = std::count(line.begin(), line.end(), ' ');
      // single word
      if (word == 0 && line.size() != 0) {
        word++;
      }
      words += word;
      chars += line.size();
    }
    std::cout << "lines : " << lines << endl
              << "words : " << words << endl
              << "chars : " << chars << std::endl;

    return;
  } // pipe mode
  else if (args.size() == 1) {
    std::cout << "wc: no input" << std::endl;
    return;
  } else { // file mode
    std::ifstream in(args[1]);
    if (!in) {
      std::cout << "wc: cannot open '" << args[1] << "'" << std::endl;
      return;
    }
    int lines = 0;
    int words = 0;
    int chars = 0;
    std::string line;
    while (std::getline(in, line)) {
      lines++;
      int word = std::count(line.begin(), line.end(), ' ');
      // single word
      if (word == 0 && line.size() != 0) {
        word++;
      }
      words += word;
      chars += line.size();
    }
    std::cout << "lines : " << lines << endl
              << "words : " << words << endl
              << "chars : " << chars << std::endl;
  }
}

// cat - concatenate files and print on the standard output
void Shell::cat() {
  print_reset();
  // -n
  if (args.size() == 3 && args[1] == "-n") {
    for (int i = 2; i < args.size(); i++) {
      std::ifstream in(args[i]);
      if (!in) {
        std::cout << "cat: cannot open '" << args[i] << "'" << std::endl;
        return;
      }
      cout << args[i] << ":" << endl;
      std::string line;
      int line_num = 1;
      while (std::getline(in, line)) {
        std::cout << line_num << " " << line << std::endl;
        line_num++;
      }
    }
  } else {
    for (int i = 1; i < args.size(); i++) {
      std::ifstream in(args[i]);
      if (!in) {
        std::cout << "cat: cannot open '" << args[i] << "'" << std::endl;
        return;
      }
      cout << args[i] << ":" << endl;
      std::string line;
      while (std::getline(in, line)) {
        std::cout << line << std::endl;
      }
    }
  }
}
// copy a file
void Shell::cp() {
  print_reset();
  if (args.size() == 1) {
    std::cout << "cp src dest" << std::endl;
    return;
  }
  if (args.size() == 2) {
    std::cout << "cp src dest" << std::endl;
    return;
  }
  std::ifstream in(args[1]);
  if (!in) {
    std::cout << "cp: cannot open '" << args[1] << "'" << std::endl;
    return;
  }
  std::ofstream out(args[2]);
  if (!out) {
    std::cout << "cp: cannot create '" << args[2] << "'" << std::endl;
    return;
  }
  std::string line;
  while (std::getline(in, line)) {
    out << line << std::endl;
  }
}
// move a file
void Shell::mv() {
  print_reset();
  if (args.size() == 1) {
    std::cout << "mv src dest" << std::endl;
    return;
  }
  if (args.size() == 2) {
    std::cout << "mv src dest" << std::endl;
    return;
  }
  std::ifstream in(args[1]);
  if (!in) {
    std::cout << "mv: cannot open '" << args[1] << "'" << std::endl;
    return;
  }
  std::ofstream out(args[2]);
  if (!out) {
    std::cout << "mv: cannot create '" << args[2] << "'" << std::endl;
    return;
  }
  std::string line;
  while (std::getline(in, line)) {
    out << line << std::endl;
  }
  std::filesystem::remove(args[1]);
}
// rename a file
void Shell::rename() {
  print_reset();
  if (args.size() == 1) {
    std::cout << "rename src dest" << std::endl;
    return;
  }
  if (args.size() == 2) {
    std::cout << "rename src dest" << std::endl;
    return;
  }
  std::ifstream in(args[1]);
  if (!in) {
    std::cout << "rename: cannot open '" << args[1] << "'" << std::endl;
    return;
  }
  std::ofstream out(args[2]);
  if (!out) {
    std::cout << "rename: cannot create '" << args[2] << "'" << std::endl;
    return;
  }
  std::string line;
  while (std::getline(in, line)) {
    out << line << std::endl;
  }
  std::filesystem::rename(args[1], args[2]);
}
// touch - create an empty file
void Shell::touch() {
  print_reset();
  if (args.size() == 1) {
    std::cout << "touch file" << std::endl;
    return;
  }
  std::ofstream out(args[1]);
  if (!out) {
    std::cout << "touch: cannot create '" << args[1] << "'" << std::endl;
    return;
  }
}
