#ifndef DIZIONARIO_H
#define DIZIONARIO_H

#include <iostream>
#include <string>
using namespace std;

//NON MI FUNZIONA SE METTO ANCHE IL TEMPLATE GENERALE
/*
//CREAZIONE CLASSE HASH____________________________________________
template <class T>
class hash {
  public:
    //SOVRACCARICO OPERATORE ()
	  size_t operator()(const T the_key) const; //restituisce la dimensione della chiave
};
*/
//SPACIALIZZAZIONE 'HASH' DI TIPO 'string'
//template <>
class hash {
  public:
	  size_t operator()(const string the_key) const {
		unsigned long hash_value = 0;
		int lenght = (int)the_key.length();
		for (int i = 0; i < lenght; i++)  {
			hash_value = 5 * hash_value + the_key.at(i); 
		}
		return (size_t(hash_value));
	}
};




//CREAZIONE STRUTTURA COPPIA mypair<K,E>_______________________________________
template <class K, class E>
struct mypair {
	//STRUTTURA mypair
  K first;
	E second;

	//FUNZIONI________________________________________________

  //COSTRUTTORE DEFOULT
	mypair() {}
  //ASSEGNA IL VALORE ALLA CHIAVE E ALL'ELEMENTO DI mypair
	mypair(K key, E element)  {
		first = key;
		second = element;
	}
  //COPIA I VALORI DI UNA COPPIA IN UN ALTRA COPPIA
	mypair(mypair<K, E> &new_pair)  {
		first =   new_pair.first;
		second = new_pair.second;
	}

  //SOVRACCARICO OPERATORI_______________________________________
  //SOVRACCARICO OPERATORE =
	mypair<K, E> &operator=(const mypair<K, E> &new_pair) {
		first = new_pair.first;
		second = new_pair.second;
		return *(this);
	}
  //SOVRACCARICO OPERATORE ==
	bool operator==(const mypair<K, E> &new_pair) {
		return ((first == new_pair.first) && (second == new_pair.second));
	}
  //SOVRACCARICO OPERATORE DI STAMPA <<
	friend ostream &operator<<(ostream &os, const mypair<K, E> &new_pair)
	{
		os <<" < "<< new_pair.first <<", "<< new_pair.second <<" > ";
		return (os);
	}
};




//CREAZIONE CLASSE DIZIONARIO______________________________________________________________________
template <class K, class E>
class dizionario  {
  public:
    //COSTRUTTORE
    dizionario(int the_divisor);
    //COSTRUTTORE DI DEFAULT (ASSEGNA come dimensione 100)
    dizionario();
    //INIZIALIZZA LA TABELLA, OVVERO IL NUM_ELEM A 0
    void create();
    //CONTROLLA SE LA TABELLA E' VUOTA
    bool empty() const;
    //NUMERO DI COPPIE NELLA TABELLA
    int size() const;
    //CONTROLLA SE LA CHIAVE E' PRESENTE NELLA TABELLA
    bool appartiene(const K &the_key) const;     //ex member
        //RESTITUISCE LA POSIZIONE DELLA CHIAVE NELLA TABELLA /SE NON E' PRESENTA RESTITUISCE UNA POS VUOTA)
        int search(const K &the_key) const;
    //INSERISCE UNA COPPIA NEL DIZIONARIO (TABELLA)
    void insert(mypair<K,E> &the_pair);
    //CANCELLA UNA COPPIA CON CHIAVE 'K'
    void remove(const K &the_key);
    //ESTRARE IL VALORE RIFERITO ALLA CHIAVE 'K'
    const E estrai_val(const K the_key);   //ex retrives
    //DISTRUTTORE
    ~dizionario();
    //MODIFICA IL VALORE LEGATO A UNA CHIAVE
	  void modify(const K &the_key, const E &the_element);
    //IN BASE ALLA CHIAVE INSERITA RESTITUISCE IL RIFERIMENTO ALLA COPPIA
	  mypair<K, E> *find(const K &the_key) const;
    //CONTROLLA SE UN VALORE E' PRESENTE NEL DIZIONARIO
	  bool containsValue(const E &value);
	  //CONTROLLA SE UNA COPPIA E' PRESENTE NEL DIZIONARIO
	  bool containsPair(const mypair<K, E> &pair);


//copiati soltanto---------------------------------------	
      //CONTENGONO LA STRUTTURA LISTA QUINDI NON SI POSSONO IMPLEMENTARE  
          //metodo che stampa la lista di tutte le chiavi presenti nella hashtable
	          //void printkeys();
	        //metodo che restituisce la lista di tutti i valori o gli elementi della hashtable
	          //listvalues values();
	        //metodo che restituisce la lista di tutte le chiavi della hashtable
	          //listkeys keys();
	        //metodo che raddoppia la massima capienza della tabella mantenendo gli stessi elementi
	          //void resize();
	        //metodo che restituisce vero se il primo dizionario e' sottoinsieme del secondo
	          //bool sottoinsieme(const hashtable<K, E> &);
	        //metodo che restituisce il valore del divisore
	          //int divisor_size() const;
//FINE funzioni copiate--------------------------------


