#ifndef TREELIST_H
#define TREELIST_H

#include <iostream>
#include "listvector.h"
#include "tree.h"
#define MAXNODES 100
using namespace std;

template <class I>
class treelist : public tree<I, int>
{
public:
  //DEFINIZIONE ALIAS
	typedef typename tree<I, int>::item item; //tipo elemento
	typedef typename tree<I, int>::node node; //tipo nodo

	//COSTRUTTORE
	treelist();
	//INIZIALIZZA IL NODO PADRE E TUTTI I SUI FIGLI
	void create();
  //VERIFICA SE L'ALBERO E' VUOTO, CON IL NUMERO DI NODI
	bool empty() const;
	//INIZIALIZZA LA RADICE
	void insRoot();
	//RESTITUISCE IL RIFERIMENTO (pos nel vettore) ALLA RADICE
	node getRoot() const;
	//RESTITUISCE IL RIFERIMENTO (pos nel vettore) AL PADRE DEL NODO INDICATO
	node parent(node) const;
	//VERO SE IL NODO n E' UNA FOGLIA
	bool leaf(node) const;
	//RESTITUISCE IL RIFERIMENTO (pos nel vettore) AL PRIMO FIGLIO DI n
	node firstChild(node) const;
	//VERO SE IL NODO INDICATO E' L'ULTIMO FRATELLO
	bool lastSibiling(node) const;
	//RESTITUISCE IL RIFERIMENTO (posizione) AL FRATELLO SUCCESSIOVO
	node nextSibiling(node) const;
	//INSERISCE UN NODO COME PRIMO FIGLIO A n, CARICANDO ANCHE IL VALORE
	void insFirstChild(node, item);
	//INSERISCE UN FRATELLO AL NODO INDICATO, CARICANDO ANCHE IL VALORE
	void insNextSibiling(node, item);
	//ELIMINA TUTTI I FIGLI DI 'n' (IN MODO RICORSIVO) ED ELIMINA 'n' NEL VETTORE DEI FIGLI
	void removeSubTree(node);
	//SCRIVE IL VALORE DI UN NODO
	void write(node, item);
  //RITORNA IL VALORE DEL NODO IN POSIZIONE n (TIPO item)
	item read(node) const;
	//DISTRUTTORE
	~treelist();
	//STAMPA TUTTO L'ALBERO
	void print() const;

private:
  //DEFINIZIONE STRUTTURA
	struct Record {
		item el;  
		bool used;  //INDICA SE L'ELEMENTO E' USATO
		listvector<int> childs; //VETTORE DEI FIGLI
	};
  //DEFINIZIONE TIPO POSIZIONE VETTORE FIGLI
	typedef listvector<int>::position position;

  //PRIVATE:
	Record nodes[MAXNODES];   //VETTORE DI RECORD PADRI
	node root;    //NODO RADICE
	int numNodes;   //NUMERO NODI OCCUPATI
};

//COSTRUTTORE
template <class I>
treelist<I>::treelist() {
	this->create();
}

//INIZIALIZZA IL NODO PADRE E TUTTI I SUI FIGLI
template <class I>
void treelist<I>::create()  {
	numNodes = 0;   //IMPOSTA IL NUMERO DI NODI A 0
	for (int i = 0; i < MAXNODES; i++)  {
		nodes[i].used = false;  //IMPOSTA TUTTI I NODI A NON USATO
		nodes[i].childs.create();   //FA LO STESSO A TUTTI I LORO FIGLI
	}
}

//VERIFICA SE L'ALBERO E' VUOTO, CON IL NUMERO DI NODI
template <class I>
bool treelist<I>::empty() const {
	return (numNodes == 0);
}

//INIZIALIZZA LA RADICE
template <class I>
void treelist<I>::insRoot() {
	if (this->empty())  {
		root = 0; //INdICA QUALE POSIZIONE DEL VETTORE E' LA RADICE DELL'ALBERO
		nodes[0].used = true;
		numNodes++;
	}
}

//RESTITUISCE IL RIFERIMENTO ALLA RADICE
template <class I>
typename treelist<I>::node treelist<I>::getRoot() const {
	return (root);
}

