// Last Update: Ibraheem
// Date & Time: Mar 1 - 3:06 pm

#include "TimeCode.h"
#include <string>
#include <stdexcept>
#include <sstream>

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
    t = ComponentsToSeconds(hours, m, s);
}

void TimeCode::SetMinutes(unsigned int minutes) {
    if (minutes > 59)
        throw invalid_argument("minutes must be 0-59");
    unsigned int h, m, s;
    GetComponents(h, m, s);
    t = ComponentsToSeconds(h, minutes, s);
}

void TimeCode::SetSeconds(unsigned int seconds) {
    if (seconds > 59)
        throw invalid_argument("seconds must be 0-59");
    unsigned int h, m, s;
    GetComponents(h, m, s);
    t = ComponentsToSeconds(h, m, seconds);
}

void TimeCode::reset() {
    t = 0;
}

// ------------------------------
// getters
// ------------------------------

unsigned int TimeCode::GetHours() const {
    return static_cast<unsigned int>(t / 3600);
}

unsigned int TimeCode::GetMinutes() const {
    return (t % 3600) / 60;
}

unsigned int TimeCode::GetSeconds() const {
    return t % 60;
}

// ------------------------------
// conversions
// ------------------------------

void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const {
    unsigned long long total = t;
    sec = total % 60;
    total /= 60;
    min = total % 60;
    total /= 60;
    hr = static_cast<unsigned int>(total);
}

unsigned long long TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long sec) {
    unsigned long long total_sec = sec;
    unsigned long long carry_min = total_sec / 60;
    unsigned int remaining_sec = total_sec % 60;

    unsigned long long total_min = min + carry_min;
    unsigned long long carry_hr = total_min / 60;
    unsigned int remaining_min = total_min % 60;

    unsigned long long total_hr = hr + carry_hr;

    return total_hr * 3600ULL + remaining_min * 60ULL + remaining_sec;
}

string TimeCode::ToString() const {
    unsigned int h, m, s;
    GetComponents(h, m, s);
    return to_string(h) + ":" + to_string(m) + ":" + to_string(s);
}

// ------------------------------
// arithmetic operators
// ------------------------------

TimeCode TimeCode::operator+(const TimeCode& other) const {
    return TimeCode(0, 0, t + other.t);
}

TimeCode TimeCode::operator-(const TimeCode& other) const {
    if (t < other.t)
        throw invalid_argument("subtraction results in negative time");
    return TimeCode(0, 0, t - other.t);
}

TimeCode TimeCode::operator+(double a) const {
    if (a < 0)
        throw invalid_argument("negative value not allowed");
    return TimeCode(0, 0, t + static_cast<unsigned long long>(a));
}

TimeCode TimeCode::operator*(double a) const {
    if (a < 0) 
        throw invalid_argument("multiplier cannot be negative");
    return TimeCode(0, 0, static_cast<unsigned long long>(t * a));
}

TimeCode TimeCode::operator/(double a) const {
    if (a <= 0) 
        throw invalid_argument("divisor must be positive");
    return TimeCode(0, 0, static_cast<unsigned long long>(t / a));
}

// ------------------------------
// comparison operators
// ------------------------------

bool TimeCode::operator==(const TimeCode& other) const {
    return t == other.t;
}

bool TimeCode::operator!=(const TimeCode& other) const {
    return t != other.t;
}

bool TimeCode::operator<(const TimeCode& other) const {
    return t < other.t;
}

bool TimeCode::operator<=(const TimeCode& other) const {
    return t <= other.t;
}

bool TimeCode::operator>(const TimeCode& other) const {
    return t > other.t;
}

bool TimeCode::operator>=(const TimeCode& other) const {
    return t >= other.t;
}