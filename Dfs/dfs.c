#include "dfs.h"

File fileVide() {
    File F;
    //On alloue dynamiquement la liste
    F = (File) malloc(sizeof(struct file));
    if (F == NULL) printf("erreur allocation fileVide");
    //La liste est vide donc de longueur 0
    F->longueur = 0;
    //La liste est vide donc ne contient aucune cellule
    F->tete = F->queue = NULL;
    return (F);
}

int longueur(File F) {
    if (F == NULL)printf("file existe pas - longueur");
    return (F->longueur);
}

void enfiler(File F, typage element) {
    Cellule cellule;
    if (F == NULL) printf("file existe pas - enfiler");

    //On alloue l'élément de la liste dynamiquement
    cellule = (Cellule) malloc(sizeof(struct cellule));
    //On vérifie l'allocation
    if (cellule == NULL) printf("erreur allocation memoire - enfiler");

    //On assigne à l'élément de la liste le numéro de sommet passé en paramètre
    cellule->element = element;
    //FIFO donc on va défiler par la tête donc on enfile en queue de liste soit le suivant = NULL
    cellule->suivant = NULL;
    //Si la liste est vide : Cellule = tête de liste et aussi queue de liste car 1 élement dans la liste
    if (longueur(F) == 0) {
        F->tete = F->queue = cellule;
    } else {
        //Sinon on part de la queue de la liste et on ajoute notre cellule
        F->queue->suivant = cellule;
        //On fait pointer la queue de la liste vers notre cellule
        F->queue = cellule;
    }
    //On augmente donc la taille de la liste de 1
    ++(F->longueur);
}

typage defilementLIFO(File F) {
    Cellule cellule;
    Cellule temp;
    typage element;
    //La file n'existe pas
    if (F == NULL || longueur(F) == 0) printf("File existe pas - defilement");

    //On assigne une cellule temporaire à la cellule de queue de file (LIFO)
    cellule = F->queue;
    //On assigne une cellule temporaire à la cellule de tête de file
    //pour pouvoir parcourir la file jusqu'à l'avant-dernier élément
    temp = F->tete;
    //On assigne au temporaire element le sommet de la cellule en tête de file
    element = cellule->element;

    //Si la file est de longueur 1
    if (longueur(F) == 1) {
        //On vide la file car l'objectif de cette fonction est d'enlever un élément de la liste
        //soit dans ce if de la mettre à 0
        F->tete = F->queue = NULL;
    } else {
        //Sinon on parcours la liste jusqu'à l'avant-dernière cellule
        while (temp->suivant != cellule){
            temp = temp->suivant;
        }
        //La nouvelle queue de liste est l'avant-dernière cellule
        F->queue = temp;
        //Cette cellule n'a donc plus de successeur car on le défile
        F->queue->suivant = NULL;
    }
    //On libère l'ex-queue de liste
    free(cellule);
    //On réduit la longueur de la file
    --(F->longueur);
    //On retourne le sommet qui a été enlevé de la file
    return (element);
}

void dfs(Graphe* graphe, int ordre, typage sommetInitial) {
    /*Initialisation de la couleur des sommets*/
    /*N=Noir, deja vu.  B=Blanc a voir*/
    /* !!! A noter : Ce parcours DFS est visité selon l'ordre inverse de ses numéros !!! */
    int i = 0;
    //Création d'une file vide
    File file = fileVide();

    for (i = 0; i < ordre; i++) {
        //On assigne à chaque sommet la couleur 'Blanche'
        graphe->sommets[i]->couleur = 'B';
        //On initialise ses prédécesseurs à une valeur arbitraire '-1' équivalente à NULL
        graphe->sommets[i]->predecesseur = -1;
    }

    //On met dans la file le 1er sommet depuis lequel on souhaite faire le parcours DFS
    enfiler(file, sommetInitial);

    //Tant que la file est pleine
    while (longueur(file)) {
        //On enlève en queue une cellule
        i = defilementLIFO(file);
        //i contient le numéro de sommet qui a été défilé
        if (graphe->sommets[i]->couleur == 'B') {
            //Si i était non découvert
            for (int j = 0; j < ordre; j++) {
                if (graphe->matriceAdj[i][j].capacite != 0 && graphe->matriceAdj[i][j].capaciteResiduelle > 0 && graphe->sommets[j]->predecesseur == -1) {
                    enfiler(file, j);
                    graphe->sommets[j]->predecesseur = i;
                }
            }

            //le sommet i est de couleur noire
            graphe->sommets[i]->couleur = 'N';
        }
    }
}

void fonctionPredecesseurs(pSommet* pSommet, int ordre, int sommetInitial){
    //boucle for pour parcourir tous les sommets
    for (int i = 0; i < ordre; ++i) {
        //Si le sommet en question n'a pas déjà de prédécesseur alors
        if (pSommet[i]->predecesseur != -1) {
            //on met un temporaire à la valeur de ce sommet
            int tempPred = i;

            //on l'affiche
            printf("\n%d", i);

            //Fonction récursive qui permet de parcourir les prédécesseurs de ce sommet
            //Tant que le prédécesseur est != du sommet initial
            while (tempPred != sommetInitial) {
                //le temporaire prend la valeur du prédécesseur du n-1 sommet
                tempPred = pSommet[tempPred]->predecesseur;
                //on affiche ce prédécesseur
                printf(" <-- %d", tempPred);
            }
            //on saute une ligne entre chaque branche de l'arborescence
            printf("\n");
        }
    }
}


int dfsTrouverCheminAugmentant(Graphe* graphe, int ordre, typage sommetInitial) {
    /*Initialisation de la couleur des sommets*/
    /*N=Noir, deja vu.  B=Blanc a voir*/
    /* !!! A noter : Ce parcours DFS est visité selon l'ordre inverse de ses numéros !!! */
    int i = 0;
    //Création d'une file vide
    File file = fileVide();

    for (i = 0; i < ordre; i++) {
        //On assigne à chaque sommet la couleur 'Blanche'
        graphe->sommets[i]->couleur = 'B';
        //On initialise ses prédécesseurs à une valeur arbitraire '-1' équivalente à NULL
        graphe->sommets[i]->predecesseur = -1;
    }

    //On met dans la file le 1er sommet depuis lequel on souhaite faire le parcours DFS
    enfiler(file, sommetInitial);

    //Tant que la file est pleine
    while (longueur(file)) {
        //On enlève en queue une cellule
        i = defilementLIFO(file);
        //i contient le numéro de sommet qui a été défilé
        if (graphe->sommets[i]->couleur == 'B') {
            //Si i était non découvert
            for (int j = 0; j < ordre; j++) {
                if (graphe->matriceAdj[i][j].capacite != 0 && graphe->matriceAdj[i][j].capaciteResiduelle > 0 && graphe->sommets[j]->predecesseur == -1) {
                    enfiler(file, j);
                    graphe->sommets[j]->predecesseur = i;
                }
            }

            //le sommet i est de couleur noire
            graphe->sommets[i]->couleur = 'N';
        }
    }
    return graphe->sommets[graphe->sommetFinal]->predecesseur;
}