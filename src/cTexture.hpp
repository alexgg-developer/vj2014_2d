#pragma once
#include "Globals.hpp"
#include "Vec3.hpp"
#include "cFrame.hpp"

/// A texture is an atlas
struct cTexture {
  cTexture();
  ~cTexture();

  bool Load(char const*const filename,int const type = GL_RGBA,int const wraps = GL_REPEAT,
	    int const wrapt = GL_REPEAT,
	    int const magf = GL_NEAREST,int const minf = GL_NEAREST,bool const mipmap = false);
  GLuint GetID() const;
  int GetWidth_W() const { return widthW; }
  int GetHeight_W() const { return heightW; }
  void Draw(Vec3 const& tex0, Vec3 const& tex1,
	    Vec3 const& screen0, Vec3 const& screen1) const;
  void Draw(cFrame const& frame,
	    Vec3 const& screen0, Vec3 const& screen1) const;
  void drawAlternative(Vec3 const& tex0, Vec3 const& tex1,
	  Vec3 const& screen0, Vec3 const& screen1) const;

private:
  GLuint id;
  int widthW;
  int heightW;
};
