#include <iostream>
#include <string>



int main() 
{  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;




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
  }
   
  
   else if(input.rfind("type ",0)==0){
    bool found = false;
    for(auto v :l){
      
      if(input.substr(5)==v){
        std::cout<<v<< " is a shell builtin\n";
        found = true;
      break;
    }
  }
    if(!found){
      std::cout<<input.substr(5)<<" : not found\n";
     }
   }    
   
  else{
    std::cout << input << ": command not found" << std::endl;
    std::cout<<"$ ";
  }
}
}
