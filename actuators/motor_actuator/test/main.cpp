#include <motor_actuator/motor_actuator.hpp>
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

Sockets::SocketsSPtr motor_sockets_1;
MotorActuator::MotorActuatorSPtr motor_actuator_1;
Json::Value actuator_data;
std::mutex sync_mutex; // for sync of message_received variable

void test_write() {

    while (true) {

        std::unique_lock<std::mutex> lk(cv_m);
        std::cerr << "Waiting... \n";

        cv.wait(lk, [] { return message_received; });
        std::cerr << "...finished waiting \n";

        // motor_actuator_1->writeData(actuator_data);

        sync_mutex.lock();
        message_received = false;
        sync_mutex.unlock();

    }
}

void signals() {

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(3));

        {
            std::lock_guard<std::mutex> lk(cv_m);

            actuator_data["counts"] = actuator_data["counts"].asInt() + 1;

            sync_mutex.lock();
            message_received = true;
            sync_mutex.unlock();

        }
        std::cerr << "Notifying...\n";
        cv.notify_one();
    }
}

int main() {

    motor_sockets_1 = std::make_shared<Sockets>(12);
    // motor_actuator_1 = std::make_shared<MotorActuator>(12, motor_sockets_1);
    // motor_actuator_1 = std::make_shared<MotorActuator>(12,motor_sockets_1);

    // motor_actuator_1->motorCommand(12, "velocity", motor_actuator_1->setPosition(0,0,0,0,0), motor_actuator_1->setVelocity(1,15,10,1,1) );


    actuator_data["counts"] = 0;

    // std::thread write_thread(test_write);
    // std::thread subscribe_thread(signals);

    // write_thread.join();
    // subscribe_thread.join();

    return 0;

}
