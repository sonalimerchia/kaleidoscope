#include <glm/glm.hpp>
#include <string>

#ifndef KALEIDOSCOPE_INCLUDE_BUTTON_H_
#define KALEIDOSCOPE_INCLUDE_BUTTON_H_

namespace kaleidoscope {

namespace visualizer {

class Button {
 public:
  /**
   * Creates a button
   * @param position the top left corner of the button
   * @param dimensions the dimensions of the button
   * @param message the text to be displayed on the button
   */
  Button(const glm::vec2 &position,
         const glm::vec2 &dimensions,
         const std::string &message);

  /**
   * Determines whether a click pressed this button
   * @param mouse_location the coordinates of where the mouse was clicked
   * @return true if the mouse location is within the area of the button; false otherwise
   */
  bool WasPressed(const glm::ivec2 &mouse_location) const;

  /**
   * Draws the button
   */
  void Draw() const;

  /**
   * A Getter and Setter for the button's text
   */
  void SetMessage(const std::string &new_message);
  const std::string &GetMessage() const;

 private:
  const glm::vec2 position_;
  const glm::vec2 dimensions_;
  std::string message_;

};

} // namespace visualizer

} // namespace kaleidoscope

#endif //KALEIDOSCOPE_INCLUDE_BUTTON_H_
