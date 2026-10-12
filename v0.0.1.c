#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	char Level[5][8] = {{'*','*','*','*','*','*','*','\n'},
			    {'*',' ',' ',' ',' ',' ','*','\n'},
			    {'*',' ','*','*','*',' ','*','\n'},
			    {'*',' ',' ',' ',' ',' ','*','\n'},
			    {'*','*','*','*','*','*','*','\n'}};

	for(;;){
		for(int i = 0; i < 5; i ++){
			for(int j = 0; j < 8; j++){
				printf("%c", Level[i][j]);
			}
		}
		usleep(10*1000); //10ms
		system("clear");
	}

	return 0;
}
