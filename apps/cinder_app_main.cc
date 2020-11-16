#include <visualizer/kaleidoscope_app.h>

using kaleidoscope::KaleidoscopeApp;

void prepareSettings(KaleidoscopeApp::Settings* settings) {
  settings->setResizable(true);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(KaleidoscopeApp, ci::app::RendererGl, prepareSettings);
