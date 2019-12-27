#include "Header.h"

TrieNode* newNode()
{
	TrieNode* node = new TrieNode;
	node->endofword = 0;
	for (int  i = 0; i < ALPHABET_SIZE; i++)
	{
		node->children[i] = NULL;
	}
	return node;
}

void insertTrie(TrieNode* root, string key)
{
	int ch;
	TrieNode* current = root;
	for (int i = 0; i < key.size(); i++)
	{
		ch = key[i] - 'a';
		if (current->children[ch] == NULL)
		{
			current->children[ch] = newNode();
		}
		current = current->children[ch];
	}
	current->endofword++;
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
	int ch;
	TrieNode* current = root;
	for (int i = 0; i < key.size(); i++)
	{
		ch = key[i] - 'a';
		if (current->children[ch] == NULL)
		{
			return false;
		}
		current = current->children[ch];
	}
	//return (current->endofword && current != NULL);
	return current->endofword > 0;
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

bool isWord(TrieNode* node)
{
	return (node->endofword != 0);
}

bool isEmpty(TrieNode* node)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (node->children[i] != NULL)
		{
			return false;
		}
	}
	return true;
}
bool remove(TrieNode* root, string key, int depth)
{
	if (!root)
		return NULL;
	int ch = key[depth] - 'a';
	if (depth == key.size())
	{
		/*root->endofword = 0;
		if (isLastNode(root))
		{
			delete root;
			root = NULL;
		}
		return root;*/
		if (root->endofword > 0)
		{
			root->endofword--;
			return true;
		}
		return false;
	}

	int flag = remove(root->children[ch], key, depth + 1);
	if (flag && !isWord(root->children[ch]) && isEmpty(root->children[ch]))
	{
		delete root->children[ch];
		root->children[ch] = NULL;
	}
	return flag;

}
