#ifndef LISTVECTOR_H
#define LISTVECTOR_H

#include <iostream>
#include "linearlist.h"
using namespace std;

template <class T>
class listvector : public linearlist<T, int>
{
public:
	//definisco un alias per il tipovalore generico
	typedef typename linearlist<T, int>::value_type value_type;
	//definisco l'indice dell'array come un intero per scorrere il vettore
	typedef typename linearlist<T, int>::position position;

	//COSTRUTTORE
	listvector();
	//COSTRUTTORE CON IN INPUT PARAMETRO PER LA LUNGHEZZA DELL'ARRAY
	listvector(int);
	//COSTRUTTORE DI COPIA
	listvector(const listvector<T> &);
	//DISTRUTTORE
	~listvector();


	/* =================================== OPERATORI =========================================== */
	//IMPOSTA LUNGHEZZA A 0
	void create();
	//VERO SE LA LISTA E' VUOTA
	bool empty() const;
	//LEGGE L'ELEMENTO DELLA LISTA IN POSIZIONE P
	value_type read(position) const;
	//SCRIVE UN ELEMENTO IN POSIZIONE pos PASSATA IN INPUT
	void write(value_type, position);
	//RESTITUISCE LA POSIZIONE INIZIALE
	position begin() const;
	//RESTITUISCE LA POSIZIONE SUCCESSIVA (se si è arrivati alla fine restituisce la posizione passata in input)
	position next(position) const;
	//RESTITUISCE LA POSIZIONE PRECEDENTE (se si è gia arrivati all'inizio restituisce la posizione passata in input)
	position previous(position) const;
	//RESTITUISCE VERO SE LA POS E' L'ULTIMA DELLA LISTA
	bool end(position) const;
	//RESTITUISCE L'ULTIMA POSIZIONE DELLA LISTA
	position last() const;
	//INSERISCE UN ELEMENTO 'v', IN POSIZIONE 'p', SE LA LISTA E PIENA ALLOCARE NUOVO SPAZIO PER IL NUOVO ELEMENTO DA INSERIRE
	void insert(value_type, position);
	//CANCELLA UN ELEMENTO IN POSIZIONE POS
	void erase(position);

	//SOVRACCARICO OPERATORI_________________________________________________________
	//SOVRACCARICO OPERATORE ASSEGNAZIONE =
	listvector<T> &operator=(const listvector<T> &);
	//SOVRACCARICO OPERATORE UGUAGLIANZA ==
	bool operator==(const listvector<T> &) const;

  //FUNZIONI UTILI_________________________________________________________________
  //INSERIMENTO ORDINATO
	void insertion_sort();

private:

	//metodo private che permette di modificare la massima dimensione dell'array
	void changeDimension(value_type *&, int, int);
	value_type *elements; //array di elementi
	int lenght;			  //lunghezza
	int array_dimension;  //capienza massima
};


/***********************IMPLEMENTAZIONE**********************/

//COSTRUTTORE
template <class T>
listvector<T>::listvector()
{
	array_dimension = 10;
	elements = new value_type[array_dimension];
	this->create();
}

//COSTRUTTORE CON IN INPUT PARAMETRO PER LA LUNGHEZZA DELL'ARRAY
template <class T>
listvector<T>::listvector(int N)
{
	array_dimension = N;
	elements = new value_type[array_dimension];
	this->create(); //inizializza la lista
}

//COSTRUTTORE DI COPIA
template <class T>
listvector<T>::listvector(const listvector<T> &list)
{
	this->array_dimension = list.array_dimension;
	this->lenght = list.lenght;
	this->elements = new value_type[array_dimension];
	for (int i = 0; i < list.array_dimension; i++)
	{
		this->elements[i] = list.elements[i];
	}
}

//DISTRUTTORE
template <class T>
listvector<T>::~listvector()
{
	delete[] elements;
	elements = nullptr;
	lenght = 0;
	array_dimension = 0;
}

//OPERATORI_________________________________________________________
//IMPOSTA LUNGHEZZA A 0
template <class T>
void listvector<T>::create()
{
	lenght = 0;
}

//VERO SE LA LISTA E' VUOTA
template <class T>
bool listvector<T>::empty() const
{
	return (lenght == 0);
}

//LEGGE L'ELEMENTO DELLA LISTA IN POSIZIONE P
template <class T>
typename listvector<T>::value_type listvector<T>::read(position pos) const
{
	value_type item;
	if ((pos > 0) && (pos < lenght + 1))
	{
		return (elements[pos - 1]);
	}
	return (item);
}

//SCRIVE UN ELEMENTO IN POSIZIONE pos PASSATA IN INPUT
template <class T>
void listvector<T>::write(value_type el, position pos)
{
	if ((pos > 0) && (pos < lenght + 1))
	{
		elements[pos - 1] = el;
	}
}

