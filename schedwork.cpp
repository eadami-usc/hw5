#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;

// Add prototypes for any helper functions here
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<int>& workerShiftCount,
    unsigned int day,
    unsigned int shift
);

// Add your implementation of schedule() and other helper functions here
bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
) {
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    
    // Add your code below
    for (unsigned int i = 0; i < avail.size(); i++) {
        std::vector<Worker_T> day;
        for (unsigned int j = 0; j < dailyNeed; j++) {
            day.push_back(INVALID_ID);
        }
        sched.push_back(day);
    }

    vector<size_t> workerShiftCount(avail[0].size(), 0);

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, workerShiftCount, 0, 0);
}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& workerShiftCount,
    unsigned int day,
    unsigned int shift
) {
    // base case
    if (day == avail.size()) {
        return true;
    }

    // move to next day
    if (shift == dailyNeed) {
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, workerShiftCount, day + 1, 0);
    }

    if (sched[day][shift] == INVALID_ID) {
        for (Worker_T worker = 0; worker < avail[day].size(); worker++) {
            // check if worker is valid
            if (avail[day][worker] == 1 &&
                workerShiftCount[worker] < maxShifts &&
                find(sched[day].begin(), sched[day].end(), worker) == sched[day].end()
            ) {
                sched[day][shift] = worker;
                workerShiftCount[worker]++;
                
                if (scheduleHelper(avail, dailyNeed, maxShifts, sched, workerShiftCount, day, shift + 1)) {
                    return true;
                }
                
                // backtrack
                workerShiftCount[worker]--;
                sched[day][shift] = INVALID_ID;
            }
        }
    }
    return false;
}