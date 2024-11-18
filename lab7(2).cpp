#include <iostream>
#include <string>
#include <vector>
#include <fstream>

struct Book
{
	std::string Author;
	std::string Title;
	int Year;
};

void saveToFile(const std::string& filename, const std::vector<Book>& data) {
	std::fstream inp;
	inp.open(filename, std::ios::app);
	for (int i = 0; i < data.size(); ++i) {
		inp << data[i].Author << " " << data[i].Title << " " << data[i].Year << "\n";
	}
	inp.close();
}

void loadFromFile(const std::string& filename, std::vector<Book>& outData) {
	std::string line, empty = " ";
	int f = 0;
	std::fstream otp;
	otp.open(filename, std::ios::in);
	if (otp.is_open())
	{
		while (std::getline(otp, line)) // otp
		{
			Book prom;
			std::string pr = "";
			for (int i = 0; i < line.size(); ++i) {
				if (line[i] != ' ') {
					pr += line[i];
					
				}
				else {
					if (f == 0) {
						prom.Author = pr;
						pr = "";
						f++;
					}

					else if (f == 1) {
						prom.Title = pr;
						pr = "";
						f++;
					}

				}
			}
			prom.Year = std::stoi(pr);
			pr = "";
			f = 0;
			outData.push_back(prom);
			prom = {};
		}
	}
	otp.close();
}

int main() {
	std::string filename;
	std::vector<Book> data;
	std::vector<Book> outData;
	std::cout << "input file name: ";
	std::cin >> filename;
	Book
		book1 = { "A", "A1", 1904 },
		book2 = { "B", "B1", 1903 },
		book3 = { "C", "C1", 1902 },
		book4 = { "D", "D1", 1901 };

	data = { book1, book2, book3, book4 };
	saveToFile(filename, data);
	loadFromFile(filename, outData);
	for (int i = 0; i < outData.size(); ++i) {
		std::cout << outData[i].Author << " " << outData[i].Title << " " << outData[i].Year << std::endl;
	}
}