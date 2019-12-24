#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const int ALPHABET_SIZE = 26;
struct TrieNode
{
	TrieNode* children[ALPHABET_SIZE];
	bool endofword;
	TrieNode()
	{
		for (int i = 0; i < ALPHABET_SIZE; i++)
			children[i] = NULL;
		endofword = 0;
	}
};

void insertTrie(TrieNode* root, string key);

int readData(const char* path, TrieNode* root);

bool searchTrie(TrieNode* root, string key);

bool isLastNode(struct TrieNode* root);

int searchExistInVector(vector <char> input, char x);

int searchPositionInVector(vector <char> input, char x);

void suggestionsRec(struct TrieNode* root, string currPrefix, vector <string>& ans, vector <char> input);

void input(vector <char>& input);

TrieNode* remove(TrieNode* root, string key, int depth = 0);

