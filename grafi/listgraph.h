#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include <iostream>
#include <string>
#include "graph.h"
#include "linearlist.h"
#include "linkedlist.h"

#define MAXDIMENSION 100
using namespace std;

//CLASSE NODO GRAFO_____________________________________________
class nodeg {
public:
    //COSTRUTTORI
    nodeg(int i)  {
        idnode = i;
    }
    nodeg() {
        idnode = 0;
    }
    //RESTITUISCE L'ID
    int getid() {
        return (idnode);
    }
    //SCRIVE L'ID
    void setid(int id)  {
        idnode = id;
    }

    //SOVRACCARICO OPERATORI__________________
    nodeg &operator=(const nodeg &n)  {
        idnode = n.idnode;
        return *(this);
    }
    bool operator==(const nodeg &n) {
        return (idnode == n.idnode);
    }

private:
    int idnode;   //(ANDRA LA POSIZONE DEL NODO NELLA 'MATRICE')
};



//CLASSE INFO ARCO___________________________________________________
template <class P>
class archinfo  {
public:
    P weight;   //PESO
    nodeg _to;  //ID_NODE DEL NODO (POSIZONE DEL NODO NELLA 'MATRICE') A CUI IL NODO SI COLLEGA
    
    archinfo<P> &operator=(const archinfo<P> &archinfo) {
      weight = archinfo.weight;
      _to = archinfo._to;
      return *(this);
    }
    
};

//CLASSE INFO NODO_____________________________________________
template <class E, class P>
class nodeinfo/* : public graph<E, P, nodeg> */ {
public:
    E label;        //ETICHETTA
    bool empty;     //VUTO SE =1
    void *info;     
    linkedlist<archinfo<P>> arches;
    
    nodeinfo()  {
        label = "";
        info = 0;
        empty = true;
    }
};

//CLASSE LISTA GRAFI_________________________________________
template <class E, class P>
class listgraph : public graph<E, P, nodeg> {
public:
    //^^^tipi
    typedef E label;                                             //tipo etichetta
    typedef P weight;                                            //tipo peso
    typedef nodeg node;                                          //tipo nodo
    typedef class arch<weight, node> arch;                       //tipo arco
    typedef class graph<label, weight, node> graph;              //ticpo grafo con etichetta peso e nodo
    typedef typename graph::listnode listnode;                   //tipo listanodi
    typedef typename graph::position_listnode position_listnode; //tipo posizione listanodi



    //COSTRUTTORE_______________________________________________
    listgraph();
    //COSTRUTTORE CON PARAMETRO (DIMENSIONE)
    listgraph(int);
    //DISTRUTTORE
    ~listgraph();

    //OPERATORI___________________________________________________
    //INIZIALIZZA A 0 IL NUMERO DI NODI
    void create();
    //VERO SE IL GRAFO E' VUOTO (NODI=0)
    bool empty() const;
    //INSERISCE UN NODO NELLA MATRICE, E COLLEGA IL SUO ID ALLA POZIONE NELLA MATRICE
    void insNode(node &);
    //INSERISCE UN ARCO NELL'VETTORE DI ARCHI DEL NODO INDICATO ('n1')
    void insArch(node, node, weight);
    //CANCELLA IL NODO INDICATO DALLA MATRICE (non lo cancella se ha archi)
    void eraseNode(node);
    //ELIMINA L'ARCO DEI NODI INDICATI
    void eraseArch(node, node);
    //VERO SE IL NODO INDICATO APPARTIENE AL GRAFO
    bool isNode(node) const;
    //VERO SE I NODI INDICATI FORMANO UN ARCO NEL GRAFO
    bool isArch(node, node) const;
    //metodo che restituisce la lista dei nodi adiacenti al nodo al quale si applica
    listnode adjacent(node) const;
    //metodo che restituisce la lista dei nodi che appartengono al grafo
    listnode listNode() const;
    //metodo che legge e restituisce l'etichetta di un nodo del grafo
    label readLabel(node) const;
    //metodo che scrive e sovrascrive l'etichetta di un nodo del grafo
    void writeLabel(node, label);
    //metodo che legge e restituisce il peso di un arco del grafo
    weight readWeight(node, node) const;
    //metodo che scrive e sovrascrive il peso di un arco del grafo
    void writeWeight(node, node, weight);
    //metodo che restituisce il numero totale dei nodi inseriti nel grafo
    int numNodes() const;
    //metodo che restituisce il totale degli archi nel grafo
    int numArches() const;

