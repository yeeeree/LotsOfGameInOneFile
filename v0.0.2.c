#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void move();
int pos_x = 1, pos_y = 2;
char Level[5][8] = {{'*','*','*','*','*','*','*','\n'},
		    {'*',' ',' ',' ',' ',' ','*','\n'},
		    {'*',' ','*','*','*',' ','*','\n'},
		    {'*',' ',' ',' ',' ',' ','*','\n'},
		    {'*','*','*','*','*','*','*','\n'}};

int main(){
	for(;;){
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 8; j++){
				printf("%c", Level[i][j]);
			}
		}
		move();
		usleep(10*1000); //10ms
		system("clear");
	}

	return 0;
}

void move(){
	char input = 'n';
	scanf("%c", &input);

	if(input == 'w')
		pos_y--;
	if(input == 's')
		pos_y++;
	if(input == 'a')
		pos_x--;
	if(input == 'd')
		pos_x++;
	Level[pos_y][pos_x] = 'C';
}
