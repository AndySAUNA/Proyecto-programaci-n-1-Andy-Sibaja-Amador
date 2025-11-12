#include "Game.h"

Game::Game(RenderWindow& window) {
	endgame = false;
	selrow = 8;
	selcolumn = 8;
	score = 0;
	moves = 20;
	this->window = &window;
	gboard = new Gameboard(window);
	gboard->randomizegameboard();
	firstselect = true;
	font.loadFromFile("resources/fonts/OpenSans-Regular.ttf");
	gameactive = false;
}

// draws score and moves ----------------------------------------------------------------------------------------------------------------------------
void Game::drawstats() {

	//prints score
	Text text1;
	text1.setFont(font);
	text1.setString("Score: " + to_string(score * 10));
	text1.setCharacterSize(24);
	text1.setFillColor(Color::White);
	text1.setPosition(40.f, 10.f);
	window->draw(text1);

	Text text2;
	text2.setFont(font);
	text2.setString("Moves: " + to_string(moves));
	text2.setCharacterSize(24);
	text2.setFillColor(Color::White);
	text2.setPosition(40.f, 40.f);
	window->draw(text2);
}

// game loop ----------------------------------------------------------------------------------------------------------------------------
void Game::drawgame() {
	drawstats();
	gboard->drawgameboard();
}

// select function does the selecction process and iniciates moves ----------------------------------------------------------------------------------------------------------------------------
void Game::select(int row, int column) {
	try {
		if ((row < 0 && column < 0) && (row > 8 && column > 8)) { throw 1; }

		gboard->conprintboard();
		if (row == selrow && column == selcolumn) {//if the same gem position is selected again, it deselects it
			cout << "deselected" << endl;
			selrow = 8;
			selcolumn = 8;
			firstselect = true;
			gboard->resetxy12();
		}
		else if (firstselect == true) {//first gem selection
			gboard->resetxy12();
			gboard->setxy1(row, column);
			selrow = row;
			selcolumn = column;
			firstselect = false;
			cout << "first select, selected: " << row << "," << column << endl;
		}
		else if (firstselect == false) {//second gem selection step
			cout << "second select, selected: " << row << "," << column << endl;
			cout << "first select was: " << selrow << "," << selcolumn << endl;
			if (gboard->checkvalidmove1(selrow, selcolumn, row, column) == true) {
				cout << "valid move" << endl;
				gboard->setxy12(selrow, selcolumn, row, column);
				selrow = 8;
				selcolumn = 8;
				firstselect = true;
				if (gboard->checkvalidmove2() == true) { // this bit checks if the move creates a match and processes the move if it does
					cout << "gboard->checkvalidmove2() check passed";
					window->clear();
					drawgame();
					window->display();
					this_thread::sleep_for(chrono::milliseconds(500));
					score += gemdestroyer();
					moves--;
					selrow = 8;
					selcolumn = 8;
					firstselect = true;
					gboard->resetxy12();
					if (moves <= 0) { endgame = true; gameactive = false; }
				}
				else { // this bit resets the selection if the move is invalid
					cout << "gboard->checkvalidmove2() check failed" << endl;
					cout << "deselected" << endl;
					selrow = 8;
					selcolumn = 8;
					firstselect = true;
					gboard->resetxy12();
				}
			}
			else if (gboard->checkadyasent(selrow, selcolumn, row, column) == false) {//if the second selection is not adyasent to the first, it becomes the new first selection
				gboard->resetxy12();
				gboard->setxy1(row, column);
				selrow = row;
				selcolumn = column;
				firstselect = false;
				cout << "first select, selected: " << row << "," << column << endl;
			}
			else {//if the move is invalid, it resets the selection to first select
				gboard->resetxy12();
				gboard->setxy1(row, column);
				selrow = row;
				selcolumn = column;
				firstselect = false;
				cout << "first select, selected: " << row << "," << column << endl;
			}
		}
	}
	catch (int error) {
		if (error == 1){ cout << "error: selection with wrong parameters" << endl; }
		
	}
}

void Game::icegame()
{
	srand((unsigned)time(0));
	int aux1, aux2;
	for (int i = 0; i < 5; i++) {
		aux1 = rand() % 8;
		aux2 = rand() % 8;
		gboard->addice(aux1,aux2);
	}
}

// this function orders the destrcution of gems ----------------------------------------------------------------------------------------------------------------------------
int Game::gemdestroyer() {
	int aux;
	int destroyedgems = 0, mincounter = 0;
	destroyedgems += gboard->countmatches(gboard->detectmatches(gboard->getboard()));
	gboard->addpowergems(destroyedgems/4);
	while (gboard->deletematches() == true) {
		gboard->gravity();
		aux= gboard->countmatches(gboard->detectmatcheswithbombs(gboard->getboard()));
		destroyedgems += aux;
		if (aux >= 4){ gboard->addpowergems(aux/4); }
		window->clear();
		drawgame();
		window->display();
		cout << "matches counted: " << destroyedgems;
		this_thread::sleep_for(chrono::milliseconds(100));
	}
	return destroyedgems;
}

void Game::setgameactive(bool b)
{
	gameactive = b;
}

bool Game::getgameactive()
{
	return gameactive;
}

void Game::clean_game()
{
}

void Game::gameend()
{
	endgame = false;
}

bool Game::endgamer()
{
	return endgame;
}

int Game::getscore()
{
	return score;
}

string Game::getstat()
{
	return to_string(getscore()*10);
}

void Game::fast_game()
{
	moves = 5;
}

void Game::reset_game()
{
	gboard->randomizegameboard();
	score = 0;
	moves = 20;
}

void Game::setendgame()
{
	endgame = false;
}

//destructor ----------------------------------------------------------------------------------------------------------------------------
Game::~Game() {
	delete gboard;
}
