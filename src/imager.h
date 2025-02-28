#ifndef IMAGER_H_
#define IMAGER_H_

#pragma once
#include <iostream>
#include <cmath>
#include "pop.h"
#include "popworld.h"
#include "colors.h"
#include <opencv2/opencv.hpp>

extern Field field;
extern PopsSpv spv_;
extern const Params &p;
class Imager
{
private:
    int SIZE = p.size;                      // Dimensione della griglia
    int CELL_SIZE = p.cellSize; // Dimensione delle celle


    cv::Mat img;

public:
    Imager() : img( CELL_SIZE* 128, CELL_SIZE * 128, CV_8UC3, cv::Scalar(255, 255, 255))
    {

        std::cout << "Creating IMAGER with size default " << SIZE << std::endl;
        //drawGrid();
    } // Bianco

    Imager(int size) : img(CELL_SIZE * size, CELL_SIZE * size, CV_8UC3, cv::Scalar(255, 255, 255))
    {
        std::cout << "Creating IMAGER with size " << size << std::endl;
        SIZE = size;
        drawGrid();
    } // Bianco

    void UpdateDraw(int run)
    {
        FillTemperature();
        drawPops();
        //save
        savePNG(run);

    }
    // Disegna la griglia
    void drawGrid()
    {
        for (int i = 0; i <= SIZE; ++i)
        {
            int pos = i * CELL_SIZE;
            cv::line(img, cv::Point(pos, 0), cv::Point(pos, CELL_SIZE * SIZE), cv::Scalar(200, 200, 200), 1); // Linee verticali
            cv::line(img, cv::Point(0, pos), cv::Point(CELL_SIZE * SIZE, pos), cv::Scalar(200, 200, 200), 1); // Linee orizzontali
        }
    }

    void drawPops()
    {
        for (int x = 0; x < SIZE; ++x)
        {
            for (int y = 0; y < SIZE; ++y)
            {
                
                if (field.planet_[x][y].occupy)
                {
                   int genColor= spv_.alivePops_[field.planet_[x][y].id]->GeneticColor();
                    drawCell(x,y,
                        RGBFromInt(genColor),  //color pop
                        ORANGE,  //border color pop
                        3,            //border thickness
                        RGBFromInt(genColor),  //outer border color
                        BLACK,  //vector color
                        x+y                         //vector angle
                     );
                     
                }
            }
        }
    }


// Funzione per disegnare una cella con cerchio, bordo e vettore orientato
void drawCell( int x, int y,  
                cv::Scalar fillColor,
                cv::Scalar borderColor,
                int borderThickness, 
                cv::Scalar outerCircleColor, 
                cv::Scalar vectorColor, 
                float angleDeg) {
    
    // Centro della cella
    int centerX = x * CELL_SIZE + CELL_SIZE / 2;
    int centerY = y * CELL_SIZE + CELL_SIZE / 2;
    cv::Point center(centerX, centerY);
    
    // Raggio del cerchio principale (adattato alla cella)
    int radius = CELL_SIZE / 3;

    // Disegna il cerchio principale
    cv::circle(img, center, radius, fillColor, cv::FILLED);

    // Disegna il bordo del cerchio
    //cv::circle(img, center, radius, borderColor, borderThickness);

    // Disegna un cerchio leggermente più grande attorno
    cv::circle(img, center, radius + borderThickness * 2, outerCircleColor, borderThickness);

    // Calcola il vettore (linea orientata) con angolo specifico
    float angleRad = angleDeg * CV_PI / 180.0;  // Conversione in radianti
    int vectorLength = CELL_SIZE*0.7;// /3;  // Lunghezza del vettore (poco meno di metà cella)
    cv::Point vectorEnd(
        center.x + static_cast<int>(vectorLength * cos(angleRad)),
        center.y - static_cast<int>(vectorLength * sin(angleRad))  // Y invertito per OpenCV
    );

    // Disegna il vettore
    cv::line(img, center, vectorEnd, vectorColor, 2);
}

    // Disegna un cerchio al centro della cella (x, y) se è "piena"
    void drawCircle(int x, int y, bool filled)
    {
        if (filled)
        {
            int centerX = x * CELL_SIZE + CELL_SIZE / 2;
            int centerY = y * CELL_SIZE + CELL_SIZE / 2;
            cv::circle(img, cv::Point(centerX, centerY), CELL_SIZE / 2.5, cv::Scalar(0, 0, 0), -1); // Nero
        }
    }

    cv::Vec3b getTemperatureColor(int temp)
    {
        // Definizione di intervalli chiave
        if (temp <= 0)
        {
            return cv::Vec3b(255, 0, 0); // Blu scuro per temperature basse
        }
        else if (temp <= 10)
        {
            float factor = temp / 10.0f;
            return cv::Vec3b(255, 255 * factor, 0); // Da blu a ciano
        }
        else if (temp <= 20)
        {
            float factor = (temp - 10) / 10.0f;
            return cv::Vec3b(255 * (1 - factor), 255, 0); // Da ciano a verde
        }
        else if (temp <= 30)
        {
            float factor = (temp - 20) / 10.0f;
            return cv::Vec3b(0, 255, 255 * factor); // Da verde a giallo
        }
        else if (temp <= 40)
        {
            float factor = (temp - 30) / 10.0f;
            return cv::Vec3b(0, 255 * (1 - factor), 255); // Da giallo a rosso
        }
        else
        {
            return cv::Vec3b(0, 0, 255); // Rosso scuro per temperature alte
        }
    }

    void FillTemperature()
    {
        for (int x = 0; x < SIZE; ++x)
        {
            for (int y = 0; y < SIZE; ++y)
            {
                cv::Rect cellRect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                cv::rectangle(img, cellRect, getTemperatureColor(field.planet_[x][y].temp), cv::FILLED);
            }
        }
    }

cv::Scalar RGBFromInt(int c)
{
    cv::Scalar wRet;
    int R = (c);                  // R: 0..255
    int G = ((c & 0x1f) << 3);    // G: 0..255
    int B = ((c & 7)    << 5);    // B: 0..255
    return wRet =cv::Scalar(B, G, R);
}
void savePNG( int run)
{
    std::stringstream oss;
    oss << "pw_" << run<<".png";
    
    std::string filename = oss.str();
    cv::imwrite(p.imageDir+filename, img);
}

cv::Mat getImage() { return img; }
};

#endif //"IMAGER_H_"
