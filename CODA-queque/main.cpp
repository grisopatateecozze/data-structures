#include <iostream>
#include "pncoda.h"
#include "codavt.h"
using namespace std;

int main()
{
  
 
 
cout<<"\n\n\n\n\n";
  codavt<int> a;
  a.encoda(1);
  a.encoda(3);
  a.encoda(7);
  a.encoda(8);
  
  a.encoda(6);
  
  a.print();

  std::cout<<"\n\n";

  pncoda<int> ab;
  ab.encoda(1);
  ab.encoda(3);
  ab.encoda(7);
  ab.encoda(8);
  
  ab.encoda(6);
  
  ab.print();

 





  

	return 0;
}