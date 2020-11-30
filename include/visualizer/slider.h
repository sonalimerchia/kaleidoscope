#include <glm/glm.hpp>
#include <string>

#ifndef KALEIDOSCOPE_INCLUDE_COMPONENTS_SLIDER_H_
#define KALEIDOSCOPE_INCLUDE_COMPONENTS_SLIDER_H_

namespace kaleidoscope {

namespace visualizer {

class Slider {
 public:
  /**
   * Constructs a slider
   * @param position the location of the top left corner of the slider
   * @param dimensions the dimensions of the slider
   * @param title the title of the slider
   */
  Slider(const glm::vec2 &position,
         const glm::vec2 &dimensions,
         const std::string &title);

  /**
   * Determines whether mouse activity in that location would change the slider
   * @param mouse_loc the location on the slider where the mouse clicked/was dragged
   * @return true if the slider would have been edited; false otherwise
   */
  bool WasEdited(const glm::ivec2 &mouse_loc) const;

  /**
   * Edits the values of the slider in accordance with the mouse activity
   * @param mouse_loc the location on the slider where the mouse activity took place
   */
  void Slide(const glm::ivec2 &mouse_loc);

  /**
   * Draws the slider
   */
  void Draw() const;

  float GetDegree();

 private:
  const glm::vec2 position_;
  const glm::vec2 dimensions_;
  std::string message_;
  float degree_; // A number between 0 and 1 which describes the selected level
                 // of the slider where 0 represents being at the bottom of the slider
                 // and 1 represents beting at the top
};

} // namespace visualizer

} // namespace kaleidoscope

#endif //KALEIDOSCOPE_INCLUDE_COMPONENTS_SLIDER_H_
