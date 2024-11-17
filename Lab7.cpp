#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void saveToFile(const std::string& filename, const std::vector<std::string>& data) {
	std::fstream inp;
	inp.open(filename, std::ios::app);
	for (int i = 0; i < data.size(); ++i) {
		inp << data[i] << "\n";
	}
	inp.close();

}
void loadFromFile(const std::string& filename, std::vector<std::string>& outdata){
	std::fstream otp;
	std::string line;
	otp.open(filename, std::ios::in);
    	if (otp.is_open())
    	{
        	while (std::getline(otp, line)) // otp
        	{
            		std::cout << line << std::endl;
			outdata.push_back(line);
        	}
    	}
	otp.close();
}
int main() {

	std::string prom, filename;
	std::vector<std::string> data, outdata;
	std::cin >> filename;
	std::cin >> prom;

	while (prom != "0") {
		data.push_back(prom);
		std::cin >> prom;
	}

	saveToFile(filename, data);

	loadFromFile(filename, outdata);
	for (int i = 0; i < outdata.size(); ++i){
		std::cout << outdata[i] << "/n";
	}
}