// Program: demo2.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Author:  Mohammad El-Ramly
// Date:    30 March 2018
// Version: 1.0

#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char mergeimage[SIZE][SIZE];
unsigned char saveimage[SIZE][SIZE];


void loadImage ();
void saveImage ();
void black_white ();
void mainmessage();
void loadMergeImage();
int main()
{
  mainmessage();
  return 0;
}

//_________________________________________
void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, image);
}
//_________________________________________
void loadMergeImage() {
   char mergeimageFileName[100];

   // Get gray scale image file name
   cout << "Please enter name of image file to merge with: ";
   cin >> mergeimageFileName;

   // Add to it .bmp extension and load image
   strcat (mergeimageFileName, ".bmp");
   readGSBMP(mergeimageFileName, mergeimage);
}
//_________________________________________
void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, saveimage);
}

//_________________________________________
void black_white() {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j< SIZE; j++) {
        if (image[i][j] > 127)
            saveimage[i][j] = 255;
        else
            saveimage[i][j] = 0;
    }
  }
}
//_________________________________________
void merge_photo() {
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE ;j++)
        {
        saveimage[i][j] = ((image[i][j])+(mergeimage[i][j]))/2;
        }
    }
}
//_________________________________________
void enlarge_photo() {
    int choose;
    cout << "Which quarter to enlarge 1, 2, 3 or 4\n=>";
    cin >> choose;

    if (choose == 1)
    {
        for (int i = 0, y = 0; i < 128 ; i++,y+=2)
        {
            for (int j = 0 , k = 0 ; j < 128 ;k+=2,j++)
            {
                saveimage[y][k] = image[i][j];
                saveimage[y+1][k+1] = image[i][j];
            }
        }
    }
    else if (choose == 2)
    {
        for (int i = 0, y = 0; i < 128 ; i++,y+=2)
        {
            for (int j = 127 , k = 0 ; j < 256 ;k+=2,j++)
            {
                saveimage[y][k] = image[i][j];
                saveimage[y+1][k+1] = image[i][j];

            }
        }
    }
    if (choose == 3)
    {
        for (int i = 128, y = 0; i < 256 ; i++,y+=2)
        {
            for (int j = 0 , k = 0 ; j < 128 ;k+=2,j++)
            {
                saveimage[y][k] = image[i][j];
                saveimage[y+1][k+1] = image[i][j];
            }
        }
    }
    else if (choose == 4)
    {
        for (int i = 127, y = 0; i < 256 ; i++,y+=2)
        {
            for (int j = 127 , k = 0 ; j < 256 ;k+=2,j++)
            {
                saveimage[y][k] = image[i][j];
                saveimage[y+1][k+1] = image[i][j];

            }
        }
    }

}
//_________________________________________
void invert_photo() {
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE ;j++)
        {
            saveimage[i][j] = 256-(image[i][j]);
        }
    }
}
//_________________________________________
void flip_photo() {
    string choose;
    int z = 0 ;
    cout << "   Horizontally [H] or Vertically [V] !?\n=>";
    cin >> choose;
    if (choose == "H"){
        for (int i = 256; i >= 0; i--)
        {
            for (int j = 0; j < SIZE ;j++)
            {
                saveimage[z][j] = (image[i][j]);
            }
            z++;
        }
    }else if (choose == "V"){
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 256,y = 0; j >= 0 ;j-- , y++)
            {
                saveimage[i][y] = (image[i][j]);
            }
        }
    }else{
        cout << "BAD INPUT ! (Make Sure you add H or V)";
        return flip_photo();
    }
}
//_________________________________________
void rotate_photo() {
    int choose;
    int z = 0 ;
    cout << "Rotate (90), (180) or (360) degrees?\n=>";
    cin >> choose;
    if (choose == 180){
        for (int i = 256; i >= 0; i--)
        {
            for (int j = 0; j < SIZE ;j++)
            {
                saveimage[z][j] = (image[i][256-j]);
            }
            z++;
        }
    }
    else if (choose == 270){
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 256, y = 0 ; j >= 0 ; j-- , y++)
            {
                saveimage[i][y] = (image[j][i]);
            }
        }
    }
    else if (choose == 90){
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE ;j++)
            {
                saveimage[i][j] = (image[j][256-i]);
            }
        }
    }
    else{
        cout << "BAD INPUT !";
        return rotate_photo();
    }
}

