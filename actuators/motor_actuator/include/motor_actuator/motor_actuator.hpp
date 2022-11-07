#ifndef MOTOR_ACTUATOR_H_
#define MOTOR_ACTUATOR_H_

#include <iostream>
#include <thread>
#include <mutex>
#include <json_reader/json_read.h>
#include <actuator/actuator.hpp>

class MotorActuator : public Actuator {

public:

    typedef std::shared_ptr<MotorActuator> MotorActuatorSPtr;
    typedef std::unique_ptr<MotorActuator> MotorActuatorUPtr;

    MotorActuator();

    ~MotorActuator();

    void writeData(Json::Value &actuator_data) override;

private:

    Json::Value actuator_data_;

    void init_json();

};

#endif // MOTOR_ACTUATOR_H_