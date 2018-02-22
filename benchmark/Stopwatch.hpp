#ifndef DATELL_STOPWATCH_H
#define DATELL_STOPWATCH_H

#include <chrono>

class Stopwatch {
public:

    Stopwatch() = default;

    // Let's just forget about this kind of strangeness
    Stopwatch(const Stopwatch&) = delete; 
    Stopwatch& operator=(const Stopwatch&) = delete; 

    void start() {
        starting_time = std::chrono::steady_clock::now();
    }

    void stop() {
        stopping_time = std::chrono::steady_clock::now();
    }

    template<typename T>
    T elapsed() {
        return std::chrono::duration_cast<T>(stopping_time-starting_time);
    }

private:
    // Today I've learned, I should use steady_clock instead of system_clock to 
    // measure time (because std::chrono::system_clock might be readjusted by the OS)
    std::chrono::time_point<std::chrono::steady_clock> starting_time;
    std::chrono::time_point<std::chrono::steady_clock> stopping_time;
};

#endif /* DATELL_STOPWATCH_H */