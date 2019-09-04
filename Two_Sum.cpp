/* Filename: Two_Sum.cpp
 * Usage: ./Two_Sum 2sum.txt
 * Description: The command line program Two_Sum.cpp takes in one parameter,
 *              an input file name. The input file specified by the input
 *		file name should contain many integers, each on a new line.
 *		Using a hash table for efficient lookups, the program will 
 *		output the number of target values t in the interval 
 *		[-10000,10000] (inclusive) such that there are distinct numbers 
 *		x,y in the input file that satisfy x+y=t.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <limits>

// argv index of input file
#define IN_IDX 1

// expected number of arguments
#define EXPECTED_ARGS 2

// lower bound of targets
#define LOWER -10000

// upper bound of targets
#define UPPER 10000

using namespace std;

// read text file and insert all the integers into a hash table
unordered_set<long> readFile(const char* filename) {

	// stores (long) integers
	unordered_set<long> hashTable;

	// used for parsing input file
	string line;

	// used for parsing input file
	long current;

	// input file stream
	ifstream * in = new ifstream(filename);

	// Raise an error if file can't be read and exit
	if (in->eof()) {
		cerr << "Failed to read " << filename << "!\n";
		delete in;
		exit(-1);
	}	
	
	// while you can getline, convert each line to a long, and 
	// insert it into the hashTable
	while (getline(*in, line)) {
		current = stol(line);	
		hashTable.insert(current);
	}

	// no memory leaks here
	delete in;

	// return hashTable of integers
	return hashTable;
}

unsigned int computeNumTargets(unordered_set<long>& hash) {

	// used for looping through range of targets
	int i;

	// used for counting the number of targets
	unsigned int count = 0;

	// Loop through the targets i. For each element *it in the hash table,
	// lookup i - *it in the hash table. If i - *it is found and does not
	// equal *it, then increment the count, and break out of the inner for 
	// loop.
	for(int i = LOWER; i <= UPPER; ++i) {
		for( auto it = hash.cbegin(); it != hash.cend(); ++it ) {
			unsigned int got = hash.count(i - *it);
			if( (got > 0) && (i-*it != *it) ){
				count += 1;
				break;
			}
		}
	}

	return count;

}

int main(int argc, char** argv) {

	// check for arguments
	if( argc != EXPECTED_ARGS ){
		cout << "This program requires 2 arguments!" << endl;
		return -1;
	}


	// myHashTable is a hash table of all the integers in the text file
	unordered_set<long> myHashTable = readFile(argv[IN_IDX]);

	// compute the number of targets in the range for which there are 
	// distinct integers in the hash table that sum to the target
	unsigned int myCount = computeNumTargets(myHashTable);

	cout << "Number of Targets: " << myCount << endl; 

}
