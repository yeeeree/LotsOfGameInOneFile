#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define X 16 //column
#define Y 13 //row


//Pacman
void Pacman();
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


//2048
void TOFE(); //Two_O_Four_Eight
void NND(int a, int b, char c[10][10]); //Now_Number_Detect
void Array_assign(char e[10][10], char f[10][10]);
char temp;
//0 0
char ZERO[10][10] = {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
	       	     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};
//2 A
char TWO[10][10] = {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
	       	    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		    {' ',' ',' ','*','*','*','*',' ',' ',' '},
		    {' ',' ',' ',' ',' ',' ','*',' ',' ',' '},
		    {' ',' ',' ','*','*','*','*',' ',' ',' '},
		    {' ',' ',' ','*',' ',' ',' ',' ',' ',' '},
		    {' ',' ',' ','*',' ',' ',' ',' ',' ',' '},
		    {' ',' ',' ','*','*','*','*',' ',' ',' '},
		    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};

//4 B
char FOUR[10][10] = {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		     {' ',' ',' ','*',' ',' ','*',' ',' ',' '},
		     {' ',' ',' ','*',' ',' ','*',' ',' ',' '},
		     {' ',' ',' ','*',' ',' ','*',' ',' ',' '},
		     {' ',' ',' ','*','*','*','*',' ',' ',' '},
		     {' ',' ',' ',' ',' ',' ','*',' ',' ',' '},
		     {' ',' ',' ',' ',' ',' ','*',' ',' ',' '},
		     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};