    //FUNZIONI DI SERVIZIO____________________________________________________
    //VERO SE LA MATRICE 'matrix' E' VUOTA
    bool isEmptyMatrix() const;
    //
    void dfs(node) const;
    //
    void dfs(node, int *) const;

private:
    nodeinfo<E, P> *matrix;   //MATRICE DI NODI
    int dimension;    //DIMENSIONE MATRIX
    int nodes;  //NUEMERO NODI
    int arches; //NUMERO ARCHI
};

//COSTRUTTORE_______________________________________________
template <class E, class P>
listgraph<E, P>::listgraph()  {
    this->create();   //INIZIALIZZA IL NUMERO DI NODI
    dimension = MAXDIMENSION;
    arches = 0;     //IMPOSTA NUMERO ARCHI
    matrix = new nodeinfo<E, P>[dimension]; //CREA MARICE NODI
    for (int i = 0; i < dimension; i++) {
        matrix[i].arches.create();//DI MATRIX, INIZIALIZZA TUTTI GLI ARCHI DEL VET DI TIPO archinfo
    }
}

//COSTRUTTORE CON PARAMETRO (DIMENSIONE)
template <class E, class P>
listgraph<E, P>::listgraph(int dim) {
    this->create();
    dimension = dim;
    arches = 0;
    matrix = new nodeinfo<E, P>[dimension];
    for (int i = 0; i < dimension; i++) {
        matrix[i].arches.create();  //CRATE DI LINKED LIST
    }
}

//DISTRUTTORE
template <class E, class P>
listgraph<E, P>::~listgraph() {
    if (!isEmptyMatrix()) {
        for (int i = 0; i < dimension; i++) {
            matrix[i].arches.~linkedlist();   //DISTRUGGE IL VETTORE DI archinfo
        }
    }
    delete[] matrix;
    matrix = nullptr;
}

//OPERATORI___________________________________________________
//INIZIALIZZA A 0 IL NUMERO DI NODI
template <class E, class P>
void listgraph<E, P>::create()  {
    nodes = 0;
}

//VERO SE IL GRAFO E' VUOTO (NODI=0)
template <class E, class P>
bool listgraph<E, P>::empty() const {
    return (nodes == 0);
}

//INSERISCE UN NODO NELLA MATRICE, E COLLEGA IL SUO ID ALLA POZIONE NELLA MATRICE
template <class E, class P>
void listgraph<E, P>::insNode(node &nodegraph)  {
    int n = 0;
    if (nodes < dimension)  {   //CONTROLLA SE C'E' SPAZIO
        //CONTROLLA TUTTI I 'nodeinfo' di MATRIX APPENA NE TROVA UNO CON LA VARIABILE 'empty' IMPOSTATA a '1' (ovvero vuota)
        while (!matrix[n].empty)  {   
            n++;
        }
        nodes++;    //AUMENTA IL NUMERO DI NODI
        matrix[n].empty = false;    //IMPOSTA IL NODO VUTO TROVATO COME PIENO 
    }
    nodegraph.setid(n); //SETTA L'ID DEL NODO DA INSERIRE CON LA POSIZIONE NELLA MATRICE ASSEGNATA
}

//VERO SE IL NODO INDICATO APPARTIENE AL GRAFO
template <class E, class P>
bool listgraph<E, P>::isNode(node n) const  {
    return (!matrix[n.getid()].empty);
}

