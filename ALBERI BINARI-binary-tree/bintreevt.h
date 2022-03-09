#ifndef BINTREEVT_H
#define BINTREEVT_H

#include <iostream>
#include <string>
#include "bintree.h"
using namespace std;

//DESTRA = right
//SINISTRA = left


template <class I>
class bintreevt : public bintree<I, int>
{
    //COSTANTE, -1 AL NODO INIZIALE SE NON CI SONO NODI
    static const int NIL = -1;

public:
    //ALIAS TIPI
    typedef typename bintree<I, int>::item item;
    typedef typename bintree<I, int>::node node;
    
    //DICHIARAZIONE TIPO CELLA
    struct cell
    {
        node parent;    //PADRE
        node left;      //FIGLIO SINISTRO
        node right;     //FIGLIO DESTRO
        item value;     //VALORE NODO
        int depth = 0;  //PROFONDITA'
    };

    typedef struct cell cell;

    //COSTRUTTORE DI DEFAULT 
    bintreevt();
    //COSTRUTTORE CON PARAMETRO
    bintreevt(int);
    //DISTRUTTORE
    ~bintreevt();

    //OPERATORI_____________________________________________________________________________________________________________

    //INIZIALIZA TUTTI I NODI DI SINISTRA, IMPOSTA IL NODO INIZIALE A -1, E IMPOSTA LIBERA E nNODI A 0
    void create();
    //VERO SE NON CI SONO NODI NELL'ALBERO
    bool empty() const;
    //RESTITUISCE LA RADICE
    node get_root() const;
    //RESTITUISCE IL PADRE DEL NODO INDICATO
    node parent(node) const;
    //RESTITUISCE IL FIGLIO SINISTRO DEL NODO INDICATO
    node sx(node) const;
    //RESTITUISCE IL FIGLIO DESTRO DEL NODO INDICATO
    node dx(node) const;
    //VERO SE IL FIGLIO SINISTRO DEL NODO INDICATO E' VUOTO
    bool sx_empty(node) const;
    //VERO SE IL FIGLIO DESTRO DEL NODO INDICATO E' VUOTO
    bool dx_empty(node) const;
    //RIMUOVE IL SOTTOALBERO CHE PARTE DAL NODO INDICATO
    void erase(node);
    //LEGGE L'ITEM DEL NODO
    item read(node) const;
    //SCRIVE L'ITEM DEL NODO
    void write(node, item);
    //CREA LA RADICE DELL'ALBERO
    void ins_root();
    //metodo che inserisce e alloca un figlio sinistro al nodo a cui si applica
    void ins_sx(node);
    //metodo che inserisce e alloca un figlio sinistro al nodo a cui si applica con un item
    void ins_sx(node, item);
    //metodo che inserisce e alloca un figlio destro al nodo a cui si applica
    void ins_dx(node);
    //metodo che inserisce e alloca un figlio destro al nodo a cui si applica con un item
    void ins_dx(node, item);

    //ALGORITMI DI VISITA_________________________________________
    //&^visite in dfs (depth first search)
    //preordine
    void preorder(node) const;
    //postordine
    void postorder(node) const;
    //simmetrica
    void inorder(node) const;
    //metodo che restituisce vero se il nodo e' foglia
    bool leaf(node) const;
    //metodo che restituisce vero se il nodo e' vuoto
    bool is_empty_node(node) const;
    //metodo che restituisce la profondita' del nodo a cui si applica
    int depth(node) const;
    //metodo che restituisce l'altezza dell'albero
    int depth() const;

private:
    int MAXLUNG;    //massima capienza
    cell *spazio;   //vettore di nodi
    int nNodi;      //totale nodi presenti
    node inizio;    //posizione della radice
    node libera;    //nodo libero
};

//COSTRUTTORE DI DEFAULT 
template <class I>
bintreevt<I>::bintreevt() {
    MAXLUNG = 100;
    spazio = new cell[MAXLUNG];
    this->create();
}

//COSTRUTTORE CON PARAMETRO
template <class I>
bintreevt<I>::bintreevt(int N) : MAXLUNG(N) //NON HO CAPITO
{
    spazio = new cell[nNodi];
    this->create();
}

//DISTRUTTORE
template <class I>
bintreevt<I>::~bintreevt()
{
    erase(inizio);
    delete[] spazio;
    spazio = nullptr;
}


//OPERATORI_______________________________________________

