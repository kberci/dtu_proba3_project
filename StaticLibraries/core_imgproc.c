#include "core_imgproc.h"

int GetPixelValue(const IplImage* frame, const CvPoint at, Pixel* out) {
	// CvPoint at -> (column, row)

	int step = frame->widthStep;
	int channels = frame->nChannels;

	*out = pixel(0, channels);
	uchar* data = (uchar*)frame->imageData;

	// for 3-channel (RGB) image: blue->k=0, green->k=1, red->k=2
	for (int k = 0; k < channels; k++) {
		int pixel_value = data[at.x * channels + at.y * step + k];
		out->val.val[k] = pixel_value;
	}

	return EOK;
}

int SetPixelValue(const IplImage* frame, const CvPoint at, const Pixel pix) {

	int step = frame->widthStep;
	int channels = frame->nChannels;
	uchar* data = (uchar*)frame->imageData;

	if (channels > pix.count) return ENOTOK;

	// for 3-channel (RGB) image: blue->k=0, green->k=1, red->k=2
	for (int k = 0; k < channels; k++) {
		data[at.x * channels + at.y * step + k] = (int)pix.val.val[k];
	}

	return EOK;
}

int SetImagePixels(const Pixel color, IplImage* out) {
	uchar* data = (uchar*)out->imageData;

	for (int j = 0; j < out->height; j++) {
		for (int i = 0; i < out->width; i++) {
			SetPixelValue(out, cvPoint(i, j), color);


			for (int k = 0; k < out->nChannels; k++) {
				data[i * out->nChannels + j * out->widthStep + k] = color.val.val[k];
			}
		}
	}

	return EOK;
}