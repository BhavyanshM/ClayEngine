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
   struct QuadVertex
   {
      glm::vec3 Position;
      glm::vec4 Color;
      glm::vec2 TexCoord;
      // TODO: texid
   };

   struct Renderer2DData
   {
      const uint32_t MaxQuads = 10000;
      const uint32_t MaxVertices = MaxQuads * 4;
      const uint32_t MaxIndices = MaxQuads * 6;

      Ref<VertexArray> QuadVertexArray;
      Ref<VertexBuffer> QuadVertexBuffer;
      Ref<Shader> TextureShader;
      Ref<Texture2D> WhiteTexture;

      uint32_t QuadIndexCount = 0;
      QuadVertex* QuadVertexBufferBase = nullptr;
      QuadVertex* QuadVertexBufferPtr = nullptr;
   };

   static Renderer2DData s_Data;

   void Renderer2D::Init()
   {
      CLAY_PROFILE_FUNCTION();

      s_Data.QuadVertexArray = VertexArray::Create();

      float vertices[4 * 5] ={
            /* Position */  -0.5f, -0.5f, 0.0f,   /* TexCoord */ 0.0f, 0.0f,
            /* Position */  0.5f, -0.5f, 0.0f,    /* TexCoord */ 1.0f, 0.0f,
            /* Position */  0.5f, 0.5f, 0.0f,     /* TexCoord */ 1.0f, 1.0f,
            /* Position */  -0.5f, 0.5f, 0.0f,    /* TexCoord */ 0.0f, 1.0f};

      s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));

      BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"},
            {ShaderDataType::Float2, "a_TexCoord"}
      };
      s_Data.QuadVertexBuffer->SetLayout(layout);
      s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

      s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

      uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

      uint32_t offset = 0;
      for(uint32_t i = 0; i< s_Data.MaxIndices; i+=6)
      {
         quadIndices[i+0] = offset + 0;
         quadIndices[i+1] = offset + 1;
         quadIndices[i+2] = offset + 2;

         quadIndices[i+3] = offset + 2;
         quadIndices[i+4] = offset + 3;
         quadIndices[i+5] = offset + 0;

         offset += 4;
      }

      Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
      s_Data.QuadVertexArray->SetIndexBuffer(indexBuffer);
      delete[] quadIndices;

      s_Data.WhiteTexture = Texture2D::Create(1,1);
      uint32_t whiteTextureData = 0xffffffff;
      s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

      s_Data.TextureShader = Shader::Create("/home/quantum/Workspace/FastStorage/IHMC_PhD/Research/ClayEngine/src/Example/Assets/Shaders/Texture.glsl");
      s_Data.TextureShader->Bind();
      s_Data.TextureShader->SetInt("u_Texture", 0);
   }

   void Renderer2D::Shutdown()
   {
      CLAY_PROFILE_FUNCTION();
   }

   void Renderer2D::OnWindowResize(uint32_t width, uint32_t height)
   {
   }

   void Renderer2D::BeginScene(const OrthographicCamera& camera)
   {
      CLAY_PROFILE_FUNCTION();

      s_Data.TextureShader->Bind();
      s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

      s_Data.QuadIndexCount = 0;
      s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
   }

   void Renderer2D::EndScene()
   {
      CLAY_PROFILE_FUNCTION();

      uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*) s_Data.QuadVertexBufferBase;
      s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

      Flush();
   }

   void Renderer2D::Flush()
   {
      RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
   }

   void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
   {
      DrawQuad({position.x, position.y, 0.0f}, size, color);
   }

   void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
   {
      CLAY_PROFILE_FUNCTION();

      s_Data.QuadVertexBufferPtr->Position = position;
      s_Data.QuadVertexBufferPtr->Color = color;
      s_Data.QuadVertexBufferPtr->TexCoord = {0.0f, 0.0f};
      s_Data.QuadVertexBufferPtr++;

      s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, 0.0f};
      s_Data.QuadVertexBufferPtr->Color = color;
      s_Data.QuadVertexBufferPtr->TexCoord = {1.0f, 0.0f};
      s_Data.QuadVertexBufferPtr++;

      s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f};
      s_Data.QuadVertexBufferPtr->Color = color;
      s_Data.QuadVertexBufferPtr->TexCoord = {1.0f, 1.0f};
      s_Data.QuadVertexBufferPtr++;

      s_Data.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, 0.0f};
      s_Data.QuadVertexBufferPtr->Color = color;
      s_Data.QuadVertexBufferPtr->TexCoord = {0.0f, 1.0f};
      s_Data.QuadVertexBufferPtr++;

      s_Data.QuadIndexCount += 6;

      /* s_Data.TextureShader->SetFloat("u_TilingFactor", 10.0f);
      s_Data.WhiteTexture->Bind();

      glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
      s_Data.TextureShader->SetMat4("u_Transform", transform);

      s_Data.QuadVertexArray->Bind();
      RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
      */
   }

   void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
   {
      DrawQuad({position.x, position.y, 0.0f}, size, texture);
   }

   void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
   {
      CLAY_PROFILE_FUNCTION();
      s_Data.TextureShader->SetFloat4("u_Color", {1.0f, 1.0f, 1.0f, 1.0f});
      s_Data.TextureShader->SetFloat("u_TilingFactor", 10.0f);
      texture->Bind();

      glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
      s_Data.TextureShader->SetMat4("u_Transform", transform);

      s_Data.QuadVertexArray->Bind();
      RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
   }
}