#ifndef IMAGER_H_
#define IMAGER_H_

#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include "pop.h"
#include "common.h"
#include "popworld.h"
#include "colors.h"
#include <opencv2/opencv.hpp>

extern Field field;
extern PopsSpv spv_;
extern const Params &p;
class Imager
{
private:
    int SIZE = p.size;          // Dimensione della griglia
    int CELL_SIZE = p.cellSize; // Dimensione delle celle
    int fps = 30;
    cv::VideoWriter writer;
    std::string outputFile = p.imageDir + "sim_.mp4";
    cv::Mat img;

public:
    Imager() : img(CELL_SIZE * 128, CELL_SIZE * 128, CV_8UC3, cv::Scalar(255, 255, 255))
    {

        std::cout << "Creating IMAGER with size default " << SIZE << std::endl;
    
    } // Bianco

    Imager(int size) : img(CELL_SIZE * size, CELL_SIZE * size, CV_8UC3, cv::Scalar(255, 255, 255))
    {
        std::cout << "Creating IMAGER with size " << size << std::endl;
        SIZE = size;
        writer = cv::VideoWriter(outputFile, cv::VideoWriter::fourcc('m', 'p', '4', 'v'), fps, cv::Size(CELL_SIZE * SIZE, CELL_SIZE * SIZE));
        UpdateDraw(0);
        SavePNG(0);

    } // Bianco

    void drawLabel(int x, int y, cv::Point organismPos, float temp, int energy, unsigned mits, unsigned clrs)
    {
        // Offset per posizionare l'etichetta sopra l'organismo
        int labelOffsetY = -500;
        cv::Point labelPos = organismPos + cv::Point(10, labelOffsetY + 40);
        cv::Point labelPos2 = organismPos + cv::Point(10, labelOffsetY);
        cv::Point labelPos3 = organismPos + cv::Point(10, labelOffsetY - 40);
        cv::Point labelPos4 = organismPos + cv::Point(10, labelOffsetY - 80);
        // Disegna la linea di collegamento
        cv::line(img, organismPos, labelPos, BLACK, 1);

        // Converte il valore numerico in stringa
        double pi = 3.14159265359;
        std::stringstream stream;
        stream << "X " << x;
        // stream <<"T "<< std::fixed << std::setprecision(2) << temp;
        std::string tempText = stream.str();

        std::stringstream stream2;
        stream2 << "Y " << y;
        // stream2 <<"E "<< std::fixed << std::setprecision(2) << energy;
        std::string energyText = stream2.str();

        std::stringstream stream3;
        stream3 << "Ms " << mits;
        std::string mitsText = stream3.str();

        std::stringstream stream4;
        stream4 << "Cl " << clrs;
        std::string clrsText = stream4.str();

        // Disegna il testo accanto all'etichetta
        int fontFace = cv::FONT_HERSHEY_SIMPLEX;
        double fontScale = 1.2;
        int thickness = 3;
        cv::putText(img, tempText, labelPos, fontFace, fontScale, BLACK, thickness);
        cv::putText(img, energyText, labelPos2, fontFace, fontScale, BLACK, thickness);
        cv::putText(img, mitsText, labelPos3, fontFace, fontScale, BLACK, thickness);
        cv::putText(img, clrsText, labelPos4, fontFace, fontScale, BLACK, thickness);
    }

    void drawPlainCellLabel(int x, int y)
    {

        cv::Point labelPos =  cv::Point(x*CELL_SIZE+CELL_SIZE/5 ,y*CELL_SIZE+(CELL_SIZE/5));
        std::stringstream stream;
        stream << x<< "|" << y;
        // stream <<"T "<< std::fixed << std::setprecision(2) << temp;
        std::string txt = stream.str();
        // Disegna il testo accanto all'etichetta
        int fontFace = cv::FONT_HERSHEY_SIMPLEX;
        double fontScale = 0.5;
        int thickness = 2;
        cv::putText(img, txt, labelPos, fontFace, fontScale, BLACK, thickness);
   
    }
   
