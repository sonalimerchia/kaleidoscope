#include <visualizer/kaleidoscope_app.h>
#include <core/slider.h>
#include <fstream>

namespace kaleidoscope {

namespace visualizer {

using ci::app::MouseEvent;
using ci::app::KeyEvent;

size_t KaleidoscopeApp::kWindowWidth = 1000;
size_t KaleidoscopeApp::kWindowHeight = 750;


void KaleidoscopeApp::mouseUp(MouseEvent event) {
  // Add stroke to app, refresh maker
  pad_.MouseUp();
  needs_refresh_ = true;
}

void KaleidoscopeApp::mouseDrag(MouseEvent event) {
  if (tools_.ContainsPoint(event.getPos())) {
    CommandType command = tools_.MouseDragged(event.getPos());
    ManageCommand(command);
  } else {
    pad_.MouseDragged(event.getPos());
  }
}

void KaleidoscopeApp::mouseDown(MouseEvent event) {
  if (tools_.ContainsPoint(event.getPos())) {
    CommandType command = tools_.MouseClicked(event.getPos());
    ManageCommand(command);
    needs_refresh_ = true;
  } else {
    pad_.MouseDown(event.getPos());
  }
}

void KaleidoscopeApp::draw() {
  // Draw stroke in progress unless you need to refresh. In which case, draw all
  if (needs_refresh_) {
    pad_.ClearAndDraw();
    needs_refresh_ = false;
  } else {
    pad_.DrawCurrentStroke();
  }

  tools_.Draw();
}

void KaleidoscopeApp::setup() {
  setWindowSize(kWindowWidth, kWindowHeight);

  // Set Up Pad
  pad_.SetBackground(ci::Color("white"));
  needs_refresh_ = true;
}

void KaleidoscopeApp::keyDown(KeyEvent event) {
  if (event.getCode() == KeyEvent::KEY_BACKSPACE) {
    pad_.Clear();
    needs_refresh_ = true;
  }
}

void KaleidoscopeApp::ManageCommand(const CommandType &command) {
  switch(command) {
    case CommandType::DrawMode:
      pad_.ChangeDrawMode();
      return;
    case CommandType::BrushSize:
      pad_.SetBrushSize(tools_.GetBrushSize());
      return;
    case CommandType::Save:
      std::experimental::filesystem::path path = getSaveFilePath("C:\\Users\\sonal\\Desktop\\CLion\\cinder\\final-project-sonalimerchia\\images", {".png", ".jpg"});
      ci::writeImage(path, copyWindowSurface(ci::Area(glm::ivec2(0, 0), glm::ivec2(kWindowHeight, kWindowHeight))));
      return;
  }
}

}

}