//_________________________________________
void mirror_image(){
    string choose;
    cout << "Left,Right,Upper or Lower mirror?\n=>";
    cin >> choose;
    if (choose == "Right")
    {
        for (int i=0; i<SIZE; i++)
        {
          for (int j=0; j<SIZE; j++)
          {
             saveimage[i][j] = image[i][256-j];
          }
        }
    }
    else if (choose == "Lower")
    {
        for (int i=0; i<SIZE; i++)
        {
            for (int j=0; j<SIZE; j++)
            {
                 saveimage[i][j] = image[256-i][j];
            }
        }
    }
    else if (choose == "Left")
    {
        for (int i=0; i<SIZE; i++)
        {
            for (int j=0 ,y=0; j<SIZE; j++,y++)
            {
               if (j < 128)
                {
                    saveimage[i][y] = image[i][j];
                }
                else
                {
                    saveimage[i][y] = image[i][256-j];
                }
            }
        }
    }
    else if (choose == "Upper")
    {
        for (int i=0,y=0; i<SIZE; i++,y++)
        {
            for (int j=0 ; j<SIZE; j++)
            {
               if (i < 128)
                {
                    saveimage[y][j] = image[i][j];
                }
                else
                {
                    saveimage[y][j] = image[256-i][j];
                }
            }
        }
    }else
    {
        cout << "BAD INPUT !"<<endl;
        return mirror_image();
    }

}
//_________________________________________
void mainmessage(){
    string choosing;
    while(true)
    {
        cout << "CHOOSE A Filter PLEASE \n";
        cout << "[1] Black And White Filter \n"
             << "[2] Invert Filter \n"
             << "[3] Merge Filter \n"
             << "[4] Flip Image \n"
             << "[5] Darken and Lighten Image \n"
             << "[6] Rotate Image \n"
             << "[7] Detect Image Edges \n"
             << "[8] Enlarge Image\n"
             << "[9] Shrink Image\n"
             << "[a] Mirror 1/2 Image\n"
             << "[b] Shuffle Image\n"
             << "[c] Blur Image\n"

             << "[0] Exit \n=> ";
        cin >> choosing;
        if(choosing == "0")
        {
            cout << "See You Next Time ..." << endl;
            break;
        }
        else if (choosing == "1")
        {
            cout << "=> Black And White FIlter" << endl;
            loadImage();
            black_white();
            saveImage();
            break;
        }
        else if (choosing == "2")
        {
            cout << "=> Invert Filter" << endl;
            loadImage();
            invert_photo();
            saveImage();
            break;
        }
        else if (choosing == "3")
        {
            cout << "=> Merge Filter" << endl;
            loadImage();
            loadMergeImage();
            merge_photo();
            saveImage();
            break;
        }else if (choosing == "4")
        {
            cout << "=> Flip Image" << endl;
            loadImage();
            flip_photo();
            saveImage();
            break;
        }else if (choosing == "6")
        {
            cout << "=> Rotate Image" << endl;
            loadImage();
            rotate_photo();
            saveImage();
            break;
        }else if (choosing == "8")
        {
            cout << "=> Enlarge Image" << endl;
            loadImage();
            enlarge_photo();
            saveImage();
            break;
        }else if (choosing == "a")
        {
            cout << "=> Mirror 1/2 Image" << endl;
            loadImage();
            mirror_image();
            saveImage();
            break;
        }else
        {
            sleep(2);
            system("CLS");
            cout << "Wrong Choose !!" << endl;
            return mainmessage();
        }

    }
}
