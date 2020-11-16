#include <visualizer/kaleidoscope_app.h>

namespace kaleidoscope {

void KaleidoscopeApp::mouseUp(ci::app::MouseEvent event) {
  strokes_.push_back(maker_.GetStroke());
  maker_.StartNewStroke(event.getPos());
  needs_refresh_ = true;
}

void KaleidoscopeApp::mouseDrag(ci::app::MouseEvent event) {
  maker_.AddPoint(event.getPos());
}

void KaleidoscopeApp::mouseDown(ci::app::MouseEvent event) {
  maker_.StartNewStroke(event.getPos());
}

void KaleidoscopeApp::draw() {
  if(needs_refresh_) {
    pad_.clear();
    pad_.draw(strokes_);
    needs_refresh_ = false;
  }
  pad_.draw(maker_.GetStroke());
}

void KaleidoscopeApp::setup() {
  setWindowSize(1000, 750);

  pad_.SetCenter(glm::vec2(500, 375));
  pad_.SetNumSectors(6);
  pad_.SetBackground(ci::Color("white"));

  maker_.SetBrushSize(5);
  maker_.SetColor(ci::Color("red"));
  maker_.SetNumSectors(6);
  maker_.SetCenter(glm::vec2(500, 375));

  needs_refresh_ = true;
}

}