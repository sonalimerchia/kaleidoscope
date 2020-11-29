#include <glm/glm.hpp>
#include <string>

#ifndef KALEIDOSCOPE_INCLUDE_CORE_BUTTON_H_
#define KALEIDOSCOPE_INCLUDE_CORE_BUTTON_H_

namespace kaleidoscope {

class Button {
 public:
  Button(const glm::vec2 &position, const glm::vec2 &dimensions, const std::string &message);

  bool WasPressed(const glm::ivec2 &mouse_location) const;
  void SetMessage(const std::string &new_message);

  void Draw() const;
  const std::string& GetMessage() const;

 private:
  const glm::vec2 position_;
  const glm::vec2 dimensions_;
  std::string message_;

};

}

#endif //KALEIDOSCOPE_INCLUDE_CORE_BUTTON_H_
