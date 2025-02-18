// .h file rewrote from the .png on this repo - program for cs iii - hw 4 - ibraheem

#ifndef TIMECODE_H
#define TIMECODE_H

#include <string>
#include <stdexcept>

class TimeCode {
public:
    TimeCode(unsigned int hr = 0, unsigned int min = 0, unsigned long long sec = 0);
    TimeCode(const TimeCode& tc);
    ~TimeCode();

    void SetHours(unsigned int hours);
    void SetMinutes(unsigned int minutes);
    void SetSeconds(unsigned int seconds);

    void reset();

    unsigned int GetHours() const;
    unsigned int GetMinutes() const;
    unsigned int GetSeconds() const;

    unsigned long long GetTimeCodeAsSeconds() const { return t; };
    void GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const;
    static unsigned long long ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long sec);

    std::string ToString() const;

    TimeCode operator+(const TimeCode& other) const;
    TimeCode operator-(const TimeCode& other) const;
    TimeCode operator+(double a) const;

    bool operator==(const TimeCode& other) const;
    bool operator!=(const TimeCode& other) const;
    bool operator<(const TimeCode& other) const;
    bool operator<=(const TimeCode& other) const;
    bool operator>(const TimeCode& other) const;
    bool operator>=(const TimeCode& other) const;

private:
    unsigned long long t = 0;
};

#endif
