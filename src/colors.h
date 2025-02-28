#ifndef COLORS_H
#define COLORS_H

#include <opencv2/opencv.hpp>

// Colori di base
const cv::Scalar BLACK      (0, 0, 0);
const cv::Scalar WHITE      (255, 255, 255);
const cv::Scalar RED        (0, 0, 255);
const cv::Scalar GREEN      (0, 255, 0);
const cv::Scalar BLUE       (255, 0, 0);
const cv::Scalar CYAN       (255, 255, 0);
const cv::Scalar MAGENTA    (255, 0, 255);
const cv::Scalar YELLOW     (0, 255, 255);
const cv::Scalar GRAY       (128, 128, 128);

// Sfumature di Grigio
const cv::Scalar LIGHT_GRAY (192, 192, 192);
const cv::Scalar DARK_GRAY  (64, 64, 64);
const cv::Scalar SILVER     (192, 192, 192);
const cv::Scalar DIM_GRAY   (105, 105, 105);

// Colori pastello e tenui
const cv::Scalar LIGHT_BLUE   (173, 216, 230);
const cv::Scalar LIGHT_GREEN  (144, 238, 144);
const cv::Scalar LIGHT_PINK   (255, 182, 193);
const cv::Scalar LIGHT_YELLOW (255, 255, 224);

// Colori accesi e intensi
const cv::Scalar ORANGE      (0, 165, 255);
const cv::Scalar BROWN       (42, 42, 165);
const cv::Scalar GOLD        (0, 215, 255);
const cv::Scalar VIOLET      (238, 130, 238);
const cv::Scalar TURQUOISE   (208, 224, 64);
const cv::Scalar INDIGO      (130, 0, 75);

#endif // COLORS_H
