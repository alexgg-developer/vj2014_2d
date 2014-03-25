
#include "cTexture.hpp"
#include "external/corona.h"
#include "Globals.hpp"

cTexture::cTexture(void) { }

cTexture::~cTexture(void) { }

bool cTexture::Load(char const*const filename,int const type,int const wraps,int const wrapt,int const magf,
					int const minf,bool const mipmap) {
	corona::Image* img;
	int components;

	img = corona::OpenImage(filename);
	if(type==GL_RGB) {
		//img = corona::OpenImage(filename,corona::PF_R8G8B8);
		components = 3;
	}
	else if(type==GL_RGBA) {
		//img = corona::OpenImage(filename,corona::PF_R8G8B8A8);
		components = 4;
	}
	else return false;

	if(img==NULL) return false;

	widthW  = img->getWidth();
	heightW = img->getHeight();

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D,id);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,wraps);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,wrapt);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,magf);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,minf);

	if(!mipmap)	{
		glTexImage2D(GL_TEXTURE_2D,0,components,widthW,heightW,0,type,
					 GL_UNSIGNED_BYTE,img->getPixels());
	} else {
		gluBuild2DMipmaps(GL_TEXTURE_2D,components,widthW,heightW,type,
						  GL_UNSIGNED_BYTE,img->getPixels());
	}

	return true;
}
GLuint cTexture::GetID() const {
	return id; }

void cTexture::Draw(cFrame const& frame,
	  Vec3 const& screen0, Vec3 const& screen1) const {
  this->Draw(frame.mBegin, frame.mEnd, screen0, screen1);
}
void cTexture::Draw(Vec3 const& tex0, Vec3 const& tex1,
					Vec3 const& screen0, Vec3 const& screen1) const {
	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, GetID());
	glBegin(GL_QUADS);	
		glTexCoord2f(tex0.x, tex0.y);	glVertex2i(screen0.x, screen0.y);
		glTexCoord2f(tex1.x, tex0.y);	glVertex2i(screen1.x, screen0.y);
		glTexCoord2f(tex1.x, tex1.y);	glVertex2i(screen1.x, screen1.y);
		glTexCoord2f(tex0.x, tex1.y);	glVertex2i(screen0.x, screen1.y);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void cTexture::drawAlternative(Vec3 const& tex0, Vec3 const& tex1,
	Vec3 const& screen0, Vec3 const& screen1) const {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GetID());
	glBegin(GL_QUADS);
	glTexCoord2f(tex0.x, tex1.y);	glVertex2i(screen0.x, screen0.y);
	glTexCoord2f(tex1.x, tex1.y);	glVertex2i(screen1.x, screen0.y);
	glTexCoord2f(tex1.x, tex0.y);	glVertex2i(screen1.x, screen1.y);
	glTexCoord2f(tex0.x, tex0.y);	glVertex2i(screen0.x, screen1.y);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
