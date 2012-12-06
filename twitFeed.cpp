#include <iostream>
#include<string>
#include <map>
#include <fstream>
#include <cstdlib>

#include <list>

using std::pair;
using std::map;
using std::string;
using std::ifstream;
using std::cout;
// better to do a splay tree??
using std::list;

int main(int argc, char** argv){
	if (argc != 2){
		cout << "usage: twits [filename]" << std::endl;
		return 0;
	}
	map <string,int> words;
	string line;
	bool found;
	int maxVal = 0;
	int count = 0;
	int count2 = 0;
	ifstream file(argv[1]);
	if (file.is_open()){
		while (file.good()){
			file >> line;
			//getline (file, line, ' '); // doesn't see end of line
			found = (bool)words.count(line);
			count++;
			if (!found){
				words.insert(pair<string, int>(line, 1));
				count2++;
			}
			else{
				words[line]++;
				if (words[line] > maxVal)
					maxVal = words[line];
			}
		}
	}
	int testCount = 0;
	list<string>* theHash = new list<string>[maxVal+1];
	for (map<string, int>::iterator it = words.begin(); it != words.end();){
		int bucket = it->second;
		if (bucket > 1){
			theHash[bucket].push_back(it->first);
			words.erase(it++);
			testCount++;
		}
		else
			++it;
	}

	//print the words in descending order of occurrence
	int testCount2 = 0;
	for (int bucket = maxVal; bucket > 0; --bucket){
		if (!theHash[bucket].empty()){
			for (list<string>::iterator i = theHash[bucket].begin(); i != theHash[bucket].end(); ++i){
				cout << bucket << " " << *i << std::endl;
				testCount2++;
			}
		}
	}

	int testCount3 = 0;
	for (map<string, int>::iterator it = words.begin(); it != words.end(); ++it){
			cout << it->second << " " << it->first << std::endl;
			testCount3++;
	}
	cout << count << " total number of words read from file" << std::endl;
	cout << count2 << " total number of entries in map" << std::endl;
	cout << testCount << " testcount of elements removed from map (those appearing more than once)" << std::endl;
	cout << testCount2 << " testcount of total elements in new hash table (should be same)" << std::endl;
	cout << testCount3 << " testcount of elements remaining in map (unique words)" << std::endl;
	cout << words.size() << " size of map (should be same) " << std::endl;
	cout << (double)count/testCount3 << " =  total occurrences of all words divided by number of words occurring only once " << std::endl;
	cout << (double)testCount3/count << " =  number of unique words divided by total occurrences of all words" << std::endl;
	cout << (double)count/count2 << " =  total occurrences of all words divided by number of distinct words " << std::endl;
	cout << (double)count2/count << " =  number of distinct words divided by total occurrences of all words" << std::endl;
	return 0;
}
