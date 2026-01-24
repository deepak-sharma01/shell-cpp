#include <iostream>
#include <string>
#include<cstdlib>
#include<sstream>
#include<vector>
#include<unistd.h>
#include<sys/wait.h>
#include<io.h>
using namespace std;

int main() 
{ 

 
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;


char* path = getenv("PATH");

  // TODO: Uncomment the code below to pass the first stage

std::string l[3] ={"type","echo","exit"};

std::cout << "$ ";

std::string input;
  
while(std::getline(std::cin,input)){
       
  
  if(input == "exit"){
                  return 0;
                }


   else if(input.rfind("echo ",0)==0) {    
    std:: cout<<input.substr(5)<<std::endl;
    std::cout<<"$ ";
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
    if(pid == 0){
      std::stringstream ss(input);
      std::string word;
      std::vector<std::string>args;
      while(ss>>word){
        args.push_back(word);
      
      std::vector<char*> argv;
      for(const auto& s : args){
        argv.push_back(const_cast<char*>(s.c_str()));
      }
      argv.push_back(nullptr);

      execvp(argv[0],argv.data());
      //if execvp fails
      perror("execvp");
      exit(1);
    
    }}
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