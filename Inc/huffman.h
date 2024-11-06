#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// Définition de la taille maximale pour le texte compressé
#define TAILLE_MAX_COMPRESS 500

// Structure pour l'en-tête
struct noeud {
    uint8_t c;               // Caractère
    uint32_t occurence;      // Nombre d'occurrences
    uint32_t code;           // Code binaire dans l'arbre
    uint32_t tailleCode;     // Nombre de bits du code
    struct noeud* gauche;    // Lien vers le noeud gauche
    struct noeud* droite;    // Lien vers le noeud droit
};



// Prototypes des fonctions
void occurence(uint8_t* chaine, uint32_t tab[256]);
void afficherOccurrencesUART(uint32_t tab[256]);
void creerFeuille(struct noeud* arbre[256], uint32_t tab[256]);
void triArbre(struct noeud* arbre[256], uint32_t taille);
void afficherTabArbreHuffman(struct noeud* arbre[256], uint32_t taille);
void afficherFeuilles(struct noeud* arbre[256]);
struct noeud* creerNoeud(struct noeud* arbre[256], uint32_t* taille);
void parcourirArbre(struct noeud* ptrNoeud);
void libererMemoireArbre(struct noeud* ptrNoeud);
void creerCode(struct noeud* ptrNoeud, uint32_t code, uint32_t taille);


#endif // HUFFMAN_H
