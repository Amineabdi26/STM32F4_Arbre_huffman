#include "huffman.h"

// Fonction pour compter les occurrences des caractères
void occurence(uint8_t* chaine, uint32_t tab[256]) {
    for (int i = 0; i < 256; i++) {
        tab[i] = 0;
    }
    while (*chaine) {
        tab[*chaine]++;
        chaine++;
    }
}

void afficherOccurrencesUART(uint32_t tab[256]) {

    printf("Caractere\tOccurrences\r\n");
    printf("-------------------------\r\n");

    for (int i = 0; i < 256; i++) {
        if (tab[i] > 0) {
            printf("%c\t\t%d\r\n", i, tab[i]);
        }
    }
}


// Fonction pour créer les feuilles de l'arbre de Huffman
void creerFeuille(struct noeud* arbre[256], uint32_t tab[256]) {
	uint32_t j = 0 ;
    for (int i = 0; i < 256; i++) {
        if (tab[i] > 0) { // Si le caractère a au moins une occurrence
            // Allocation dynamique d'une feuille
            struct noeud* feuille = (struct noeud*)malloc(sizeof(struct noeud));
            if (feuille == NULL) {
                printf("Erreur d'allocation mémoire\n");
                return;
            }
            feuille->c = (uint8_t)i;
            feuille->occurence = tab[i];
            feuille->gauche = NULL;
            feuille->droite = NULL;
            feuille->code = 0;
            feuille->tailleCode = 0;
            arbre[j] = feuille;
            j++;
        }
    }
}

void afficherFeuilles(struct noeud* arbre[256]) {
    printf("`\nFeuilles de l'arbre de Huffman :\r\n");
    printf("Caractere\tOccurrences\tCode\tTaille Code\tAdresse\t\tGauche\t\tDroite\r\n");
    printf("---------------------------------------------------------------------------------------\r\n");

    for (int i = 0; i < 256; i++) {
        if (arbre[i] != NULL) {
            printf("%c\t\t%d\t\t%x\t%d\t\t%lx\t%lx\t%lx\r\n",
                   arbre[i]->c,
                   arbre[i]->occurence,
                   arbre[i]->code,
                   arbre[i]->tailleCode,
                   arbre[i],
                   arbre[i]->gauche,
                   arbre[i]->droite);
        }
    }
}

void triArbre(struct noeud* arbre[256], uint32_t taille) {
    struct noeud* f;
    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            if (arbre[j]->occurence > arbre[j + 1]->occurence) {
                f = arbre[j];
                arbre[j] = arbre[j + 1];
                arbre[j + 1] = f;
            }
        }
    }
}


void afficherTabArbreHuffman(struct noeud* arbre[256], uint32_t taille) {
    printf("\nAffichage de %d elements de l'arbre de Huffman :\r\n", taille);
    printf("Caractere\tOccurrences\tCode\tTaille Code\tAdresse\t\tGauche\t\tDroite\r\n");
    printf("---------------------------------------------------------------------------------------\r\n");

    for (uint32_t i = 0; i < taille; i++) {
        if (arbre[i] != NULL) {
            printf("%c\t\t%d\t\t%x\t%d\t\t%lx\t%lx\t%lx\r\n",
                   arbre[i]->c,
                   arbre[i]->occurence,
                   arbre[i]->code,
                   arbre[i]->tailleCode,
                   arbre[i],
                   arbre[i]->gauche,
                   arbre[i]->droite);
        }
    }
}


// Fonction pour créer des nœuds jusqu'à obtenir la racine de l'arbre de Huffman
struct noeud* creerNoeud(struct noeud* arbre[256], uint32_t* taille) {
    while (*taille > 1) {
        triArbre(arbre, *taille);
        struct noeud* newNoeud = (struct noeud*)malloc(sizeof(struct noeud));
        newNoeud->gauche = arbre[0];
        newNoeud->droite = arbre[1];
        newNoeud->occurence = arbre[0]->occurence + arbre[1]->occurence;
        newNoeud->code = 0;
        newNoeud->tailleCode = 0;
        newNoeud->c = 0;

        arbre[0] = newNoeud;
        arbre[1] = arbre[*taille - 1];
        (*taille)--;
    }

    return arbre[0];
}

void parcourirArbre(struct noeud* ptrNoeud) {
    if (ptrNoeud == NULL) {
        return;
    }

    if (ptrNoeud->gauche == NULL && ptrNoeud->droite == NULL) {
        printf("Je suis une feuille : '%c' avec %d occurrences.\r\n", ptrNoeud->c, ptrNoeud->occurence);
    }
    else {
        printf("Je suis un nœud avec %d occurrences.\r\n", ptrNoeud->occurence);
        parcourirArbre(ptrNoeud->gauche);
        parcourirArbre(ptrNoeud->droite);
    }
}

// Fonction pour libérer la mémoire de l'arbre de Huffman
void libererMemoireArbre(struct noeud* ptrNoeud) {
    if (ptrNoeud == NULL) {
        return;
    }
    libererMemoireArbre(ptrNoeud->gauche);
    libererMemoireArbre(ptrNoeud->droite);
    free(ptrNoeud);
}

void creerCode(struct noeud* ptrNoeud, uint32_t code, uint32_t taille) {
    if (ptrNoeud == NULL) {
        return;
    }
    if (ptrNoeud->gauche == NULL && ptrNoeud->droite == NULL) {
        ptrNoeud->tailleCode = taille;
        ptrNoeud->code = code;
        printf("Caractere : '%c' \t Code : ", ptrNoeud->c);
        for (int i = taille - 1; i >= 0; i--) {
            printf("%d", (code >> i) & 1);
        }
        printf(" \t Taille : %d bits\r\n", taille);
    } else {
        creerCode(ptrNoeud->droite, code << 1, taille + 1);
        creerCode(ptrNoeud->gauche, (code << 1) + 1, taille + 1);
    }
}

// Fonction pour retrouver le nœud correspondant à un caractère dans l'arbre de Huffman
struct noeud* getAddress(struct noeud* ptrNoeud, uint8_t caractere) {
    if (ptrNoeud == NULL) {
        return NULL;
    }
    if (ptrNoeud->gauche == NULL && ptrNoeud->droite == NULL && ptrNoeud->c == caractere) {
        return ptrNoeud;
    }

    struct noeud* gauche = getAddress(ptrNoeud->gauche, caractere);
    if (gauche != NULL) return gauche;

    return getAddress(ptrNoeud->droite, caractere);
}


