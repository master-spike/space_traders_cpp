#pragma once

#include <chrono>
#include <thread>
#include <atomic>

class RateLimiter {
    std::chrono::steady_clock clock;
    std::atomic<std::chrono::steady_clock::time_point> last_time;
    std::chrono::milliseconds interval;
    bool is_enabled;

public:
    explicit RateLimiter();
    explicit RateLimiter(int millis);
    ~RateLimiter() = default;
    explicit RateLimiter(RateLimiter& in_ratelimiter) = delete;
    explicit RateLimiter(RateLimiter&& in_ratelimiter) = delete;
    RateLimiter& operator=(RateLimiter& other) = delete;
    // rule of 5, each ratelimiter instance should be completely independent of any others;
    void rl_wait();
    void enable();
    void disable();
    bool status();

};