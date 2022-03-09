#include <iostream>
#include "stack.h"
#include "vettstack.h"
#include "linkedstack.h"

int main(){

linkedstack<int> kri;
kri.push(5);
kri.push(6);
kri.push(8);

std::cout<<"l'elemento rimosso e----->"<<kri.pop()<<"\n";

kri.print();
   
  return 0;
}



