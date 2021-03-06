/* the file define some advanced functions for the shell
 * redirect - redirect the output of a command to a file
 * background - run a command in the background
 */
#include "shell.h"
#include "tools.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>
#include <unistd.h>

using namespace std;

// redirects stdout to a file
void Shell::redirect() {
  string his = input;
  // split by >
  vector<string> arg = split(input, '>');

  if (arg.size() == 2) {
    // delete space in the end
    delete_all_space(arg[1]);
    // redirect to file
    streambuf *buf = cout.rdbuf();
    ofstream out(arg[1]);
    cout.rdbuf(out.rdbuf());
    // run command
    input = arg[0];
    run_once();
    // add to history
    add_history(his);
    // refresh stdout stream
    cout.flush();
    // reset cout
    cout.rdbuf(buf);
  } else {
    cout << "Error: need 2 args" << endl;
  }
}
// run command in background
void Shell::background() {
  // split by &
  string his = input;
  vector<string> arg = split(input, '&');
  // run command in background
  pid_t pid = fork();
  if (pid == 0) {
    // run command
    input = arg[0];
    run_once();
    // add to history
    add_history(his);
    // get the pid of the child process
    int child_pid = getpid();
    cout << "run in background pid:" << child_pid << endl;
    std::exit(0);
  }
}
// run command with pipe
void Shell::pipe() {
  // split by |
  string his = input;
  // redirect to pipe
  streambuf *buf = cout.rdbuf();
  cout.rdbuf(pipe_stream.rdbuf());
  // add_history
  add_history(input);

  vector<string> arg = split(input, '|');
  // run command with pipe
  for (int i = 0; i < arg.size() - 1; i++) {
    // delete space in the end
    string cmd = arg[i];
    // refresh stream
    // clear only reset state
    // pipe_stream.clear();
    // pipe_stream.str("");
    // redirect stdout to string stream
    // run command
    input = cmd;
    run_once();
    cout.flush();
  }

  // delete space in the end
  string cmd = arg[arg.size() - 1];
  // redirect to stdout
  cout.rdbuf(buf);
  // run command
  input = cmd;
  run_once();
  cout.flush();
  //  reset pipe_stream
  //???????????????????????????wc ?????????????????????
  pipe_stream.clear();
  pipe_stream.str("");
}
