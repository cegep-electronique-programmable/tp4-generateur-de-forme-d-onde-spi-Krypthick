/*
* ecran.h
* Contient toutes les fonctions pour interagir avec l'ecran modele
* NHD-0420D3Z-FL-GBW
*
* Auteur : Philippe Lefebvre
*/

#ifndef ECRAN_H
#define ECRAN_H

/***********Includes************/


/************Defines************/


/*********Declarations**********/
/*
* Fonction : ecranAllume
* Description : Envoie la commande pour allumer l'ecran
*
* Params : Aucun
* 
* Retour : Aucun
*/
void ecranAllume(void);

/*
* Fonction : ecranEteint
* Description : Envoie la commande pour eteindre l'ecran
*
* Params : Aucun
* 
* Retour : Aucun
*/
void ecranEteint(void);


int curseurPosition(int position);


void videEcran(void);


void ecrireCaractere(char caractere);

void backlightOn(int brightness);

#endif