//RESTITUISCE LA POSIZIONE INIZIALE
template <class T>
typename listvector<T>::position listvector<T>::begin() const
{
	return (1); 
}

//RESTITUISCE LA POSIZIONE SUCCESSIVA (se si è arrivati alla fine restituisce la posizione passata in input)
template <class T>
typename listvector<T>::position listvector<T>::next(position pos) const
{
	if ((pos > 0) && (pos < lenght + 1))
	{
		return (pos + 1);
	}
	else
	{
		return (pos);
	}
}

//RESTITUISCE LA POSIZIONE PRECEDENTE (se si è gia arrivati all'inizio restituisce la posizione passata in input)
template <class T>
typename listvector<T>::position listvector<T>::previous(position pos) const
{
	if ((pos > 1) && (pos < lenght + 1))
	{
		return (pos - 1);
	}
	else
	{
		return (pos);
	}
}

//RESTITUISCE VERO SE LA POS E' L'ULTIMA DELLA LISTA
template <class T>
bool listvector<T>::end(position pos) const
{
	bool flag = false;
	if ((pos > 0) && (pos <= lenght + 1))
	{
		flag = (pos == lenght + 1);
	}
	return (flag);
}

//RESTITUISCE L'ULTIMA POSIZIONE DELLA LISTA
template <class T>
typename listvector<T>::position listvector<T>::last() const
{
	position pos = begin();
	
	while (!end(next(pos)))
	{
		pos = next(pos);
	}
	return (pos);
}

//INSERISCE UN ELEMENTO 'v', IN POSIZIONE 'p', SE LA LISTA E PIENA ALLOCARE NUOVO SPAZIO PER IL NUOVO ELEMENTO DA INSERIRE
template <class T>
void listvector<T>::insert(value_type el, position pos)
{
	//controllo sel la lista è gia piena
	if (lenght == array_dimension)
	{
		changeDimension(elements, array_dimension, array_dimension * 2);
		array_dimension = array_dimension * 2;
	}
	//verifico se la posizione in cui voglio inserire v, e' una posizione valida
	if ((pos > 0) && (pos <= lenght + 1))
	{
		for (int i = lenght; i >= pos; i--)
		{
			elements[i] = elements[i - 1];
		}
		elements[pos - 1] = el;
		lenght++;
	}
}

//CANCELLA UN ELEMENTO IN POSIZIONE POS
template <class T>
void listvector<T>::erase(position pos)
{
  //ELIMINA META' SPAZIO DELL'ARREY SE NON E' UTILIZZATO (LA DIMENSIONE, NON GLI ELEMENTI)
	if (lenght < array_dimension / 2)
	{
		changeDimension(elements, array_dimension, array_dimension / 2);
		array_dimension = array_dimension / 2;
	}

	if ((pos > 0) && (pos < lenght + 1))
	{
		if (!empty())
		{
			for (int i = pos - 1; i < (lenght - 1); i++)
			{
				elements[i] = elements[i + 1];
			}
			lenght--;
		}
	}
}

//SOVRACCARICO OPERATORI_________________________________________________________

//SOVRACCARICO OPERATORE =
template <class T>
listvector<T> &listvector<T>::operator=(const listvector<T> &list)
{
	if (!(*this == list))
	{ //!attenzione agli autoassegnamenti
		this->array_dimension = list.array_dimension;
		this->lenght = list.lenght;
		delete[] this->elements;
		elements = new value_type[array_dimension];
		for (int i = 0; i < list.array_dimension; i++)
		{
			this->elements[i] = list.elements[i];
		}
	}
	return *(this);
}
//SOVRACCARICO OPERATORE ==
template <class T>
bool listvector<T>::operator==(const listvector<T> &list) const
{
	if (this->size() != list.size())
	{
		return (false);
	}
	else
	{
		position pos1 = begin();
		position pos2 = list.begin();
		while (!end(pos1))
		{
			if (!(read(pos1) == read(pos2)))
			{
				return (false);
			}
			pos1 = next(pos1);
			pos2 = next(pos2);
		}
	}
	return (true);
}

//CAMBIA DIMENSIONE
template <class T>
void listvector<T>::changeDimension(value_type *&e, int oldSize, int newSize)
{
	value_type *temp = new value_type[newSize];
	int number = 0;

	if (oldSize < newSize)  {
		number = oldSize;
	}
	  else  {
		  number = newSize;
	  }

	for (int i = 0; i < number; i++)  {
		temp[i] = e[i];
	}

	delete[] e;
	e = temp;
}

//FUNZIONI UTILI___________________________________________________________
//INSERIMENTO ORDINATO
template <class T>
void listvector<T>::insertion_sort()
{
	T temp;
	position i, j;
	for (i = 1; i < lenght; i++)
	{
		temp = elements[i];
		j = i - 1;
		while ((j >= 0) && (elements[j] > temp))
		{
			elements[j + 1] = elements[j];
			j--;
		}
		elements[j + 1] = temp;
	}
}

#endif