    cv::Point2f getPopPosition(int x, int y)
    {
        cv::Point2f center = projectIsometric(x, y, field.planet_[y][x].height);
        center.y -= CELL_SIZE * 0.4; // Sposta il cerchio un po’ più in alto
        return center;
    }
    void UpdateDrawDebug(int run)
    {

        img.setTo(LIGHT_YELLOW);
        for (int x = 0; x < SIZE; ++x)
        {
            for (int y = 0; y < SIZE; ++y)
            {
                drawPlainCell(x, y); 
            }
        }
        for (int x = 0; x < SIZE; ++x)
        {
            for (int y = 0; y < SIZE; ++y)
            {
                if (field.planet_[y][x].occupy)
                {
                    float radius = CELL_SIZE / 5;
                    
                    int genColor = spv_.alivePops_[field.planet_[y][x].id]->GeneticColor();
                    int chloroplasts = spv_.alivePops_[field.planet_[y][x].id]->Chloroplasts();
                    drawPlainPop(x,y,RGBFromInt(genColor),BLACK,2,RED,BLACK,0.0,chloroplasts);
                    DrawDebugBoundaries( spv_.alivePops_[field.planet_[y][x].id]->Sensitiveness(),  x, y);
                  
                }
                else{
                    assert (field.planet_[y][x].id=="");
                }

            }
        }
       
        // save
        StackFrame(run);
    }
    void UpdateDraw(int run)
    {

        img.setTo(LIGHT_YELLOW);
        for (int x = 0; x < SIZE; ++x)
        {
            for (int y = 0; y < SIZE; ++y)
            {

                drawPlainCell(x, y);
                DrawGlucose(x, y);
                drawFeromone(x,y,field.planet_[y][x].feromones[fA]/MAX_fA);
                if (field.planet_[y][x].occupy)
                {
                    float radius = CELL_SIZE / 5;
                    
                    //std::cout<<"Draw pop ["<< field.planet_[y][x].id<<"] at location  ["<< y<<"] ["<< x<<"]"<<std::endl;
                    int genColor = spv_.alivePops_[field.planet_[y][x].id]->GeneticColor();
                    int chloroplasts = spv_.alivePops_[field.planet_[y][x].id]->Chloroplasts();
                    Coord dir = spv_.alivePops_[field.planet_[y][x].id]->LastDirection();
                    double arctan= atan2(dir.y,dir.x);
                    drawPlainPop(x,y,RGBFromInt(genColor),BLACK,2,RED,BLACK,arctan,chloroplasts);
                    //DrawDebugBoundaries( spv_.alivePops_[field.planet_[y][x].id]->Sensitiveness(),  x, y);
                  
                } else{
                    assert (field.planet_[y][x].id=="");
                }
            }
        }

        // save
        StackFrame(run);
    }
    void UpdateDrawIsometric(int run)
    {

        img.setTo(LIGHT_YELLOW);
        for (int x = 0; x < SIZE; ++x)
        {
            for (int y = 0; y < SIZE; ++y)
            {

                drawIsometricCell(x, y);
                if (field.planet_[y][x].occupy)
                {
                    float radius = CELL_SIZE / 5;
                    drawShadow(getPopPosition(x, y), radius);
                    int genColor = spv_.alivePops_[field.planet_[y][x].id]->GeneticColor();
                    drawIsoPop(x, y,
                                      RGBFromInt(genColor),
                                      x + y, spv_.alivePops_[field.planet_[y][x].id]->Temp(),
                                      spv_.alivePops_[field.planet_[y][x].id]->Energy(),
                                      spv_.alivePops_[field.planet_[y][x].id]->Mitochondrions(),
                                      spv_.alivePops_[field.planet_[y][x].id]->Chloroplasts());
                }
            }
        }

        // save
        StackFrame(run);
    }

