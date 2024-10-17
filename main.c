#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

int width = 144;
int height = 64;

//Initializing neighbor directions from a given point.
int dir[8][2] = {{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};

int BSRule(int i, int j, int n, int board_in, int board_out, int neighbors, int bs[2][9]){

	int bornRule = bs[0][n] && board_in == 0;
	int surviveRule = bs[1][n] && board_in == 1;

	//Born / survive and neighbors check.
	if((bornRule || surviveRule) && neighbors == n){

		board_out = 1;
	}

	return board_out;
}
int GetRule(int bs[2][9], int bsi, int i){

	printf("Rule %d:", i);
	scanf("%d", &bs[bsi][i]);

	return bs[bsi][i];
}
int main(){

	int bornSurvive[2][9] = {{0,0,0,1,0,0,0,0,0}, {0,0,1,1,0,0,0,0,0}};
	int generations;

	printf("Input amount of generations: \n");
	scanf("%d", &generations);

	printf("Input born rules: \n");
	bornSurvive[0][0] = GetRule(bornSurvive, 0, 0);
	bornSurvive[0][1] = GetRule(bornSurvive, 0, 1);
	bornSurvive[0][2] = GetRule(bornSurvive, 0, 2);
	bornSurvive[0][3] = GetRule(bornSurvive, 0, 3);
	bornSurvive[0][4] = GetRule(bornSurvive, 0, 4);
	bornSurvive[0][5] = GetRule(bornSurvive, 0, 5);
	bornSurvive[0][6] = GetRule(bornSurvive, 0, 6);
	bornSurvive[0][7] = GetRule(bornSurvive, 0, 7);
	bornSurvive[0][8] = GetRule(bornSurvive, 0, 8);

	printf("Input survive rules: \n");
	bornSurvive[1][0] = GetRule(bornSurvive, 1, 0);
	bornSurvive[1][1] = GetRule(bornSurvive, 1, 1);
	bornSurvive[1][2] = GetRule(bornSurvive, 1, 2);
	bornSurvive[1][3] = GetRule(bornSurvive, 1, 3);
	bornSurvive[1][4] = GetRule(bornSurvive, 1, 4);
	bornSurvive[1][5] = GetRule(bornSurvive, 1, 5);
	bornSurvive[1][6] = GetRule(bornSurvive, 1, 6);
	bornSurvive[1][7] = GetRule(bornSurvive, 1, 7);
	bornSurvive[1][8] = GetRule(bornSurvive, 1, 8);

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
		#pragma omp parallel for
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
		#pragma omp parallel for
		for(int i = 0; i < height; ++i){
			for(int j = 0; j < width; ++j){
				
				board2[i][j] = 0;

				//Checking if selected cell is alive then adding to it 1 until it is at the generations count.
				if(board1[i][j] >= 1){

					board2[i][j] = (board1[i][j] + 1) % generations;
				}
				//Performing rules.
				board2[i][j] = BSRule(i, j, 0, board1[i][j], board2[i][j], neighbors[i][j], bornSurvive);
				board2[i][j] = BSRule(i, j, 1, board1[i][j], board2[i][j], neighbors[i][j], bornSurvive);
				board2[i][j] = BSRule(i, j, 2, board1[i][j], board2[i][j], neighbors[i][j], bornSurvive);
				board2[i][j] = BSRule(i, j, 3, board1[i][j], board2[i][j], neighbors[i][j], bornSurvive);
				board2[i][j] = BSRule(i, j, 4, board1[i][j], board2[i][j], neighbors[i][j], bornSurvive);
				board2[i][j] = BSRule(i, j, 5, board1[i][j], board2[i][j], neighbors[i][j], bornSurvive);
				board2[i][j] = BSRule(i, j, 6, board1[i][j], board2[i][j], neighbors[i][j], bornSurvive);
				board2[i][j] = BSRule(i, j, 7, board1[i][j], board2[i][j], neighbors[i][j], bornSurvive);
				board2[i][j] = BSRule(i, j, 8, board1[i][j], board2[i][j], neighbors[i][j], bornSurvive);

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
	printf("%d", bornSurvive[0][0]);
	printf("%d", bornSurvive[0][1]);
	printf("%d", bornSurvive[0][2]);
	printf("%d", bornSurvive[0][3]);
	printf("%d", bornSurvive[0][4]);
	printf("%d", bornSurvive[0][5]);
	printf("%d", bornSurvive[0][6]);
	printf("%d", bornSurvive[0][7]);
	printf("%d", bornSurvive[0][8]);

	printf("\nSurvive: ");
	printf("%d", bornSurvive[1][0]);
	printf("%d", bornSurvive[1][1]);
	printf("%d", bornSurvive[1][2]);
	printf("%d", bornSurvive[1][3]);
	printf("%d", bornSurvive[1][4]);
	printf("%d", bornSurvive[1][5]);
	printf("%d", bornSurvive[1][6]);
	printf("%d", bornSurvive[1][7]);
	printf("%d", bornSurvive[1][8]);
	printf("\n");

    return 0;
}
