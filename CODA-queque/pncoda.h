#ifndef PNCODA_H
#define PNCODA_H

#include <iostream>
#include "coda.h"
using namespace std;

//DICHIARAZIONE CLASSE CODA CON PUNTATORI
template <class T>
class pncoda;

//DICHIARAZIONE CLASSE NODO CODA_______________________________________________
template <class T>
class codanode
{
	friend class pncoda<T>;

public:
  //COSTRUTTORI
	codanode()  {
		next = nullptr;
	}

	codanode(T el)  {
		item = el;
		next = nullptr;
	}

private:
	T item;
	codanode<T> *next;
};

//DICHIARAZIONE CLASSE CODA_______________________________________________________
template <class T>
class pncoda : public coda<T>
{

public:
	//DEFINISCE ALIAS TIPI
	typedef codanode<T> *node;
	typedef typename coda<T>::value_type value_type;

	//COSTRUTTORI________________________________________
	pncoda();
  //DISTRUTTORE
	~pncoda();

	//OPERATORI_________________________________________
	//IMPOSTA LA LUNGHEZZA (POSIZIONI OCCUPATE)
	void create();
	//metodo che restituisce vero se la coda e' vuota
	bool empty() const;
  //LEGGE E RESTITUISCE L'ELEMENTO IN ULTIMA POSIZIONE, OVVERO IL PRIMO INSERITO
	value_type top() const;
  //ELIMINA L'ULTIMO ELEMENTO DELLA CODA, OVVERO IL PRIMO INSERITO
	void decoda();
	//INSERISCE UN ELEMENTO IN TESTA ALLA CODA
	void encoda(value_type);
	//metodo che restituisce la grandezza della coda
	int size() const;
	//STAMPA TUTTA LA CODA
	void print();

  //OPERATORI ULTERIORI DI 'pncode'_______________________
  //COPIA UNA CODA IN UN ALTRA
	void copycoda(pncoda<T> *newnode);
	

private:
	node head;     //ULTIMO ELEMENTO CODA (PRIMO INSERITO)
	node tail;     //PRIMO ELEMENTO CODA (ULTIMO INSERITO)
	int lenght;
};

//COSTRUTTORI________________________________________________________
template <class T>
pncoda<T>::pncoda()
{
	this->create();
	head = tail = nullptr;
}


//DISTRUTTORE
template <class T>
pncoda<T>::~pncoda()
{
	while (!this->empty())
	{
		this->decoda();
	}
	head = tail = nullptr;
	lenght = 0;
}

//OPERATORI_____________________________________________________________
//IMPOSTA LA LUNGHEZZA (POSIZIONI OCCUPATE)
template <class T>
void pncoda<T>::create()
{
	lenght = 0;
}

//---------------------------------------------
template <class T>
bool pncoda<T>::empty() const
{
	return (lenght == 0);
}

//LEGGE E RESTITUISCE L'ELEMENTO IN ULTIMA POSIZIONE, OVVERO IL PRIMO INSERITO
template <class T>
typename pncoda<T>::value_type pncoda<T>::top() const
{
	value_type item;
	if (!this->empty())
	{
		return (head->item);
	}
	return (item);
}

//ELIMINA L'ULTIMO ELEMENTO DELLA CODA, OVVERO IL PRIMO INSERITO
template <class T>
void pncoda<T>::decoda()
{
	if (!this->empty())
	{
		node temp = head;
		head = head->next;
		delete temp;
		temp = nullptr;
		lenght--;
	}
}

//INSERISCE UN ELEMENTO IN TESTA ALLA CODA
template <class T>
void pncoda<T>::encoda(value_type el)
{
	node temp = new codanode<T>(el);    //CREO IL NODO TEMP E LO INIZIALIZZO CON 'el'
	
  if (this->empty())  {     //SE LA CODA E VUOTA 
		head = tail = temp;     //METTE COME TESTA E COME CODA IL NODO APPENA CREATO (TEMP) INIZIALIZZATO CON el
	}
	else                    //ALTRIMENTI
	{
		tail->next = temp;    //AL NEXT DI TAIL(CHE E' L'ULTIMO INSERITO), METTE TEMP CHE DIVENTA L'ULTIMO
	}
	temp->next = nullptr;    //FA PUNTARE L'ULTIMO NODO CHE ORA E' TEMP A NIENTE (nullptr)
	tail = temp;  //DICE CHE ORA IL NUOVO NODO TEMP E' IL NUOVO ULTIMO NODO
	lenght++;     //AUMENTA LUNGHEZZA CODA
}

//--------------------------------------------
template <class T>
int pncoda<T>::size() const
{
	return (lenght);
}


//STAMPA TUTTA LA CODA
template <class T>
void pncoda<T>::print()
{
  cout<<"\nELEMENTI CODA (ptr):";
	if (!this->empty())
	{
		node i = head;          //ASSEGNO AL NODO i LA TESTA, PER NON PERDERE 
		while (i != nullptr)    //FINO A QUANDO LA i PUNTA A QUALCOSA
		{
			cout << "\n--> "<< i->item;   //STAMPA L'ITEM DI i
			i = i->next;                  //FA PUNTARE i AL NODO SUCCESSIVO
		}
	}
}

//COPIA UNA CODA IN UN ALTRA
template <class T>
void pncoda<T>::copycoda(pncoda<T> *newnode)
{
  if(!newnode->empty())  {      //controlla se la coda ha elelementi
    node temp = newnode->head;  //copia la testa della coda da cui copiare gli elemnti in un nodo 'temp'
		while (temp != nullptr)  {
			encoda(temp->item);       //inserisce l'elemeto nella coda 
			temp = temp->next;        //seleziona il prossiamo nodo da copiare
		}
	}
}



#endif