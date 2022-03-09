#include <iostream>
#include <string>
#include "dizionario.h"
using namespace std;

int main() {
  //crea coppia
	mypair<string, int> the_pair;
  //definisce coppia
	the_pair.first = "firstkey";
	the_pair.second = 10;

  //crea dizionario
  dizionario<string, int> h(5);
  //stampa se il dizionario è vuoto
	cout << "\nvuoto: " <<h.empty();
  //stampa la dimensione
	cout << "\nnum elementi: " << h.size();
  //inserisce coppia
	h.insert(the_pair);

  //stampa se il dizionario è vuoto
	cout << "\nvuoto: " <<h.empty();
  //stampa la dimensione
	cout << "\nnum elementi: " << h.size();


  //crea coppia
	mypair<string, int> _pair;
  //definisce coppia
	_pair.first = "key";
	_pair.second = 100;

  cout << "\nvalore primachiave: " << h.estrai_val(the_pair.first);
  h.modify(the_pair.first,99);
  cout << "\nvalore primachiave modificato: " << h.estrai_val(the_pair.first);
  
  cout << "\nvalore chiave non inserita (0 SE NON PRESENTE): " << h.estrai_val(_pair.first);

  cout << "\nappartiene: " << h.appartiene(the_pair.first);
  cout << "\nappartiene: " << h.appartiene(_pair.first);
	cout << "\n\n";
	//h.printkeys();

  cout << "NUMERO COPPIE --> "<<h.size();
  cout << "\nPOSIZIONE CHIAVE --> "<<h.search(the_pair.first);



  //CREAO E INSERISCO 5 COPPIE
  mypair<string, int> the_pair1;
  //definisce coppia
	the_pair1.first = "firstkey1";
	the_pair1.second = 1;

  mypair<string, int> the_pair2;
  //definisce coppia
	the_pair2.first = "firstkey2";
	the_pair2.second = 12;

  mypair<string, int> the_pair3;
  //definisce coppia
	the_pair3.first = "firstkey3";
	the_pair3.second = 13;

  mypair<string, int> the_pair4;
  //definisce coppia
	the_pair4.first = "firstkey4";
	the_pair4.second = 14;

  mypair<string, int> the_pair5;
  //definisce coppia
	the_pair5.first = "firstkey5";
	the_pair5.second = 15;

  h.insert(the_pair1);
  h.insert(the_pair2);
  h.insert(the_pair3);
  h.insert(the_pair4);
  //QUESTA NON VIENE INSERITA PERCHE IL DIZIONARIO E' PIENO
  h.insert(the_pair5);
    
  cout << "\nNUMERO COPPIE --> "<<h.size();
  cout << "\nPOSIZIONE CHIAVE --> "<<h.search(the_pair5.first);

  cout << "\nappartiene: " << h.appartiene(the_pair.first);

  
  cout << "\nvalore chiave: (NON E' STATO INSERITO) --> " << h.estrai_val(the_pair5.first);

  cout << "\n\n\nINDIRIZZO COPPIA (presente) --> " << h.find(the_pair.first);
  cout << "\nINDIRIZZO COPPIA (non presente) --> " << h.find(the_pair5.first);


} 

