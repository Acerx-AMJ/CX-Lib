<img height=150 src="assets/cx.png"/>

CX is an UI/Utility library for SFML-based applications. It is primarily made for 2D projects - games and desktop applications. It integrates well with SFML and makes creating projects easier, faster and more comfortable. It includes utility classes like grid, asset manager, audio manager and many more and UI elements like buttons, sliders, bars and so on, which can be easily included in an already existing SFML project.

## Usage
CX can be included in projects using CMake's fetchContent module. It depends on C++20 and [SFML 2.6](https://www.sfml-dev.org). Here's an example:
```cmake
cmake_minimum_required(VERSION 3.10)
project(myProject)

set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(cx GIT_REPOSITORY https://github.com/Acerx-AMJ/CX-Library.git GIT_TAG main GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(cx)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/main.cpp)

find_package(SFML 2.6 COMPONENTS window system graphics audio REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-window sfml-system sfml-graphics sfml-audio cx)
```

Here's a test program to compile:
```cpp
#include <CX/EventHandler/EventHandler.hpp>
#include <CX/Rect/Rect.hpp>

int main() {
   sf::RenderWindow window (sf::VideoMode(800, 600), "Hello, CX!");
   window.setFramerateLimit(60);

   cx::EventHandler event (window);
   cx::Rect rect ({500.0f, 500.0f}, {400.0f, 300.0f}, cx::Color::red());

   while (window.isOpen()) {
      event.update();
      window.clear();
      rect.render(window);
      window.display();
   }
}
```

Compile with:
```bash
cmake -B build
cmake --build build
```
The executable will be located in `build/myProject` (or whatever you named your CMake project).

## Building
Cross-platform way to build and install the library, you need to be in the same directory as CMakeLists.txt file:
```bash
cmake -S . -B build
cmake --build build --config Release
cmake --install build --config Release # needs sudo on Linux/MacOS
```

Here's an example on how to include the library with CMake:
```cmake
cmake_minimum_required(VERSION 3.10)
project(myProject)

set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/main.cpp)

find_package(cx REQUIRED)
find_package(SFML 2.6 COMPONENTS window system graphics audio REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-window sfml-system sfml-graphics sfml-audio cx)
```

## Credits
This library uses SFML [(Official SFML website)](https://www.sfml-dev.org/) for most of the features, which is licensed under zlib/png license.

This library was made by Daniel Vishnevsky and is licensed under MIT License. It was in development from December 2024 to June 2025 and republished as an effort to make all of my projects open-source.
