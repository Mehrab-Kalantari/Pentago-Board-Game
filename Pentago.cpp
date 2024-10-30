#include <iostream>
#include <conio.h>
#include <cmath>
#include <fstream>
#include <iomanip>
using namespace std;

string matrix[14][26] = {" "};

bool k = true;

int counter = 0;

struct player
{
	string name;
	int lose;
	int win;
	int tie;
};

player p[2] = {{" " , 0 , 0 , 0} , {" " , 0 , 0 , 0}};

struct point
{
	int y;
	int x;
};

void changes(point a, point b);
void movement(point a, point b);
void dots(point a, point b);
void printer();
void normal();
void first_time();
void rotate(point c, point d);
void changeb(point c, point d);
void movementb(point c, point d);
void tie(int dot[][6]);
void win(string c);
int max_of_subs(int dot[][6], int x, int y, int num);
int max_of_main(int dot[][6], int x, int y, int num);
int max_of_cols(int dot[][6], int col, int num);
int max_of_rows(int dot[][6], int row, int num);
void check();
void ranking(player list[], int score[]);
void menu();
void player_turn();
void save_info();
void merge(player list[]);
void sort(player list[], int score[]);
void swap(player &p1, player &p2);
void swap(int &a, int &b);

int main()
{

	cout << "welcome to pentago :D " << endl;  

	menu();

	return 0;
}

// function to change the thickness of a house.
void changes(point a, point b)
{

	normal();
	
	matrix[a.y][a.x] = "\u2554";

	for(int j = a.y; j < b.y+1; j = j + 2)
	{
		for(int i = a.x+1; i < b.x; i++)
		{
			matrix[j][i] = "\u2550";
		}
	}

	matrix[a.y + 1][a.x] = "\u2551";
	matrix[a.y + 1][b.x] = "\u2551";
	matrix[a.y][b.x] = "\u2557";
	matrix[b.y][a.x] = "\u255A";
	matrix[b.y][b.x] = "\u255D";

	movement(a, b);
}

// function to change the value of a point using WASD.
void movement(point a, point b)
{
	printer();

	player_turn();

	char move = getch();

	while(move != '\r')
	{
		if(move == 'w')
		{
			a.y -= 2;
			b.y -= 2;

			if(a.y < 0)
				a.y = 0;

			if(b.y < 2)
				b.y = 2;

			if(a.y == 5)
				a.y--;

			if(b.y == 7)
				b.y--;
		}

		if(move == 's')
		{
			a.y += 2;
			b.y += 2;

			if(a.y == 6)
				a.y++;

			if(a.y > 12)
				a.y = 11;

			if(b.y == 8)
				b.y++;

			if(b.y > 14)
				b.y = 13;

		}

		if(move == 'a')
		{
			a.x -= 4;
			b.x -= 4;

			if(a.x < 0)
				a.x = 0;

			if(a.x == 9)
				a.x--;

			if(b.x == 13)
				b.x--;

			if(b.x < 4)
				b.x = 4;
		}

		if(move == 'd')
		{
			a.x += 4;
			b.x += 4;

			if(a.x == 12)
				a.x++;

			if(a.x > 22)
				a.x = 21;

			if(b.x == 16)
				b.x++;

			if(b.x > 26)
				b.x = 25;
		}

		changes(a, b);
	}

	if(move == '\r')
	{

		// if player tries to place a value in a place which is already full.
		if(matrix[(a.y + b.y) / 2][(a.x + b.x) / 2] == " ")
		{
			dots(a, b);
		}

		else
			movement(a, b);

		point c, d;

		c.x = 0;
		c.y = 0;
		d.x = 12;
		d.y = 6;

		k = !k;

		check();

		changeb(c, d);
	}	

}

// giving each house the right value (X / O).
void dots(point a, point b)
{
	if(k)
	{
		matrix[(a.y + b.y) / 2][(a.x + b.x) / 2] = 'X';
	}

	if(!k)
	{
		matrix[(a.y + b.y) / 2][(a.x + b.x) / 2] = 'O';
	}

	printer();
}

void player_turn()
{
	if(k)
	{
		cout << p[0].name << "'s turn. as X : " << endl;
	}

	if(!k)
	{
		cout << p[1].name << "'s turn. as O : " << endl;
	}
}

