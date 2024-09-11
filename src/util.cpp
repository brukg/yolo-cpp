

#include "yolo/util.hpp"



Configs parseConfigFile(const std::string& configFile) {
    std::cout << "Parsing configuration file: " << configFile << std::endl;
    YAML::Node config = YAML::LoadFile(configFile);
    Configs configs;
    configs.videoPath = config["video_path"].as<std::string>();
    configs.device = config["device"].as<std::string>();
    configs.useOpenVINO = config["use_openvino"].as<bool>();
    configs.useTensorRT = config["use_tensorrt"].as<bool>();
    configs.renderer = config["renderer"].as<std::string>();
    configs.useRenderingThread = config["use_rendering_thread"].as<bool>();
    configs.useInferenceThread = config["use_inference_thread"].as<bool>();
    configs.modelConfig = config["model"]["config"].as<std::string>();
    configs.modelWeights = config["model"]["weights"].as<std::string>();
    configs.classesFile = config["model"]["classes"].as<std::string>();
    configs.colorsFile = config["model"]["colors"].as<std::string>();
    configs.confidenceThreshold = config["model"]["confidence_threshold"].as<float>();
    configs.nmsThreshold = config["model"]["nms_threshold"].as<float>();
    configs.onnxModelPath = config["model"]["onnx_model_path"].as<std::string>();
    configs.openvinoDevice = config["model"]["openvino_device"].as<std::string>();
    configs.openvinoModelXML = config["model"]["openvino_model_xml"].as<std::string>();
    configs.openvinoModelBIN = config["model"]["openvino_model_bin"].as<std::string>();
    return configs;
}
    

std::vector<std::string> loadClassNames(const std::string& filename) {
    std::cout << "Loading class names from file: " << filename << std::endl;
    std::vector<std::string> classNames;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
    classNames.push_back(line);
    }
    return classNames;
}



std::vector<cv::Scalar> loadColors(const std::string& filename) {
    std::cout << "Loading colors from file: " << filename << std::endl;
    std::vector<cv::Scalar> colors;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string item;
    std::vector<int> rgbValues;

    while (std::getline(ss, item, ',')) {
        try {
            rgbValues.push_back(std::stoi(item));
        } catch (const std::invalid_argument&) {
        std::cerr << "Invalid number in color file: " << item << std::endl;
        continue;
        }
    }

    if (rgbValues.size() == 3) {
        colors.emplace_back(cv::Scalar(rgbValues[0], rgbValues[1], rgbValues[2]));
    } else {
        std::cerr << "Error parsing color line: " << line << std::endl;
    }
    }

    std::cout << "Loaded " << colors.size() << " colors." << std::endl;
    return colors;
}