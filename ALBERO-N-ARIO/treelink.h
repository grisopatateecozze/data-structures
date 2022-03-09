#ifndef TREELINK_H
#define TREELINK_H

#include <iostream>
#include "tree.h"
#include "pnqueque.h"
using namespace std;

template <class I>
class treelink;

//CREAZIONE CLASSE NODO DELL'ALBERO
template <class I>
class treenode  {
	friend class treelink<I>;

public:
	treenode()
	{
		first = nullptr;
		next = nullptr;
		parent = nullptr;
		level = 0;
	}
	treenode(I el)
	{
		first = nullptr;
		next = nullptr;
		parent = nullptr;
		item = el;
		level = 0;
	}

private:
	treenode<I> *parent; //NODO GENITORE
	treenode<I> *first;  //PRIMO NODO FIGLIO
	treenode<I> *next;   //
	I item;              //VALORE NODO
	int level;           //PROFONDITA NODO
};

//CREAZIONE CLASSE ALBERO
template <class I>
class treelink : public tree<I, treenode<I> *>
{
public:
	//definisco un alias per i tipi: item e nodo
	typedef typename tree<I, treenode<I> *>::item item;
	typedef treenode<I> *node;
	
  /*===================COSTRUTTORI=========================*/
  //costruttore
	treelink();
  //distruttore
	~treelink();
	
  /*==================OPERATORI============================*/
  //INIZIALIZZA LA RADICE A NULLPTR
	void create();
	//VERO SE LA RADICE E' NULLPTR
	bool empty() const;
	//ALLOCA SPAIO PER LA RADICE E LA INNESTA
	void insRoot();
	//INSERISCI IL PRIMO NODO FIGLIO DEL NODO IN INPUT
	void insFirstChild(node, item);
	//INSERISCI NUOVO FRATELLO DEL NODO IN INPUT
	void insNextSibiling(node, item);
	//RESTITUISCE LA RADICE
	node getRoot() const;
	//RESTITUISCE IL GENITORE DEL NODO INDICATO
	node parent(node) const;
  //VERIFICA SE IL NOD E' UNA FOGLIA
	bool leaf(node) const;
	//RESTITUISCE RIFERIMENTO AL PRIMO FIGLIO DEL NODO INDICATO
	node firstChild(node) const;
	//VERO SE IL NODO INDICATO E' L'ULTIMO FRATELLO
	bool lastSibiling(node) const;
	//RESTITUISCE IL RIFERIMENTO AL SUCCESSIVO FRATELLO
	node nextSibiling(node) const;
	//INNESTA ALBERO INDICATO COME PRIMO FIGLIO DEL NOME INDICATO
	void insFirstSubTree(node, treelink<I> &);
	//INSERISCE UN SOTTOALBERO NEL NEXT DEL NODO INDICATO
	void insSubTree(node, treelink<I> &);
	//RIMUOVE TUTTI I NODI PARTENDO DA QUELLO INDICATO
	void removeSubTree(node);
	//SCRIVE IL VALORE DI UN NODO
	void write(node, item);
  //LEGGE IL VALORE DI UN NODO
	item read(node) const;

	/*==============ALGORITMI DI VISITA===========================*/
	//&visite eseguite in dfs usando quindi la ricerca in profondita'

	//STAMPA DI TIPO PREORDER (stampa in profoniìdita del nodo padre, poi tutti i nodi partendo da sinstra) DEL SOTTOALBERO CON RADICE 'n'
	void preorder(node) const;

  //STAMPA DI TIPO POSTORDER (stampa in profoniìdita tutti i nodi partendo da sinstra, e da sotto e poi il padre) DEL SOTTOALBERO CON RADICE 'n'
	void postorder(node) const;
	//metodo che esegue una visita in ampiezza
	void bfs(node) const;
	
  
	//STAMPA L'ALBERO PARTENDO DAL NODO 'n'
	void print(node) const;
	//STAMPA L'ALBERO PARTENDO DALLA RADICE
	void print() const;

private:
	treenode<I> *root;
};

/*====================COSTRUTTORI==================*/
template <class I>
treelink<I>::treelink() {
	this->create();
}

template <class I>
treelink<I>::~treelink()
{
	if (!empty())
	{
		this->removeSubTree(root);
	}
	delete root;
	root = nullptr;
}

/*==================OPERATORI============================*/

//INIZIALIZZA LA RADICE A NULLPTR
template <class I>
void treelink<I>::create()
{
	root = nullptr;
}

//VERO SE LA RADICE E' NULLPTR
template <class I>
bool treelink<I>::empty() const
{
	return (root == nullptr);
}

//ALLOCA SPAZIO PER LA RADICE E LA INNESTA
template <class I>
void treelink<I>::insRoot()
{
	if (this->empty())
	{
		root = new treenode<I>;
	}
}

