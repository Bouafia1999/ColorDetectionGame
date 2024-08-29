#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>

class Circle {
public:
    Circle(int imageWidth, int imageHeight) {
        x = std::rand() % imageWidth;
        y = 0;
        radius = 10;
    }

    void fall() {
        y += 4;
        // Les cercles tombent deux fois plus vite
    }

    bool isOutOfScreen(int imageHeight) {
        return y - radius > imageHeight; 
        // Utilisez "- radius" pour vérifier que tout le cercle est hors de l'écran.
    }

    int x;
    int y;
    int radius;
};

int main() {
    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cerr << "Erreur : la caméra ne peut pas être ouverte." << std::endl;
        return -1;
    }

    std::srand(static_cast<unsigned>(std::time(0)));

    int imageWidth = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int imageHeight = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    cv::Mat redMask(imageHeight, imageWidth, CV_8UC1, cv::Scalar(0));

    std::vector<Circle> circles;
    int numCircles = 20;
    int score = 0;
    bool isGameOver = false;

    for (int i = 0; i < numCircles; i++) {
        circles.push_back(Circle(imageWidth, imageHeight));
    }

    while (!isGameOver) {
        cv::Mat frame;
        cap >> frame;

        if (frame.empty()) {
            std::cerr << "Erreur : la capture d'image a échoué." << std::endl;
            break;
        }

        for (auto it = circles.begin(); it != circles.end();) {
            it->fall();

            cv::inRange(frame, cv::Scalar(0, 0, 150), cv::Scalar(100, 100, 255), redMask);

            bool isTouchingRed = false;
            for (int dx = -it->radius; dx <= it->radius; dx++) {
                for (int dy = -it->radius; dy <= it->radius; dy++) {
                    int x = it->x + dx;
                    int y = it->y + dy;

                    if (x >= 0 && x < imageWidth && y >= 0 && y < imageHeight) {
                        if (redMask.at<uchar>(y, x) != 0) {
                            isTouchingRed = true;
                            break;
                        }
                    }
                }

                if (isTouchingRed) {
                    break;
                }
            }

            if (isTouchingRed) {
                it = circles.erase(it);
                score++;
                circles.push_back(Circle(imageWidth, imageHeight));
            }
            else {
                if (it->isOutOfScreen(imageHeight)) {
                    isGameOver = true;
                    break; // Sortez immédiatement de la boucle pour éviter de travailler avec un itérateur invalide.
                }
                ++it;
            }
        }

        for (const auto& circle : circles) {
            cv::circle(frame, cv::Point(circle.x, circle.y), circle.radius, cv::Scalar(0, 255, 0), -1);
        }

        std::string scoreText = "Score: " + std::to_string(score);
        cv::putText(frame, scoreText, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);

        if (isGameOver) {
            cv::putText(frame, "Game Over", cv::Point(imageWidth / 4, imageHeight / 2), cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(0, 0, 255), 3);
            cv::imshow("Circles and Color Detection", frame);
            cv::waitKey(5000); // Attendez 5 secondes
            break;
        }

        cv::imshow("Circles and Color Detection", frame);

        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
