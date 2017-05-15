#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>

using namespace std;

void shrink(const string&, const vector<string>&, const set<string>&);

int main()
{
	string filename;
	cout << "Input the dictionary file name:";
	cin >> filename;
	fstream infile(filename);
	if (!infile || !infile.is_open()) {
		cerr << "Error open file." << endl;
		return -1;
	}

	set<string> dict;
	string word;
	infile >> word;
	while (!infile.eof() && word != "") {
		dict.insert(word);
		infile >> word;
	}
	for (char c = 'a'; c <= 'z'; c++) {
		string ch;
		ch += c;
		dict.insert(ch);
	}
	string input;
	cout << "input the word to shrink.";
	cin >> input;
	if (dict.find(input) != dict.end()) {
		vector<string> record;
		record.push_back(input);
		shrink(input, record, dict);
		cout << "Done" << endl;
	}
	return 0;
}

void shrink(const string& original, const vector<string>& cache, const set<string>& lexicon)
{
	if (original.size() == 1) {
		for (vector<string>::const_iterator it = cache.cbegin(); it != cache.cend(); ++it) {
			cout << *it << " -> ";
		}
		cout << original << endl;
	}
	else {
		for (size_t i = 0; i != original.size(); i++) {
			string cut = original.substr(0, i) + original.substr(i + 1, original.size());
			if (lexicon.find(cut) == lexicon.end()) continue;
			vector<string> new_cache(cache);
			new_cache.push_back(cut);
			shrink(cut, new_cache, lexicon);
		}
	}
	return;
}