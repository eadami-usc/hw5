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
    unsigned int day,
    unsigned int shift
);

bool isValid(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    unsigned int day,
    Worker_T worker
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

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, 0, 0);
}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    unsigned int day,
    unsigned int shift
) {
    // base case
    if (day == avail.size()) {
        return true;
    }

    // move to next day
    if (shift == dailyNeed) {
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, day + 1, 0);
    }

    if (sched[day][shift] == INVALID_ID) {
        for (Worker_T worker = 0; worker < avail[day].size(); worker++) {
            sched[day][shift] = worker;
            if (isValid(avail, dailyNeed, maxShifts, sched, day, worker)) {
                if (scheduleHelper(avail, dailyNeed, maxShifts, sched, day, shift + 1)) {
                    return true;
                }
            }
        }
        // backtrack
        sched[day][shift] = INVALID_ID;
    } else {
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, day, shift + 1);
    }

    return false;
}

bool isValid(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    unsigned int day,
    Worker_T worker
) {
    if (avail[day][worker] == 0) {
        return false;
    }

    size_t shiftCount = 0;

    for (unsigned int i = 0; i < sched.size(); i++) {
        size_t dailyShiftCount = 0;
        for (unsigned int j = 0; j < dailyNeed; j++) {
            if (sched[i][j] == worker) {
                shiftCount++;
                dailyShiftCount++;
            }
        }
        if (dailyShiftCount > 1) {
            return false;
        }
    }
    
    return shiftCount <= maxShifts;
}