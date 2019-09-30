// Program Name: P4 - Sudoku Solver
// Programmer Name: Andrew Gasparovich
// Date Created: 8/16/2019
// Description: Solves a Sudoku pizzle
/////////////// given by Sudoku Creator

#include <iostream>
#include <fstream>
#include <chrono>
#include "Sudoku.h"
using namespace std::chrono;

void main()
{
	// Variables
	int y, x, val;
	string inputFileName, outputFileName;
	ifstream fin;
	ofstream fout;
	Sudoku board;

	// Input file
	cout << "Enter input file name: "; 
	cin >> inputFileName;
	fin.open(inputFileName, ios::in);
	if (fin.fail()) {
		cout << "Input file " << inputFileName << " not found. Terminating program.\n";
		return;
	}
	else if (fin.peek() == ifstream::traits_type::eof()) {
		cout << "Input file " << inputFileName << " is empty. Terminating program.\n";
		return;
	}
	else 
		cout << "Input file " << inputFileName << " opened successfully.\n\n";

	// Output file
	cout << "Enter output file name: ";
	cin >> outputFileName;
	while (outputFileName.substr(outputFileName.length() - 4, 4) != ".txt") {
		cout << "Error - File name must end in '.txt'.\nTry again: ";
		cin >> outputFileName;
	}
	fout.open(outputFileName, ios::in);
	cout << outputFileName << " opened successfully.\n\n";

	// Label the output file with the name of the input file used
	fout << "Input file: " << inputFileName << endl << endl;

	// Data input
	fin >> y >> x >> val;
	while (!fin.eof()) {
		board.addHint(y - 1, x - 1, val, fout);
		fin >> y >> x >> val;
	}

	// Start clock
	auto start = high_resolution_clock::now();

	// Sudoku
	board.printBoard(fout);

	board.solve(fout);

	cout << "Completed grid:\n";
	fout << "Completed grid:\n";
	board.printBoard(fout);

	// Stop clock
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	// Metrics reporting

	// Increments whenever the solver removes a value to try another
	cout << "Number of backtracks: " << board.getBacktracks() << endl;
	fout << "Number of backtracks: " << board.getBacktracks() << endl;

	// Increments whenever the solver compares a potential value to another value
	cout << "Number of comparisons to solve: " << board.getComparisons() << endl;
	fout << "Number of comparisons to solve: " << board.getComparisons() << endl;

	// Total time taken to solve the grid
	cout << "Time taken to solve: " << duration.count() << " ms (" << duration.count() / 1000000.0 << " s)" << endl;
	fout << "Time taken to solve: " << duration.count() << " ms (" << duration.count() / 1000000.0 << " s)" << endl;

	// Number of times a number failed Sudoku's rules
	cout << "Number of failed attemps to place: " << board.getPlacementFailures() << endl;
	fout << "Number of failed attemps to place: " << board.getPlacementFailures() << endl;

	// Is unique solution
	if (board.isUnique()) {
		cout << "The solution is unique.\n\n";
		fout << "The solution is unique.\n\n";
	}
	else {
		cout << "The solution is not unique.\n\n";
		fout << "The solution is not unique.\n\n";
	}

	// Close the files
	fin.close();
	fout.close();
}