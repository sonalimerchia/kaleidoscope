# Kaleidoscope 

A drawing app that allows the user to rotate each stroke into a number of sectors
around a circle. The app supports drawing in 2-50 sectors, selecting custom colors, 
undoing the last action, and saving using your device's save file dialog.

![demo](demo.gif)

## Set Up

Download the project and build using cmake. Downloading can
be done in a number of ways using git, unzipping a .zip file, etc.
Below are examples of how to download (using git) and how to build/run the app
#####Downloading with Git
```
cd path\to\cinder_master
git clone https://github.com/uiuc-fa20-cs126/final-project-sonalimerchia
cd final-project-sonalimerchia
```

#####Building/Running with CMake
```
mkdir cmake-build
cd cmake-build
cmake ..
cmake --build
.\kaleidoscope.cc
```

## Dependencies
* [cmake](https://cmake.org/)
* [cinder](https://github.com/cinder/Cinder)
* [catch2](https://github.com/catchorg/Catch2)
* [Microsoft Visual Studio 2019](https://visualstudio.microsoft.com/)

## Controls

#####Keyboard Controls
| Key        | Action                              |
|------------|------------------------------------ |
| `BACKSPACE`| Clear Editor                        |
| `Up`       | Increase the number of sectors by 1 |
| `Down`     | Decrease number of sectors by 1     |

#####Editor Toolbar
| Component      | Action                                           |
|----------------|--------------------------------------------------|
| Draw           | Switch your brush to draw if is erasing          |
| Erase          | Switch your brush to erase if is drawing         |
| Slider         | Change brush size                                |
| Color Selector | Change brush color to selected values            |
| Undo           | Undo last stroke                                 |
| Save           | Save image to desired location and quit the app  | 

## Customization

#### Changing Size of Editor
1. Navigate to \src\visualizer\kaleidoscope_app.cc
2. Edit kWindowWidth and kWindowHeight as desired
    * Keep in mind that your toolbar will be the width of 
    kWindowWidth - kWindowHeight to keep your drawing square 
    so kWindowHeight should be less than kWindowWidth

#### Changing Pad Color
1. Navigate to \src\visualizer\sketchpad.cc
2. Change kDefaultDrawingColor to another cinder-supported color

#### Changing Default Save Location
1. Navigate to src\visualizer\kaleidoscope_app.cc
2. Change kImagesFolderPath to the default path you would like to save 
your images to. 
    * Whether or not you do this, the save file dialog will allow you to 
    save your images wherever you would like. Only use this option if you 
    would like the default location to change so you can navigate from there