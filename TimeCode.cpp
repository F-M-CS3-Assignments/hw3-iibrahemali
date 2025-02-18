#include "TimeCode.h"
#include <string>
#include <stdexcept>

using namespace std;

// ------------------------------
// constructor and destructor
// ------------------------------

TimeCode::TimeCode(unsigned int hr, unsigned int min, unsigned long long sec) {
    t = ComponentsToSeconds(hr, min, sec);
}

TimeCode::TimeCode(const TimeCode& tc) : t(tc.t) {}

TimeCode::~TimeCode() {}

// ------------------------------
// setters
// ------------------------------

void TimeCode::SetHours(unsigned int hours) {
    unsigned int h, m, s;
    GetComponents(h, m, s);
    t = ComponentsToSeconds(hours, m, s);  // update only hours
}

void TimeCode::SetMinutes(unsigned int minutes) {
    if (minutes > 59)
        throw invalid_argument("minutes must be 0-59");
    unsigned int h, m, s;
    GetComponents(h, m, s);
    t = ComponentsToSeconds(h, minutes, s);  // update only minutes
}

void TimeCode::SetSeconds(unsigned int seconds) {
    if (seconds > 59)
        throw invalid_argument("seconds must be 0-59");
    unsigned int h, m, s;
    GetComponents(h, m, s);
    t = ComponentsToSeconds(h, m, seconds);  // update only seconds
}

void TimeCode::reset() {
    t = 0;  // reset the timecode to 0:0:0
}

// ------------------------------
// getters
// ------------------------------

unsigned int TimeCode::GetHours() const {
    return static_cast<unsigned int>(t / 3600);  // divide by 3600 to get hours
}

unsigned int TimeCode::GetMinutes() const {
    return (t % 3600) / 60;  // get the minutes after removing full hours
}

unsigned int TimeCode::GetSeconds() const {
    return t % 60;  // get the remaining seconds
}

// ------------------------------
// conversions
// ------------------------------

void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const {
    unsigned long long total = t;
    sec = total % 60;  // calculate seconds
    total /= 60;
    min = total % 60;  // calculate minutes
    total /= 60;
    hr = static_cast<unsigned int>(total);  // calculate hours
}

unsigned long long TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long sec) {
    // process seconds overflow
    unsigned long long total_sec = sec;
    unsigned long long carry_min = total_sec / 60;
    unsigned int remaining_sec = total_sec % 60;

    // process minutes overflow
    unsigned long long total_min = min + carry_min;
    unsigned long long carry_hr = total_min / 60;
    unsigned int remaining_min = total_min % 60;

    // add the hours and return the total seconds
    unsigned long long total_hr = hr + carry_hr;

    return total_hr * 3600ULL + remaining_min * 60ULL + remaining_sec;
}

string TimeCode::ToString() const {
    unsigned int h, m, s;
    GetComponents(h, m, s);
    return to_string(h) + ":" + to_string(m) + ":" + to_string(s);  // format as "h:m:s"
}

// ------------------------------
// arithmetic operators
// ------------------------------

TimeCode TimeCode::operator+(const TimeCode& other) const {
    return TimeCode(0, 0, t + other.t);  // add total seconds
}

TimeCode TimeCode::operator-(const TimeCode& other) const {
    if (t < other.t)
        throw invalid_argument("subtraction results in negative time");
    return TimeCode(0, 0, t - other.t);  // subtract total seconds
}

TimeCode TimeCode::operator+(double a) const {
    if (a < 0)
        throw invalid_argument("negative value not allowed");
    return TimeCode(0, 0, t + static_cast<unsigned long long>(a));  // add a double as seconds
}

// ------------------------------
// comparison operators
// ------------------------------

bool TimeCode::operator==(const TimeCode& other) const {
    return t == other.t;  // compare total seconds
}

bool TimeCode::operator!=(const TimeCode& other) const {
    return t != other.t;  // compare total seconds
}

bool TimeCode::operator<(const TimeCode& other) const {
    return t < other.t;  // compare total seconds
}

bool TimeCode::operator<=(const TimeCode& other) const {
    return t <= other.t;  // compare total seconds
}

bool TimeCode::operator>(const TimeCode& other) const {
    return t > other.t;  // compare total seconds
}

bool TimeCode::operator>=(const TimeCode& other) const {
    return t >= other.t;  // compare total seconds
}
