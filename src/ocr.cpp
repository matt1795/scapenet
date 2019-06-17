// first test with ocr
//

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/text.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
	std::vector<cv::Rect> components;
	std::vector<std::string> texts;
	std::vector<float> confidence;

	cv::Mat image = cv::imread(argv[1]);

	if (image.empty()) {
		std::cout << "image is empty" << std::endl;
		exit(1);
	}
	std::string text;
	auto ocr = cv::text::OCRTesseract::create(NULL, NULL, NULL, 3, 7);
	ocr->setWhiteList("0123456789");
	ocr->run(image, text, &components, &texts, &confidence);

	std::cout << text << std::endl;

	// make sure that the length is the same for the above vectors
	if (
		components.size() != texts.size()
		|| texts.size() != confidence.size()
		|| confidence.size() != components.size()
	) {
		std::cout << "The vectors do not match in size" << std::endl;
		exit(1);
	}

	for (int i = 0; i < components.size(); i++) {
		std::cout << components[i] << ", " << texts[i] << ", " << confidence[i] << std::endl;
		cv::rectangle(image, components[i], cv::Scalar(0, 0, 255));
		cv::imwrite("output.png", image);
	}
}
