#ifndef KALEIDOSCOPE_INCLUDE_CORE_COMMAND_TYPE_H_
#define KALEIDOSCOPE_INCLUDE_CORE_COMMAND_TYPE_H_

namespace kaleidoscope {

enum CommandType {
  None,
  DrawMode,
  BrushSize,
  ColorChange,
  Undo,
  Save
};

} // namespace kaleidoscope

#endif //KALEIDOSCOPE_INCLUDE_CORE_COMMAND_TYPE_H_
