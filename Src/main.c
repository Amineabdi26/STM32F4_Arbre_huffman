#include <stdint.h>
#include <stm32f446xx.h>
#include <stdio.h>
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "timer.h"
#include "huffman.h"
#include "text_comp_decomp.h"

    struct noeud* arbreHuffman[256] = {NULL};
    struct noeud* racine ;
    uint8_t texte[] = "Une banane";
    uint8_t texteCompress[TAILLE_MAX_COMPRESS] = {0};
    uint32_t tabCaractere[256] = {0};
    uint32_t nbrCaractereDifferent = 0;
    struct Entete entete;
    uint32_t nbrCaractereTotal = 0;
    char texteCompressBinaire[TAILLE_MAX_COMPRESS * 8] = {0}; // Chaîne pour le texte compressé en binaire
uint8_t rx ;
int main(void)
{

	GPIO_Init();
	USART1_Init();
	USART2_Init();
	SYSTICK_Init();
	USART1_TransmitChar('B');
	rx=USART1_ReceiveChar();
    // Calcul du nombre total de caractères dans le texte d'origine
    for (int i = 0; texte[i] != '\0'; i++) {
        nbrCaractereTotal++;
    }
    occurence(texte, tabCaractere);
    afficherOccurrencesUART(tabCaractere);
    creerFeuille(arbreHuffman, tabCaractere);
    for (int i = 0; i < 256; i++) {
        if (tabCaractere[i] > 0) {
            nbrCaractereDifferent++;
        }
    }
    afficherFeuilles(arbreHuffman);


    afficherTabArbreHuffman(arbreHuffman, nbrCaractereDifferent);

    triArbre(arbreHuffman, nbrCaractereDifferent);

    afficherTabArbreHuffman(arbreHuffman, nbrCaractereDifferent);

    racine=creerNoeud(arbreHuffman, &nbrCaractereDifferent);

    afficherTabArbreHuffman(arbreHuffman, nbrCaractereDifferent);

    parcourirArbre(racine);

    libererMemoireArbre(racine);

    printf("Codes de Huffman pour chaque caractere :\r\n");
    creerCode(racine, 0, 0);

    uint32_t tailleCompress = 0;
    compresserTexte(texte, racine, texteCompress, &tailleCompress);
    creerEntete(arbreHuffman, &entete, tailleCompress, nbrCaractereTotal);
    printf("En-tete : Taille = %d, Fichier compresse = %d, Nombre de caracteres = %x\r\n",
           entete.tailleEntete, entete.tailleCompress, entete.donnees);

    for (int i = 0; i < tailleCompress; i++) {
        printf("0x%02x ", texteCompress[i]);
    }
    printf("\r\n");

    compresserTexteEnBinaire(texte, racine, texteCompressBinaire);

    printf("Texte compresse en binaire : %s\n", texteCompressBinaire);
   // afficherFeuilles(arbreHuffman);
	while(1){
		for(uint32_t i = 0 ; i<100000; i++);
		SYSTICK_Delay(1000);
		//GPIOA->ODR ^= 1<<5;

		//printf("Hello\r\n");
	}
}


