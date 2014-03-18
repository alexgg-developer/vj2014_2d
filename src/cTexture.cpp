
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

	width  = img->getWidth();
	height = img->getHeight();

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D,id);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,wraps);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,wrapt);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,magf);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,minf);

	if(!mipmap)	{
		glTexImage2D(GL_TEXTURE_2D,0,components,width,height,0,type,
					 GL_UNSIGNED_BYTE,img->getPixels());
	} else {
		gluBuild2DMipmaps(GL_TEXTURE_2D,components,width,height,type,
						  GL_UNSIGNED_BYTE,img->getPixels());
	}

	return true;
}
GLuint cTexture::GetID() const {
	return id; }
std::tuple<int,int> cTexture::GetSize() const {
	return std::make_tuple(width, height); }

void cTexture::Draw(float const texX0, float const texY0, float const texX1, float const texY1,
					float const verX0, float const verY0, float const verX1, float const verY1) const {
	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, GetID());
	glBegin(GL_QUADS);	
		glTexCoord2f(texX0, texY0);	glVertex2i(verX0, verY0);
		glTexCoord2f(texX1, texY0);	glVertex2i(verX1, verY0);
		glTexCoord2f(texX1, texY1);	glVertex2i(verX1, verY1);
		glTexCoord2f(texX0, texY1);	glVertex2i(verX0, verY1);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}