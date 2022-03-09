#ifndef VETTSTACK_H
#define VETTSTACK_H

#include <iostream>
#include "stack.h"
using namespace std;

template <class T>
class vettstack : public stack<T> {
  
  public:
  //DEFINIZIONE ALIAS PER IL TIPO GENERICO
  typedef typename stack<T> :: value_type value_type;

    //COSTRUTTORI____________________________
    vettstack();
    vettstack(int n);

    //OPERATORI______________________________
    //DISTRUTTORE
	  ~vettstack();
    //IMPOSTA LA TESTA A 0, OVVERO SENZA ELEMENTI
    void create();
    //CONTROLLA SE LA LISTA E' VUOTA
    bool empty() const;
    //MOSTRA TESTA
    value_type top() const;
    //AGGIUNGE IN TESTA
    void push(value_type e);
    //RIMUOVE IN TESTA
    value_type pop();
    //STAMPA STACK
    void print();
    
  private:
	  value_type *S;
	  int dim;
	  int head;
};

//COSTRUTTORE DEFAULT
  template <class T> 
  vettstack<T> :: vettstack(){
    dim=100;
    S = new value_type[dim];
    this->create();
    
  }

//COSTRUTTORE CON PARAMETRO
  template <class T> 
  vettstack<T> :: vettstack(int n)  {
		dim = n;
    S = new T[dim];
		this->create();  
	}

//CREATORE IMPOSTA LA TESTA A 0
  template <class T> 
  void vettstack<T> :: create(){
    head=0;
  }

//CONTROLLA SE LA PILA E' VUOTA
	template<class T> 
  bool vettstack<T> :: empty() const {
		return head == 0;
	}

//MOSTRA TOP
	template <class T> 
  typename vettstack<T> :: value_type vettstack<T>:: top() const{
	    if (!empty())
	    {
		    return (S[head]);
	    }
    return 0; // restituisce 0 se non trova il top
	}

//AGGIIUNGE IN TESTA
	template <class T> 
  void vettstack<T>:: push(value_type e) {
   if (head < dim)
	  {
		  head++;
		  S[head] = e;
	  }
  }
  
//RIMUOVE IN TESTA
	template <class T> 
  typename vettstack<T> :: value_type vettstack<T> :: pop() {
	  value_type value; //CREA VARIABILE DOVE METTERE L'ELEMENTO DA RIMUOVERE
	  if (!empty()) {
	    value = top();
	  	head--;
	  }
	  return (value);
	}
  
//DISTRUTTORE
	template <class T> 
  vettstack<T> :: ~vettstack() {
    dim = 0;
	  head = 0;
	  if (S != nullptr) {
		  delete[] S;
		  S = nullptr;
	  }
	}
  
 
//STAMPA TUTTA LA PILA
  template<class T> 
  void vettstack<T> :: print() {
	  cout<<"\nLA PILA:\n";
    while(head!=0) {
		  cout<< S[head]<<"\n";
      head--;
	  }
  }

#endif