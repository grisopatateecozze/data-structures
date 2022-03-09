#ifndef CODAVT_H
#define CODAVT_H

#include <iostream>
#include "coda.h"
#define MAXDIM 100 //DIMENSIONE PILA CON COSTRUTTORE DI DEFAULT 
using namespace std;

//DEFINIZIONE CLASSE CODA______________________________________
template <class T>
class codavt : public coda<T>
{
public:
	//DEFINIZIONE TIPO
	typedef typename coda<T>::value_type value_type;

	//COSTRUTTORI________________________________
	codavt();
	codavt(int);
	~codavt();

	//OPERATORI___________________________________
	//IMPOSTA LA LUNGHEZZA (POSIZIONI OCCUPATE)
	void create();
	//metodo che restituisce vero se la coda e' vuota
	bool empty() const;
	//LEGGE E RESTITUISCE L'ELEMENTO IN ULTIMA POSIZIONE, OVVERO IL PRIMO INSERITO
	value_type top() const;
	///ELIMINA L'ULTIMO ELEMENTO DELLA CODA, OVVERO IL PRIMO INSERITO
	void decoda();
	//INSERISCE UN ELEMENTO IN TESTA ALLA CODA
	void encoda(value_type);
	//metodo che restituisce la lunghezza della coda
	int size() const;
  //STAMPA TUTTA LA CODA (DAL'ULTIMO ELEMENTO), ELIMINA LA CODA!!!
  void print();

private:
	value_type *elements; //array di elementi
	int head;			  //cursore che punta alla testa dell'array
	int lenght;			  //lunghezza della coda
	int MAXLENGHT;		  //massima capienza
};

//COSTRUTTORI________________________________________________
template <class T>
codavt<T>::codavt()
{
	this->create();
	MAXLENGHT = MAXDIM;
	elements = new value_type[MAXLENGHT];
	head = 0;
}

//------------------------------------
template <class T>
codavt<T>::codavt(int N)
{
	this->create();
	MAXLENGHT = N;
	elements = new value_type[MAXLENGHT];
	head = 0;
}

//DISTRUTTORE
template <class T>
codavt<T>::~codavt()
{
	lenght = 0;
	delete[] elements;
	elements = nullptr;
}

//OPERATORI__________________________________________________________
//IMPOSTA LA LUNGHEZZA (POSIZIONI OCCUPATE)
template <class T>
void codavt<T>::create()
{
	lenght = 0;
}

//---------------------------------------
template <class T>
bool codavt<T>::empty() const
{
	return (lenght == 0);
}

//---------------------------------------
template <class T>
typename codavt<T>::value_type codavt<T>::top() const
{
	value_type item;
	if (!this->empty())
	{
		return (elements[head]);
	}
	return (item);
}

//ELIMINA L'ULTIMO ELEMENTO DELLA CODA, OVVERO IL PRIMO INSERITO
template <class T>
void codavt<T>::decoda()
{
	if (!this->empty())
	{
		head = ((head + 1) % MAXLENGHT);
		lenght--;
	}
}

//INSERISCE UN ELEMENTO IN TESTA ALLA CODA
template <class T>
void codavt<T>::encoda(value_type el)
{
  if (lenght < MAXLENGHT) {
		elements[((head + lenght) % MAXLENGHT)] = el;
		lenght++;
	  }
  else cout<< "la coda è piena!!!, impossibile aggiungere elemento"<<endl;

}

//---------------------------------------
template <class T>
int codavt<T>::size() const
{
	return (lenght);
}

//STAMPA TUTTA LA CODA
template <class T>
void codavt<T> :: print() {
/*
  cout<<"\nELEMENTI CODA:\n";

    while(!empty()) {
		  cout<<top()<<"\n";
      decoda();
      

	  }
    */

  cout<<"\nELEMENTI CODA (vtr):";
  int i=0;
  while(i<lenght)  {
    cout<<"\n--> "<<elements[i];
    i++;
  }

}



#endif