//RESTITUISCE IL RIFERIMENTO AL PADRE DEL NODO INDICATO
template <class I>
typename treelist<I>::node treelist<I>::parent(node n) const  {
	position child;
	int p;

	for (int i = 0; i < MAXNODES; i++)  {
		if (!nodes[i].childs.empty()) {   //SE IL FIGLIO NON E' VUOTO FA IL CONTROLLO
			child = nodes[i].childs.begin();    //IN child METTE pos del PRIMO FIGLIO DEL NODO i
			
      bool found = false;
			while (!nodes[i].childs.end(child) && !found) {   //CONTROLLA TUTTI I FIGLI DEL NODO IN POSIZ i
        //il read utilizzato su child è una funzione che restituisce in valore che è presente in quel figlio 
        //(i vettori di figli contengono la loro posiozine come nodi nel vettore 'nodes' )
        if (nodes[i].childs.read(child) == n) { //SE LA POSIZONE DEL FIGLIO DEL NODO i E' UGUALE AL NODO n, IL PADRE E' IN POSIZIONE 'i'
          found = true;
					p = i;
				}
				child = nodes[i].childs.next(child);  //mette la pos del FIGLIO SUCCESSIVO DEL NODO i
			}
			if (found)  { //SE IL PADRE E' STATO TROVATO RITORNA LA POSIZIONE
        return (p);
			}
		}
	}
	return (n); //SE NON E' STATO TROVATO IL PADRE DEL NODO n
}

//VERO SE IL NODO n E' UNA FOGLIA
template <class I>
bool treelist<I>::leaf(node n) const  {
	return (nodes[n].childs.empty());
}

//RESTITUISCE IL RIFERIMENTO AL PRIMO FIGLIO DI n
template <class I>
typename treelist<I>::node treelist<I>::firstChild(node n) const  {
	if (!leaf(n)) { //SE n NON E' UNA FOGLIA
		return (nodes[n].childs.read(nodes[n].childs.begin())); //nel vettore dei figli del nodo 'n' legge il figlio in prima posizione
	}
	return (n); // n E' UNA FOGLIA
}

//VERO SE IL NODO INDICATO E' L'ULTIMO FRATELLO
template <class I>
bool treelist<I>::lastSibiling(node n) const  {
	position c;
	node p = parent(n); //TROVA IL PADRE DI 'n'
	c = nodes[p].childs.begin();  //posizione del primo fratello
	while (!nodes[p].childs.end(c)) {
		c = nodes[p].childs.next(c);  //ciclo che arriva fino all'ultimo fratello
	}
	return (n == nodes[p].childs.read(c));
}

//RESTITUISCE IL RIFERIMENTO (posizione) AL FRATELLO SUCCESSIOVO
template <class I>
typename treelist<I>::node treelist<I>::nextSibiling(node n) const  {
	if (!lastSibiling(n)) {   //se non è l'ultimo fratello
		position c;   //alias listvector(posizione)
		node p = parent(n);   //inserisce posizione padre del nodo 'n'
		c = nodes[p].childs.begin();    //posizione del primo fratello (begin metodo di listvector)
		
    while (!nodes[p].childs.end(c)) {   //finchè non si arriva all'ultimo fratello
			if (nodes[p].childs.read(c) == n) {   //quando arriva al nodo che è uguale al nodo 'n'
				return (nodes[p].childs.read(nodes[p].childs.next(c)));
			}
			c = nodes[p].childs.next(c);
		}
	}
	return (n); //il nodo e' ultimo figlio
}

//INSERISCE UN NODO COME PRIMO FIGLIO A n, CARICANDO ANCHE IL VALORE
template <class I>
void treelist<I>::insFirstChild(node n, item el)  {
	//cerca una posizione libera
	int k = 0;
	while ((k < MAXNODES) && (nodes[k].used == true)) { //il ciclo si blocca quando trova un nodo libero
		k++;
	}
	if (k < MAXNODES) {

    //al nodo trovato assegna il valore, aumenta il numero di nodi e lo incica come usato
		nodes[k].used = true;   
		numNodes++;
		nodes[k].el = el;
		nodes[n].childs.push_front(k);  //inserisce il nodo k al primo posto nel vettore dei figli di n (FUNZIONE DI LINEARLIST)
	}
}

