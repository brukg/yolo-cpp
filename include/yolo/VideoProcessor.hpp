#include <thread>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

#include "yolo/gui/GUIRenderer.hpp"
#include "yolo/detector/OpenCVDetector.hpp"  
#ifdef WITH_OPENVINO
#include "yolo/detector/OpenVINODetector.hpp"
#else
#include "yolo/detector/TensorRTDetector.hpp"
#endif
#include "yolo/util.hpp"


#include "yolo/gui/GUIRenderer.hpp"
#include "yolo/gui/GUIRendererGL.hpp"
#include "yolo/gui/GUIRendererCV.hpp"

namespace yolo{

class VideoProcessor {
public: 
    VideoProcessor(Configs& config);

    void processVideo();


private:
    std::unique_ptr<BaseDetector> detector;
    OpenCVDetector yoloDetector;
    std::string modelConfig, modelWeights;
    std::string classesFile, colorsFile;
    Configs& config;
    std::unique_ptr<GUIRenderer> guiRenderer;

};

} // namespace yolo