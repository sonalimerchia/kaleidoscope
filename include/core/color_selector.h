#include <glm/glm.hpp>
#include <cinder/gl/gl.h>

#ifndef KALEIDOSCOPE_INCLUDE_VISUALIZER_COLOR_SELECTOR_H_
#define KALEIDOSCOPE_INCLUDE_VISUALIZER_COLOR_SELECTOR_H_

namespace kaleidoscope {

using glm::vec2;
using glm::ivec2;

using ci::ColorA;
using ci::Area;
using ci::Surface;

class ColorSelector {
 public:
  /**
   * Create a color selector in the passed position with the given dimensions
   *
   * @param position The location of the top left corner of the color selector
   * @param dimensions The dimensions of the color selector
   */
  ColorSelector(const ivec2 &position, const ivec2 &dimensions);

  /**
   * Draw the color selector
   */
  void Draw() const;

  /**
   * @return the current color chosen on the selector (default if none selected yet)
   */
  const ColorA& GetColor() const;

  /**
   * Check to see if mouse activity in the given location would change the color
   *
   * @param mouse_location the location of the mouse activity in the window
   * @return true if the mouse activity would change the color; false otherwise
   */
  bool WasEdited(const ivec2 &mouse_location) const;

  /**
   * Change the color of the color selector according to user activity
   *
   * @param mouse_location the location of the mouse activity
   */
  void ChangeColor(const ivec2 &mouse_location);

 private:
  // The areas occupied by the different components
  const Area palette_area_;
  const Area slider_area_;
  const Area color_display_area_;

  // The surfaces that display the gradients of the components
  Surface palette_;
  Surface slider_;

  // The current color of the selector
  ColorA color_;

  // The HSV components of the current color selected
  float hue_;
  float saturation_;
  float value_;

  /**
   * Draw a slider such that the left end is black, the right side
   * is the current color with a value of 1 (brightest coloring), and there
   * is a bar to show where in the slider the value component of the current
   * color's HSV is represented
   */
  void DrawValueSlider() const;

  /**
   * Draw a color palette such that the HSV models of the pixels show that
   * hue varies horizontally, saturation varies vertically, and the value component
   * is equal to that of the current color's HSV. Add a small circle to show where
   * the current color's hue and saturation are represented
   */
  void DrawHueSaturationPalette() const;

  /**
   * Refresh the surface that holds the gradient of the palette drawn by
   * DrawHueSaturationPalette(). Generating the surface such that its image is saved
   * and can simply be rendered upon drawing saves significant time when rendering
   * the images.
   *
   * Call whenever the value component of the current color is edited so the
   * value component of the HSVs of the pixels can be updated
   */
  void RefreshPalette();

  /**
   * Refresh the surface that holds the gradient of the slider drawn by
   * DrawValueSlider(). Generating the surface such that its image is saved
   * and can simply be rendered upon drawing saves significant time when rendering
   * the images.
   *
   * Call whenever the hue or saturation components of the current color is edited
   * so the slider can be updated to match
   */
  void RefreshSlider();

  /**
   * Change the hue and saturation components of the current color's HSV according
   * to mouse activity
   *
   * @param mouse_location the location of the mouse activity that affects hue or
   * saturation
   */
  void ChangeHueNSaturation(const ivec2 &mouse_location);

  /**
   * Change the value component of the current color's HSV according to mouse
   * activity
   *
   * @param mouse_location the location of the mouse activity that affects the value
   */
  void ChangeValue(const ivec2 &mouse_location);
};

} // namespace kaleidoscope

#endif //KALEIDOSCOPE_INCLUDE_VISUALIZER_COLOR_SELECTOR_H_
