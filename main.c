#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int width = 64;
int height = 64;

int dir[8][2] = {{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};

int bornSurvive[2][9] = {{0,0,0,1,0,0,0,0,0}, {0,0,1,1,0,0,0,0,0}};
int generations = 2;

int main(){
    
	srand(time(NULL));

	int board1[width][height];
	int board2[width][height];

	int neighbors[width][height];

	int loops = 0;
		
	//Setting up board
	for(int i = 0; i < width; ++i){
		for(int j = 0; j < height; ++j){
			
			board1[i][j] = rand() % generations;
			board2[i][j] = board1[i][j];
		}
	}
    
	//Looping
	while(loops <= 1024){
			
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
				
				board2[i][j] = 0;

				//Checking if selected cell is alive then adding to it 1 until it is at the generations count.
				if(board1[i][j] >= 1){

					board2[i][j] = (board1[i][j] + 1) % generations;
				}
				//Performing rules
				for(int k = 0; k < 9; ++k){
					
					if((bornSurvive[0][k] && board1[i][j] == 0 || 
						bornSurvive[1][k] && board1[i][j] == 1) && 
						neighbors[i][j] == k){

						board2[i][j] = 1;
						break;
					}
				}
				//Making Dead state blank
				if(board2[i][j] == 0){

					printf(" ");
				}
				else{

					//Printing Alive (or in between) state to screen
					printf("%d", board2[i][j]);
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
