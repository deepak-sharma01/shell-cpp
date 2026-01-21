#include <iostream>
#include <string>

int main() 
{  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage
  
  std::cout << "$ ";

  
  
  std::string input;
  while(std::getline(std::cin,input))
    if(input == "exit"){
      return 0;
    }
   else if(input.rfind("echo ",0)==0) {    
    std:: cout<<input.substr(5)<<std::endl;
    std::cout<<"$ ";
   }
   else{
    std::cout << input << ": command not found" << std::endl;
    std::cout<<"$ ";
   }
  
  }