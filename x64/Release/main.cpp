// Maps lab exercise
// Adam Sampson <a.sampson@abertay.ac.uk>

#include <cassert>
#include <iostream>
#include <string>
#include<unordered_map>
#include<chrono>
#include "utils.h"
#include <fstream>
#include"DictionaryTree.h"
#include<algorithm>

// Import things we need from the standard library
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::hash;
using std::cin;
long long int number = 0;
long long int numberofPermutation = 0;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::milliseconds;
using std::chrono::microseconds;


std::unordered_map< string, size_t> dictionary;

typedef std::chrono::steady_clock the_clock;

struct Dictionary* root = getNode();

int main(int argc, char *argv[]) {
	string file;
	load_file("words.txt", file);
	//dictionary.reserve(300000);

	size_t pos1 = 0;
	size_t pos2;

	//create the array to store the strings.
	std::vector<string> str;
	//235886
	//TRIE
	for (int x = 0; x < 235890; x++) {
		pos2 = file.find("\n", pos1);
		str.push_back(file.substr(pos1, (pos2 - pos1)));

		std::transform(str[x].begin(), str[x].end(), str[x].begin(),
			[](unsigned char c) { return std::tolower(c); });
		insert(root, str[x]);
		pos1 = pos2 + 1;
	}
	//MAP
	for (int x = 0; x < 235890; x++) {
		pos2 = file.find("\n", pos1);
		str.push_back(file.substr(pos1, (pos2 - pos1)));

		std::transform(str[x].begin(), str[x].end(), str[x].begin(),
			[](unsigned char c) { return std::tolower(c); });
		//cout <<x<<". "<<str[x]<<endl;
		//dictionary[std::hash<std::string>{}(str[x])] = str[x];
		dictionary[str[x]] = std::hash<std::string>{}(str[x]);
		pos1 = pos2 + 1;
	}



	file.erase();
	str.clear();
	


	cout << "Anagram Finder:- It finds all the anagram for a given word or a string and shows how much time it took to find the anagrams\nTry the word:  Treason\n";

	string s;
	int choice;
	the_clock::time_point start;
	the_clock::time_point end;
	auto time_taken = duration_cast<milliseconds>(end - start).count();

	cout << "Press 1 for unordered_map.\nPress 2 for Trie Tree\nPress 0 to Exit\n";
	cin >> choice;
	while (choice != 0)
	{
		switch (choice) {
		case 1:
			cout << "Enter a word: ";
			cin >> s;
			std::sort(s.begin(), s.end());

			start = the_clock::now();
			do {
				numberofPermutation++;
				std::unordered_map< string, size_t >::const_iterator got = dictionary.find(s);
				if (got == dictionary.end())
					//std::cout << "not found"<<endl;
					cout << "";

				else
				{
					std::cout << "->" << got->first << endl;
					number++;
				}
			} while (std::next_permutation(s.begin(), s.end()));
			end = the_clock::now();

			if (number <= 1)
				cout << number << " anagram exist" << endl;
			else
				cout << number << " anagrams exist" << endl;
			cout<< numberofPermutation<<" unique permutation exists." << endl;

			time_taken = duration_cast<microseconds>(end - start).count();
			cout << "It took " << time_taken << " micro seconds.\n";
			number = 0;
			numberofPermutation = 0;
			break;

		case 2:


			cout << "Enter a word: ";
			cin >> s;
			std::sort(s.begin(), s.end());

			start = the_clock::now();
			do {
				numberofPermutation++;

				if (search(root, s)) {
					number++;
					cout << "->" << s << endl;
				}
			} while (std::next_permutation(s.begin(), s.end()));
			end = the_clock::now();

			//findPermutations(input,0,strlen(input));
			if (number <= 1)
				cout << number << " anagram exist" << endl;
			else
				cout << number << " anagrams exist" << endl;
			cout << numberofPermutation << " unique permutation exists." << endl;

			time_taken = duration_cast<microseconds>(end - start).count();
			cout << "It took " << time_taken << "  micro seconds.\n";
			number = 0;
			numberofPermutation = 0;
			break;
		}
		cout << "\n\nPress 1 for unordered_map.\nPress 2 for Trie Tree\nPress 0 to Exit\n";
		cin >> choice;
	}
	return 0;
}
/*undefinability*/

