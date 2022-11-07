#ifndef ENCODER_SENSOR_DATA_HPP_
#define ENCODER_SENSOR_DATA_HPP_

#include <iostream>

class EncoderSensorData{

    private:
   
    
    public:
    EncoderSensorData();
    ~EncoderSensorData();

    typedef std::shared_ptr<EncoderSensorData> EncoderSensorDataSPtr;
    typedef std::unique_ptr<EncoderSensorData> EncoderSensorDataUPtr;
    
};

#endif
