#include "ford_fulkerson.h"

void ford_fulkerson(Graphe* g){
    //On part d'un flot nul ou réalisable
    for (int i = 0; i < g->ordre; i++) {
        for(int j = 0; j < g->ordre; j++){
            g->matriceAdj[i][j].flot = 0;
        }
    }
}
