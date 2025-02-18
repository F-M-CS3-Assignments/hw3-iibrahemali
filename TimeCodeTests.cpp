// Last Update: Ibraheem
// Date & Time: Feb 18 - 11 am

#include <iostream>
#include <cassert>
#include "TimeCode.h"

using namespace std;

// ------------------------------
// Test ComponentsToSeconds
// ------------------------------
void TestComponentsToSeconds() {
    cout << "Testing ComponentsToSeconds" << endl;
    
    // Random but "safe" inputs
    assert(TimeCode::ComponentsToSeconds(3, 17, 42) == 11862);
    
    // Edge case: all zeros
    assert(TimeCode::ComponentsToSeconds(0, 0, 0) == 0);
    
    // Roll-over: 60 minutes should turn into an hour
    assert(TimeCode::ComponentsToSeconds(1, 60, 0) == 2 * 3600);
    
    // Very large values to test overflow behavior
    assert(TimeCode::ComponentsToSeconds(1000, 0, 0) == 1000 * 3600);

    // More edge cases
    assert(TimeCode::ComponentsToSeconds(0, 59, 59) == 3599);

    cout << "PASSED!" << endl << endl;
}

// ------------------------------
// Test Default Constructor
// ------------------------------
void TestDefaultConstructor() {
    cout << "Testing Default Constructor" << endl;

    // Ensure that a default TimeCode object initializes to 0:0:0
    TimeCode tc;
    assert(tc.ToString() == "0:0:0");
    
    cout << "PASSED!" << endl << endl;
}

// ------------------------------
// Test Component Constructor
// ------------------------------
void TestComponentConstructor() {
    cout << "Testing Component Constructor" << endl;

    // Constructor with zero values
    TimeCode tc1(0, 0, 0);
    assert(tc1.ToString() == "0:0:0");

    // Constructor with roll-over values (e.g., minutes > 60)
    TimeCode tc2(3, 71, 3801);
    assert(tc2.ToString() == "5:14:21");

    // Constructor with large hours
    TimeCode tc3(25, 0, 0);
    assert(tc3.ToString() == "25:0:0");

    // Edge case: all components at their maximum without rolling over
    TimeCode tc4(0, 59, 59);
    assert(tc4.ToString() == "0:59:59");

    cout << "PASSED!" << endl << endl;
}

// ------------------------------
// Test GetComponents
// ------------------------------
void TestGetComponents() {
    cout << "Testing GetComponents" << endl;
    
    unsigned int h, m, s;

    // Regular values
    TimeCode tc(5, 2, 18);
    tc.GetComponents(h, m, s);
    assert(h == 5 && m == 2 && s == 18);

    // Edge case: 100 hours, 59 minutes, and 59 seconds
    TimeCode tc2(100, 59, 59);
    tc2.GetComponents(h, m, s);
    assert(h == 100 && m == 59 && s == 59);

    cout << "PASSED!" << endl << endl;
}

// ------------------------------
// Test Subtract
// ------------------------------
void TestSubtract() {
    cout << "Testing Subtract" << endl;

    // Simple subtraction
    TimeCode tc1(1, 0, 0);
    TimeCode tc2(0, 50, 0);
    TimeCode tc3 = tc1 - tc2;
    assert(tc3.ToString() == "0:10:0");

    // Test for exception when result would be negative
    TimeCode tc4(1, 15, 45);
    try {
        TimeCode tc5 = tc1 - tc4;
        assert(false);  // This should not be reached
    } catch (const invalid_argument& e) {}

    // Subtracting zero
    TimeCode tc6(10, 10, 10);
    TimeCode tc7(0, 0, 0);
    assert((tc6 - tc7).ToString() == "10:10:10");

    cout << "PASSED!" << endl << endl;
}

// ------------------------------
// Test SetMinutes
// ------------------------------
void TestSetMinutes() {
    cout << "Testing SetMinutes" << endl;

    TimeCode tc(8, 5, 9);

    // Test valid change
    tc.SetMinutes(15);
    assert(tc.ToString() == "8:15:9");

    // Test for exception on invalid input (minutes >= 60)
    try {
        tc.SetMinutes(80);
        assert(false);  // Should not reach here
    } catch (const invalid_argument& e) {}

    // Ensure time did not change after the exception
    assert(tc.ToString() == "8:15:9");

    cout << "PASSED!" << endl << endl;
}

// ------------------------------
// Test Operators
// ------------------------------
void TestOperators() {
    cout << "Testing Operators" << endl;

    TimeCode tc1(1, 30, 0);
    TimeCode tc2(0, 45, 0);

    // Test addition
    assert((tc1 + tc2).ToString() == "2:15:0");

    // Test comparison operators
    assert(tc1 > tc2);
    assert(tc2 < tc1);
    assert(tc1 != tc2);

    // Equality
    TimeCode tc3(1, 30, 0);
    assert(tc1 == tc3);

    // Test adding a double value
    TimeCode tc4 = tc1 + 3600.0;  // Should add 1 hour
    assert(tc4.ToString() == "2:30:0");

    cout << "PASSED!" << endl << endl;
}

// ------------------------------
// Main Function
// ------------------------------
int main() {
    TestComponentsToSeconds();
    TestDefaultConstructor();
    TestComponentConstructor();
    TestGetComponents();
    TestSubtract();
    TestSetMinutes();
    TestOperators();
    cout << "PASSED ALL TESTS!!!" << endl;
    return 0;
}
