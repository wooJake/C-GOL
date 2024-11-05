#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

int width = 144;
int height = 64;

//Initializing neighbor directions from a given point.
//right, bottom right, down, bottom left, left, top left, top, top right.
int dir[8][2] = {{ 1,0}, {1,-1}, {0,-1}, {-1,-1}, {-1,0}, {-1,1}, {0,1}, {1,1}};
//Strings for making code shorter.
char str1[3][50] = {"Input born rules: ", "Input survive rules: ", "Input amount of generations: "};
char str2[3][50] = {"Born: ", "Survive: ", "Generations: "};

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
	int generations = 2;

	//printf("%s\n", str1[2]);
	//scanf("%d", &generations);

	//for(int i = 0; i < 2; ++i){

		//printf("%s\n", str1[i]);
		//for(int j = 0; j < 9; ++j){

			//bornSurvive[i][j] = GetRule(bornSurvive, i, j);
		//}
	//}

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
	while(loops < 1024){

		//Copying.
		#pragma omp parallel for
		for(int i = 0; i < height; ++i){
			for(int j = 0; j < width; ++j){

				for(int k = 0; board2[i][j] == 1 && k < 8; ++k){

					//Making torus world.
					int posx = j + dir[k][0];
					int posy = i + dir[k][1];

					if(j + dir[k][0] < 0){

						posx = width - 1;
					}
					else if(j + dir[k][0] > width - 1){

						posx = 0;
					}
					if(i + dir[k][1] < 0){

						posy = height - 1;
					}
					else if(i + dir[k][1] > height - 1){

						posy = 0;
					}

					++neighbors[posy][posx];
				}
			
				board1[i][j] = board2[i][j];
			}
		}

		//Clearing the screen.
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
				for(int k = 0; k < 9; ++k){

					board2[i][j] = BSRule(i, j, k, board1[i][j], board2[i][j], neighbors[i][j], bornSurvive);
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

	printf("\n%s", str2[2]);
	printf("%d", generations);
	for(int i = 0; i < 2; ++i){
		printf("\n%s", str2[i]);
		for(int j = 0; j < 9; ++j){

			printf("%d", bornSurvive[i][j]);
		}
	}
	printf("\n");

    return 0;
}
