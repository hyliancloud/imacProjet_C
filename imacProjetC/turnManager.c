#include <stdio.h>
#include <stdlib.h>
#include "headers/turnManager.h"
#include "headers/playerManagerV2.h"
#include "headers/unitManager.h"
#include "headers/board.h"

void initializeGame(){
	// Préparation du terrain : création (le malloc) et initialization du board -> displayBoard
	// Énonciation des règles -> displayBoard
	// Préparation des pions -> placeAllUnit : initialization, création de la liste des pions pour chaque joueur, placement des pions

	_world = (World*)malloc(sizeof(World));

	int i, j;

	for(j = 0; j < HEIGHT; j++){
		for(i = 0; i < WIDTH; i++){
			_world->board[i][j] = NULL;
		}
	}

	displayBoard();
	placeAllUnit();
}

void manageTurn(){

	char* directionInput = initializeDirectionInput();

	while(1){ // 0 est faux, toute autre valeur est vraie. Ceci donne une boucle infinie
		displayBoard();
		printf("Blue team turn!\n");
		turnPlayer(_world->blueList, directionInput, "red team");

		displayBoard();
		printf("Red team turn!\n");
		turnPlayer(_world->redList, directionInput, "blue team");
	}
}

int iterateUnitList(unitList list, char* directionInput){ // = (Unit* list, char* ...)

	int aliveUnit = 0;
	// parcourir une liste chaînée
	for( ; list != NULL; list = list->next){
		if(list->isAlive == 1){ // list est un pointeur sur Unit
			printf("Moving %s unit(%d:%d)", list->type == SERF ? "Serf" : "Warrior", list->posX, list->posY);
			unitMove(list, directionInput);
			++aliveUnit;
		}
	}
	// if(list == NULL), on ne rentre pas dans la boucle et la fonction fait un return direct
	// si le type de mon unité (list) est == SERF, donc %s va afficher "Serf", sinon, %s va afficher "Warrior"
	return aliveUnit;
}

void turnPlayer(unitList list, char* directionInput, char* playerEnemyName){

	int unitTurn = iterateUnitList(list, directionInput);
	if(unitTurn == 0){
		printf("%s won the game !\n", playerEnemyName);
		quitGame(directionInput);
	}
}