/*
Benoetigt: https://opencv.org/releases/
Fuer Include Verzeichnisse im Visual Studio siehe Screenshots im Projekt ordner
*/

#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    // Festlegung des Fehlertolreanz Wertes (1 bis 100)
    int errorScale = 70;

    // Festlegung des Error Scale Wertes (1 bis 100)
    int jPEGQuality = 90;

    // Bildpfad
    string imageLocation = "C:\\Users\\matth\\Downloads\\Guilin_Pferd.jpg";

    // Deklaration der Image-Container (Mat)
    Mat inputImage, compareImage, outputImage;

    // Bild einlesen
    inputImage = imread(imageLocation);

    // Legt die angegebene JPEG Qualitaet als parameter fest
    vector<int> parameters;
    parameters.push_back(jPEGQuality);
    
    // Komprimiert das Bild erneut (Und speichert es temporaer)
    imwrite("temp.jpg", inputImage);
    compareImage = imread("temp.jpg");

    outputImage = Mat::zeros(inputImage.rows, inputImage.cols, CV_8UC3);
    for (int i = 0; i < inputImage.rows; i++) {

        uchar* pointerInput = inputImage.ptr<uchar>(i);
        uchar* pointerCompare = compareImage.ptr<uchar>(i);
        uchar* pointerOutput = outputImage.ptr<uchar>(i);

        for (int j = 0; j < inputImage.cols; j++) {
            pointerOutput[0] = abs(pointerInput[0] - pointerCompare[0]) * errorScale;
            pointerOutput[1] = abs(pointerInput[1] - pointerCompare[1]) * errorScale;
            pointerOutput[2] = abs(pointerInput[2] - pointerCompare[2]) * errorScale;

            pointerInput += 3;
            pointerCompare += 3;
            pointerOutput += 3;
        }
    }

    // Zeigt Fenster mit original Bild
    namedWindow("Originalbild", WINDOW_NORMAL);
    imshow("Originalbild", inputImage);

    // Zeigt Fenster nach ELA
    namedWindow("Error Level Analyse", WINDOW_NORMAL);
    imshow("Error Level Analyse", outputImage);

    // Konsole im Wartemodus (Visual Studio)
    while (char(cv::waitKey(0)) != 'q');
}