#include <iostream>
#include <vector>
#include <chrono>
#include <random>

// ---------------- AoS ----------------
struct Sample {
    double voltage;
    double current;
    double time;
};

// ---------------- SoA ----------------
struct Samples {
    std::vector<double> voltage;
    std::vector<double> current;
    std::vector<double> time;
};

int main() {
    const size_t N = 5'000'000; // 5 million samples

    // Random data generator
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(0.0, 5.0);
    double myVoltage = 1500.0;  // example: 3.3V
    // ---------------- Initialize AoS ----------------
    std::vector<Sample> aos;
    aos.reserve(N);

    for (size_t i = 0; i < N; ++i) {
    aos.push_back({
    myVoltage,
    dist(rng),
    static_cast<double>(i)
    });

    }

    // ---------------- Initialize SoA ----------------
    Samples soa;
    soa.voltage.reserve(N);
    soa.current.reserve(N);
    soa.time.reserve(N);
    


    for (size_t i = 0; i < N; ++i) {
    soa.voltage.push_back(myVoltage);

    }

    // ---------------- Measure AoS ----------------
    auto start_aos = std::chrono::high_resolution_clock::now();

    double sum_aos = 0.0;
    for (const auto& s : aos) {
        sum_aos += s.voltage;
    }
    double avg_aos = sum_aos / N;

    auto end_aos = std::chrono::high_resolution_clock::now();
    auto time_aos = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_aos - start_aos
    ).count();

    // ---------------- Measure SoA ----------------
    auto start_soa = std::chrono::high_resolution_clock::now();

    double sum_soa = 0.0;
    for (double v : soa.voltage) {
        sum_soa += v;
    }
    double avg_soa = sum_soa / N;

    auto end_soa = std::chrono::high_resolution_clock::now();
    auto time_soa = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_soa - start_soa
    ).count();

    // ---------------- Results ----------------
    std::cout << "AoS Average Voltage: " << avg_aos << "\n";
    std::cout << "AoS Time: " << time_aos << " ms\n\n";

    std::cout << "SoA Average Voltage: " << avg_soa << "\n";
    std::cout << "SoA Time: " << time_soa << " ms\n";

    return 0;
}
