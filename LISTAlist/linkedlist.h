#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "linearlist.h"
using namespace std;

//DICHIARAZIONE LINKEDLIST
template <class T>
class linkedlist;

//DICHIARO LA CLASSE NODE
template <class T>
class node
{
	friend class linkedlist<T>;

  public:
    //COSTRUTTORE
	  node()  {
		  next = nullptr;
		  prev = nullptr;
	  }
    //COSTRUTTORE CON ETICHETTA
	  node(T el)  {
		  value = el;
		  next = nullptr;
		  prev = nullptr;
	  }

  private:
	  T value;
	  node<T> *next;
	  node<T> *prev;
};

//CLASSE LISTA______________________________________________________________________
template <class T>
class linkedlist : public linearlist<T, node<T> *>
{
public:
	//DEFINISCE ALIAS value_type E position
	typedef typename linearlist<T, node<T> *>::value_type value_type;
	typedef node<T> *position;
  
	//COSTRUTTORE 
	linkedlist();
	//COSTRUTTORE DI COPIA
	linkedlist(const linkedlist<T> &);
  //&DISTRUTTORE
	~linkedlist();


  //OPERATORI_____linearlist___________________________________
	//IMPOSTA LUNGHEZZA A 0 SE VUOTO
	void create();
	//VERO SE VUOTA
	bool empty() const;
	//LEGGE ELEMENTO IN UNA POSIZIONE ECCETTO SE E' LA TESTA
	value_type read(position) const;
	//SCRIVE UN ELEMENTO IN POSIZIONE P
	void write(value_type, position);
	//RESTITUISCE LA TESTA
	position begin() const;
	//RESTITUISCE L'ULTIMO ELEMENTO
	position last() const;
	//CONTROLLLA SE E' RITORNATO NELLA TESTA
	bool end(position) const;
	//RESTITUISCE SUCCESSIVO
	position next(position) const;
	//RESTITUISCE IL PRECEDENTE
	position previous(position) const;
	//INSERICSE UN NUOVO NODO IN POSIZIONE P
	void insert(value_type, position);
	//SERVE IN DISTRUTTORI, E CANCELLA UN NODO RELATIVO ALLA POSIZIONE
	void erase(position);

  //SOVRACCARICO DI OPERATORI----------------------------------------------
	//SOVRACCARICO OPERATORE ASSEGNAMENTO =
	linkedlist<T> &operator=(const linkedlist<T> &);
	//SOVRACCARICO OPERATORE UGUALIANZA ==
	bool operator==(const linkedlist<T> &) const;
	//SOVRACCARICO OPERATORE DISUGUAGLIANZA !=
	bool operator!=(const linkedlist<T> &) const;


	//FUNZIONI AGGIUNTIVE---------------------------------------------------
	/*metodo che quando la lista è di elementi di tipo intero, sposta, nel modo più efficiente possibile, il massimo in ultima posizione, e il minimo in prima posizione*/
	void move_min_max();
	//metodo che elimina da una lista L1 tutti gli elementi presenti nella lista L2.
	void difference(const linkedlist<T> &);
	
private:
	node<T> *head;
	int lenght;			
};

//COSTRUTTORE______________________________________________________
template <class T>
linkedlist<T>::linkedlist()
{
	this->create();
	head = new node<T>;
	head->next = head;
	head->prev = head;
}

//COSTRUTTORE DI COPIA
template <class T>
linkedlist<T>::linkedlist(const linkedlist<T> &list)
{
	//inizializzo lo stato
	this->create();
	head = new node<T>;
	head->next = head;
	head->prev = head;
	//copio gli elementi del secondo oggetto nel primo
	if (!list.empty())
	{
		position pos2 = list.begin();
		while (!list.end(pos2))
		{
			this->push_back(list.read(pos2));
			pos2 = pos2->next;
		}
	}
}

//DISTRUTTORE
template <class T>
linkedlist<T>::~linkedlist()
{
	//cancello tutti gli elementi nella lista
	while (!this->empty())
	{
		this->erase(begin());
	}
	//se la testa e' diversa da un puntatore nullo la dealloco
	delete head;
	head = nullptr;
}

//OPERATORI_____linearlist______________________________________________

//IMPOSTA LUNGHEZZA A 0 SE VUOTO
template <class T>
void linkedlist<T>::create()
{
	lenght = 0;
}

//VERO SE VUOTA
template <class T>
bool linkedlist<T>::empty() const
{
	return (lenght == 0);
}

//LEGGE ELEMENTO IN UNA POSIZIONE ECCETTO SE E' LA TESTA
template <class T>
typename linkedlist<T>::value_type 
linkedlist<T>::read(position pos) const
{
	value_type value; 
	if (!end(pos) && !empty())
	{
		return (pos->value);
	}
	return (value);
}

//SCRIVE UN ELEMENTO IN POSIZIONE P
template <class T>
void linkedlist<T>::write(value_type el, position pos)
{
	if (!end(pos))
	{
		pos->value = el;
	}
}

