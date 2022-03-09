#ifndef PNBINTREE_H
#define PNBINTREE_H

#include <iostream>
#include <string>
#include "bintree.h"
using namespace std;

//dichiaro la classe albero binario
template <class I>
class pnbintree;

//CLASSE NODO ALBERO BINARIO
template <class I>
class bintreenode
{
	friend class pnbintree<I>;

public:
	bintreenode()
	{
		parent = nullptr;
		sx = nullptr;
		dx = nullptr;
		level = 0;
		depth = 0;
	}
	bintreenode(I el)
	{
		parent = nullptr;
		sx = nullptr;
		dx = nullptr;
		item = el;
		level = 0;
		depth = 0;
	}

private:
	bintreenode<I> *parent;   //riferimento al nodo genitore
	bintreenode<I> *sx;		    //riferimento al nodo sinistro
	bintreenode<I> *dx;		    //riferimento al nodo destro
	I item;					          //valore associato al nodo
	int level;				        //altezza del nodo(numero di nodi che ci sono sotto n)
	int depth;				        //campo intero relativo alla profondita' del nodo
};

//CLASSE ALBERO BINARIO____________________________________________________
template <class I>
class pnbintree : public bintree<I, bintreenode<I> *>
{
public:
	//definisco gli alias per il tipo generico typeitem e il tipo nodo
	typedef typename bintree<I, bintreenode<I> *>::item item; //tipoelem
	typedef bintreenode<I> *node;							  //tiponodo

  //COSTRUTTORE_______________________________________________________
	pnbintree();
	//COSTRUTTORE DI COPIA
	pnbintree(const pnbintree<I> &);

  //OPERATORI_________________________________________________________
	//INIZIALIZZA LA RADICE
	void create();
	//VERO SE NON CI SONO NODI NELL'ALBERO
	bool empty() const;
	//RIFERIMENTO ALLA RADICE
	node get_root() const;
	//RESTITUISCE RIFERIMENTO AL PADRE
	node parent(node) const;
	//RESTITUISCE RIFERIMENTO AL FIGLIO SINISTRO DEL NODO INDICATO
	node sx(node) const;
	//RESTITUISCE RIFERIMENTO AL FIGLIO DESTRO DEL NODO INDICATO
	node dx(node) const;
	//VERO SE IL FIGLIO SINISTRO E VUOTO
	bool sx_empty(node) const;
	//VERO SE IL FIGLIO DESTRO E VUOTO
	bool dx_empty(node) const;
	//VERO SE IL NODO INDICATO NON HA FIGLI
	bool leaf(node) const;
	//RESTITUISCE IL VALORE DEL NODO INDICATO
	item read(node) const;
	//MODIFICA IL VALORE DEL NODO INDICATO
	void write(node, item);
	//ALLOCA LA RADICE
	void ins_root();
	//INSERISCO UN FIGLIO SINISTRO AL NODO INDICATO
	void ins_sx(node, item);
	//INNESTA UN SOTTOALBERO NEL FIGLIO SINISTRO DEL NODO INDICATO
	void ins_sub_sx(node, pnbintree<I> &);
	//INSERISCO UN FIGLIO DESTRO AL NODO INDICATO
	void ins_dx(node, item);
	//INNESTA UN SOTTOALBERO NEL FIGLIO DESTRO DEL NODO INDICATO
	void ins_sub_dx(node, pnbintree<I> &);
	//CANCELLA IL SOTTOALBERO CHE PARTE DAL NODO INDICATO
	void erase(node);

	//FUNZIONI UTILI________________________________________________________________________
	//metodo che cancella da un albero di interi tutte le foglie con valore pari
	void canc_foglie_pari();
	//metodo che cancella da un sottoalbero di interi tutte le folgie pari
	void canc_foglie_pari(bintreenode<int> *);
	//metodo che restituisce vero se un nodo ha valore nullo
	bool is_empty_node(node) const;
	//&metodo che restituisce la profondita' di un sottoalbero radicato in n
	int depth(node) const;
	//metodo che restituisce la profondita' dell'albero binario
	int depth() const;
	//&metodo che permette di costruire un albero binario avendo come figlio sinisetro l'oggetto this e figlio destro tree
	void costr_bintree(pnbintree<I> &);
	//^metodo che permette di incrementare il livello di tutti i nodi
	void increase_level(node);
	//^metodo che restituisce il livello del nodo a cui si applica
	int get_level(node) const;
	//^metodo che scrive il valore del nodo con un intero l
	void write_level(node, int);
	//^metodo che restituisce un sottoalbero a partire dal nodo a cui si applica
	node get_sub_bintree(node);
	