	  //SOVRACCARICO OPERATORE UGUALIANZA ==
	  //bool operator==(const hashtable<K, E> &);         UTILIZZA LA LISTA

    
  private:
    mypair<K, E> **table;     //TABELLA DI COPPIE 
    hash<K> hashmap;	  //INDICA COME VIENE CALCOLATA LA POSIZONE IN BASE ALLA CHIAVE, INCLUDE LA FUNZIONE DI HASH
	  int num_elem;   //NUMERO DI COPPIE NEL DIZIONARIO
	  int divisor;    //INDICA LA DIMENSIONE ED E' ANCHE IL DIVISORE NELLA FUNZIONE DI HASH
    
};
 
//COSTRUTTORE___________________________________________
template <class K, class E> 
dizionario<K, E> :: dizionario(int the_divisor)
{
  this->create();  //da vedere
  divisor = the_divisor;  //ASSEGNA DIMENSIONE ALLA TABELLA
  table = new mypair<K, E> *[divisor];    //CREA LA TABELLA E LA INIZIALIZZA
	for (int i = 0; i < divisor; i++)
	{
		table[i] = nullptr;
	}
}

//COSTRUTTORE DI DEFAULT (ASSEGNA come dimensione 100)
template <class K, class E> 
dizionario<K, E> :: dizionario()
{
  this->create();
  divisor = 100;  //DIMENSIONE DI DEFLAUT
  table = new mypair<K, E> *[divisor];    //CREA LA TABELLA E LA INIZIALIZZA (PUNATORE DI PUNTATORI PERCHE OGNI POSIZIONE DELLA TABELLA PUNTA AD UNA COPPIA)
	for(int i = 0; i < divisor; i++)
	{
		table[i] = nullptr;
	}
}

//INIZIALIZZA LA TABELLA, OVVERO IL NUM_ELEM A 0
template <class K, class E>
void dizionario<K, E> :: create()  {
	num_elem = 0;
}

//CONTROLLA SE LA TABELLA E' VUOTA
template <class K, class E>
bool dizionario<K, E>::empty() const {
	return (num_elem == 0);
}

//NUMERO DI COPPIE NELLA TABELLA
template <class K, class E>
int dizionario<K, E>::size() const  {
	return (num_elem);
}

//CONTROLLA SE LA CHIAVE E' PRESENTE NELLA TABELLA
template <class K, class E>
bool dizionario<K, E> :: appartiene(const K &the_key) const  {
	if(!this->empty()) {
		int position = search(the_key);   //ASSEGNA LA POSIZIONE DELLA CHIAVE NELLA TABELLA A 'position'
		if (table[position] != nullptr) {
			return (table[position]->first == the_key);
		}
	}
	return (false);
}

//RESTITUISCE LA POSIZIONE DELLA CHIAVE NELLA TABELLA (SE NON E' PRESENTA RESTITUISCE UNA POS VUOTA)
template <class K, class E>
int dizionario<K, E> :: search(const K &the_key) const  {
  //ricerca tramite modulo della dimensione della tabella (divisor), in modo che il risultato sia sempre una posizione della tabella 
	int i = (int)hashmap(the_key) % divisor; //IN BASE ALLA FUNZIONE DI HASH VIENE GENERATA UNA POSIZIONE
	int j = i;
	do {
    //SE: la poszione trovata è vuota || la chiave della poszione trovata è la chiave cercata
		if ((table[j] == nullptr) || (table[j]->first == the_key))  { 
      return j; 
    }
		j = (j + 1) % divisor; //LA POSIZIONE DI PRIMA VIENE AUMENTATA DI 1, E SI RIPETE LA RICERCA
	}while (j != i);  //QUANDO j=i, SIGNIFICA CHE TUTTE LE POSIZIONI SONO STATE CONTROLLATE

	return (j);
}

