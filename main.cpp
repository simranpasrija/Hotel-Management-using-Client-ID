#include <bits/stdc++.h>
#include <windows.h>

using namespace std;
//base class
class client
{
public:
    //base class data members
    static int c_id_count;
    int cost_cnt;
    char c_type;
    
    //base class member functions
    //using csv file to store & check the user data
    //virtual function for polymorphism
    virtual void check() {
        //Here searching if a client has his / her account
        fstream fin;
        fin.open("client.csv", ios::in);
        string target_phn,phn;
        int count = 0;
        cout << "\nEnter the phone number of the client to display details: ";
        cin >> target_phn;
        
        //using vector to get a line at a time
        vector<string> row;
        string line, word;
        
        while (fin >> line) {
            row.clear();
            stringstream s(line);
            
            //get the data splitting by comma from the line
            while (getline(s,word,',')) {
            row.push_back(word);
            }
            
            phn = row[2];
            
            if (target_phn == phn) {
                //printing the client data
                count = 1;
                cout << "\nClient ID: " << row[0] << "\n";
                cout << "Name: " << row[1] << "\n";
                cout << "Phone No: " << row[2] << "\n";
                cout << "Address: " << row[3] << "\n";
                cout << "Aadhar: " << row[4] << "\n";
                break;
            }
        }
        
        //if the client isn't registered
        if (count == 0)
            cout << "\nRecord not found\n";

    }
    // virtual function for polymorphism
    virtual int update() {
        fstream fout;
        //open file to append new client data
        fout.open("client.csv", ios::out | ios::app);
        int c_id;
        
        //getting the client informations
        string c_name;
        string c_phone_no;
        string c_address;
        string c_aadhar;
        
        cout << "\nEnter Client ID: ";
        cin >> c_id;
        cout << "Enter Client Name: ";
        cin >> c_name;
        cout << "Enter Client Phone No: ";
        cin >> c_phone_no;
        cout << "Enter Client Address: ";
        cin >> c_address;
        cout << "Enter Client Aadhar:";
        cin >> c_aadhar;
        
        //printing the client details in csv file
        fout << c_id << ","
                 << c_name << ","
                 << c_phone_no << ","
                 << c_address << ","
                 << c_aadhar << "\n";
        fout.close();
        return 0;
    }
    /*
    we can also get the information using constructor
    client(string c_name,string c_phone_no,string c_address,string c_aadhar,char c_type)
    {
        c_id_count++;
        c_id = c_id_count;
        this->c_name = c_name; 
        this->c_phone_no = c_phone_no; 
        this->c_address = c_address; 
        this->c_aadhar = c_aadhar; 
        this->c_type = c_type;
    }
    */
};

