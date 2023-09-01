
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define NUM_GOOSE_SPACES 3
#define NUM_BRIDGE_SPACES 1
#define NUM_MAZE_SPACES 2
#define NUM_SKULL_SPACES 1
#define BOARD_SIZE  24
const int gooseSpaces[NUM_GOOSE_SPACES] = {7, 11, 15};
const int bridgeSpaces[NUM_BRIDGE_SPACES] = {6};
const int mazeSpaces[NUM_MAZE_SPACES] = {13, 20};
const int skullSpaces[NUM_SKULL_SPACES] = {23};

int specialSpaces(int *playerSpot, int dieRoll){
int count2;
	for(count2=0;count2<NUM_GOOSE_SPACES;count2++){
		if(*playerSpot==gooseSpaces[count2]){	
			if(*playerSpot+dieRoll<BOARD_SIZE){
			printf("go to space %d, ",*playerSpot);
			*playerSpot+=dieRoll;
			}
			else{
				printf("unable to make this move\n");
				*playerSpot=*playerSpot;
			}
		}
	}
	for(count2=0;count2<NUM_BRIDGE_SPACES;count2++){
		if(*playerSpot==bridgeSpaces[count2]){
			if(*playerSpot*2<BOARD_SIZE){
				printf("go to space %d, ",*playerSpot);
				*playerSpot*=2;
			}
			else{
				printf("unable to make this move\n");
				*playerSpot=*playerSpot;
			}
		}
	}
	for(count2=0;count2<NUM_MAZE_SPACES;count2++){
		if(*playerSpot==mazeSpaces[count2]){
			printf("go to space %d, ",*playerSpot);
			*playerSpot-=dieRoll;	
		}
		
	}
	for(count2=0;count2<NUM_SKULL_SPACES;count2++){
		if(*playerSpot==skullSpaces[count2]){
			printf("go to space %d, ",*playerSpot);
			*playerSpot=1;	
		}
	}
return 0;	
}

int rollTheDice(){
int die_roll1,die_roll2;
die_roll1 = (rand()%6) + 1;
die_roll2 = (rand()%6) + 1;
printf("you rolled a %d and a  %d for a sum of %d\n", die_roll1, die_roll2, die_roll1+die_roll2);
return die_roll1+die_roll2;
}

void printBoard(int humanSpot, int cpuSpot){
int count,gooseSpace,bridgeSpace,mazeSpace,skullSpace,count2;
char boardSize[BOARD_SIZE+1][10],buf[10];
for(count=0;count<BOARD_SIZE;count++){
	if(count==BOARD_SIZE-1){
		sprintf(buf," <%d>",BOARD_SIZE);
		strcpy(boardSize[BOARD_SIZE-1],buf);
		}
	else{
		sprintf(buf," [%d]", count+1);
		strcpy(boardSize[count],buf);
		}
}
strcpy(boardSize[BOARD_SIZE],"");
for(count=0;count<=BOARD_SIZE;count++){
	for(count2=0;count2<NUM_GOOSE_SPACES;count2++){
		gooseSpace=gooseSpaces[count2];
		sprintf(buf," +[%d]",gooseSpace);
		strcpy(boardSize[gooseSpace-1],buf);
	}
	for(count2=0;count2<NUM_BRIDGE_SPACES;count2++){
		bridgeSpace=bridgeSpaces[count2];
		sprintf(buf," *[%d]",bridgeSpace);
		strcpy(boardSize[bridgeSpace-1],buf);
	}
	for(count2=0;count2<NUM_MAZE_SPACES;count2++){
		mazeSpace=mazeSpaces[count2];
		sprintf(buf," -[%d]",mazeSpace);
		strcpy(boardSize[mazeSpace-1],buf);
	}
	for(count2=0;count2<NUM_SKULL_SPACES;count2++){
		skullSpace=skullSpaces[count2];
		sprintf(buf," ![%d]",skullSpace);
		strcpy(boardSize[skullSpace-1],buf);
	}	
	if(humanSpot==BOARD_SIZE){
		strcpy(boardSize[BOARD_SIZE-1], " <$>");
		strcpy(boardSize[cpuSpot-1], " [%]");
	}
	else if(cpuSpot==BOARD_SIZE){
		strcpy(boardSize[BOARD_SIZE-1], " <%>");
		strcpy(boardSize[humanSpot-1], " [$]");
	}
	else if(humanSpot==cpuSpot)
		strcpy(boardSize[humanSpot-1]," [$%]");
	else{
		strcpy(boardSize[humanSpot-1]," [$]");
		strcpy(boardSize[cpuSpot-1]," [%]");
	}
}
for(count=0;count<=BOARD_SIZE;count++){

	printf("%s",boardSize[count]);
	if(count==BOARD_SIZE/2-1)
		printf("\n");
}
printf("\n");
return;
}
 