// function to print each step.
void printer()
{
	system("cls");

	for(int j = 0; j < 14; j++)
	{
		for(int i = 0; i < 26; i++)
		{
			cout << matrix[j][i];
		}
		cout << endl;
	}
}

// giving each place in matrix a value to form a box.
void first_time()
{
	for(int j = 0; j < 7; j = j + 2)
	{
		for(int i = 0; i < 12; i++)
		{
			matrix[j][i] = "\u2501";
		}
	}

	for(int j = 1; j < 7; j = j  + 2)
	{
		for(int i = 1; i < 12; i++)
		{
			matrix[j][i] = " ";
		}
	}

	for(int j = 1; j < 7; j = j + 2)
	{
		for(int i = 0; i < 13; i = i + 4)
		{
			matrix[j][i] = "\u2503";
		}
	}

	matrix[0][0] = "\u250F";
	matrix[0][4] = "\u2533";
	matrix[0][8] = "\u2533";
	matrix[0][12] = "\u2513";
	matrix[2][0] = "\u2523";
	matrix[2][4] = "\u254B";
	matrix[2][8] = "\u254B";
	matrix[2][12] = "\u252B";
	matrix[4][0] = "\u2523";
	matrix[4][4] = "\u254B";
	matrix[4][8] = "\u254B";
	matrix[4][12] = "\u252B";
	matrix[6][0] = "\u2517";
	matrix[6][4] = "\u253B";
	matrix[6][8] = "\u253B";
	matrix[6][12] = "\u251B";

	for(int j = 0; j < 7; j++)
	{
		for(int i = 13; i < 26; i++)
		{
			matrix[j][i] = matrix[j][i-13];
		}
	}

	for(int j = 7; j < 14; j++)
	{
		for(int i = 0; i < 13; i++)
		{
			matrix[j][i] = matrix[j-7][i];
		}
	}

	for(int j = 7; j < 14; j++)
	{
		for(int i = 13; i < 26; i++)
		{
			matrix[j][i] = matrix[j-7][i-13];
		}
	}

}

