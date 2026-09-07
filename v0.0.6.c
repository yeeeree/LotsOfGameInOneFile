#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void move();
void Ghost_move();
void array_assign(char a[5][8], char b[5][8], int c, int d);

int pos_x = 1, pos_y = 1, Gpos_x = 5, Gpos_y = 3;
char Level[5][8] = {{'*','*','*','*','*','*','*','\n'},
		    {'*',' ',' ',' ',' ',' ','*','\n'},
		    {'*',' ','*','*','*',' ','*','\n'},
		    {'*',' ',' ',' ',' ',' ','*','\n'},
		    {'*','*','*','*','*','*','*','\n'}};
char Level2[5][8], over, input;
bool Gameover = 0;

int main(){
	array_assign(Level2, Level, 5, 8); //copy Level
there:
	for(;;){
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 8; j++){
				printf("%c", Level[i][j]);
			}
		}
		array_assign(Level, Level2, 5, 8); //refresh map
		if(Gameover == 0)
			move();
		Ghost_move();
		usleep(10*1000); //10ms
		system("clear");
		if(Gpos_x == pos_x && Gpos_y == pos_y){
			Gameover = 1;
			printf("Gameover\n");
		here:
			printf("Retry type \'R\'. exit type \'E\'.\n");
			scanf("%c", &over);
			if(over == 'R' || over == 'r'){
				pos_x = 1;
				pos_y = 1;
				Gpos_x = 5;
				Gpos_y = 3;
				Gameover = 0;
				goto there;
			}
			else if(over == 'E' || over == 'e')
				exit(0);
			else{
				printf("Missing argument to \"%c\"\n", over);
				goto here;
			}
		}
	}

	return 0;
}

void move(){
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

void Ghost_move(){
	if(input != '\n'){
		if(Gpos_x - pos_x > 0 && Level[Gpos_y][Gpos_x - 1] != '*') //Ghost at right of player
			Gpos_x--;
		else if(Gpos_x - pos_x < 0 && Level[Gpos_y][Gpos_x + 1] != '*') //Ghost at left of player
			Gpos_x++;
		else if(Gpos_y - pos_y > 0 && Level[Gpos_y - 1][Gpos_x] != '*') //Ghost below player
			Gpos_y--;
		else if(Gpos_y - pos_y < 0 && Level[Gpos_y + 1][Gpos_x] != '*') //Ghost above player
			Gpos_y++;
	}
	Level[Gpos_y][Gpos_x] = 'M';
}
