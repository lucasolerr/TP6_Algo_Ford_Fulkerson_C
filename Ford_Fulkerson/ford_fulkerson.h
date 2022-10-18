#ifndef TP6_ALGO_FORD_FULKERSON_C_FORD_FULKERSON_H
#define TP6_ALGO_FORD_FULKERSON_C_FORD_FULKERSON_H

#include "../Graphe/Graphe.h"
#include "../Dfs/dfs.h"

void calculsCapaciteesResiduelles(Graphe* g);

void majFlots(Graphe* graphe, int sommetFinal, int sommetInitial);

void ford_fulkerson(Graphe* g);


#endif