// after changing a a house's thickness we have to make it normal again.
void normal()
{
	for(int j = 0; j < 7; j = j + 2)
	{
		for(int i = 0; i < 12; i++)
		{
			matrix[j][i] = "\u2501";
		}
	}

	for(int j = 1; j < 7; j = j + 2)
	{
		for(int i = 0; i < 13; i = i + 4)
		{
			matrix[j][i] = "\u2503";
		}
	}

	matrix[0][0] = "\u250F";
	matrix[0][4] = "\u2533";
	matrix[0][8] = "\u2533";
	matrix[0][12] = "\u2513";
	matrix[2][0] = "\u2523";
	matrix[2][4] = "\u254B";
	matrix[2][8] = "\u254B";
	matrix[2][12] = "\u252B";
	matrix[4][0] = "\u2523";
	matrix[4][4] = "\u254B";
	matrix[4][8] = "\u254B";
	matrix[4][12] = "\u252B";
	matrix[6][0] = "\u2517";
	matrix[6][4] = "\u253B";
	matrix[6][8] = "\u253B";
	matrix[6][12] = "\u251B";

	for(int j = 0; j < 7; j = j + 2)
	{
		for(int i = 13; i < 26; i++)
		{
			matrix[j][i] = "\u2501";
		}
	}

	for(int j = 1; j < 7; j = j + 2)
	{
		for(int i = 13; i < 26; i = i + 4)
		{
			matrix[j][i] = "\u2503";
		}
	}

	matrix[0][13] = "\u250F";
	matrix[0][17] = "\u2533";
	matrix[0][21] = "\u2533";
	matrix[0][25] = "\u2513";
	matrix[2][13] = "\u2523";
	matrix[2][17] = "\u254B";
	matrix[2][21] = "\u254B";
	matrix[2][25] = "\u252B";
	matrix[4][13] = "\u2523";
	matrix[4][17] = "\u254B";
	matrix[4][21] = "\u254B";
	matrix[4][25] = "\u252B";
	matrix[6][13] = "\u2517";
	matrix[6][17] = "\u253B";
	matrix[6][21] = "\u253B";
	matrix[6][25] = "\u251B";

	for(int j = 7; j < 14; j = j + 2)
	{
		for(int i = 13; i < 26; i++)
		{
			matrix[j][i] = "\u2501";
		}
	}

	for(int j = 8; j < 14; j = j + 2)
	{
		for(int i = 13; i < 26; i = i + 4)
		{
			matrix[j][i] = "\u2503";
		}
	}

	matrix[7][13] = "\u250F";
	matrix[7][17] = "\u2533";
	matrix[7][21] = "\u2533";
	matrix[7][25] = "\u2513";
	matrix[9][13] = "\u2523";
	matrix[9][17] = "\u254B";
	matrix[9][21] = "\u254B";
	matrix[9][25] = "\u252B";
	matrix[11][13] = "\u2523";
	matrix[11][17] = "\u254B";
	matrix[11][21] = "\u254B";
	matrix[11][25] = "\u252B";
	matrix[13][13] = "\u2517";
	matrix[13][17] = "\u253B";
	matrix[13][21] = "\u253B";
	matrix[13][25] = "\u251B";

	for(int j = 7; j < 14; j = j + 2)
	{
		for(int i = 0; i < 13; i++)
		{
			matrix[j][i] = "\u2501";
		}
	}

	for(int j = 8; j < 14; j = j + 2)
	{
		for(int i = 0; i < 13; i = i + 4)
		{
			matrix[j][i] = "\u2503";
		}
	}	

	matrix[7][0] = "\u250F";
	matrix[7][4] = "\u2533";
	matrix[7][8] = "\u2533";
	matrix[7][12] = "\u2513";
	matrix[9][0] = "\u2523";
	matrix[9][4] = "\u254B";
	matrix[9][8] = "\u254B";
	matrix[9][12] = "\u252B";
	matrix[11][0] = "\u2523";
	matrix[11][4] = "\u254B";
	matrix[11][8] = "\u254B";
	matrix[11][12] = "\u252B";
	matrix[13][0] = "\u2517";
	matrix[13][4] = "\u253B";
	matrix[13][8] = "\u253B";
	matrix[13][12] = "\u251B";

}

// function to change thickness of a big house.
void changeb(point c, point d)
{
	normal();

	for(int j = c.y; j < d.y+1; j += 6)
	{
		for(int i = c.x+1; i < d.x; i++)
		{
			matrix[j][i] = "\u2550";
		}
	}

	for(int j = c.y+1; j < d.y; j++)
	{
		for(int i = c.x; i < d.x+1; i += 12)
		{
			matrix[j][i] = "\u2551";
		}
	}

	matrix[c.y][c.x] = "\u2554";
	matrix[c.y][d.x] = "\u2557";
	matrix[d.y][c.x] = "\u255A";
	matrix[d.y][d.x] = "\u255D";

	movementb(c, d);
}

// function to move in big house's using WASD.
void movementb(point c, point d)
{
	printer();

	char move = getch();

	while(move != '\r')
	{
		if(move == 'w')
		{
			c.y -= 7;
			d.y -= 7;

			if(c.y < 0)
			{
				c.y = 0;
			}

			if(d.y < 6)
			{
				d.y = 6;
			}
		}

		if(move == 's')
		{
			c.y += 7;
			d.y += 7;

			if(c.y > 7)
			{
				c.y = 7;
			}

			if(d.y > 13)
			{
				d.y = 13;
			}
		}

		if(move == 'a')
		{
			c.x -= 13;
			d.x -= 13;

			if(c.x < 0)
			{
				c.x = 0;
			}

			if(d.x < 12)
			{
				d.x = 12;
			}
		}

		if(move == 'd')
		{
			c.x += 13;
			d.x += 13;

			if(d.x > 25)
			{
				d.x = 25;
			}

			if(c.x > 13)
			{
				c.x = 13;
			}
		}

		changeb(c, d);
	}
	
	if(move == '\r')
	{
		rotate(c, d);

		check();

		point a,b;
		a.x = 0;
		a.y = 0;
		b.x = 4;
		b.y = 2;

		changes(a, b);

		printer();

		movement(a, b);

	}	
}

