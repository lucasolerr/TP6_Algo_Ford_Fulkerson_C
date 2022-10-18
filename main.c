#include "stdio.h"
#include "Graphe/Graphe.h"
#include "Dfs/dfs.h"
#include "Ford_Fulkerson/ford_fulkerson.h"




int main() {
    Graphe* g = lire_graphe("../binaries/graphe1_TP6.txt");

    //afficher le graphe
    graphe_afficher(g);

    //Appel fonction globale permettant de lancer l'algorithme Ford-Fulkerson
    ford_fulkerson(g);

    return 0;
}