// RuneScape Client
//
// Author: Matthew Knight
// File Name: client.hpp
// Date: 2018-12-28

#include <client.hpp>

#include <player.hpp>

namespace {
    const float loginThresh = 2e8;
    const std::chrono::seconds maxPlayTime = std::chrono::seconds(30);
} // namespace

Client::Client(const cv::Rect& borders, const cv::Mat& frame, std::mutex& mtx)
    : borders(borders)
    , frame(frame)
    , mtx(mtx) {
    std::ifstream accounts("../accounts.csv");

    for (std::string line; std::getline(accounts, line);) {
        char username[80];
        char password[80];

        sscanf(line.c_str(), "%s %s", username, password);
        users.push({username, password});
    }
    // wait for login screen
    cv::Mat login = cv::imread("../images/login.png");
    float thresh = loginThresh;
    while (thresh >= loginThresh) {
        cv::Mat similarity;
        mtx.lock();
        matchTemplate(frame, login, similarity, cv::TM_SQDIFF);
        mtx.unlock();
        thresh = similarity.at<float>(0, 0);
    }

    std::cout << "Finished loading" << std::endl;

    leftClick(50, 495);
    leftClick(40, 60);

    std::cout << "World 301 chosen" << std::endl;

    login_info_t info = users.front();
    users.pop();

    activePlayer = new Player(info, this);
}

void Client::iterate() {
    if (activePlayer->playTime() > maxPlayTime) {
        users.push(activePlayer->getLoginInfo());
        login_info_t info = users.front();
        users.pop();

        delete activePlayer;
        activePlayer = new Player(info, this);
    } else {
        std::cout << activePlayer->playTime().count() << "/"
                  << maxPlayTime.count() << std::endl;
        activePlayer->iterate();
    }
}

void Client::leftClick(int x, int y) {
    mouse.leftClick(cv::Point(borders.x + x, borders.y + y));
}

void Client::type(const std::string& text) { keyboard.type(text); }

void Client::Create(const cv::Rect& borders, const cv::Mat& frame,
                    std::mutex& mtx) {
    std::thread th([&] {
        std::cout << "About to create client" << std::endl;
        Client client(borders, frame, mtx);

        while (true) {
            client.iterate();
        }
    });
    th.detach();
}
