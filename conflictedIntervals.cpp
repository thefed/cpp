// b*, find conflicted time windows / intervals
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
using namespace std;

struct Event {
    int id; // event id
    string startDate, endDate;
    Event(int i, string s, string e) : id(i), startDate(s), endDate(e) {}
};

struct ConflictedTimeWindow {
    string startDate, endDate;
    set<int> conflictedEventIds;
    ConflictedTimeWindow(string s, string e, set<int>& cE) : startDate(s), endDate(e), conflictedEventIds(cE) {}
};

enum {START=0, END};
struct EventPoint {
    string date;
    int id;
    int type; // start date : 0, end date: 1
    EventPoint(string d, int i, int t) : date(d), id(i), type(t) {}
};

class Calendar {
private:
    vector<EventPoint> m_eventPoints;
public:
    void schedule(const Event& event) {
        m_eventPoints.push_back(EventPoint(event.startDate, event.id, 0));
        m_eventPoints.push_back(EventPoint(event.endDate, event.id, 1));
    }

    vector<ConflictedTimeWindow> findConflictedTimeWindow() {
        // sort all event points by date
        auto cmpDate = [] (const EventPoint
                & e1, const EventPoint& e2) {
            return e1.date == e2.date ? e1.id < e2.id : e1.date < e2.date;
        };

        sort(m_eventPoints.begin(), m_eventPoints.end(), cmpDate);

        vector<ConflictedTimeWindow> res;   //result windows
        // add self event id
        set<int> conflictedIds = {m_eventPoints[0].id};
        string startDate = m_eventPoints[0].date;

        for (int i = 1; i < m_eventPoints.size(); i++) {
            if (m_eventPoints[i].type == START) {
                conflictedIds.insert(m_eventPoints[i].id);
                startDate = m_eventPoints[i].date;
                if (conflictedIds.size() > 1 && startDate != m_eventPoints[i + 1].date) {
                    ConflictedTimeWindow win(startDate, m_eventPoints[i + 1].date, conflictedIds);
                    res.push_back(win); 

                    startDate = m_eventPoints[i + 1].date;
                }
            }
            else {
                if (conflictedIds.size() > 1 && startDate != m_eventPoints[i].date) {
                    ConflictedTimeWindow win(startDate, m_eventPoints[i].date, conflictedIds);
                    res.push_back(win);
                    startDate = m_eventPoints[i].date;
                }

                // rm event id of current end date event    
                conflictedIds.erase(m_eventPoints[i].id);
            }
        }
        return res;
    }
};

void print(ConflictedTimeWindow& window) {
    printf("ConflictedTimeWindow{ startDate=%s, endDate=%s, }", window.startDate.c_str(), window.endDate.c_str());
    for (auto id : window.conflictedEventIds) {
        printf(" %d", id);
    }
    printf("\n");
}

void print(vector<ConflictedTimeWindow>& windows) {
    for (auto win: windows) print(win);
    printf("\n");
}

struct Interval {
    //int id;
    int start, end;
    Interval() : start(0), end() {}
    Interval(int s, int e) : start(s), end(e) {}
};

void print(vector<Interval>& v) {
    for (Interval i : v) {
        printf("[%d, %d] ", i.start, i.end);
    }
    printf("\n");
}

vector<vector<Interval>> findConflictIntervals(vector<Interval>& Intervals) {
    vector<vector<Interval>> res;
    return res;
}

void test_sortInterval() {
    vector<Interval> intervals = {{1,5},{3,7},{2,6},{10,15},{5,6},{4,100}};

    // sort intervals by start time, if equal, cmp end time
    auto compi = [](const Interval &a, const Interval &b) { 
        return a.start == b.start ? a.end < b.end : a.start < b.start; 
    };
    sort(intervals.begin(), intervals.end(), compi);
    print(intervals);    
}

int main() {
    // test_sortInterval();

    Calendar calendar;

    calendar.schedule(Event(1, "2014-01-01 10:00", "2014-01-01 11:00"));
    calendar.schedule(Event(2, "2014-01-01 11:00", "2014-01-01 12:00"));
    calendar.schedule(Event(3, "2014-01-01 12:00", "2014-01-01 13:00"));

    calendar.schedule(Event(4, "2014-01-02 10:00", "2014-01-02 11:00"));
    calendar.schedule(Event(5, "2014-01-02 09:30", "2014-01-02 11:30"));
    calendar.schedule(Event(6, "2014-01-02 09:45", "2014-01-02 11:30"));
    calendar.schedule(Event(7, "2014-01-02 08:30", "2014-01-02 12:30"));
    calendar.schedule(Event(8, "2014-01-02 10:20", "2014-01-02 10:40"));

    calendar.schedule(Event(9, "2014-01-03 10:00", "2014-01-03 11:00"));
    calendar.schedule(Event(10, "2014-01-03 09:30", "2014-01-03 10:30"));
    calendar.schedule(Event(11, "2014-01-03 09:45", "2014-01-03 10:45"));
    calendar.schedule(Event(12, "2014-01-03 10:00", "2014-01-03 10:35"));
    calendar.schedule(Event(13, "2014-01-03 10:00", "2014-01-03 11:00"));

    vector<ConflictedTimeWindow> windows = calendar.findConflictedTimeWindow();
    print(windows); 
    return 0;
}