//8 C
char EIGHT[10][10] = {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
	       	      {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		      {' ',' ',' ','*','*','*','*',' ',' ',' '},
		      {' ',' ',' ','*',' ',' ','*',' ',' ',' '},
		      {' ',' ',' ','*','*','*','*',' ',' ',' '},
		      {' ',' ',' ','*',' ',' ','*',' ',' ',' '},
		      {' ',' ',' ','*',' ',' ','*',' ',' ',' '},
		      {' ',' ',' ','*','*','*','*',' ',' ',' '},
		      {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		      {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};

//16 D
char ONE_SIX[10][10] = {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			{' ',' ','*',' ','*','*','*','*',' ',' '},
			{' ',' ','*',' ','*',' ',' ',' ',' ',' '},
			{' ',' ','*',' ','*','*','*','*',' ',' '},
			{' ',' ','*',' ','*',' ',' ','*',' ',' '},
			{' ',' ','*',' ','*',' ',' ','*',' ',' '},
			{' ',' ','*',' ','*','*','*','*',' ',' '},
			{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};

//32 E
char THREE_TWO[10][10] = {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		  	  {' ',' ','*','*',' ','*','*','*',' ',' '},
		    	  {' ',' ',' ','*',' ',' ',' ','*',' ',' '},
			  {' ',' ','*','*',' ','*','*','*',' ',' '},
			  {' ',' ',' ','*',' ','*',' ',' ',' ',' '},
			  {' ',' ',' ','*',' ','*',' ',' ',' ',' '},
			  {' ',' ','*','*',' ','*','*','*',' ',' '},
			  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};

//64 F
char SIX_FOUR[10][10] = {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			 {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		  	 {' ',' ','*','*',' ','*',' ','*',' ',' '},
		    	 {' ',' ','*',' ',' ','*',' ','*',' ',' '},
			 {' ',' ','*','*','*','*','*','*',' ',' '},
			 {' ',' ','*',' ','*',' ',' ','*',' ',' '},
			 {' ',' ','*',' ','*',' ',' ','*',' ',' '},
			 {' ',' ','*','*','*',' ',' ','*',' ',' '},
			 {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			 {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};

//128 G
char ONE_TWO_EIGHT[10][10] = {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			      {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		  	      {' ','*',' ','*','*','*',' ','*','*','*'},
		    	      {' ','*',' ',' ',' ','*',' ','*',' ','*'},
			      {' ','*',' ','*','*','*',' ','*','*','*'},
			      {' ','*',' ','*',' ',' ',' ','*',' ','*'},
			      {' ','*',' ','*',' ',' ',' ','*',' ','*'},
			      {' ','*',' ','*','*','*',' ','*','*','*'},
			      {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			      {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};

//256 H
char TWO_FIVE_SIX[10][10] = {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		  	     {' ','*','*',' ','*','*',' ','*','*','*'},
		    	     {' ',' ','*',' ','*',' ',' ','*',' ',' '},
			     {' ','*','*',' ','*','*',' ','*','*','*'},
			     {' ','*',' ',' ',' ','*',' ','*',' ','*'},
			     {' ','*',' ',' ',' ','*',' ','*',' ','*'},
			     {' ','*','*',' ','*','*',' ','*','*','*'},
			     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};

//512 I
char FIVE_ONE_TWO[10][10] = {{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		  	     {' ','*','*',' ','*',' ','*','*','*',' '},
		    	     {' ','*',' ',' ','*',' ',' ',' ','*',' '},
			     {' ','*','*',' ','*',' ','*','*','*',' '},
			     {' ',' ','*',' ','*',' ','*',' ',' ',' '},
			     {' ',' ','*',' ','*',' ','*',' ',' ',' '},
			     {' ','*','*',' ','*',' ','*','*','*',' '},
			     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};

//1024 J
char ONE_ZERO_TWO_FOUR[10][10] = {{'*',' ',' ',' ','*','*','*',' ',' ',' '},
				  {'*',' ',' ',' ',' ',' ','*',' ',' ',' '},
			  	  {'*',' ',' ',' ','*','*','*',' ',' ',' '},
			    	  {'*',' ',' ',' ','*',' ',' ',' ',' ',' '},
				  {'*',' ',' ',' ','*','*','*',' ',' ',' '},
				  {' ','*','*','*',' ',' ',' ','*',' ','*'},
				  {' ','*',' ','*',' ',' ',' ','*',' ','*'},
				  {' ','*',' ','*',' ',' ',' ','*','*','*'},
				  {' ','*',' ','*',' ',' ',' ',' ',' ','*'},
				  {' ','*','*','*',' ',' ',' ',' ',' ','*'}};

//2048 K
char TWO_ZERO_FOUR_EIGHT[10][10] = {{'*','*',' ',' ','*',' ','*',' ',' ',' '},
				    {' ','*',' ',' ','*',' ','*',' ',' ',' '},
		  		    {'*','*',' ',' ','*','*','*',' ',' ',' '},
		    		    {'*',' ',' ',' ',' ',' ','*',' ',' ',' '},
				    {'*','*',' ',' ',' ',' ','*',' ',' ',' '},
				    {' ',' ','*','*','*',' ',' ','*','*','*'},
				    {' ',' ','*',' ','*',' ',' ','*',' ','*'},
				    {' ',' ','*',' ','*',' ',' ','*','*','*'},
				    {' ',' ','*',' ','*',' ',' ','*',' ','*'},
				    {' ',' ','*','*','*',' ',' ','*','*','*'}};
char Locate[4][4] = {{'0','0','0','0'},
		     {'0','0','0','0'},
		     {'0','0','0','0'},
		     {'0','0','0','0'}};


//Main
int main(){
	int play_code;
	printf("\033[95m*        ****      ***     *****   ****   *****    \n");
	printf("\033[95m*       *    *    *   *      *    *    *  *        \n");
	printf("\033[95m*      *      *  *           *   *      * *****    \n");
	printf("\033[95m*      *      *  *  ***      *   *      * *        \n");
	printf("\033[95m*       *    *    *  **      *    *    *  *        \n");
	printf("\033[95m*****ot  ****f     ** *ame *****n  ****ne *ile     \n");
	printf("1. Pacman\n");
	printf("2. 2048\n");
	printf("Type the code to play game.");
	scanf("%d", &play_code);
	if(play_code == 1)
		Pacman();
	else if(play_code == 2)
		TOFE();

	return 0;
}


//Pacman
void Pacman(){
	char L;	//Level
	printf("\033[95m*****     ***        ****        *     *        ***     *     *\n");
	printf("\033[95m*    *   *   *     **    **     * *   * *      *   *    **    *\n");
	printf("\033[95m*    *  *     *   *        *    * *   * *     *     *   * *   *\n");
	printf("\033[95m*****   *     *   *            *   * *   *    *     *   *  *  *\n");
	printf("\033[95m*       *******   *        *   *   * *   *    *******   *   * *\n");
	printf("\033[95m*      *       *   **    **   *     *     *  *       *  *    **\n");
	printf("\033[95m*      *       *     ****     *     *     *  *       *  *     *\033[0m\n");
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
		printf("Level \033[91m%d\033[0m doesn't exist.");
		system("clear");
		Pacman();
	}
}

void Play(){
	Gpos_x = column - 3;
	Gpos_y = row - 2;
	Point_place(Map);
	Array_copy(Map2, Map);
there:
	for(;;){
		printf("\033[93mScore\033[0m:%d     ", score);
		for(int h = heart; h > 0; h--)
			printf("\033[91m*\033[0m ");
		for(int h = 3 - heart; h > 0; h--)
			printf("\033[37mo\033[0m ");
		printf("\n");
		for(int i = 0; i < row; i++){			
			for(int j = 0; j < column; j++){
				if(Map[i][j] == '\n')					//D	
					printf(" %c", Map[i][j]);			//i
				else if(Map[i][j] == '@')				//s
					printf("\033[36;46m %c\033[0m", Map[i][j]);	//p
				else if(Map[i][j] == ' ')				//l
					printf(" %c", Map[i][j]);			//a
				else if(Map[i][j] == '*')				//y
					printf(" \033[33m%c\033[0m", Map[i][j]);	//
				else if(Map[i][j] == 'C')				//m
					printf(" \033[93m%c\033[0m", Map[i][j]);	//a
				else if(Map[i][j] == 'M')				//p
					printf(" \033[35m%c\033[0m", Map[i][j]);	//
			}					
		}						
		Eat_point(Map2);
		Array_copy(Map, Map2); //refresh map
		if(Gameover == 0)
			Move();
		Ghost_move();
		usleep(10*1000); //10ms,100fps
		system("clear");
		if(Gpos_x == pos_x && Gpos_y == pos_y && heart != 1){
			Gameover = 1;
			heart--;
			printf("You died, You remain \033[91m%d\033[0m life.\n", heart);
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
				Pacman();
			}
			else if(over == 'E' || over == 'e')
				exit(0);
			else{
				printf("Missing argument to \"%c\"\n", over);
				goto where;
			}
		}
		if(score == total_score){
			system("clear");
			printf("\033[93mYou Won!\033[0m\n");
			printf("You perfectly did that will only %d hearts!\n", 4 - heart);
		everywhere:
			printf("If you want to try another level type \'R\'. ");
			printf("Want try another games type \'T\'. ");
			printf("Leave type \'E\'.\n");
			scanf("%c%c", &over, &deenter);
			if(over == 'R' || over == 'r'){
				heart = 3;
				score = 0;
				pos_x = 1;
				pos_y = 1;
				Gameover = 0;
				Pacman();
			}
			else if(over == 'T' || over == 't'){
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
				goto everywhere;
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


//2048
void TOFE(){
	char e[10][10];
	printf("\033[95m *****     ****          *     ****  \n");
	printf("\033[95m*     *   *    *      *  *    *    * \n");
	printf("\033[95m      *  *      *    *   *    *    * \n");
	printf("\033[95m      *  *      *   *    *     ****  \n");
	printf("\033[95m     *   *      *  *********  *    * \n");
	printf("\033[95m   *     *      *        *   *      *\n");
	printf("\033[95m *        *    *         *   *      *\n");
	printf("\033[95m*******    ****          *    ****** \033[0m\n");
	printf("Welcome to 2048 game.\n");
	printf("Press anykey to \033[5mstart\033[0m.\n");
	if(scanf("%c", &temp)){
		for(;;){
			for(int h = 0; h < 4; h++){//h_is_height_4_rows
				for(int b = 0; b < 2; b++){//b_is_broder_width
					for(int a = 0; a < 50; a++)//a_is_whole_wide
						printf("* ");
					printf("\n");
				}
				for(int g = 0; g < 10; g++){//g_is_block_height
					for(int f = 0; f < 4; f++){//f_is_4_column
						for(int c = 0; c < 2; c++)//c_is_broder
							printf("* ");
						for(int d = 0; d < 10; d++){//d_is_a_block_width
							NND(h, f, e);
							printf("%c ", e[f][d]);
						}
					}
					printf("* * \n");
				}
			}
			for(int b = 0; b < 2; b++){//b_is_broder		//Bottom_border
				for(int a = 0; a < 50; a++)//a_is_whole_wide	//
					printf("* ");
				printf("\n");
			}
			system("clear");
			usleep(10*1000); //10ms 100fps
		}
	}

}

void NND(int a, int b, char c[10][10]){ //a_is_row,b_is_column,c_is_changed_array
	switch(Locate[a][b]){
		case '0':
			Array_assign(c, ZERO);
			break;
		case 'A':
			Array_assign(c, TWO);
			break;		
		case 'B':
			Array_assign(c, FOUR);
			break;		
		case 'C':
			Array_assign(c, EIGHT);
			break;		
		case 'D':
			Array_assign(c, ONE_SIX);
			break;		
		case 'E':
			Array_assign(c, THREE_TWO);
			break;		
		case 'F':
			Array_assign(c, SIX_FOUR);
			break;		
		case 'G':
			Array_assign(c, ONE_TWO_EIGHT);
			break;		
		case 'H':
			Array_assign(c, TWO_FIVE_SIX);
			break;		
		case 'I':
			Array_assign(c, FIVE_ONE_TWO);
			break;		
		case 'J':
			Array_assign(c, ONE_ZERO_TWO_FOUR);
			break;		
		case 'K':
			Array_assign(c, TWO_ZERO_FOUR_EIGHT);
			break;		

	}
}


void Array_assign(char e[10][10], char f[10][10]){
	//assign f to e
	for(int c = 0; c < 10; c++){
		for(int d = 0; d < 10; d++){
			e[c][d] = f[c][d];
		}
	}
}