// function to rotate a big house.
void rotate(point c, point d)
{
	char turn;

	cout << "how do you wanna rotate this square ? (l / r)  : ";
	cin >> turn;

	if(turn != 'l' && turn != 'r')
	{
		rotate(c, d);
	}

	string dot[3][3];

	for(int j = c.y+1, p = 0; j < d.y; j += 2, p++)
	{
		for(int i = c.x+2, q = 0; i < d.x; i += 4, q++)
		{
			dot[p][q] = matrix[j][i];
		}
	}

	if(turn == 'l')
	{
		string tmp[3][3];

		for(int j = 0; j < 3; j++)
		{
			for(int  i = 0; i < 3; i++)
			{
				tmp[j][i] = dot[i][2-j];
			}
		}

		for(int j = 0; j < 3; j++)
		{
			for(int  i = 0; i < 3; i++)
			{
				dot[j][i] = tmp[j][i];
			}
		}
	}

	if(turn == 'r')
	{
		string tmp[3][3];

		for(int j = 0; j < 3; j++)
		{
			for(int  i = 0; i < 3; i++)
			{
				tmp[j][i] = dot[2-i][j];
			}
		}

		for(int j = 0; j < 3; j++)
		{
			for(int i = 0; i < 3; i++)
			{
				dot[j][i] = tmp[j][i];
			}
		}
	}

	for(int j = c.y+1, p = 0; j < d.y; j += 2, p++)
	{
		for(int i = c.x+2, q = 0; i < d.x; i += 4, q++)
		{
			matrix[j][i] = dot[p][q];
		}
	}

	printer();
}

// checking if anyone has one.
void check()
{

	int dot[6][6];

	for(int j = 1, p = 0; j < 7; j += 2, p++)
	{
		for(int i = 2, q = 0; i < 11; i += 4, q++)
		{
			if(matrix[j][i] == "X")
				dot[p][q] = 1;

			else if(matrix[j][i] == "O")
				dot[p][q] = -1;

			else if(matrix[j][i] == " ")
				dot[p][q] = 0;
		}
	}

	for(int j = 8, p = 3; j < 13; j += 2, p++)
	{
		for(int i = 2, q = 0; i < 11; i += 4, q++)
		{
			if(matrix[j][i] == "X")
				dot[p][q] = 1;

			else if(matrix[j][i] == "O")
				dot[p][q] = -1;

			else if(matrix[j][i] == " ")
				dot[p][q] = 0;
		}
	}

	for(int j = 1, p = 0; j < 7; j += 2, p++)
	{
		for(int i = 15, q = 3; i < 24; i += 4, q++)
		{
			if(matrix[j][i] == "X")
				dot[p][q] = 1;

			else if(matrix[j][i] == "O")
				dot[p][q] = -1;

			else if(matrix[j][i] == " ")
				dot[p][q] = 0;
		}
	}

	for(int j = 8, p = 3; j < 13; j += 2, p++)
	{
		for(int i = 15, q = 3; i < 24; i += 4, q++)
		{
			if(matrix[j][i] == "X")
				dot[p][q] = 1;

			else if(matrix[j][i] == "O")
				dot[p][q] = -1;

			else if(matrix[j][i] == " ")
				dot[p][q] = 0;
		}
	}

	for(int j = 0; j < 6; j++)
	{
		if(max_of_rows(dot, j, 1) >= 5)
		{
			win("X");
		}
	}

	for(int i = 0; i < 6; i++)
	{
		if(max_of_cols(dot, i, 1) >= 5)
		{
			cout << '\a' << endl;

			win("X");
		}
	}

	if(max_of_main(dot, 0, 0, 1) >= 5)
	{
		win("X");
	}

	if(max_of_main(dot, 0, 1, 1) >= 5)
	{
		win("X");
	}

	if(max_of_main(dot, 1, 0, 1) >= 5)
	{
		win("X");
	}

	if(max_of_subs(dot, 5, 0, 1) >= 5)
	{
		win("X");
	}

	if(max_of_subs(dot, 5, 1, 1) >= 5)
	{
		win("X");
	}

	if(max_of_subs(dot, 4, 0, 1) >= 5)
	{
		win("X");
	}

	for(int j = 0; j < 6; j++)
	{
		if(max_of_rows(dot, j, -1) >= 5)
		{
			win("O");
		}
	}

	for(int i = 0; i < 6; i++)
	{
		if(max_of_cols(dot, i, -1) >= 5)
		{
			win("O");
		}
	}

	if(max_of_main(dot, 0, 0, -1) >= 5)
	{
		win("O");
	}

	if(max_of_main(dot, 0, 1, -1) >= 5)
	{
		win("O");
	}

	if(max_of_main(dot, 1, 0, -1) >= 5)
	{
		win("O");
	}

	if(max_of_subs(dot, 5, 0, -1) >= 5)
	{
		win("O");
	}

	if(max_of_subs(dot, 5, 1, -1) >= 5)
	{
		win("O");
	}

	if(max_of_subs(dot, 4, 0, -1) >= 5)
	{
		win("O");
	}

	tie(dot);

	return;
}