  /*_________________________________________________________________________________________
 	* Dati due alberi binari A e B, e due nodi u e v, con u appartenente ad A
 	* e v appartenente a B, implementare la funzione mutation che scambia i
 	* sottoalberi con radice u e v.
 	*/
	void mutation(node, node, pnbintree<I> &);


	//ALGORITMI DI VISITA (dfs (depth first search))___________________________________________
	//VISITA IN PRE-ORDER  (NODO PADRE -> FIGLIO SINISTRO -> FIGLIO DESTRO)
	void preorder(node) const;
	//VISITA SIMMETRICA  (FIGLIO SINISTRO -> NODO PADRE -> FIGLIO DESTRO)
	void inorder(node) const;
	//VISITA IN POST-ORDER  (FIGLIO SINISTRO -> FIGLIO DESTRO -> NODO PADRE)
	void postorder(node) const;

	//SOVRACCARICO OPERATORE ASSEGNAMENTO '='__________________________________________________
	pnbintree<I> &operator=(const pnbintree<I> &);
	//DISTRUTTORE
	~pnbintree();

private:
	bintreenode<I> *root;   //RIFERIMENTO ALLA RADICE DELL'ALBERO
};

//COSTRUTTORE_______________________________________________________
template <class I>
pnbintree<I>::pnbintree() {
	this->create();
}

//OPERATORI_________________________________________________________

//INIZIALIZZA LA RADICE
template <class I>
void pnbintree<I>::create() {
	root = nullptr;
}

//COSTRUTTORE DI COPIA
template <class I>
pnbintree<I>::pnbintree(const pnbintree<I> &bintree)  {
	this->create();
	root = get_sub_bintree(bintree.root);
}

//VERO SE NON CI SONO NODI NELL'ALBERO
template <class I>
bool pnbintree<I>::empty() const  {
	return (root == nullptr);
}

//RIFERIMENTO ALLA RADICE
template <class I>
typename pnbintree<I>::node pnbintree<I>::get_root() const  {
	return (root);
}

//RESTITUISCE IL RIFERIMENTO AL PADRE
template <class I>
typename pnbintree<I>::node pnbintree<I>::parent(node n) const  {
	if (n != root)  {
		return (n->parent);
	}
	else  {
		return (n);
	}
}

//RESTITUISCE RIFERIMENTO AL FIGLIO SINISTRO DEL NODO INDICATO
template <class I>
typename pnbintree<I>::node pnbintree<I>::sx(node n) const  {
	return (n->sx);
}

//RESTITUISCE RIFERIMENTO AL FIGLIO DESTRO DEL NODO INDICATO
template <class I>
typename pnbintree<I>::node pnbintree<I>::dx(node n) const  {
	return (n->dx);
}

//VERO SE IL FIGLIO SINISTRO E VUOTO
template <class I>
bool pnbintree<I>::sx_empty(node n) const {
	return (n->sx == nullptr);
}

//VERO SE IL FIGLIO DESTRO E VUOTO
template <class I>
bool pnbintree<I>::dx_empty(node n) const {
	return (n->dx == nullptr);
}

//VERO SE IL NODO INDICATO NON HA FIGLI
template <class I>
bool pnbintree<I>::leaf(node n) const {
	return ((n->sx == nullptr) && (n->dx == nullptr));
}

//RESTITUISCE IL VALORE DEL NODO INDICATO
template <class I>
typename pnbintree<I>::item pnbintree<I>::read(node n) const  {
	item item; //valore vuoto
	if (n != nullptr) {
		return (n->item);
	}
	return (item);
}

//MODIFICA IL VALORE DEL NODO INDICATO
template <class I>
void pnbintree<I>::write(node n, item el) {
	if (n != nullptr) {
		n->item = el;
	}
}

//ALLOCA LA RADICE
template <class I>
void pnbintree<I>::ins_root() {
	if (this->empty())  {
		root = new bintreenode<I>;
	}
}

//INSERISCO UN FIGLIO SINISTRO AL NODO INDICATO
template <class I>
void pnbintree<I>::ins_sx(node parent, item el) {
	if (!empty() && (parent != nullptr))  {
		if (sx_empty(parent)) {
			node child = new bintreenode<I>(el);		//creo il nodo da inserire
			child->level = parent->level + 1;			  //inserisco (nel nuovo figlio) il livello di altezza dell'albero
			//collego il figlio con il padre e viceversa
      child->parent = parent;	            		
			parent->sx = child;                         
		}
		else  {
			parent->sx->item = el;  //cambio solo il valore
		}
	}
}