//RESTITUISCE LA TESTA
template <class T>
typename linkedlist<T>::position 
linkedlist<T>::begin() const
{
	return (head->next);
}

//RESTITUISCE L'ULTIMO ELEMENTO
template <class T>
typename linkedlist<T>::position 
linkedlist<T>::last() const
{
	return (head->prev);
}

//CONTROLLLA SE E' RITORNATO NELLA TESTA
template <class T>
bool linkedlist<T>::end(position pos) const
{
	return (pos == head);
}

//RESTITUISCE SUCCESSIVO
template <class T>
typename linkedlist<T>::position 
linkedlist<T>::next(position pos) const
{
	return (pos->next);
}

//RESTITUISCE IL PRECEDENTE
template <class T>
typename linkedlist<T>::position 
linkedlist<T>::previous(position pos) const
{
	if (!end(pos))
	{
		return (pos->prev);
	}
	else
	{
		return (pos);
	}
}

//INSERICSE UN NUOVO NODO IN POSIZIONE P
template <class T>
void linkedlist<T>::insert(value_type el, position pos)
{
	//creo un nuovo nodo
	position newnode = new node<T>(el);
	//innesto il nuovo nodo nella posizion p
	newnode->next = pos;
	newnode->prev = pos->prev;
	//sposto i puntatori per sistemare la lista
	pos->prev->next = newnode;
	pos->prev = newnode;
	//incremento la lunghezza
	lenght++;
}

//SERVE IN DISTRUTTORI, E CANCELLA UN NODO RELATIVO ALLA POSIZIONE
template <class T>
void linkedlist<T>::erase(position pos)
{
	if (!empty() && !end(pos))
	{
		pos->prev->next = pos->next;
		pos->next->prev = pos->prev;
		//elimino il nodo
		delete pos;
		pos = nullptr;
		//decremento la lunghezza
		lenght--;
	}
}

//SOVRACCARICO DI OPERATORI----------------------------------------------
//SOVRACCARICO OPERATORE ASSEGNAMENTO =
template <class T>
linkedlist<T> &linkedlist<T>::operator=(const linkedlist<T> &list)
{
	if (!(*this == list))
	{
		//ELIMINO LA LISTA this DOVE ANDRA COPIATA LA NUOVA LISTA
		while (!this->empty())
		{
			this->erase(begin());
		}
		delete head;
		head = nullptr;
		lenght = 0;
    
		//COPIO NELLA LISTA this LA LISTA INDICATA
		this->create();
		head = new node<T>;
		head->next = head;
		head->prev = head;
		if (!list.empty())
		{
			position pos2 = list.begin();
			while (!list.end(pos2))
			{
				this->push_back(list.read(pos2));
				pos2 = pos2->next;
			}
		}
	}
	return *(this);
}

//SOVRACCARICO OPERATORE UGUALIANZA ==
template <class T>
bool linkedlist<T>::operator==(const linkedlist<T> &list) const
{
	if (this->size() != list.size())
	{
		return (false);    //SE LA DIMENSIONE E' DIVERSA
	}
	position pos1 = begin();
	position pos2 = list.begin();
	while (!end(pos1))
	{
		if (!(read(pos1) == read(pos2)))
		{
			return (false);    //SE I NODI CONFRONTATI SONO DIVERSI
		}
		pos1 = next(pos1);
		pos2 = next(pos2);
	}
	return (true);
}


//SOVRACCARICO OPERATORE DISUGUAGLIANZA !=
template <class T>
bool linkedlist<T>::operator!=(const linkedlist<T> &list) const
{
	return (!(*this == list));
}

//FUNZIONI AGGIUNTIVE---------------------------------------------------
	/*metodo che quando la lista è di elementi di tipo intero, sposta, nel modo più efficiente possibile, il massimo in ultima posizione, e il minimo in prima posizione*/
template <>
void linkedlist<int>::move_min_max()
{
	if (!empty())
	{
		//cerco la posizione del minimo
		position minpos = begin();
		for (auto pos = begin(); !end(pos); pos = next(pos))
		{
			if (read(pos) < read(minpos))
			{
				minpos = pos;
			}
		}
		this->exchange(begin(), minpos);
		//cerco la posizione del massimo
		position maxpos = begin();
		for (auto pos = begin(); !end(pos); pos = next(pos))
		{
			if (read(pos) > read(maxpos))
			{
				maxpos = pos;
			}
		}
		this->exchange(last(), maxpos);
	}
}

//metodo che elimina da una lista L1 tutti gli elementi presenti nella lista L2.
template <class T>
void linkedlist<T>::difference(const linkedlist<T> &list)
{
	linkedlist<T> list_difference;
	if (!empty())
	{
		//rimuovo gli elementi in comune con la lista B
		for (auto i = begin(); !end(i); i = next(i))
		{
			if (!list.member(read(i)))
			{
				list_difference.push_back(read(i));
			}
		}
	}
	//assegno alla lista implicita A , la nuova lista differenza
	*this = list_difference;
}

#endif