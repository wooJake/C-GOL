#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int width = 144;
int height = 64;

//Initializing neighbor directions from a given point.
int dir[8][2] = {{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};

int main(){

	int bornSurvive[2][9] = {{0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0}};
	int generations;

	printf("Input amount of generations: \n");
	scanf("%d", &generations);
	printf("Input born rules: \n");
	for(int i = 0; i < 9; ++i){

		printf("Rule %d:", i);
		scanf("%d", &bornSurvive[0][i]);
	}
	printf("Input survive rules: \n");
    for(int i = 0; i < 9; ++i){

		printf("Rule %d:", i);
		scanf("%d", &bornSurvive[1][i]);
	}

	srand(time(NULL));

	int board1[height][width];
	int board2[height][width];
	int neighbors[height][width];

	int loops = 0;
		
	//Setting up board.
	for(int i = 0; i < height; ++i){
		for(int j = 0; j < width; ++j){
			
			board1[i][j] = rand() % generations;
			board2[i][j] = board1[i][j];
		}
	}
	//Looping.
	while(loops < 256){
		//Copying.
		for(int i = 0; i < height; ++i){
			for(int j = 0; j < width; ++j){

				if(board2[i][j] == 1){

					++neighbors[i + dir[0][0]][j + dir[0][1]];
					++neighbors[i + dir[1][0]][j + dir[1][1]];
					++neighbors[i + dir[2][0]][j + dir[2][1]];
					++neighbors[i + dir[3][0]][j + dir[3][1]];
					++neighbors[i + dir[4][0]][j + dir[4][1]];
					++neighbors[i + dir[5][0]][j + dir[5][1]];
					++neighbors[i + dir[6][0]][j + dir[6][1]];
					++neighbors[i + dir[7][0]][j + dir[7][1]];
				}
			
				board1[i][j] = board2[i][j];
			}
		}
		system("clear");
		//Interacting.
		for(int i = 0; i < height; ++i){
			for(int j = 0; j < width; ++j){
				
				board2[i][j] = 0;

				//Checking if selected cell is alive then adding to it 1 until it is at the generations count.
				if(board1[i][j] >= 1){

					board2[i][j] = (board1[i][j] + 1) % generations;
				}
				//Performing rules.
				for(int k = 0; k < 9; ++k){
					
					//Born / survive check.
					if((bornSurvive[0][k] && board1[i][j] == 0 || 
						bornSurvive[1][k] && board1[i][j] == 1) && 
						neighbors[i][j] == k){

						board2[i][j] = 1;
						break;
					}
				}

				//Setting neighbors to 0.
				neighbors[i][j] = 0;

				//Making Dead state blank.
				if(board2[i][j] == 0){

					//If Dead print nothing.
					printf(" ");
					continue;
				}

				//Printing Alive (or in between) state to screen.
				printf("%d", board2[i][j]);
			}
			printf("\n");
		}
		
		++loops;
		usleep( 60000 );
	}

	printf("\nGenerations: ");
	printf("%d", generations);
	printf("\nBorn: ");
	for(int i = 0; i < 9; ++i){

		printf("%d", bornSurvive[0][i]);
	}
	printf("\nSurvive: ");
	for(int i = 0; i < 9; ++i){

		printf("%d", bornSurvive[1][i]);
	}
	printf("\n");

    return 0;
}
