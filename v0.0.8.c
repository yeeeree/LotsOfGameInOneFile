#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void Move();
void Ghost_move();
void Array_copy(char a[13][16], char b[13][16]);
void Point_place(char a[13][16]);

int pos_x = 1, pos_y = 1, Gpos_x = 14, Gpos_y = 10;
char Map[13][16] = {{'@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','\n'},
		    {'@',' ',' ',' ',' ',' ',' ',' ',' ',' ','@',' ',' ',' ','@','\n'},
		    {'@',' ',' ',' ',' ',' ',' ',' ',' ',' ','@',' ',' ',' ','@','\n'},
		    {'@',' ',' ',' ','@',' ','@','@','@',' ','@',' ',' ',' ','@','\n'},
		    {'@','@','@','@','@',' ',' ','@',' ',' ','@','@',' ',' ','@','\n'},
		    {'@',' ',' ',' ',' ',' ',' ','@',' ',' ',' ',' ',' ',' ','@','\n'},
		    {'@',' ',' ',' ',' ',' ',' ','@',' ',' ',' ',' ',' ',' ','@','\n'},
		    {'@',' ',' ',' ',' ',' ',' ','@',' ',' ',' ',' ',' ',' ','@','\n'},
		    {'@',' ',' ','@','@',' ',' ','@',' ',' ','@','@','@','@','@','\n'},
		    {'@',' ',' ',' ','@',' ','@','@','@',' ','@',' ',' ',' ','@','\n'},
		    {'@',' ',' ',' ','@',' ',' ',' ',' ',' ',' ',' ',' ',' ','@','\n'},
		    {'@',' ',' ',' ','@',' ',' ',' ',' ',' ',' ',' ',' ',' ','@','\n'},
		    {'@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','\n'}};
char Map2[13][16], Map3[13][16], over, input;
bool Gameover = 0;

int main(){
	Array_copy(Map2, Map); //Map2 is clear map
	Point_place(Map);
	Array_copy(Map3, Map); //Map3 is point map
there:
	for(;;){
		for(int i = 0; i < 13; i++){
			for(int j = 0; j < 16; j++){
				printf(" %c", Map[i][j]);
			}
		}
		Array_copy(Map, Map3); //refresh map
		if(Gameover == 0)
			Move();
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
				Gpos_x = 14;
				Gpos_y = 10;
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

void Move(){
	input = getchar();

	if(input == 'w' && Map[pos_y - 1][pos_x] != '@')
		pos_y--;
	if(input == 's' && Map[pos_y + 1][pos_x] != '@')
		pos_y++;
	if(input == 'a' && Map[pos_y][pos_x - 1] != '@')
		pos_x--;
	if(input == 'd' && Map[pos_y][pos_x + 1] != '@')
		pos_x++;
	Map[pos_y][pos_x] = 'C';
}

void Array_copy(char a[13][16], char b[13][16]){
	//assign b to a
	for(int e = 0; e < 13; e++){
		for(int f = 0; f < 16; f++){
			a[e][f] = b[e][f];
		}
	}
}

void Ghost_move(){
	if(input != '\n'){
		if(Gpos_x - pos_x > 0 && Map[Gpos_y][Gpos_x - 1] != '@') //Ghost at right of player
			Gpos_x--;
		else if(Gpos_x - pos_x < 0 && Map[Gpos_y][Gpos_x + 1] != '@') //Ghost at left of player
			Gpos_x++;
		else if(Gpos_y - pos_y > 0 && Map[Gpos_y - 1][Gpos_x] != '@') //Ghost below player
			Gpos_y--;
		else if(Gpos_y - pos_y < 0 && Map[Gpos_y + 1][Gpos_x] != '@') //Ghost above player
			Gpos_y++;
	}
	Map[Gpos_y][Gpos_x] = 'M';
}

void Point_place(char a[13][16]){
	for(int b = 0; b < 13; b++){
		for(int c = 0; c < 16; c++){
			if(a[b][c] == ' ')
				a[b][c] = '*';
		}
	}
}
