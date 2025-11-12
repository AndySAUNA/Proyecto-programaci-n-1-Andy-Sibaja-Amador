#include "Gameboard.h"
using namespace std;

//constructor, creates the dynamic matrix and randomizes it's content with NormalGems ----------------------------------------------------------------------------------------------------------------------------
Gameboard::Gameboard(RenderWindow& window) {
	srand((unsigned)time(0));
	t = 0;
	row1 = 8;
	column1 = 8;
	row2 = 8;
	column2 = 8;
	powergemcounter = 0;
	this->window = &window;
	//makes a pointer array of Gem type;
	board = new Gem * *[8];
	for (int i = 0; i < 8; i++) {
		board[i] = new Gem * [8];
		for (int j = 0; j < 8; j++) {
			board[i][j] = new NormalGem(i, j, &window);
		}
	}
	randomizegameboard();
	cout << "randomized gameboard:" << endl;
	for (int i = 0; i < 8; i++) {
		cout << "row " << i;
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == nullptr) { cout << "\tNull"; }
			if (board[i][j] != nullptr) {
				cout << "\t" << board[i][j]->getgemtype();
				if (board[i][j]->getselect() == true) { cout << "'S'"; }
			}
		}
		cout << endl;
	}
}

//this function draws the gameboard on the window ----------------------------------------------------------------------------------------------------------------------------
void Gameboard::drawgameboard() {
	RectangleShape rect(Vector2f(70.f, 70.f));
	rect.setOutlineColor(Color::Black);
	rect.setOutlineThickness(5.f);
	Color test(211, 211, 211);
	rect.setFillColor(test);
	float dcolumn;
	float drow;

	try {
		Texture backgroundTexture;
		if (!backgroundTexture.loadFromFile("resources\\box grid 600.png")) { throw 2; }
		Sprite backgroundSprite;
		backgroundSprite.setTexture(backgroundTexture);
		backgroundSprite.setPosition(195, 0);
		window->draw(backgroundSprite);

		if (row1 < 0 && column1 < 0 && row1 > 8 && column1 > 8 && row2 < 0 && column2 < 0 && row2 > 8 && column2 > 8) { throw 1; }
		if (row1 >= 0 && column1 >= 0 && row1 < 8 && column1 < 8 && row2 >= 0 && column2 >= 0 && row2 < 8 && column2 < 8) { if (board[row1][column1] == nullptr) { throw 2; } }
		if (row1 >= 0 && column1 >= 0 && row1 < 8 && column1 < 8 && row2 >= 0 && column2 >= 0 && row2 < 8 && column2 < 8) { if (board[row1][column1] == nullptr || board[row2][column2] == nullptr) { throw 3; } }
		if ((row1 != 8 && column1 != 8) && (row2 != 8 && column2 != 8)) {
			if (board[row1][column1] != nullptr || board[row2][column2] != nullptr) {
				board[row1][column1]->select();
				board[row2][column2]->select();
			}
		}
		else if (row1 != 8 && column1 != 8) {
			if (board[row1][column1] != nullptr) {
				board[row1][column1]->select();
			}
		}
		//draws the gems on the board
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board[i][j] != nullptr) {
					board[i][j]->draw_on_grid();
				}
				else {
					dcolumn = j * 75.f + 200.f;
					drow = i * 75.f;
					rect.setPosition(dcolumn, drow);
				}
			}
		}

		if ((row1 != 8 && column1 != 8) && (row2 != 8 && column2 != 8)) {
			board[row1][column1]->deselect();
			board[row2][column2]->deselect();
		}
		else if (row1 != 8 && column1 != 8) {
			board[row1][column1]->deselect();
		}
	}
	catch (int error) {
		if (error == 1) { cout << "error drawing board: invalid selection coordinates " << endl; }
		if (error == 2) { cout << "error drawing board: attempted to select a null pointer" << endl; }
		if (error == 2) { cout << "error drawing board: attempted to select a null pointer" << endl; }
	}
}

//this function sets the coordinates of the first and second selection ----------------------------------------------------------------------------------------------------------------------------
void Gameboard::setxy12(int row1, int column1, int row2, int column2) {
	this->row1 = row1;
	this->column1 = column1;
	this->row2 = row2;
	this->column2 = column2;
}

// sets the x and y coordinates for selection  ----------------------------------------------------------------------------------------------------------------------------
void Gameboard::setxy1(int row, int column) {
	row1 = row;
	column1 = column;
}