//derived class of the base class client
//virtually inherited client to solve diamond problem
class client_hotelroom:virtual public client
{
public:
    //extended check function to check if a hotel room is vacant
    void check() {
        //opening txt file to read
        ifstream inf("hotelroom.txt");
        
        //if the text file is not available
        if(!inf) 
            cout << "\nUnable to open hotelroom file"<<endl;
            
        int room_id; string room_type; string room_book;
        cout << "\nTypes of Hotel rooms available to book: "<<endl;
        cout << "\nRoom ID \tRoom Type\n";
        
        //reading the whole file to print available hotel rooms
        while (!inf.eof()) {
            inf >> room_id >> room_type >> room_book;
            if(room_book == "NULL")
                cout << "  " << room_id << "\t         " << room_type << endl;
        }
        //closing the file
        inf.close();
    }  
    //extented update funtion to book a hotel room
    int update() {
        //taking the information to book a definite room
        int target_room_id,c_id;
        cout << "\nPlease enter the required room id: ";
        cin >> target_room_id;
        cout << "Please enter the client id: ";
        cin >> c_id;
        
        //changing the int c_id to string client_id to compare
        string client_id;
        stringstream ss;
        ss << c_id;
        client_id = ss.str();
        
        //opening the text file to read and append
        ifstream inf("hotelroom.txt");
        ofstream outf("hotelroom1.txt");
        
        if(!inf) 
            cout<< "\nUnable to open hotelroom file" << endl;
            
        int room_id; string room_type; string room_book;
        
        //taking all the data to book the required room
        while (!inf.eof()) {
            inf>>room_id>>room_type>>room_book;
            
            if(room_id==target_room_id) {
                //using the base class data member to calculate client's cost
                switch(room_id){
                    case 101 : 
                        cost_cnt+=1000;
                    case 102 : 
                        cost_cnt+=1000;
                    case 103 : 
                        cost_cnt+=1000;
                    case 201 : 
                        cost_cnt+=2000;
                    case 202 : 
                        cost_cnt+=2000;
                    case 203 : 
                        cost_cnt+=3000;
                    case 204 : 
                        cost_cnt+=3000;
                    case 301 : 
                        cost_cnt+=5000;
                    case 302 : 
                        cost_cnt+=5000;
                    case 401 : 
                        cost_cnt+=1000;
                    case 402 : 
                        cost_cnt+=1000;
                    case 403 : 
                        cost_cnt+=1000;
                    case 404 : 
                        cost_cnt+=3000;
                    case 501 : 
                        cost_cnt+=9000;
                }
                
                //using the base class data member to check
                cout << "\nRoom booked succesfully" << endl;
                cout << room_id << " " << room_type << endl;
                //updating the room id with client_id to make it booked
                outf << room_id << " " << room_type << " " << client_id << endl;
            }
            else {
                //if it isn't the required room then simply rewriting it
                outf << room_id << " " << room_type << " " << room_book << endl;
            }
        }
        
        //closing the two files to save update
        outf.close();
        inf.close();
        
        //deleting previous text file then renaming the updated textfile to replace the previous one
        remove("hotelroom.txt");
        rename("hotelroom1.txt","hotelroom.txt");
        return cost_cnt;
    }
    //checkout a booked room to make it available again
    void checkout() {
        //getting necessary information and changing to string
        int c_id;
        cout << "\nPlease enter the client id: ";
        cin >> c_id;
        
        string client_id;
        stringstream ss;
        ss << c_id;
        client_id = ss.str();
        
        //read & write the text file
        ifstream inf("hotelroom.txt");
        ofstream outf("hotelroom1.txt");
        
        if(!inf) 
            cout << "\nUnable to open hotelroom file"<<endl;
            
        int room_id; string room_type; string room_book;
        //updating the rooms which the client hold to make it available
        while (true) {
            inf >> room_id >> room_type >> room_book;
            if(inf.eof()) 
                break;
            if(room_book==client_id) {
                cout << room_id << " " << room_type << endl;
                outf << room_id << " " << room_type << " " << "NULL" << endl;
                cout << "\nCheckout successful";
            }
            else {
                outf << room_id << " " << room_type << " " << room_book << endl;
            }
        }
        
        //closing the file and replacing the previous file
        outf.close();
        inf.close();
        remove("hotelroom.txt");
        rename("hotelroom1.txt","hotelroom.txt");
    }
    
    //virtual function for polymorphism in derived class cost
    virtual void display_cost(){};
};

//client's derived class to book the convention hall
class client_banquethall:virtual public client
{
    public:
        //check function to check if the hall is empty in the required time
    void check() {
        //opening the text file and taking necessary informations
        ifstream inf("banquet.txt");
        if (!inf) 
            cout << "\nUnable to open banquet file" << endl;
            
        string day,time,hall_book,target_day,target_time; 
        string res = "No reservations for the entered date and time";
        cout << "\nEnter the date to check for reservation(Ex: 23/10/2020): ";
        cin >> target_day;
        cout << "Enter the time to check for reservation(Ex: 18:00): ";
        cin >> target_time;
        
        //If the entered time exists already then the result(res) will be changed to reserved
        while (!inf.eof()) {
            inf >> day >> time >> hall_book;
            cout << day << " " << time << " " << hall_book << endl;
            if (day==target_day && time==target_time) 
                res = "Banquet hall is already reserved for the given date and time";
        }
        
        //Closing the file after displaying acknowledgment
        cout << endl << res << endl;
        inf.close();
    }
    //updating the booking of the convention hall
    int update() {
        //taking necessary infos to book a time
        string target_day,target_time;int c_id;
        cout << "\nEnter the date to book the Banquet hall: ";
        cin >> target_day;
        cout << "Enter the time for booking: ";
        cin >> target_time;
        cout << "Enter the Client ID : ";
        cin >> c_id;
        cout << "\nBooking successful";
        
        //cost count
        cost_cnt+=30000;
        
        //opening the text file to append
        ofstream outf("banquet.txt",ios::app);
        outf << endl << target_day << " " << target_time << " " << c_id;
        outf.close();
        return cost_cnt;
    }
    virtual void display_cost(){};
};

