#ifndef RECCHECK
#include <iostream>
#include <vector>
#include <algorithm>
#endif

#include "schedwork.h"

using namespace std;
static const Worker_T INVALID_ID = (unsigned int)-1;

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shiftCount,
    size_t day,
    size_t slot
) {
    size_t n = avail.size();
    size_t k = avail[0].size();

    if (day == n) {
        return true;
    }

    if (slot == dailyNeed) {
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftCount, day + 1, 0);
    }

    for (Worker_T w = 0; w < k; ++w) {
        if (!avail[day][w] || shiftCount[w] >= maxShifts) {
            continue;
        }

        bool alreadyScheduled = false;
        for (size_t s = 0; s < slot; ++s) {
            if (sched[day][s] == w) {
                alreadyScheduled = true;
                break;
            }
        }
        if (alreadyScheduled) {
            continue;
        }

        sched[day][slot] = w;
        shiftCount[w]++;

        if (scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftCount, day, slot + 1)) {
            return true;
        }

        shiftCount[w]--;
        sched[day][slot] = INVALID_ID;
    }

    return false;
}

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
) {
    size_t n = avail.size();
    if (n == 0 || dailyNeed == 0) {
        return false;
    }
    size_t k = avail[0].size();

    sched.assign(n, vector<Worker_T>(dailyNeed, INVALID_ID));
    vector<size_t> shiftCount(k, 0);

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftCount, 0, 0);
}