//resets the x an y coordinates for selecction ----------------------------------------------------------------------------------------------------------------------------
void Gameboard::resetxy12() {
	row1 = 8;
	column1 = 8;
	row2 = 8;
	column2 = 8;
}

// this function randomizes the gems on the board  only to NormalGem, if there is another child class of Gem, it will be deleted and replaced----------------------------------------------------------------------------------------------------------------------------
void Gameboard::randomizegameboard() {
	int i, j;
	
	srand((unsigned)time(0));
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (board[i][j]->getgemtype() == 6 || board[i][j]->getgemtype() == 7) { 
				delete board[i][j]; 
				board[i][j] = new NormalGem; 
			}
			else {
				board[i][j]->setgemtype(rand() % 5 + 1);
			}
		}
	}
	try {
		if (board == nullptr) { throw 1; }
		for (int i = 0; i < 8; i++) {
			if (board[i] == nullptr) { throw 2; }
		}
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if (board[i][j] == nullptr) {
					board[i][j] = new NormalGem;
				}
				else if (board[i][j]->getgemtype() == 6 || board[i][j]->getgemtype() == 7) {
					delete board[i][j];
					board[i][j] = new NormalGem;
				}
			}
		}
		bool** fakeboard = detectmatches(board);
		while (countmatches(fakeboard) != 0) {
			for (i = 0; i < 8; i++) {
				for (j = 0; j < 8; j++) {
					if (fakeboard[i][j] == true) {
						board[i][j]->setgemtype((rand() % 5) + 1);
					}
				}
			}
			for (i = 0; i < 8; i++) {
				delete[] fakeboard[i];
			}
			delete[] fakeboard;
			fakeboard = detectmatches(board);
		}
	}
	catch (int error) {
		if (error == 1) { cout << "error while randomizing game board, Board not initialized" << endl; }
		if (error == 2) { cout << "error while randomizing game board, Board not properly initialized, series of pointer arrays missing" << endl; }
	}
}

//this function detects mathces on the board ----------------------------------------------------------------------------------------------------------------------------
bool** Gameboard::detectmatches(Gem*** board) {
	bool** fakeboard;
	int i, j;
	fakeboard = new bool* [8];
	for (i = 0; i < 8; i++) {
		fakeboard[i] = new bool[8];
		for (j = 0; j < 8; j++) {
			fakeboard[i][j] = false;
		}
	}
	for (i = 0; i < 8; i++) {
		for (j = 1; j < 7; j++) {
			//testing for row matches
			if(board[i][j]!= nullptr && board[i][j-1] != nullptr && board[i][j+1] != nullptr && board[j][i]!= nullptr && board[j-1][i] != nullptr && board[j+1][i] != nullptr){
				if ((board[i][j]->getgemtype() == board[i][j - 1]->getgemtype()) && (board[i][j]->getgemtype() == board[i][j + 1]->getgemtype()) && (board[i][j]->getgemtype() != 0)) {
					fakeboard[i][j] = true;
					fakeboard[i][j + 1] = true;
					fakeboard[i][j - 1] = true;
				}
				//testing for column matches
				if ((board[j][i]->getgemtype() == board[j - 1][i]->getgemtype()) && (board[j][i]->getgemtype() == board[j + 1][i]->getgemtype()) && (board[i][j]->getgemtype() != 0)) {
					fakeboard[j][i] = true;
					fakeboard[j - 1][i] = true;
					fakeboard[j + 1][i] = true;
				}
			}
		}
	}
	return fakeboard;
}

bool** Gameboard::detectmatcheswithbombs(Gem*** board)
{
	bool** fakeboard;
	fakeboard = detectmatches(board);
	bomber(fakeboard);
	return fakeboard;
}

