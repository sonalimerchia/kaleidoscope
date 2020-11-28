#include <visualizer/kaleidoscope_app.h>
#include <core/slider.h>

namespace kaleidoscope {

namespace visualizer {

using ci::app::MouseEvent;
using ci::app::KeyEvent;

void KaleidoscopeApp::mouseUp(MouseEvent event) {
  // Add stroke to app, refresh maker
  strokes_.push_back(maker_.GetStroke());
  maker_.clear();
  needs_refresh_ = true;
}

void KaleidoscopeApp::mouseDrag(MouseEvent event) {
  maker_.AddPointToStroke(event.getPos());
}

void KaleidoscopeApp::mouseDown(MouseEvent event) {
  for (size_t button_index = 0; button_index < buttons_.size(); button_index++) {
    if (buttons_.at(button_index).WasPressed(event.getPos())) {
      ButtonPressed(button_index);
      return;
    }
  }
  maker_.StartNewStroke(event.getPos());
}

void KaleidoscopeApp::draw() {
  // Draw stroke in progress unless you need to refresh. In which case, draw all
  if (needs_refresh_) {
    pad_.draw(strokes_);
    needs_refresh_ = false;
  } else {
    pad_.draw(maker_.GetStroke());
  }

  for (const Button &button : buttons_) {
    button.Draw();
  }
}

void KaleidoscopeApp::setup() {
  //TODO:: Set to constants
  setWindowSize(1000, 750);

  // Set Up Pad
  pad_.SetBackground(ci::Color("white"));

  // Set up maker
  maker_.SetBrushSize(3);
  maker_.SetColor(ci::Color("blue"));
  maker_.SetNumSectors(6);
  maker_.SetCenter(getWindowSize()/2);

  buttons_.push_back(Button(glm::vec2(900, 0),
                            glm::vec2(100, 50),
                            "Erase"));
  buttons_.push_back(Slider(glm::vec2(900, 50), glm::vec2(100, 300), "Brush Size"));

  needs_refresh_ = true;
}

void KaleidoscopeApp::keyDown(KeyEvent event) {
  if (event.getCode() == KeyEvent::KEY_BACKSPACE) {
    strokes_.clear();
    maker_.clear();
    needs_refresh_ = true;
  }
}

void KaleidoscopeApp::ButtonPressed(size_t button_index) {
  const std::string &message = buttons_.at(button_index).GetMessage();
  if (message == "Erase" || message == "Draw") {
    maker_.ChangeMode();
    if (message == "Erase") {
      buttons_.at(button_index).SetMessage("Draw");
    } else {
      buttons_.at(button_index).SetMessage("Erase");
    }
  }

  needs_refresh_ = true;
}

}

}