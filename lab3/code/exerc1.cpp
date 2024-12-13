/*****************************************
 * Lab 3: exercise 1                      *
 ******************************************/

#include <iostream> // for everything
#include <map> //for map
#include <vector> //for vector
#include <algorithm> // for copy_if
#include <numeric> // accumulate
#include <string> // to string
 
 /*
<Payer name> <Receiver name> <price>
AE EM 102
AN PS 190
EM BD 23
CK EM 15
FF CK 17
AE CK 9
PS FF 50
DH FF 35
DH EM 65
PS AN 75
FF CK 18
AE EM 91
JP FF 203
*/

// Struct for holding the person information about name and balance
struct Person {
	std::string name;
	int balance;
};

bool loanCheck(const Person& a, const Person& b) {
	if (a.balance == b.balance) {
		return a.name < b.name;
	}
	return a.balance > b.balance;
}

bool debtCheck(const Person& a, const Person& b) {
	if (abs(a.balance) == abs(b.balance)) {
		return a.name < b.name;
	}
	return abs(a.balance) < abs(b.balance);
}

int main() {

	// Values
	std::string payer, receiver;
	int amount;

	// Add a key to every name and adds amount to it
	// map takes in name, and the amount
	std::map<std::string, int> balances;

	// Read input
	std::cout << "Enter list of friend to friend loans:\n";
	while (std::cin >> payer >> receiver >> amount) {
		balances[payer] += amount;
		balances[receiver] -= amount;
	}

	//Transfer data from map "balances" to a vector with the struct Person
	std::vector<Person> people;
	for (const auto& entry : balances) {
		people.push_back({ entry.first, entry.second });
	}

	//Seperate loans and debts
	std::vector<Person> loans;
	std::vector<Person> debts;

	// std::copy if(beginning of source, end of source, where element should be copied to, "condition" return a bool value)
	// to use condition we use a lambda function [capture](parameters) { return true/false});
	// people has parameters Person therefor [const Person& p], capture we dont need anything accessible inside lambda
	std::copy_if(people.begin(), people.end(), std::back_inserter(loans), [](const Person& p) {
		return p.balance > 0;
		});
	std::copy_if(people.begin(), people.end(), std::back_inserter(debts), [](const Person& p) {
		return p.balance < 0;
		});


	std::sort(loans.begin(), loans.end(), loanCheck);
	std::sort(debts.begin(), debts.end(), debtCheck);
	


	std::cout << "\nName Balance\n";
	//for (const auto& person : loans) {
	//	std::cout << person.name << " " << person.balance << "\n";
	//}

	//for (const auto& person : debts) {
	//	std::cout << person.name << " " << person.balance << "\n";



	//std::ostream_iterator -> An output iterator that writes strings to std::cout, followed by a newline character.
	//This is where the transformed elements will be stored
	// std::transform iterates over the range [loans.begin(), loans.end()).
	// For each Person object in the range, the lambda function is called.
	// The lambda function takes a Person object p and returns a string in the format "name balance".
	// The resulting string is written to std::cout using the std::ostream_iterator.
	std::transform(loans.begin(), loans.end(), std::ostream_iterator<std::string>(std::cout, "\n"), [](const Person& p) {
		return p.name + " " + std::to_string(p.balance);
		});	

	std::transform(debts.begin(), debts.end(), std::ostream_iterator<std::string>(std::cout, "\n"), [](const Person& p) {
		return p.name + " " + std::to_string(p.balance);
		});


	int meanLoan = 0;
	int meanDebt = 0;

	meanLoan = std::accumulate(loans.begin(), loans.end(), 0, [](double sum, Person& p) {
		return sum + abs(p.balance);
		})/loans.size();

	meanDebt = std::accumulate(debts.begin(), debts.end(), 0, [](double sum, Person& p) {
		return sum + abs(p.balance);
		}) /debts.size();
	

	std::cout << "\nMean loan amount: " << meanLoan << "\n";
	std::cout << "Mean debt amount: " <<  meanDebt << "\n";
	

}