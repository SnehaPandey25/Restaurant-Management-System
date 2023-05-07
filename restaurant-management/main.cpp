#include <iostream>
#include <ctime>
using namespace std;
class Restaurant{
    string* restaurant_name;
    public:                  //public access specifier
        Restaurant(){       //dynamic constructor
            restaurant_name=new string;
            *restaurant_name="CHILL BAY RESTAURANT";
            cout<<"-------------WELCOME TO CHILL BAY RESTAURANT-------------"<<endl;
        }
        void open(){
            cout<<"                  Opens at 10:00 am"<<endl;
            cout<<"                  Closes at 10:00 pm"<<endl;
        }
        ~Restaurant(){}      //destructor 
};
class Customer{
    private:                    //private access specifier
        string customer_name;
        int customer_age;
        long phone_no;
    public:
        void customer_details(){
            cout<<"Enter name of customer: ";
            cin>>customer_name;
            cout<<"Enter age: ";
            cin>>customer_age;
            cout<<"Enter your phone number: ";
            cin>>phone_no;
        }
};
class Menu{
    int* item_id{new int[10]{1,2,3,4,5,6,7,8,9,10}};
    string* item_name{new string[10]{"Cold Coffee","Garlic Bread","Grilled Sandwich","Hot Chocolate","Pasta","Pizza","Burger","Lasagna","French Fries","Brownie"}};
    int* amount{new int[10]{100,140,60,110,175,250,100,295,95,200}};
    friend class Bill;              //friend class
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
    protected:                  //protected access specifier
        static int employee_id;
        int employee_salary;
    public:
        void employee_details(){
            cout<<"Enter name of Employee: ";
            cin>>employee_name;
        }
        void employee_get_details(){
            employee_id++;
            cout<<"Employee Id: "<<employee_id<<endl;
            cout<<"Employee name: "<<employee_name<<endl;
            cout<<"Employee salary: "<<employee_salary<<endl;
        }
};
int Employees::employee_id=1000;        
class Receptionist:public Employees{    //hierarchical inheritance
    static int reservation_id;
    char* datetime;
    public:
        Receptionist(){                 //inheritance constructor
            this->employee_salary=15000;
        }
        void create_reservation(){
            reservation_id++;
            cout<<"Your Reservation Id is: "<<reservation_id<<endl;
            time_t now = time(0);                       //time module
            datetime = ctime(&now);
            cout << "Reservation date and time: "<<datetime;
        }
        ~Receptionist(){}               //inheritance destructor
};
int Receptionist::reservation_id=100;
class Waiter:public Employees{
    int& waiterId=this->employee_id;        //independent reference
    public:
        Waiter(){                           //default constructor
            this->employee_salary=10000;
        }
};
class Chef:public Employees{
    public:
        Chef(){
            this->employee_salary=20000;
        }
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
class Order{
    Menu m;                     //Container class
    static int orderId;
    int no_of_items;
    int* itemId{new int[10]};
    friend class Bill;              // friend class
    public:
        int* order_items(){
            orderId++;
            cout<<"Your orderId is: "<<orderId<<endl;
            cout<<"How many items you want to order: ";
            cin>>no_of_items;
            cout<<"Give your order(Item Id): ";
            for(int i=0;i<no_of_items;i++){
                cin>>itemId[i];
            }
            return itemId;          // function returning reference
        }
};
int Order::orderId;
class Bill{
    double total_bill=0;
    public:
        Bill(){}
        Bill(Menu m,Order o){               //parameterised constructor
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
            cout<<"Service Tax (10%"<<") = "<<0.1*(total_bill)<<endl;
            cout<<"GST (5%"<<") = "<<0.05*(total_bill)<<endl;
            total_bill=((0.1)*total_bill)+(0.05*(total_bill))+total_bill;
            cout<<"Total payable amount = "<<total_bill<<endl;
        }
};
class Payment{              //Container class
    Bill b;             
    string mode_of_payment;
    public:
        void payment_mode(){
            cout<<"-----------------------Payment---------------------------"<<endl;
            cout<<"Choose Payment Mode(Cash or Card): ";
            cin>>mode_of_payment;
        }
        void ispaid(){
            if (mode_of_payment=="Cash" || mode_of_payment=="Card"){
                cout<<"Payment done !"<<endl;
                cout<<"Thank you, please visit again!"<<endl;
            }
            else{
                cout<<"Payment declined! Enter valid mode of payment."<<endl;
            }
        }
};
int main(){
    Restaurant XYZ;       
    XYZ.open();
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
                    Receptionist* r=new Receptionist[no_of_entries];     //dynamic array of objects
                    for(int i=0;i<no_of_entries;i++){
                        cout<<"---------------------------------------------------------"<<endl;
                        r[i].employee_details();
                        r[i].employee_get_details();
                    }
                    break;
                }
                case 2:{
                    Waiter* w=new Waiter[no_of_entries];     //dynamic array of objects
                    for(int i=0;i<no_of_entries;i++){
                        cout<<"---------------------------------------------------------"<<endl;
                        w[i].employee_details();
                        w[i].employee_get_details();
                    }
                    break;
                }
                case 3:{
                    Chef* c=new Chef[no_of_entries];     //dynamic array of objects
                    for(int i=0;i<no_of_entries;i++){
                        cout<<"---------------------------------------------------------"<<endl;
                        c[i].employee_details();
                        c[i].employee_get_details();
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
                Receptionist r;
                r.create_reservation();
                Table t;
                t.table_details();
                Menu m;
                m.display_items();
                cout<<"--------------------------Order--------------------------"<<endl;
                Order o;
                o.order_items();
                cout<<"--------------------------Bill---------------------------"<<endl;
                Bill b(m,o);
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