//INSERISCI IL PRIMO NODO FIGLIO DEL NODO IN INPUT
template <class I>
void treelink<I>::insFirstChild(node nodeparent, item el)
{
	if (!this->empty())
	{
		node newchild = new treenode<I>(el);     //CREA NUOVO NODO INSERENDOGLI GIA IL VALOR(USA COSTRUTTORE DI CLASSE NODE CON PARAMETRO)
		newchild->level = nodeparent->level + 1; //IMPOSTA LIVELLO NUOVO NODO = A QUELLO DEL PADRE +1
		newchild->parent = nodeparent;           //IMPOSTA COME GENITORE IL NODO PASSATO IN INPUT
		newchild->next = nodeparent->first;      //FRATELLO DEL NUOVO NODO SARA UGUALE AL VECCHIO PRIMO FIGLIO DEL GENITORE IN INPUT
		nodeparent->first = newchild;            //METTE COME PRIMO FIGLIO DEL GENITORE IL NODO CREATO SOPRA
	}
}

//INSERISCI NUOVO FRATELLO DEL NODO IN INPUT
template <class I>
void treelink<I>::insNextSibiling(node nodechild, item el)
{
	if (nodechild != root)
	{
		if (nodechild != nullptr)
		{
			node newsibiling = new treenode<I>(el);   
			newsibiling->level = nodechild->level;
			newsibiling->parent = nodechild->parent;
			newsibiling->next = nodechild->next;    //IMPOSTA COME SUCCESSIVO DEL FRATELLO APPENA AGGIUNTO, IL SUCCESSIVO DEL NODO CHE ERA LI PRIMA
			nodechild->next = newsibiling;        //IL SUCCESSIVO DEL NODO IN INPUT DIVENTA IL FRATELLO APPENA CREATO
		}
	}
}

//RESTITUISCE LA RADICE
template <class I>
typename treelink<I>::node treelink<I>::getRoot() const
{
	return (root);
}

//RESTITUISCE IL GENITORE DEL NODO INDICATO 
template <class I>
typename treelink<I>::node treelink<I>::parent(node n) const
{
	if (n != root)
	{
		return (n->parent);
	}
	else
	{
		return (n);
	}
}

//VERIFICA SE IL NOD E' UNA FOGLIA
template <class I>
bool treelink<I>::leaf(node n) const
{
	return (n->first == nullptr);
}

//RESTITUISCE RIFERIMENTO AL PRIMO FIGLIO DEL NODO INDICATO
template <class I>
typename treelink<I>::node treelink<I>::firstChild(node n) const
{
	if (!leaf(n))
	{
		return (n->first);
	}
	else
	{
		return (n);
	}
}

//VERO SE IL NODO INDICATO E' L'ULTIMO FRATELLO
template <class I>
bool treelink<I>::lastSibiling(node n) const
{
	return (n->next == nullptr);
}

//RESTITUISCE IL RIFERIMENTO AL SUCCESSIVO FRATELLO
template <class I>
typename treelink<I>::node treelink<I>::nextSibiling(node n) const
{
	if (!lastSibiling(n))
	{
		return (n->next);
	}
	else
	{
		return (n);
	}
}

//INNESTA ALBERO INDICATO COME PRIMO FIGLIO DEL NOME INDICATO
template <class I>
void treelink<I>::insFirstSubTree(node nodeparent, treelink<I> &tree)
{
	if (!this->empty() && !tree.empty())
	{
		if (nodeparent != nullptr)  //NODO A CUI INNSESTARE COME PRIMO FIGLIO L'ALBERO INDICATO
		{
			node nodechild;
      nodechild=nodeparent->first;      //ASSEGNA 
			nodeparent->first = tree.root;    //IMPOSTA COME PRIMO FIGLIO LA RADICE DELL'ALBERO DA INNESTARE
			tree.root->parent = nodeparent;   //IMPOSTA IL PADRRE DELLA RADICE DELL'ALBERO DA INNESTARE CON IL NODO PASSATO IN INPUT (NODO A CUI INNESTARE L'ALBERO)
			tree.root->next = nodechild;      //IMPOSTA IL FRATELLO DELLA RADICE COME IL VECCHIO PRIMO FIGLIO
			tree.root = nullptr;
		}
		else
		{
			cout << "\nnodo nullo insFirstSubTree\n";
		}
	}
}

//INSERISCE UN SOTTOALBERO NEL NEXT DEL NODO INDICATO
template <class I>
void treelink<I>::insSubTree(node nodechild, treelink<I> &tree)
{
	if (!this->empty() && !tree.empty() && (nodechild != root))
	{
		if (nodechild != nullptr)
		{
			node nodesibiling = nodechild->next;
      nodechild->next = tree.root;
			tree.root->parent = nodechild->parent;
			tree.root->next = nodesibiling;
			tree.root = nullptr;
		}
	}
}