//INSERISCO UN FIGLIO DESTRO AL NODO INDICATO
template <class I>
void pnbintree<I>::ins_dx(node parent, item el) {
	if (!empty() && (parent != nullptr))  {
		if (dx_empty(parent)) {
			node child = new bintreenode<I>(el);  //creo il nodo da inserire con valore eL
			child->level = parent->level + 1;
			//collego il figlio con il padre e viceversa
			child->parent = parent;
			parent->dx = child; }
		else  {
			parent->dx->item = el;			//il nodo esiste e quindi cambio solo l'item
		}
	}
}

//INNESTA UN SOTTOALBERO NEL FIGLIO SINISTRO DEL NODO INDICATO
template <class I>
void pnbintree<I>::ins_sub_sx(node parent, pnbintree<I> &tree)  {
	if (!empty() && (parent != nullptr))  {
		if (sx_empty(parent)) {
			increase_level(tree.root);  //incremento il livello di tutti i nodi
      parent->sx = tree.root; //IMPOSTO IL FIGLIO SINISTRO (del nodo dove collegare) CON LA ROOT DELL'ALBERO DA COLLEGARE
			tree.root->parent = parent; //IMPOSTO IL PADRE DELLA ROOT DELL'ALBERO DA COLLEGARE
			tree.root = nullptr;
		}
	}
}

//INNESTA UN SOTTOALBERO NEL FIGLIO DESTRO DEL NODO INDICATO
template <class I>
void pnbintree<I>::ins_sub_dx(node parent, pnbintree<I> &tree)  {
	if (!empty() && (parent != nullptr))  {
		if (dx_empty(parent)) {
			increase_level(tree.root);
			parent->dx = tree.root;
			tree.root->parent = parent;
			tree.root = nullptr;
		}
	}
}

//CANCELLA IL SOTTOALBERO CHE PARTE DAL NODO INDICATO
template <class I>
void pnbintree<I>::erase(node n)  {
	//algoritmo che cancella ricorsivamente un sottoalbero radicato in n
	if (n != nullptr && !empty()) {
		if (!sx_empty(n)) {
			erase(n->sx); //CHIAMA RICORSIVAMENTE LA FUNZIONE SUL FIGLIO SINISTRO
		}
		if (!dx_empty(n)) {
			erase(n->dx); //CHIAMA RICORSIVAMENTE LA FUNZIONE SUL FIGLIO DESTRO
		}
		if (leaf(n))  { 
			if (n != root)  {
        //ELIMINA DAL PADRE IL COLLEGAMENTO DEL FIGLIO CHE VOGLIAMO ELIMINARE
				node p = n->parent;
				if (p != nullptr) {
					if (n == p->sx) {
						p->sx = nullptr;
					}
					else  {
						p->dx = nullptr;
					}
				}
			}
			else  {
				root = nullptr;
			}
			delete n;
			n = nullptr;
		}
	}
}


//FUNZIONI UTILI________________________________________________________________________
//metodo che cancella da un albero di interi tutte le foglie con valore pari
template <>
void pnbintree<int>::canc_foglie_pari(bintreenode<int> *subroot)
{
	if (subroot == nullptr)
	{
		return;
	}
	if (!leaf(subroot))
	{
		canc_foglie_pari(subroot->sx);
		canc_foglie_pari(subroot->dx);
	}
	if (leaf(subroot) && (subroot->item % 2 == 0))
	{
		erase(subroot);
	}
}

//metodo che cancella da un sottoalbero di interi tutte le folgie pari
template <>
void pnbintree<int>::canc_foglie_pari()
{
	this->canc_foglie_pari(this->get_root());
}

//metodo che restituisce vero se un nodo ha valore nullo
template <class I>
bool pnbintree<I>::is_empty_node(node n) const
{
	return (n == nullptr);
}

//metodo che restituisce la profondita' dell'albero binario
template <class I>
int pnbintree<I>::depth(node sub_root) const
{
	if (sub_root == nullptr)
	{
		return (-1); //nodo nullo
	}
	int left_depth = depth(sub_root->sx);
	int right_depth = depth(sub_root->dx);
	if (left_depth > right_depth)
	{
		return (left_depth + 1);
	}
	else
	{
		return (right_depth + 1);
	}
}

//metodo che restituisce la profondita' dell'albero binario
template <class I>
int pnbintree<I>::depth() const
{
	return depth(this->get_root());
}

