#include "ofxYolo2.h"




std::vector<std::string> objects_names_from_file(std::string const filename) {
	std::ifstream file(filename);
	std::vector<std::string> file_lines;
	if (!file.is_open()) return file_lines;
	for (std::string line; file >> line;) file_lines.push_back(line);
	std::cout << "object names loaded \n";
	return file_lines;
}



std::vector<bbox_t> ofxYolo2::detect(ofPixels& pixels) {

	image_t convertedImage = convert(pixels);
	std::vector<bbox_t> results = detector->detect(convertedImage);

	free(convertedImage.data);
	return results;
}

void ofxYolo2::setup() {

	string config = ofToDataPath("yolo-voc.cfg");
	string weights = ofToDataPath("yolo-voc.weights");
	string names = ofToDataPath("voc.names");

	detector = new Detector(config, weights);
	objectNames = objects_names_from_file(names);
}


std::string ofxYolo2::getName(int index) {
	if(index >= objectNames.size()) return "";
	return objectNames[index];
}


image_t ofxYolo2::convert(ofPixels & pix)
{
	unsigned char *data = (unsigned char *)pix.getData();
	int h = pix.getHeight();
	int w = pix.getWidth();
	int c = pix.getNumChannels();
	int step = w * c;
	image_t im;// = make_image_custom(w, h, c);
	int i, j, k, count = 0;;

	im.data = (float *)calloc(h*w*c, sizeof(float));
	im.c = c;
	im.h = h;
	im.w = w;

	for (k = 0; k < c; ++k) {
		for (i = 0; i < h; ++i) {
			for (j = 0; j < w; ++j) {
				im.data[count++] = data[i*step + j*c + k] / 255.;
			}
		}
	}

	return im;
}



//
//ofPixels ofxYolo2::convert(image_t & im)
//{
//	unsigned char *data = (unsigned char*)calloc(im.w*im.h*im.c, sizeof(char));
//	int i, k;
//	for (k = 0; k < im.c; ++k) {
//		for (i = 0; i < im.w*im.h; ++i) {
//			data[i*im.c + k] = (unsigned char)(255 * im.data[i + k*im.w*im.h]);
//		}
//	}
//
//	ofPixels pix;
//	pix.setFromPixels(data, im.w, im.h, im.c);
//	return pix;
//}


