#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

// Afficher le mot a deviner en remplacant les lettres non trouvees par des tirets
void afficherMot(const char* mot, const bool* lettresTrouvees){
    for(int i = 0; mot[i] != '\0'; i++){
        if (lettresTrouvees[i]) {
            std::cout << mot[i] << " "; // affichage de la lettre si elle est trouvee

        } else {
            std::cout << "_"; // affichage du tiret si la lettre n'est pas trouvee
        }
    }
    std::cout << std::endl;
}

// affichage du dessin du pendu en fonction du nombre d'erreur donc etape par etape
void afficherPendu(int erreurs) {
    switch (erreurs)
    {
    case 1: std::cout << "0" << std::endl;
        break; // tete
    case 2: std::cout << " 0\n|" << std::endl;
        break; // tete+corps
    case 3: std::cout << "0\n|/" << std::endl;
        break; // tete+corps+bras gauche
    case 4: std::cout << "0\n|\\" << std::endl;
        break; // tete+corps+bras gauche et droit
    case 5: std::cout << "0\n|/\\\n|" << std::endl;
        break; // tete+corps+bras gauche et droit+tronc
    case 6: std::cout << "0\n|/\\\n||" << std::endl;
        break; // tete+corps+bras gauche et droit+tronc+jambe
          
    default:
        break;
    }
}
// on verifie si la lettre tapee est dans le mot
bool estDansMot(char lettre, const char* mot) {
    for(int i = 0; mot[i] != '\0'; i++) {
        if (mot[i] == lettre) return true; // retourne vrai si la lettre est trouvee
        
    }
    return false; // retourne faux si la lettre ne se trouve pas dans le mot

}
//montre toute les occurences de la lettre dans le mot
void revelerLettres(char lettre, const char* mot, bool* lettresTrouvees) {
    for(int i = 0; mot[i] != '\0'; i++) {
        if (mot[i] == lettre) {
            lettresTrouvees[i] = true;
        }
    }
}
//verifie si toute les lettres ont ete trouvees
bool aGagne(const bool* lettresTrouvees, int longueurMot) {
    for (int i = 0; i < longueurMot; i++)
    {
        if (!lettresTrouvees[i]) return false;
    }
    return true;
    
}

int main() {
    const char*mots[] = {"PROGRAMMATION", "ORDINATEUR", "ALGORITHME", "CLAVIER", "ESPAGNE", "POLYTECHNIQUE"};
    srand(time(0)); // initialisation du generateur de nombres aleatoires
    const char* mot = mots[rand() % 4]; // permet de choisir un mot de maniere aleatoire dans la liste

    int longueurMot = strlen(mot); // longueur du mot choisi
    bool lettresTrouvees[longueurMot]; //tableau pour suivre les lettres trouvees
    for (int i = 0; i < longueurMot; i++)
    {
        lettresTrouvees[i] = false;
    }
    int erreurs = 0;
    const int erreursMax = 6;
    char lettre;

    while(erreurs < erreursMax) {
        afficherMot(mot, lettresTrouvees);
        std::cout << "Entrez une lettre : ";
        std::cin >> lettre;
        lettre = toupper(lettre); // convertit la lettre en majuscule pour pouvoir correspondre au mot

        if(estDansMot(lettre, mot)) {
            revelerLettres(lettre, mot, lettresTrouvees);
        } else {
            erreurs++; // incrementation du compteur d'erreurs pour lettre incorrectes
            std::cout << "Lettre incorrecte ! Tentatives restantes : " << erreursMax - erreurs << std::endl;
            afficherPendu(erreurs);

        }
        if(aGagne(lettresTrouvees, longueurMot)) {
            std::cout <<"Felicitations ! Vous avez trouve le  mot : " << mot << std::endl;
            return 0;
        }
    }
    std::cout << "Desole, vous avez perdu ! Le mot etait : " << mot << std::endl;
    std::cout << "Vous aurez plus de chance la prochaine fois " << std::endl;
    return 0;
    
}
