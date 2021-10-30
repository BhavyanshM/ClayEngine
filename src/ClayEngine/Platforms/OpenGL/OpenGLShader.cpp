#include "OpenGLShader.h"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

namespace Clay
{

   static GLenum ShaderTypeFromString(const std::string& type)
   {
      if(type == "vertex")
         return GL_VERTEX_SHADER;
      if(type == "fragment" || type == "pixel")
         return GL_FRAGMENT_SHADER;
      if(type == "geometry")
         return GL_GEOMETRY_SHADER;

      CLAY_LOG_ERROR("Unknown Shader Type!");
      return 0;
   }

   OpenGLShader::OpenGLShader(const std::string& filePath)
   {
      CLAY_PROFILE_FUNCTION();
      std::string shaderSrc = ReadFile(filePath);
      auto shaderSources = PreProcess(shaderSrc);
      Compile(shaderSources);

      auto lastSlash = filePath.find_last_of("/\\");
      lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
      auto lastDot = filePath.rfind('.');
      auto count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;
      _name = filePath.substr(lastSlash, count);
   }

   OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc, const std::string& geometrySrc) : _name(name)
   {
      CLAY_PROFILE_FUNCTION();
      std::unordered_map<GLenum, std::string> sources;
      sources[GL_VERTEX_SHADER] = vertexSrc;
      sources[GL_FRAGMENT_SHADER] = fragmentSrc;
      sources[GL_GEOMETRY_SHADER] = geometrySrc;
      Compile(sources);
   }

   OpenGLShader::~OpenGLShader()
   {
      CLAY_PROFILE_FUNCTION();
      glDeleteProgram(_rendererId);
   }

   std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
   {
      CLAY_PROFILE_FUNCTION();
      std::unordered_map<GLenum, std::string> shaderSources;

      const char* typeToken = "#type";
      size_t typeTokenLength = strlen(typeToken);
      size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
      while (pos != std::string::npos)
      {
         size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
         size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
         std::string type = source.substr(begin, eol - begin);

         size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
         pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line

         shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
      }

      return shaderSources;
   }

   std::string OpenGLShader::ReadFile(const std::string& filePath)
   {
      CLAY_PROFILE_FUNCTION();
      std::string result;
      std::ifstream in(filePath, std::ios::in | std::ios::binary);
      if(in)
      {
         in.seekg(0, std::ios::end);
         result.resize(in.tellg());
         in.seekg(0, std::ios::beg);
         in.read(&result[0], result.size());
         in.close();
      }else
      {
         CLAY_LOG_ERROR("Shader File Not Found. {0}", filePath.c_str());
      }
      return result;
   }

   void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
   {
      CLAY_PROFILE_FUNCTION();
      GLuint program = glCreateProgram();
      std::vector<GLenum> glShaderIDs(shaderSources.size());

      for(auto& kv : shaderSources)
      {
         GLenum type = kv.first;
         const std::string& sourceStr = kv.second;

         GLuint shader = glCreateShader(type);
         const GLchar *source = (const GLchar *) sourceStr.c_str();
         glShaderSource(shader, 1, &source, 0);
         glCompileShader(shader);

         GLint isCompiled = 0;
         glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
         if (isCompiled == GL_FALSE)
         {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
            glDeleteShader(shader);

            CLAY_LOG_ERROR("Shader Compilation Failed: ");
            CLAY_LOG_ERROR("{0}", infoLog.data());
            break;
         }

         glAttachShader(program, shader);
         glShaderIDs.push_back(shader);
      }

      glLinkProgram(program);

      GLint isLinked = 0;
      glGetProgramiv(program, GL_LINK_STATUS, (int *) &isLinked);
      if (isLinked == GL_FALSE)
      {
         GLint maxLength = 0;
         glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

         std::vector<GLchar> infoLog(maxLength);
         glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

         CLAY_LOG_ERROR("Shader Linking Failed: ");
         CLAY_LOG_ERROR("{0}", infoLog.data());

         glDeleteProgram(program);

         for(auto id : glShaderIDs)
            glDeleteShader(id);

         return;
      }
      for(auto id : glShaderIDs)
         glDetachShader(program, id);

      _rendererId = program;
   }

   void OpenGLShader::Bind() const
   {
      CLAY_PROFILE_FUNCTION();
      glUseProgram(_rendererId);
   }

   void OpenGLShader::Unbind() const
   {
      CLAY_PROFILE_FUNCTION();
      glUseProgram(0);
   }

   void OpenGLShader::UploadUniformInt(const std::string& name, int value)
   {
      GLint location = glGetUniformLocation(_rendererId, name.c_str());
      glUniform1i(location, value);
   }

   void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
   {
      GLint location = glGetUniformLocation(_rendererId, name.c_str());
      glUniform1f(location, value);
   }

   void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
   {
      GLint location = glGetUniformLocation(_rendererId, name.c_str());
      glUniform2f(location, value.x, value.y);
   }

   void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
   {
      GLint location = glGetUniformLocation(_rendererId, name.c_str());
      glUniform3f(location, value.x, value.y, value.z);
   }

   void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
   {
      GLint location = glGetUniformLocation(_rendererId, name.c_str());
      glUniform4f(location, value.x, value.y, value.z, value.w);
   }

   void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
   {
      GLint location = glGetUniformLocation(_rendererId, name.c_str());
      glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
   }

   void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
   {
      GLint location = glGetUniformLocation(_rendererId, name.c_str());
      glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
   }

   void OpenGLShader::UploadUniformIntArray(const std::string& name, int *values, uint32_t count)
   {
      GLint location = glGetUniformLocation(_rendererId, name.c_str());
      glUniform1iv(location, count, values);
   }

   void OpenGLShader::UploadUniformMat4Array(const std::string& name, const std::vector<glm::mat4>& values, uint32_t count)
   {
      GLint location = glGetUniformLocation(_rendererId, name.c_str());
      glUniformMatrix4fv(location, count, GL_FALSE, glm::value_ptr(values[0]));
   }

   void OpenGLShader::SetFloat(const std::string& name, float value)
   {
      CLAY_PROFILE_FUNCTION();
      UploadUniformFloat(name, value);
   }

   void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
   {
      CLAY_PROFILE_FUNCTION();
      UploadUniformFloat3(name, value);
   }

   void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
   {
      CLAY_PROFILE_FUNCTION();
      UploadUniformFloat4(name, value);
   }

   void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
   {
      CLAY_PROFILE_FUNCTION();
      UploadUniformMat4(name, value);
   }

   void OpenGLShader::SetInt(const std::string& name, int value)
   {
      CLAY_PROFILE_FUNCTION();
      UploadUniformInt(name, value);
   }

   void OpenGLShader::SetIntArray(const std::string& name, int *values, uint32_t count)
   {
      CLAY_PROFILE_FUNCTION();
      UploadUniformIntArray(name, values, count);
   }

   void OpenGLShader::SetMat4Array(const std::string& name, const std::vector<glm::mat4>& values, uint32_t count)
   {
      CLAY_PROFILE_FUNCTION();
      UploadUniformMat4Array(name, values, count);
   }
}