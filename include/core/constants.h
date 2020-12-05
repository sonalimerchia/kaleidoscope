#include <string>
#include "cinder/gl/gl.h"

#ifndef KALEIDOSCOPE_INCLUDE_CORE_CONSTANTS_H_
#define KALEIDOSCOPE_INCLUDE_CORE_CONSTANTS_H_

namespace kaleidoscope {

using std::string;
using ci::Color;

// App Constants
static const size_t kWindowHeight = 750;
static const size_t kWindowWidth = 1000;
static const string kImagesFolderPath = "C:\\Users\\sonal\\Desktop\\CLion\\cinder\\final-project-sonalimerchia\\images";
static const string kDefaultImageExtension = "png";

static const string kPaletteFolderPath = "C:\\Users\\sonal\\Desktop\\CLion\\cinder\\final-project-sonalimerchia\\palette_images";

// Drawing settings
static const size_t kMinBrushSize = 1;
static const size_t kMaxBrushSize = 40;

static const float PI = 3.141592653589793238462643383279502884197169399375105820974944592307f;

// Component Visualization Constants
static const size_t kFontSize = 20;
static const string kFontStyle = "arial";

static const size_t kButtonHeight = 50;
static const size_t kSliderHeight = 300;

static const Color kButtonColor = Color("black");
static const Color kButtonTextColor = Color("white");
static const size_t kSliderTabHeight = 4;

// Default drawing settings
static const size_t kDefaultNumSectors = 6;
static const Color kDefaultBackgroundColor = Color("white");
static const Color kDefaultDrawingColor = Color("blue");

} // namespace kaleidoscope

#endif //KALEIDOSCOPE_INCLUDE_CORE_CONSTANTS_H_
