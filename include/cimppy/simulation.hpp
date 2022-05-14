#pragma once

#include <queue>
#include <vector>

namespace cimppy
{

class event;
class stop_event;

struct scheduled_event
{
    int time;
    int priority;
    int event_id;
    event* event_ptr;
};
class event_comparisson {
public:
    bool operator() (scheduled_event one, scheduled_event other) {
        if (one.time != other.time) {
            return one.time < other.time;
        }
        if (one.priority != other.priority) {
            return one.priority < other.priority;
        }
        return one.event_id < other.event_id;
    }
};

class simulation
{
public:
    simulation(/* args */) = default;

    [[nodiscard]] int now() const { return now_; }

    void schedule(int time, event& event, int priority = 0);

    stop_event run(int until);

    stop_event run(stop_event& stop_event);

    void step();

private:
    // TODO: convert to chrono instead of int or template?
    int now_ = 0;
    int event_nr_ = 0;

    std::priority_queue<scheduled_event, std::vector<scheduled_event>, event_comparisson> event_queue_;
};

} // namespace cimppy
