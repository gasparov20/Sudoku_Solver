#include "Sudoku.h"

// Default constructor
Sudoku::Sudoku()
{
	backtracks = 0;
	comparisons = 0;
	placementFailures = 0;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			hints[i][j] = false;
			board[i][j] = 0;
		}
	}
}

// Prints the board in 9 x 9 grid format.
// Free spaces are marked by the '-' character.
// Pre-condition: Input is a 9 x 9 Sudoku board
// object containing a 9 x 9 array of ints.
// Post-condition: Prints the grid
void Sudoku::printBoard(ofstream &fout)
{
	for (int j = 0; j < 9; j++) {
		for (int i = 0; i < 9; i++) {

			if (board[j][i] == 0) {
				cout << "-" << " ";
				fout << "#" << " ";
			}
			else {
				cout << board[j][i] << " ";
				fout << board[j][i] << " ";
			}
		}
		cout << endl;
		fout << endl;
	}
	cout << endl;
	fout << endl;
}

// Adds a number to the grid. Won't add the number if there's
// already a hint there. Prints row groups when they're
// completed if this function is used to solve initial grid.
// Pre-condition: Valid row and column indices, valid value.
// It is assumed that these values are valid since they don't
// come from the user.
// Post-condition: Adds the value to the specified coordinates.
void Sudoku::addNumber(int row, int col, int value, ofstream &fout, bool printIterations)
{
	// Double check to make sure a hint isn't already there.
	if (hints[row][col]) {
		cout << "Cannot change hint at position("
			<< row + 1 << ", " << col + 1 << ")\n";
		fout << "Cannot change hint at position ("
			<< row + 1 << ", " << col + 1 << ")\n";
		throw("Cannot change hints");
	}

	// Numbers added by the program can be replaced.
	board[row][col] = value;

	// Check if the row group is complete that the newly-added value
	// is part of. Print the row group if it is complete. Some grids
	// will involve many backtracks which will result in the same row
	// group being printed as many times as a value is changed once it
	// is initially complete. Doesn't print when this function is used
	// to check for unique solutions.
	if (printIterations)
		rowGroupComplete(row, fout);
	else
		return;
}

// Add hint to board
// Pre-condition: Integer inputs.
// Post-condition: If the inputs are determined to be
// valid, they are added to the grid as hints.
void Sudoku::addHint(int row, int col, int value, ofstream& fout)
{
	// If the input is valid, add the value to the board as a hint.
	if (inputGood(row, col, value, fout)) {
		board[row][col] = value;
		hints[row][col] = true;
	}
}

// Returns true if the coordinates and value are valid.
// Coordinates must be between 0 and 8, and values must be
// between 1 and 9.
// Pre-condition: Integer inputs.
// Post-condition: Returns true if the inputs are valid.
bool Sudoku::inputGood(int row, int col, int value, ofstream &fout)
{
	bool good = true;

	if (row < 0 || row > 8) {
		cout << "Error - Invalid coordinate\n";
		fout << "Error - Invalid coordinate\n";
		throw("invalid coordinate");
		good = false;
	}

	if (col < 0 || col > 8) {
		cout << "Error - Invalid coordinate\n";
		fout << "Error - Invalid coordinate\n";
		throw("invalid coordinate");
		good = false;
	}

	if (value < 1 || value > 9) {
		cout << "Error - Invalid value\n";
		fout << "Error - Invalid value\n";
		throw("invalid value");
		good = false;
	}
	return good;
}

// Returns true if "value" is not already in the specified row.
// Pre-condition: Integer inputs.
// Post-condition: Returns true if the value doesn't already
// exist in the specified row.
bool Sudoku::openingInRow(int row, int value)
{
	for (int i = 0; i < 9; i++) {
		comparisons++;
		if (board[row][i] == value)
			return false;
	}
	return true;
}

// Returns true if "value" is not already in the specified column.
// Pre-condition: Integer inputs.
// Post-condition: Returns true if the value doesn't already
// exist in the specified column.
bool Sudoku::openingInColumn(int col, int value)
{
	for (int i = 0; i < 9; i++) {
		comparisons++;
		if (board[i][col] == value)
			return false;
	}
	return true;
}

// Returns true if "value" is not already in the specified group.
// Pre-condition: Integer inputs.
// Post-condition: Returns true if the value doesn't already
// exist in the specified group.
bool Sudoku::openingInGroup(int row, int col, int value)
{
	int y, x;

	// These statements set y and x to the upperleft-most index
	// of the group that "value" belongs to.

	if (row >= 0 && row < 3)
		y = 0;
	else if (row >= 3 && row < 6)
		y = 3;
	else if (row >= 6 && row < 9)
		y = 6;

	if (col >= 0 && col < 3)
		x = 0;
	else if (col >= 3 && col < 6)
		x = 3;
	else if (col >= 6 && col < 9)
		x = 6;

	for (int j = y; j < y + 3; j++) {
		for (int i = x; i < x + 3; i++) {
			comparisons++;
			if (board[j][i] == value) {
				return false;
			}
		}
	}

	return true;
}

