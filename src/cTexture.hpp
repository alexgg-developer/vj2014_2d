#pragma once
#include "Globals.hpp"
#include <tuple>

struct cTexture {
  cTexture();
  ~cTexture();

  bool Load(char const*const filename,int const type = GL_RGBA,int const wraps = GL_REPEAT,
	  int const wrapt = GL_REPEAT,
	    int const magf = GL_NEAREST,int const minf = GL_NEAREST,bool const mipmap = false);
  GLuint GetID() const;
  std::tuple<int,int> GetSize() const;
  void Draw(float const texX0, float const texY0, float const texX1, float const texY1,
			float const verX0, float const verY0, float const verX1, float const verY1) const;

private:
  GLuint id;
  int width;
  int height;
};