//INIZIALIZA TUTTI I NODI DI SINISTRA, IMPOSTA IL NODO INIZIALE A -1, E IMPOSTA LIBERA E nNODI A 0
template <class I>
void bintreevt<I>::create() {
    inizio = NIL;
    for (int i = 0; i < MAXLUNG; i++) {
        spazio[i].left = (i + 1) % MAXLUNG;
    }
    libera = 0;
    nNodi = 0;
}

//VERO SE NON CI SONO NODI NELL'ALBERO
template <class I>
bool bintreevt<I>::empty() const  {
    return (nNodi == 0);
}

//RESTITUISCE LA RADICE
template <class I>
typename bintreevt<I>::node bintreevt<I>::get_root() const  {
    return (inizio);
}

//RESTITUISCE IL PADRE DEL NODO INDICATO
template <class I>
typename bintreevt<I>::node bintreevt<I>::parent(node n) const  {
    if (n != inizio)  {
        return (spazio[n].parent);      //SPAZIO[N] E' UNA POSIZIONE CHE EQUIVALE A U NODO, E DI UN NODO PUOI PRENDERE UN SUO CAMPO CON .PARENT
    }
    else  {
        return (n);
    }
}

//RESTITUISCE IL FIGLIO SINISTRO DEL NODO INDICATO
template <class I>
typename bintreevt<I>::node bintreevt<I>::sx(node n) const  {
    return (spazio[n].left);
}
//RESTITUISCE IL FIGLIO DESTRO DEL NODO INDICATO
template <class I>
typename bintreevt<I>::node bintreevt<I>::dx(node n) const  {
    return (spazio[n].right);
}

//VERO SE IL FIGLIO SINISTRO DEL NODO INDICATO E' VUOTO
template <class I>
bool bintreevt<I>::sx_empty(node n) const {
    return (spazio[n].left == NIL);
}
//VERO SE IL FIGLIO DESTRO DEL NODO INDICATO E' VUOTO
template <class I>
bool bintreevt<I>::dx_empty(node n) const {
    return (spazio[n].right == NIL);
}

//CREA LA RADICE DELL'ALBERO
template <class I>
void bintreevt<I>::ins_root() {
    if (inizio == NIL)  {
        inizio = libera;
        libera = spazio[libera].left;
        spazio[inizio].left = NIL;
        spazio[inizio].right = NIL;
        nNodi++;
    }
}

//metodo che inserisce e alloca un figlio sinistro al nodo a cui si applica
template <class I>
void bintreevt<I>::ins_sx(node n) {
    if (inizio == NIL)  {
        cout << "\nalbero vuoto\n";
        return;
    }
    if (n == NIL) {
        cout << "\nnodo vuoto\n";
        return;
    }
    if (spazio[n].left != NIL)  {
        cout << "\nsinistro occupato\n";
        return;
    }
    if (nNodi >= MAXLUNG) {
        cout << "\nalbero pieno\n";
        return;
    }
    node q = libera;
    libera = spazio[libera].left;
    spazio[n].left = q;
    spazio[q].left = NIL;
    spazio[q].parent = n;
    spazio[q].right = NIL;
    nNodi++;
}

//metodo che inserisce e alloca un figlio sinistro al nodo a cui si applica con un item
template <class I>
void bintreevt<I>::ins_sx(node n, item v)
{
    if (inizio == NIL)
    {
        cout << "\nalbero vuoto\n";
        return;
    }
    if (n == NIL)
    {
        cout << "\nnodo vuoto\n";
        return;
    }
    if (spazio[n].left != NIL)
    {
        cout << "\nsinistro occupato\n";
        return;
    }
    if (nNodi >= MAXLUNG)
    {
        cout << "\nalbero pieno\n";
        return;
    }
    node q = libera;
    libera = spazio[libera].left;
    spazio[n].left = q;
    spazio[q].left = NIL;
    spazio[q].parent = n;
    spazio[q].right = NIL;
    spazio[q].value = v;
    nNodi++;
}

//metodo che inserisce e alloca un figlio destro al nodo a cui si applica
template <class I>
void bintreevt<I>::ins_dx(node n)
{
    if (inizio == NIL)
    {
        cout << "\nalbero vuoto\n";
        return;
    }
    if (n == NIL)
    {
        cout << "\nnodo vuoto\n";
        return;
    }
    if (spazio[n].right != NIL)
    {
        cout << "\ndestro occupato\n";
        return;
    }
    if (nNodi >= MAXLUNG)
    {
        cout << "\nalbero pieno\n";
        return;
    }
    node q = libera;
    libera = spazio[libera].left;
    spazio[n].right = q;
    spazio[q].left = NIL;
    spazio[q].parent = n;
    spazio[q].right = NIL;
    nNodi++;
}

