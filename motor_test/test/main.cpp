#include <motor_test/motor_test.hpp>
#include <sockets.hpp>
#include <thread>
#include <condition_variable>
#include <chrono>

using namespace std;

std::condition_variable cv;

// This mutex is used for three purposes:
// 1) to synchronize accesses to i
// 2) to synchronize accesses to std::cerr
// 3) for the condition variable cv
std::mutex cv_m;

bool message_received = false;

MotorTest::MotorTestSPtr motor_test;

Json::Value actuator_data;
std::mutex sync_mutex; // for sync of message_received variable


int main() {

    // motor_test = std::make_shared<MotorTest>();
    // motor_actuator_1 = std::make_shared<MotorActuator>(12, motor_sockets_1);
    

    

    return 0;

}
