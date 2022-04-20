// Program: PHOTOSHOP.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
//          then we ask the user which filter do you want then do the filter..
// Author - 1:  Abdelrhman Reda Mohammed
// Author - 2:  Mahmoud Mamdouh
// Author - 3:  Abo Bakr Ahmed
// Date:    11 / 4 / 2022
// Version: 2.5

#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char saveimage[SIZE][SIZE];
unsigned char mergeimage[SIZE][SIZE];

void mainmessage();
void loadImage();
void loadMergeImage();

void saveImage();

int main()
{
    cout << "AHLAN YA USER !" <<endl ;
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
    cout << "Please Enter the Name of the image to process: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    while(readGSBMP(imageFileName, image) == 1)
    {
       return loadImage();
    }

    sleep(1);
    system("CLS");
    cout << "Image Added Successfully\n";
}
//_________________________________________
void loadMergeImage() {
   char mergeimageFileName[100];

   // Get gray scale image file name
   cout << "Please enter name of image file to merge with: ";
   cin >> mergeimageFileName;

   // Add to it .bmp extension and load image
   strcat (mergeimageFileName, ".bmp");
   while(readGSBMP(mergeimageFileName, mergeimage) == 1)
    {
       return loadMergeImage();
    }
    cout << "2nd Image Added Successfully\n";


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


//---------------------------------------------
//              BLACK AND WHITE FILTER
//---------------------------------------------
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
//---------------------------------------------
//              Flip Filter
//---------------------------------------------
void do_flip()
{
    int want;
    cout << "Flip:\n[1] Horizontally \n[2] Vertically\n=> ";
    cin >> want;
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            saveimage[i][j] = image[i][j];
        }
    }
    if(want == 1)
    {
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                image[i][j] = saveimage[i][SIZE - j - 1];
            }
        }
    }
    else if(want == 2)
    {
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                image[i][j] = saveimage[SIZE - i - 1][j];
            }
        }
    }
    else
    {
        sleep(1);
        system("CLS");
        cout << "BAD INPUT " <<endl;
        return do_flip();
    }
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            saveimage[i][j] = image[i][j];
        }
    }
}
//---------------------------------------------
//              Mirror Filter
//---------------------------------------------
void do_mirror()
{
    int want;
    cout << "Mirror\n[1] Left\n[2] Upper\n[3] Right\n[4] Lower\n=> ";
    cin >> want;
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            saveimage[i][j] = image[i][j];
        }
    }
    if(want == 1)
    {
        for(int i = 0; i < SIZE; i++)
        {
            int tmp = SIZE / 2 - 1;
            for(int j = SIZE / 2; j < SIZE; j++)
            {
                saveimage[i][j] = image[i][tmp];
                tmp--;
            }
        }
    }
    else if(want == 2)
    {
        int tmp = SIZE / 2 - 1;
        for(int i = SIZE / 2; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                saveimage[i][j] = image[tmp][j];
            }
            tmp--;
        }
    }
    else if(want == 3)
    {
        for(int i = 0; i < SIZE; i++)
        {
            int tmp = SIZE - 1;
            for(int j = 0; j < SIZE / 2 + 1; j++)
            {
                saveimage[i][j] = image[i][tmp];
                tmp--;
            }
        }
    }
    else if(want == 4)
    {
        int tmp = SIZE - 1;
        for(int i = 0; i < SIZE / 2 + 1; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                saveimage[i][j] = image[tmp][j];
            }
            tmp--;
        }
    }
    else
    {
        sleep(1);
        system("CLS");
        cout << "BAD INPUT " <<endl;
        return do_mirror();
    }
}
//---------------------------------------------
//                  Shrink FILTER
//---------------------------------------------
void do_shrink()
{
    int want;
    cout << "Shrink to:\n[1] 1/2\n[2] 1/3\n[3] 1/4\n=> ";
    cin >> want;
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            saveimage[i][j] = 255;
        }
    }
    if(want == 1)
    {
        int x = 0, y = 0;
        while(x < 256 && y < 256)
        {
            saveimage[x / 2][y / 2] = image[x][y];
            if(y == 254 && x != 254)
            {
                x += 2;
                y = 0;
            }
            else
                y += 2;
        }
    }
    else if(want == 2)
    {
        int x = 0, y = 0;
        while(x < 255 && y < 255)
        {
            saveimage[x / 3][y / 3] = image[x][y];
            if(y == 252 && x != 252)
            {
                x += 3;
                y = 0;
            }
            else
                y += 3;
        }
    }
    else if(want == 3)
    {
        int x = 0, y = 0;
        while(x < 256 && y < 256)
        {

            saveimage[x / 4][y / 4] = image[x][y];
            if(y == 252 && x != 252)
            {
                x += 4;
                y = 0;
            }
            else
                y += 4;
        }
    }
    else
    {
        sleep(1);
        system("CLS");
        cout << "BAD INPUT " <<endl;
        return do_shrink();
    }

}
//---------------------------------------------
//                  Rotate FILTER
//---------------------------------------------
void do_rotate()
{
    int want;
    cout << "Rotate:\n[1] 90 Degrees\n[2] 180 Degrees\n[3] 270 Degrees\n=> ";
    cin >> want;
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            saveimage[i][j] = image[i][j];
        }
    }
    if(want == 1)
    {
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                saveimage[i][j] = image[j][SIZE - i - 1];
            }
        }
    }
    else if(want == 2)
    {
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                saveimage[i][j] = image[SIZE - i - 1][SIZE - j - 1];
            }
        }
    }
    else if(want == 3)
    {
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                saveimage[i][j] = image[SIZE - j - 1][i];
            }
        }
    }
    else
    {
        sleep(1);
        system("CLS");
        cout << "BAD INPUT " <<endl;
        return do_rotate();
    }
}
//---------------------------------------------
//                  ENLARGE FILTER
//---------------------------------------------

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
                saveimage[y+1][k] = image[i][j];
                saveimage[y][k+1] = image[i][j];
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
                saveimage[y+1][k] = image[i][j];
                saveimage[y][k+1] = image[i][j];
                saveimage[y+1][k+1] = image[i][j];

            }
        }
    }
    else if (choose == 3)
    {
        for (int i = 128, y = 0; i < 256 ; i++,y+=2)
        {
            for (int j = 0 , k = 0 ; j < 128 ;k+=2,j++)
            {
                saveimage[y][k] = image[i][j];
                saveimage[y+1][k] = image[i][j];
                saveimage[y][k+1] = image[i][j];
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
                saveimage[y+1][k] = image[i][j];
                saveimage[y][k+1] = image[i][j];
                saveimage[y+1][k+1] = image[i][j];

            }
        }
    }
    else
    {
        sleep(1);
        system("CLS");
        cout << "BAD INPUT " <<endl;
        return enlarge_photo();
    }

}

