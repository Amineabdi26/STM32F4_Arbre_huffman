#include "text_comp_decomp.h"




void compresserTexte(uint8_t* texte, struct noeud* racine, uint8_t* texteCompress, uint32_t* tailleCompress) {
    *tailleCompress = 0;
    uint32_t positionBit = 0;

    for (int i = 0; texte[i] != '\0'; i++) {
        struct noeud* noeudChar = getAddress(racine, texte[i]);

        if (noeudChar == NULL) {
            printf("Erreur : caractere '%c' non trouve dans l'arbre de Huffman\r\n", texte[i]);
            return;
        }

        // Parcours de chaque bit du code de Huffman pour le caractère
        for (int j = noeudChar->tailleCode - 1; j >= 0; j--) {
            // Décale le code pour extraire le bit le plus significatif
            uint8_t bit = (noeudChar->code >> j) & 1;

            // Ajoute le bit au bon emplacement dans texteCompress
            texteCompress[positionBit / 8] |= (bit << (7 - (positionBit % 8)));
            positionBit++;
        }
    }
    *tailleCompress = (positionBit + 7) / 8;
}

// Fonction pour créer l'en-tête
void creerEntete(struct noeud* arbre[256], struct Entete* entete, uint32_t tailleCompress, uint32_t nbrCaractereTotal) {
    entete->tailleCompress = tailleCompress;
    entete->nbrCaractereTotal = nbrCaractereTotal;
    int pos = 0;

    // Ajouter chaque caractère avec son code Huffman et sa taille dans l'en-tête
    for (int i = 0; i < 256; i++) {
        if (arbre[i] != NULL) {
            entete->donnees[pos++] = arbre[i]->c;
            entete->donnees[pos++] = arbre[i]->tailleCode;

            // Stocke chaque bit du code dans l'en-tête
            for (int j = arbre[i]->tailleCode - 1; j >= 0; j--) {
                uint8_t bit = (arbre[i]->code >> j) & 1;
                entete->donnees[pos] = (entete->donnees[pos] << 1) | bit;
            }
            pos++;
        }
    }
    entete->tailleEntete = pos;
}


void compresserTexteEnBinaire(uint8_t* texte, struct noeud* racine, char* texteCompressBinaire) {
    texteCompressBinaire[0] = '\0';

    for (int i = 0; texte[i] != '\0'; i++) {
        struct noeud* noeudChar = getAddress(racine, texte[i]);

        if (noeudChar == NULL) {
            printf("Erreur : caractere '%c' non trouve dans l'arbre de Huffman\r\n", texte[i]);
            return;
        }

        for (int j = noeudChar->tailleCode - 1; j >= 0; j--) {
            uint8_t bit = (noeudChar->code >> j) & 1;
            strncat(texteCompressBinaire, bit ? "1" : "0", 1); // Ajoute '1' ou '0' à la chaîne
        }
    }
}