int main(){
char buff[10],choice;
int humanSpot,cpuSpot,seed,humanFirstRoll,cpuFirstRoll,dieRoll=0;
while(choice!='q' && choice!= 'Q'){
	humanSpot=1,cpuSpot=1;
	printf("enter a seed for the random number generator:\n");
	fgets(buff,10,stdin);
	sscanf(buff,"%d",&seed);
	srand(seed);
	printf("Welcome to the game of goose, please select an option:\n");
	printf("Press 'P' or 'p' to play\n");
	printf("Press 'Q' or 'q' to quit\n");
	fgets(buff,10,stdin);
	sscanf(buff,"%c",&choice);
	if(choice=='p'|| choice == 'P'){
		printf("HUMAN PLAYER, Press <enter> to roll the dice\n");
		while(getchar()!='\n');
		humanFirstRoll=rollTheDice();
		printf("COMPUTER PLAYER, Press <enter> to roll the dice\n");
		while(getchar()!='\n');
		cpuFirstRoll=rollTheDice();
		if(humanFirstRoll==cpuFirstRoll){
			while(humanFirstRoll==cpuFirstRoll){
				printf("Both players rolled the same number, will reroll again\n");
				printf("HUMAN PLAYER, Press <enter> to roll the dice\n");
				while(getchar()!='\n');
				humanFirstRoll=rollTheDice();
				printf("COMPUTER PLAYER, Press <enter to roll the dice\n");
				while(getchar()!='\n');
				cpuFirstRoll=rollTheDice();		
				}
		}
		 if(humanFirstRoll>cpuFirstRoll){
			printf("HUMAN PLAYER goes first\n");
			printBoard(humanSpot,cpuSpot);
			while(humanSpot!=BOARD_SIZE && cpuSpot!=BOARD_SIZE){
				printf("HUMANS`S TURN, [%d]... Press <enter> to roll the dice\n",humanSpot);
				while(getchar()!='\n');
				dieRoll=rollTheDice();
				if(humanSpot+dieRoll<BOARD_SIZE && humanSpot+dieRoll!=BOARD_SIZE)
					humanSpot+=dieRoll;
				 if(humanSpot+dieRoll==BOARD_SIZE){
					humanSpot+=dieRoll;
					printf("go to space %d\n",humanSpot);
					printBoard(humanSpot,cpuSpot);
					printf("Game Over! Human Won!\n");
					printf("Press <enter> to return to the main menu\n");
					while(getchar()!='\n');
					break;
				}
				specialSpaces(&humanSpot,dieRoll);
				printf("go to space %d\n",humanSpot);
				printBoard(humanSpot,cpuSpot);
				printf("COMPUTER`S TURN [%d]... Press <enter> to roll the dice\n",cpuSpot);
				while(getchar()!='\n');
				dieRoll=rollTheDice();
				if(cpuSpot+dieRoll<BOARD_SIZE && cpuSpot+dieRoll!=BOARD_SIZE)
					cpuSpot+=dieRoll;
				else if(cpuSpot+dieRoll==BOARD_SIZE){
					cpuSpot+=dieRoll;
					printf("go to space %d\n",cpuSpot);
					printBoard(humanSpot,cpuSpot);
					printf("Game Over! Computer Won!\n");
					printf("Press <enter> to return to the main menu\n");
					while(getchar()!='\n');
					break;
				}
				specialSpaces(&cpuSpot,dieRoll);
				printf("go to space %d\n",cpuSpot);
				printBoard(humanSpot,cpuSpot);
			}	
		 }
		else if(cpuFirstRoll>humanFirstRoll){
			printf("COMPUTER PLAYER goes first\n");
				printBoard(humanSpot,cpuSpot);
			while(humanSpot!=BOARD_SIZE && cpuSpot!=BOARD_SIZE){
				printf("COMPUTER`S TURN, [%d]... Press <enter> to roll the dice\n", cpuSpot);
				while(getchar()!='\n');
				dieRoll=rollTheDice();
				if(cpuSpot+dieRoll<BOARD_SIZE && cpuSpot+dieRoll!=BOARD_SIZE)
					cpuSpot+=dieRoll;
				else if(cpuSpot+dieRoll==BOARD_SIZE){
					cpuSpot+=dieRoll;
					printf("go to space %d\n",cpuSpot);
					printBoard(humanSpot,cpuSpot);
					printf("Game Over! Computer Won!\n");
					printf("Press <enter> to return to the main menu\n");
					while(getchar()!='\n');
					break;
				}
				specialSpaces(&cpuSpot,dieRoll);
				printf("go to space %d\n",cpuSpot);
				printBoard(humanSpot,cpuSpot);
				printf("HUMAN PLAYER`S TURN, [%d]... Press <enter> to roll the dice\n", humanSpot);
				while(getchar()!='\n');
				dieRoll=rollTheDice();
				if(humanSpot+dieRoll<BOARD_SIZE && humanSpot+dieRoll!=BOARD_SIZE)
					humanSpot+=dieRoll;
				else if(humanSpot+dieRoll==BOARD_SIZE){
					humanSpot+=dieRoll;
					printf("go to space %d\n",humanSpot);
					printBoard(humanSpot,cpuSpot);
					printf("Game Over! Human Won!\n");
					printf("Press <enter> to return to the main menu\n");
					while(getchar()!='\n');
					break;
				}
				specialSpaces(&humanSpot,dieRoll);
				printf("go to space %d\n",humanSpot);
				printBoard(humanSpot,cpuSpot);
			}

		}
	}

}
return 0;
}
