#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;
// first class
class FloatArray{
//first class attributes
protected:
    int arrcount=0;
    float*farr;
    int thesize;
//the public functions
public:
    // parameterized constructor
    FloatArray(int n){
        thesize=n;
        farr=new float [thesize];
    }
    // getter for the current size of the array
    int getcurrentsize(){
        return arrcount;
    }
    //function to add element to the array
    virtual void add(float number){
        if(arrcount < thesize){
            farr[arrcount]=number;
            arrcount++;
        }
    }
//operator overloading >> to take the array
    friend ifstream &operator>>(ifstream &iff, FloatArray &obj){
        float fnum;
        iff >> fnum;
        obj.add(fnum);
        return iff;
    }
//operator overloading << to print the array
    friend ofstream &operator<<(ofstream &off, FloatArray &obj){
        //print the array
        for (int i = 0; i < obj.arrcount; ++i) {
            off << obj.farr[i] << '\t';
        }
        return off;
    }
//Destructor
    virtual ~ FloatArray(){
        delete[]farr;
    }
};
//second class
class SortedArray:public FloatArray{
public:
    //parameterized constructor for class SortedArray
    SortedArray(int szz): FloatArray(szz){}
    // adding element sorted in the right place to the array
    virtual void add(float number){
            int exist= 0;
            int pos=arrcount;
        if(arrcount == 0){
            farr[0]=number;
            arrcount=arrcount+1;
        }
        else{
            for (int i = arrcount - 1; i >= 0; --i) {
                if(farr[i] > number){
                    farr[i + 1]=farr[i];
                    exist++;
                    pos=i;
                }
                else
                    break;
            }
            farr[pos]=number;
            arrcount=arrcount+1;
        }
    }
};
// third class
class FrontArray:public FloatArray{
public:
    // parameterized constructor
    FrontArray(int szz): FloatArray(szz){}
    //adding number in the front of the array
    void add(float number){
        float anotherarray[thesize];
        for (int i = 0; i < thesize; ++i) {
            anotherarray[i]=farr[i];
        }
        int l=0;
        for (int i =1; i < thesize; ++i) {
            farr[i]=anotherarray[l];
            l+=1;
        }
        farr[0]=number;
        arrcount++;
    }
};
// fourth class
class PositiveArray:public SortedArray{
public:
    // parameterized constructor
    PositiveArray(int szz): SortedArray(szz){
    }
    //function to add the Positive float numbers  to the array
    void add(float number){
        if(number > 0){
            SortedArray::add(number);
        }
    }
};
// fifth class
class NegativeArray:public SortedArray{
public:
    // parameterized constructor
    NegativeArray(int szz): SortedArray(szz){
    }
    // adding the negative float numbers to the array
    void add(float number){
        if(number < 0){
            SortedArray::add(number);
        }
    }
};
int main()
{
    string ifile;

    //the input file
    cout<<"Enter the name of the input file int txt type"<<endl;
    cin >> ifile;

    //the output file
    string ofile;

    cout<<"Enter the name of the output file in txt type"<<endl;
    cin >> ofile;
    ifstream inputfile(ifile);
    ofstream outputfile(ofile);
    if(inputfile.fail()){
        cout<<"cannot open the input file"<<endl;
    }
    else{
        while (!inputfile.eof()){
            FloatArray*farray;
            string task;
            int sizearray;
            // take the option of the new object  and the size of the array
            inputfile >> task >> sizearray;
            if(task == "Array")
                farray=new FloatArray(sizearray);

            else if(task == "Negative")
                farray=new NegativeArray(sizearray);

            else if(task == "Front")
                farray=new FrontArray(sizearray);

            else if(task == "Sorted")
                farray=new SortedArray(sizearray);

            else if(task == "Positive")
                farray=new PositiveArray(sizearray);
            // taking the array from the input file
            for (int i = 0; i < sizearray; ++i) {
                inputfile >> *farray;
            }
            // printing the object to the output file
            outputfile << farray->getcurrentsize() << "|" << "\t";
            outputfile << *farray;
            outputfile << endl;
        }
    }
    //closing the files
    inputfile.close();
    outputfile.close();
}
