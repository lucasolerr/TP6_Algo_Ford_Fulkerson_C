#include "stdio.h"
#include "Graphe/Graphe.h"




int main() {
    Graphe* g = lire_graphe("../binaries/graphe1_TP6.txt");

    //afficher le graphe
    graphe_afficher(g);

    return 0;
}