//---------------------------------------------
//              INVERT FILTER
//---------------------------------------------

void invert_photo() {
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE ;j++)
        {
            saveimage[i][j] = 255-(image[i][j]);
        }
    }
}

//---------------------------------------------
//            Darken Lighten Filter
//---------------------------------------------

void dark_light_photo() {
    char choose;
    int average;
    cout << "Do you want to (d)arken or (l)ighten?\n => ";
    cin >> choose;
    for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE ;j++)
            {
                average += image[i][j];
            }
        }
    average = average / (256*256);
    if (choose == 'd')
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE ;j++)
            {
                if (image[i][j] > average)
                {
                    saveimage[i][j] = image[i][j] - 70;
                }else
                {
                    saveimage[i][j] = image[i][j];
                }
            }
        }

    }
    else if (choose == 'l')
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE ;j++)
            {
                if (image[i][j] < average)
                {
                    saveimage[i][j] = image[i][j] + 70;
                }else
                {
                    saveimage[i][j] = image[i][j];
                }
            }
        }
    }
    else
    {
     sleep(1);
     system("CLS");
     cout << "BAD INPUT "<<endl;
     return dark_light_photo();
    }
}
//---------------------------------------------
//              Merge Filter
//---------------------------------------------
void do_merge()
{
    loadMergeImage();
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            saveimage[i][j] = (image[i][j] + mergeimage[i][j]) / 2;
        }
    }

}

