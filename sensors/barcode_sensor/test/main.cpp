#include <barcode_sensor/barcode_sensor.hpp>
#include <thread>
#include <gls_barcode.hpp>


using namespace std;

BarcodeSensor::BarcodeSensorSPtr barcode_sensor_1;

// void read_data() {

//     while (true) {
//         std::this_thread::sleep_for(std::chrono::milliseconds(3000));
//         Json::Value data;
//         barcode_sensor_1->getData(data);
//         std::cout << "x: " << data["x"].asInt() << std::endl;
//         std::cout << "y: " << data["y"].asInt() << std::endl;
//     }

// }
Json::Value barcode_data_1;

int main() {

    barcode_sensor_1 = std::make_shared<BarcodeSensor>(12,1152);

    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        barcode_sensor_1->getData(barcode_data_1); 
        std::cout << "test: x: " << barcode_data_1["x"].asDouble() << std::endl;
        std::cout << "test: y: " << barcode_data_1["y"].asDouble() << std::endl;
        std::cout << "test: ang: " << barcode_data_1["ang"].asDouble() << std::endl;
        std::cout << "test: sensor_time: " << barcode_data_1["sensor_time"].asInt64() << std::endl;
        std::cout << "test: decode_time: " << barcode_data_1["decode_time"].asInt64() << std::endl;
        std::cout << "test:  tag_x: " << barcode_data_1["tag_x"].asInt64() << std::endl;
        std::cout << "test:  tag_y: " << barcode_data_1["tag_y"].asInt64() << std::endl;


    }
    // std::thread read_thread(read_data);
    // read_thread.join();


    return 0;

}
