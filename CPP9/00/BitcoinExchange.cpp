#include "BitcoinExchange.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <sstream>
#include <cstdlib>

/*
step 1: check argument list
step 2: open files
step 3: validate and save csv file to map
    step 1: open file
    step 2: check for corruption or correct format?
    step 3: create map with date+value entries for each line in csv
step 3: validate file(s)
    step a: open file
    step b: for each line
        step 1: seperate date + value
        step 2: validate date + value
        step 3: print message
*/

#define CSV_FILE "priceFile.csv"

//Helper functions
//1. Value checker
bool validateValue(double value)
{
    return (value >= 0 && value <= 1000);
}

//2. Date checker
bool isLeapYear(int year)
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

bool isValidDate(int year, int month, int day)
{
    if (year < 2000 || year > 2024)
        return false;
    if (month < 1 || month > 12 )
        return false;
    if (day < 1 || day > 31)
        return false;

    if (month == 2)
    {
        return (day <= (isLeapYear(year) ? 29 : 28));
    }
    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        return (day <= 30);
    }
    return true;

}

bool parseAndValidateDate(std::string dateValue, std::string &formattedDate) //add formatted date?
{
    int year, month, day;
    char delim1, delim2;

    //1. split date string
    std::istringstream iss(dateValue);
    iss >> year >> delim1 >> month >> delim2 >> day;

    //2. evaluate the parts of the string
    if (iss.fail() || delim1 != '-' || delim2 != '-' || !isValidDate(year, month, day))
        return false;

    //3. reconstruct date string to prepare for comparison
    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << year << '-'
        << std::setw(2) << std::setfill('0') << month << '-'
        << std::setw(2) << std::setfill('0') << day;
    formattedDate = oss.str();
    return true;
}

//3. process values and print
void processValues(const std::map<std::string, double>& priceMap, const std::string& date, double value)
{
    if (priceMap.empty())
    {
        std::cerr << "Price data is empty." << std::endl;
        return;
    }
    std::map<std::string, double>::iterator it;
    it = priceMap.lower_bound(date);
    if (it == priceMap.begin() && it->first > date)
    {
        std::cerr << "Error: Date " << date << " is earlier than  the earliest date in the data." << std::endl;
        return;
    }
    if (it == priceMap.end() || it->first != date)
    {
        if (it != priceMap.begin())
            --it;
    }
    double result = value * it->second;
    std::cout << date << " => " << value << " * " << it->second << " = " << result << std::endl;
}


void processCSVFile(std::map<std::string, double>& priceMap) {
    std::ifstream priceFile(CSV_FILE);
    if (!priceFile) {
        std::cerr << "Error: couldn't open file " << CSV_FILE << std::endl;
        std::exit(1);
    }

    std::string line, date, tempValue;
    double value;
    std::getline(priceFile, line); // skip header

    while (std::getline(priceFile, line)) {
        std::istringstream iss(line);
        if (!std::getline(iss, date, ',') || !std::getline(iss, tempValue)) {
            std::cerr << "Error: corrupted data in prices file" << std::endl;
            continue; // skip corrupted lines
        }
        try {
            value = std::stod(tempValue);
            priceMap[date] = value;
        } catch(const std::exception& e) {
            std::cerr << "Error: invalid number encountered " << e.what() << std::endl;
            continue;
        }
    }
}

void processInputFile(const char* inputFile, const std::map<std::string, double>& priceMap) {
    std::ifstream file(inputFile);
    if (!file) {
        std::cerr << "Error: couldn't open file " << inputFile << std::endl;
        std::exit(1);
    }

    std::string line, inputDate, formattedDate;
    double inputValue;
    char delimiter;

    std::getline(file, line); // skip header
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (!(iss >> inputDate >> delimiter >> inputValue) || delimiter != '|') {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (!parseAndValidateDate(inputDate, formattedDate)) {
            std::cerr << "Error: invalid date => " << inputDate << std::endl;
            continue;
        }
        if (!validateValue(inputValue)) {
            std::cerr << "Error: invalid value => " << inputValue << std::endl;
            continue;
        }

        processValues(priceMap, formattedDate, inputValue);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " input.txt" << std::endl;
        std::exit(1);
    }

    std::map<std::string, double> priceMap;
    processCSVFile(priceMap);
    processInputFile(argv[1], priceMap);

    return 0;
}
