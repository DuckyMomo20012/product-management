#include "function.h"
CELL p[50][5];
PRODUCT q[50];
int X = 3;
int Y = 3;
void textColor(int x) {
	HANDLE color;
	color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, x); // TO MAU
}

void move(int x, int y) {
	HANDLE hConsoleOutput;
	COORD Cursor;
	Cursor.X = x;
	Cursor.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor); // DI CHUYEN 
}

void moveUp() {
	if (Y > p[0][0].y) {
		Y -= 2;
		move(X, Y);
	}
}

void moveDown() {
	if (Y < p[50 - 1][5 - 1].y) {
		Y += 2;
		move(X, Y);
	}
}

void moveRight() {
	if (X < p[50 - 1][5 - 1].x) {
		X += 30;
		move(X, Y);
	}
}

void moveLeft() {
	if (X > p[0][0].x) {
		X -= 30;
		move(X, Y);
	}
}

void resizeConsole(int width, int height) {
	HWND console = GetConsoleWindow();
	RECT r;
	LONG style = GetWindowLong(console, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(console, GWL_STYLE, style); // LAM MO NUT MAXIMIZE
	GetWindowRect(console, &r); // THAY DOI KICH CO CMD
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void resetData() {
	for (int i = 0; i < 50; i++) { // MOI HANG CACH NHAU 2 O
		for (int j = 0; j < 5; j++) { // MOI COT CACH NHAU 50 O
			p[i][j].x = j * 30 + LEFT;
			p[i][j].y = i * 2 + TOP;
			p[i][j].m = 0;
		}
	}
}

void drawBoard() {
	for (int i = 2; i < 102; i++) {
		for (int j = 1; j < 145; j++) {
			if (i % 2 == 0) {
				move(j, i);
				cout << "_";
			}
			if (i == 2) {
				move(j, i);
				printf("%c", 219);
			}
			if (i == 101) {
				move(j, i + 1);
				printf("%c", 219);
			}
		}
		move(1, i);
		printf("%c", 219);
		move(30, i);
		printf("%c", 219);
		move(60, i);
		printf("%c", 219);
		move(90, i);
		printf("%c", 219);
		move(120, i);
		printf("%c", 219);
		move(144, i);
		printf("%c", 219);
	}
}

void tab() {
	time_t now = time(0);
	tm newtime;
	localtime_s(&newtime, &now);
	move(p[0][0].x, p[0][0].y);
	cout << "NOW: " << newtime.tm_mday << "/" << 1 + newtime.tm_mon << "/" << 1900 + newtime.tm_year;
	move(p[0][1].x, p[0][1].y);
	cout << "LOAD";
	move(p[0][2].x, p[0][2].y);
	cout << "SAVE";
	move(p[0][3].x, p[0][3].y);
	cout << "FIND";
	move(p[0][4].x, p[0][4].y);
	cout << "EXIT";
}

void header(){
	move(p[1][0].x, p[1][0].y);
	cout << "ID";
	move(p[1][1].x, p[1][1].y);
	cout << "NAME";
	move(p[1][2].x, p[1][2].y);
	cout << "EXP";
	move(p[1][3].x, p[1][3].y);
	cout << "COMPANY";
	move(p[1][4].x, p[1][4].y);
	cout << "MFG";
}

void print() {
	for (int i = 2; i < 50; i++) {
		for (int j = 0; j < 5; j++) {
			move(p[i][j].x, p[i][j].y);
			if (j == 0) {
				if (q[i].id != " ") cout << q[i].id;
			}
			if (j == 1) {
				if (q[i].name != " ") cout << q[i].name;
			}
			if (j == 2) {
				if (q[i].exp != " ") {
					if (q[i].date.date == -1) {
						cout << "INVALID VALUE!!!";
					}
					else if (q[i].date.date > 0) {
						if (q[i].date.month > 10) {
							cout << q[i].date.date << "/" << q[i].date.month << "/" << q[i].date.year;
						}
						else cout << q[i].date.date << "/0" << q[i].date.month << "/" << q[i].date.year;
					}
				}
			}
			if (j == 3) {
				if (q[i].company != " ") cout << q[i].company;
			}
			if (j == 4) {
				if (q[i].mfg != " ") { 
					if (q[i].year == -1) {
						cout << "INVALID VALUE!!!";
					}
					else if (q[i].year > 0) cout << q[i].year; 
				}
			}
		}
	}
}

int check(string p) { // kiem tra xem chuoi co ky tu ngoai so ko
	for (int j = 0; j < p.length(); j++) {
		if (p[j] < 47 || p[j] > 57) {
			return 1;
		}
	}
	return 0;
}

int check_day(int date, int month, int year) {
	if (date < 0 || month > 12) {
		return 0;
	}
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 10 || month == 12) {
		if (date > 31) {
			return 0;
		}
	}
	if (month == 4 || month == 6 || month == 8 || month == 9 || month == 11) {
		if (date > 30) {
			return 0;
		}
	}
	if (month == 2) {
		if (((year % 4 == 0) && (year % 100 != 0)) ||
			(year % 400 == 0)) {
			if (date > 29) {
				return 0;
			}
		}
		else {
			if (date > 28) {
				return 0;
			}
		}
	}
	return 1;
}

void check_exp() {
	for (int i = 2; i < 50; i++) {
		if (q[i].exp.find('/', 0) < 0 || q[i].exp.find('/', 4) < 0 || q[i].exp.length() != 10) { // kiem tra xem han su dung co nhap dung cu phap ko
			q[i].date.date = -1;
			q[i].date.month = -1;
			q[i].date.month = -1;
		}
		else {
			if (check(q[i].exp) != 1) {
				string temp = q[i].exp.substr(0, 2);
				q[i].date.date = stoi(temp);
				temp = q[i].exp.substr(3, 2);
				q[i].date.month = stoi(temp);
				temp = q[i].exp.substr(6, 4);
				q[i].date.year = stoi(temp);
				if (check_day(q[i].date.date, q[i].date.month, q[i].date.year) == 0) {
					q[i].date.date = -1;
					q[i].date.month = -1;
					q[i].date.month = -1;
				}
			}
			else {
				q[i].date.date = -1;
				q[i].date.month = -1;
				q[i].date.month = -1;
			}
		}
		if (q[i].exp.length() == 0) {
			q[i].date.date = 0;
			q[i].date.month = 0;
			q[i].date.month = 0;
		}
	}
}

void check_mfg() {
	for (int i = 2; i < 50; i++) {
		if (q[i].mfg.length() != 4) {
			q[i].year = -1;
		}
		else {
			if (check(q[i].mfg) == 0) {
				q[i].year = stoi(q[i].mfg);
			}
			else q[i].year = -1;
		}
		if (q[i].mfg.length() == 0) q[i].year = 0;
	}
}

int exit(int x, int y) {
	if (x + 1 == p[0][4].x && y == p[0][4].y) {
		system("cls");
		drawBoard();
		move(4, 3);
		cout << "YES";
		move(4, 5);
		cout << "NO";
		X = 3, Y = 3;
		move(X, Y);
		while (1) {
			int COMMAND = toupper(_getch());
			if (COMMAND == 27) {
				system("cls");
				break;
			}
			if (COMMAND == 'W') {
				moveUp();
			}
			if (COMMAND == 'S') {
				moveDown();
			}
			if (COMMAND == 'A') {
				moveLeft();
			}
			if (COMMAND == 'D') {
				moveRight();
			}
			if (COMMAND == 13) {
				if (Y == 3) return 0;
				if (Y == 5) {
					drawBoard();
					tab();
					header();	
					print();
					X = 3, Y = 3;
					move(X, Y);
					return 1;
				}
			}
		}
	}
	return 1;
}

void load(int x, int y) {
	if (x + 1 == p[0][1].x && y == p[0][1].y) {
		system("cls");
		header();
		drawBoard();
		tab();
		ifstream file;
		move(4, 7);
		cout << "file1";
		move(4, 9);
		cout << "file2";
		move(4, 11);
		cout << "file3";
		move(4, 13);
		cout << "file4";
		move(4, 15);
		cout << "file5";
		X = 3, Y = 7;
		move(X, Y);
		while (1) {
			int COMMAND = toupper(_getch());
			if (COMMAND == 'W') {
				moveUp();
			}
			if (COMMAND == 'S') {
				moveDown();
			}
			if (COMMAND == 'A') {
				moveLeft();
			}
			if (COMMAND == 'D') {
				moveRight();
			}
			if (COMMAND == 13) {
				if (Y == 7) {
					file.open("data1.txt", ios::out);
					break;
				}
				if (Y == 9) {
					file.open("data2.txt", ios::out);
					break;
				}
				if (Y == 11) {
					file.open("data3.txt", ios::out);
					break;
				}
				if (Y == 13) {
					file.open("data4.txt", ios::out);
					break;
				}
				if (Y == 15) {
					file.open("data5.txt", ios::out);
					break;
				}
				if (exit(X, Y) == 0) {
					break;
				}
				else continue;
			}
		}
		for (int i = 2; i < 50; i++) {
			string product;
			getline(file, product);
			int first, last = 0, mark = 0;
			for (int j = 0; j < 5; j++) {
				mark += last - mark;
				first = product.find('(', mark);
				last = product.find(')', mark + 1);
				if (j == 0) {
					q[i].id = product.substr(first + 1, last - first - 1);
				}
				if (j == 1) {
					q[i].name = product.substr(first + 1, last - first - 1);
				}
				if (j == 2) {
					q[i].exp = product.substr(first + 1, last - first - 1);
					check_exp();
				}
				if (j == 3) {
					q[i].company = product.substr(first + 1, last - first - 1);
				}
				if (j == 4) {
					q[i].mfg = product.substr(first + 1, last - first - 1);
					check_mfg();
				}
			}
		}
		file.close();
		move(4, 7);
		cout << "     ";
		move(4, 9);
		cout << "     ";
		move(4, 11);
		cout << "     ";
		move(4, 13);
		cout << "     ";
		move(4, 15);
		cout << "     ";
		print();
		move(3, 3);
		X = 3, Y = 3;
	}
}

void validEnter(int x, int y) {
	for (int i = 2; i < 50; i++) {
		for (int j = 0; j < 5; j++) {
			if (p[i][j].x == x + 1 && p[i][j].y == y && p[i][j].m == 0) {
				textColor(8);
				move(p[i][j].x, p[i][j].y);
				if (j == 0) {
					if (q[i].id != " ") cout << q[i].id;
				}
				if (j == 1) {
					if (q[i].name != " ") cout << q[i].name;
				}
				if (j == 2) {
					if (q[i].exp != " ") {
						if (q[i].date.date == -1) {
							cout << "INVALID VALUE!!!";
						}
						else if (q[i].date.date > 0) {
							if (q[i].date.month > 10) {
								cout << q[i].date.date << "/" << q[i].date.month << "/" << q[i].date.year;
							}
							else cout << q[i].date.date << "/0" << q[i].date.month << "/" << q[i].date.year;
						}
					}
				}
				if (j == 3) {
					if (q[i].company != " ") cout << q[i].company;
				}
				if (j == 4) {
					if (q[i].mfg != " ") {
						if (q[i].year == -1) {
							cout << "INVALID VALUE!!!";
						}
						else if (q[i].year > 0) cout << q[i].year;
					}
				}
				p[i][j].m = 1;
				move(x, y);
				break;
			}
			if (p[i][j].x == x + 1 && p[i][j].y == y && p[i][j].m == 1) {
				textColor(15);
				move(p[i][j].x, p[i][j].y);
				if (j == 0) {
					if (q[i].id != " ") cout << q[i].id;
				}
				if (j == 1) {
					if (q[i].name != " ") cout << q[i].name;
				}
				if (j == 2) {
					if (q[i].exp != " ") {
						if (q[i].date.date == -1) {
							cout << "INVALID VALUE!!!";
						}
						else if (q[i].date.date > 0) {
							if (q[i].date.month > 10) {
								cout << q[i].date.date << "/" << q[i].date.month << "/" << q[i].date.year;
							}
							else cout << q[i].date.date << "/0" << q[i].date.month << "/" << q[i].date.year;
						}
					}
				}
				if (j == 3) {
					if (q[i].company != " ") cout << q[i].company;
				}
				if (j == 4) {
					if (q[i].mfg != " ") {
						if (q[i].year == -1) {
							cout << "INVALID VALUE!!!";
						}
						else if (q[i].year > 0) cout << q[i].year;
					}
				}
				p[i][j].m = 0;
				move(x, y);
				break;
			}
		}
	}
}

void edit(int x, int y) {
	for (int i = 2; i < 50; i++) {
		for (int j = 0; j < 5; j++) {
			if (p[i][j].x == x + 1 && p[i][j].y == y) {
				move(x + 1, y);
				cout << "                    ";
				move(x + 1, y);
				int count = 0;
				if (j == 0) {
					q[i].id = "";
				}
				if (j == 1) {
					q[i].name = "";
				}
				if (j == 2) {
					q[i].exp = "";
				}
				if (j == 3) {
					q[i].company = "";
				}
				if (j == 4) {
					q[i].mfg = "";
				}
				while (1) {
					char temp;
					temp = toupper(_getch());
					if (temp == 8) { // phim backspace
						if (count > 0) {
							printf_s("%c", temp);
							cout << " ";
							printf_s("%c", temp);
							count -= 1;
						}
					}
					else if (temp == 13) {
						move(x, y);
						break;
					}
					else if (count < 20) {
						printf_s("%c", temp);
						if (j == 0) {
							q[i].id += temp;
						}
						if (j == 1) {
							q[i].name += temp;
						}
						if (j == 2) {
							q[i].exp += temp;
						}
						if (j == 3) {
							q[i].company += temp;
						}
						if (j == 4) {
							q[i].mfg += temp;
						}
						count += 1;
					}
					else continue;
				}
			}
		}
		check_exp();
		check_mfg();
	}
}

void delete_product(int x, int y) {
	for (int i = 2; i < 50; i++) {
		for (int j = 0; j < 5; j++) {
			if (p[i][j].x == x + 1 && p[i][j].y == y) {
				move(x + 1, y);
				if (j == 0) {
					q[i].id = "";
					cout << "                         ";
				}
				if (j == 1) {
					q[i].name = "";
					cout << "                         ";
				}
				if (j == 2) {
					q[i].exp = "";
					cout << "                         ";
				}
				if (j == 3) {
					q[i].company = "";
					cout << "                         ";
				}
				if (j == 4) {
					q[i].mfg = "";
					cout << "                ";
				}
				move(x, y);
			}
		}
	}
}

void delete_entire_product(int x, int y) {
	for (int i = 2; i < 50; i++) {
		for (int j = 0; j < 5; j++) {
			if (p[i][j].x == x + 1 && p[i][j].y == y) {
				q[i].id = "";
				q[i].name = "";
				q[i].exp = "";
				q[i].company = "";
				q[i].mfg = "";
				move(p[i][0].x, p[i][0].y);
				cout << "                         ";
				move(p[i][1].x, p[i][1].y);
				cout << "                         ";
				move(p[i][2].x, p[i][2].y);
				cout << "                         ";
				move(p[i][3].x, p[i][3].y);
				cout << "                         ";
				move(p[i][4].x, p[i][4].y);
				cout << "                ";
				move(x, y);
			}
		}
	}
}

void save(int x, int y) {
	if (x + 1 == p[0][2].x && y == p[0][2].y) {
		system("cls");
		header();
		drawBoard();
		tab();
		ofstream file;
		move(4, 7);
		cout << "file1";
		move(4, 9);
		cout << "file2";
		move(4, 11);
		cout << "file3";
		move(4, 13);
		cout << "file4";
		move(4, 15);
		cout << "file5";
		X = 3, Y = 7;
		move(X, Y);
		while (1) {
			int COMMAND = toupper(_getch());
			if (COMMAND == 'W') {
				moveUp();
			}
			if (COMMAND == 'S') {
				moveDown();
			}
			if (COMMAND == 'A') {
				moveLeft();
			}
			if (COMMAND == 'D') {
				moveRight();
			}
			if (COMMAND == 13) {
				if (Y == 7) {
					file.open("data1.txt", ios::out);
					break;
				}
				if (Y == 9) {
					file.open("data2.txt", ios::out);
					break;
				}
				if (Y == 11) {
					file.open("data3.txt", ios::out);
					break;
				}
				if (Y == 13) {
					file.open("data4.txt", ios::out);
					break;
				}
				if (Y == 15) {
					file.open("data5.txt", ios::out);
					break;
				}
				if (exit(X, Y) == 0) {
					break;
				}
				else continue;
			}
		}
		for (int i = 2; i < 50; i++) {
			if (q[i].date.date > 0 && q[i].date.month > 0 && q[i].date.year > 0 && q[i].year > 0) {
				file << "(" << q[i].id << ")" << "(" << q[i].name << ")";
				if (q[i].date.month > 10) {
					file << "(" << q[i].date.date << "/" << q[i].date.month << "/" << q[i].date.year << ")";
				}
				else {
					file << "(" << q[i].date.date << "/" << "0" << q[i].date.month << "/" << q[i].date.year << ")";
				}
				file << "(" << q[i].company << ")" << "(" << q[i].year << ")" << endl;
			}
		}
		file.close();
		move(4, 7);
		cout << "     ";
		move(4, 9);
		cout << "     ";
		move(4, 11);
		cout << "     ";
		move(4, 13);
		cout << "     ";
		move(4, 15);
		cout << "     ";
		print();
		move(3, 3);
	}
}

void find(int x, int y) {
	if (x + 1 == p[0][3].x && y == p[0][3].y) {
		move(3, 1);
		int count = 0;
		string find;
		while (1) {
			char temp;
			temp = toupper(_getch());
			if (temp == 8) { // phim backspace
				if (count > 0) {
					printf_s("%c", temp);
					cout << " ";
					printf_s("%c", temp);
					count -= 1;
				}
			}
			else if (temp == 13) {
				move(x, y);
				break;
			}
			else if (count < 20) {
				printf_s("%c", temp);
				find += temp;
				count += 1;
			}
			else continue;
		}
		textColor(8);
		for (int i = 2; i < 50; i++) {
			if (find.compare(q[i].id) == 0) {
				move(p[i][0].x, p[i][0].y);			
				cout << q[i].id;
				p[i][0].m = 1;
			}
			if (find.compare(q[i].name) == 0) {
				move(p[i][1].x, p[i][1].y);
				cout << q[i].name;
				p[i][1].m = 1;
			}
			if (find.compare(q[i].exp) == 0) {
				move(p[i][2].x, p[i][2].y);
				cout << q[i].exp;
				p[i][2].m = 1;
			}
			if (find.compare(q[i].company) == 0) {
				move(p[i][3].x, p[i][3].y);
				cout << q[i].company;
				p[i][3].m = 1;
			}
			if (find.compare(q[i].mfg) == 0) {
				move(p[i][4].x, p[i][4].y);
				cout << q[i].mfg;
				p[i][4].m = 1;
			}
		}
		textColor(15);
		move(3, 1);
		cout << "                    ";
		move(x, y);
	}
}

int compare_day(int day1, int month1, int year1, int day2, int month2, int year2) { // so ngay 1 voi ngay 2, neu ngay 1 tre hon ngay 2 return 1, bang tra ve 0, som hon tra ve -1 
	if (year1 > year2) return 1;
	else if (year1 < year2) return -1;
	if (month1 > month2) return 1;
	else if (month1 < month2) return -1;
	if (day1 > day2) return 1;
	else if (day1 < day2) return -1;
	return 0;
}

void filter(int x, int y) {
	time_t now = time(0);
	tm newtime;
	localtime_s(&newtime, &now);
	if (x + 1 == p[1][2].x && y == p[1][2].y) {
		for (int i = 2; i < 50; i++) {
			int temp = compare_day(q[i].date.date, q[i].date.month, q[i].date.year, newtime.tm_mday, 1 + newtime.tm_mon, 1900 + newtime.tm_year);
			if (temp == -1 || temp == 0) {
				move(p[i][0].x, p[i][0].y);
				cout << "                         ";
				move(p[i][1].x, p[i][1].y);
				cout << "                         ";
				move(p[i][2].x, p[i][2].y);
				cout << "                         ";
				move(p[i][3].x, p[i][3].y);
				cout << "                         ";
				move(p[i][4].x, p[i][4].y);
				cout << "                ";
				move(x, y);
			}
		}
	}
}

void run() {
	while (1) {
		int COMMAND = toupper(_getch());
		if (COMMAND == 27) {
			if (exit(123, 3) == 0) {
				system("cls");
				break;
			}
			else continue;
		}
		if (COMMAND == 'W') {
			moveUp();
		}
		if (COMMAND == 'S') {
			moveDown();
		}
		if (COMMAND == 'A') {
			moveLeft();
		}
		if (COMMAND == 'D') {
			moveRight();
		}
		if (COMMAND == 'E') {
			validEnter(X, Y);
		}
		if (COMMAND == 'Q') {
			delete_product(X, Y);
		}
		if (COMMAND == 'Z') {
			delete_entire_product(X, Y);
		}
		if (COMMAND == 13) {
			edit(X, Y);
			load(X, Y);
			save(X, Y);
			find(X, Y);
			filter(X, Y);
			if (exit(X, Y) == 0) { 
				system("cls");
				break; 
			}
			else continue;
		}
	}
}
