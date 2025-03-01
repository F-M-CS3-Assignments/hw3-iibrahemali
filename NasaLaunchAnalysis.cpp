// Last Update: Ibraheem
// Date & Time: Mar 1 - 3:16 pm

// Note: I have read the notes at ./assignment _3_part2.pdf

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include "TimeCode.h"

using namespace std;

// split csv line into fields, handle quotes
vector<string> split_csv_line(const string& line) {
    vector<string> fields;
    string current;
    bool in_quotes = false;
    char prev_char = 0;

    for (char c : line) {
        if (c == '"' && prev_char != '\\') {
            in_quotes = !in_quotes;  // toggle quote state
        } else if (c == ',' && !in_quotes) {
            if (!current.empty() && current.front() == '"' && current.back() == '"') {
                current = current.substr(1, current.size() - 2);  // remove quotes
            }
            fields.push_back(current);  // add field
            current.clear();  // reset for next field
        } else {
            current += c;  // build current field
        }
        prev_char = c;  // track prev char for escape
    }
    if (!current.empty() && current.front() == '"' && current.back() == '"') {
        current = current.substr(1, current.size() - 2);  // handle last field
    }
    fields.push_back(current);  // add last field

    return fields;
}

// parse line to extract timecode
TimeCode parse_line(const string& line) {
    vector<string> fields = split_csv_line(line);
    if (fields.size() < 4) throw invalid_argument("invalid line");

    string datum = fields[3];  // get date-time field
    vector<string> tokens;
    stringstream ss(datum);
    string token;
    while (ss >> token) tokens.push_back(token);  // split into tokens

    if (tokens.size() < 5 || tokens[4].find(':') == string::npos)
        throw invalid_argument("no time component");

    vector<string> timeParts;
    stringstream ts(tokens[4]);
    string part;
    while (getline(ts, part, ':')) timeParts.push_back(part);  // split time

    int hours = stoi(timeParts[0]);  // extract hours
    int minutes = stoi(timeParts[1]);  // extract minutes
    int seconds = (timeParts.size() > 2) ? stoi(timeParts[2]) : 0;  // extract seconds

    return TimeCode(hours, minutes, seconds);  // create timecode
}

int main() {
    vector<TimeCode> times;
    ifstream file("Space_Corrected.csv");
    string line;

    getline(file, line);  // skip header

    // read and parse each line
    while (getline(file, line)) {
        try {
            TimeCode tc = parse_line(line);
            times.push_back(tc);  // store timecode
        } catch (...) {}  // ignore invalid lines
    }

    // sum all timecodes
    TimeCode sum;
    for (const TimeCode& tc : times) sum = sum + tc;

    // calc and print average
    TimeCode average = sum / times.size();
    cout << times.size() << " data points." << endl;
    cout << "AVERAGE: " << average.ToString() << endl;

    return 0;
}