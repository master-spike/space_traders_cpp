#include "space_traders_cpp/ratelimiter.h"

RateLimiter::RateLimiter(int millis) : clock()
                                     , last_time(clock.now())
                                     , interval(std::chrono::milliseconds(millis))
                                     , is_enabled(true) {}

RateLimiter::RateLimiter() : clock()
                           , last_time(clock.now())
                           , interval(std::chrono::milliseconds(0))
                           , is_enabled(false) {}

bool RateLimiter::status() {
    return is_enabled;
}

void RateLimiter::enable()  {
    if (is_enabled) return;
    last_time = clock.now();
    is_enabled = true;
}
void RateLimiter::disable() { is_enabled = false; }

void RateLimiter::rl_wait() {
    if (!is_enabled) return;
    // lock free using compare-and-swap
    while(true) {
        std::chrono::steady_clock::time_point ct = clock.now();
        std::chrono::steady_clock::time_point lt = last_time.load();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(ct - lt) < interval) {
            std::this_thread::sleep_for(lt + interval - ct);
            continue;
        }
        ct = clock.now();
        if (last_time.compare_exchange_weak(lt, ct)) return;
    }
}