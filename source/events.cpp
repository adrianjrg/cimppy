#include <stdexcept>
#include <fmt/core.h>

#include "cimppy/events.hpp"
#include "cimppy/simulation.hpp"

namespace cimppy
{

Event::Event(Simulation& env)
    : env_(env)
{
}

// Event::~Event()
// {
// }
void Event::Trigger(Event triggerEvent, int priority) {
    if (is_triggered_)
        throw std::runtime_error("Event already triggered!");
    this->is_ok_ = triggerEvent.is_ok_;
    // this->
    this->is_triggered_ = true;
    this->env_.schedule(env_.now, *this, priority);
}

void Event::Succeed(/*value??,*/ int priority)
{
    if (is_triggered_)
        throw std::runtime_error("Event already triggered!");
    this->is_ok_ = true;
    // value??
    this->is_triggered_ = true;
    this->env_.schedule(env_.now, *this, priority);
}

void Event::Fail(/*value??,*/ int priority){
    if (is_triggered_)
        throw std::runtime_error("Event already triggered!");
    this->is_ok_ = false;
    // value??
    this->is_triggered_ = true;
    this->env_.schedule(env_.now, *this, priority);
}

void Event::AddCallback(EventCallback_t callback){
    if (is_processed_)
        throw std::runtime_error("Event already processed!");
    callbacks_.push_back(callback);
}

void Event::Process() {
    if (is_processed_)
        throw std::runtime_error("Event already processed!");
    is_processed_ = true;
    
    for (auto &&cb : callbacks_) {
        cb(*this);
    }
    callbacks_.clear();
};

void StopEvent::Process() {
    fmt::print("Stop event processed at {}.\n", env_.now);
}

} // namespace cimppy

