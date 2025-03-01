// Last Update: Ibraheem
// Date & Time: Mar 1 - 3:06 pm


// Note: I have read the notes at ./assignment _3_part2.pdf

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include "TimeCode.h"

using namespace std;

vector<string> split_csv_line(const string& line) {
    vector<string> fields;
    string current;
    bool in_quotes = false;
    char prev_char = 0;

    for (char c : line) {
        if (c == '"' && prev_char != '\\') {
            in_quotes = !in_quotes;
        } else if (c == ',' && !in_quotes) {
            if (!current.empty() && current.front() == '"' && current.back() == '"') {
                current = current.substr(1, current.size() - 2);
            }
            fields.push_back(current);
            current.clear();
        } else {
            current += c;
        }
        prev_char = c;
    }
    if (!current.empty() && current.front() == '"' && current.back() == '"') {
        current = current.substr(1, current.size() - 2);
    }
    fields.push_back(current);

    return fields;
}

TimeCode parse_line(const string& line) {
    vector<string> fields = split_csv_line(line);
    if (fields.size() < 4) throw invalid_argument("Invalid line");

    string datum = fields[3];
    vector<string> tokens;
    stringstream ss(datum);
    string token;
    while (ss >> token) tokens.push_back(token);

    if (tokens.size() < 5 || tokens[4].find(':') == string::npos)
        throw invalid_argument("No time component");

    vector<string> timeParts;
    stringstream ts(tokens[4]);
    string part;
    while (getline(ts, part, ':')) timeParts.push_back(part);

    int hours = stoi(timeParts[0]);
    int minutes = stoi(timeParts[1]);
    int seconds = (timeParts.size() > 2) ? stoi(timeParts[2]) : 0;

    return TimeCode(hours, minutes, seconds);
}

int main() {
    vector<TimeCode> times;
    ifstream file("Space_Corrected.csv");
    string line;

    getline(file, line); // Skip header

    while (getline(file, line)) {
        try {
            TimeCode tc = parse_line(line);
            times.push_back(tc);
        } catch (...) {}
    }

    TimeCode sum;
    for (const TimeCode& tc : times) sum = sum + tc;

    TimeCode average = sum / times.size();
    cout << times.size() << " data points." << endl;
    cout << "AVERAGE: " << average.ToString() << endl;

    return 0;
}