//INSERISCE UNA COPPIA NEL DIZIONARIO (TABELLA)
template <class K, class E>
void dizionario<K,E> :: insert(mypair<K, E> &the_pair)  {
	if (!appartiene(the_pair.first))  {  //se non appartiene alla tabella
		int b = search(the_pair.first);
		//se la posizione torvata è nullptr
		if (table[b] == nullptr)  {
			table[b] = new mypair<K, E>(the_pair);  //nella posizione vuota crea una coppia
			num_elem++;
		}
		else  {
			//altrimenti si controlla se la chiave è gia presente e si carica il valore
			if (table[b]->first == the_pair.first)  {
				table[b]->second = the_pair.second;
			}
			else  {
				//se la poszione trovata non è 'nullptr' e non contiene la chiave cercata ALLORA LA TABELLA E' PIENA
				return;
			}
		}
	}
}

//CANCELLA UNA COPPIA CON CHIAVE 'K'
template <class K, class E>
void dizionario<K,E> :: remove(const K &the_key)  {
	if (appartiene(the_key))  {
		int position = search(the_key);   //si trova la posizione nella tabella
		if (table[position]->first == the_key)  { //se le chiavi coincidono
			//cancella la coppia
      delete table[position];
			table[position] = nullptr;
			num_elem--;
		}
	}
}

//ESTRARE IL VALORE RIFERITO ALLA CHIAVE 'K'
template <class K, class E>
const E dizionario<K,E> :: estrai_val(const K the_key) {
	if (appartiene(the_key))  {  //se la chiave appartiene
		int position = search(the_key);   //inserisi la posizoone della chiave in 'position'
		return (table[position]->second);
	}
  return 0;
}

//MODIFICA IL VALORE LEGATO A UNA CHIAVE
template <class K, class E>
void dizionario<K, E>::modify(const K &the_key, const E &the_element) {
	//VERIFICA SE LA CHIAVE APPARTIENE
	if (appartiene(the_key))  {
		int position = search(the_key);
		table[position]->second = the_element;
	}
	else  {
		cout << "\nLA CHIAVE NON E' PRESENTE";
	}
}

//IN BASE ALLA CHIAVE INSERITA RESTITUISCE IL RIFERIMENTO ALLA COPPIA
template <class K, class E>
mypair<K, E> *dizionario<K, E>::find(const K &the_key) const  {
	//CERCA LA POSIZIONE DELLA CHIAVE
  int b = search(the_key);
	if ((table[b] == nullptr) || (table[b]->first != the_key))  {
		return (nullptr); //CHIAVE NON TROVATA
	}
	return (table[b]);
}

//CONTROLLA SE UN VALORE E' PRESENTE NEL DIZIONARIO
template <class K, class E>
bool dizionario<K, E>::containsValue(const E &value)  {
	bool found = false;
	if (!this->empty()) {
		//cerco il valore nel dizionario
		for (int i = 0; (i < divisor) && !found; i++) {
			if (table[i] != nullptr)  {
				if (table[i]->second == value)  {
					found = true;
				}
			}
		}
	}
	return (found);
}

//CONTROLLA SE UNA COPPIA E' PRESENTE NEL DIZIONARIO
template <class K, class E>
bool dizionario<K, E>::containsPair(const mypair<K, E> &pair) {
	bool found = false;
	for (int i = 0; (i < divisor) && !found; i++) {
		if (table[i] != nullptr)  {
			found = (*(table[i]) == pair);
		}
	}
	return (found);
}

//DISTRUTTORE
template <class K, class E>
dizionario<K,E> :: ~dizionario()
{
	if (!this->empty())
	{
		for (int i = 0; i < divisor; i++)
		{
			if (table[i] != nullptr)
			{
				delete table[i];
				table[i] = nullptr;
				num_elem--;
			}
		}
	}
	delete[] table;
	table = nullptr;
}

/*ANCHE STA CAZZO DI FUNZIONE UTILIZZA LA LISTA QUINDI NON SI PUO IMPLEMENTARE
//SOVRACCARICO OPERATORE UGUALIANZA ==
template <class K, class E>
bool dizionario<K, E>::operator==(const dizionario<K, E> &h)  {
	if (this->size() != h.size()) {  //CONTROLLA SE LA DIMENSIONE E' DIVERSA
		return (false);
	}
	listpair l1;
	for (int i = 0; i < divisor; i++) {
		if (table[i] != nullptr)  {
			mypair<K, E> pair_copy = *(table[i]);
			l1.push_back(pair_copy);
		}
	}
	listpair l2;
	for (int i = 0; i < h.divisor; i++)
	{
		if (h.table[i] != nullptr)
		{
			mypair<K, E> pair_copy = *(h.table[i]);
			l2.push_back(pair_copy);
		}
	}
	return (l1 == l2);
}
*/
#endif