//CANCELLA IL NODO INDICATO DALLA MATRICE (non lo cancella se ha archi)
template <class E, class P>
void listgraph<E, P>::eraseNode(node n)
{
    /*
    !!!!!!!!!!!!!!
     * nell'eliminazione di un nodo suppongo che non ci siano
     * nodi entranti ne nodi uscenti
    !!!!!!!!!!!!!!
    */
    bool canc = true;
    //controllo sugli archi uscenti
    for (int i = 0; (i < dimension) && (canc); i++)
    {
        if (!matrix[n.getid()].arches.empty())
        {
            canc = false;
        }
    }
    //controllo sugli archi entranti
    for (int i = 0; (i < dimension) && (canc); i++)
    {
        if (!matrix[i].empty)
        {
            for (auto p = matrix[i].arches.begin(); !matrix[i].arches.end(p); p = matrix[i].arches.next(p))
            {
                if (matrix[i].arches.read(p)._to.getid() == n.getid())
                {
                    canc = false;
                }
            }
        }
    }
    //se canc e' vero elimino il nodo
    if (canc)
    {
        //per sicurezza elimino eventuali archi uscenti
        while (!matrix[n.getid()].arches.empty())
        {
            matrix[n.getid()].arches.pop_front();
        }
        //imposto il nodo come vuoto
        matrix[n.getid()].empty = true;
        //decremento il totale nodi
        nodes--;
    }
}


//INSERISCE UN ARCO NELL'VETTORE DI ARCHI DEL NODO INDICATO ('n1')
template <class E, class P>
void listgraph<E, P>::insArch(node n1, node n2, weight w) {
    //CREO IL NODO ARCO DA INSERIRE
    archinfo<P> infoarco;

    infoarco.weight = w;    //ASSEGNO IL PESO
    infoarco._to = n2;      //ASSEGNO L'ID DEL NODO A CUI SI COLLEGA

    //SELEZIONO LA POSIZONE NELLA MATRICE DEL NODO 'n1'....SELEZIONO IL VETTORE 'arches' NELLA MATRICE DI TIPO 'nodeinfo'....DEL VETTORE DI ARCHI FACCIO push_back FUNZIONE DI linkedlist, QUINDI INSERISCO 'infoarco' nell'ultima posizione del vettore di archi
    matrix[n1.getid()].arches.push_back(infoarco);
    arches++;   //AUMENTO IL NUMERO DI ARCHI
}

//VERO SE I NODI INDICATI FORMANO UN ARCO NEL GRAFO
template <class E, class P>
bool listgraph<E, P>::isArch(node n1, node n2) const  {
  bool found = false;

  if (!matrix[n1.getid()].arches.empty()) { //controllo se il primo nodo ha archi
    //salvo il primo arco nel vettore di archi del primo nodo ('n1')
    typename linkedlist<archinfo<P>>::position p = matrix[n1.getid()].arches.begin();

    while (!matrix[n1.getid()].arches.end(p) && !(found)) { //finche i nodi non finiscono o viene trovato
      //se nell'arco selezionato (archinfo) dal primo nodo, l'id del nodo collegato (_to) e' uguale all'id del secondo nodo
      if (matrix[n1.getid()].arches.read(p)._to.getid() == n2.getid())  {
        found = true;
      }
      p = matrix[n1.getid()].arches.next(p);  //seleziona l'arco successivo
    }
  }
  return (found);
}

//ELIMINA L'ARCO DEI NODI INDICATI
template <class E, class P>
void listgraph<E, P>::eraseArch(node n1, node n2) {
    typename linkedlist<archinfo<P>>::position p;
    p = matrix[n1.getid()].arches.begin(); //SELEZIONA IL PRIMO ARCO DEL PRIMO NODO
    bool found = false;

    while (!matrix[n1.getid()].arches.end(p) && !(found)) {
        if (matrix[n1.getid()].arches.read(p)._to.getid() == n2.getid())  {
            found = true;
        }
        else  {
            p = matrix[n1.getid()].arches.next(p);
        }
    }
    if (found)
    {
        matrix[n1.getid()].arches.erase(p);
        arches--;
    }
}

//metodo che restituisce la lista dei nodi adiacenti al nodo al quale si applica
template <class E, class P>
typename listgraph<E, P>::listnode listgraph<E, P>::adjacent(node n) const
{
    listnode list;
    if (isNode(n))  {
        if (!matrix[n.getid()].arches.empty())  {
            //scansiono la lista archi
            for (auto i = matrix[n.getid()].arches.begin(); !matrix[n.getid()].arches.end(i); i = matrix[n.getid()].arches.next(i))
            {
                //inserisco il p-esimo arco nella lista dei nodi adiacenti l
                node copy(matrix[n.getid()].arches.read(i)._to.getid());
                list.push_back(copy);
            }
        }
    }
    return (list);
}

