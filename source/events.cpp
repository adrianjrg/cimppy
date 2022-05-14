#include <stdexcept>
#include <fmt/core.h>

#include "cimppy/events.hpp"
#include "cimppy/simulation.hpp"

namespace cimppy
{

event::event(simulation& env)
    : env_(env)
{
}

void event::trigger(const event& trigger_event, int priority) {
    if (is_triggered_) {
        throw std::runtime_error("Event already triggered!");
    }
    this->is_ok_ = trigger_event.is_ok_;
    // this->
    this->is_triggered_ = true;
    this->env_.schedule(env_.now(), *this, priority);
}

void event::succeed(/*value??,*/ int priority)
{
    if (is_triggered_) {
        throw std::runtime_error("Event already triggered!");
    }
    this->is_ok_ = true;
    // value??
    this->is_triggered_ = true;
    this->env_.schedule(env_.now(), *this, priority);
}

void event::fail(/*value??,*/ int priority){
    if (is_triggered_) {
        throw std::runtime_error("Event already triggered!");
    }
    this->is_ok_ = false;
    // value??
    this->is_triggered_ = true;
    this->env_.schedule(env_.now(), *this, priority);
}

void event::add_callback(const event_callback_t& callback){
    if (is_processed_) {
        throw std::runtime_error("Event already processed!");
    }
    callbacks_.push_back(callback);
}

void event::process() {
    if (is_processed_) {
        throw std::runtime_error("Event already processed!");
    }
    is_processed_ = true;
    
    for (auto &&callback : callbacks_) {
        callback(*this);
    }
    callbacks_.clear();
};

void stop_event::process() {
    fmt::print("Stop event processed at {}.\n", env_.now());
}

} // namespace cimppy