// this function deletes matches on the board and returns true if matches were found ----------------------------------------------------------------------------------------------------------------------------
bool Gameboard::deletematches() {
	bool** fakeboard = detectmatches(board);
	int i, j;
	resetxy12();
	
	bool matchesfound = false;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (fakeboard[i][j] == true) {
				board[i][j]->select();
			}
		}
	}

	window->clear();
	drawgameboard();
	window->display();
	this_thread::sleep_for(chrono::milliseconds(100));

	bomber(fakeboard);

	window->clear();
	drawgameboard();
	window->display();
	this_thread::sleep_for(chrono::milliseconds(500));

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (fakeboard[i][j] == true) {
				delete board[i][j];
				board[i][j] = nullptr;
				matchesfound = true;
			}
		}
	}
	window->clear();
	drawgameboard();
	window->display();
	this_thread::sleep_for(chrono::milliseconds(100));
	// this bit is in case gems are deleted at the top, so new ones are generated
	generatetop();
	return matchesfound;
}
//function finds bombs and checks adyecent coordinates for detected matches in a given fakeboard, then calls the Kaboom! operation
int Gameboard::bomber(bool** fakeboard)
{
	try {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board[i][j] == nullptr) { throw 1; }// no null pointers should be on the board when this operation executes 
				if (board[i][j]->getgemtype() == 6) {// next bit sets restrictions when checking the boarders of the board
					bool tt = true,ml = true, mr = true,bb = true,find = false;
					if (i == 0) {tt = false;}
					if (i == 7) {bb = false;}
					if (j == 0) {ml = false;}
					if (j == 7) {mr = false;}
					if (tt == true) { if (fakeboard[i - 1][j] == true) { find = true; } }
					if (ml == true) { if (fakeboard[i][j - 1] == true) { find = true; } }
					if (mr == true) { if (fakeboard[i][j + 1] == true) { find = true; } }
					if (bb == true) { if (fakeboard[i + 1][j] == true) { find = true; } }
					if (find == true) { kaboom(i, j, fakeboard); }
				}

			}
		}
	}
	catch (int error) {
		if (error == 1) { cout << "error in bomber function: null pointer found" << endl; }
	}
	return 0;
}
// this bit detects if a bomb is supposed to explode, destroys the gems and returns the amount;
int Gameboard::kaboom(int row, int column, bool** fakeboard)
{
	int destroyedgems = 0;
	bool tl = true, tt = true, tr = true, ml = true, mr = true, bl = true, bb = true, br = true;
	if (row == 0) { tl = false; tt = false; tr = false; }
	if (row == 7) { bl = false; bb = false; br = false; }
	if (column == 0) { tl = false; ml = false; bl = false; }
	if (column == 7) { tr = false; mr = false; br = false; }
	destroyedgems++; fakeboard[row][column] = true;
	board[row][column]->select();
	if (tl == true) { destroyedgems++; fakeboard[row - 1][column - 1] = true; board[row - 1][column - 1]->select(); }
	if (tt == true) { destroyedgems++; fakeboard[row - 1][column] = true; board[row - 1][column]->select();}
	if (tr == true) { destroyedgems++; fakeboard[row - 1][column + 1] = true; board[row - 1][column + 1]->select();}
	if (ml == true) { destroyedgems++; fakeboard[row][column - 1] = true; board[row][column - 1]->select();}
	if (mr == true) { destroyedgems++; fakeboard[row][column + 1] = true; board[row][column + 1]->select();}
	if (bl == true) { destroyedgems++; fakeboard[row + 1][column - 1] = true; board[row + 1][column - 1]->select();}
	if (bb == true) { destroyedgems++; fakeboard[row + 1][column] = true; board[row + 1][column]->select();}
	if (br == true) { destroyedgems++; fakeboard[row + 1][column + 1] = true; board[row + 1][column + 1]->select();}
	return destroyedgems;
}

//this function takes a fakeboard and counts the amount of matches in it and returns the number ----------------------------------------------------------------------------------------------------------------------------
int Gameboard::countmatches(bool** fakeboard) {
	int i, j;
	int matchesfound = 0;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (fakeboard[i][j] == true) {
				matchesfound++;
			}
		}
	}
	return matchesfound;
}

// gives you the Gem class board matrix ----------------------------------------------------------------------------------------------------------------------------
Gem*** Gameboard::getboard() {
	return board;
}

//this function does the gravity effect ----------------------------------------------------------------------------------------------------------------------------
void Gameboard::lightup(int row, int column) {
	RectangleShape shape(Vector2f(70.f, 70.f));
	shape.setFillColor(Color::Red);
	shape.setOutlineColor(Color::Black);
	shape.setOutlineThickness(5.f);
	shape.setPosition(Vector2f((column * 75.f + 200.f), (row * 75.f)));
	window->draw(shape);
}

// this function produces the gravity effect by cycling a operation that pulls gems down
void Gameboard::gravity() {
	srand((unsigned)time(0));
	bool clean;
	for (int i = 0; i < 8; i++) {//runs the gravity operation 8 times to make sure all gems have fallen to the bottom
		clean = gravitystep();// this pulls everything down once
		if (clean == true) { i = 8; }// if a pass shows that there wasn't a single coodrinate with a 0, then it is clean and the operation can stop
	}
}

