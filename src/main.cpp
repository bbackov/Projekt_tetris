#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#include <iostream>
#include <stdexcept>
#include "game/Game.hpp"
#include "board/Board.hpp"
#include "util/shader.hpp"
#include "blocks/Blocks.hpp"
#include "input/input.hpp"
#include "blocks/Factory.hpp"
#include <algorithm>

void renderText(const std::string& text, float x, float y, float scale,
                stbtt_bakedchar* charData, GLuint textVAO, GLuint textVBO,
                GLint uColorLoc, float r, float g, float b,
                int BITMAP_W, int BITMAP_H){

    glUniform3f(uColorLoc, r, g, b);
    glBindVertexArray(textVAO);

    for(char c : text){
        stbtt_aligned_quad q;
        stbtt_GetBakedQuad(charData, BITMAP_W, BITMAP_H, c - 32, &x, &y, &q, 1);

        // pretvori piksel koordinate u NDC
        float vertices[24] = {
            q.x0 / 400.0f - 1.0f,  1.0f - q.y0 / 300.0f,  q.s0, q.t0,
            q.x1 / 400.0f - 1.0f,  1.0f - q.y0 / 300.0f,  q.s1, q.t0,
            q.x1 / 400.0f - 1.0f,  1.0f - q.y1 / 300.0f,  q.s1, q.t1,

            q.x0 / 400.0f - 1.0f,  1.0f - q.y0 / 300.0f,  q.s0, q.t0,
            q.x1 / 400.0f - 1.0f,  1.0f - q.y1 / 300.0f,  q.s1, q.t1,
            q.x0 / 400.0f - 1.0f,  1.0f - q.y1 / 300.0f,  q.s0, q.t1
        };

        glBindBuffer(GL_ARRAY_BUFFER, textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    glBindVertexArray(0);
}

int main() {

    try{
    std::cout << "NEW BUILD OK\n";
    // init GLFW...
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const int WIDTH = 800, HEIGHT = 600;
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Tetris (OpenGL)", nullptr, nullptr);
    if (!window) return -1;

    glfwMakeContextCurrent(window);

    // === GLAD init ===
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to init GLAD\n";
        return -1;
    }
    std::cout << "GLAD OK\n";
    glViewport(0, 0, WIDTH, HEIGHT);

    Game game; 
    game.spawn();   

    std::cout << "BEFORE SHADER\n";
    Shader shader("res/shaders/simple.vert", "res/shaders/simple.frag");
    Shader textShader("res/shaders/text.vert", "res/shaders/text.frag");

        float quadVerts[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,

        -0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };
    std::cout << "AFTER SHADER\n";
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVerts), quadVerts, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //uključivanje blendinga
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //VAO VBO za tekst
    GLuint textVAO, textVBO;
    glGenVertexArrays(1, &textVAO);
    glGenBuffers(1, &textVBO);

    glBindVertexArray(textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, nullptr, GL_DYNAMIC_DRAW); // nullptr jer mijenjamo svaki frame

    // pozicija - location 0
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // UV koordinate - location 1
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //učitavanje fonta
    FILE* fontFile = fopen("res/fonts/arial.ttf", "rb");
    if(!fontFile){
        std::cerr << "Font file not found!\n";
        return -1;
    }   
    fseek(fontFile, 0, SEEK_END);
    long size = ftell(fontFile);
    fseek(fontFile, 0, SEEK_SET);

    unsigned char* fontBuffer = new unsigned char[size];
    fread(fontBuffer, 1, size, fontFile);
    fclose(fontFile);

    //bitmapa
    const int BITMAP_W = 512, BITMAP_H = 512;
    unsigned char bitmap[BITMAP_W * BITMAP_H];

    stbtt_bakedchar charData[96]; // podatci za znakove ASCII 32-128

    stbtt_BakeFontBitmap(fontBuffer, 0, 32.0f, bitmap, BITMAP_W, BITMAP_H, 32, 96, charData);
    delete[] fontBuffer;

    //generiranje teksture
    GLuint fontTexture;
    glGenTextures(1, &fontTexture);
    glBindTexture(GL_TEXTURE_2D, fontTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, BITMAP_W, BITMAP_H, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    

    //grid i blokovi
    GLint uScaleLoc  = glGetUniformLocation(shader.program, "uScale");
    GLint uOffsetLoc = glGetUniformLocation(shader.program, "uOffset");
    GLint uColorLoc  = glGetUniformLocation(shader.program, "uColor");
    //tekst
    GLint uTextColorLoc = glGetUniformLocation(textShader.program, "uColor");  
    //računanje širine i visine ćelije grida
    float cellH = 2.0f / Board::play_height;
    float cellW = cellH;
    float cellHoldW=(0.5f/4);
    float cellHoldH=(0.5f/4);

    //input i registracija callbacka
    Input input;
    glfwSetWindowUserPointer(window, &input);
    glfwSetKeyCallback(window, Input::keyCallback);


    double lastTime = glfwGetTime();

    shader.use();
    

    while (!glfwWindowShouldClose(window)) {

        input.beginFrame();
        glfwPollEvents();

        // ESC->zatvaranje prozora
        if (input.pressed(GLFW_KEY_ESCAPE)){
            glfwSetWindowShouldClose(window, true);
        }

        // postavljanje inputa
        game.setMoveLeft(input.pressed(GLFW_KEY_LEFT));
        game.setMoveRight(input.pressed(GLFW_KEY_RIGHT));
        game.setSoftDrop(input.pressed(GLFW_KEY_DOWN));

        game.setRotateCW(input.justPressed(GLFW_KEY_UP));
        game.setRotateCCW(input.justPressed(GLFW_KEY_A));

        game.setHardDrop(input.justPressed(GLFW_KEY_SPACE));
        game.setPauseUsed(input.justPressed(GLFW_KEY_P));
        game.setHoldUsed(input.justPressed(GLFW_KEY_C));

                    
        glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);

        if(game.getState()==State::Game_over){
                glUniform2f(uScaleLoc, 2, 2);
                glUniform3f(uColorLoc, 0.08f, 0.06f, 0.07f);
                glUniform2f(uOffsetLoc,0,0);
                glDrawArrays(GL_TRIANGLES, 0, 6);
                textShader.use();
                renderText("Game Over ", 300.0f, 300.0f, 1.0f, charData, textVAO, textVBO, uTextColorLoc, 1.0f, 1.0f, 1.0f, 512, 512);
                shader.use();
        }
        else if(game.getState()==State::Playing){

            double now = glfwGetTime();
            int deltaMS = (int)((now - lastTime) * 1000.0);
            lastTime=now;
            game.tick(deltaMS);
        

            float offsetX;
            float offsetY;
            float boardWidth = Board::width * cellW;
            float boardOffsetX = (2.0f - boardWidth) / 2.0f;
            const Board& board = game.getBoard();

            for(int i=0;i<Board::width;i++){
                for(int j=0;j<Board::play_height;j++){
                    int cell=board.getCell({i,j  + Board::hidden_height});

                    offsetX = -1 + cellW * (i + 0.5)+boardOffsetX;
                    offsetY = 1 - cellH * (j + 0.5);
                    glUniform2f(uOffsetLoc, offsetX, offsetY);

                    glUniform2f(uScaleLoc, cellW * 0.92f, cellH * 0.92f);
                    glUniform3f(uColorLoc, 0.0f, 0.0f, 0.0f);
                    glDrawArrays(GL_TRIANGLES, 0, 6);

                    if(cell!=Board::EMPTY){
                        ShapeType shape = static_cast<ShapeType>(cell);
                        Color color=getColorForShape(shape);
                        glUniform2f(uScaleLoc, cellW * 0.80f, cellH * 0.80f);
                        glUniform3f(uColorLoc, color.r,color.g,color.b);
                        glDrawArrays(GL_TRIANGLES, 0, 6);
                    }


                }
            }

            const Block* ghost=game.getGhost();

            if(ghost){
                ShapeType shape=ghost->getShape();
                Color color=getColorForShape(shape);

                for(auto point:ghost->getAbsoluteCells()){

                    int x=point.first;
                    int y=point.second;
                    if(y < Board::hidden_height) continue;
                    y-=Board::hidden_height;

                    float offsetX = -1 + cellW * (x + 0.5f)+boardOffsetX;
                    float offsetY =  1 - cellH * (y + 0.5f);

    

                    glUniform2f(uOffsetLoc, offsetX, offsetY);

                    glUniform2f(uScaleLoc, cellW * 0.8f, cellH * 0.8f);
                    glUniform3f(uColorLoc, color.r* 0.35f, color.g* 0.35f, color.b* 0.35f);
                    glDrawArrays(GL_TRIANGLES, 0, 6);


                }
            }


            const Block* current=game.getCurrent();

            if(current){
                ShapeType shape=current->getShape();
                Color color=getColorForShape(shape);

                for(auto point:current->getAbsoluteCells()){

                    int x=point.first;
                    int y=point.second;
                    if(y < Board::hidden_height) continue;
                    y-=Board::hidden_height;

                    float offsetX = -1 + cellW * (x + 0.5f)+boardOffsetX;
                    float offsetY =  1 - cellH * (y + 0.5f);

    

                    glUniform2f(uOffsetLoc, offsetX, offsetY);

                    glUniform2f(uScaleLoc, cellW * 0.8f, cellH * 0.8f);
                    glUniform3f(uColorLoc, color.r, color.g, color.b);
                    glDrawArrays(GL_TRIANGLES, 0, 6);


                }
            }

            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){

                    float offsetX = -1 + cellHoldW * (i + 0.5);
                    float offsetY = 1 - cellHoldH * (j + 0.5)-0.25f;
                    glUniform2f(uOffsetLoc, offsetX, offsetY);
                    glUniform2f(uScaleLoc, cellHoldW, cellHoldH);
                    glUniform3f(uColorLoc, 0.0f, 0.0f, 0.0f);
                    glDrawArrays(GL_TRIANGLES, 0, 6);
                            
                }
            }

            if(game.getHold().has_value()){
                std::unique_ptr<Block> hold = makeBlock(game.getHold().value());
                std::array<point,4> points= hold->getCells();
                Color color=getColorForShape(game.getHold().value());

                std::pair<int,int> min={points[0].first, points[0].second};
                std::pair<int,int> max={points[0].first, points[0].second};

                for(point p:points){
                    min.first=std::min(min.first,p.first);
                    min.second=std::min(min.second,p.second);
                    max.first=std::max(max.first,p.first);
                    max.second=std::max(max.second,p.second);
                }

                float blockCenterX = (min.first + max.first) / 2.0f;
                float blockCenterY = (min.second + max.second) / 2.0f;

                float centerOffsetX = (1.5f - blockCenterX) * cellHoldW;
                float centerOffsetY = (1.5f - blockCenterY) * cellHoldH;

        

                for(point p:points){

                    float offsetX = -1 + cellHoldW * (p.first + 0.5f)+centerOffsetX;
                    float offsetY =  1 - cellHoldH * (p.second + 0.5f)-0.25f-centerOffsetY;
                            
                    glUniform2f(uOffsetLoc, offsetX, offsetY);

                    glUniform2f(uScaleLoc, cellHoldW * 0.80f, cellHoldH * 0.80f);
                    glUniform3f(uColorLoc, color.r, color.g, color.b);
                    glDrawArrays(GL_TRIANGLES, 0, 6);
                }

            }
            textShader.use();
            glBindTexture(GL_TEXTURE_2D, fontTexture);
            renderText("Holded Block: ", 10.0f, 40.0f, 1.0f, charData, textVAO, textVBO, uTextColorLoc, 1.0f, 1.0f, 1.0f, 512, 512);
            renderText("Score:"+ std::to_string(game.getScore()), 10.0f, 350.0f, 1.0f, charData, textVAO, textVBO, uTextColorLoc, 1.0f, 1.0f, 1.0f, 512, 512);
            renderText("Level:"+ std::to_string(game.getLevel()), 10.0f, 500.0f, 1.0f, charData, textVAO, textVBO, uTextColorLoc, 1.0f, 1.0f, 1.0f, 512, 512);
            shader.use();

        }
        
        glBindVertexArray(0);

            
        glfwSwapBuffers(window);
    }


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;

    }
    catch(const std::exception& e) {
        std::cerr << "PROGRAM CRASH: " << e.what() << std::endl;
        std::cin.get();
        return -1;
    }
}


