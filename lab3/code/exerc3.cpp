/**************************
 * Lab 3: exercise 3      *
 **************************/

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <vector>

std::string getSubject(const std::string& word) {
	std::string subject = word;
	std::sort(subject.begin(), subject.end());
	return subject;
}

int main() {

	// First read in files and out
	std::ifstream inputFile("../code/uppgift3.txt");
	std::ofstream outputFile("../code/out_uppgift3.txt");

	while (!inputFile || !outputFile) {
		std::cout << "Error opening file\n";
		return 1;
	}

	std::map<std::string, std::vector<std::string>> anagramGroups;
	std::string word;

	// Read words from the input file and group them by their subject
	while (inputFile >> word) {
		std::string subject = getSubject(word);
		anagramGroups[subject].push_back(word);
	}

	// Write anagram groups to the output file
	outputFile << "---Anagram group---\n";
	for (const auto& group : anagramGroups) {
		if (group.second.size() > 1) {
			for (const auto& anagram : group.second) {
				outputFile << anagram << " ";
			}
			outputFile << "--> " << group.second.size() << " words.\n";
		}
	}

	inputFile.close();
	outputFile.close();
}