// this function pulls everything down once, retruns true if it doesn't find anything to pull ----------------------------------------------------------------------------------------------------------------------------
bool Gameboard::gravitystep() {
	bool clean = true;
	for (int i = 7; i > 0; i--) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == nullptr) {
				if (board[i - 1][j] != nullptr) {
					if (board[i - 1][j]->getgemtype() != 7) {
						board[i][j] = board[i - 1][j];
						board[i - 1][j] = nullptr;
						if (board[i][j] != nullptr) {
							board[i][j]->setrow(i);
							board[i][j]->setcolumn(j);
						}
						clean = false;
						generatetop();
						window->clear();
						drawgameboard();
						window->display();
						this_thread::sleep_for(chrono::milliseconds(100));
					}
				}
			}
		}
	}
	return clean;
}

// this function generates the missing gems int he top part in a randomized manner ----------------------------------------------------------------------------------------------------------------------------
void Gameboard::generatetop() {
	srand((unsigned)time(0));
	int r;
	// this bitgenerates the gems in the top part
	for (int i = 0; i < 8; i++) {
		if (board[0][i] == nullptr) {
			r = (rand() % 8) + 1;
			if (powergemcounter > 0 && r == 8) {
				board[0][i] = new BombGem(0, i, window);
				powergemcounter--;
				
			}
			else{
				board[0][i] = new NormalGem(0, i, window);
				while (t == board[0][i]->getgemtype()) {
					board[0][i]->setgemtype(rand() % 5 + 1);
				}
				t=board[0][i]->getgemtype();
			}
			window->clear();
			drawgameboard();
			window->display();
			this_thread::sleep_for(chrono::milliseconds(100));
			
		}
	}
}

//unrefranced, must consider deleting ----------------------------------------------------------------------------------------------------------------------------
bool Gameboard::gravitybrake() {
	bool clean;
	for (int i = 0; i < 8; i++) {//for every column of the first row of the matrix
		clean = true;//on the start of a new run on the matrix it is assumed clean until proven otherwise
		if (board[0][i]->getgemtype() == 0) {//if entry is equal to 0 and isn't the top row, return false
			clean = false;
		}
	}
	return clean;//will give true if top row is full, false if not
}

//checks if 2 sets of coordinates are adyacent to each other and returns a boolean ----------------------------------------------------------------------------------------------------------------------------
bool Gameboard::checkadyasent(int x1, int y1, int x2, int y2) {
	if ((x1 == x2 + 1 || x1 == x2 - 1) && (y1 == y2) || ((y1 == y2 + 1 || y1 == y2 - 1) && (x1 == x2))) {
		return true;
	}
	else { return false; }
}

//this function checks valid move and returns true or false ----------------------------------------------------------------------------------------------------------------------------
bool Gameboard::checkvalidmove1(int x1, int y1, int x2, int y2) {

	cout << "valid move test 0" << endl;
	if (x1 >= 0 && x1 <= 7 && y1 >= 0 && y1 <= 7 && x2 >= 0 && x2 <= 7 && y2 >= 0 && y2 <= 7) {
		cout << "valid move test 1" << endl;
		if ((x1 == x2 + 1 || x1 == x2 - 1) && (y1 == y2) || ((y1 == y2 + 1 || y1 == y2 - 1) && (x1 == x2))) {
			cout << "valid move test 2" << endl;
			cout << "x1,y1: " << x1 << "," << y1 << " x2,y2: " << x2 << "," << y2 << endl;
			cout << "gem 1 is: " << board[x1][y1]->getgemtype() << "gem 2 is: " << board[x2][y2]->getgemtype() << endl;
			if (board[x1][y1]->getgemtype() != board[x2][y2]->getgemtype()) {
				cout << "valid move test 3" << endl;
				cout << "valid move" << endl;
				return true;
			}
			else { return false; }
		}
		else { return false; }
	}
	else { return false; }
}

