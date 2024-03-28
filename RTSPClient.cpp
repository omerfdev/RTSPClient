#include <iostream>
#include <opencv2/opencv.hpp>

// RTSP iletişimi ve video yayını işlemlerini gerçekleştiren sınıf
class RTSPClient {
private:
    cv::VideoCapture capture; // Video yakalama nesnesi
    std::string rtspUrl; // RTSP URL'si

public:
    // Kurucu fonksiyon
    RTSPClient(const std::string& url) : rtspUrl(url) {}

    // RTSP yayınına bağlanma işlemi
    bool connect() {
        capture.open(rtspUrl);
        return capture.isOpened();
    }

    // Video akışından bir kare alıp döndüren işlev
    cv::Mat getNextFrame() {
        cv::Mat frame;
        capture >> frame;
        return frame;
    }

    // RTSP yayınına bağlantıyı kapatma işlemi
    void disconnect() {
        capture.release();
    }
};

int main() {
    std::string rtspUrl = "rtsp://example.com/live/stream";
    RTSPClient client(rtspUrl);

    if (!client.connect()) {
        std::cerr << "Error: Failed to connect to RTSP stream" << std::endl;
        return -1;
    }

    cv::namedWindow("Live Stream", cv::WINDOW_NORMAL);

    while (true) {
        cv::Mat frame = client.getNextFrame();

        if (frame.empty()) {
            std::cerr << "Error: Failed to receive frame from RTSP stream" << std::endl;
            break;
        }

        cv::imshow("Live Stream", frame);

        if (cv::waitKey(25) == 'q') {
            break;
        }
    }

    cv::destroyAllWindows();
    client.disconnect();

    return 0;
}
