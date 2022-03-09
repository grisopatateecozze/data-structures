#include <iostream>
#include "treelink.h"
#include "treelist.h"
using namespace std;

//la nuova funzione della traccia sta in treelist.h


int main()
{
	//albero di interi
	treelist<int> T;
	T.insRoot();

	T.write(T.getRoot(), 1);
	T.insFirstChild(T.getRoot(), 2);
	T.insNextSibiling(T.firstChild(T.getRoot()), 3);
	T.insNextSibiling(T.firstChild(T.getRoot()), 4);
	T.insFirstChild(T.firstChild(T.getRoot()), 4);
  T.insFirstChild(T.nextSibiling(T.firstChild(T.getRoot())), 7);
  T.insFirstChild(T.nextSibiling(T.firstChild(T.getRoot())), 5);
	T.insFirstChild(T.nextSibiling(T.nextSibiling(T.firstChild(T.getRoot()))), 10);
  T.insFirstChild(T.nextSibiling(T.nextSibiling(T.firstChild(T.getRoot()))), 6);
  
	T.print();

  
  

  
  


  


  
	cout << "\n";
	return 0;
}


