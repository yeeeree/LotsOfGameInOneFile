#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void move();
void array_assign(char a[5][8], char b[5][8], int c, int d);

int pos_x = 1, pos_y = 1;
char Level[5][8] = {{'*','*','*','*','*','*','*','\n'},
		    {'*',' ',' ',' ',' ',' ','*','\n'},
		    {'*',' ','*','*','*',' ','*','\n'},
		    {'*',' ',' ',' ',' ',' ','*','\n'},
		    {'*','*','*','*','*','*','*','\n'}};
char Level2[5][8];

int main(){
	array_assign(Level2, Level, 5, 8); //copy Level
	for(;;){
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 8; j++){
				printf("%c", Level[i][j]);
			}
		}
		array_assign(Level, Level2, 5, 8); //refresh map
		move();
		usleep(10*1000); //10ms
		system("clear");
	}

	return 0;
}

void move(){
	char input;
	input = getchar();

	if(input == 'w' && Level[pos_x - 1][pos_y] != '*')
		pos_x--;
	if(input == 's' && Level[pos_x + 1][pos_y] != '*')
		pos_x++;
	if(input == 'a' && Level[pos_x][pos_y - 1] != '*')
		pos_y--;
	if(input == 'd' && Level[pos_x][pos_y + 1] != '*')
		pos_y++;
	Level[pos_x][pos_y] = 'C';
}

void array_assign(char a[5][8], char b[5][8], int c, int d){
	//assign b to a
	//c is row (horizon)
	//d is column (vertical)
	for(int e = 0; e < c; e++){
		for(int f = 0; f < d; f++){
			a[e][f] = b[e][f];
		}
	}
}
