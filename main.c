#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int width = 64;
int height = 64;

int bornSurvive[2][9] = {{0,0,0,1,0,0,0,0,0}, {0,0,1,1,0,0,0,0,0}};

int dir[8][2] = {{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};

int ReturnDeadAlive(int neighborsNum, int i, int j, int s){

	int Out = 0;
	for(int k = 0; k < 8; ++k){

		if(neighborsNum == k){
							
			Out = bornSurvive[s][k];
			break;
		}
	}

	return Out;
}
int main(){
    
	srand(time(NULL));

	int board1[width][height];
	int board2[width][height];

	int neighbors[width][height];

	int loops = 0;
		
	//Setting up board
	for(int i = 0; i < width; ++i){
		for(int j = 0; j < height; ++j){
			
			board1[i][j] = rand() % 2;
			board2[i][j] = board1[i][j];
		}
	}
    
	//Looping
	while(loops <= 1000){
			
		//Copying
		for(int i = 0; i < width; ++i){
			for(int j = 0; j < height; ++j){

				for(int k = 0; board2[i][j] == 1 && k < 8; ++k){

					++neighbors[i + dir[k][0]][j + dir[k][1]];
				}
			
				board1[i][j] = board2[i][j];
			}
		}
		system("clear");
		
		//Interacting
		for(int i = 0; i < width; ++i){
			for(int j = 0; j < height; ++j){
				
				//Checking if selected cell is alive
				if(board1[i][j] == 1){
				
					printf("%c", 'O');
					board2[i][j] = ReturnDeadAlive(neighbors[i][j], i, j, 1);
				}
				else{
				
					//Otherwise if selected cell is dead
					printf("%c", ' ');
					board2[i][j] = ReturnDeadAlive(neighbors[i][j], i, j, 0);
				}
				neighbors[i][j] = 0;
			}
			printf("\n");
		}
		
		++loops;
		usleep( 60000 );
	}

    return 0;
}
