/****************************
 * Lab 3: exercise 2        *
 ****************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <cmath>

struct Point {
	int x, y;

	// Constructor to initialize from a string like "x,y"
	Point(const std::string& line) {
		size_t commaPos = line.find(",");
		x = std::stoi(line.substr(0, commaPos));
		y = std::stoi(line.substr(commaPos + 1));
	}

	// Function to convert point to a string for printing
	std::string toString() const {
		return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
	}
};

double distance(const Point& p1, const Point& p2) {
	return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}


int main() {
	//First Read in file
	std::ifstream inputFile("../code/points.txt");
	if (!inputFile) {
		std::cout << "Error: Couldnt open file!!!" << "\n";
		return 1;
	}

	// Read the lines from the file into a vector of strings
	std::vector<std::string> lines((std::istream_iterator<std::string>(inputFile)), std::istream_iterator<std::string>());

	// Transform the vector of strings into a vector of Points
	std::vector<Point> points;
	points.reserve(lines.size());

	std::transform(lines.begin(), lines.end(), std::back_inserter(points), [](const std::string& line) {
		return Point(line);
		});

	// Print the points
	std::cout << "The points:\n";
	std::transform(points.begin(), points.end(), std::ostream_iterator<std::string>(std::cout, "\n"), [](const Point& p) {
		return p.toString();
		});

	// Calculate the total distance traveled
	double totalDistance = std::accumulate(points.begin(), points.end() - 1, 0.0, [](double sum, const Point& p1) {
		const Point& p2 = *(std::next(&p1));
		return sum + distance(p1, p2);
		});

	// Print the total distance traveled
	std::cout << "\nTotal distance traveled = " << totalDistance << "\n";


}