//derived class of client to book restaurant
class client_restaurant:virtual public client
{
public:
    //check if the restaurant is booked or not
    void check()
    {
        //input the necessary infos
        ifstream inf("restaurant.txt");
        if(!inf) 
            cout << "\nUnable to open restaurant file" << endl;
            
        string day,time,res_book,target_day,target_time;
        string res = "No reservations for the entered date and time";
        
        cout << "\nEnter the date to check for reservation(Ex: 23/10/2020): ";
        cin >> target_day;
        cout << "Enter the time to check for reservation(Ex: 18:00): ";
        cin >> target_time;
        
        //comparing with the required time and giving result
        while(!inf.eof())
        {
            inf >> day >> time >> res_book;
            cout << day << " " << time << " " << res_book << endl;
            if(day==target_day && time==target_time)
                res = "Restaurant table is already reserved for the given date and time";
        }
        cout<<endl<<res<<endl;
        inf.close();
    }
    //booking restaurant table
    int update()
    {
        //taking necessary infos to book a time
        string target_day,target_time;int c_id;
        cout << "\nEnter the date to book the Restaurant table: ";
        cin >> target_day;
        cout << "Enter the time for booking: ";
        cin >> target_time;
        cout << "Enter the Client ID : ";
        cin >> c_id;
        cout << "\nBooking successful";
        
        //cost count
        cost_cnt+=200;
        
        //write the text file and returning cost
        ofstream outf("restaurant.txt",ios::app);
        outf<<endl<<target_day<<" "<<target_time<<" "<<c_id;
        outf.close();
        return cost_cnt;
    }
    virtual void display_cost(){};
};

//derived class of children of the base class, creating diamond problem
//cost class derived from all the derived class of client
class cost : public client_banquethall, public client_hotelroom, public client_restaurant
{
public:
    //check and update function for creating polymorphism
    void check(){}
    int update() {return 0;}
    
    //displaying the total cost of a client
    //previously declared virtually
    void display_cost(int cost)
    {
        cout << "\nTotal cost: Rs. " << cost << endl;
        int paid,total_paid; 
        C:cout << "Amount paid: Rs. ";
        cin >> paid;
        total_paid += paid;
        if(total_paid < cost){
            cout << "Paid amount less than Total cost, Please pay Rs. " << cost-total_paid << " more\n";
            goto C;
        }
        cout << "Change Amount: Rs. " << total_paid-cost << endl;
    }
    
    //operator overloading to compute the cost
    cost operator - (cost c)
    {
        cost c3;
        c3.cost_cnt = c.cost_cnt - this->cost_cnt;
        return c3;
    }
};

void gotoxy(short x=0,short y=0)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x,y};
    SetConsoleCursorPosition(out,c);
}

void displayHeading() {
    cout << "\t\t\t\t\t  _    _       _       _    _____ _____  \n";
    cout << "\t\t\t\t\t | |  | |     | |     | |  / ____/ ____| \n";
    cout << "\t\t\t\t\t | |__| | ___ | |_ ___| | | (___| (___   \n";
    cout << "\t\t\t\t\t |  __  |/ _ \\| __/ _ \\ |  \\___ \\\\___ \\  \n";
    cout << "\t\t\t\t\t | |  | | (_) | ||  __/ |  ____) |___) | \n";
    cout << "\t\t\t\t\t |_|  |_|\\___/ \\__\\___|_| |_____/_____/  \n";
    
    cout << "\n\n\t\t\t\t\t\tWelcome Shubham!\n\n\n";
    
}

bool login() {
    //strings for username and password
    string userName;
    string userPassword;
    int loginAttempt = 0;
    cout << "\n\n\n\n\tLOGIN\n";
    
    //while loop to limit login attempts
    while (loginAttempt < 5)
    {
        //taking input from user
        cout << "\n\tPlease enter your user name: ";
        cin >> userName;
        cout << "\tPlease enter your user password: ";
        cin >> userPassword;
        
        //checking for correct username and password
        if (userName == "shubham" && userPassword == "sahu")
        {
            cout << "\n\n\t\t\t\t\t\tWelcome Shubham!\n";
            break;
        }
        else if (userName == "simran" && userPassword == "pasrija")
        {
            cout << "\n\n\t\t\t\t\t\tWelcome Simran!\n";
            break;
        }
        //failed attempt
        else
        {
            cout << "\tInvalid login attempt. Please try again.\n" << '\n';
            loginAttempt++;
        }
    }
    //login attempts exceeded
    if (loginAttempt == 5)
    {
            cout << "\tToo many login attempts! The program will now terminate.";
            return 0;
    }
    return 1;
}

