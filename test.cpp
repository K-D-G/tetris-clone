#include <iostream>

int main(){

  int count=0;
  while(true){
    count++;
    if(count==2){
      continue;
    }
    if(count==10){
      break;
    }
    std::cout<<count<<std::endl;
  }
}
