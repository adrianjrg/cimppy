#pragma once

#include <queue>
#include <vector>

namespace cimppy
{

class Event;
class StopEvent;

struct scheduled_event
{
    int time;
    int priority;
    int event_id;
    Event* event;
};
class EventComparisson {
public:
    bool operator() (scheduled_event a, scheduled_event b){
        if (a.time != b.time)
            return a.time < b.time;
        else if (a.priority != b.priority)
            return a.priority < b.priority;
        else
            return a.event_id < b.event_id;
    }
};

class Simulation
{
private:
    // TODO: convert to chrono instead of int or template?
    int now_ = 0;
    int event_nr_ = 0;

    std::priority_queue<scheduled_event, std::vector<scheduled_event>, EventComparisson> eventQueue_;
public:
    Simulation(/* args */);
    ~Simulation();
    
    // "Property"
    const int& now = now_; 

    void schedule(int time, Event& event, int priority = 0);

    StopEvent run(int until);

    StopEvent run(StopEvent& stop_event);

    void step();
};

} // namespace cimppy
