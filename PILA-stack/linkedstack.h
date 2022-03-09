#ifndef PNSTACK_H
#define PNSTACK_H

#include <iostream>
#include "stack.h"
using namespace std;

//dichiaro la classe linkedstack
template <class T>
class linkedstack;

//CLASSE NODO PILA_______________________________________________________
template <class T>
class stacknode
{
	friend class linkedstack<T>;

public:
//COSTRUTTORI
	stacknode()
	{
		prev = nullptr;
	}
	stacknode(T el)
	{
		item = el;
		prev = nullptr;
	}

private:
	stacknode<T> *prev;
	T item;
};

template <class T>
class linkedstack : public stack<T> {
public:
	//definisco un alias per il tipo generico tipovalore e il tipo stacknode
	typedef typename stack<T>::value_type value_type;
	typedef stacknode<T> *node;
  
  //COSTRUTTORE________________________________________________________
	linkedstack();
	//DISTRUTTORE
	~linkedstack(); 

  //OPERATORI___________________________________________________________
	//metodo che inizializza l'oggetto pila
	void create();
	//metodo che restituisce vero se la pila e' vuota
	bool empty() const;
	//metodo che restituisce il valore in cima alla pila
	value_type top() const;
	//metodo che restituisce e rimuove l'elemento in cima alla pila
	value_type pop();
	//metodo che inserisce un valore in testa alla pila
	void push(value_type);
	//inserisce un elemento in cima alla pila senza duplicarlo in base al flag del secondo parametro
	void push(value_type, bool);
	//funzione di servizio che stampa tutti gli elementi contenuti nella pila
	void print();
	//funzione di servizio che verifica se un elemento e' già presente nella pila
	bool contains(value_type) const;

private:
	stacknode<T> *head;
};

//IMPLEMENTAZIONI____________________________________________

//COSTRUTTORE________________________________________________
template <class T>
linkedstack<T>::linkedstack()
{
	this->create();
}

//DISTRUTTORE
template <class T>
linkedstack<T>::~linkedstack()
{
	while (!this->empty())
	{
		this->pop();
	}
	delete head;
	head = nullptr;
}

//OPERATORI___________________________________________________________
//metodo che inizializza l'oggetto pila
template <class T>
void linkedstack<T>::create()
{
	head = nullptr;
}

//metodo che restituisce vero se la pila e' vuota
template <class T>
bool linkedstack<T>::empty() const
{
	return (head == nullptr);
}

//metodo che restituisce il valore in cima alla pila
template <class T>
typename linkedstack<T>::value_type linkedstack<T>::top() const
{
	if (!this->empty())
	{
		return (head->item);
	}
	return 0;
}

//metodo che restituisce e rimuove l'elemento in cima alla pila
template <class T>
typename linkedstack<T>::value_type linkedstack<T>::pop()
{
	if (!this->empty())
	{
    node n;
    n=head;
    head=head->prev;
    return (n->item);
	}
	return 0;
}

//metodo che inserisce un valore in testa alla pila
template <class T>
void linkedstack<T>::push(value_type el)
{
	stacknode<T> *newHead = new stacknode<T>(el);
	newHead->prev = head;
	head = newHead;
}

//funzione di servizio che stampa tutti gli elementi contenuti nella pila
template <class T>
void linkedstack<T>::print()
{
	if (!this->empty())
	{
		node i = head;
		while (i != nullptr)
		{
			cout << " " << i->item << " ";
			i = i->prev;
		}
	}
}

//funzione di servizio che verifica se un elemento e' già presente nella pila
template <class T>
bool linkedstack<T>::contains(value_type el) const
{
	bool found = false;
	if (!this->empty())
	{
		node i = head;
		while ((i != nullptr) && !found)
		{
			if (i->item == el)
			{
				found = true;
			}
			i = i->prev;
		}
	}
	return (found);
}

//metodo che inserisce un valore in testa alla pila
template <class T>
void linkedstack<T>::push(value_type el, bool flag)
{
	//inserisco un elemento ammettendo ripetizioni di quest'ultimo
	if (!flag)
	{
		push(el);
	}
	//inserisco un elemento senza ripetizioni
	else
	{
		if (!contains(el))
		{
			push(el);
		}
	}
}

#endif
