//Mahmoud Yassin Mahmoud ---> 20200506
//Hager Ali Younes ---> 20200614
#include <iostream>
using namespace std;
class  Item
{
private:
    string name;
    int quantity;
    int ID;
    int price;
public:
    static int countt;
   //Empty Constructors
    Item()
    {
        name="";
        quantity=0;
        price=0;
        ID=countt;
        countt++;
    }
    //parameterized Constructors
    Item(string n,int q,int p)
    {
        name=n;
        quantity=q;
        price=p;
        ID=countt;
        countt++;
    }
    //Copy Constructors
    Item(Item &obj)
    {
        name=obj.name;
        quantity=obj.quantity;
        price=obj.price;
        ID=obj.ID;

    }
    //Setter
    string set_name()
    {
        cout<<"Enter Name: ";
        cin>>name;
        return name;
    }
    int set_quantity()
    {
        cout<<"Enter Quantity: ";
        cin>>quantity;
        return quantity;
    }
    int set_price()
    {
        cout<<"Enter Price: ";
        cin>>price;
        return price;
    }
   void set_ID(int n)
    {
        ID=n;
        countt++;
    }
    //Getters
    string get_name()
    {
        return name;
    }
    int get_quantity()
    {
        return quantity;
    }
    int get_price()
    {
        return price;
    }
    int get_ID()
    {
        return ID;
    }
    //Overloaded functions
    bool operator==(Item &B)
    {
        if(name==B.name)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    Item operator+=(Item B2)
    {
        quantity+=B2.quantity;
        return *this;
    }

    friend ostream &operator<<(ostream&,const Item &);
    friend istream &operator>>(istream&,Item &);
    friend class Seller;
    friend void Find_an_Item_by_ID(int i);


};
int Item::countt=1;
istream &operator>>(istream&input,Item &obj)
    {
        cout<<"Name: ";
        input>>obj.name;
        //cout<<endl;
        cout<<"Quantity: ";
        input>>obj.quantity;
        //cout<<endl;
        cout<<"Price: ";
        input>>obj.price;
        cout<<endl;
        return input;
    }
ostream  &operator<<(ostream&output,const Item &obj2)
    {
        cout<<"Name: ";
        output<<obj2.name;
        cout<<endl;
        cout<<"Quantity: ";
        output<<obj2.quantity;
        cout<<endl;
        cout<<"Price: ";
        output<<obj2.price;
        cout<<endl;
        cout<<"ID: ";
        output<<obj2.ID;
        return output;
    }

class Seller
{
private:
    string namee;
    string email;
    Item *arr;
    int maxItems;
   public:
    //Seller();
    static int counter_of_Item;
    friend ostream &operator<<(ostream&,const Seller &);
    friend istream &operator>>(istream&,Seller &);
    //Parameterized Constructor
    Seller(string n,string e,int m)
    {
        namee=n;
        email=e;
        maxItems=m;
        arr=new Item[maxItems];

    }
    //Function To Set Elements is array
    void Set_Elem_In_arr(Item &Q)
    {
            arr[counter_of_Item]=Q;
            arr[counter_of_Item].set_ID(counter_of_Item+1);
            counter_of_Item=counter_of_Item+1;
    }
    //Function To Add An Item.
    bool Add_An_Item(Item &Q)
    {

        for(int i=0;i<counter_of_Item;i++)
        {
            if(arr[i].name==Q.name)
            {
                arr[i].quantity+=Q.quantity;
                return true;
            }

        }
        if(counter_of_Item<maxItems)
        {
            Set_Elem_In_arr(Q);
            return true;

        }
        else
        {
            return false;
        }

    }
    //Function To Sell An Item.
    bool Sell_An_Item(string name_of_product,int num)
    {
        for(int i=0;i<counter_of_Item;i++)
        {
            if(arr[i].name==name_of_product)
            {
                if(arr[i].quantity>=num)
                {
                    arr[i].quantity-=num;
                    return true;
                }
                else
                {
                    cout<<"There is only {quantity} left for this item"<<endl;
                    return false;
                }
            }

        }

    }
   //Function To Print Items.
   void Print_Items()
   {
       for(int i=0;i<counter_of_Item;i++)
       {
            cout<<"------------------"<<endl;
            cout<<arr[i]<<endl;
            cout<<"------------------"<<endl;
       }

   }
   //Function To Find an Item by ID .
   void Find_an_Item_by_ID(int U)
   {
       for(int i=0;i<counter_of_Item;i++)
       {
           if(arr[i].ID==U)
           {
               cout<<arr[i]<<endl;
               return ;

           }
       }
       cout<<"NOT FOUNDED"<<endl;
   }
//Destructor
 ~Seller()
 {
     delete []arr;
 }

};
int Seller::counter_of_Item=0;
istream &operator>>(istream&input,Seller &obj)
    {
        input>>obj.namee;
        input>>obj.email;
        return input;
    }
ostream  &operator<<(ostream&output,const Seller &obj2)
    {
        cout<<"Name: ";
        output<<obj2.namee;
        cout<<endl;
        cout<<"Email: ";
        output<<obj2.email;
        cout<<endl;
        return output;
    }

int main()
{
    int num_of_items;
    Item obj_of_item;

    string N,E;
    int I,num_of_choose=0;
    cout<<"Enter Your Details:"<<endl<<endl;
    cout<<"Please enter your name: ";
    cin>>N;
    cout<<"Please enter your email: ";
    cin>>E;
    cout<<"Please enter your capacity: ";
    cin>>I;
    Seller obj_of_seller(N,E,I);
    cout<<"Please enter number of items: ";
    cin>>num_of_items;
    cout<<endl;
    cout<<"ENTER YOUR PRODUCTS: "<<endl<<endl;
    for(int i=0;i<num_of_items;i++)
    {
        cout<<"Product "<<i+1<<":"<<endl;
        cin>>obj_of_item;
        obj_of_seller.Set_Elem_In_arr(obj_of_item);
        cout<<endl;
    }

    cout<<"************************************"<<endl;
    cout<<"1 - print My Info"<<endl;
    cout<<"2 - Add An Item"<<endl;
    cout<<"3 - Sell An Item"<<endl;
    cout<<"4 - Print Items"<<endl;
    cout<<"5 - Find An Item by ID"<<endl;
    cout<<"6 - Exit"<<endl;
    cout<<"************************************"<<endl;

    while(num_of_choose !=6)
    {
        cout<<endl;
        cout<<"Choose What you want to do: ";
        cin>>num_of_choose;
        cout<<endl;
        if(num_of_choose==1)
        {
            cout<<obj_of_seller;
        }
        else if(num_of_choose==2)
        {
            cout<<"Please Enter Item Name,Quantity and price :"<<endl;
            cin>>obj_of_item;
            obj_of_seller.Add_An_Item(obj_of_item);
            cout<<"The item has been added succesfully"<<endl;

        }
        else if(num_of_choose==3)
        {
            string Product_You_Need_To_Sell_it;
            int Quantity_Of_Product;
            cout<<"Enter The Product You Need To Sell it: ";
            cin>>Product_You_Need_To_Sell_it;
            cout<<"Enter Quantity Of Product You Need To Sell it: ";
            cin>>Quantity_Of_Product;
            obj_of_seller.Sell_An_Item(Product_You_Need_To_Sell_it,Quantity_Of_Product);

        }
         else if(num_of_choose==4)
         {
             obj_of_seller.Print_Items();
         }
         else if(num_of_choose==5)
         {
             int id;
             cout<<"Enter The Id: ";
             cin>>id;
             obj_of_seller.Find_an_Item_by_ID(id);
         }
         else if(num_of_choose==6)
         {
             break;
         }
    }

}
