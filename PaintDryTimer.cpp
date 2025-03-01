// Last Update: Ibraheem
// Date & Time: Mar 1 - 3:27 pm

#include <ctime>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <sstream>
#include "TimeCode.h"

using namespace std;

struct DryingSnapShot { //struct to track drying batches
    int id;
    time_t startTime;
    TimeCode* timeToDry;
    unsigned long long dryTimeSeconds;
};

//calc time left for drying
long long get_time_remaining(const DryingSnapShot& dss) {
    time_t now = time(0);
    long long elapsed = now - dss.startTime;
    long long remaining = dss.dryTimeSeconds - elapsed;
    return remaining > 0 ? remaining : 0;
}

//create status string for batch
string drying_snap_shot_to_string(const DryingSnapShot& dss) {
    stringstream ss;
    ss << "Batch-" << dss.id << " (takes " << dss.timeToDry->ToString() << " to dry) ";
    long long remaining = get_time_remaining(dss);
    if (remaining <= 0) {
        ss << "DONE!";
    } else {
        TimeCode tc(0, 0, remaining); //convert seconds to hh:mm:ss
        ss << "time remaining: " << tc.ToString();
    }
    return ss.str();
}

// calc sphere surface area
double get_sphere_sa(double rad) {
    return 4.0 * M_PI * rad * rad;
}

// convert sa to timecode (1cm^2 = 1sec)
TimeCode* compute_time_code(double surfaceArea) {
    unsigned long long seconds = static_cast<unsigned long long>(surfaceArea);
    return new TimeCode(0, 0, seconds); // store on heap
}

int main() {
    srand(time(0)); // seed random numbers
    vector<DryingSnapShot> batches;
    char choice;

    do { /// main loop for user choices
        cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
        cin >> choice;
        choice = toupper(choice);

        if (choice == 'A') {
            // add new batch
            double radius;
            cout << "    radius: ";
            cin >> radius;

            double sa = get_sphere_sa(radius);
            TimeCode* tc = compute_time_code(sa);
            DryingSnapShot dss{rand(), time(0), tc, tc->GetTimeCodeAsSeconds()};
            batches.push_back(dss);
            cout << "    " << drying_snap_shot_to_string(dss) << endl;
        } else if (choice == 'V') {
            // update and show batches
            vector<DryingSnapShot> remaining;
            for (auto& batch : batches) {
                long long rem = get_time_remaining(batch);
                if (rem <= 0) {
                    delete batch.timeToDry; // free memory
                    cout << "    Batch-" << batch.id << " (takes " << batch.timeToDry->ToString() << " to dry) DONE!" << endl;
                } else {
                    remaining.push_back(batch);
                    cout << "    " << drying_snap_shot_to_string(batch) << endl;
                }
            }
            batches = remaining; // cleanup done batches
        }
    } while (choice != 'Q');

    for (auto& batch : batches) delete batch.timeToDry; // free memory before exit
    return 0;
}