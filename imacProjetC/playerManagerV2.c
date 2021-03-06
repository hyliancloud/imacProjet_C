#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/playerManagerV2.h"
#include "headers/unitManager.h"

int placeUnitInput(char axis, int size){
	int newPosition;

	printf("choose your %c position between 0 and %d\n", axis, size-1);
	scanf("%d", &newPosition);
	emptyBuffer();

	while(newPosition < 0 || newPosition >= size){
		printf("try again\n");
		scanf("%d", &newPosition);
		emptyBuffer();
	}

	return newPosition;
}

void emptyBuffer(){
  int unitBuffer;
  while((unitBuffer=getchar()) != EOF && unitBuffer != '\n');
  // fonction qui va nous permettre de vider le buffer qui va être rempli par un joueur pas doué
  // qui va écrire n'importe quoi (pas des int) dans les fonctions ci-dessus
  // EOF est un caractère qui désigne la fin d'un fichier
}

char* initializeDirectionInput(){

	const int taille = 3;
	return (char*)malloc(sizeof(char)*taille); // = malloc(3)
	// malloc sert à initialiser un pointeur

	// on lui dit à malloc de nous donner autand de mémoire qu'ont besoin 3 char (donc, 1 octet * 3)
	// sizeof est lui-même une fonction, voire plutôt un utilitaire, qui va retourner une valeur qu'il aura calculé à partir des paramètres entrés
	// malloc va renvoyer un void pointeur. Du coup, il va falloir faire un "cast" pour changer le void au type recherché (forcément un pointeur)
	// dans ce cas le cast est le (*char) qu'on a rajouté devant malloc
	// parce qu'on fait une égalité entre char* player et le malloc qui doit être donc un char* aussi
}

char* directionInput(char* playerInput){

    scanf("%3s", playerInput); // %3s -> va demander une chaîne de caractères d'une taille de 3, sachant que le troisième caractère = \0
    printf("Player has entered command \"%s\"\n", playerInput);
    while(checkInput(playerInput) == -1){
    	printf("Which is invalid you dummy !\n");
        scanf("%3s", playerInput);
    	printf("Player has entered command \"%s\"\n", playerInput);
    }

    return playerInput;
}

int checkInput(char* input){

    int i;

    for(i = 0; input[i] != '\0'; i++){
        if(input[i] == 'q'){
        	quitGame(input);
        }else if(!(input[i] == 'w'
            || input[i] == 'a' 
            || input[i] == 's' 
            || input[i] == 'd')){
            return -1;
            // avec !( condition ), on inverse la condition, car ! est un opérateur d'inversion, aussi appelé négation logique
            // input[i] = 'qqe chose' sont mes conditions sans erreurs, si je les met entre !() j'inverse la condition
            // donc je pourrait envoyer mon code d'erreur -1 à partir de là
        }
    }

    if(strcmp(input, "ws") == 0
        || strcmp(input, "sw") == 0
        || strcmp(input, "ad") == 0 
        || strcmp(input, "da") == 0){
        return -1;
    }

    // la fonction est "int strcmp(const char* s1, const char* s2)"
    // elle compare les deux chaînes de caractères passées en paramètre
    // strcmp renvoit un code de succès (0) si les deux chaînes de caractère sont pareilles

	if (input[0] == input[1]) {
		return -1;
	}
	
    return 0; // si ya pas de cas d'erreurs, je retourne 0
}