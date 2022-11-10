#ifndef BARCODE_SENSOR_H_
#define BARCODE_SENSOR_H_

#include <iostream>
#include <thread>
#include <mutex>

#include <sensor/sensor.hpp>
#include <json_reader/json_read.h>
#include <sockets.hpp>
#include <gls_barcode.hpp>
#include <queue>

#include "../../socketcan/printd.c"
#include "../../socketcan/socketcan.c"
#include "../../canopen/canopen.h"
#include "../../canopen/NMT.c"
#include "../../canopen/PDO.c"
#include "../../canopen/SDO.c"

class BarcodeSensor : public Sensor {

public:

    typedef std::shared_ptr<BarcodeSensor> BarcodeSensorSPtr;
    typedef std::unique_ptr<BarcodeSensor> BarcodeSensorUPtr;

    BarcodeSensor(int barcode_id, int barcode_base_id);

    ~BarcodeSensor();

    void getData(Json::Value &sensor_data);

private:
    int barcode_id_;
    int read_err_;
    std::thread update_data_thread_;
    std::thread read_barcode_data_thread_;

    void updateData();

    Json::Value sensor_data_;
    std::mutex read_mutex_;

    void init_json();

    GlsBarcode::GlsBarcodeSPtr gls_barcode_ ;

    GlsBarcode::feedback_s feedback_s_b_;

    void readData();
    std::condition_variable cv;
    bool message_received;
    void readBarcodeData();

    std::queue<GlsBarcode::feedback_s> q_barcode_data_;
    GlsBarcode::feedback_s encoder_barcode_q_element_; 

    // std::shared_ptr<spdlog::logger> logger_;


};

#endif // BARCODE_SENSOR_H_