//metodo che inserisce e alloca un figlio destro al nodo a cui si applica con un item
template <class I>
void bintreevt<I>::ins_dx(node n, item v)
{
    if (inizio == NIL)
    {
        cout << "\nalbero vuoto\n";
        return;
    }
    if (n == NIL)
    {
        cout << "\nnodo vuoto\n";
        return;
    }
    if (spazio[n].right != NIL)
    {
        cout << "\ndestro occupato\n";
        return;
    }
    if (nNodi >= MAXLUNG)
    {
        cout << "\nalbero pieno\n";
        return;
    }
    node q = libera;
    libera = spazio[libera].left;
    spazio[n].right = q;
    spazio[q].left = NIL;
    spazio[q].parent = n;
    spazio[q].right = NIL;
    spazio[q].value = v;
    nNodi++;
}

//RIMUOVE IL SOTTOALBERO CHE PARTE DAL NODO INDICATO
template <class I>
void bintreevt<I>::erase(node n)  {
    if (n != NIL) {
        if (!sx_empty(n)) {             
            erase(spazio[n].left);    //FUNZIONE RICHIAMATA RICORSIVAMENTE SUL NODO SINISTRO
        }
        if (!dx_empty(n)) {
            erase(spazio[n].right);   //FUNZIONE RICHIAMATA RICORSIVAMENTE SUL NODO DESTRO
        }
        if (n != inizio)  {
            node p = parent(n);
            if (spazio[p].left == n)  {   //IN BASE A QUALE FIGLIO E' IL NODO DA ELIMINARE VIENE INIZIALIZZATO IL FIGLIO
                spazio[p].left = NIL;
            }
            else  {
                spazio[p].right = NIL;
            }
        }
        else  {
            inizio = NIL;
        }
        nNodi--;
        spazio[n].left = libera;
        libera = n;
    }
}

//LEGGE L'ITEM DEL NODO
template <class I>
typename bintreevt<I>::item bintreevt<I>::read(node n) const  {
    item value;
    if (n != NIL) {
        return (spazio[n].value);
    }
    return (value);
}

//SCRIVE L'ITEM DEL NODO
template <class I>
void bintreevt<I>::write(node n, item v)  {
    if (n != NIL) {
        spazio[n].value = v;
    }
    else  {
        cout << "\nnodo nullo\n";
    }
}

//ALGORITMI DI VISITA_________________________________________
//preordine
template <class I>
void bintreevt<I>::preorder(node n) const
{
    if (n == NIL)
    {
        return;
    }
    cout << " " << read(n) << " ";
    preorder(spazio[n].left);
    preorder(spazio[n].right);
}
//postordine
template <class I>
void bintreevt<I>::postorder(node n) const
{
    if (n == NIL)
    {
        return;
    }
    postorder(spazio[n].left);
    postorder(spazio[n].right);
    cout << " " << read(n) << " ";
}
//simmetrica
template <class I>
void bintreevt<I>::inorder(node n) const
{
    if (n == NIL)
    {
        return;
    }
    inorder(spazio[n].left);
    cout << " " << read(n) << " ";
    inorder(spazio[n].right);
}

//metodo che restituisce vero se il nodo e' foglia
template <class I>
bool bintreevt<I>::leaf(node n) const
{
    return (sx_empty(n) && dx_empty(n));
}
//metodo che restituisce vero se il nodo e' vuoto
template <class I>
bool bintreevt<I>::is_empty_node(node n) const
{
    return (n == NIL);
}

//metodo che restituisce la profondita' del nodo a cui si applica
template <class I>
int bintreevt<I>::depth(node sub_root) const
{
    if (sub_root == NIL)
    {
        return (-1); //nodo nullo
    }
    int left_depth = depth(spazio[sub_root].left);
    int right_depth = depth(spazio[sub_root].right);
    if (left_depth > right_depth)
    {
        return (left_depth + 1);
    }
    else
    {
        return (right_depth + 1);
    }
}

//metodo che restituisce l'altezza dell'albero
template <class I>
int bintreevt<I>::depth() const
{
    int d = 0;
    if (!empty())
    {
        d = depth(get_root());
    }
    else
    {
        d = -1;
    }
    return (d);
}

#endif