// Program: PHOTOSHOP.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Author - 1:  Abdelrhman Reda Mohammed
// Author - 2:  Mahmoud Mamdouh
// Author - 3:  Abo Bakr Ahmed
// Date:    31 March 2018
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
    cout << " Do you want to (d)arken or (l)ighten? : ";
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
//              Mirror Filter
//---------------------------------------------
void do_mirror()
{
    int want;
    cout << "Mirror\n[1] Horizontally\n[2] Vertically\n=> ";
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
    else
    {
        sleep(1);
        system("CLS");
        cout << "BAD INPUT " <<endl;
        return do_mirror();
    }
}
//---------------------------------------------
//              Edge Detector Filter
//---------------------------------------------
void Noise_Cancell()
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
            for(int x = i - 2; x < i + 3; x++)
            {
                for(int y = j - 2; y < j + 3; y++)
                {
                    if(y >= 0 && x >= 0 && x < 256 && y < 256)
                        sum += image[x][y];
                }
            }

            saveimage[i][j] = sum / 25;
        }
    }
}

void detectImage()
{
    Noise_Cancell();
    int ix[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int iy[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            image[i][j] = saveimage[i][j];
            saveimage[i][j] = 255;
        }
    }
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
            saveimage[i][j] = sqrt(sumx * sumx + sumy * sumy);
        }
    }
    int avg = 0;
    for(int i = 0; i < 254; i++)
    {
        for(int j = 0; j < 254; j++)
        {
            avg += saveimage[i][j];
        }
    }
    avg /= (254 * 254);
    for(int i = 0; i < 254; i++)
    {
        for(int j = 0; j < 254; j++)
        {
            if(saveimage[i][j] > avg)
                saveimage[i][j] = 0;
            else
                saveimage[i][j] = 255;
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
//              Flip Filter
//---------------------------------------------
void do_flip()
{
    int want;
    cout << "Flip:\n[1] Horizontaly\n[2] Vertically\n=> ";
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

void shuffle_photo() {                      // Main Filter function..
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
             << "[4] Flip Image \n"
             << "[5] Rotate Image \n"
             << "[6] Darken and Lighten Image \n"
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
            cout << "\n=> Black And White FIlter" << endl;
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
            cout << "\n=> Enlarge Image" << endl;
            enlarge_photo();
            break;
        }
        else if(choosing == "9")
        {
            cout << "\n=> Shrink Image" << endl;
            do_shrink();
            break;
        }
        else if(choosing == "a")
        {
            cout << "\n=> Mirror Image" << endl;
            do_mirror();
            break;
        }
        else if (choosing == "b")
        {
            cout << "\n=> Shuffle Image" << endl;
            shuffle_photo();
            break;
        }
        else if(choosing == "c")
        {
            cout << "\n=> Blur Image" << endl;
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
