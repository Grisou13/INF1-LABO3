/*
 -----------------------------------------------------------------------------------
 Laboratoire : 03
 Fichier     : main.cpp
 Auteur(s)   : Thomas Ricci
 Date        : 26.09.2018

 But         : <TODO>

 Remarque(s) : <TODO>

 Compilateur : g++ (Ubuntu 5.4.0-6ubuntu1~16.04.10)
 -----------------------------------------------------------------------------------
 */

#include <cstdlib>
#include <iostream>
#include <climits>

using namespace std;

int main() {
   
   const unsigned int NBR_EXP_MIN = 1000;
   const unsigned int NBR_EXP_MAX = 100000;
   
   const unsigned int TAILLE_GRILLE_MAX = 50;
   const unsigned int TAILLE_GRILLE_MIN = 2;
   const unsigned int TAILLE_GRILLE_INCREMENT = 2;
   
   const unsigned short DIRECTION_DROITE = 1;
   const unsigned short DIRECTION_GAUCHE = 2;
   const unsigned short DIRECTION_HAUT = 3;
   const unsigned short DIRECTION_BAS = 4;
   const unsigned short DISTANCE_DEPLACEMENT = 1;
   
   
   unsigned int x,y;
   unsigned int compteur, nbrExperience;
   
   //Demander à l'utilisateur d'entrer le nombre d'expériences à effectuer
   do{
      cout << "Veuillez entrer un nombre d'experience " 
           << "( entre " << NBR_EXP_MIN << " et " << NBR_EXP_MAX << "): ";
      if (not(cin >> nbrExperience))
      {
         cin.clear();
         cin.ignore(INT_MAX,'\n');
      }
   }while(nbrExperience <NBR_EXP_MIN || nbrExperience > NBR_EXP_MAX);
   
   //Effectuer les expériences
   for(int i = TAILLE_GRILLE_MIN; i < TAILLE_GRILLE_MAX; i += TAILLE_GRILLE_INCREMENT){
      for(int j = 0; j < nbrExperience; j ++){
         
      }
   }
   
   
   return EXIT_SUCCESS;
}
