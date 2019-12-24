#include "Header.h"

int main()
{
	vector <char> in;
	TrieNode* root = new TrieNode();
	readData("Dic.txt", root);
	input(in);
	
	string cur = "";
	
	vector <string> ans;
	suggestionsRec(root, cur, ans, in);
	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); i++)
	{
		cout << ans[i] << endl;
	}
	return 0;
}