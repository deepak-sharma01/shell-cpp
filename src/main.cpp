#include <iostream>
#include <string>
#include<cstdlib>
#include<sstream>
#include<vector>
#include<unistd.h>
#include<sys/wait.h>
#include<limits.h>
// #include<io.h>

using namespace std;

void pwdbuiltin(){

/*char *getcwd(char *buf, size_t size);
char*buf arguements can have two choice 
first is cwd as buffer to store the path or as nullptr which means 
its tells os "you allocate memory" 
size_t size  this is the size of the buffer 
if we provide a buffer then size = sizeof(cwd)
otherwise put 0 inside it which means os decide for me 

getcwd returns:

✅ Pointer to the path string (same as buf)

❌ NULL on error*/   

  char *cwd = getcwd(nullptr,0);
  if(cwd){
    std::cout<<cwd <<std ::endl;
    free(cwd);
  }
  else{
    perror("getcwd");
  }

}
void cdbuiltin(const vector<string>args){
  const char* home = getenv("HOME");
  if(!home){
    cerr<< "cd: HOME not set"<<endl;
    return;
  }
  string path;
  //cd or cd~
  if(args.size() == 1 || args[1] =="~"){
    path = home;
  }
  else if(args[1].rfind("~/",0)==0){
    path = string(home) +args[1].substr(1);

  }
  //cd normal_path
  else{
    path = args[1];
  }
  if(chdir(path.c_str())!= 0){
    perror(("cd: "+ path).c_str());
    }
    


  }
  vector<string>tokenise( const string& input){
    bool in_single_quote =false;
    bool in_double_quote = false;

    string current;
    vector<string>args;
    for (size_t i = 0; i < input.size(); i++)
    {
      if(input[i] == '\'' && !in_double_quote){
        in_single_quote = !in_single_quote;

      }
// "\" " as " " means there is a string inside in it \" means it escaped the " therefore there is string of 0 length and string is decay to const char* when needed makes first character as pointer char == const char* not true
      else if(input[i] == '"' && !in_single_quote) {
        in_double_quote = !in_double_quote;
      }
      
      
      else if(input[i]==' ' && (!in_single_quote || !in_double_quote)){
        if(!current.empty()){
              args.push_back(current);
              current.clear();
        }
        }
        else{
          current+=input[i];
        }
    }
    if(!current.empty()){
      args.push_back(current);
    }
    return args;
    
  }



int main() 
{ 

 
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;


char* path = getenv("PATH");

  // TODO: Uncomment the code below to pass the first stage

std::string l[4] ={"type","echo","exit","pwd"};

std::cout << "$ ";

std::string input;
  
while(std::getline(std::cin,input)){
       
  
  if(input == "exit"){
                  return 0;
                }
else if(input.rfind("echo ",0)== 0){
    string cmd = input.substr(5);
 vector<string>args = tokenise(cmd);
  for(const auto& s:args ){
    cout<<s<<" ";
    }
    cout<<endl<<"$ ";
}

   else if(input.rfind("echo ",0)==0) {    
    std:: cout<<input.substr(5)<<std::endl;
    std::cout<<"$ ";
  }
else if(input.rfind("pwd",0)==0){
      char *cwd = getcwd(nullptr,0);
  if(cwd){
    std::cout<<cwd <<std ::endl;
    free(cwd);
  }
  else{
    perror("getcwd");
  }

    std::cout<<"$ ";
  }
 else if(input.rfind("cd",0)==0){
    
    vector<string> args;
std::stringstream ss(input);
string token;
while(ss >> token ){
  args.push_back(token);
}
    cdbuiltin(args);
    
 }  
  
   else if(input.rfind("type ",0)==0){
    bool found = false;
   std:: string cmd = input.substr(5);
    
    for(auto v :l){
      
      if(cmd==v){
        std::cout<<v<< " is a shell builtin\n";
        found = true;
      break;
    }
  }
  if (!found){
    if(path){
      
      
    std::stringstream ss(path);
    std::string dir;

    // vector<string> exts = {".exe",".bat",".cmd",".com",""};


    while(std::getline(ss,dir,':')){
      // for(auto& ext : exts){
        //  std::string full = dir + "\\"+ cmd + ext ;
        std::string full = dir + "/"+cmd;
      if(access(full.c_str(),X_OK) == 0){
        std::cout<<cmd<<" is "<<full<<endl;
        found = true;
        break;
      // }
      }
      if(found) break;
    }
    }
  
    if(!found){
     std:: cout<< cmd << ": not found\n";
    }
   
  }
    
    
 
   std::cout<<"$ "; 
    } 
  else {
    pid_t pid = fork();
   
    std::vector<std::string> args = tokenise(input);
  
  
      if(args.empty()) return 0;
      
      if(pid == 0){
      //child process

      //convert vector<string> -> char*[]
      std::vector<char*> argv;
      for(const auto& s : args){
        argv.push_back(const_cast<char*>(s.c_str()));
      }
      argv.push_back(nullptr);

      execvp(argv[0],argv.data());
      //if execvp fails
      // perror("execvp");
      std:cerr<<input<<": command not found"<<std::endl;
      exit(1);
    
    }
    else if(pid > 0){
      //parent process
      wait(nullptr);
      std::cout<<"$ ";
    }
    else{
     std::cout << input << ": command not found" << std::endl;
    std::cout<<"$ ";
    
  }
}
  
    
 

}
}