//---------------------------------------------
//              Edge Detector Filter
//---------------------------------------------

/*
    Here We are using Sobel Edge Detector algorithm, but first
    we darken the image by 1/3 to make the edges more clear
*/


void detectImage()
{
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            saveimage[i][j] = 255;
        }
    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE ;j++)
        {
            image[i][j] = 0.3 * image[i][j];   // Darken The Image
        }
    }
    int ix[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};   // To detect the Horizontal Edges
    int iy[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};   // To detect the Vertical Edges

    for(int i = 0; i < 254; i++)
    {
        for(int j = 0; j < 254; j++)
        {
            float sumx = 0, sumy = 0;
            for(int x = i, c = 0; x < i+3 && c < 3; x++, c++)
            {
                for(int y = j, v = 0; y < j+3 && v < 3; y++, v++)
                {
                    sumx += (image[x][y] * ix[c][v]);
                    sumy += (image[x][y] * iy[c][v]);
                }
            }
            saveimage[i][j] = sqrt(sumx * sumx + sumy * sumy);   // Taking the Average of the horizontal and the vertical edges
        }
    }
    for(int i = 0; i < 254; i++)
    {
        for(int j = 0; j < 254; j++)
        {
            saveimage[i][j] = 255 - saveimage[i][j];
        }
    }
}

//---------------------------------------------
//              Blur Filter
//---------------------------------------------
void do_blur()
{
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            saveimage[i][j] = image[i][j];
        }
    }
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            float sum = 0;
            for(int x = i - 5; x < i + 6; x++)
            {
                for(int y = j - 5; y < j + 6; y++)
                {
                    if(y >= 0 && x >= 0 && x < 256 && y < 256)
                        sum += image[x][y];
                }
            }

            saveimage[i][j] = sum / 121;
        }
    }
}

//---------------------------------------------
//              Shuffle Filter
//---------------------------------------------

void first_quarter(int quarter) // first quarter function..
{
    int y = 128;
    for (int i = 0; i < 128 ; i++)
    {
        int x = 128;
        for (int j = 0 ; j < 128 ;j++)
        {
            if (quarter == 0)
            {
                saveimage[i][j] = image[i][j]; // add first quarter into quarter 1
            }
            else if (quarter == 1)
            {
                saveimage[i][x] = image[i][j]; // add second quarter into quarter 2
                x++;
            }
            else if (quarter == 2)
            {
                saveimage[y][j] = image[i][j]; // add second quarter into quarter 3
            }
            else if (quarter == 3)
            {
                saveimage[y][x] = image[i][j]; // add second quarter into quarter 4
                x++;
            }
        }
    y++;
    }
}
void second_quarter(int quarter) // Second quarter function..
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
                saveimage[i][j] = image[i][j]; // add second quarter into quarter 2
            }
            else if (quarter == 0)
            {
                saveimage[i][l] = image[i][j]; // add second quarter into quarter 1
                l++;
            }
            else if (quarter == 3)
            {
                saveimage[y][j] = image[i][j]; // add second quarter into quarter 4
            }
            else if (quarter == 2)
            {
                saveimage[y][l] = image[i][j]; // add second quarter into quarter 3
                l++;
            }
        }
    y++;
    }
}
void third_quarter(int quarter) // Third quarter function..
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
                saveimage[i][j] = image[i][j]; // add third quarter into quarter 3
            }
            else if (quarter == 3)
            {
                saveimage[i][x] = image[i][j]; // add third quarter into quarter 4
                x++;
            }
            else if (quarter == 0)
            {
                saveimage[y][l] = image[i][j]; // add third quarter into quarter 1
                l++;
            }
            else if (quarter == 1)
            {
                saveimage[y][x] = image[i][j]; // add third quarter into quarter 2
                x++;
            }
        }
    y++;
    }
}
void fourth_quarter(int quarter) // Fourth quarter function..
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
                saveimage[i][j] = image[i][j]; // add fourth quarter into quarter 4
            }
            else if (quarter == 2)
            {
                saveimage[i][x] = image[i][j]; // add fourth quarter into quarter 3
                x++;
            }
            else if (quarter == 0)
            {
                saveimage[y][x] = image[i][j]; // add fourth quarter into quarter 1
                x++;
            }
            else if (quarter == 1)
            {
                saveimage[y][l] = image[i][j]; // add fourth quarter into quarter 2
                l++;
            }
        }
    y++;
    }
}