// checking for the maximum number of a character in a row.
int max_of_rows(int dot[][6], int row, int num)
{
	int maxsub = 0;
	int maxT = 0;

	for(int i = 0; i < 6; i++)
	{
		if(dot[row][i] == num)
		{
			maxsub++;

			maxT = max(maxT, maxsub);
		}

		else
		{
			maxsub = 0;
		}
	}

	return maxT;
}

// checking for the maximum number of a character in a column. 
int max_of_cols(int dot[][6], int col, int num)
{
	int maxsub = 0;
	int maxT = 0;

	for(int j = 0; j < 6; j++)
	{
		if(dot[j][col] == num)
		{
			maxsub++;

			maxT = max(maxT, maxsub);
		}

		else
		{
			maxsub = 0;
		}
	}

	return maxT;
}

// checking for the maximum number of a character in a diameter.
int max_of_main(int dot[][6], int x, int y, int num)
{
	int maxsub = 0;
	int maxT = 0;

	for(; x < 6 && y < 6 ; x++, y++)
	{
		if(dot[y][x] == num)
		{
			maxsub++;

			maxT = max(maxT, maxsub);
		}

		else
		{
			maxsub = 0;
		}
	}

	return maxT;

}

// checking for the maximum number of a character in a diameter.
int max_of_subs(int dot[][6], int x, int y, int num)
{
	int maxsub = 0;
	int maxT = 0;

	for(; x >= 0 && y < 6 ; x--, y++)
	{
		if(dot[y][x] == num)
		{
			maxsub++;

			maxT = max(maxT, maxsub);
		}

		else
		{
			maxsub = 0;
		}
	}

	return maxT;
}

void win(string c)
{
	if(c == "X")
	{
		p[0].win++;
		p[1].lose++;

		cout << "GG! " << p[0].name << " has won!" << endl;
	}

	if(c == "O")
	{
		p[0].lose++;
		p[1].win++;

		cout << "GG! " << p[1].name << " has won!" << endl;
	}

	k = true;

	first_time();

	save_info();

	menu();
}

// checking if it's a tie.
void tie(int dot[][6])
{
	for(int j = 0; j < 6; j++)
	{
		for(int i = 0; i < 6; i++)
		{
			if(dot[j][i] == 0)
				return;
		}
	}

	p[0].tie++;
	p[1].tie++;

	k = true;

	first_time();

	save_info();

	cout << "it's a tie!" << endl;

	menu();
}


void menu()
{
	int action;

	cout << "1- enter 1 to start the game : " << endl;
	cout << "2- enter 2 to see the rankings : " << endl;
	cout << "3- enter 3 to exit the game : " << endl;

	cin >> action;

	if(action == 1)
	{
		cout << "please enter player1's name : ";
		cin >> p[0].name;
		cout << "please enter player2's name : ";
		cin >> p[1].name;
		cout << endl;

		point a,b;
		a.x = 0;
		a.y = 0;
		b.x = 4;
		b.y = 2;

		first_time();

		changes(a, b);

		movement(a, b);

	}

	else if(action == 2)
	{
		ifstream infoT("info.text");

		while(true)
		{
			string str;
			getline(infoT, str);

			if(str.length() == 0)
			{
				infoT.close();
				break;
			}

			counter++;
		}

		player list[counter];

		merge(list);
	}

	else if(action == 3)
		exit(0);

	else
	{
		system("cls");

		cout << "please try again" << endl;
		
		menu();
	}
}

