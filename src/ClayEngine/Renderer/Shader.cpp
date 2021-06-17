//
// Created by quantum on 6/16/21.
//

#include "Shader.h"

namespace Clay
{
   Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
   {
      // Create an empty vertex shader handle
      GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

      // Send the vertex shader source code to GL
      // Note that std::string's .c_str is NULL character terminated.
      const GLchar *source = (const GLchar *) vertexSrc.c_str();
      glShaderSource(vertexShader, 1, &source, 0);

      // Compile the vertex shader
      glCompileShader(vertexShader);

      GLint isCompiled = 0;
      glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
      if (isCompiled == GL_FALSE)
      {
         GLint maxLength = 0;
         glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

         // The maxLength includes the NULL character
         std::vector<GLchar> infoLog(maxLength);
         glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

         // We don't need the shader anymore.
         glDeleteShader(vertexShader);

         CLAY_LOG_ERROR("Vertex Shader Compilation Failed: ");
         CLAY_LOG_ERROR("{0}", infoLog.data());

         return;
      }

      // Create an empty fragment shader handle
      GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

      // Send the fragment shader source code to GL
      // Note that std::string's .c_str is NULL character terminated.
      source = (const GLchar *) fragmentSrc.c_str();
      glShaderSource(fragmentShader, 1, &source, 0);

      // Compile the fragment shader
      glCompileShader(fragmentShader);

      glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
      if (isCompiled == GL_FALSE)
      {
         GLint maxLength = 0;
         glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

         // The maxLength includes the NULL character
         std::vector<GLchar> infoLog(maxLength);
         glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

         // We don't need the shader anymore.
         glDeleteShader(fragmentShader);
         // Either of them. Don't leak shaders.
         glDeleteShader(vertexShader);

         CLAY_LOG_ERROR("Fragment Shader Compilation Failed: ");
         CLAY_LOG_ERROR("{0}", infoLog.data());

         return;
      }

      // Vertex and fragment shaders are successfully compiled.
      // Now time to link them together into a program.
      // Get a program object.
      _rendererId = glCreateProgram();
      GLuint program = _rendererId;

      // Attach our shaders to our program
      glAttachShader(program, vertexShader);
      glAttachShader(program, fragmentShader);

      // Link our program
      glLinkProgram(program);

      // Note the different functions here: glGetProgram* instead of glGetShader*.
      GLint isLinked = 0;
      glGetProgramiv(program, GL_LINK_STATUS, (int *) &isLinked);
      if (isLinked == GL_FALSE)
      {
         GLint maxLength = 0;
         glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

         // The maxLength includes the NULL character
         std::vector<GLchar> infoLog(maxLength);
         glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

         CLAY_LOG_ERROR("Shader Linking Failed: ");
         CLAY_LOG_ERROR("{0}", infoLog.data());

         // We don't need the program anymore.
         glDeleteProgram(program);
         // Don't leak shaders either.
         glDeleteShader(vertexShader);
         glDeleteShader(fragmentShader);


         return;
      }
   }

   Shader::~Shader()
   {
      glDeleteProgram(_rendererId);
   }

   void Shader::Bind()
   {
      glUseProgram(_rendererId);
   }

   void Shader::Unbind()
   {
      glUseProgram(0);
   }
}