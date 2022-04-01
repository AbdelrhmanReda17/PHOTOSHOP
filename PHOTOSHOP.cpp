// Program: PHOTOSHOP.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Author - 1:  Abdelrhman Reda Mohammed
// Author - 2:  Mahmoud Mamdouh
// Author - 3:  Abo Bakr Ahmed

// Date:    31 March 2018
// Version: 3.0

#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char saveimage[SIZE][SIZE];

void mainmessage();
void loadImage();
void saveImage();

int main()
{
    cout << "AHLAN YA USER !" <<endl;
    loadImage();
    cout << "Please select a filter to apply or 0 to exit: " <<endl;
    mainmessage();
    saveImage();
  return 0;
}

//_________________________________________
void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Please enter file name of the image to process: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, image);
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

//               FILTERS
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
    }else
    {
        cout << "BAD INPUT " <<endl;
        return enlarge_photo();
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
void first_quarter(int quarter)
{
    int y = 128;
    for (int i = 0; i < 128 ; i++)
    {
        int x = 128;
        for (int j = 0 ; j < 128 ;j++)
        {
            if (quarter == 0)
            {
                saveimage[i][j] = image[i][j];
            }
            else if (quarter == 1)
            {
                saveimage[i][x] = image[i][j];
                x++;
            }
            else if (quarter == 2)
            {
                saveimage[y][j] = image[i][j];
            }
            else if (quarter == 3)
            {
                saveimage[y][x] = image[i][j];
                x++;
            }
        }
    y++;
    }
}
void second_quarter(int quarter)
{
    int y = 128;
    for (int i = 0; i < 128 ; i++)
    {
        int x = 128;
        int l = 0;
        for (int j = 128 ; j <= 256 ;j++)
        {
            if (quarter == 1)
            {
                saveimage[i][j] = image[i][j];
            }
            else if (quarter == 0)
            {
                saveimage[i][l] = image[i][j];
                l++;
            }
            else if (quarter == 3)
            {
                saveimage[y][j] = image[i][j];
            }
            else if (quarter == 2)
            {
                saveimage[y][l] = image[i][j];
                l++;
            }
        }
    y++;
    }
}
void third_quarter(int quarter)
{
    int y = 0;
    for (int i = 128; i <= 256 ; i++)
    {
        int x = 128;
        int l = 0;
        for (int j = 0 ; j < 128 ;j++)
        {
            if (quarter == 2)
            {
                saveimage[i][j] = image[i][j];
            }
            else if (quarter == 3)
            {
                saveimage[i][x] = image[i][j];
                x++;
            }
            else if (quarter == 0)
            {
                saveimage[y][l] = image[i][j];
                l++;
            }
            else if (quarter == 1)
            {
                saveimage[y][x] = image[i][j];
                x++;
            }
        }
    y++;
    }
}
void fourth_quarter(int quarter)
{
    int y = 0;
    for (int i = 128; i <= 256 ; i++)
    {
        int x = 0;
        int l = 128;
        for (int j = 128 ; j <= 256 ;j++)
        {
            if (quarter == 3)
            {
                saveimage[i][j] = image[i][j];
            }
            else if (quarter == 2)
            {
                saveimage[i][x] = image[i][j];
                x++;
            }
            else if (quarter == 0)
            {
                saveimage[y][x] = image[i][j];
                x++;
            }
            else if (quarter == 1)
            {
                saveimage[y][l] = image[i][j];
                l++;
            }
        }
    y++;
    }
}

void shuffle_photo() {
    string arr ={'1','2','3','4'};
    int check = 0;
    string choose;
    cout << "Enter New order of quarters : ";
    cin >> choose;
    for (int i = 0 ; i < choose.length() ;i++)
        {
        for (int y = 0 ; y < 4 ; y++)
            {
                if ( choose[0] != choose[1] && choose[0] != choose[2] && choose[0] != choose[3])
                {
                    if (choose[1] != choose[2] && choose[1] != choose[3] && choose[2] != choose[3])
                    {
                        if ( choose[i] == arr[y])
                        {
                                check += 1;
                                continue;
                        }
                    }
                }
            }
        }
    if (check == 4)
    {
        for ( int i = 0 ; i < choose.length() ; i++)
        {
            if (choose[i] == '1' )
            {
                first_quarter(i);
            }
            else if (choose[i] == '2' )
            {
                second_quarter(i);
            }
            else if (choose[i] == '3' )
            {
                third_quarter(i);
            }
            else if (choose[i] == '4' )
            {
                fourth_quarter(i);
            }
        }
    }
    else
    {
        cout << "BAD INPUT" << endl;
        return shuffle_photo();
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
            black_white();
            break;
        }
        else if (choosing == "2")
        {
            cout << "=> Invert Filter" << endl;
            invert_photo();
            break;
        }
        else if (choosing == "8")
        {
            cout << "=> Enlarge Image" << endl;
            enlarge_photo();
            break;
        }else if (choosing == "b")
        {
            cout << "=> Shuffle Image" << endl;
            shuffle_photo();
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
