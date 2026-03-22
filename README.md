# Tetris (OpenGL C++)

Simple Tetris game built in C++ using OpenGL.

## Technologies

- C++
- OpenGL (GLFW + GLAD)
- stb_truetype (font rendering)

## Controls

- ⬅️ ➡️ Move left / right  
- ⬇️ Soft drop  
- ⬆️ Rotate (CW)  
- A Rotate (CCW)  
- Space Hard drop  
- C Hold piece  
- P Pause  
- ESC Exit  

## How to Run

1. Build the project (g++ / Visual Studio / CMake)
2. Make sure required libraries are linked:
   - GLFW
   - GLAD
3. Run the executable

## Structure

- `game/` – core game logic  
- `board/` – grid and collision  
- `blocks/` – tetromino shapes  
- `util/` – shaders, timers, helpers  
- `input/` – input handling  

## Notes

- Uses modern OpenGL (Core Profile)
- Rendering is done manually (no engine)
- Project made for learning graphics and game logic
