#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

enum Score
{
    Unsatisfactorily = 2,
    Satisfactorily,
    Good,
    Excellent
};



struct Student
{
    std::string Name;
    int Year;
    std::map<std::string, Score> RecordBook;
};

// в качестве ключа - название группы
// в качестве значения - список студентов
using Groups = std::map<std::string, std::vector<Student>>;

void saveToFile(const std::string& filename, const Groups& groups) {
    std::fstream inp;
    inp.open(filename, std::ios::out);              
    for (std::pair<std::string, std::vector<Student>> element : groups) {
        inp << element.first << std::endl;
        for (int i = 0; i < element.second.size(); ++i) {
            inp << element.second[i].Name << " " << element.second[i].Year << std::endl;
            for (std::pair<std::string, Score> el : element.second[i].RecordBook) {
                inp << el.first << " " << el.second << std::endl;
            }
        }
    }
 
    inp.close();
}

void loadFromFile(const std::string& filename, Groups& outGroups) {
    std::string line, gr_name, a;
    std::vector<Student> St;
    Student pr;
    int f = 0, f1 = 0;
    std::fstream otp;
    otp.open(filename, std::ios::in);
    if (otp.is_open())
    {
        while (std::getline(otp, line))
        {
            if (line.substr(0, 5) == "group") {
                if (f) {
                    St.push_back(pr);
                    pr = {};
                    outGroups[gr_name] = St;
                    gr_name = "";
                    St = {};
                    f1 = 0;
                }
                gr_name = line;
                f = 1;
            }

            else {
                if (line.size() == 6 and line.substr(0, 4) == "math") {
                    if (line[5] == '2') {
                        pr.RecordBook["math"] = Unsatisfactorily;
                    }
                    else if (line[5] == '3') {
                        pr.RecordBook["math"] = Satisfactorily;
                    }
                    else if (line[5] == '4') { ////////////////////////////////////////////////
                        pr.RecordBook["math"] = Good;
                    }
                    else if (line[5] == '5') {
                        pr.RecordBook["math"] = Excellent;
                    }
                }
                else if (line.size() == 4 and line.substr(0, 2) == "Pe") {
                    if (line[3] == '2') {
                        pr.RecordBook["Pe"] = Unsatisfactorily;
                    }
                    else if (line[3] == '3') {
                        pr.RecordBook["Pe"] = Satisfactorily;
                    }
                    else if (line[3] == '4') {
                        pr.RecordBook["Pe"] = Good;
                    }
                    else if (line[3] == '5') {
                        pr.RecordBook["Pe"] = Excellent;
                    }

                }
                else if (line.size() == 5 and line.substr(0, 3) == "ENG") {
                    if (line[4] == '2') {
                        pr.RecordBook["ENG"] = Unsatisfactorily;
                    }
                    else if (line[4] == '3') {
                        pr.RecordBook["ENG"] = Satisfactorily;
                    }
                    else if (line[4] == '4') {
                        pr.RecordBook["ENG"] = Good;
                    }
                    else if (line[4] == '5') {
                        pr.RecordBook["ENG"] = Excellent;
                    }

                }
                else {
                    int i = 0;
                    while (line[i] != ' ') {
                        a += line[i];
                        i++;
                    }
                    if (f1) {
                        St.push_back(pr);
                        pr = {};
                    }
                    pr.Name = a;
                    pr.Year = std::stoi(line.substr(i + 1, 1));
                    
                    a = "";
                    f1 = 1;
                
                }
            }
        }
    }
    St.push_back(pr);
    outGroups[gr_name] = St;

    otp.close();
}

int main() {
    std::string filename;
    Student s1 = { "Dania", 3, {std::pair<std::string, Score>{"math", Excellent}, std::pair<std::string, Score>{"Pe", Good}, std::pair<std::string, Score>{"ENG", Good}}};
    Student s2 = { "Jhon", 3, {std::pair<std::string, Score>{"math", Good}, std::pair<std::string, Score>{"Pe", Good}, std::pair<std::string, Score>{"ENG", Excellent}}};
    Student s3 = { "Maria", 1, {std::pair<std::string, Score>{"math", Excellent}, std::pair<std::string, Score>{"Pe", Excellent}, std::pair<std::string, Score>{"ENG", Good}}};
    Student s4 = { "Kola", 1, {std::pair<std::string, Score>{"math", Unsatisfactorily}, std::pair<std::string, Score>{"Pe", Satisfactorily}, std::pair<std::string, Score>{"ENG", Excellent}}};

    std::vector<Student> v1 = { s1, s2 };
    std::vector<Student> v2 = { s3, s4 };
    Groups g1 = { std::pair<std::string, std::vector<Student>>{"group1", v1}, std::pair<std::string, std::vector<Student>>{"group2", v2} };
    std::cin >> filename;
    saveToFile(filename, g1);
    Groups g2;
    loadFromFile(filename, g2);

    for (std::pair<std::string, std::vector<Student>> element : g2) {
        std::cout << element.first << std::endl;
        std::cout << std::endl;
        for (int i = 0; i < element.second.size(); ++i) {
            std::cout << element.second[i].Name << " " << element.second[i].Year << std::endl;
            
            for (std::pair<std::string, Score> el : element.second[i].RecordBook) {
                std::cout << el.first << " " << el.second << std::endl;
            }
            std::cout << std::endl;
        }
    }

}