//metodo che permette di incrementare il livello di tutti i nodi
template <class I>
void pnbintree<I>::increase_level(node n)
{
	if (n == nullptr)
	{
		return;
	}
	increase_level(n->sx);
	increase_level(n->dx);
	n->level++;
}

//&metodo che permette di costruire un albero binario avendo come figlio sinistro l'oggetto this e figlio destro tree
template <class I>
void pnbintree<I>::costr_bintree(pnbintree<I> &tree)
{
	node newroot = new bintreenode<I>(item(NULL));
	ins_sub_sx(newroot, *this);
	ins_sub_dx(newroot, tree);
	root = newroot;
}

//^metodo che restituisce il livello del nodo a cui si applica
template <class I>
int pnbintree<I>::get_level(node n) const
{
	int level = 0;
	if (!empty())
	{
		if (n != nullptr)
		{
			level = n->level;
		}
	}
	else
	{
		level = -1; //albero vuoto
	}
	return (level);
}

//^metodo che scrive il valore del nodo con un intero l
template <class I>
void pnbintree<I>::write_level(node n, int l)
{
	if (!empty())
	{
		if (n != nullptr)
		{
			n->level = l;
		}
	}
}

//^metodo che restituisce un sottoalbero a partire dal nodo a cui si applica
template <class I>
typename pnbintree<I>::node pnbintree<I>::get_sub_bintree(node i)
{
	//copia tutti i nodi a partire da i e li mette in temp
	if (i != nullptr)
	{
		node temp = new bintreenode<I>;
		node sx = new bintreenode<I>;
		node dx = new bintreenode<I>;
		temp->item = i->item;
		temp->level = i->level;
		temp->parent = i->parent; //se i era radice, prende nullptr, altrimenti prende il padre
		sx = get_sub_bintree(i->sx);
		temp->sx = sx;
		dx = get_sub_bintree(i->dx);
		temp->dx = dx;
		return (temp);
	}
	else
	{
		return (nullptr);
	}
}

/*___________________________________________________________________________________________
 	* Dati due alberi binari A e B, e due nodi u e v, con u appartenente ad A
 	* e v appartenente a B, implementare la funzione mutation che scambia i
 	* sottoalberi con radice u e v.
*/
template <class I>
void pnbintree<I>::mutation(node u, node v, pnbintree<I> &bintree)
{
	if ((u != root) && (v != root))
	{
		if (u == u->parent->sx)
		{
			u->parent->sx = v;
		}
		else
		{
			u->parent->dx = v;
		}
		if (v == v->parent->sx)
		{
			v->parent->sx = u;
		}
		else
		{
			v->parent->dx = u;
		}
		node parent = u->parent;
		u->parent = v->parent;
		v->parent = u->parent;
	}
}

//ALGORITMI DI VISITA (dfs (depth first search))________________________________________
//VISITA IN PRE-ORDER  (NODO PADRE -> FIGLIO SINISTRO -> FIGLIO DESTRO)
template <class I>
void pnbintree<I>::preorder(node n) const {
	if (n != nullptr) {
		cout << "\nnode: " << read(n) << " level: " << n->level << " depth: " << (n->depth = depth(n)); //preorder
		preorder(n->sx);
		preorder(n->dx);
	}
}

//VISITA SIMMETRICA  (FIGLIO SINISTRO -> NODO PADRE -> FIGLIO DESTRO)
template <class I>
void pnbintree<I>::inorder(node n) const
{
	if (n != nullptr)
	{
		inorder(n->sx);
		cout << " " << read(n) << " "; //inorder
		inorder(n->dx);
	}
}

//VISITA IN POST-ORDER  (FIGLIO SINISTRO -> FIGLIO DESTRO -> NODO PADRE)
template <class I>
void pnbintree<I>::postorder(node n) const
{
	if (n != nullptr)
	{
		postorder(n->sx);
		postorder(n->dx);
		cout << " " << read(n) << " "; //postorder
	}
}

//DISTRUTTORE
template <class I>
pnbintree<I>::~pnbintree()  {
	if (!empty()) {
		//elimino il sotto albero radicato nella radice
		this->erase(root);
	}
	//imposto la radice a nullpointer
	root = nullptr;
}

//SOVRACCARICO OPERATORE ASSEGNAMENTO '='_______________________________________________
template <class I>
pnbintree<I> &pnbintree<I>::operator=(const pnbintree<I> &bintree)  {
	//cancello il vecchio stato
	if (!empty()) {
		this->erase(root);
	}
	root = nullptr;
	//copio il nuovo stato
	root = this->get_sub_bintree(bintree.root);
	return *(this);
}

#endif