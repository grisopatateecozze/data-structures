#ifndef CODA_H
#define CODA_H

#include <iostream>
#include <string>
using namespace std;

template <class T>
class coda
{
public:
	//DEFINIZIONE TIPO
	typedef T value_type;

	//OPERATORI
  //IMPOSTA LA LUNGHEZZA (POSIZIONI OCCUPATE)
	virtual void create() = 0;
  //CONTROLLA SE LA CODA E' VUOTA
	virtual bool empty() const = 0;
  //LEGGE E RESTITUISCE L'ELEMENTO IN ULTIMA POSIZIONE, OVVERO IL PRIMO INSERITO
	virtual value_type top() const = 0;
  //ELIMINA L'ULTIMO ELEMENTO DELLA CODA, OVVERO IL PRIMO INSERITO
	virtual void decoda() = 0;
  //INSERISCE UN ELEMENTO IN TESTA ALLA CODA
	virtual void encoda(value_type) = 0;
  //metodo che restituisce la lunghezza della coda
	virtual int size() const = 0;
  //STAMPA TUTTA LA PILA
  virtual void print() =0;
  //virtual void copycoda(coda) =0;
};

#endif