#ifndef ENCODER_SENSOR_DATA_HPP_
#define ENCODER_SENSOR_DATA_HPP_

#include <iostream>
#include <memory>

class EncoderSensorData{

    private:
   
    
    public:
    EncoderSensorData();
    ~EncoderSensorData();

    typedef std::shared_ptr<EncoderSensorData> EncoderSensorDataSPtr;
    typedef std::unique_ptr<EncoderSensorData> EncoderSensorDataUPtr;
    
    uint16_t status_m; 
    float battery_vol_m;
    uint32_t pos_m; // position loop params
    double vel_m;
    uint32_t manufacturer_reg_m;
    uint32_t latched_fault_m;
    
};

#endif
