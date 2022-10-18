#include "Graphe.h"

/* La construction du reseau peut se faire à partir d'un fichier dont le nom est passe en parametre
Le fichier contient : ordre, taille, orientation (0 ou 1)et liste des arcs. */
Graphe* lire_graphe(char *nomFichier) {
    Graphe* graphe;
    FILE* ifs = fopen(nomFichier, "r");
    int ordre;

    if (!ifs) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    fscanf(ifs, "%d", &ordre);

    graphe = (Graphe*) malloc(sizeof(Graphe));

    graphe->sommets = (pSommet*) malloc(ordre * sizeof(pSommet*));

    for (int i = 0; i < ordre; i++) {
        graphe->sommets[i] = malloc(sizeof(pSommet));
        fscanf(ifs, "%d", &graphe->sommets[i]->valeur);
    }

    graphe->sommetInitial = graphe->sommets[0]->valeur;
    graphe->sommetFinal = graphe->sommets[ordre - 1]->valeur;


    graphe->ordre = ordre;

    graphe->matriceAdj = malloc(sizeof(Arrete*) * ordre);
    for (int i = 0; i < ordre; i++) {
        (graphe->matriceAdj[i]) = malloc(sizeof(Arrete) * ordre);
    }

    for (int i = 0; i < ordre; i++) {
        for (int j = 0; j < ordre; j++) {
            fscanf(ifs, "%d", &graphe->matriceAdj[i][j].capacite);
            graphe->matriceAdj[i][j].flot = 0;
            graphe->matriceAdj[i][j].capaciteResiduelle = graphe->matriceAdj[i][j].capacite - graphe->matriceAdj[i][j].flot;
        }
    }


    return graphe;
}

/*affichage du graphe avec les successeurs de chaque sommet */
void graphe_afficher(Graphe *graphe) {
    printf("graphe\n");

    printf("ordre = %d\n", graphe->ordre);

    for (int i = 0; i < graphe->ordre; i++) {
        printf("%d ", graphe->sommets[i]->valeur);
    }

    printf("\nMatrice d'adjacence :\n");

    for (int i = 0; i < graphe->ordre; i++) {
        for (int j = 0; j < graphe->ordre; j++) {

            printf("%d ", graphe->matriceAdj[i][j].capacite);

        }
        printf("\n");
    }
}