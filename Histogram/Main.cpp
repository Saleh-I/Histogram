#include<opencv2\core.hpp>
#include<opencv2\highgui.hpp>
#include<opencv2\imgcodecs.hpp>
#include<opencv2\imgproc.hpp>

using namespace cv;

class Histogram {
public:
	Mat calc_histogram(Mat scr) {
		Mat hist;
		hist = Mat::zeros(256, 1, CV_32F);
		scr.convertTo(scr, CV_32F);
		double value = 0;
		for (int i = 0; i < scr.rows; i++)
		{
			for (int j = 0; j < scr.cols; j++)
			{
				value = scr.at<float>(i, j);
				hist.at<float>(value) = hist.at<float>(value) + 1;
			}
		}
		return hist;
	}

	void plot_histogram(Mat histogram) {
		Mat histogram_image(400, 512, CV_8UC3, Scalar(0, 0, 0));
		Mat normalized_histogram;
		normalize(histogram, normalized_histogram, 0, 400, NORM_MINMAX, -1, Mat());

		for (int i = 0; i < 256; i++)
		{
			rectangle(histogram_image, Point(2 * i, histogram_image.rows - normalized_histogram.at<float>(i)),
				Point(2 * (i + 1), histogram_image.rows), Scalar(255, 0, 0));
		}

		namedWindow("Histogram", WINDOW_NORMAL);
		imshow("Histogram", histogram_image);
	}
};

void main() {

	Mat img;
	img = imread("airship.jpg", 0);
	Histogram H1;
	Mat hist = H1.calc_histogram(img);
	H1.plot_histogram(hist);

	waitKey(0);

}
