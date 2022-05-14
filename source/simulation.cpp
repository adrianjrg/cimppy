#include <stdexcept>
#include <iostream>

#include "cimppy/simulation.hpp"
#include "cimppy/events.hpp"


namespace cimppy
{

void simulation::schedule(int time, event& event, int priority){
    this->event_queue_.push(
        {
            .time = time,
            .priority = priority,
            .event_id = this->event_nr_++,
            .event_ptr = &event,
        }
    );
}

stop_event simulation::run(int until){
    if (until < this->now_) {
        throw std::runtime_error("Simulation must run until a point in the future.");
    }
    
    stop_event stop_event( *this );
    schedule(until, stop_event, 1);
    return run(stop_event);
}

stop_event simulation::run(stop_event& stop_event){
    try
    {
        while (!this->event_queue_.empty())
        {
            step();
        }            
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return stop_event;
}

void simulation::step(){
    // Grab event
    auto sched_event = event_queue_.top();
    event_queue_.pop();

    // Update time
    now_ = sched_event.time;

    // Process event
    sched_event.event_ptr->process();
}

} // namespace cimppy

