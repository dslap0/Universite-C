/* 

Auteur : Nicolas Levasseur

1. a) 
    float F, rep;
    5 * (F - 32) / 9.0F;

   b)
    int a, b, c;
    float x;
    a * x * x + b * x + c;

   c)
    float x, y, z;
    (x < 0 ? –x : x) + (y < 0 ? –y : y) + (z < 0 ? -z : z)

   d)
    float x;
    !(-3 < x <= 5);

   e)
    int x;
    x == -5 || x == -2 || x == 0 || x == 3 || x == 7;


2. a)
    a / 2 + b / 4 + c / 8;

   b)
    (a + b) * 10 >= c / a * 5 + b;

   c)
    a % 2 <= b % 3 && (a + b) % 4 == (b - c) % 5;

   d)
    a == b && b == c || a < b && b > c;

   e)
    (a = b) != (b = c) && a * b >= c == b * c <= a;

3. a)
    0

   b)
    1 (ou true)

   c)
    1 (ou true)

   d)
    1 (ou true)

   e)
    0 (ou false)

4. a)
    a != b;

   b)
    a > 0 || b > 0 || c > 0;

   c)
    a <= 0 && b <= 0 && c <= 0;

   d)
    a == b || b == c;

   e)
    a < b == b > c;

5. Le code présenté ci-après calcule le volume d'une sphère lorsqu'on lui
fournit un rayon, et le programme se répète dans une do loop tant que 
l'utilisateur le demande.

*/

#include <stdio.h>
#define PI 3.14159265

float VolumeSphere(float rayon) {

/*
Cette fonction calcule le volume d'une sphère à partir de son rayon et de la 
formule standard de calcul d'un volume à partir du rayon, soit 
V = 4/3 * pi * r^3.
rayon : Seul paramètre de la fonction, float qui correspond au rayon de la 
sphère dont on veut obtenir le volume.
*/

    return 4.0f / 3.0f * PI * rayon * rayon * rayon;
}

int main() {
    // On déclare la variable qui entreposera la réponse de l'utilisateur 
    // lorsqu'on lui demande s'il veut calculer d'autres volumes
    char rep;

    // Boucle principale du programme qui s'exécute tant que l'utilisateur répond 
    // 'o' à la dernière question
    do {
        // On affiche un message
        printf("Entrez le rayon de la sphere dont on cherche le volume: ");

        // On déclare ici la variable qui aura le rayon de la sphère
        float rayon;

        // On récupère ici la réponse de l'utilisateur
        scanf ("%f", &rayon);

        // On affiche deux messagex
        printf("Une sphere de rayon %.2f a %.2f de volume\n", rayon, VolumeSphere(rayon));
        printf("Voulez-vous calculer un autre volume (o/n)? ");

        // On récupère ici la réponse de l'utilisateur
        scanf(" %c", &rep);
    } while (rep == 'o');

    return 0;
}

/*
Une sphere de rayon 1.20 a 7.24 de volume
Une sphere de rayon 3.40 a 164.64 de volume
Une sphere de rayon 4.50 a 381.70 de volume
Une sphere de rayon 6.70 a 1259.83 de volume
Une sphere de rayon 8.90 a 2952.97 de volume
*/