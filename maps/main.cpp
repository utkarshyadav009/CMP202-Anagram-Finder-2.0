// Maps lab exercise
// Adam Sampson <a.sampson@abertay.ac.uk>

#include <iostream>
#include <string>
#include<unordered_map>
#include<chrono>
#include "utils.h"
#include <fstream>
#include"DictionaryTree.h"
#include<algorithm>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <cassert>
#include<thread>
#include"ThreadPool.h"

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
using std::vector;
using std::thread;
using std::mutex;
using std::unique_lock;
using std::queue;
using std::condition_variable;


std::unordered_map< string, size_t> dictionary;

typedef std::chrono::steady_clock the_clock;

struct Dictionary* root = getNode();
string s;

std::vector<string> words;
std::vector<string> results;
std::mutex results_mutex;



string map_search(std::string s) {
	auto got = dictionary.find(s);
	numberofPermutation++;
	if (got == dictionary.end())
		return "";
	else
	{
		//number_m++;
		number++;
		return (*got).first;
	}
}

string tree_search(std::string s) {
	numberofPermutation++;
	if ((search(root, s))) {
		number++;
		return s;
	}
	return "";
}
int main(int argc, char *argv[]) {

	
	int num_threads = std::thread::hardware_concurrency();
	ThreadPool pool(num_threads);

	//string for loading the entire dictionary 
	string file;
	load_file("words.txt", file);

	size_t pos1 = 0;
	size_t pos2;

	//vector to store the each individual word.
	vector<string> str;
	//235886
	//TRIE
	//storing all the words in a tree using a vector of strings 
	for (int x = 0; x < 235890; x++) {
		//finding the end of line each word is stored in one row and multiple columns 
		pos2 = file.find("\n", pos1);
		str.push_back(file.substr(pos1, (pos2 - pos1)));

		//converting all the alphabets in a particular word to lowercase 
		std::transform(str[x].begin(), str[x].end(), str[x].begin(),
			[](unsigned char c) { return std::tolower(c); });

		//storing the word in the tree 
		insert(root, str[x]);

		//hashing the word and storing it in a map		
		dictionary[str[x]] = std::hash<std::string>{}(str[x]);

		//incrementing the position
		pos1 = pos2 + 1;
	}
	

	//free-ing memory out of the main dictionary string and the vector of words
	file.erase();
	str.clear();
	


	cout << "Anagram Finder:- It finds all the anagram for a given word or a string and shows how much time it took to find the anagrams\nTry the word:  Treason\n";

	
	int choice;
	the_clock::time_point start;
	the_clock::time_point end;
	auto time_taken = duration_cast<milliseconds>(end - start).count();

	cout << "Press 1 for unordered_map.\nPress 2 for Trie Tree\nPress 0 to Exit\n";
	cin >> choice;
	while (choice != 0)
	{
		switch (choice) {
		case 1: {
			cout << "Enter a word: ";
			cin >> s;
			std::sort(s.begin(), s.end());

			start = the_clock::now();
			std::vector<std::future<void>> values;

			do {
				words.emplace_back(s);
				//auto returnValue = pool.push(map_search, s);
				//values.emplace_back(pool.push(map_search, s));
				//string str = map_search(s);
				//if (str.empty())
				//	continue;
				//cout << "->" << str << endl;
				
				//if (returnValue.get() == true)
				//{
				//	cout << "->" << s<<endl;
				//}
			} while (std::next_permutation(s.begin(), s.end()));

			/*
			[][][][][] [][][][][] [][][][][]
			*/

			auto func =
				[](size_t from, size_t to) {
					std::vector<string> local_results;
					for (size_t i = from; i < to; ++i) {
						local_results.emplace_back(map_search(words[i]));
					}
					std::unique_lock<std::mutex> lock(results_mutex);
					for (auto& res : local_results)
						results.emplace_back(std::move(res));
				};
			 
			size_t n = 500;

			size_t word_skip = words.size() / 30;

			for (size_t i = 0; i < words.size(); i += word_skip) {
				size_t to = i + word_skip;
				if (to >= words.size())
					to = words.size();
				values.emplace_back(pool.enqueue(func, i, to));
			}

			for (auto& v : values)
				v.get();

			end = the_clock::now();

			for (auto& res : results) {
				if(!res.empty())
					cout << "->" << res << endl;
			}

			results.clear();

			if (number <= 1)
				cout << number << " anagram exist" << endl;
			else
				cout << number << " anagrams exist" << endl;
			cout << numberofPermutation << " unique permutation exists." << endl;

			time_taken = duration_cast<microseconds>(end - start).count();
			cout << "It took " << time_taken << " micro seconds.\n";
			number = 0;
			numberofPermutation = 0;
			break;

		}
		case 2:


			cout << "Enter a word: ";
			cin >> s;
			std::sort(s.begin(), s.end());

			start = the_clock::now();
			std::vector<std::future<void>> values;
			do {
				words.emplace_back(s);			
 			} while (std::next_permutation(s.begin(), s.end()));
			auto func =
				[](size_t from, size_t to) {
				std::vector<string> local_results;
				for (size_t i = from; i < to; ++i) {
					local_results.emplace_back(map_search(words[i]));
				}
				std::unique_lock<std::mutex> lock(results_mutex);
				for (auto& res : local_results)
					results.emplace_back(std::move(res));
			};
			size_t word_skip = words.size() / 26;

			for (size_t i = 0; i < words.size(); i += word_skip) {
				size_t to = i + word_skip;
				if (to >= words.size())
					to = words.size();
				values.emplace_back(pool.enqueue(func, i, to));
			}

			for (auto& v : values)
				v.get();

			end = the_clock::now();

			for (auto& res : results) {
				if (!res.empty())
					cout << "->" << res << endl;
			}
			results.clear();
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