void save_info() 
{
	ofstream player_info("info.text", ios::app);

	for(int i = 0; i < 2; i++)
	{
		player_info << p[i].name<< " " << p[i].lose << " " << p[i].win << " " << p[i].tie << " " << endl;
	}
	player_info.close();
}

// we may have same names in multiple lines in our file.
void merge(player list[])
{

	ifstream info("info.text");

	info >> list[0].name >> list[0].lose >> list[0].win >> list[0].tie;

	int len = 0;

	while(true)
	{
		bool flag = true;
		
		string str;
		int temp[3];
		info >> str >> temp[0] >> temp[1] >> temp[2];

		if(str.length() == 0)
		{	
			info.close();
			break;
		}
			
		for(int i = 0; i <= len; i++)
		{
			if(str == list[i].name)
			{
				flag = false;
				list[i].lose += temp[0];
				list[i].win += temp[1];
				list[i].tie += temp[2];
			}
		}
		
		if(flag)
		{
			len++;
			list[len] = {str , temp[0] , temp[1] , temp[2]};
		}
	}	

	counter = len+1;

	int score[counter];
	
	// each player's score :
	
	for(int q = 0; q < counter; q++)
		score[q] = (-3*list[q].lose) + (3*list[q].win) + (list[q].tie);
	
	sort(list, score);
}

//sorting the names using score.
void sort(player list[], int score[])
{
	for(int i = 0; i < counter-1; i++)
	{
		for(int j = 0; j < counter-1; j++)
		{
			if(score[j] < score[j+1])
			{
				swap(score[j] , score[j+1]);
				swap(list[j] , list[j+1]);
			}
		}
	}

	ranking(list, score);
}

void swap(player &p1, player &p2)
{
	player temp = p1;
	p1 = p2;
	p2 = temp;
}

void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

//drawing a box to show the rankings.
void ranking(player list[], int score[])
{
	system("cls");

	cout << "           \a   "<< "* RANKING *" <<endl;
	cout << "\u250c";
	
	for(int o = 0; ; o++)
	{
		if(o == 3 || o == 18 || o == 22 || o == 27 || o == 31)
		{
			cout << "\u252c";
		}
		
		else if (o==37)
		{
			cout << "\u2510" << endl;
			break;
		}
		
		else
		{
			cout << "\u2500";
		}
	}
	
	cout << "\u2502   \u2502" << setw(9) << "Name" << "     \u2502Win\u2502Lose\u2502Tie\u2502Score\u2502" << endl;
	cout << "\u251c";
	
	for(int u = 0; ; u++)
	{
		if(u == 3 || u == 18 || u == 22 || u == 27 || u == 31)
		{
			cout << "\u253c";
		}
		
		else if (u == 37)
		{
			cout << "\u2524" << endl;
			break;
		}
		
		else
		{
			cout << "\u2500";
		}
	}

	for(int i = 0; i < counter; i++)
	{
		cout << "\u2502" << left << setw(3) << i+1 << "\u2502" << setw(14) << list[i].name;

		cout << "\u2502" << setw(3) << list[i].win << "\u2502" << setw(4);

		cout << list[i].lose << "\u2502" << setw(3) << list[i].tie;

		cout << "\u2502" << setw(5) << score[i] << "\u2502" << endl;
			
		if(i == counter-1)
		{
			cout << "\u2514\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500";

			cout << "\u2500\u2500\u2500\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2534\u2500";

			cout << "\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2500\u2500\u2518" << endl;
		}
			
		else 
		{
			cout << "\u251c\u2500\u2500\u2500\u253c\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500";

			cout << "\u2500\u2500\u2500\u2500\u2500\u253c\u2500\u2500\u2500\u253c\u2500\u2500\u2500\u2500";

			cout << "\u253c\u2500\u2500\u2500\u253c\u2500\u2500\u2500\u2500\u2500\u2524" << endl;
		}
	}

	p[0].lose = 0;
	p[0].win = 0;
	p[0].tie = 0;

	p[1].lose = 0;
	p[1].win = 0;
	p[1].tie = 0;
	
	counter = 0;

	menu();
	
}