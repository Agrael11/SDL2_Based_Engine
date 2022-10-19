#include "Sprite.h"
#include "Renderer.h"
#include "../../Helper/Logger.h"
#include "../../Helper/format.h"
#include "../../Math/MathHelper.h"

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../../Math/Colorf.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace Engine::Helper;
using namespace Engine::Rendering;
using namespace Engine::Math;

void Sprite::mBuildVAO()
{
    float uvX1 = (float)this->sourceRectangle.X / (float)this->mSize.X;
    float uvX2 = (float)(this->sourceRectangle.X + this->sourceRectangle.Width) / (float)this->mSize.X;
    float uvY1 = 1.f - ((float)this->sourceRectangle.Y / (float)this->mSize.Y);
    float uvY2 = 1.f - ((float)(this->sourceRectangle.Y + this->sourceRectangle.Height) / (float)this->mSize.Y);

    float vertices[] = {
         1.0f,  1.0f, 0.0f,    mColor.R, mColor.G, mColor.B, mColor.A,     uvX2, uvY1, //Top Right
         1.0f,  0.0f, 0.0f,    mColor.R, mColor.G, mColor.B, mColor.A,     uvX2, uvY2, //Bottom Right
         0.0f,  0.0f, 0.0f,    mColor.R, mColor.G, mColor.B, mColor.A,     uvX1, uvY2, //Bottom Left
         0.0f,  1.0f, 0.0f,    mColor.R, mColor.G, mColor.B, mColor.A,     uvX1, uvY1  //Top Left
    };

    unsigned int indicies[] = {
        0, 1, 3,
        1, 2, 3
    };

    glGenVertexArrays(1, &this->mVAO);
    glBindVertexArray(this->mVAO);
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

bool Sprite::Load(std::string filePath, Renderer &renderer)
{
    Logger::Log(Logger::Info, string_format("Loading texture %s...", filePath.c_str()));

    int sizeX = 0;
    int sizeY = 0;
    int nrChannels;

    glGenTextures(1, &this->mTexture);
    glBindTexture(GL_TEXTURE_2D, this->mTexture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filePath.c_str(), &sizeX, &sizeY, &nrChannels, 0);
    if (data)
    {
        if (nrChannels == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sizeX, sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else if (nrChannels == 4)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sizeX, sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);   
        }
    }
    else
    {
        Logger::Log(Logger::Error, "Failed to load texture.");
    }

    this->sourceRectangle = Rectangle(0, 0, sizeX, sizeY);
    this->mSize = Vector2(sizeX, sizeY);
    this->origin = Vector2f(0,0);

    this->mColor.R = 1;
    this->mColor.G = 1;
    this->mColor.B = 1;
    this->mColor.A = 1;
    this->mBuildVAO();

    stbi_image_free(data);

    return true;
}

bool Sprite::Load(std::string filePath, Rectangle sourceRectangle, Renderer &renderer)
{Logger::Log(Logger::Info, string_format("Loading texture %s...", filePath.c_str()));

    int sizeX = 0;
    int sizeY = 0;
    int nrChannels;

    glGenTextures(1, &this->mTexture);
    glBindTexture(GL_TEXTURE_2D, this->mTexture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filePath.c_str(), &sizeX, &sizeY, &nrChannels, 0);
    if (data)
    {
        if (nrChannels == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sizeX, sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else if (nrChannels == 4)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sizeX, sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);   
        }
    }
    else
    {
        Logger::Log(Logger::Error, "Failed to load texture.");
    }

    this->sourceRectangle = sourceRectangle;
    this->mSize = Vector2(sizeX, sizeY);
    this->origin = Vector2f(0,0);

    this->mColor.R = 1;
    this->mColor.G = 1;
    this->mColor.B = 1;
    this->mColor.A = 1;
    this->mBuildVAO();

    stbi_image_free(data);

    return true;
}
void Sprite::SetOrigin(float x, float y)
{
    this->origin.X = x;
    this->origin.Y = y;
}

void Sprite::SetSourceRectangle(Rectangle &r)
{
    this->sourceRectangle = r;
    this->mBuildVAO();
}

int Sprite::GetWidth()
{
    return this->mSize.X;
}

int Sprite::GetHeight()
{
    return this->mSize.Y;
}

