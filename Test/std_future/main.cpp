/*
#include <iostream>
#include <thread>
#include <future>
#include <vector>

int counter = 0;  // Shared resource

// Function that increments a shared counter
void increment_counter(int id) {
    for (int i = 0; i < 100000; ++i) {
        ++counter;  // Increment the shared counter
    }
    std::cout << "Thread " << id << " finished." << std::endl;
}

int main() {
    const int num_threads = 10;
    std::vector<std::future<void>> futures;

    // Launch multiple async tasks that increment the counter
    for (int i = 0; i < num_threads; ++i) {
        // Start asynchronous tasks
        futures.push_back(std::async(std::launch::async, increment_counter, i));
    }

    // Wait for all threads to finish
    for (auto& f : futures) {
        f.get();  // Get the result (in this case, void)
    }

    // Print the final value of the counter
    std::cout << "Final counter value: " << counter << std::endl;

    return 0;
}
*/

#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <mutex>

int counter = 0;  // Shared resource
std::mutex mtx;   // Mutex to protect the shared resource

// Function that increments a shared counter
void increment_counter(int id) {
    for (int i = 0; i < 100000; ++i) {
        std::lock_guard<std::mutex> lock(mtx);  // Lock the mutex before accessing the counter
        ++counter;  // Increment the shared counter
    }
    std::cout << "Thread " << id << " finished." << std::endl;
}

int main() {
    const int num_threads = 10;
    std::vector<std::future<void>> futures;

    // Launch multiple async tasks that increment the counter
    for (int i = 0; i < num_threads; ++i) {
        futures.push_back(std::async(std::launch::async, increment_counter, i));
    }

    // Wait for all threads to finish
    for (auto& f : futures) {
        f.get();  // Wait for the result
    }

    // Print the final value of the counter
    std::cout << "Final counter value: " << counter << std::endl;

    return 0;
}
