#pragma once
#include "Globals.hpp"
#include "Vec3.hpp"

struct cTexture {
  cTexture();
  ~cTexture();

  bool Load(char const*const filename,int const type = GL_RGBA,int const wraps = GL_REPEAT,
	  int const wrapt = GL_REPEAT,
	    int const magf = GL_NEAREST,int const minf = GL_NEAREST,bool const mipmap = false);
  GLuint GetID() const;
  int GetWidth_W() const { return widthW; }
  int GetHeight_W() const { return heightW; }
  void Draw(float const texX0, float const texY0, float const texX1, float const texY1,
			Vec3 screen0, Vec3 screen1) const;

private:
  GLuint id;
  int widthW;
  int heightW;
};
