#ifndef GUIRENDERERCV_HPP
#define GUIRENDERERCV_HPP

#include <thread>
#include <mutex>
#include <condition_variable>

#include "yolo/util.hpp"
#include "yolo/gui/GUIRenderer.hpp"

namespace yolo{

class GUIRendererCV : public GUIRenderer {

public:
    GUIRendererCV();
    void start(Configs config);
    void display();
    bool isStopRequested() const; 
    void renderLoop();
};

#endif // GUIRENDERERCV_HPP

} // namespace yolo