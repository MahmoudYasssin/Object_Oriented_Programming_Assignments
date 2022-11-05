#include <iostream>
#include <windows.h>
using namespace std;
void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    //We use csbi for the wAttributes word.
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        //Mask out all but the background attribute, and add in the forgournd color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

class ColoredBox
{
private:
    int Length;
    int Width;
    char Character;
    int color;
    char* *arr;
public:
    static int maxarea;
    //A constructor
    ColoredBox(int len,int wid,int col=15,char a='#')
    {
        Length=len;
        Width=wid;
        color=col;
        Character=a;
        arr=new char*[Length];
        for(int i=0;i<Length;i++)
        {
            arr[i]=new char[Width];
        }
        for(int a=0;a<Length;a++)
        {
            for(int b=0;b<Width;b++)
            {
                arr[a][b]=Character;
            }
        }
    }
    //setters
    void setLength(int L)
    {
        Length=L;
    }
    void setWidth(int W)
    {
        Width=W;
    }
    void setCharacter(char C)
    {
        Character=C;
    }
    void setColor(int c)
    {
        color=c;
    }
    //Getters
    char getcharacter()
    {
        return Character;
    }
    int getLentgh()
    {
        return Length;
    }
    int getWidtgh()
    {
        return Width;
    }
    //display function
    void display()
    {
        SetColor(color);
        for(int i=0;i<Length;i++)
        {
            for(int j=0;j<Width;j++)
            {
                cout<<arr[i][j];
            }
            cout<<endl;
        }
        SetColor(15);
    }
    //A function displayTransposed
    void displayTransposed()
    {
        SetColor(color);
        for(int i=0;i<Width;i++)
        {
            for(int j=0;j<Length;j++)
            {
                cout<<arr[j][i];
            }
            cout<<endl;
        }
        SetColor(15);
    }
    //function displayWider
    void displayWider()
    {
        SetColor(color);
        for(int i=0;i<Length;i++)
        {
            for(int j=0;j<Width;j++)
            {
                cout<<arr[i][j];
                cout<<" ";
            }
            cout<<endl;
        }
        SetColor(15);
    }
    //displayChess
    void displayChess(int color2)
    {
        SetColor(color);
        for(int i=0;i<Length;i++)
        {
            for(int j=0;j<Width;j++)
            {
                if((i+j)%2==1)
                {
                    SetColor(color2);
                }
                else
                {
                    SetColor(color);
                }
                cout << arr[i][j];
            }
            cout<<endl;
        }
        SetColor(15);
    }
    //A function getArea
    int getArea()
    {
        return (Length) * (Width);
    }
    //A static member function getMaxArea
    int getMaxArea()
    {
        if(maxarea<(Length) * (Width))
        {
            maxarea=(Length) * (Width);
        }
        return maxarea;
    }
    //A destructor
    ~ColoredBox()
    {
        for (int i=0; i<Length; i++)
        {
            delete[] arr[i];
        }
    }
};
int ColoredBox::maxarea=0;

int main()
{
    int len, wid, col, col2;
    char boxChar;
    cout << "Enter length and width of the box separated by a space: ";
    cin >> len >> wid;
    ColoredBox* cb1;
    cb1 = new ColoredBox(len, wid);
    cb1->display();
    cout << "Set the box to another color: ";
    cin >> col;
    cout << "Displaying Transposed: " << endl;
    cb1->setColor(col);
    cb1->displayTransposed();
    cout << "Displaying Wider: " << endl;
    cb1->displayWider();
    cout << "Displaying Chess, enter the other color: " << endl;
    cin >> col2;
    cb1->displayChess(col2);
    cout << endl << "Area=" << cb1->getArea();
    cout << endl << "Max Area=" << cb1->getMaxArea()<<endl;
    delete cb1;
    cout << "Enter length,width,color,character of the box separated by spaces: " ;
    cin >> len >> wid >> col >> boxChar;
    ColoredBox* cb2;
    cb2 = new ColoredBox(len, wid, col, boxChar);
    cb2->display();
    cout << "Displaying Transposed: " << endl;
    cb2->displayTransposed();
    cout << "Displaying Wider: " << endl;
    cb2->displayWider();
    cout << "Displaying Chess, enter the other color: " << endl;
    cin >> col2;
    cb2->displayChess(col2);
    cout << "Displaying original again:" << endl;
    cb2->display();
    cout << endl << "Area=" << cb2->getArea();
    cout << endl << "Max Area=" << cb2->getMaxArea();
    delete cb2;
    return 0;
}
