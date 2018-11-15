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
#include <iomanip>
#include <climits>
#include <ctime> //Utilisé pour générer des nombres pseudo-aléatoires

using namespace std;

int main() {
   
   const unsigned int NBR_EXP_MIN = 1000;
   const unsigned int NBR_EXP_MAX = 100000;
   
   const unsigned int TAILLE_GRILLE_MAX = 4; //50
   const unsigned int TAILLE_GRILLE_MIN = 2;
   const unsigned int TAILLE_GRILLE_INCREMENT = 2;
   
   const unsigned short DIRECTION_DROITE = 1;
   const unsigned short DIRECTION_GAUCHE = 2;
   const unsigned short DIRECTION_HAUT = 3;
   const unsigned short DIRECTION_BAS = 4;
   const unsigned short DISTANCE_DEPLACEMENT = 1;
   
   unsigned nbrExperiences;
   
   nbrExperiences = 1;
   //Demander à l'utilisateur d'entrer le nombre d'expériences à effectuer
   /*do{
      cout << "Veuillez entrer un nombre d'experience " 
           << "( entre " << NBR_EXP_MIN << " et " << NBR_EXP_MAX << "): ";
      if (not(cin >> nbrExperiences))
      {
         cin.clear();
         cin.ignore(INT_MAX,'\n');
      }
   }while(nbrExperiences <NBR_EXP_MIN || nbrExperiences > NBR_EXP_MAX); */
   
   int x,y;
   short direction; //1=gauche; 2=droite; 3=haut; 4=bas
   unsigned int longueur;
   double longueurMoyenne;
   bool droiteTouch,
        gaucheTouch,
        hautTouch,
        basTouch;
   
   int nbDroiteTouch,
       nbGaucheTouch,
       nbHautTouch,
       nbBasTouch;
   
   int maxNbDroiteTouch,
       maxNbGaucheTouch,
       maxNbHautTouch,
       maxNbBasTouch;
   
   double moyenneNbDroiteTouch,
          moyenneNbGaucheTouch,
          moyenneNbHautTouch,
          moyenneNbBasTouch;
   
   int prevBord;
   
   srand((unsigned)time(0));
   
   //Effectuer les expériences
   for(unsigned tailleGrille = TAILLE_GRILLE_MIN; tailleGrille <= TAILLE_GRILLE_MAX; tailleGrille += TAILLE_GRILLE_INCREMENT){
      longueurMoyenne = 0;
      moyenneNbDroiteTouch = moyenneNbGaucheTouch = moyenneNbHautTouch = moyenneNbBasTouch = 0;
      
      for(unsigned j = 0; j < nbrExperiences; ++j){
         longueur = 0;
         x = y = tailleGrille / 2;
         droiteTouch = gaucheTouch = hautTouch = basTouch = false;
         nbHautTouch = nbDroiteTouch = nbGaucheTouch = nbBasTouch = 0;
         prevBord=0;
         maxNbHautTouch = maxNbDroiteTouch = maxNbGaucheTouch = maxNbBasTouch = 0;
         while(!(droiteTouch && gaucheTouch && hautTouch && basTouch)){
            //Déterminer direction et effectuer le déplacement
            direction = short(rand() % 4 + 1);
            switch(direction){
               case DIRECTION_GAUCHE: 
                  x -= DISTANCE_DEPLACEMENT; break;
               case DIRECTION_DROITE: 
                  x += DISTANCE_DEPLACEMENT; break;
               case DIRECTION_HAUT: 
                  y += DISTANCE_DEPLACEMENT; break;
               case DIRECTION_BAS: 
                  y -= DISTANCE_DEPLACEMENT; break;
               default:
                  continue;
            }         
            
            
            //Si nouvelle direction = bord, rebondir et incrémenter le compteur de bord
            if(x % tailleGrille == 0 ||  y % tailleGrille == 0){
               
              
               if(prevBord != direction)
               {
                  switch(direction)
                  {
                     case DIRECTION_GAUCHE:
                        if(nbGaucheTouch > maxNbGaucheTouch)
                        {
                           maxNbGaucheTouch = nbGaucheTouch;
                           cout << maxNbGaucheTouch << endl;
                        }
                        nbGaucheTouch = 0;
                        break;
                     case DIRECTION_DROITE:
                        if(nbDroiteTouch > maxNbDroiteTouch)
                        {
                           maxNbDroiteTouch = nbDroiteTouch;
                        }
                        nbDroiteTouch = 0;
                        break;
                     case DIRECTION_HAUT:
                        if(nbHautTouch > maxNbHautTouch)
                        {
                           maxNbHautTouch = nbHautTouch;
                        }  
                        nbHautTouch = 0;
                        break;
                     case DIRECTION_BAS:
                        if(nbBasTouch > maxNbBasTouch)
                        {
                           maxNbBasTouch = nbBasTouch;
                        }
                        nbBasTouch = 0;
                  }
               }
               
               
               //Rebondir
               switch (direction){
                  case DIRECTION_GAUCHE:
                     x += DISTANCE_DEPLACEMENT; 
                     gaucheTouch=true;
                     nbGaucheTouch++;
                     cout << "2 " << nbGaucheTouch << endl;
                     break;
                  case DIRECTION_DROITE:
                     x -= DISTANCE_DEPLACEMENT; 
                     droiteTouch=true;
                     nbDroiteTouch++;
                     cout << "1 " << nbDroiteTouch << endl;
                     break;
                  case DIRECTION_HAUT:
                     y -= DISTANCE_DEPLACEMENT; 
                     hautTouch=true;
                     nbHautTouch++;
                                          cout << "3 " << nbHautTouch << endl;
                     break;
                  case DIRECTION_BAS:
                     y += DISTANCE_DEPLACEMENT; 
                     basTouch=true;
                     nbBasTouch++;
                                          cout << "4 " << nbBasTouch << endl;
                     break;
                     
               }
               
               
               
               prevBord = direction;
               
               
               
               // Incrément en cas de rebond
               ++longueur;
               
               
            }
            // Incrément de fonctionnement normal
            ++longueur;
            
         }
         
         cout << maxNbDroiteTouch << " " <<
       maxNbGaucheTouch << " " <<
       maxNbHautTouch<< " " <<
       maxNbBasTouch << " - " << longueur << endl;
         
         moyenneNbGaucheTouch += (double)maxNbGaucheTouch / nbrExperiences;
         moyenneNbDroiteTouch += (double)maxNbDroiteTouch / nbrExperiences;
         moyenneNbHautTouch += (double)maxNbHautTouch / nbrExperiences;
         moyenneNbBasTouch += (double)maxNbBasTouch / nbrExperiences;
         
         longueurMoyenne += (double)longueur/nbrExperiences;
      //Ajouter les compteurs de cotés à la moyenne
         
         
      } //Fin de l'expérience 
      
      
      cout << "{" << tailleGrille << "," << longueurMoyenne << "},";
      cout << setprecision(2) << fixed << "Pour une grille de " << tailleGrille
           << " cases, " << "La longueur moyenne du parcours du robot est " 
           << longueurMoyenne << endl;
      cout << "Le bord gauche a été heurté en moyenne " << moyenneNbGaucheTouch << " fois" << endl;
      cout << "Le bord droite a été heurté en moyenne " << moyenneNbDroiteTouch << " fois" << endl;
      cout << "Le bord haut a été heurté en moyenne " << moyenneNbHautTouch << " fois" << endl;
      cout << "Le bord bas a été heurté en moyenne " << moyenneNbBasTouch << " fois" << endl;
   }
   
   
   
   return EXIT_SUCCESS;
}



//               if(prevBord != direction)
//               {
//                  switch (direction){
//                     case DIRECTION_GAUCHE:
//                        if(nbGaucheTouch > maxNbGaucheTouch)
//                        {
//                           maxNbGaucheTouch = nbGaucheTouch;
//                        }
//                        nbGaucheTouch = 0;
//                        break;
//                     case DIRECTION_DROITE:
//                        if(nbDroiteTouch > maxNbDroiteTouch)
//                        {
//                           maxNbDroiteTouch = nbDroiteTouch;
//                        }
//                        nbDroiteTouch = 0;
//                        break;
//                     case DIRECTION_HAUT:
//                        if(nbHautTouch > maxNbHautTouch)
//                        {
//                           maxNbHautTouch = nbHautTouch;
//                        }
//                        nbHautTouch = 0;
//                        break;
//                     case DIRECTION_BAS:
//                        if(nbBasTouch > maxNbBasTouch)
//                        {
//                           maxNbBasTouch = nbBasTouch;
//                        }
//                        nbBasTouch = 0;
//                        break;
//                  
//                  }
//               }