Vector2* Sprite::GetSize()
{
    return &this->mSize;
}

bool Sprite::Draw(Rectangle &destinationRectangle, Renderer &renderer, double rotationRad, bool flipHorizontal, bool flipVertical)
{
    Shader* shader = renderer.GetActiveShader();
    shader->UseShader();
    
    Vector2f actualOrigin(destinationRectangle.Width * this->origin.X, destinationRectangle.Height * this->origin.Y);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3((float)destinationRectangle.X, (float)destinationRectangle.Y, -1.0));
    model = glm::translate(model, glm::vec3((float)actualOrigin.X, (float)actualOrigin.Y, 0.0));
    model = glm::rotate(model, (float)rotationRad, glm::vec3(0.0, 0.0, 1.0));
    model = glm::translate(model, glm::vec3(-(float)actualOrigin.X, -(float)actualOrigin.Y, 0.0));
    model = glm::scale(model, glm::vec3((float)destinationRectangle.Width, (float)destinationRectangle.Height, 10));

    glm::mat4 view = glm::mat4(1.0f);

    Rectangle viewport = renderer.GetViewport();

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::ortho(0.0f, (float)viewport.Width, 0.0f, (float)viewport.Height, 0.1f, 100.0f);


    /*3D
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
    //model = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
    //model = glm::rotate(model, 0.f, glm::vec3(0.0, 0.0, 1.0));
    //model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), (float)mSize.X / (float)mSize.Y, 0.1f, 100.0f);
    */

    unsigned int modelLoc = glGetUniformLocation(shader->GetHandle(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    unsigned int viewLoc = glGetUniformLocation(shader->GetHandle(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    unsigned int projectionLoc = glGetUniformLocation(shader->GetHandle(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->mTexture);
    glBindVertexArray(this->mVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    return true;
}

bool Sprite::Draw(Rectangle &sourceRectangle, Rectangle &destinationRectangle, Renderer &renderer, double rotationRad, bool flipHorizontal, bool flipVertical)
{    
    Rectangle tmpRect = this->sourceRectangle;
    SetSourceRectangle(sourceRectangle);

    Shader* shader = renderer.GetActiveShader();
    shader->UseShader();
    
    Vector2f actualOrigin(destinationRectangle.Width * this->origin.X, destinationRectangle.Height * this->origin.Y);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3((float)destinationRectangle.X, (float)destinationRectangle.Y, -1.0));
    model = glm::translate(model, glm::vec3((float)actualOrigin.X, (float)actualOrigin.Y, 0.0));
    model = glm::rotate(model, (float)rotationRad, glm::vec3(0.0, 0.0, 1.0));
    model = glm::translate(model, glm::vec3(-(float)actualOrigin.X, -(float)actualOrigin.Y, 0.0));
    model = glm::scale(model, glm::vec3((float)destinationRectangle.Width, (float)destinationRectangle.Height, 10));

    glm::mat4 view = glm::mat4(1.0f);

    Rectangle viewport = renderer.GetViewport();
    
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::ortho(0.0f, (float)viewport.Width, 0.0f, (float)viewport.Height, 0.1f, 100.0f);

    unsigned int modelLoc = glGetUniformLocation(shader->GetHandle(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    unsigned int viewLoc = glGetUniformLocation(shader->GetHandle(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    unsigned int projectionLoc = glGetUniformLocation(shader->GetHandle(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->mTexture);
    glBindVertexArray(this->mVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    return true;
}

bool Sprite::SetBlendMode(BlendMode::BlendMode mode)
{
    switch (mode)
    {
        case BlendMode::Min:
            glBlendEquation(GL_MIN);
            break;
        case BlendMode::Max:
            glBlendEquation(GL_MAX);
            break;
        case BlendMode::Subtract:
            glBlendEquation(GL_FUNC_SUBTRACT);
            break;
        case BlendMode::ReverseSubtract:
            glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
            break;
        default:
        case BlendMode::Add:
            glBlendEquation(GL_FUNC_ADD);
            break;
    }
    return true;
}

bool Sprite::SetColorMod(Colorf &color)
{
    this->mColor = color;
    this->mBuildVAO();
    return true;
}

void Sprite::Unload()
{
    glDeleteTextures(1, &this->mTexture);
    this->mTexture = NULL;
}