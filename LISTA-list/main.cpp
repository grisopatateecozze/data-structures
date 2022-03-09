#include <iostream>
#include "linkedlist.h"


int main()
{
  linkedlist<int> kri;

  kri.insert(0, kri.begin());
  
  int i=1;
   while(i<11){
     kri.push_back(i);
     i++;
   }
  
  cout<<(kri);

  int gi = 0;

  
	return 0;
}
