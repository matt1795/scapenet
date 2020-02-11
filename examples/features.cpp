// Show features of the mini map
//
// Author: Matthew Knight
// File Name: features.cpp
// Date: 2018-12-22

#include <opencv2/opencv.hpp>

#include <iostream>
#include <map>
#include <string>

const std::map<std::string, cv::Ptr<cv::Feature2D>> detectors{
    {"orb", cv::ORB::create()},
    {"brisk", cv::BRISK::create()},
    {"mser", cv::MSER::create()},
    {"agast", cv::AgastFeatureDetector::create()},
    {"fast_feature_detector", cv::FastFeatureDetector::create()},
    {"good_features_to_track", cv::GFTTDetector::create()},
    {"simple_blob", cv::SimpleBlobDetector::create()},
    {"kaze", cv::KAZE::create()},
    {"akaze", cv::AKAZE::create()}};

cv::Mat maskObjects(const cv::Mat& image, const cv::Mat& baseMask,
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

int main() {
    cv::Mat map = cv::imread("../images/map/stitching/1600.png");
    cv::Mat mask = cv::imread("../images/map/stitching/map-mask.png",
                              cv::IMREAD_GRAYSCALE);

    cv::Mat yellowDot = cv::imread("../images/map/yellow_dot.png", -1);
    cv::Mat whiteDot = cv::imread("../images/map/white_dot.png", -1);
    cv::Mat flag = cv::imread("../images/map/flag.png", -1);

    cv::Mat newMask = maskObjects(map, mask, {yellowDot, whiteDot, flag});
    for (auto detector : detectors) {
        cv::Mat out;
        std::vector<cv::KeyPoint> keypoints;

        detector.second->detect(map, keypoints, newMask);
        cv::drawKeypoints(map, keypoints, out);

        cv::imwrite(detector.first + ".png", out);
    }

    cv::imwrite("output_mask.png", newMask);
}
