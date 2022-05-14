#pragma once

#include <functional>
#include <vector>


namespace cimppy
{

class Simulation;

/**
 * @brief Base class for all events in cimppy
 * 
 */
class Event
{
protected:
    /// The IsOk flag indicates if the event succeeded or failed. An event
    /// that failed indicates to a waiting process that the action could
    /// not be performed and that the faulting situation must be handled.
    /// Typically, interrupting a process sets the IsOk flag to false.
    bool is_ok_ = false;
    /// An event is alive when it is not triggered and not processed. That
    /// is, when it exists in memory without being scheduled. Typically,
    /// a Process is alive until its last event has been processed and the
    /// process event itself is to be processed.
    bool is_alive_ = false;
    /// An event becomes processed when its callbacks have been executed.
    /// Events may only be processed once and an exception will be thrown
    /// if they are to be processed multiple times.
    bool is_processed_ = false;
    /// An event becomes triggered when it is placed into the event queue.
    /// That is, when its callbacks are going to be executed.
    /// An event that is triggered may later not be failed or retriggered.
    bool is_triggered_ = false;

    Simulation& env_;

    typedef std::function<void(Event)> EventCallback_t;
    std::vector<EventCallback_t> callbacks_;

public:
    Event(Simulation& env);
    // ~Event();

    /// This method schedules the event right now. It takes the IsOk state
    /// and uses the <see cref="Value"/> of the given <paramref name="@event"/>.
    /// Thus if the given event fails, this event will also be triggered as
    /// failing.
    virtual void Trigger(Event triggerEvent, int priority = 0);

    virtual void Succeed(/*value??,*/ int priority = 0);

    virtual void Fail(/*value??,*/ int priority = 0);

    virtual void AddCallback(EventCallback_t callback);

    // virtual void RemoveCallback(EventCallback_t callback){
    //     if (is_processed_)
    //         throw std::runtime_error("Event already processed!");
    //     callbacks_.erase(std::remove_if(callbacks_.begin(),
    //                                     callbacks_.end(),
    //                                     [&](const EventCallback_t cb) -> bool 
    //                                         { return cb == callback; }),
    //                     callbacks_.end());
    // }

    virtual void Process();
};

class StopEvent : public Event
{
public:
    StopEvent(Simulation& env) : Event(env) {};

    virtual void Process() override;
    // {
    //     fmt::print("Stop event processed at {}.\n", env_.now);
    // }
};

} // namespace cimppy
