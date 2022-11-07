#ifndef ACTUATOR_H_
#define ACTUATOR_H_

#include <iostream>
#include <memory>
#include <json_reader/json_read.h>

class Actuator {

public:

    typedef std::shared_ptr<Actuator> ActuatorSPtr;
    typedef std::unique_ptr<Actuator> ActuatorUPtr;

    Actuator();

    ~Actuator();

    virtual void writeData(Json::Value &actuator_data) = 0;


};

#endif //ACTUATOR_H_