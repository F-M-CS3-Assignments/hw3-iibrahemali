#include <ctime>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <sstream>
#include "TimeCode.h"

using namespace std;

struct DryingSnapShot {
    int id;
    time_t startTime;
    TimeCode* timeToDry;
    unsigned long long dryTimeSeconds;
};

long long get_time_remaining(const DryingSnapShot& dss) {
    time_t now = time(0);
    long long elapsed = now - dss.startTime;
    long long remaining = dss.dryTimeSeconds - elapsed;
    return remaining > 0 ? remaining : 0;
}

string drying_snap_shot_to_string(const DryingSnapShot& dss) {
    stringstream ss;
    ss << "Batch-" << dss.id << " (takes " << dss.timeToDry->ToString() << " to dry) ";
    long long remaining = get_time_remaining(dss);
    if (remaining <= 0) {
        ss << "DONE!";
    } else {
        TimeCode tc(0, 0, remaining);
        ss << "time remaining: " << tc.ToString();
    }
    return ss.str();
}

double get_sphere_sa(double rad) {
    return 4.0 * M_PI * rad * rad;
}

TimeCode* compute_time_code(double surfaceArea) {
    unsigned long long seconds = static_cast<unsigned long long>(surfaceArea);
    return new TimeCode(0, 0, seconds);
}

int main() {
    srand(time(0));
    vector<DryingSnapShot> batches;
    char choice;

    do {
        cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
        cin >> choice;
        choice = toupper(choice);

        if (choice == 'A') {
            double radius;
            cout << "    radius: ";
            cin >> radius;

            double sa = get_sphere_sa(radius);
            TimeCode* tc = compute_time_code(sa);
            DryingSnapShot dss{rand(), time(0), tc, tc->GetTimeCodeAsSeconds()};
            batches.push_back(dss);
            cout << "    " << drying_snap_shot_to_string(dss) << endl;
        } else if (choice == 'V') {
            vector<DryingSnapShot> remaining;
            for (auto& batch : batches) {
                long long rem = get_time_remaining(batch);
                if (rem <= 0) {
                    delete batch.timeToDry;
                    cout << "    Batch-" << batch.id << " (takes " << batch.timeToDry->ToString() << " to dry) DONE!" << endl;
                } else {
                    remaining.push_back(batch);
                    cout << "    " << drying_snap_shot_to_string(batch) << endl;
                }
            }
            batches = remaining;
        }
    } while (choice != 'Q');

    for (auto& batch : batches) delete batch.timeToDry;
    return 0;
}