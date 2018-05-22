#pragma once

#include "BitMap.h"
#include "stdafx.h"
#include "bitmap_image.hpp"
#include <vector>
#include <iomanip>
#include <fstream>
#include <random>


using namespace std;

class Bitmap {

private:

	int colorRGB = 0;				// ��� ��������� ������ �����
	vector<unsigned int> object;	// ��������� �������
	bitmap_image *image;			// �����������
	bitmap_image::rgb_t white;		// ����� ����
	bitmap_image::rgb_t colorPixel; // ���� �������

public:

	Bitmap() {

		white.blue = 255;
		white.green = 255;
		white.red = 255;

		colorPixel.blue = 10;
		colorPixel.green = 200;
		colorPixel.red = 0;
	};

	/*		�������� �����������	*/
	bool loadImage(string path) {

		image = new bitmap_image(path);

		if (!image) {

			cout << "Error - Failed to open";
			return false;
		}
		return true;
	}
	/*		���������� �����������		*/
	bool saveImage(string path) {

		image->save_image(path);
		return true;
	}

	/*	���������� ������� �������� � Objects.txt ����	*/
	void getObject() {

		ofstream file("Objects.txt");

		file << setw(10) << "����� �������"
			 << setw(20) << "������� �������" << endl << endl;

		for (unsigned int i = 0; i < object.size(); i++) {

			file << setw(5) << i
				 << setw(20) << object[i] << endl;
		}
		file.close();
	}

	/*			����� �������� �� ���������			*/
	void processing() {

		unsigned int i = 0;
		for (unsigned int x = 1; x < image->width() - 1; x++) {
			for (unsigned int y = 1; y < image->height() - 1; y++) {

				// ���� ������� ������� ������ �����, �������� ��� � ������� ������  objectSearch()
				if (image->get_pixel(x, y) == white) {

					object.push_back(i);
					generationColor();
					objectSearch(x, y);

				}
			}
		}
	}
	/*			����� ������  �������			 */
	void objectSearch(unsigned x, unsigned y) {

		// ������ ���� �������� �������, ��������� ����� (4-���������)
		image->set_pixel(x, y, colorPixel); 
		bitmap_image::rgb_t pixel = image->get_pixel(x, y);
		object[object.size() - 1] ++;

		if (image->get_pixel(x - 1, y) == white) {	// ���� ������� ����� �����

			image->set_pixel(x - 1, y, pixel);
			objectSearch(x - 1, y);

		}
		if (image->get_pixel(x + 1, y) == white) {	// ���� ������� ������ �����

			image->set_pixel(x + 1, y, pixel);
			objectSearch(x + 1, y);

		}
		if (image->get_pixel(x, y - 1) == white) {	// ���� ������� ������ �����

			image->set_pixel(x, y - 1, pixel);
			objectSearch(x, y - 1);

		}
		if (image->get_pixel(x, y + 1) == white) {	// ���� ������� ����� �����

			image->set_pixel(x, y + 1, pixel);
			objectSearch(x, y + 1);

		}
	}

	/*		��������� ������ �����		*/
	void generationColor() {

		random_device rd;
		mt19937 mt(rd());
		uniform_real_distribution<double> random(0, 255);

		switch (colorRGB){

		case(0):
			colorRGB++;
			colorPixel.red = random(mt);
			break;
		case(1):
			colorRGB++;
			colorPixel.blue = random(mt);
		case(2):
			colorRGB = 0;
			colorPixel.green = random(mt);
			break;
		default:
			break;

		}
	}
};