//RIMUOVE TUTTI I NODI PARTENDO DA QUELLO INDICATO
template <class I>
void treelink<I>::removeSubTree(node n) {
	if (n != nullptr) {
		node i;
    //SE IL NODO PASSATO IN INPUT NON E' UNA FOGLIA
		if (!leaf(n)) {
			for (i = firstChild(n); !lastSibiling(i); i = nextSibiling(i))  {
				removeSubTree(i);
			}
			removeSubTree(i);
		}
    //SE IL NODO PASSATO IN INPUT E' UNA FOGLIA
		if (leaf(n))  {
			if (n != root)  {
				if (n == n->parent->first)  {     //SE n E IL PRIMO TRA I SUOI FRATELLI
					n->parent->first = n->next;     //IMPOSTA COME PRIMO FIGLIO IL NODO SUCCESSIVO DI n
				}
				else  {                           //
					i = n->parent->first;
					while (i->next != n)  {         //QUANDO IL PROSSIMO DI i E' UGUALE A n SI INTERROMPE
						i = i->next;
					}
					i->next = n->next;             //FA PUNTARE IL PROSSIMO DI i AL PROSSIMO DI n (SALTANDO n)
				}
			}
			else  { //SE n E' LA RADICE
				root = nullptr;
			}
			delete n;
			n = nullptr;
		}
	}
}

//SCRIVE IL VALORE DI UN NODO
template <class I>
void treelink<I>::write(node n, item el)  {
	if (n != nullptr)
	{
		n->item = el;
	}
	else
	{
		cout << "\nnodo nullo scrittura\n";
	}
}

//LEGGE IL VALORE DI UN NODO
template <class I>
typename treelink<I>::item treelink<I>::read(node n) const
{
	item item; //elemento vuoto
	if (n != nullptr)
	{
		return (n->item);
	}
	return (item);
}


/*==============ALGORITMI DI VISITA===========================*/

//STAMPA DI TIPO PREORDER (stampa in profoniìdita del nodo padre, poi tutti i nodi partendo da sinstra) DEL SOTTOALBERO CON RADICE 'n'
template <class I>
void treelink<I>::preorder(node n) const  {
	if (n != nullptr)
	{
		node child;
		cout << "\nitem: " << read(n) << " level: " << n->level; //(1) preorder
		if (!leaf(n))
		{
			child = firstChild(n);  //INSERISCE IL PRIMO FIGLIO DEL NODO INDICATO
			
      //STAMPA RICORSIVAMENTE UTILIZZANDO preorder TUTTI I FIGLI DI 'n'
      while (!lastSibiling(child))
			{
				preorder(child);
				child = nextSibiling(child);
			}
			preorder(child);
		}
	}
}

//STAMPA DI TIPO POSTORDER (stampa in profoniìdita tutti i nodi partendo da sinstra, e da sotto e poi il padre) DEL SOTTOALBERO CON RADICE 'n'
template <class I>
void treelink<I>::postorder(node n) const {
	if (n != nullptr)
	{
		node child;
		if (!leaf(n))
		{
			child = firstChild(n);  //INSERISCE IL PRIMO FIGLIO DI 'n'
			while (!lastSibiling(child))
			{
				postorder(child);
				child = nextSibiling(child);
			}
			postorder(child);
		}
		cout << "\nitem: " << read(n); //(2) postorder
	}
}

template <class I>
void treelink<I>::bfs(node n) const
{
	if (n != nullptr)
	{
		pnqueque<node> queque;
		queque.enqueque(n);
		while (!queque.empty())
		{
			node i = queque.top();
			queque.dequeque();
			//esame per livelli del nodo i
			cout << " (" << read(i) << ") ";
			i = i->first;
			while (i != nullptr)
			{
				queque.enqueque(i);
				i = i->next;
			}
		}
	}
}

//STAMPA L'ALBERO PARTENDO DAL NODO 'n'
template <class I>
void treelink<I>::print(node n) const
{
	node p;
	cout << read(n) << ":";
	if (!leaf(n))
	{
		p = firstChild(n);  //INSERISCE IL PRIMO FIGLIO DI 'n'
		//stampa tutti i figli di 'n'
    while (!lastSibiling(p))  {
			cout << " " << read(p); 
			p = nextSibiling(p);
		}
		cout << " " << read(p) << "\n";

    //STAMPA TUTTI I FIGLI DEI FIGLI DI 'n'
		p = firstChild(n);
		while (!lastSibiling(p))  {
			print(p);
			p = nextSibiling(p);
		}
		print(p);
	}
	else
	{
		cout << "\n";
	}
}

//STAMPA L'ALBERO PARTENDO DALLA RADICE
template <class I>
void treelink<I>::print() const
{
	if (!empty())
	{
		this->print(root);
	}
}

#endif