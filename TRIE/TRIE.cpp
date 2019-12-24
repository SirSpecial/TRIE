#include "Header.h"

void insertTrie(TrieNode* root, string key)
{
	TrieNode* current = root;
	for (int i = 0; i < key.size(); i++)
	{
		char index = key[i] - 'a';
		if (!current->children[index]) current->children[index] = new TrieNode();
		current = current->children[index];
	}
	current->endofword = 1;
}

int readData(const char* path, TrieNode* root)
{
	ifstream fin;
	fin.open(path);
	if (!fin.is_open()) return 0;
	string word;
	while (!fin.eof())
	{
		getline(fin, word);
		insertTrie(root, word);
	}
	fin.close();
	return 1;
}

bool searchTrie(TrieNode* root, string key)
{
	TrieNode* current = root;
	for (int i = 0; i < key.size(); i++)
	{
		char index = key[i] - 'a';
		if (!current->children[index]) return false;
		current = current->children[index];
	}
	return (current->endofword && current != NULL);
}

bool isLastNode(struct TrieNode* root)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root->children[i])
			return 0;
	return 1;
}

int searchExistInVector(vector <char> input, char x)
{
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == x) return 1;
	}
	return 0;
}

int searchPositionInVector(vector <char> input, char x)
{
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == x) return i;
	}
	return 0;
}

void display(struct TrieNode* root, char str[], int level)
{

	if (root->endofword)
	{
		str[level] = '\0';
		cout << str << endl;
	}

	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (root->children[i])
		{
			str[level] = i + 'a';
			display(root->children[i], str, level + 1);
		}
	}
}

TrieNode* remove(TrieNode* root, string key, int depth)
{
	if (!root) return NULL;
	if (depth == key.size())
	{
		root->endofword = 0;
		if (isLastNode(root))
		{
			delete root;
			root = NULL;
		}
		return root;
	}
	char index = key[depth] - 'a';
	root->children[index] = remove(root->children[index], key, depth + 1);
	if (isLastNode(root) && root->endofword == false)
	{
		delete root;
		root = NULL;
	}
	return root;
}

void suggestionsRec(struct TrieNode* root, string currPrefix, vector <string>& ans, vector <char> input)
{
	if (root->endofword)
	{
		if (currPrefix.size() >= 3)
			ans.push_back(currPrefix);
	}
	if (input.size() == 0) return;
	if (isLastNode(root))
		return;

	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		vector <char> temp = input;
		if (root->children[i] && searchExistInVector(temp, i + 'a'))
		{
			temp.erase(temp.begin() + searchPositionInVector(temp, i + 'a'));
			//currPrefix.push_back('a' + i);
			char x = 'a' + i;
			suggestionsRec(root->children[i], currPrefix + x, ans, temp);
		}
	}
}

void input(vector <char>& input)
{
	char temp;
	string line;
	getline(cin, line);
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] != ' ') input.push_back(line[i]);
	}
}

