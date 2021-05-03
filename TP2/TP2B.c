/**
 * Auteur : Nicolas Levasseur
 *
 * Ce programme trouve a quel acide amine (ou a quelle ponctuation) le codon
 * de nucleotide entre par l'utilisateur correspond et montre le resultat. On
 * gere les cas ou on ne connait pas l'acide amine et les cas ou le codon
 * entre est invalide. On repete le processus jusqu'a un arret utilisateur.
 */
#include <stdio.h>

// Macro pour encoder 3 lettres de maniere unique
#define DEF_ACIDE_AMINE(a, b, c) a * 65536 + b * 256 + c
#define UUU DEF_ACIDE_AMINE('U', 'U', 'U')
#define UUC DEF_ACIDE_AMINE('U', 'U', 'C')
#define UGU DEF_ACIDE_AMINE('U', 'G', 'U')
#define UGC DEF_ACIDE_AMINE('U', 'G', 'C')
#define CUU DEF_ACIDE_AMINE('C', 'U', 'U')
#define CUA DEF_ACIDE_AMINE('C', 'U', 'A')
#define CAU DEF_ACIDE_AMINE('C', 'A', 'U')
#define CAC DEF_ACIDE_AMINE('C', 'A', 'C')
#define GUU DEF_ACIDE_AMINE('G', 'U', 'U')
#define GUC DEF_ACIDE_AMINE('G', 'U', 'C')
#define GAU DEF_ACIDE_AMINE('G', 'A', 'U')
#define GAC DEF_ACIDE_AMINE('G', 'A', 'C')
#define AUG DEF_ACIDE_AMINE('A', 'U', 'G')
#define GUG DEF_ACIDE_AMINE('G', 'U', 'G')
#define UAA DEF_ACIDE_AMINE('U', 'A', 'A')
#define UAG DEF_ACIDE_AMINE('U', 'A', 'G')

/**
 * Cette fonction trouve a quel acide amine correspond le codon entre et donne
 * le reslutat de ce decodage a l'utilisateur. La fonction gere aussi les
 * cas ou l'acide amine est inconnu ou impossible.
 *
 * c1: Premier caractere du codon.
 * c2: Deuxieme caractere du codon.
 * c3: Troisieme caractere du codon.
 */
void decode(char c1, char c2, char c3) {
    // On declare la variable qui va contenir le decodage du codon
    char* mes;

    // On teste si le codon entre existe
    if (c1 != 'U' && c1 != 'C' && c1 != 'G' && c1 != 'A') {
        mes = "ne forme pas un codon";
    } else if (c2 != 'U' && c2 != 'C' && c2 != 'G' && c2 != 'A') {
        mes = "ne forme pas un codon";
    } else if (c3 != 'U' && c3 != 'C' && c3 != 'G' && c3 != 'A') {
        mes = "ne forme pas un codon";
    }
    // On trouve la signification du codon donne
    else {
        switch (DEF_ACIDE_AMINE(c1, c2, c3)) {
            case UUU:
            case UUC:
                mes = "forme le codon de la phenylalanine";
                break;

            case UGU:
            case UGC:
                mes = "forme le codon de la cysteine";
                break;

            case CUU:
            case CUA:
                mes = "forme le codon de la leuncine";
                break;

            case CAU:
            case CAC:
                mes = "forme le codon de l'histine";
                break;

            case GUU:
            case GUC:
                mes = "forme le codon de la valine";
                break;

            case GAU:
            case GAC:
                mes = "forme le codon de l'asparagine";
                break;

            case AUG:
            case GUG:
                mes = "forme un codon d'initialisation";
                break;

            case UAA:
            case UAG:
                mes = "forme un codon de terminaison";
                break;

            default:
                mes = "forme un acide amine inconnu";
                break;
        }  // end switch
    }      // end else

    // On montre le resultat a l'utilisateur
    printf("Le triplet %c%c%c %s.\n", c1, c2, c3, mes);
}

int main() {
    // On declare nos variables contenant les reponses de l'utilisateur
    char c1, c2, c3, rep;

    // On effectue des iterations tant que l'utilisateur le demande
    do {
        // On demande a l'utilisateur d'entrer la chaine de nucleotides
        printf("Entrez le codon de nucleotides qu'on veux etudier:\n");
        scanf(" %c%c%c", &c1, &c2, &c3);

        // On decode la chaine entree
        decode(c1, c2, c3);

        // On verifie si on execute encore une iteration
        printf("Voulez-vous continuer?\n");
        scanf(" %c", &rep);
    } while (rep == 'o');

    return 0;
}

/*
Entrez le codon de nucleotides qu'on veux etudier:
UAA
Le triplet UAA forme un codon de terminaison.
Voulez-vous continuer?
o
Entrez le codon de nucleotides qu'on veux etudier:
UUC
Le triplet UUC forme le codon de la phenylalanine.
Voulez-vous continuer?
o
Entrez le codon de nucleotides qu'on veux etudier:
TAU
Le triplet TAU ne forme pas un codon.
Voulez-vous continuer?
o
Entrez le codon de nucleotides qu'on veux etudier:
GUC
Le triplet GUC forme le codon de la valine.
Voulez-vous continuer?
o
Entrez le codon de nucleotides qu'on veux etudier:
GAG
Le triplet GAG forme un acide amine inconnu.
Voulez-vous continuer?
o
Entrez le codon de nucleotides qu'on veux etudier:
UGC
Le triplet UGC forme le codon de la cysteine.
Voulez-vous continuer?
o
Entrez le codon de nucleotides qu'on veux etudier:
GUG
Le triplet GUG forme un codon d'initialisation.
Voulez-vous continuer?
o
Entrez le codon de nucleotides qu'on veux etudier:
CUU
Le triplet CUU forme le codon de la leuncine.
Voulez-vous continuer?
o
Entrez le codon de nucleotides qu'on veux etudier:
CAU
Le triplet CAU forme le codon de l'histine.
Voulez-vous continuer?
o
Entrez le codon de nucleotides qu'on veux etudier:
GAC
Le triplet GAC forme le codon de l'asparagine.
Voulez-vous continuer?
n
*/
