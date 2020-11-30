#include <visualizer/kaleidoscope_app.h>

using kaleidoscope::visualizer::KaleidoscopeApp;

void prepareSettings(KaleidoscopeApp::Settings* settings) {
  settings->setResizable(true);
  settings->setMultiTouchEnabled( false );
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(KaleidoscopeApp, ci::app::RendererGl, prepareSettings);
