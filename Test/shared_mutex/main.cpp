#include <iostream>
#include <thread>
#include <shared_mutex>
#include <vector>

std::shared_mutex rw_mutex;  // Reader-Writer lock
std::vector<int> shared_data = {1, 2, 3};

void read_data(int id) {
    std::shared_lock<std::shared_mutex> lock(rw_mutex);  // Shared lock for reading
    std::cout << "Thread " << id << " is reading data: ";
    for (int val : shared_data) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

void write_data(int id, int new_value) {
    std::unique_lock<std::shared_mutex> lock(rw_mutex);  // Unique lock for writing
    shared_data.push_back(new_value);
    std::cout << "Thread " << id << " is writing data: " << new_value << std::endl;
}

int main() {
    std::thread t1(read_data, 1);
    std::thread t2(write_data, 2, 4);
    std::thread t3(read_data, 3);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}

