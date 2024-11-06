#ifndef TEXT_COMP_DECOMP_H
#define TEXT_COMP_DECOMP_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"

struct Entete {
    uint16_t tailleEntete;
    uint16_t tailleCompress;
    uint16_t nbrCaractereTotal;
    uint8_t donnees[TAILLE_MAX_COMPRESS];
};

struct noeud* getAddress(struct noeud* ptrNoeud, uint8_t caractere);
void compresserTexte(uint8_t* texte, struct noeud* racine, uint8_t* texteCompress, uint32_t* tailleCompress);
void creerEntete(struct noeud* arbre[256], struct Entete* entete, uint32_t tailleCompress, uint32_t nbrCaractereTotal);
void compresserTexteEnBinaire(uint8_t* texte, struct noeud* racine, char* texteCompressBinaire);



#endif // TEXT_COMP_DECOMP_H
