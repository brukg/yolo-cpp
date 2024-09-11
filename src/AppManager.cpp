#include "yolo/AppManager.hpp"

namespace yolo{

AppManager::AppManager(const std::string& configFile)
{ 

    config =  parseConfigFile(configFile);
    videoProcessor = std::make_unique<VideoProcessor>(config);

}

void AppManager::run() {
    videoProcessor->processVideo();
}

} // namespace yolo