    void drawIsoGrid()
    {
        std::cout << "drawIsoGrid " << std::endl;
        for (int y = 0; y < SIZE; y++)
        {
            for (int x = 0; x < SIZE; x++)
            {
                drawIsometricCell(x, y);
            }
        }
    }

   
    void drawPlainPop(int x, int y,
                      cv::Scalar fillColor,
                      cv::Scalar borderColor,
                      int borderThickness,
                      cv::Scalar outerCircleColor,
                      cv::Scalar vectorColor,
                      float angleDeg,
                      int chloroplasts
                    )
    {

       
        // Centro della cella
        int centerX = x * CELL_SIZE + CELL_SIZE / 2;
        int centerY = y * CELL_SIZE + CELL_SIZE / 2;
        cv::Point center(centerX, centerY);

        // Raggio del cerchio principale (adattato alla cella)
        int radius = CELL_SIZE / 2.6;

        // Disegna il cerchio principale
        cv::circle(img, center, radius, fillColor, cv::FILLED);

        // Disegna il bordo del cerchio
        // cv::circle(img, center, radius, borderColor, borderThickness);

        // Disegna un cerchio leggermente più grande attorno per i vegetali
       
       //if (chloroplasts>0) 
        //cv::circle(img, center, radius  , outerCircleColor, borderThickness);

        // Calcola il vettore (linea orientata) con angolo specifico
        float angleRad = angleDeg;/// * CV_PI / 180.0; // Conversione in radianti
        int vectorLength = CELL_SIZE * 0.7;        // /3;  // Lunghezza del vettore (poco meno di metà cella)
        cv::Point vectorEnd(
            center.x + static_cast<int>(vectorLength * cos(angleRad)),
            center.y - static_cast<int>(vectorLength * sin(angleRad)) // Y invertito per OpenCV
        );

        // Disegna il vettore
       // cv::line(img, center, vectorEnd, vectorColor, 2);
        // Disegna il vettore
        //cv::Point origin(0, 0);
        //cv::line(img, origin, center, vectorColor, 2);
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
    

    cv::Point2f projectIsometric(int x, int y, double height)
    {
        float isoX = (x - y) * 0.5 * CELL_SIZE;
        float isoY = (x + y) * 0.25 * CELL_SIZE - height; // Altezza abbassa/eleva la cella
                                                          // Centro l'intera mappa
        float imgWidth = CELL_SIZE * SIZE;
        float centerX = imgWidth / 2.0;
        float centerY = imgWidth / 4.0; // Regolabile per il posizionamento

        return cv::Point2f(isoX + centerX, isoY + centerY);
    }

    cv::Scalar getWallColor(cv::Scalar baseColor, bool isLeft)
    {
        double factor = isLeft ? 0.6 : 0.8; // Più scuro a sinistra
        return cv::Scalar(baseColor[0] * factor, baseColor[1] * factor, baseColor[2] * factor);
    }

    void drawIsometricWall(cv::Point2f topLeft, cv::Point2f bottomLeft, double height, cv::Scalar color)
    {
        // Calcola i punti in basso (livello del terreno)
        cv::Point2f baseTopLeft = topLeft + cv::Point2f(0, height);
        cv::Point2f baseBottomLeft = bottomLeft + cv::Point2f(0, height);

        // Costruisci la parete come un poligono
        std::vector<cv::Point> wall = {topLeft, bottomLeft, baseBottomLeft, baseTopLeft};
        cv::fillConvexPoly(img, wall, color);
    }

    void drawIsometricCell(int x, int y)
    {
        // Ottieni i quattro vertici della cella in coordinate isometriche
        cv::Point2f topLeft = projectIsometric(x, y, field.planet_[y][x].height);
        cv::Point2f topRight = projectIsometric(x + 1, y, field.planet_[y][x].height);
        cv::Point2f bottomLeft = projectIsometric(x, y + 1, field.planet_[y][x].height);
        cv::Point2f bottomRight = projectIsometric(x + 1, y + 1, field.planet_[y][x].height);

        // Base a livello del terreno
        cv::Point2f baseTopLeft = projectIsometric(x, y, 0);
        cv::Point2f baseBottomLeft = projectIsometric(x, y + 1, 0);

        // Disegna le pareti laterali
        drawIsometricWall(topLeft, bottomLeft, field.planet_[y][x].height, getWallColor(DIM_GRAY, true));
        drawIsometricWall(topRight, bottomRight, field.planet_[y][x].height, getWallColor(DIM_GRAY, false));
        drawIsometricWall(bottomLeft, bottomRight, field.planet_[y][x].height, getWallColor(LIGHT_GREEN, false));
        // Disegna la superficie superiore della cella
        std::vector<cv::Point> topFace = {topLeft, topRight, bottomRight, bottomLeft};

        cv::Scalar tempColor = getTemperatureColor(field.planet_[y][x].temp);
        cv::Scalar baseColor = getTerrainColor(field.planet_[y][x].height);

        cv::Scalar blendedColor = blendColors(baseColor, tempColor, p.tempBlendFactor);

        if (x == 0 && y == 0)
            blendedColor = BLACK;
        cv::fillConvexPoly(img, topFace, applyHeightLighting(blendedColor, field.planet_[y][x].height));
        // Border
        cv::polylines(img, topFace, true, cv::Scalar(0, 0, 0), 1, cv::LINE_AA);
    }

    void DrawDebugBoundaries(int sens, int x,int y)
    { 
        
        //WEST
        int startPx=x-sens;
        int startPy=y-sens;
        /*
        for(int i=startPy;i<startPy+(2*sens)+1;i++) //y
           { 
            for(int j=startPx;j<startPx+(sens);j++) //x
                {   
                    Coord c;
                    c.y=i;
                    c.x=j;
                    if (field.IsInBound(c))
                    {   
                    
                        cv::Rect cellRect(j * CELL_SIZE,i * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                        cv::rectangle(img, cellRect, LIGHT_GREEN, cv::FILLED);
                        drawPlainCellLabel( j,  i);
                        if (field.planet_[i][j].occupy)
                        {
                            float radius = CELL_SIZE / 5;
                            //std::cout << "Pop at WEST i["<<y<<"]j["<<x<<"]   found pop at pos i["<<i<<"]j["<<j<<"] "  << std::endl;
                            int genColor = spv_.alivePops_[field.planet_[i][j].id]->GeneticColor();
                            drawPlainPop(j,i,RGBFromInt(genColor),BLACK,2,RED,BLACK,0.0);
                        }
                    }
                }
            }
        */
        //EAST
        //std::cout << "EAST FOR "  << std::endl;
        /*
        startPx=x+sens;
        startPy=y+sens;
        for(int i=startPy;i>startPy-(2*sens)-1;i--) //y
        {  
            for(int j=startPx;j>startPx-(sens);j--) //x
                {   
                    Coord c;
                    c.y=i;
                    c.x=j;
                    if (field.IsInBound(c))
                    {   
                        //std::cout << "DRAW EAST AT  i["<<i<<"]j["<<j<<"]/["<<startPx-(sens)<<"]  "  << std::endl;
                        cv::Rect cellRect(j * CELL_SIZE,i * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                        cv::rectangle(img, cellRect, LIGHT_BLUE, cv::FILLED);
                        drawPlainCellLabel( j,  i);
                        if (field.planet_[i][j].occupy)
                        {
                            float radius = CELL_SIZE / 5;
                            //std::cout << "Pop at EAST  i["<<y<<"]j["<<x<<"]   found pop at pos i["<<i<<"]j["<<j<<"] "  << std::endl;
                            int genColor = spv_.alivePops_[field.planet_[i][j].id]->GeneticColor();
                            drawPlainPop(j,i,RGBFromInt(genColor),BLACK,2,RED,BLACK,0.0);
                        }
                    }
                } 
        }   */
        
        /*startPx=x-sens;
        startPy=y-sens;
        for(int i=startPy;i<startPy+(sens);i++) //y
        { 
         for(int j=startPx;j<startPx+(2*sens)+1;j++) //x
             {   
                 Coord c;
                 c.y=i;
                 c.x=j;
                 if (field.IsInBound(c))
                 {   
                 
                     cv::Rect cellRect(j * CELL_SIZE,i * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                     cv::rectangle(img, cellRect, LIGHT_GREEN, cv::FILLED);
                     drawPlainCellLabel( j,  i);
                     if (field.planet_[i][j].occupy)
                     {
                         float radius = CELL_SIZE / 5;
                         //std::cout << "Pop at WEST i["<<y<<"]j["<<x<<"]   found pop at pos i["<<i<<"]j["<<j<<"] "  << std::endl;
                         int genColor = spv_.alivePops_[field.planet_[i][j].id]->GeneticColor();
                         drawPlainPop(j,i,RGBFromInt(genColor),BLACK,2,RED,BLACK,0.0);
                     }
                 }
             }
         }
*/
/*
        startPx=x-sens;
        startPy=y+1;
        for(int i=startPy;i<startPy+(sens);i++) //y
        { 
         for(int j=startPx;j<startPx+(2*sens)+1;j++) //x
             {   
                 Coord c;
                 c.y=i;
                 c.x=j;
                 if (field.IsInBound(c))
                 {   
                 
                     cv::Rect cellRect(j * CELL_SIZE,i * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                     cv::rectangle(img, cellRect, LIGHT_GREEN, cv::FILLED);
                     drawPlainCellLabel( j,  i);
                     if (field.planet_[i][j].occupy)
                     {
                         float radius = CELL_SIZE / 5;
                         //std::cout << "Pop at WEST i["<<y<<"]j["<<x<<"]   found pop at pos i["<<i<<"]j["<<j<<"] "  << std::endl;
                         int genColor = spv_.alivePops_[field.planet_[i][j].id]->GeneticColor();
                         drawPlainPop(j,i,RGBFromInt(genColor),BLACK,2,RED,BLACK,0.0);
                     }
                 }
             }
         }
             */
        
    }
    void DrawGlucose(int x, int y)
    {    
            int maxDrawableGlucose=60;
            float percent=(float)field.planet_[y][x].resources.c6h12o6/maxDrawableGlucose;
            if (field.planet_[y][x].resources.c6h12o6>maxDrawableGlucose)
                percent=1;
             
            if (percent>0.55)
            {   
            //std::cout << "Glucose percent ["<<field.planet_[y][x].resources.c6h12o6 <<"]["<<percent<<"]" << std::endl;   
            int size=CELL_SIZE*percent;
            int centerX = x * CELL_SIZE + CELL_SIZE / 2;
            int centerY = y * CELL_SIZE + CELL_SIZE / 2;
            cv::Point center(centerX, centerY);
           /* std::vector<cv::Point> points{
                {centerX,centerY-size},
                {centerX+size,centerY},
                {centerX,centerY+size},
                {centerX-size,centerY},
            };
         
            const cv::Point * pts[1]={points.data()};
            int npts[]={static_cast<int>(points.size()) };*/
            //cv::polylines(img, pts,npts,1,true,WHITE, 2);
            cv::circle(img, center, 7*percent, WHITE, -1); // Nero
        }
   
    }

    void drawFeromone(int x, int y,float percent)
    {
       
        if (percent>0)
        {   
            int centerX = x * CELL_SIZE + CELL_SIZE / 2;
            int centerY = y * CELL_SIZE + CELL_SIZE / 2;
            cv::Point center(centerX, centerY);
            cv::circle(img, center, 5*percent, MAGENTA, -1); // Nero
        }
     
    }
    void drawPlainCell(int x, int y)
    {
        // Ottieni i quattro vertici della cella in coordinate isometriche
        
        cv::Rect cellRect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
    
        cv::Scalar tempColor = getTemperatureColor(field.planet_[y][x].temp);
        cv::Scalar baseColor = getTerrainColor(field.planet_[y][x].height);
        
        /*if (field.planet_[y][x].resources.h2o>20)
        {
            baseColor=LIGHT_BLUE;
        }
        if (field.planet_[y][x].resources.h2o>40)
        {
            baseColor=BLUE;
        }
            */
        cv::Scalar blendedColor = blendColors(baseColor, tempColor, p.tempBlendFactor);

      
        cv::rectangle(img, cellRect, applyHeightLighting(blendedColor, field.planet_[y][x].height), cv::FILLED);

        // Border
        //cv::polylines(img, topFace, true, WHITE, 1, cv::LINE_AA);
        //drawPlainCellLabel( x,  y);
    }
    cv::Scalar applyHeightLighting(cv::Scalar color, double height)
    {
        double heightFactor = std::min(1.0, height / 100.0);
        return color * (0.7 + 0.3 * heightFactor); // Più alta, più chiara
    }
    cv::Scalar getShadedColor(cv::Scalar baseColor, double height)
    {
        double shadeFactor = 1.0 - (height / p.maxHeight); // Ombra più forte in basso
        shadeFactor = std::max(0.6, shadeFactor);          // Limitiamo l'ombra minima

        return cv::Scalar(
            baseColor[0] * shadeFactor,
            baseColor[1] * shadeFactor,
            baseColor[2] * shadeFactor);
    }
    cv::Scalar getTerrainColor(int height)
    {
        cv::Scalar groundColor = GRASS; // Verde erba
        if (height > 50)
            groundColor = MOUNTAINS; // Montagne grigie
        if (height < 10)
            groundColor = LIGHT_GREEN; //SAND; // Sabbia
        return groundColor;
    }
    cv::Scalar blendColors(cv::Scalar baseColor, cv::Scalar tempColor, double tempFactor)
    {
        return baseColor * (1 - tempFactor) + tempColor * tempFactor;
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
                cv::rectangle(img, cellRect, getTemperatureColor(field.planet_[y][x].temp), cv::FILLED);
            }
        }
    }
    void drawShadow(cv::Point2f pos, int radius)
    {
        cv::ellipse(img, pos + cv::Point2f(2, 4), cv::Size(radius, radius * 0.4),
                    0, 0, 360, cv::Scalar(50, 50, 50, 50), cv::FILLED, cv::LINE_AA);
    }
    

    void drawIsoPop(int x, int y, cv::Scalar color, double angle, float temp, int energy, int mits, int clrs)
    {
        // Centro della cella

        cv::Point2f pos = getPopPosition(x, y);
        drawLabel(x, y, pos, temp, energy, mits, clrs);
        int radiusX = CELL_SIZE / 2.5;
        int radiusY = CELL_SIZE / 7; // Rende l'effetto ellissoidale

        cv::ellipse(img, pos, cv::Size(radiusX, radiusY),
                    0, 0, 360, color, cv::FILLED, cv::LINE_AA);

        cv::ellipse(img, pos, cv::Size(radiusX, radiusY),
                    0, 0, 360, BLACK, 1, cv::LINE_AA);
        // Disegna la piccola linea direzionale (vettore)
        double lineLength = radiusX * 1.2;
        cv::Point2f end(
            pos.x + cos(angle) * lineLength,
            pos.y - sin(angle) * lineLength);
        cv::line(img, pos, end, BLACK, 2, cv::LINE_AA);
    }
    cv::Scalar RGBFromInt(int c)
    {
        cv::Scalar wRet;
        int R = (c);               // R: 0..255
        int G = ((c & 0x1f) << 3); // G: 0..255
        int B = ((c & 7) << 5);    // B: 0..255
        return wRet = cv::Scalar(B, G, R);
    }
    void StackFrame(int run)
    {
        writer.write(img);
    }

    void SavePNG(int run)
    {
        std::stringstream oss;
        oss << "pw_" << run << ".png";

        std::string filename = oss.str();
        cv::imwrite(p.imageDir + filename, img);
    }

    void ReleaseVideoEditor()
    {
        writer.release();
    }
    cv::Mat getImage() { return img; }
};

#endif //"IMAGER_H_"
