/*
 * the file defines the class of the data structure of the shell
*/
#ifndef SHELL_H
#define SHELL_H
#include <functional>
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
using namespace std;

#define Green "\033[0;32m"
#define Red "\033[0;31m"
#define Blue "\033[0;34m"
#define Yellow "\033[0;33m"
#define White "\033[ 0;37m"

class Shell {
 private:
  // store config variables
  map<string,string> configmap;
  string wlcolor = Yellow;
  string wltext = "";
  string byecolor;
  string bye = "";
  string prompt_text = ">>";
  string prompt_color = White;
  string command_color = Blue;
  string exec_color = White;
  string input = "";
  // history file name
  string history_file;

  vector<string> args;
  // pipe string stream
  stringstream pipe_stream;
  // map of commands
  // key: command name void (*func)(void);
  // value: function pointer
  typedef function<void(void)> Callback;
  map<string, Callback> commands;

 public:
  // constructor
  Shell();
  // destructor
  ~Shell(){};
  //shell function
  void run();
  void run_once();
  void init();
  void history();
  void add_history(string);
  void print_prompt();
  void print_reset();
  //command functions
  void clear();
  void welcome();
  void help();
  void exit();
  void echo();
  void parse();
  // file command
  void cat();
  void wc();
  void ls();
  void cd();
  void pwd();
  void mkdir();
  void rm();
  //set function
  void readconfig();
  // redirect
  void redirect();
  // background
  void background();
  // pipe 
  void pipe();
};
#endif
