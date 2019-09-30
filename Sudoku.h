#include <fstream>
#include <iostream>
#include <istream>
#include <deque>
#include <stdlib.h>
#include <string>
#include <tuple>
#include <time.h>
#include <vector>
using namespace std;

class Sudoku
{
	int board[9][9];
	bool hints[9][9];
	int backtracks, comparisons, placementFailures;
public:
	Sudoku();
	void printBoard(ofstream&);
	void addNumber(int, int, int, ofstream&, bool);
	void addHint(int, int, int, ofstream&);
	bool inputGood(int, int, int, ofstream&);
	bool openingInRow(int, int);
	bool openingInColumn(int, int);
	bool openingInGroup(int, int, int);
	bool canPlaceValue(int, int, int, ofstream&);
	bool boardFull();
	void rowGroupComplete(int, ofstream&);
	bool getEmptyLocation(int&, int&);
	bool solve(ofstream&);
	bool isUnique();
	bool solve2(ofstream&);
	int getBacktracks() { return backtracks; }
	int getComparisons() { return comparisons; }
	int getPlacementFailures() { return placementFailures; }
};