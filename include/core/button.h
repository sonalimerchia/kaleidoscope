#include <string>

#include <glm/glm.hpp>
#include <cinder/gl/gl.h>

#ifndef KALEIDOSCOPE_INCLUDE_BUTTON_H_
#define KALEIDOSCOPE_INCLUDE_BUTTON_H_

namespace kaleidoscope {

namespace visualizer {

using glm::vec2;
using glm::ivec2;
using ci::Area;

using std::string;

class Button {

 public:
  static const float kFontSize;
  static const string kFontStyle;

  /**
   * Creates a button
   * @param position the top left corner of the button
   * @param dimensions the dimensions of the button
   * @param message the text to be displayed on the button
   */
  Button(const vec2 &position, const vec2 &dimensions, const string &message);

  /**
   * Determines whether a click pressed this button
   * @param mouse_location the coordinates of where the mouse was clicked
   * @return true if the mouse location is within the area of the button; false otherwise
   */
  bool WasPressed(const ivec2 &mouse_location) const;

  /**
   * Draws the button
   */
  void Draw() const;

  /* Getter and Setter Methods */
  void SetMessage(const string &new_message);
  const string& GetMessage() const;

 private:
  const Area area_;
  string message_;

};

} // namespace visualizer

} // namespace kaleidoscope

#endif //KALEIDOSCOPE_INCLUDE_BUTTON_H_
