#include <visualizer/kaleidoscope_app.h>

namespace kaleidoscope {

namespace visualizer {

using glm::ivec2;

using ci::Area;
using ci::app::MouseEvent;
using ci::app::KeyEvent;

using std::experimental::filesystem::path;

const size_t KaleidoscopeApp::kWindowHeight = 750;
const size_t KaleidoscopeApp::kWindowWidth = 1000;

const std::string KaleidoscopeApp::kDefaultImageExtension = "png";
const std::string KaleidoscopeApp::kImagesFolderPath = "images";

void KaleidoscopeApp::mouseUp(MouseEvent event) {
  // React to mouse up
  pad_.MouseUp();
}

void KaleidoscopeApp::mouseDrag(MouseEvent event) {
  // Respond to mouse activity in the toolbar
  if (toolbar_.ContainsPoint(event.getPos())) {
    pad_.MouseUp();

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
    pad_.MouseUp();

    CommandType command = toolbar_.MouseClicked(event.getPos());
    ManageCommand(command);

    // React to mouse activity on the sketchpad
  } else {
    pad_.MouseDown(event.getPos());
  }
}

void KaleidoscopeApp::draw() {
  pad_.Draw();
  toolbar_.Draw();
}

void KaleidoscopeApp::setup() {
  setWindowSize(kWindowWidth, kWindowHeight);
}

void KaleidoscopeApp::keyDown(KeyEvent event) {
  // Clear if backspace is pressed
  if (event.getCode() == KeyEvent::KEY_BACKSPACE) {
    pad_.Clear();

    // Change number of sectors if arrow keys are used
  } else if (event.getCode() == KeyEvent::KEY_UP || event.getCode() == KeyEvent::KEY_DOWN) {
    pad_.ChangeNumSectors(event.getCode() == KeyEvent::KEY_UP ? 1 : -1);
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

    // Change drawing color
    case CommandType::ColorChange:
      pad_.SetBrushColor(toolbar_.GetColor());
      return;

    // Undo last action
    case CommandType::Undo:
      pad_.Undo();
      return;

    // Save and quit
    case CommandType::Save:
      path path = getSaveFilePath(kImagesFolderPath);
      if (!path.has_extension()) {
        path.replace_extension(kDefaultImageExtension);
      }
      ci::writeImage(path, copyWindowSurface(Area(ivec2(0, 0),
                                                      ivec2(kWindowHeight, kWindowHeight))));
      quit();
  }
}

} // namespace visualizer

} // namespace kaleidoscope