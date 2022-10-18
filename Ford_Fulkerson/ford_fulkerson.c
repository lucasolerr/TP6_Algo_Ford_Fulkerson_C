#include "ford_fulkerson.h"

void calculsCapaciteesResiduelles(Graphe* g){
    for (int i = 0; i < g->ordre; i++) {
        for (int j = 0; j < g->ordre; j++) {
            g->matriceAdj[i][j].capaciteResiduelle = g->matriceAdj[i][j].capacite - g->matriceAdj[i][j].flot;
            g->matriceAdj[j][i].capaciteResiduelle = g->matriceAdj[j][i].capacite - g->matriceAdj[j][i].flot;
        }
    }
}

void majFlots(Graphe* graphe, int sommetFinal, int sommetInitial){
    int parcoursChemin = sommetFinal;
    int parcoursChemin2 = graphe->sommets[sommetFinal]->predecesseur;

    //pivot prendra la valeur minimum de la capacité sur les arcs
    int pivot = graphe->matriceAdj[parcoursChemin2][parcoursChemin].capaciteResiduelle;

    while (parcoursChemin2 != sommetInitial) {
        parcoursChemin = parcoursChemin2;
        parcoursChemin2 = graphe->sommets[parcoursChemin]->predecesseur;

        if(graphe->matriceAdj[parcoursChemin2][parcoursChemin].capaciteResiduelle < pivot){
            pivot = graphe->matriceAdj[parcoursChemin2][parcoursChemin].capaciteResiduelle;
        }
        //on affiche ce prédécesseur
    }

    parcoursChemin = sommetFinal;
    parcoursChemin2 = graphe->sommets[sommetFinal]->predecesseur;
    graphe->matriceAdj[parcoursChemin2][parcoursChemin].flot += pivot;

    while (parcoursChemin2 != sommetInitial) {
        parcoursChemin = parcoursChemin2;
        parcoursChemin2 = graphe->sommets[parcoursChemin]->predecesseur;

        graphe->matriceAdj[parcoursChemin2][parcoursChemin].flot += pivot;
    }

}

void ford_fulkerson(Graphe* g){

    while (dfsTrouverCheminAugmentant(g, g->ordre, g->sommetInitial) != -1) {
        dfs(g, g->ordre, g->sommetInitial);

        majFlots(g, g->sommetFinal, g->sommetInitial);

        calculsCapaciteesResiduelles(g);
    }

    int flotMaximal = 0;

    for (int i = 0; i < g->ordre; i++) {
        flotMaximal += g->matriceAdj[i][g->sommetFinal].flot;
    }

    printf("\nFlot maximal %d\n", flotMaximal);

    printf("\n    A B C D E F G\n");
    for (int i = 0; i < g->ordre; i++) {
        printf("%c : ", i + 65);
        for (int j = 0; j < g->ordre; j++) {
            printf("%d ", g->matriceAdj[i][j].flot);
        }
        printf("\n");
    }

}
