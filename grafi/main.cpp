#include <iostream>
#include <string>
//#include "matgraph.h"
#include "listgraph.h"
using namespace std;
int main()
{
	listgraph<string, int> gl(5);
	//nodi grafo
	listgraph<string, int>::node n0(0), n1(1), n2(2), n3(3);
	gl.insNode(n0);
	gl.writeLabel(n0, "n0");
	gl.insNode(n1);
	gl.writeLabel(n1, "n1");
	gl.insNode(n2);
	gl.writeLabel(n2, "n2");
	gl.insNode(n3);
	gl.writeLabel(n3, "n3");

  //INSERISCE ARCHI
	gl.insArch(n2, n0, 50);
	gl.insArch(n0, n3, 20);
	gl.insArch(n3, n1, 0);
  gl.insArch(n1, n2, 10);
	//gl.insArch(n0, n2, 0);

  //gl.eraseArch(n3, n0);
  //gl.eraseNode(n3);
	cout << "\nlista nodi: "
		 << "\n";
	auto l2 = gl.listNode();
	for (auto i = l2.begin(); !l2.end(i); i = l2.next(i))
	{
		cout << "\nnode: " << gl.readLabel((l2.read(i)));
	}
	cout << "\nnum nodi: " << gl.numNodes() << "\nnum archi: " << gl.numArches();


  //auto a=gl.listNode();
  //cout<<"\n\nprova---->"<<a.begin();
  //cout<<"\n\nprova---->"<<a.next(a.begin());
  cout<<"\n\n";
  gl.dfs(n3);


	gl.~listgraph();
	//=============================================================================================================//
	// matgraph<string, int> g(4);				 //grafo con etichette di tipo stringa e peso di tipo intero
	// nodeGraph n0(1000), n1(1), n2(2), n3(3); //inizializzo gli id dei nodi
	// //inserisco i nodi
	// g.insNode(n0);
	// g.writeLabel(n0, "a");
	// g.insNode(n1);
	// g.writeLabel(n1, "b");
	// g.insNode(n2);
	// g.writeLabel(n2, "c");
	// g.insNode(n3);
	// g.writeLabel(n3, "d");
	// //inserisco gli archi
	// g.insArch(n0, n1, 10);
	// g.insArch(n0, n2, 20);
	// g.insArch(n0, n3, 22);
	// g.insArch(n1, n0, 23);
	// g.insArch(n1, n2, 33);
	// g.insArch(n2, n0, 49);
	// g.insArch(n2, n1, 44);
	// g.insArch(n2, n3, 39);
	// g.insArch(n3, n0, 45);
	// g.insArch(n3, n2, 46);

	// g.adjacencyMatrix();
	// g.dfs(n3);

	// g.~matgraph();
	cout << "\n";
	return 0;
}