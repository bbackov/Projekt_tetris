# Tetris (OpenGL C++)

Jednostavna Tetris igra izrađena u C++ koristeći OpenGL.

## Tehnologije

- C++
- OpenGL (GLFW + GLAD)
- stb_truetype (renderiranje fontova)

## Kontrole

- ⬅️ ➡️ Pomak lijevo / desno  
- ⬇️ Ubrzano spuštanje  
- ⬆️ Rotacija (u smjeru kazaljke na satu)  
- A Rotacija (suprotno od kazaljke na satu)  
- Space Trenutno spuštanje (hard drop)  
- C Držanje bloka (hold)  
- P Pauza  
- ESC Izlaz  

## Pokretanje (MSYS2 MinGW64)

```bash
g++ src/main.cpp src/glad.c src/*/*.cpp -Iinclude -L/mingw64/lib -lglfw3 -lopengl32 -lgdi32 -luser32 -std=c++20 -O2 -o Tetris.exe