void shuffle_photo() {                      // Main Filter function..
    string arr ={'1','2','3','4'};
    int check = 0;
    string choose;
    cout << "Enter New order of quarters : ";
    cin >> choose;
    //check if there's a duplication or no ...

    for (int i = 0 ; i < choose.length() ;i++)
        {
        for (int y = 0 ; y < 4 ; y++)
            {
                if ( choose[0] != choose[1] && choose[0] != choose[2] && choose[0] != choose[3])
                {
                    if (choose[1] != choose[2] && choose[1] != choose[3] && choose[2] != choose[3])
                    {
                        if ( choose[i] == arr[y])    // check if user add a correct numbers..
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
                first_quarter(i); // i => the place of the quarter 1
            }
            else if (choose[i] == '2' )
            {
                second_quarter(i); // i => the place of the quarter 2
            }
            else if (choose[i] == '3' )
            {
                third_quarter(i); // i => the place of the quarter 3
            }
            else if (choose[i] == '4' )
            {
                fourth_quarter(i); // i => the place of the quarter 4
            }
        }
    }
    else
    {
        sleep(1);
        system("CLS");
        cout << "BAD INPUT" << endl;
        return shuffle_photo();
    }

}

//---------------------------------------------
//              CHOOSING FUNCTION
//---------------------------------------------

void mainmessage(){
    string choosing;
    while(true)
    {
        cout << "[1] Black And White Filter \n"
             << "[2] Invert Filter \n"
             << "[3] Merge Filter \n"
             << "[4] Flip Filter \n"
             << "[5] Rotate Filter \n"
             << "[6] Darken and Lighten Filter \n"
             << "[7] Detect Edges Filter \n"
             << "[8] Enlarge Filter\n"
             << "[9] Shrink Filter\n"
             << "[a] Mirror 1/2 Filter\n"
             << "[b] Shuffle Filter\n"
             << "[c] Blur Filter\n"

             << "[0] Exit \n=> ";
        cin >> choosing;
        if(choosing == "0")
        {
            cout << "See You Next Time ..." << endl; // if user choose exit
            break;
        }
        else if (choosing == "1")
        {
            cout << "\n=> Black And White Filter" << endl;
            black_white();
            break;
        }
        else if (choosing == "2")
        {
            cout << "\n=> Invert Filter" << endl;
            invert_photo();
            break;
        }
        else if(choosing == "3")
        {
            cout << "\n=> Merge Filter" << endl;
            do_merge();
            break;
        }
        else if(choosing == "4")
        {
            cout << "\n=> Flip Filter" << endl;
            do_flip();
            break;
        }
        else if(choosing == "5")
        {
            cout << "\n=> Rotate Filter" << endl;
            do_rotate();
            break;
        }
        else if (choosing == "6")
        {
            cout << "\n=> Darken And Lighten Filter" << endl;
            dark_light_photo();
            break;
        }
        else if(choosing == "7")
        {
            cout << "\n=> Edge Detector Filter\n";
            detectImage();
            break;
        }
        else if (choosing == "8")
        {
            cout << "\n=> Enlarge Filter" << endl;
            enlarge_photo();
            break;
        }
        else if(choosing == "9")
        {
            cout << "\n=> Shrink Filter" << endl;
            do_shrink();
            break;
        }
        else if(choosing == "a")
        {
            cout << "\n=> Mirror Filter" << endl;
            do_mirror();
            break;
        }
        else if (choosing == "b")
        {
            cout << "\n=> Shuffle Filter" << endl;
            shuffle_photo();
            break;
        }
        else if(choosing == "c")
        {
            cout << "\n=> Blur Filter" << endl;
            do_blur();
            break;
        }
        else
        {
            sleep(1);
            system("CLS");
            cout << "Wrong Choose !!" << endl;
            return mainmessage();
        }

    }
}