//INSERISCE UN FRATELLO AL NODO INDICATO, CARICANDO ANCHE IL VALORE
template <class I>
void treelist<I>::insNextSibiling(node n, item el)  {
	//CERCA UN NODO LIBERO
	int k = 0;
	while ((k < MAXNODES) && (nodes[k].used == true)) {
		k++;
	}

	if (k < MAXNODES) {
		nodes[k].used = true;
		numNodes++;
		nodes[k].el = el;

		node p = parent(n); //CERCA POSIZONE DEL PADRE DI n
		position child = nodes[p].childs.begin();   //CERCA POSIZONE DEL PRIMO FRATELLO DI n
		
    bool found = false;
		while (!nodes[p].childs.end(child) && !found) {
			if (nodes[p].childs.read(child) == n) {
				found = true;
			}
			child = nodes[p].childs.next(child); //SALVA LA POSIZONE DEL FRATELLO SUCCESSIVO AD n 
		}
		nodes[p].childs.insert(k, child); //INSERISCE NELLA POSIZIONE TROVATA SOPRA IL NUOVO NODO
	}
}

//ELIMINA TUTTI I FIGLI DI 'n' (IN MODO RICORSIVO) ED ELIMINA 'n' NEL VETTORE DEI FIGLI
template <class I>
void treelist<I>::removeSubTree(node n) {
	position c;
	if (!leaf(n)) { //se n non è gia una foglia (quindi non si rimuove niente)
		while (!nodes[n].childs.empty())  { //finche il vettore dei figli non è vuoto 
			removeSubTree(nodes[n].childs.read(nodes[n].childs.begin())); //rimuove il primo figlio, (E TUTTI I SUI FIGLI IN MODO RICORSIVO)
		}
	}

	if (n != root)  { //se n è diverso dalla radice
		node p = parent(n);   //trova il padre di 'n'
		c = nodes[p].childs.begin();    //salva la posizone del rpimo fratello di 'n'
		while (nodes[p].childs.read(c) != n)  {   //finche non si arriva ad n
			c = nodes[p].childs.next(c);  //nel vettore dei fratelli di n, va aventi finche non trova n
		}
		nodes[p].childs.erase(c); //elimina n tra i figli di suo padre
	}
	nodes[n].used = false;
	numNodes--;
}

//SCRIVE IL VALORE DI UN NODO
template <class I>
void treelist<I>::write(node n, item el)  {
	if (nodes[n].used == true)  {
		nodes[n].el = el;
	}
}

//RITORNA IL VALORE DEL NODO IN POSIZIONE n (TIPO item)
template <class I>
typename treelist<I>::item treelist<I>::read(node n) const  {
	item el;
	if (nodes[n].used == true)  { //SE IL NODO E' USATO
		return (nodes[n].el); //IL VALORE DEL NODO
	}
	return (el);
}

//DISTRUTTORE
template <class I>
treelist<I>::~treelist()  {
	if (!this->empty()) {
		this->removeSubTree(root);
	}
	numNodes = 0;
}

//STAMPA TUTTO L'ALBERO
template <class I>
void treelist<I>::print() const {
	cout << "\n{";
	for (int i = 0; i < MAXNODES; i++)  {
		if (nodes[i].used == true)  {
			cout << "\n " << read(i) << ": ";
			if (!leaf(i)) { //SE 'i' NON è UNA FOGLIA STAMPA ANCHE I SUI FIGLI
				position child = nodes[i].childs.begin(); //POSIZONE DEL PRIMO FIGLIO DI 'i'
				//STAMPA TUTTI I FIGLI DI 'i'
        while (!nodes[i].childs.end(child)) {
					cout << read(nodes[i].childs.read(child)) << " ";
					child = nodes[i].childs.next(child);
				}
			}
		}
	}
	cout << "\n}\n";
}


#endif