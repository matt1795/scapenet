// Stitch a collection of map screenshots
//
// Author: Matthew Knight
// File Name: stitch-map.cpp
// Date: 2020-01-03
//
// Takes image files, tries to stitch them into groups, outputs large map(s) and
// output summary to specific directory.

#include <opencv2/opencv.hpp>

#include <filesystem>

static const cv::Mat mask { cv::imread("../images/map/mask.png", -1), }

static const std::vector<cv::Mat> unwanted {
    cv::imread("../images/map/yellow_dot.png", -1),
        cv::imread("../images/map/white_dot.png", -1),
        cv::imread("../images/map/flag.png", -1),
        cv::imread("../images/map/cursor.png", -1)
}

void merge(cv::Mat& dst, cv::Mat const& source, cv::Point const& loc) {}

// if merging two then do a regular check and merge, more re
void merge_stitched(std::vector<cv::Mat>& stitched,
                    std::vector<int> const& suggestions) {

	// regular check and merge
	if (suggestions.size() == 2)

	if (suggestions.size() > 2)
	std::vector<bool> match
}

void print_usage() {
    std::cout << "stitch-map usage:" << std::endl
              << "--help          print this" << std::endl
              << "--output-dir    directory to save results to" << std::endl;
}

cv::Mat mask_objects(const cv::Mat& image, const cv::Mat& baseMask,
                     const std::vector<cv::Mat>& objects) {
    cv::Mat newMask = baseMask.clone();

    int count = 0;
    for (auto object : objects) {
        std::vector<cv::Mat> channels(4);
        std::list<cv::Point> points;
        cv::Mat objMask, obj;
        cv::Mat diff(image.rows - object.rows + 1, image.cols - object.cols + 1,
                     CV_32FC1);

        cv::split(object, channels);
        objMask = channels[3];
        channels.pop_back();
        cv::merge(channels, obj);

        for (int i = 0; i < diff.rows; i++) {
            for (int j = 0; j < diff.cols; j++) {
                cv::Mat window(image, cv::Rect(j, i, obj.cols, obj.rows));

                cv::MatConstIterator_<cv::Vec3b> itWin =
                    window.begin<cv::Vec3b>();
                cv::MatConstIterator_<cv::Vec3b> itObj = obj.begin<cv::Vec3b>();
                cv::MatConstIterator_<uint8_t> itMask =
                    objMask.begin<uint8_t>();

                double acc = 0;

                while (itWin != window.end<cv::Vec3b>()) {
                    if (*itMask) {
                        cv::Vec3b d = *itWin - *itObj;
                        for (int n = 0; n < 3; n++) {
                            acc += std::pow(d[n], 2);
                        }
                    }

                    itWin++;
                    itObj++;
                    itMask++;
                }

                diff.at<float>(i, j) = acc;
            }
        }

        cv::normalize(diff, diff, 0, 255, cv::NORM_MINMAX, -1, cv::Mat());

        // search for matches
        for (int i = 0; i < diff.rows; i++) {
            for (int j = 0; j < diff.cols; j++) {
                if (diff.at<float>(i, j) == 0) {
                    points.emplace_back(i, j);
                }
            }
        }

        for (auto point : points) {
            for (int i = 0; i < objMask.rows; i++) {
                for (int j = 0; j < objMask.cols; j++) {
                    if (objMask.at<uint8_t>(i, j) > 0) {
                        newMask.at<uint8_t>(point.x + i, point.y + j) = 0;
                    }
                }
            }
        }

        cv::imwrite(std::to_string(count++) + ".png", diff);
    }

    return newMask;
}

int main(int argc, char* argv[]) {
    std::filesystem::path output_dir{"."};
    std::vector<cv::Mat> images;
    std::vector<cv::Mat> stitched;

    for (auto it = std::begin(argv); it != std::next(argv, argc); ++it) {
        if (*it == "--help") {
            print_usage();
            return 0;
        }

        if (*it == "--output-dir" && it++ != std::next(argv, argc)) {
            output_dir = *it;
            if (!std::filesystem::exists(output_dir)) {
                std::cerr << output_dir " does not exist" << std::endl;
                return -1;
            }

            if (!std::filesystem::is_directory(output_dir)) {
                std::cerr << output_dir << " is not a directory" << std::endl;
                return -1;
            }
        } else {
            // must be an image then
            if (!std::filesystem::exists(std::filesystem::path{*it})) {
                std::cerr << *it << " does not exist" << std::endl;
                return -1;
            }

            images.emplace_back(cv::imread(*it));

            if (images.back().data == NULL) {
                std::cerr << "error reading " << *it << std::endl;
                return -1;
            }
        }
    }

    // go through each image and remove unwanted dots and whatnot
    for (auto& mini_map : images) {
        cv::Mat masked = mask_objects(mini_map, mask, unwanted);
        std::vector<int> matches;

        for (int i = 0; i < stitched.size(); ++i) {
            if (match && overlap > threshold) {
                matches.push_back(i);
                merge(stitched[i], mini_map);
            }
        }

        if (matches.empty())
            stitched.push_back(mini_map);
        else if (matches.size() > 1)
            merge_stitched(stitched, matches);
    }
}
