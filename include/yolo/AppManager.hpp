#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

#include "yolo/VideoProcessor.hpp"
#include "yolo/util.hpp"

namespace yolo{

class AppManager {
public:
    AppManager(const std::string& configFile); 
    void run();

private:
    Configs config;
    std::unique_ptr<VideoProcessor> videoProcessor;  
};

} // namespace yolo