#ifndef TP6_ALGO_FORD_FULKERSON_C_DFS_H
#define TP6_ALGO_FORD_FULKERSON_C_DFS_H

#include "../Graphe/Graphe.h"

typedef int typage;

struct cellule {
    typage element;
    struct cellule *suivant;
};

typedef struct cellule* Cellule;

struct file {
    int longueur;
    Cellule tete;
    Cellule queue;
};

typedef struct file* File;


File fileVide();
int longueur(File F);
void enfiler(File F, typage element);
typage tete(File F);
void defiler(File F);
typage defilement(File F);

void fonctionPredecesseurs(pSommet* pSommet, int ordre, int sommetInitial);
void dfs(Graphe* graphe, int ordre, typage sommetInitial);
int dfsTrouverCheminAugmentant(Graphe* graphe, int ordre, typage sommetInitial);
typage defilementLIFO(File F);


#endif
