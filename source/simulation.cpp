#include <stdexcept>
#include <iostream>

#include "cimppy/simulation.hpp"
#include "cimppy/events.hpp"


namespace cimppy
{

Simulation::Simulation(/* args */)
{
}

Simulation::~Simulation()
{
}

void Simulation::schedule(int time, Event& event, int priority){
    this->eventQueue_.push(
        {
            .time = time,
            .priority = priority,
            .event_id = this->event_nr_++,
            .event = &event,
        }
    );
}

StopEvent Simulation::run(int until){
    if (until < this->now_)
        throw std::runtime_error("Simulation must run until a point in the future.");
    
    StopEvent stop_event( *this );
    schedule(until, stop_event, 1);
    return run(stop_event);
}

StopEvent Simulation::run(StopEvent& stop_event){
    try
    {
        while (this->eventQueue_.size() != 0)
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

void Simulation::step(){
    // Grab event
    auto sched_event = eventQueue_.top();
    eventQueue_.pop();

    // Update time
    now_ = sched_event.time;

    // Process event
    sched_event.event->Process();
}

} // namespace cimppy

