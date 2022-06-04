## 实验目的

  1. 使用C/C++构造一个简单的Shell

  2. 理解Shell 程序的功能

  3. 学会Shell 程序的使用

  4. 掌握基本的makefile方法

## 实验内容

1. 基本任务1：用C/C＋＋编写一个简单的shell程序，实现以下基本的命令：

   - 浏览目录和文件的各种属性1s（可以不支持参数）
  
   - 回显命令 echo
  
   - 显示文件内容cat
  
   - 创建目录mkdir
  
   - 删除文件rm
  
   - 切换目录cd
  
   - 显示当前目录pwd

   - 文字统计 wc


2. 基本任务2：
 
   每一条命令单独对应一个源程序文件，不允许所有命令一个源文件。

3. 基本任务3：

   写一个 makefile来管理这些源文件。

4. 基本任务4：

   写清楚make编译和运行的过程。
5. 选做任务: Advanced shell 功能，例如：

    - 输入输出重定向，例如．／a．out＞output．dat

    - 支持多管道命令，例如．／a．out｜．／b．out｜．／c．out

    - 支持后台运行命令，例如ls｜wc＆

    - 其它：参考GNU bash提供的功能。

6. 提供友好的人机界面：例如提供命令列表、命令查询、命令帮助等；

7. 任何你想实现的其它命令；

## 实验步骤


#### 设计思路

本项目采用C++进行构建，使用面向对象的设计思想，建立一个Shell 类。

类属性控制全局的行为。如颜色，提示符等；

Shell 命令作为类函数，在不同的文件里实现，再通过make编译。

#### 基础类
```cpp
// 定义在Shell.h 中
class Shell {
 private:
  // store config variables
  map<string, string> configmap;
  // welcome color 
  string wlcolor = Yellow;
  // welcome text 
  string wltext = "";
  // bye color
  string byecolor;
  // bye text
  string bye = "";
  // prompt_text
  string prompt_text = ">>";
  string prompt_color = White;
  string command_color = Blue;
  //cmd result color
  string exec_color = White;
  // input text
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
  // shell function
  void run();
  void run_once();
  void init();
  void history();
  void add_history(string);
  void print_prompt();
  void print_reset();
  // command functions
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
  void cp();
  void mv();
  void touch();
  void rename();
  void grep();
  void exec();

  // set function
  void readconfig();
  // redirect
  void redirect();
  // background
  void background();
  // pipe
  void pipe();
};
```
如上所示，Shell 类主要有几部分组成: 
     
  1. 全局使用的变量，如颜色，提示符，命令映射map等; 
     
     在代码上基本都有相应的注释，这里着重介绍几个属性。

     __input 存放每次输入的文字,所有Shell类里的函数都可以随时读取;__

     __commands 用map将命令与相应的函数对应起来__
     
     __pipe_stream 一个string 流，在管道命令中用来传递数据流__
     
  2. Shell 本身的配置函数，如构造函数，读取配置的函数，析构函数;
  3. 工具函数,如运行一次的函数，打印提示符函数，解析输入函数，清屏函数;
  4. 命令函数，实现Shell命令;
     
     可以看到，实现了所有目标要求的功能
    
