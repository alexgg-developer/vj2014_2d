#include "cData.hpp"

cData::cData(void) {}
cData::~cData(void){}

int cData::GetID(int img)
{
	return texture[img].GetID();
}

std::tuple<int,int> cData::GetSize(int img) {
	return texture[img].GetSize();
}

bool cData::LoadImage(int img, char *filename, int type)
{
	int res;

	res = texture[img].Load(filename,type);
	if(!res) return false;

	return true;
}