#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

template <class T> 
class stack{
  public:
  //ALIAS DEL TIPO DI DATO
  typedef T value_type;

  //OPERATORI_______________________________________
  
  //IMPOSTA LUNGHEZZA A 0
  virtual void create() =0;
  //CONTROLLA SE LA PILA E' VUOTA
  virtual bool empty() const =0;
  //RIMUOVE IN TESTA
  virtual value_type pop() =0;
  //RESTITUISCE IL VALORE IN TESTA
  virtual value_type top() const =0;
  //IMPILA ELEMENTO IN POSIZIONE TOP
  virtual void push(value_type) =0;
  //STAMPA STACK
  virtual void print() =0;
};


#endif