//tests the swap for combinations and returns true if any are found ----------------------------------------------------------------------------------------------------------------------------
bool Gameboard::checkvalidmove2() {
	//  makes a temporary copy board of the original for testing
	try {
		Gem*** temp = new Gem **[8];
		for (int i = 0; i < 8; i++) {
			temp[i] = new Gem * [8];
			for (int j = 0; j < 8; j++) {
				if (board[i][j] != nullptr) {
					if (board[i][j]->getgemtype() < 0 && board[i][j]->getgemtype() > 7) { throw 1; }
					if (board[i][j]->getgemtype() == 7) {
						temp[i][j] = new IceGem;
						temp[i][j]->setrow(i);
						temp[i][j]->setcolumn(j);
					}
					else if (board[i][j]->getgemtype() == 6) {
						temp[i][j] = new BombGem;
						temp[i][j]->setrow(i);
						temp[i][j]->setcolumn(j);
					}
					else if (board[i][j]->getgemtype() >= 0 && board[i][j]->getgemtype() <= 5 ) {
						temp[i][j] = new NormalGem;
						temp[i][j]->setrow(i);
						temp[i][j]->setcolumn(j);
						temp[i][j]->setgemtype(board[i][j]->getgemtype());
					}
				}
				else { temp[i][j] = nullptr;}
			}
		}
		cout << "printing temp board" << endl;
		for (int i = 0; i < 8; i++) {
			cout << "Row " << i << ": \t";
			for (int j = 0; j < 8; j++) {
				if (temp[i][j] == nullptr) {
				cout << "null" << "\t";
				}
				else {
					cout << temp[i][j]->getgemtype() << "\t";
				}
			}
			cout << std::endl;
		}
		//this part swaps the gems in the temporary board
		Gem* t1 = temp[row1][column1];
		Gem* t2 = temp[row2][column2];
		temp[row1][column1] = t2;
		temp[row2][column2] = t1;
		cout << "printing temp board after move" << endl;
		for (int i = 0; i < 8; i++) {
			cout << "Row " << i << ": \t";
			for (int j = 0; j < 8; j++) {
				std::cout << temp[i][j]->getgemtype() << "\t";
			}
			std::cout << std::endl;
		}
		//this part checks if the swap creates a match
		bool** fakeboard = detectmatches(temp);
		cout << "sx1,sy1 and sx2,sy2 are: " << row1 << "," << column1 << " and " << row2 << "," << column2 << endl;
		// this part prints the fakeboard
		cout << "fakeboard is: " << endl;
		for (int i = 0; i < 8; i++) {
			cout << "Row " << i << ": \t";
			for (int j = 0; j < 8; j++) {
				cout << fakeboard[i][j] << "\t";
			}
			cout << endl;
		}
		if (countmatches(fakeboard) > 0) {
			//if a match is found, swap the real board and delete the temp and fakeboard and return true
			cout << "matches found" << endl;
			Gem* aux1 = board[row1][column1];
			Gem* aux2 = board[row2][column2];
			board[row1][column1] = aux2;
			board[row2][column2] = aux1;
			//setting new pos 1 gem with pos 1 coordiniates
			aux1->setrow(row2);
			aux1->setcolumn(column2);
			//setting new pos 2 gem with pos 2 coordinates
			aux2->setrow(row1);
			aux2->setcolumn(column1);
			
			conprintboard();
			cout << "positions swapped" << endl;

			return true;
		}
			for (int i = 0; i < 8; i++) {
				delete[] fakeboard[i];
				for (int j = 0; j < 8; j++) {
					delete temp[i][j];
				}
				delete[] temp[i];
			}
			delete[] fakeboard;
			delete[] temp;
			return false;
	}
	catch (int error) {
		if (error == 1) { cout << "error in validmove2: a gem is using a non existant gem number."; }
		if (error == 2) { cout << "error generating temporary board, invalid Gem found."; }
	}

}

//this function deletes a gem of set coordinates  ----------------------------------------------------------------------------------------------------------------------------
void Gameboard::deletegem(int x, int y) {
	delete board[x][y];
}

//consol prints the board as a matrix of numbers corresponding to the gem type of each entry ----------------------------------------------------------------------------------------------------------------------------
void Gameboard::conprintboard() {
	int i, j;
	for (i = 0; i < 8; i++) {
		cout << "Row " << i << ": \t";
		for (j = 0; j < 8; j++) {
			if (board[i][j] != nullptr) {
				cout << board[i][j]->getgemtype() << "\t";
			}
		}
		cout << std::endl;
	}
}
void Gameboard::addice(int x, int y)
{
	delete board[x][y];
	board[x][y] = new IceGem(x,y,window);
	
}
//destyer
Gameboard::~Gameboard() {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (board[i][j] != nullptr) {
				delete board[i][j];
				board[i][j] = nullptr;
			}
		}
		delete[] board[i];
		board[i] = nullptr;
	}
	delete[] board;
	board = nullptr;
}
