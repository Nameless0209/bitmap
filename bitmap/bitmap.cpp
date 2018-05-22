// bitmap.cpp: определяет точку входа для консольного приложения.
//
#include "BitMap.h"
#include <string>

using namespace std;

int main(){

	Bitmap bitmap;
	bitmap.loadImage("image.bmp");
	bitmap.processing();
	bitmap.saveImage("newImage.bmp");
	bitmap.getObject();

    return 0;
}

