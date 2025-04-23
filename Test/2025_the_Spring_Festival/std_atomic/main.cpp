#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <atomic>

std::atomic<int> counter(0);  // Shared resource, initialized as atomic

// Function that increments the atomic counter
void increment_counter(int id) {
    for (int i = 0; i < 100000; ++i) {
        counter.fetch_add(1, std::memory_order_relaxed);  // Atomic increment
    }
    std::cout << "Thread " << id << " finished." << std::endl;
}

int main() {
    const int num_threads = 10;
    std::vector<std::future<void>> futures;

    // Launch multiple async tasks that increment the atomic counter
    for (int i = 0; i < num_threads; ++i) {
        futures.push_back(std::async(std::launch::async, increment_counter, i));
    }

    // Wait for all threads to finish
    for (auto& f : futures) {
        f.get();  // Wait for the result
    }

    // Print the final value of the atomic counter
    std::cout << "Final counter value: " << counter.load() << std::endl;

    return 0;
}