// Checks if a row group (groups are rows 1-3, rows 4-6, and rows 7-9)
// is complete; if so, the group is printed.
// Pre-condition: Row index.
// Post-condition: Prints the row group if the row group is complete.
void Sudoku::rowGroupComplete(int row, ofstream &fout)
{
	int y, j, i;

	if (row >= 0 && row < 3)
		y = 0;
	else if (row >= 3 && row < 6)
		y = 3;
	else if (row >= 6 && row < 9)
		y = 6;
	else y = 0;

	for (j = y; j < y + 3; j++) {
		for (i = 0; i < 9; i++) {
			if (board[j][i] == 0)
				return;
		}
	}

	cout << "Printing rows " << y + 1 << " to "
		<< y + 3 << endl;
	
	fout << "Printing rows " << y + 1 << " to "
		<< y + 3 << endl;

	for (j = y; j < y + 3; j++) {
		for (i = 0; i < 9; i++) {
			cout << board[j][i] << " ";
			fout << board[j][i] << " ";
		}
		cout << endl;
		fout << endl;
	}
	cout << endl;
	fout << endl;
}

// Returns true if the value in question does not already appear in the specified
// coordinate's row, column, or group.
// Pre-condition: Integer inputs.
// Post-condition: Returns true if the value abides by Sudoku rules in the
// specified coordinate.
bool Sudoku::canPlaceValue(int row, int col, int value, ofstream &fout)
{
	if (!inputGood(row, col, value, fout))
		return false;

	if (hints[row][col])
		return false;
	else if (openingInRow(row, value)
		&& openingInColumn(col, value)
		&& openingInGroup(row, col, value))
		return true;
	else
		return false;
}

// Returns true if the board is full
// Pre-condition: Valid Sudoku board object.
// Post-condition: Returns true if the board is full.
bool Sudoku::boardFull()
{
	for (int j = 0; j < 9; j++) {
		for (int i = 0; i < 9; i++) {
			if (board[j][i] == 0)
				return false;
		}
	}
	return true;
}

// Returns true if there is an empty location on the board.
// If true, row and col of the calling function will contain
// the coordinates of an empty location on the board.
// Finds a new list of empty locations each call.
// Pre-condition: Sudoku object with empty locations in the grid.
// Post-condition: Returns false if the board is full. Returns true
// if an empty location is available. Sets the values held at the
// row and column addresses to coordinates of an empty location.
bool Sudoku::getEmptyLocation(int &row, int &col)
{
	// If the board is full, return false. This will tell the solver
	// function that it is done.
	if (boardFull())
		return false;

	// Stores the empty location coordinates in the form of an int tuple
	deque<tuple<int, int>> emptyLocations;
	int y, x, max;

	// Find all empty locations and push them to the deque
	if (emptyLocations.empty()) {
		for (int j = 0; j < 9; j++) {
			for (int i = 0; i < 9; i++) {
				if (board[j][i] == 0)
					emptyLocations.push_back(make_tuple(j, i));
			}
		}
	}

	// Get next empty location
	tie(row, col) = emptyLocations.front();
	emptyLocations.pop_front();

	return true;
}

// Recursive function to solve the Sudoku board.
// Pre-condition: Sudoku object with a partial grid.
// Post-condition: If the Sudoku grid is solvable,
// the object will contain a solved Sudoku grid
// after this function concludes.
bool Sudoku::solve(ofstream &fout)
{
	int row, col;
	
	// Base case. When the board is full, the recursion ends.  
	if (!getEmptyLocation(row, col))
		return true;  

	// Try numbers 1 through 9
	for (int num = 1; num <= 9; num++)
	{ 
		if (canPlaceValue(row, col, num, fout))
		{
			// If the number is a valid placement, do it
			addNumber(row, col, num, fout, true);

			// Go to the next location
			if (solve(fout)) 
				return true;

			// The previous choice didn't work, so reset the cell
			board[row][col] = 0;
		}
		else placementFailures++;
	}
	// If no numbers worked for the last empty location,
	// go back to the empty location before that and try
	// again. Backtracks are counted.
	backtracks++;
	return false;
}

// This is a messy function that creates a copy of the initial
// unsolved board, then solves it using the same algorithm
// as used in the main program EXCEPT it starts with 9 and
// goes down to 1 rather than vice versa. This way should
// result in a different solution than the main method
// IF there is one. It returns true if the solution is
// unique and false if there are multiple solutions.
// Pre-condition: Partial and solved Sudoku grids.
// Post-condition: Returns true if the solved grid is
// the only solution. Returns false if there are
// multiple solutions.
bool Sudoku::isUnique()
{
	Sudoku board2;
	ofstream fout;
	bool r = true;
	
	// Create copy of initial unsolved board
	for (int j = 0; j < 9; j++) {
		for (int i = 0; i < 9; i++) {
			if (hints[j][i])
				board2.board[j][i] = board[j][i];
		}
	}

	// Solve it differently
	board2.solve2(fout);

	// Compare the original solved board to the
	// board solved with descending candidate solutions
	for (int j = 0; j < 9; j++) {
		for (int i = 0; i < 9; i++) {
			if (board[j][i] != board2.board[j][i])
				return false;
		}
	}

	return true;
}

// Solves using descending candidate solutions rather
// than ascending. Used by isUnique() function.
// Pre-condition: Partial Sudoku grid.
// Post-condition: Results in a solved Sudoku grid that
// could be different from the solved grid from the
// solve() function.
bool Sudoku::solve2(ofstream &fout)
{
	int row, col;

	if (!getEmptyLocation(row, col))
		return true;

	for (int num = 9; num >= 1; num--)
	{
		if (canPlaceValue(row, col, num, fout))
		{
			addNumber(row, col, num, fout, false);

			if (solve2(fout))
				return true;

			board[row][col] = 0;
		}
	}
	return false;
}