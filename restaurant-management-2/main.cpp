#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;
template<class T1,class T2>                                     //Class template
class Restaurant{
    string* restaurant_name;
    T1 opens;
    T2 closes;
    public:                  
        Restaurant(){       
            restaurant_name=new string;
            *restaurant_name="CHILL BAY RESTAURANT";
            cout<<"-------------WELCOME TO CHILL BAY RESTAURANT-------------"<<endl;
        }
        void open(){                                                        //function overloading
            cout<<"                  Opens at 10:00 am"<<endl;
            cout<<"                  Closes at 10:00 pm"<<endl;
        }
        void open(T1 opens,T2 closes){                              //function overloading
            this->opens=opens;
            this->closes=closes;
            cout<<"                  Opens at "<<opens<<" am"<<endl;
            cout<<"                  Closes at "<<closes<<" pm"<<endl;
        }
        ~Restaurant(){}      
};
class Customer{
    private:                    
        string customer_name;
        int customer_age;
        long phone_no;
    public:
        void customer_details(){
            string MyText;
            cout<<"Enter name of customer: ";
            cin>>customer_name;
            ofstream out("Customer_details.txt");               //writing file
            out<<"Customer Name: "<<customer_name<<"\n";
            cout<<"Enter age: ";
            cin>>customer_age;
            out<<"Customer Age: "<<customer_age<<"\n";
            cout<<"Enter your phone number: ";
            cin>>phone_no;
            out<<"Customer Phone No.: "<<phone_no<<"\n";
            out.close();
            ifstream in("Customer_details.txt");                //reading file
            cout<<"-------------Reading Customer Details File---------------"<<endl;
            while (getline (in,MyText)) {
                cout <<MyText<<endl;
            }
            in.close();
        }
};
class Menu{
    int* item_id{new int[10]{1,2,3,4,5,6,7,8,9,10}};
    string* item_name{new string[10]{"Cold Coffee","Garlic Bread","Grilled Sandwich","Hot Chocolate","Pasta","Pizza","Burger","Lasagna","French Fries","Brownie"}};
    int* amount{new int[10]{100,140,60,110,175,250,100,295,95,200}};
    friend class Bill;           
    public:
        void display_items(){
            cout<<"--------------------------Menu---------------------------"<<endl;
            cout<<"Id - Name - Price"<<endl;
            for(int i=0;i<10;i++){
                cout<<item_id[i]<<". "<<item_name[i]<<" = "<<amount[i]<<endl;
            }
        }
};
class Employees{
    string employee_name;
    protected:                 
        static int employee_id;
        int employee_salary;
    public:
        void employee_details(){
            cout<<"Enter name of Employee: ";
            cin>>employee_name;
        }
        virtual void create_reservation()=0;                //Pure virtual function
        virtual void display_details(){                     //Virtual function
            employee_id++;
            cout<<"Employee Id: "<<employee_id<<endl;
            cout<<"Employee name: "<<employee_name<<endl;
            cout<<"Employee salary: "<<employee_salary<<endl;
        }
};
int Employees::employee_id=1000;        
class Receptionist:public Employees{    
    static int reservation_id;
    char* datetime;
    public:
        Receptionist(){                 
            this->employee_salary=15000;
        }
        void display_details(){
            reservation_id++;
            cout<<"Your Reservation Id is: "<<reservation_id<<endl;
        }
        void create_reservation(){
            time_t now = time(0);                      
            datetime = ctime(&now);
            cout << "Reservation date and time: "<<datetime;
        }
        ~Receptionist(){}              
};
int Receptionist::reservation_id=100;
class Waiter:public Employees{
    int& waiterId=this->employee_id;
    static int orderId;
    public:
        Waiter(){                          
            this->employee_salary=10000;
        }
        void create_reservation(){}
        void give_orderId(){
            orderId++;
            cout<<"Your orderId is: "<<orderId<<endl; 
        }
};
int Waiter::orderId;
class Chef:public Employees{
    public:
        Chef(){
            this->employee_salary=20000;
        }
        void create_reservation(){}
};
class Table{
    int* table_no{new int[10]{1,2,3,4,5,6,7,8,9,10}};
    int* occupied_status{new int[10]{1,1,1,1,1,1,1,1,1,1}};
    public:
        void table_details(){
            for(int i=0;i<10;i++){
                if(occupied_status[i]==1){
                    cout<<"Your Table number is: "<<table_no[i]<<endl;
                    occupied_status[i]=0;
                    break;
                }
            }
        }
};
template<class T,int size>                      //Nontype template argument
class Order{
    Menu m;
    int no_of_items;
    T itemId[size];
    friend class Bill;             
    public:
        int* order_items(){ 
            cout<<"How many items you want to order: ";
            cin>>no_of_items;
            cout<<"Give your order(Item Id): ";
            for(int i=0;i<no_of_items;i++){
                cin>>itemId[i];
            }
            for(int i=no_of_items;i<size;i++){
                itemId[i]=0;
            }
            return itemId;          
        }
};
class Bill{
    double total_bill=0;
    int m;
    public:
        Bill(){}
        Bill(Menu m,Order<int,10> o){               
            cout<<"Id - Name - Price"<<endl;
            for(int i=0;i<10;i++){
                for(int j=0;j<10;j++){
                    if(o.itemId[i]==m.item_id[j]){
                        total_bill+=m.amount[j];
                        cout<<m.item_id[j]<<". "<<m.item_name[j]<<" = "<<m.amount[j]<<endl;
                    }
                }
            }
            cout<<"Total = "<<total_bill<<endl;
            cout<<"Service Tax (10%"<<") = "<<0.1*total_bill<<endl;
            cout<<"GST (5%"<<") = "<<0.05*total_bill<<endl;
        }
        void operator++(){                                  //operator overloading
            total_bill=0.1*total_bill+(0.05*total_bill)+total_bill;
        }
        void display_bill(){
            cout<<"Total payable amount = "<<total_bill<<endl;
        }
};
class Payment{             
    Bill b;             
    string mode_of_payment;
    public:
        void payment_mode(){
            cout<<"-----------------------Payment---------------------------"<<endl;
            cout<<"Choose Payment Mode(Cash or Card): ";
            cin>>mode_of_payment;
        }
        void ispaid(){
            try{                                                //Exception handling
                if (mode_of_payment!="Cash" && mode_of_payment!="Card"){
                    throw "Payment declined! Enter valid mode of payment.";
                }
                cout<<"Payment done !"<<endl;
                cout<<"Thank you, please visit again!"<<endl;
            }
            catch(const char *ex){
                cout<<ex<<endl;
            }
        }
};
int main(){
    Restaurant<char*,char*> XYZ;         //Class template   
    char open[6]="9:00";
    char close[6]="9:00";
    //XYZ.open();                       //function overloading in use
    XYZ.open(open,close);               //function overloading in use
    cout<<"---------------------------------------------------------"<<endl;
    int button;
    cout<<"Enter 1 if you are Employee."<<endl;
    cout<<"Enter 2 if you are Customer."<<endl;
    cin>>button;
    switch(button){
        case 1:{
            int plug;
            cout<<"Enter 1 for Receptionist."<<endl;
            cout<<"Enter 2 for Waiter."<<endl;
            cout<<"Enter 3 for Chef."<<endl;
            cin>>plug;
            int no_of_entries;
            cout<<"Input number of entries: ";
            cin>>no_of_entries;
            switch(plug){
                case 1:{
                    Receptionist* r=new Receptionist[no_of_entries];     
                    for(int i=0;i<no_of_entries;i++){
                        cout<<"---------------------------------------------------------"<<endl;
                        r[i].employee_details();
                        r[i].Employees::display_details();
                    }
                    break;
                }
                case 2:{
                    Waiter* w=new Waiter[no_of_entries];     
                    for(int i=0;i<no_of_entries;i++){
                        cout<<"---------------------------------------------------------"<<endl;
                        w[i].employee_details();
                        w[i].display_details();
                    }
                    break;
                }
                case 3:{
                    Chef* c=new Chef[no_of_entries];     
                    for(int i=0;i<no_of_entries;i++){
                        cout<<"---------------------------------------------------------"<<endl;
                        c[i].employee_details();
                        c[i].display_details();
                    }
                    break;
                }
                default:{
                    cout<<"Invalid Input!"<<endl;
                }
            }
            break;
        }
        case 2:{
            int no_of_customers;
            cout<<"Enter number of customers: ";
            cin>>no_of_customers;
            Customer c[no_of_customers];
            for(int i=0;i<no_of_customers;i++){
                cout<<"-----------------Enter customer details------------------"<<endl;
                c[i].customer_details();
                cout<<"-------------------Creating reservation------------------"<<endl;
                Employees* e;
                Receptionist r;
                e=&r;
                //e->display_details();         // virtual function in use
                r.display_details();            //function overridding
                e->create_reservation();        //pure virtual function in use
                Table t;
                t.table_details();
                Menu m;
                m.display_items();
                cout<<"--------------------------Order--------------------------"<<endl;
                Waiter w;
                w.give_orderId();
                Order<int,10>o;
                o.order_items();
                cout<<"--------------------------Bill---------------------------"<<endl;
                Bill b(m,o);
                ++b;                            //calling "void operator++()"
                b.display_bill();
                Payment p;
                p.payment_mode();
                p.ispaid();
            }
            cout<<"---------------------------------------------------------"<<endl;
            break;
        }
        default:{
            cout<<"Invalid Input!"<<endl;
        }   
    }
    return 0;
}