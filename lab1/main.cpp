#include <QImage>
#include <QColor>
#include <iostream>
#include <QtCore/QCoreApplication>

using namespace std;

int main(int argc, char** argv) {



    float x1,x2,x3,y1,y2,y3;
    float r1,r2,r3,g1,g2,g3,b1,b2,b3;

    //Gets 3 coordinate points from user

    cout << "Your triangle can be a max of 640 pixels wide and 480 pixels tall \n";
    cout << "Please enter your first set of coordinates: ";
    cin >> x1 >> y1;
    cout << "Your coordinates for this point are (" << x1 << "," << y1 << ")\n";

    cout << "Please enter your second set of coordinates: ";
    cin >> x2 >> y2;
    cout << "Your coordinates for this point are (" << x2 << "," << y2 << ")\n";

    cout << "Please enter your third set of coordinates: ";
    cin >> x3 >> y3;
    cout << "Your coordinates for this point are (" << x3 << "," << y3 << ")\n";

    //Gets 3 color values for each point

    cout << "Please enter your rgb colors for point one ranging from 0 to 1 (r value, g value, b value)\n";
    cin >> r1 >> g1 >> b1;
    cout << "Your r value is: " << r1 <<" Your g value is: " << g1 << " Your b value is: " << b1 << "\n";

    //find max and min for x,y

    float maxX, maxY, minX, minY;

    if(x1 <= x2 && x1 <= x3){
        minX = x1;
    }
    else if(x2 <= x1 && x2 <= x3){
        minX = x2;
    }
    else{
        minX = x3;
    }



    if(x1 >= x2 && x1 >= x3){
        maxX = x1;
    }
    else if(x2 >= x1 && x2 >= x3){
        maxX = x2;
    }
    else{
        maxX = x3;
    }



    if(y1 >= y2 && y1 >= y3){
        maxY = y1;
    }
    else if(y2 >= y1 && y2 >= y3){
        maxY = y2;
    }
    else{
        maxY = y3;
    }




    if(y1 <= y2 && y1 <= y3){
        minY = y1;
    }
    else if(y2 <= y1 && y2 <= y3){
        minY = y2;
    }
    else{
        minY = y3;
    }

    cout << "Your minimum x value is: " << minX << "\n";
    cout << "Your maximum x value is: " << maxX << "\n";
    cout << "Your minimum y value is: " << minY << "\n";
    cout << "Your maximum y value is: " << maxY << "\n";

    /*
      Prompt user for 3 points separated by whitespace.

      Part 1:
          You'll need to get the x and y coordinate as floating point values
          from the user for 3 points that make up a triangle.

      Part 3:
          You'll need to also request 3 colors from the user each having
          3 floating point values (red, green and blue) that range from 0 to 1.
    */

    // create an image 640 pixels wide by 480 pixels tall
    // with a standard 32 bit red, green, blue format
    QImage image(640, 480, QImage::Format_RGB32);


    /*for(float i = minY; i <= maxY; i++){
        for(float j = minX; j <= maxX; j++){
            image.setPixel(j,i, qRgb(255,255,255));
          }
    }*/
    
    float red = (r1*255)/32;
    float green = (g1*255)/32;
    float blue = (b1*255)/64;

    for(float i = minY; i <= maxY; i++){
        for(float j = minX; j <= maxX; j++){
            float alpha = ((y2 - y3)*i + (x3 - x1)*j + x2*y3 - x3*y2)/((y2 - y3)*x1 + (x3 - x1)*y1 + x2*y3 - x3*y2);

            float beta = ((y3 - y1)*i + (x1 - x3)*j + x3*y1 - x1*y3)/((y3 - y1)*x2 + (x1 - x3)*y2 + x3*y1 - x1*y3);

            float gamma = ((y1 - y2)*i + (x2 - x1)*j + x1*y2 - x2*y1)/((y1 - y2)*x3 + (x2 - x1)*y3 + x1*y2 - x2*y1);
            //cout << alpha + beta + gamma;

            if(alpha > 0 && beta > 0 && gamma > 0){
                image.setPixel(j,i, qRgb(255 * alpha * r1, 255 * beta * g1 ,255 * gamma * b1));
            }
        }
    }
    /*
      Part 1:
          over each pixel in that box and set it to white using:
          Calculate the bounding box of the 3 provided points and loop

          image.setPixel(x,y, qRgb(255,255,255));

      Part 2:
          Modify your loop from part 1. Using barycentric coordinates,
          determine if the pixel lies within the triangle defined by
          the 3 provided points. If it is color it white, otherwise
          move on to the next pixel.

          For more on barycentric coordinates:
          http://en.wikipedia.org/wiki/Barycentric_coordinate_system

      Part 3:
          For each pixel in the triangle, calculate the color based on
          the calculated barycentric coordinates and the 3 provided
          colors. Your colors should have been entered as floating point
          numbers from 0 to 1. Since we have a 32 bit image, the red,
          green and blue components range from 0 to 255. Be sure to make
          the conversion.
    */

    if(image.save("triangle.jpg",0,100)) {
        cout << "Output triangle.jpg" << endl;
    } else {
        cout << "Unable to save triangle.jpg" << endl;
    }
    return 0;
}
