#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define X 16 //column
#define Y 13 //row

void Choose_level();
void Play();
void Move();
void Ghost_move();
void Array_copy(char a[Y][X], char b[Y][X]);
void Point_place(char a[Y][X]);
void Eat_point(char a[Y][X]);

int row, column, Gpos_x, Gpos_y, pos_x = 1, pos_y = 1, score = 0, total_score, heart = 3;
char Level1[Y][X] = {{'@','@','@','@','@','@','@','\n'},
		   {'@',' ','@',' ',' ',' ','@','\n'},
		   {'@',' ','@',' ',' ',' ','@','\n'},
		   {'@',' ',' ',' ',' ',' ','@','\n'},
		   {'@',' ',' ',' ',' ',' ','@','\n'},
		   {'@',' ',' ',' ','@',' ','@','\n'},
		   {'@',' ',' ',' ','@',' ','@','\n'},
		   {'@','@','@','@','@','@','@','\n'}};

char Level2[Y][X] = {{'@','@','@','@','@','@','@','@','@','@','@','@','@','\n'},
		   {'@',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','@','\n'},
		   {'@',' ','@',' ','@',' ','@',' ','@',' ','@',' ','@','\n'},
		   {'@',' ','@',' ','@',' ','@',' ','@',' ','@',' ','@','\n'},
		   {'@',' ','@',' ','@',' ','@',' ','@',' ','@',' ','@','\n'},
		   {'@',' ','@',' ','@',' ','@',' ','@',' ','@',' ','@','\n'},
		   {'@',' ','@',' ','@',' ','@',' ','@',' ','@',' ','@','\n'},
		   {'@',' ','@',' ','@',' ','@',' ','@',' ','@',' ','@','\n'},
		   {'@',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','@','\n'},
		   {'@','@','@','@','@','@','@','@','@','@','@','@','@','\n'}};

char Level3[Y][X] = {{'@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','\n'},
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
char Map[Y][X], Map2[Y][X], over, input;
char deenter; //defend '\n' by move() affect gameover
bool Gameover = 0;

int main(){
	Choose_level();

	return 0;
}

void Choose_level(){
	char L;	//Level
	printf("*****     ***        ****        *     *        ***     *     *\n");
	printf("*    *   *   *     **    **     * *   * *      *   *    **    *\n");
	printf("*    *  *     *   *        *    * *   * *     *     *   * *   *\n");
	printf("*****   *     *   *            *   * *   *    *     *   *  *  *\n");
	printf("*       *******   *        *   *   * *   *    *******   *   * *\n");
	printf("*      *       *   **    **   *     *     *  *       *  *    **\n");
	printf("*      *       *     ****     *     *     *  *       *  *     *\n");
	printf("Level 1\n");
	printf("Level 2\n");
	printf("Level 3\n");
	printf("I want to play Level:");
	scanf("%c%c", &L, &deenter);
	if(L == '1'){
		row = 8;
		column = 8;
		total_score = 26;
		Array_copy(Map, Level1);
		Play();
	}
	else if(L == '2'){
		row = 10;
		column = 14;
		total_score = 58;
		Array_copy(Map, Level2);
		Play();
	}
	else if(L == '3'){
		row = 13;
		column = 16;
		total_score = 112;
		Array_copy(Map, Level3);
		Play();
	}
	else{
		printf("Level %d doesn't exist.");
		system("clear");
		Choose_level();
	}
}

void Play(){
	Gpos_x = column - 3;
	Gpos_y = row - 2;
	Point_place(Map);
	Array_copy(Map2, Map);
there:
	for(;;){
		printf("Score:%d     ", score);
		for(int h = heart; h > 0; h--)
			printf("* ");
		printf("\n");
		for(int i = 0; i < row; i++){			//
			for(int j = 0; j < column; j++){	//
				printf(" %c", Map[i][j]);	//print map
			}					//
		}						//
		Eat_point(Map2);
		Array_copy(Map, Map2); //refresh map
		if(Gameover == 0)
			Move();
		Ghost_move();
		usleep(10*1000); //10ms
		system("clear");
		if(Gpos_x == pos_x && Gpos_y == pos_y && heart != 1){
			Gameover = 1;
			heart--;
			printf("You died, You remain %d life.\n", heart);
		here:
			printf("Retry type \'R\', give up type \'E\'.\n");
			scanf("%c%c", &over, &deenter);
			if(over == 'R' || over == 'r'){
				pos_x = 1;
				pos_y = 1;
				Gpos_x = column - 3;
				Gpos_y = row - 2;
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
		else if(Gpos_x == pos_x && Gpos_y == pos_y && heart == 1){
			Gameover = 1;
			printf("You died, and you don't have enough life to contiune.\n");
		where:
			printf("Retry type \'R\', give up type \'E\'.\n");
			scanf("%c%c", &over, &deenter);
			if(over == 'R' || over == 'r'){
				heart = 3;
				score = 0;
				pos_x = 1;
				pos_y = 1;
				Gameover = 0;
				main();
			}
			else if(over == 'E' || over == 'e')
				exit(0);
			else{
				printf("Missing argument to \"%c\"\n", over);
				goto where;
			}
		}
	}
}

void Move(){
	scanf("%c%c", &input, &deenter);

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

void Array_copy(char a[Y][X], char b[Y][X]){
	//assign b to a
	for(int c = 0; c < row; c++){
		for(int d = 0; d < column; d++){
			a[c][d] = b[c][d];
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

void Point_place(char a[Y][X]){
	for(int b = 0; b < row; b++){
		for(int c = 0; c < column; c++){
			if(a[b][c] == ' ')
				a[b][c] = '*';
		}
	}
}

void Eat_point(char a[Y][X]){
	if(a[pos_y][pos_x] == '*'){
		a[pos_y][pos_x] = ' ';
		score++;
	}
}