#### 运行逻辑
![运行逻辑](https://i.imgur.com/73kIWpn.png)
 
1. 启动程序后,首先构建一个shell类。

   它的构造函数如下,先加载cmd到command map 里。

    然后进行初始化: 读取配置文件，清屏，显示欢迎辞，初始化pipe_stream 和 history_file
```cpp
// main.cc 
int main() {
    Shell shell;
    shell.run();
    return 0;
}
//shell.cc
Shell::Shell() {
  // add commands
  commands["clear"] = bind(&Shell::clear, this);
  commands["echo"] = bind(&Shell::echo, this);
  commands["exit"] = bind(&Shell::exit, this);
  commands["rm"] = bind(&Shell::rm, this);
  commands["pwd"] = bind(&Shell::pwd, this);
  commands["cd"] = bind(&Shell::cd, this);
  commands["mkdir"] = bind(&Shell::mkdir, this);
  commands["ls"] = bind(&Shell::ls, this);
  commands["cat"] = bind(&Shell::cat, this);
  commands["wc"] = bind(&Shell::wc, this);
  commands["help"] = bind(&Shell::help, this);
  commands["history"] = bind(&Shell::history, this);
  commands["cp"] = bind(&Shell::cp, this);
  commands["mv"] = bind(&Shell::mv, this);
  commands["grep"] = bind(&Shell::grep, this);
  commands["exec"] = bind(&Shell::exec, this);
  commands["touch"] = bind(&Shell::touch, this);
  commands["rename"] = bind(&Shell::rename, this);
  // init
  init();
}
// init shell
void Shell::init() {
  // read config file
  readconfig();
  clear();
  welcome();
  // init pipe_stream
  pipe_stream << "";
  // check history file exist
  if (!filesystem::exists(history_file)) {
    // create history file
    ofstream ofs(history_file);
    ofs.close();
  }
}

```
2. 开始运行。

    run 函数的逻辑就是 

    在一个循环中，不断读取输入。对输入字符进行预处理,如去除空格，筛选特殊字符等。

    接着判断输入是否有特殊字符，如果有就执行相应操作，如果没有，就在commands中查找是否存在此命令，来执行相应的命令函数。

```cpp
// shell.cc
// run
void Shell::run() {
  while (true) {
    print_prompt();
    // read command
    getline(cin, input);
    // if input is empty, continue
    if (input == "") {
      continue;
    }
    // & is first than >
    // if & is in the input, background
    if (input.find("&") != string::npos) {
      // cout << "background" << endl;
      background();
      continue;
    }
    // if | is in the input, pipe
    if (input.find("|") != string::npos) {
      // cout << "pipe" << endl;
      pipe();
      continue;
    }
    // if > is in the input, redirect
    if (input.find(">") != string::npos) {
      // cout << "redirect" << endl;
      redirect();
      continue;
    }
    // parse input
    // if command in map , call it
    parse();
    if (commands.find(args[0]) != commands.end()) {
      commands[args[0]]();
      add_history(input);
    } else {
      cout << Red << "Command not found" << endl;
    }
  }
}
```

#### 配置函数
  
  bash,zsh等经典shell可以通过配置文件来对shell的外观，属性等进行自定义。我对这个功能进行了实现。

  readconfig() 函数在构建Shell时读取config.ck文件的配置，可以对提示词，欢迎辞，颜色等内容进行修改
  
  这里逐行读取,其中 # 是注释符号，自动忽略。

  配置文件使用键值对来存放，读取时对空格等特殊情况做了处理。
```cc
//config.ck

# welcome config
WL_TEXT="          welcome to use this shell by RedK"
WL_COLOR="yellow"
#
# prompt config
# prompt content
PROMPT_TEXT="$ "
# prompt color
#
PROMPT_COLOR="blue"
#command color
CMD_COLOR="yellow"

// config.cc
void Shell::readconfig() {
  // open the file
  ifstream config("config.ck");
  string line;
  // int a = 0;
  while (getline(config, line)) {
    // if the line is a comment or empty, ignore it
    // delete spaces
    // cout << "read line:" << a++ << "\b empty:" << line.empty() << endl;
    try {
      // first check if the line is a empty
      if (line.empty() || line[0] == '#') {
        continue;
      }
      // line = delete_first_space(line);
      if (line.find("=") != string::npos) {
        // read key
        string keystr = line.substr(0, line.find("="));
        delete_all_space(keystr);
        string key = keystr.substr(0, line.find("="));
        // read value
        string value = line.substr(line.find_first_of("\"")+1,
				   line.find_last_of("\"")-line.find_first_of("\"")-1);
        configmap[key] = value;
	//cout << "read key:" << key << " value:" << value << endl;
      }
    } catch (...) {
      cout << "Error reading config file" << endl;
    }
  }
  config.close();

  prompt_color = colors[configmap["PROMPT_COLOR"]];
  prompt_text = configmap["PROMPT_TEXT"];
  wlcolor =colors[configmap["WL_COLOR"]];
  wltext = configmap["WL_TEXT"];
  byecolor = colors[configmap["BYE_COLOR"]];
  bye = configmap["BYE"];
  command_color = colors[configmap["CMD_COLOR"]];
  history_file = configmap["HIST_FILE"];
}

```
  

#### 工具函数

  下面介绍一些辅助的工具函数：
  
  ***clear()*** 用来清屏: 
  ```cc
void Shell::clear() { cout << "\033[2J\033[1;1H"; }
  ```
  ***welcome()*** 打印欢迎辞;

  ***print_prompt()*** 打印提示符;

  ***print_reset()*** 清除之前的文字格式;

  ***split()*** 将string按照指定的间隔符分割; 主要用于解析输入的字符串
```cc
template <typename Out>
void split(const std::string &s, char delim, Out result) {
  std::istringstream iss(s);
  std::string item;
  while (std::getline(iss, item, delim)) {
    *result++ = item;
  }
}
std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, std::back_inserter(elems));
  return elems;
}

```
  ***delete_all_space() 与 delete_first_space()*** 用来删除空格

 ***parse()*** 对输入的命令进行处理，先删除首部空格,再通过空格作为分隔符split



#### 普通命令处理

当一个输入没有 & | > 等特殊字符时，当作正常命令来处理。

先进行parse(),清理首部空格将输入的内容***按照空格分割关键词放到args中***

这样args[0] 就是命令名称，后面就是命令的参数；

在commands中查找命令，如果找到就执行对应的处理函数，并把输入加入到history_file。

如果没有找到就提示命令不存在
```cc
 // parse input
 // if command in map , call it
    parse();
    if (commands.find(args[0]) != commands.end()) {
      commands[args[0]]();
      add_history(input);
    } else {
      cout << Red << "Command not found" << endl;
    }

```

#### 重定向和后台命令处理

对于重定向,管道,后台命令的判断顺序是: ***先判断后台执行，再判断管道命令，最后判断重定向***

因为管道和重定向命令都可以后台执行。管道命令的结果也可以重定向输出。

```cc
   if (input.find("&") != string::npos) {
      // cout << "background" << endl;
      background();
      continue;
    }
    // if | is in the input, pipe
    if (input.find("|") != string::npos) {
      // cout << "pipe" << endl;
      pipe();
      continue;
    }
    // if > is in the input, redirect
    if (input.find(">") != string::npos) {
      // cout << "redirect" << endl;
      redirect();
      continue;
    }
```
后台执行命令的处理函数为***background()***
```cc
// advanced.cc
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
```
1. 首先将输入string使用&作为分隔符分离。
2. fork()一个子进程
3. 在子进程使用run_once()执行提取出来的命令。

重定向的处理函数为***redirect()***

```cc
void Shell::redirect() {
   string his = input;
  // split by >
  vector<string> arg = split(input, '>');

  if (arg.size() == 2) {
    // delete space in the end
    delete_all_space(arg[1]);
    // redirect to file
    streambuf* buf = cout.rdbuf();
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
```
1. 将输入的string 按照>分割

2. 判断分割得到arg的大小,如果不是2，报错。

3. 前面的输入命令进行处理，删除空格。

4. 将标准输出重定向到后一个arg,即输入到的文件

5. 运行args[0]命令，将命令添加到history_file

6. flush输出流,重定向回之前的标准输出。

#### 管道命令处理

管道命令的处理函数在pipe()

```cc
// advanced.cc
// run command with pipe
void Shell::pipe() {
  // split by |
  string his = input;
  // redirect to pipe 
  streambuf* buf = cout.rdbuf();
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
    pipe_stream.clear();
    pipe_stream.str("");
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
   // reset pipe_stream
   //不能提前清空，否则wc 的输出会被清空
   pipe_stream.clear();
   pipe_stream.str("");
}
```
此处理函数可以处理多个管道执行。

之前在Shell类中 __名为pipe_stream的stringstream,就是连接各个命令的管道__。

__每个可以使用管道的命令还要有自己对接管道的"水龙头"__,即读取管道里的stringstream 进行处理

1. 重定向标准输出到管道pipe_stream

2. 根据 | 作为分隔符来分割输入，并保存到arg中

3. 执行命令前，先清空管道(这里要clear与str同时使用)。执行命令后，flush cout保证输出都存入管道。
4. 循环执行命令。最后一个命令要单独执行(因为要输出到屏幕)，此时将输出重定向回标准输出。
#### 文件系统命令

Shell中对文件系统的命令有:

**cat查看文件内容** 

```cc
// filecmd.cc
// cat - concatenate files and print on the standard output
void Shell::cat() {
  print_reset();
  if (args.size() == 1) {
    std::cout << "cat file" << std::endl;
    return;
  }
  // cat -n
  if (args.size() == 2 && args[1] == "-n") {
    std::ifstream in(args[2]);
    if (!in) {
      std::cout << "cat: cannot open '" << args[2] << "'" << std::endl;
      return;
    }
    int line = 1;
    std::string line_str;
    while (std::getline(in, line_str)) {
      std::cout << line << " " << line_str << std::endl;
      line++;
    }
  }
  // cat file
  else if (args.size() == 2) {
    std::ifstream in(args[1]);
    if (!in) {
      std::cout << "cat: cannot open '" << args[1] << "'" << std::endl;
      return;
    }
    std::string line;
    while (std::getline(in, line)) {
      std::cout << line << std::endl;
    }
  }
}

```
1. 可以支持参数 -n 来显示行号；

2. 首先对分割后的输入(在parse()中处理)进行解析。

3. 使用文件流打开参数文件,然后逐行读取显示。

**wc统计文件字数** 
```cc
// wc - count the lines, words and characters in a file
void Shell::wc() {
  print_reset();
  // wc no args
  if (pipe_stream.str().size() != 0) {
    cout << pipe_stream.str() << endl;
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

```
**wc支持管道命令** 

1. 首先检测 pipe_stream() 管道里有没有输入(*这也是为什么要每次使用管道后要清理的原因*)

2. 管道里存在输入,进入管道模式。从pipe_stream()流中逐行读取。

3. 有三个变量 lines,words,chars。lines通过读取的行数来判断，words通过空格作为间隔符分割每行来计算,chars通过每行的大小来计算。

4. 如果管道里没有输入，进入普通模式,将文件通过文件流读取。其他操作与上面一样。

**cp复制文件** 

```cc
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
```

简单通过将src文件在输入流中打开，将des文件在输出流中打开。逐行将输入流中的数据输出到输出流中。

**touch创建文件** 
```cc
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
```
通过输出流打开一个文件即可创建。

**rm 删除文件**
```cc
void Shell::rm() {
  print_reset();
  for (int i = 1; i < args.size(); i++) {
    if (std::remove(args[i].c_str()) != 0)
      std::cout << "rm: cannot remove '" << args[i] << "'" << std::endl;
  }
}
```
直接使用标准库里的remove 来删除文件

**mkdir创建一个文件夹**
```cc
// make a directory by c++ 17
void Shell::mkdir() {
  print_reset();
  for (int i = 1; i < args.size(); i++) {
    if (std::filesystem::create_directory(args[i]))
      std::cout << "mkdir: cannot create '" << args[i] << "'" << std::endl;
  }
}
```
直接使用C++17中标准库 create_directory() 进行创建文件夹

**cd切换当前目录**
```cc
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
```
直接使用current_path()来切换当前目录，这里有一个容错处理，如果失败会报错。

**pwd显示当前工作目录**

```cc
// show the current directory
void Shell::pwd() {
  print_reset();
  std::cout << std::filesystem::current_path() << std::endl;
}
```
同样使用标准库里的current_path()函数来显示当前path。
**ls显示当前目录下的文件**
```cc
// ls - list the files in the current directory
void Shell::ls() {
  print_reset();
  // ls
  if (args.size() == 1) {
    for (auto &p : std::filesystem::directory_iterator(".")) {
      std::cout << p.path().filename().string() << std::endl;
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
```
有两种方式: 不加参数是展示当前目录下的所有文件;可以加指定目录;

通过 对当前目录进行遍历,打印出目录下文件的信息。

#### 特殊命令

**echo 打印**

**grep搜索匹配的文本**
```cc
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
```
grep命令可以执行管道,原理和之前的wc一样：将pipe_stream中的内容读出；

这个查找是对每个读出的行进行查找关键词,再打印出来;

**history 打印执行过的历史命令**

```cc
// read history file
void Shell::history() {
  // open history file
  ifstream ifs(history_file);
  // read line by line
  string line;
  while (getline(ifs, line)) {
    // add line to history
    cout << line << endl;
  }
  // close history file
  ifs.close();
}
```
在shell启动时，加载有history_file，每次执行一条命令，都会添加到文件后。
history命令通过逐行读取history_file文件流来打印历史命令

**help 打印帮助文档**

#### Makefile 文件

```makefile
shell:  shell.o print.o tools.o config.o filecmd.o advanced.o toolcmd.o main.o 
	g++  $^ -o shell 
.c.o:
	g++ -c $<
clean:
	rm -f *.o
cleanfile:
	rm .history
```
使用g++ 编译;

需要编译的文件有:
  
    shell.o: shell自身的一些函数,如构造函数,run函数.
    print.o: 和打印相关的函数,如欢迎辞,提示符.
    tools.o: 工具函数,如split(),clear()
    config.o: 配置文件相关的函数,readconfig().
    filecmd.o: 与文件系统有关的命令: 如ls,rm,cat,cd,wc;
    advanced.o: 一些高级指令,管道，重定向等。
    toolcmd.o: 工具命令: grep;
    main.o: 主函数;

提供的两个清理命令，来清理生成的编译文件和历史文件

## 实验结果

此次实验完成了所有实验任务，并且参照bash添加了一些特色功能。
比如查看历史命令
使用配置文件进行shell的配置

下面是一些运行截图

![](https://i.imgur.com/RxT7yxm.jpg)
![](https://i.imgur.com/L5bXEIp.jpg)
![](https://i.imgur.com/MgVLC1c.jpg)
## 用户手册

#### 安装

本程序已经将代码上传至github

可以直接通过git clone 仓库 来进行安装:

```
git clone https://github.com/Chi-Kai/Course
cd Course/linux2022/lab1
make
```
#### 卸载
```
rm -rf lab1
```
#### 其他注意事项请阅读README文档

## 实验总结。

1. stream 的使用。在shell中使用来大量的stream对象来实现重定向，管道等功能。使用stream时，一方面要做好与标准输入输出流的切换，一方面要注意及时清除stream中的数据。

2. 面向对象编程。通过定义一个shell对象，将重定向，管道等公用的处理逻辑作为公共函数,减少代码量。

3. 通过此次实验我巩固了课程所学的知识，加深了对linux系统的理解，同时巩固了各种命令的特性和实现，有利于我以后对linux系统的运用。





