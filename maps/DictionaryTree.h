// C++ implementation of search and insert 
// operations on Trie 

#include<iostream>
using std::string;
using std::cout;

const int Maximum_Size = 26;

// trie node 
struct Dictionary
{
	 Dictionary* word[Maximum_Size];

	// isEndOfWord is true if the node represents 
	// end of a word 
	bool isEndOfWord;
};

// Returns new trie node (initialized to NULLs) 
 Dictionary* getNode(void)
{
	 Dictionary* node = new Dictionary;

	node->isEndOfWord = false;

	for (int i = 0; i < Maximum_Size; i++)
		node->word[i] = NULL;

	return node;
}

// If not present, inserts key into trie 
// If the key is prefix of  trie node, just 
// marks leaf node 
void insert( Dictionary* root, string key)
{
	 Dictionary* insert = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!insert->word[index])
			insert->word[index] = getNode();

		insert = insert->word[index];
	}

	// mark last node as leaf 
	insert->isEndOfWord = true;
}

// Returns true if key presents in trie, else 
// false 
bool search( Dictionary* root, string key)
{
	 Dictionary* search = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!search->word[index])
			return false;

		search = search->word[index];
	}

	return (search != NULL && search->isEndOfWord);
}



