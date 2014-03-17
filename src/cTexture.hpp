#pragma once

#include "Globals.hpp"
#include <tuple>

struct cTexture {
  cTexture();
  ~cTexture();

  bool Load(char *filename,int type = GL_RGBA,int wraps = GL_REPEAT,int wrapt = GL_REPEAT,
	    int magf = GL_NEAREST,int minf = GL_NEAREST,bool mipmap = false);
  GLuint GetID() const;
  std::tuple<int,int> GetSize() const;

private:
  GLuint id;
  int width;
  int height;
};