//metodo che restituisce la lista dei nodi che appartengono al grafo
template <class E, class P>
typename listgraph<E, P>::listnode listgraph<E, P>::listNode() const  {
    listnode list;
    for (int i = 0; i < dimension; i++) {
        if (!matrix[i].empty) {
            node copy(i);
            list.push_back(copy);
        }
    }
    return (list);
}

//metodo che legge e restituisce l'etichetta di un nodo del grafo
template <class E, class P>
E listgraph<E, P>::readLabel(node n) const  {
    return (matrix[n.getid()].label);
}

//metodo che scrive e sovrascrive l'etichetta di un nodo del grafo
template <class E, class P>
void listgraph<E, P>::writeLabel(node n, E label) {
    matrix[n.getid()].label = label;
}

//metodo che legge e restituisce il peso di un arco del grafo
template <class E, class P>
typename listgraph<E, P>::weight listgraph<E, P>::readWeight(node n1, node n2) const  {
    P weight = -1;
    if (isArch(n1, n2)) {
        bool found = false;
        auto p = matrix[n1.getid()].arches.begin();
        while (!matrix[n1.getid()].arches.end(p) && !found) {
            if (matrix[n1.getid()].arches.read(p)._to.getid() == n2.getid())  {
                found = true;
            }
            else  {
                p = matrix[n1.getid()].arches.next(p);
            }
        }
        if (found)  {
            return (matrix[n1.getid()].arches.read(p).weight);
        }
    }
    return (weight);
}

//metodo che scrive e sovrascrive il peso di un arco del grafo
template <class E, class P>
void listgraph<E, P>::writeWeight(node n1, node n2, P weight) {
    if (isArch(n1, n2)) {
        bool found = false;
        auto p = matrix[n1.getid()].arches.begin();
        while (!matrix[n1.getid()].arches.end(p) && !found) {
            if (matrix[n1.getid()].arches.read(p)._to.getid() == n2.getid())  {
                found = true;
            }
            else  {
                p = matrix[n1.getid()].arches.next(p);
            }
        }
        if (found)  {
            archinfo<P> infoarco;
            infoarco.weight = weight;
            infoarco._to = n2;
            matrix[n1.getid()].arches.write(infoarco, p);
        }
    }
}

//metodo che restituisce il numero totale dei nodi inseriti nel grafo
template <class E, class P>
int listgraph<E, P>::numNodes() const {
    return (nodes);
}
//metodo che restituisce il totale degli archi nel grafo
template <class E, class P>
int listgraph<E, P>::numArches() const  {
    return (arches);
}

//FUNZIONI DI SERVIZIO____________________________________________________
//VERO SE LA MATRICE 'matrix' E' VUOTA
template <class E, class P>
bool listgraph<E, P>::isEmptyMatrix() const {
    return (matrix == nullptr);
}

//algoritmo di visita, crea un alista con tutti i nodi adiacenti e richiama la funzione dfs
template <class E, class P>
void listgraph<E, P>::dfs(node n) const {
  if (isNode(n))  {
    int visitato[dimension];
    for (int i = 0; i < dimension; i++) {
      if (!matrix[i].empty) { //se il nodo non e vuoto
        visitato[i] = 0; //nodo occupato
      }
      else  {
        visitato[i] = -1; //nodo nullo
      }
    }
  dfs(n, visitato);
  }
}

//algoritmo di visita che stampa tutti i nodi adiacenti a quello selezionato
template <class E, class P>
void listgraph<E, P>::dfs(node n, int *visitato) const  {
    //esamino il nodo
    cout << " node(" << readLabel(n) << ") --> ";
    //marco il nodo come visitato
    visitato[n.getid()] = 1;
    listnode l = this->adjacent(n); //inserisce tutti i nodi adicenti
    if (!l.empty()) {   //se ci sono nodi adiacenti
    
        for (auto p = l.begin(); !l.end(p); p = l.next(p))  { //controlla tutti i nodi adiacenti
          node i(l.read(p).getid());  
          if (visitato[i.getid()] == 0) { //se il nodo non e stato visitato 
            dfs(i, visitato);             //esegue ricorsivamente questa funzione
          }
        }
    }
}

#endif