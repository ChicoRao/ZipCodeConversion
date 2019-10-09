//  @file    hw1q1.cpp
//  @author  Rico Chao, Angus Kan
//  @date    10/03/2017
//  @version 1
//
//  @brief HW1 question 1
//
//  @section DESCRIPTION
//  This code is able to encode and decode both zipcode and barcodes into each other
//  The code features a class and also various functions to check and preform conversions to change the input into the desired form
//  
//
//
// I declare that this assignment is my own work and that I have correctly acknowledged the
// work of others. I acknowledged that I have read and followed the Academic Honesty and
// Integrity related policies as outlined in the syllabus. 
//
// _____ Rico Chao ____ _____10/03/2017______________ 
//
// ____ 301310624 ______ 
//
// (if this is group project, please list all the team members at the following space: 
//
// _____ Angus Kan ____ _____10/03/2017______________ 
//
// ____ 301309417 ______


#include <iostream>
#include <string>

using namespace std;

class PostNet
{
    public:
        // Constructor that creates a zip code with 5 digit integer values
        PostNet(int zip);
        
        // Constructor that creates a barcode with a string of 0's and 1's
        PostNet(string bar);
        
        // Returns the zip code integer
        int returnInt();
        
        // Returns the string barcode
        string returnString();
        
    private:
        // Check if the barcode has any errors
        void checkBarCode(string bar);
    
        // Converts the barcode to zip code
        int conversion(string bar);
    
        int zip; ///< The zip code
    
};

int main()
{
    cout << "Test 1" << endl;
    PostNet zipCode1(99504);
    cout << "The barcode of " << zipCode1.returnInt() << " is " << zipCode1.returnString() << endl;
    cout << "This is the decoded zip code" << endl << endl;
    
    cout << "Test 2" << endl;
    PostNet zipCode2("110100101000101011000010011");
    cout << "The barcode of " << zipCode2.returnInt() << " is " << zipCode2.returnString() << endl;
    cout << "This is the decoded zip code" << endl << endl;
    
    cout << "Test 3" << endl;
    PostNet zipCode3("110200101000101011000010011");
    
    cout << "Test 4" << endl;
    PostNet zipCode4("111100101000101011000010011");
    
    cout << "Test 5" << endl;
    PostNet zipCode5("1110100101000101011000010011");
    
    cout << "Test 6" << endl;
    PostNet zipCode6("001100101000101011000010011");
    
    return 0;
}


PostNet::PostNet(int value): zip(value)
{
}

PostNet::PostNet(string bar)
{
    zip = conversion(bar);
}

void PostNet::checkBarCode(string bar) 
{
    if (((bar.length() - 2) % 5) != 0) //checking if the length of the barcode is 27
    {
        cerr << "ERROR: The barcode " << bar << " has an incorrect length" << endl << endl;
        return;
    }
    
    if ((bar[0] != '1') || (bar[bar.length() - 1] != '1')) //checking if the barcode's first and last digit is 1
    {
        cerr << "ERROR: The barcode " << bar << " does not start or end with 1" << endl << endl;
        return;
    }
    
    for (int i=0; i<bar.length(); i++)  //checking if barcode contains only 1s and 0s
    {
        if((bar[i] != '1') && (bar[i] != '0'))
        {
            cerr << "ERROR: The barcode " << bar << " contains values other than 1 or 0" << endl << endl;
            return;
        }
    }
    return;
}  

int PostNet::conversion(string bar)
{
    checkBarCode(bar); //calls checkbarcode function
    int zipValue = 0;
    int barLength = 0;
    
    barLength = (bar.length() - 2) / 5; //barlength becomes 5
    
    for (int i=0; i <barLength; i++)
    {
        int count = 0;
        int check = 0;
        const int value[5]={7, 4, 2, 1, 0}; //value that the group multiply to  obtain the zip code
        
        for (int j=0; j<5; j++) //checks each number to see if its 1 or 0
        {
            char code = bar[1 + 5 * i + j];
            if(code == '1')
            {
                count += value[j]; //when the program goes through the for loop, the 1s will corrospond to the value
                check++;           //the function will then give the number decoded from the section of the barcode
            }
        }
        if (check > 2) //checking if the barcode section has too many 1s, the barcode group should only have two 1s
        {
            cerr << "ERROR: The barcode " << bar << " has too many 1's for a 5 digit group" << endl << endl;
            return 1;
        }
        
        if (count > 11 || count < 1 || count == 10)
        {
            cerr << "ERROR: Zip code digit for barcode " << bar << " is invalid" << endl << endl;
            return 2;
        }
        if (count == 11)
        {
            count = 0;
        }
    
    zipValue = zipValue * 10 + count;
    }
    
     return zipValue; 
}

int PostNet::returnInt()
{
    return zip; //returns the zipcode
}

string PostNet::returnString()
{
    int i = 4;
    string bar[i+1];
    string fullBar;
    int zipCode;
    
    zipCode = zip;
    
    while (zipCode > 0 && i >= 0) //while the zipcode isnt zero and i is greater than 0
    {                             //the code will divide the zipcode by 10, and use the remainder
                                  //as the number represented by the corrosponding section of the barcode
        if (zipCode % 10 == 1)
        { 
            bar[i] += "00011";
        }
        else if (zipCode % 10 == 2)
        {
            bar[i] += "00101";
        }
        else if (zipCode % 10 == 3)
        {
            bar[i] += "00110";
        }
        else if (zipCode % 10 == 4)
        {
            bar[i] += "01001";
        }
        else if (zipCode % 10 == 5)
        {
            bar[i] += "01010";
        }
        else if (zipCode % 10 == 6)
        {
            bar[i] += "01100";
        }
        else if (zipCode % 10 == 7)
        {
            bar[i] += "10001";
        }
        else if (zipCode % 10 == 8)
        {
            bar[i] += "10010";
        }
        else if (zipCode % 10 == 9)
        {
            bar[i] += "10100";
        }
        else if (zipCode > 10 && (zipCode % 10 == 0))
        {
            bar[i] += "11000"; 
        }
        zipCode = zipCode / 10;
        i--;
    }
    
    fullBar += "1";     //the full barcode is then made by adding 1s to the beginning and end of the barcode
    fullBar += bar[0];  
    fullBar += bar[1];
    fullBar += bar[2];
    fullBar += bar[3];
    fullBar += bar[4];
    fullBar += "1";
    
    return fullBar;
}
