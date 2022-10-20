#include "RenderTexture.h"
#include "Renderer.h"
#include "../../Helper/Logger.h"
#include "../../Helper/format.h"
#include "../../Math/MathHelper.h"

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace Engine::Helper;
using namespace Engine::Rendering;
using namespace Engine::Math;

void RenderTexture::mBuildVAO()
{
    float uvX1 = (float)this->mSourceRectangle.X / (float)this->mSize.X;
    float uvX2 = (float)(this->mSourceRectangle.X + this->mSourceRectangle.Width) / (float)this->mSize.X;
    float uvY1 = 1.f - ((float)this->mSourceRectangle.Y / (float)this->mSize.Y);
    float uvY2 = 1.f - ((float)(this->mSourceRectangle.Y + this->mSourceRectangle.Height) / (float)this->mSize.Y);

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

bool RenderTexture::Create(int width, int height, Renderer &renderer)
{
    glGenFramebuffers(1, &this->mFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, this->mFrameBuffer);

    if (!glCheckFramebufferStatus(GL_FRAMEBUFFER))
    {
        Logger::Log(Logger::Error, "Unable to create render texture!");
        return false;
    }

    glGenTextures(1, &this->mTexture);
    glBindTexture(GL_TEXTURE_2D, this->mTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->mTexture, 0);

    this->mSize = Vector2(width, height);
    this->mSourceRectangle = Rectangle(0, 0, width, height);
    this->origin = Vector2f(0, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0); 

    this->mColor.R = 1;
    this->mColor.G = 1;
    this->mColor.B = 1;
    this->mColor.A = 1;
    this->mBuildVAO();

    return true;
}

void RenderTexture::SetOrigin(float x, float y)
{
    this->origin.X = x;
    this->origin.Y = y;
}

int RenderTexture::GetWidth()
{
    return this->mSize.X;
}

int RenderTexture::GetHeight()
{
    return this->mSize.Y;
}

Vector2* RenderTexture::GetSize()
{
    return &this->mSize;
}

bool RenderTexture::SetAsRenderTarget(Renderer &renderer)
{
    glBindFramebuffer(GL_FRAMEBUFFER, this->mFrameBuffer);
    return true;
}

bool RenderTexture::Draw(Rectangle &destinationRectangle, Renderer &renderer, double rotationRad, bool flipHorizontal, bool flipVertical)
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

bool RenderTexture::Draw(Rectangle &sourceRectangle, Rectangle &destinationRectangle, Renderer &renderer, double rotationRad, bool flipHorizontal, bool flipVertical)
{
    Rectangle tmpRect = this->mSourceRectangle;
    this->mSourceRectangle = sourceRectangle;
    this->mBuildVAO();

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

bool RenderTexture::SetBlendMode(BlendMode::BlendMode mode)
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

bool RenderTexture::SetColorMod(Colorf &color)
{
    this->mColor = color;
    this->mBuildVAO();
    return true;
}

void RenderTexture::Unload()
{
    glDeleteFramebuffers(1, &this->mFrameBuffer);
    glDeleteTextures(1, &this->mTexture);
    this->mFrameBuffer = NULL;
    this->mTexture = NULL;
}