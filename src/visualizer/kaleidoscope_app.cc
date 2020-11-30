#include <visualizer/kaleidoscope_app.h>
#include <core/constants.h>

namespace kaleidoscope {

namespace visualizer {

using glm::ivec2;
using ci::app::MouseEvent;
using ci::app::KeyEvent;
using std::experimental::filesystem::path;

void KaleidoscopeApp::mouseUp(MouseEvent event) {
  // React to mouse up, refresh the pad
  pad_.MouseUp();
  needs_refresh_ = true;
}

void KaleidoscopeApp::mouseDrag(MouseEvent event) {
  // Respond to mouse activity in the toolbar
  if (toolbar_.ContainsPoint(event.getPos())) {
    CommandType command = toolbar_.MouseDragged(event.getPos());
    ManageCommand(command);

    // React to mouse activity on the sketchpad
  } else {
    pad_.MouseDragged(event.getPos());
  }
}

void KaleidoscopeApp::mouseDown(MouseEvent event) {
  // Respond to mouse activity in the toolbar
  if (toolbar_.ContainsPoint(event.getPos())) {
    CommandType command = toolbar_.MouseClicked(event.getPos());
    ManageCommand(command);

    // React to mouse activity on the sketchpad
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

  // Draw the toolbar
  toolbar_.Draw();
}

void KaleidoscopeApp::setup() {
  setWindowSize(kWindowWidth, kWindowHeight);

  // Set Up Pad
  pad_.SetBackground(kDefaultBackgroundColor);
  needs_refresh_ = true;
}

void KaleidoscopeApp::keyDown(KeyEvent event) {
  // Clear if backspace is pressed
  if (event.getCode() == KeyEvent::KEY_BACKSPACE) {
    pad_.Clear();
    needs_refresh_ = true;

    // Change number of sectors if arrow keys are used
  } else if (event.getCode() == KeyEvent::KEY_UP || event.getCode() == KeyEvent::KEY_DOWN) {
    pad_.ChangeNumSectors(event.getCode() == KeyEvent::KEY_UP ? 1 : -1);
    needs_refresh_ = true;
  }
}

void KaleidoscopeApp::ManageCommand(const CommandType &command) {
  switch(command) {
    // Change mode of drawing from eraser to drawing or vice versa
    case CommandType::DrawMode:
      pad_.ChangeDrawMode();
      return;

    // Change brush size
    case CommandType::BrushSize:
      pad_.SetBrushSize(toolbar_.GetBrushSize());
      return;

    // Save and quit
    case CommandType::Save:
      path path = getSaveFilePath(kImagesFolderPath);
      if (!path.has_extension()) {
        path.replace_extension(kDefaultImageExtension);
      }
      ci::writeImage(path, copyWindowSurface(ci::Area(ivec2(0, 0),
                                                      ivec2(kWindowHeight, kWindowHeight))));
      quit();
  }
}

} // namespace visualizer

} // namespace kaleidoscope