//main function
int main()
{
    //base class pointer and other class objects
    client *bptr; 
    int t = -1;
    int p = -1;
    client c1;
    client_banquethall bh1;
    client_hotelroom h1;
    client_restaurant r1;
    cost c2;
    
    //displaying introduction
    system("Color 06");
    cout << "\t\t\t\t\t  _    _       _       _    _____ _____  \n";
    cout << "\t\t\t\t\t | |  | |     | |     | |  / ____/ ____| \n";
    cout << "\t\t\t\t\t | |__| | ___ | |_ ___| | | (___| (___   \n";
    cout << "\t\t\t\t\t |  __  |/ _ \\| __/ _ \\ |  \\___ \\\\___ \\  \n";
    cout << "\t\t\t\t\t | |  | | (_) | ||  __/ |  ____) |___) | \n";
    cout << "\t\t\t\t\t |_|  |_|\\___/ \\__\\___|_| |_____/_____/  \n";
    
    int check = login();
    if(check == 0) goto D;
    
    system("PAUSE");
    system("CLS");
    
    //displaying the options
    while(t!=0 && p!=0){
        //options to create and search client id
        A:
        cout << "\n   Client ID Menu\n" << endl;
        cout << "[1] Search for a Client ID" << endl;
        cout << "[2] Create a new Client ID" << endl; 
        cout << "[0] Skip to Booking/checkout" << endl;
        cout << "\nEnter your choice: ";
        cin >> t;
        
        //base class pointer pointing to a base class object
        bptr = &c1;
        
        //exception handing if gives unnecessary inputs
        try {
            if(t==1) 
                bptr->check();
            else if(t==2) 
                bptr->update();
            else if (t==0) {}
            else throw(t);
        }
        catch(...) {
            cout << "\nInvalid input, Please try again";
            goto A;
        }
        
        //options to book and checkout
        B:
        cout << "\nBooking and Checkout Menu";
        cout << "\n[1] Book a Hotel room"; 
        cout << "\n[2] Book the Banquet hall";
        cout << " \n[3] Book Restaurant table";
        cout << "\n[4] Check out Hotel room";
        cout << "\n[5] Go back to Client ID menu";
        cout << "\n[0] Exit" << endl;
        cout << "\nEnter your choice: ";
        cin >> p;
        
        //exception handling if given unnecessary inputs
        try {
            //base class pointer pointing to derived class objects
            if (p==1) {
                bptr = &h1;
                bptr->cost_cnt=0;
                bptr->check();
                cout << "\nEnter 1 to Checkin \nEnter 0 to skip"<<endl;
                cout << "\nEnter your choice: ";
                int q,d=0;
                cin >> q;
                if (q==1) {
                    int i;
                    cout << "\nEnter number of rooms to book: ";
                    cin >> i;
                    while (i--) 
                        d += bptr->update();
                    c2.display_cost(d);
                }
                else goto B;
            }
            else if (p==2) {
                bptr = &bh1;
                bptr->cost_cnt=0;
                bptr->check();
                cout << "\nEnter 1 to book \nEnter 0 to skip"<<endl;
                cout << "\nEnter your choice: ";
                int j;
                cin >> j;
                if (j==1){
                    c2.display_cost(bptr->update());
                }
                else goto B;
            }
            else if(p==3) {
                bptr= &r1;
                bptr->cost_cnt=0; 
                bptr->check();
                cout << "\nEnter 1 to book \nEnter 0 to skip"<<endl;
                cout << "\nEnter your choice: ";
                int k;
                cin >> k;
                if(k==1){ 
                    c2.display_cost(bptr->update());
                }
                else goto B;
            }
            else if (p==4) {h1.checkout(); goto B;}
            else if (p==5) {goto A;}
            else if (p==0) {}
            else throw(p);
        }
        catch(...) {
            cout << "\nInvalid input, Please try again";
            goto B;
        }
    }
    D:cout << "\n\n";
    return 0;
}