//
// Created by quantum on 6/29/21.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Renderer2D.h"
#include "Shader.h"
#include "VertexArray.h"
#include "RenderCommand.h"

namespace Clay
{
   struct Renderer2DStorage
   {
      Ref<VertexArray> QuadVertexArray;
      Ref<Shader> TextureShader;
      Ref<Texture2D> WhiteTexture;
   };

   static Renderer2DStorage *s_Data;

   void Renderer2D::Init()
   {
      s_Data = new Renderer2DStorage();

      s_Data->QuadVertexArray = VertexArray::Create();

      float vertices[4 * 5] = {/* Position */  -0.5f, -0.5f, 0.0f,   /* TexCoord */ 0.0f, 0.0f,
            /* Position */  0.5f, -0.5f, 0.0f,    /* TexCoord */ 1.0f, 0.0f,
            /* Position */  0.5f, 0.5f, 0.0f,     /* TexCoord */ 1.0f, 1.0f,
            /* Position */  -0.5f, 0.5f, 0.0f,    /* TexCoord */ 0.0f, 1.0f};

      Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float));

      BufferLayout layout = {{ShaderDataType::Float3, "a_Position"},
                             {ShaderDataType::Float2, "a_TexCoord"}};
      vertexBuffer->SetLayout(layout);
      s_Data->QuadVertexArray->AddVertexBuffer(vertexBuffer);

      unsigned int indices[6] = {0, 1, 2, 2, 3, 0};
      Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

      s_Data->QuadVertexArray->SetIndexBuffer(indexBuffer);

      s_Data->WhiteTexture = Texture2D::Create(1,1);
      uint32_t whiteTextureData = 0xffffffff;
      s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

      s_Data->TextureShader = Shader::Create("/home/quantum/Workspace/FastStorage/IHMC_PhD/Research/ClayEngine/src/Example/Assets/Shaders/Texture.glsl");
      s_Data->TextureShader->Bind();
      s_Data->TextureShader->SetInt("u_Texture", 0);
   }

   void Renderer2D::Shutdown()
   {
      delete s_Data;
   }

   void Renderer2D::OnWindowResize(uint32_t width, uint32_t height)
   {
   }

   void Renderer2D::BeginScene(const OrthographicCamera& camera)
   {
      s_Data->TextureShader->Bind();
      s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
   }

   void Renderer2D::EndScene()
   {
   }

   void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
   {
      s_Data->TextureShader->SetFloat4("u_Color", color);
      s_Data->WhiteTexture->Bind();

      glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
      s_Data->TextureShader->SetMat4("u_Transform", transform);

      s_Data->QuadVertexArray->Bind();
      RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
   }

   void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
   {
      DrawQuad({position.x, position.y, 0.0f}, size, color);
   }

   void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
   {
      s_Data->TextureShader->SetFloat4("u_Color", {1.0f, 1.0f, 1.0f, 1.0f});
      texture->Bind();

      glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
      s_Data->TextureShader->SetMat4("u_Transform", transform);

      s_Data->QuadVertexArray->Bind();
      RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
   }

   void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
   {
      DrawQuad({position.x, position.y, 0.0f}, size, texture);
   }
}