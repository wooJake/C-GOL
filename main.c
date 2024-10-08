#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(){
    
	srand(time(NULL));

	int boardWidth = 24;
	int boardHeight = 24;

	int board1[boardWidth][boardHeight];
	int board2[boardWidth][boardHeight];

	int neighbors[boardWidth][boardHeight];

	int dir[8][2] = {{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};

	int loops = 0;
		
	//Setting up board
	for(int i = 0; i < boardWidth; ++i){
		for(int j = 0; j < boardHeight; ++j){
			
			board1[i][j] = rand() % 2;
			board2[i][j] = board1[i][j];
			
			printf("%d", board1[i][j]);
		}
		printf("\n");
	}
    
	//Looping
	while(loops <= 1000){
			
		//Copying
		for(int i = 0; i < boardWidth; ++i){
			for(int j = 0; j < boardHeight; ++j){

				if(board2[i][j] == 1){

					for(int k = 0; k < 8; ++k){

						++neighbors[i + dir[k][0]][j + dir[k][1]];
					}
				}
			
				board1[i][j] = board2[i][j];
			}
		}
			
		system("clear");
		
		//Interacting
		for(int i = 0; i < boardWidth; ++i){
			for(int j = 0; j < boardHeight; ++j){
				
			if(board1[i][j] == 1){
				
				printf("O");
				
				if(neighbors[i][j] != 2 && neighbors[i][j] != 3){
				
				board2[i][j] = 0;
				}
		
				neighbors[i][j] = 0;
				continue;
			}
				
			printf(" ");
			
			if(neighbors[i][j] == 3){
			
				board2[i][j] = 1;
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
