#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct Arrete {
    int s1, s2, poids, couleur;
    struct Arrete* next;
} Arrete;



/* Structure d'un sommet*/
struct Sommet
{
    //numéro du sommet / Lettre du sommet
    char valeur;
    //si le sommet est marqué = 1 sinon 0
    char couleur;
};

/* Alias de pointeur sur un Sommet */
typedef struct Sommet* pSommet;

/* Alias d'un Graphe */
typedef struct Graphe
{
    int orientation;
    int ordre;
    char* sommets;
    int** matriceAdj;
} Graphe;

// creer le graphe
Graphe* CreerGraphe(int ordre);

/* La construction du reseau peut se faire à partir d'un fichier dont le nom est passe en parametre
Le fichier contient : ordre, taille, orientation (0 ou 1)et liste des arcs. */
Graphe * lire_graphe(char * nomFichier);

// Ajouter l'arete entre les sommets s1 et s2 du graphe
pSommet* CreerArete(pSommet* sommet,int s1,int s2, int poids);

/* affichage des successeurs du sommet num*/
void afficher_successeurs(pSommet * sommet, int num);

/*affichage du graphe avec les successeurs de chaque sommet */
void graphe_afficher(Graphe* graphe);

void afficherListe(Arrete* liste);

void freeListe(Arrete* liste);

#endif // GRAPHE_H_INCLUDED
