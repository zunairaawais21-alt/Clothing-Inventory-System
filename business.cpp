#include <iostream>
#include<conio.h>
#include<windows.h>
#include <string>
#include <iomanip>
#include <fstream>

// Store in txt file 

// ali,abc12,admin,
// noor,nf67,user,
// ;
// shirt,t-shirt,50,20,15.0,2.0,30.0
// pants,cargo pants,60,30,20.0,3.0,45.0
// jacket,leather jacket,30,10,50.0,5.0,100.0
// shoes,sneakers,20,5,80.0,8.0,150.0
// shirt,Polo-Shirt,40,15,25.0,5.0,25.0

using namespace std;

// Function declarations
string signIn(string &uN,string &uP,string userNames[], string userPasswords[], string userRoles[], int &userCount, int &idx);
void SignUp(string &uN,string &uP,string &uR,string userNames[], string userPasswords[], string userRoles[], int &userCount,int &userCapacity);
void print_header();
void printMenuHeader(string mainMenu,string subMenu);
int main_menu();
int admin_menu();
int user_menu();
void user_interface(int &garment_count,string &day, string names[], int stock_left[], double retail_price[], int units[], int sold[], string types[], float &amount, float &change, float &discount, int &free_items, string &garment_name, int &quantity, double &total_price, int &cart_idx, string cart[], int idx, string userHistory[]);
void clearScreen();
void admin_interface(int &garment_count, int MAX_GARMENTS, string names[], int units[], double whole_sale[], double shipping[], double retail_price[], int sold[], int stock_left[],string userNames[], string userPasswords[], string userRoles[], string &garment_name, int &quantity, double &total_price, string &day, float &amount, float &change, float &discount, int &free_items, int &userCount, string userHistory[]);
void input_garment(int &garment_count, int &MAX_GARMENTS, string names[], int units[], double whole_sale[], double shipping[], double retail_price[], int sold[]);   
void view_profit(int &garment_count, string names[], int units[], double whole_sale[], double shipping[], double retail_price[], int sold[], int stock_left[]);        
void delete_garment(int &garment_count, string names[], int units[], double whole_sale[], double shipping[], double retail_price[], int sold[]); 
void view_garments(int garment_count, string names[], int stock_left[], double retail_price[]);
void view_customers(string userNames[], string userPasswords[], string userRoles[], string userHistory[], int userCount);
void setColor(int color); 
void make_purchase(string &garment_name,string &day, int &quantity,double &total_price,int &garment_count, string names[], int units[], double retail_price[], int sold[], int stock_left[],int &cart_idx,string cart[], int idx, string userHistory[], string types[], int &free_items);
void view_purchase_history(string userHistory[], int idx, int quantity, double total_price);
void view_catogories(int &garment_count,string types[],string names[],double retail_price[],int stock_left[]);
float update_amount(double &total_price, float &amount, float &change);
void add_to_cart(string &garment_name, int &quantity, double &total_price, int &garment_count, string names[], int units[], double retail_price[], int sold[], int stock_left[],int &cart_idx,string cart[]);
void receipt_generation(string &garment_name, int &quantity, double &total_price, float &amount, float &change, float &discount, string &day, int &free_items);
void updateStock(int &garment_count,string names[], int units[], int sold[],int stock_left[]);
void updateStockArray(int &garment_count, int stock_left[], int units[], int sold[]);
void sort_garments_by_units(int &garment_count, string names[], int stock_left[], double retail_price[], int units[], int sold[], string types[]);
//int saveData(int &userCount,string &file_name,string userNames[],string userPasswords[],string userRoles[],int &userCapacity);
//int loadData(int &userCount,string &file_name,string userNames[],string userPasswords[],string userRoles[],int &userCapacity);

void saveToFile(string userNames[], string userPasswords[], string userRoles[], string userHistory[], int userCount, string types[], string names[], int units[], int sold[], double whole_sale[], double shipping[], double retail_price[], int garment_count) {
    
    fstream file;
    file.open("GarmentStore.txt", ios::out);
    
    // User Data
    for(int i = 0; i < userCount; i++) {
        file << userNames[i] << "," << userPasswords[i] << "," << userRoles[i] << "," << userHistory[i];
        file << endl;
    }
    file << ";" << endl;
    
    // Garment Data
    for(int i = 0; i < garment_count; i++) {
        file << types[i] << "," << names[i] << "," << units[i] << "," << sold[i] << "," 
             << whole_sale[i] << "," << shipping[i] << "," << retail_price[i];
        file << endl;
    }
    
    file.close();
}
void readingFile(string userNames[], string userPasswords[], string userRoles[], string userHistory[], int &userCount, string types[], string names[], int units[], int sold[], double whole_sale[], double shipping[], double retail_price[], int &garment_count) {
    
    userCount = 0;
    garment_count = 0;
    
    fstream file;
    file.open("GarmentStore.txt", ios::in);
    
    // if(!file) {
    //     cout << "No saved data found. Starting with default values." << endl;
    //     return;
    // }
    
    string line;
    
    // USER DATA
    while(getline(file, line)) {
        if(line == ";") 
            break;
        if(line.empty()) 
            continue;
        
        string tempArr[4] = {"", "", "", ""};
        int idx = 0;
        
        for(char ch : line) {
            if(ch == ',')
                idx++;
            else
                tempArr[idx] += ch;
        }
        
        userNames[userCount] = tempArr[0];
        userPasswords[userCount] = tempArr[1];
        userRoles[userCount] = tempArr[2];
        userHistory[userCount] = tempArr[3];
        userCount++;
    }
    
    // GARMENT DATA
    while(getline(file, line)) {
        if(line.empty()) 
            continue;
        
        string tempArr[7] = {"", "", "", "", "", "", ""};
        int idx = 0;
        
        for(char ch : line) {
            if(ch == ',')
                idx++;
            else
                tempArr[idx] += ch;
        }
        
        types[garment_count] = tempArr[0];
        names[garment_count] = tempArr[1];
        units[garment_count] = stoi(tempArr[2]);
        sold[garment_count] = stoi(tempArr[3]);
        whole_sale[garment_count] = stod(tempArr[4]);
        shipping[garment_count] = stod(tempArr[5]);
        retail_price[garment_count] = stod(tempArr[6]);
        garment_count++;
    }
    
    file.close();
}

int main(){
    int userCapacity=100;
    int MAX_GARMENTS=100;
    string userNames[userCapacity];
    string userPasswords[userCapacity];
    string userRoles[userCapacity];
    string userHistory[userCapacity];
    int userCount=2;
    int garment_count=5;
    string types[MAX_GARMENTS];  
    string names[MAX_GARMENTS];
    int units[MAX_GARMENTS];
    int sold[MAX_GARMENTS];
    int stock_left[MAX_GARMENTS];
    string cart[50];
    string garment_name = "";
    // string file_name="users.txt";
    int cart_idx=0;
    int quantity = 0;
    double total_price = 0.0;
    string day = "";
    float amount = 0.0;
    float change = 0.0;
    float discount = 0.0;
    int free_items = 0;
    double whole_sale[MAX_GARMENTS];      
    double shipping[MAX_GARMENTS];       
    double retail_price[MAX_GARMENTS];
    
    readingFile(userNames, userPasswords, userRoles, userHistory, userCount,types, names, units, sold, whole_sale, shipping, retail_price, garment_count);

    
    
    int option=0;
    while(option!=3){
        print_header();
        option=main_menu();
        clearScreen();
        if(option==1){
            print_header();
            printMenuHeader("login Menu","Sign In");
            string uN, uP,uR;
            cout<<"Enter Username: ";
            cin>>uN;
            cout<<"Enter Password: ";
            cin>>uP;
            int idx;
            string userRole=signIn(uN,uP, userNames, userPasswords, userRoles, userCount, idx);
            if(userRole!="undefined"){
                if (userRole=="admin")
                {
                    admin_interface(garment_count, MAX_GARMENTS, names, units, whole_sale, shipping, retail_price, sold, stock_left, userNames, userPasswords, userRoles, garment_name, quantity, total_price, day, amount, change, discount, free_items, userCount, userHistory);
                    saveToFile(userNames, userPasswords, userRoles, userHistory, userCount,types, names, units, sold, whole_sale, shipping, retail_price, garment_count);
                }
                else if (userRole=="user")
                {
                    user_interface(garment_count, day, names, stock_left, retail_price, units, sold, types, amount, change, discount, free_items, garment_name, quantity, total_price, cart_idx, cart, idx, userHistory);
                    saveToFile(userNames, userPasswords, userRoles, userHistory, userCount,types, names, units, sold, whole_sale, shipping, retail_price, garment_count);
                }
                else
                  cout<<"wrong input.Try writing all lowercase"<<endl;
            }
            else 
            cout<<"User not found"<<endl;
        }
        if(option==2){
            print_header();
            printMenuHeader("login Menu","Sign Up");
            string uN,uP,uR;
            cout<<"Enter Username: ";
            cin>>uN;
            cout<<"Enter Password: ";
            cin>>uP;
            uR = "user";
            SignUp(uN,uP, uR, userNames, userPasswords, userRoles, userCount, userCapacity);
            saveToFile(userNames, userPasswords, userRoles, userHistory, userCount,types, names, units, sold, whole_sale, shipping, retail_price, garment_count);
        }
        if(option!=1 && option!=2 && option!=3)
         cout<<"Invalid option"<<endl;
    }
    if(option==3)
      clearScreen();
    
    return 0;
} 

void setColor(int color) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,color);
}

string signIn(string &uN,string &uP,string userNames[], string userPasswords[], string userRoles[], int &userCount, int &idx){
    for(int i=0;i<userCount;i++)
    {
        if(userNames[i]==uN && userPasswords[i]==uP ){
            idx = i;
            return userRoles[i];
        }
        else if(userNames[i]==uN && userPasswords[i]!=uP){
            cout<<"Incorrect password!"<<endl;
            return "undefined";
        }
    }
    return "undefined";
}

void SignUp(string &uN, string &uP, string &uR,string userNames[], string userPasswords[], string userRoles[], int &userCount,int &userCapacity)
{
    if (userCount < userCapacity)
    {
        for (int idx = 0; idx < userCount; idx++)
        {
            if (userNames[idx] == uN)
            {
                cout <<"Username already exists"<<endl;
                return;
            }
        }
        userNames[userCount] = uN;
        userPasswords[userCount] = uP;
        userRoles[userCount] = uR;
        userCount++;
        cout<<"Registration successful"<<endl;
    }
    else
    {
        cout<<"User capacity reached. Cannot register more users."<<endl;
    }
}

int main_menu(){
    setColor(11);
    int option;
    printMenuHeader("main menu","select option");
    cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<< "|         MAIN MENU          |"<<endl;
    cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<< "| 1. Sign In                 |" << endl;
    cout<< "| 2. Sign Up                 |" << endl;
    cout<< "| 3. Exit                    |" << endl;
    cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<< "Enter option: ";
    cin>> option;
    setColor(7);
    return option;
}

void clearScreen()
{
    cout << "Press Any Key to Continue..";
    getch();
    system("cls"); 
}

void admin_interface(int &garment_count, int MAX_GARMENTS, string names[], int units[], double whole_sale[], double shipping[], double retail_price[], int sold[], int stock_left[], string userNames[], string userPasswords[], string userRoles[], string &garment_name, int &quantity, double &total_price, string &day, float &amount, float &change, float &discount, int &free_items, int &userCount, string userHistory[])
{  
    clearScreen();
    int choice = 0;
    while (choice != 6) {
        print_header();
        choice = admin_menu();
        clearScreen();
        if (choice == 1) {
            input_garment(garment_count, MAX_GARMENTS, names, units, whole_sale, shipping, retail_price, sold);
        } else if (choice == 2) {
            view_profit(garment_count, names, units, whole_sale, shipping, retail_price, sold, stock_left);
        } else if (choice == 3) {
            updateStock(garment_count, names, units, sold, stock_left);
        } else if (choice == 4) {
            delete_garment(garment_count, names, units, whole_sale, shipping, retail_price, sold);
        }else if(choice==5){
            view_customers(userNames, userPasswords, userRoles, userHistory, userCount);
        }else if (choice == 6) {
            break;
        } else {
            cout << "Invalid choice" << endl;
        }
        clearScreen();
    }
}

void print_header ()
{
    setColor(11);
    cout << "  ___  __    _____  ____  _   _  ____  _  _  ___    ____  _  _  _  _  ____  _  _  ____  _____  ____  _  _   ___  _  _  ___  ____  ____  __  __ " << endl;
    cout << " / __)(  )  (  _  )(_  _)( )_( )(_  _)( \\( )/ __)  (_  _)( \\( )( \\/ )( ___)( \\( )(_  _)(  _  )(  _ \\( \\/ ) / __)( \\/ )/ __)(_  _)( ___)(  \\/  )" << endl;
    cout << "( (__  )(__  )(_)(    )(   ) _ (  _)(_  )  (( (_-   _)(_  )  (  \\  /  )__)  )  (   )(   )(_)(  )   / \\  /  \\__ \\ \\  / \\__ \\  )(   )__)  )    ( " << endl;
    cout << " \\___)(____)(_____) (__) (_) (_)(____)(_)\\_)\\___/  (____)(_)\\_)  \\/  (____)(_)\\_) (__) (_____)(_)\\_) (__)  (___/ (__) (___/ (__) (____)(_/\\/\\_)" << endl;
    setColor(7);
}

void printMenuHeader(string mainMenu,string subMenu){
    string msg=mainMenu +" > "+ subMenu;
    cout<<msg<<endl;
    cout<<"------------------------------"<<endl;
}

int admin_menu()
{  
    setColor(6);
    printMenuHeader("login menu","admin menu");
    cout<<"~---------------------------------------------~"<<endl;
    cout<<"|            ADMIN MENU                       |"<<endl;
    cout<<"~---------------------------------------------~"<<endl;
    cout<<"| 1. Input new garment data (CREATE)          |"<<endl;
    cout<<"| 2. View Profit and Stock Report (RETRIEVE)  |"<< endl;
    cout<<"| 3. Update units sold for a garment (UPDATE) |" << endl;
    cout<<"| 4. Delete a garment record (DELETE)         |" << endl;
    cout<<"| 5. View customer history                    |" <<endl;
    cout<<"| 6. Exit to Main Menu                        |" << endl;
    cout<<"~---------------------------------------------~"<<endl;
   
    int choice_local;
    cout<<"Enter your choice (1-6): "<<endl;
    cin>>choice_local;
    setColor(7);
    return choice_local;
}

void input_garment(int &garment_count,int &MAX_GARMENTS, string names[], int units[], double whole_sale[], double shipping[], double retail_price[], int sold[])
{  setColor(12);
    if (garment_count >= MAX_GARMENTS) {
        cout << "\nERROR: Inventory is full. Cannot add more garments (Max " << MAX_GARMENTS << ").\n";
        return;
    }
    
    int i = garment_count; 

    cout << "\n--- 1. INPUT GARMENT DATA ---\n";
    
    cout << "Enter garment name (no spaces): ";
    cin >> names[i]; 

    cout << "Enter the units recieved from supplier: ";
    cin >> units[i];
    
    cout << "Wholesale rate per unit: ";
    cin >> whole_sale[i];
    
    cout << "Shipping cost per unit: ";
    cin >> shipping[i];
    
    cout << "Retail price per unit: ";
    cin >> retail_price[i];
    
    cout << "Units sold (initial value): ";
    cin >> sold[i];
    
    if(sold[i]>units[i]){
        cout<<"\nERROR: Units sold cannot exceed units received. Garment not added.\n";
        return;
    }
    if(whole_sale[i]<0 || shipping[i]<0 || retail_price[i]<0 || units[i]<0 || sold[i]<0){
        cout<<"\nERROR: Negative values are not allowed. Garment not added.\n";
        return;
    }
    if(retail_price[i] < (whole_sale[i] + shipping[i])){
        cout<<"\nWARNING: Retail price is less than total cost (wholesale + shipping). This may lead to losses.\n";
    }

    garment_count++; 
    cout << "\nSUCCESS: Garment '" << names[i] << "' added to inventory.\n";
    setColor(7);
}

void view_profit(int &garment_count, string names[], int units[], double whole_sale[], double shipping[], double retail_price[], int sold[], int stock_left[])
{    setColor(13);
    if (garment_count == 0) {
        cout << "\nREPORT EMPTY: No garment data has been entered yet.\n";
        return;
    }
    const int NAME_W = 24;
    const int NUM_W  = 12;

    cout << "\n" << string(NAME_W + NUM_W * 6, '=') << endl;
    cout << left << setw(NAME_W) << "Name"
         << right << setw(NUM_W) << "StockLeft"
         << setw(NUM_W) << "StockNeeded"
         << setw(NUM_W) << "UnitCost"
         << setw(NUM_W) << "UnitProfit"
         << setw(NUM_W) << "TotalProfit"
         << setw(NUM_W) << "Loss" << endl;
    cout << string(NAME_W + NUM_W * 6, '=') << endl;

    for (int i = 0; i < garment_count; i++)
    {
        double cost_per_unit = whole_sale[i] + shipping[i];
        double profit_per_unit = retail_price[i] - cost_per_unit;
        stock_left[i] = units[i] - sold[i];

        int stock_needed = 0;
        if (sold[i] > units[i]) stock_needed = sold[i] - units[i];

        double total_profit = profit_per_unit * sold[i];
        if (total_profit < 0) total_profit = 0;

        double loss = ((whole_sale[i] + shipping[i]) - retail_price[i]) * sold[i];
        if (loss < 0) loss = 0;

        cout << left << setw(NAME_W) << names[i]
             << right << setw(NUM_W) << stock_left[i]
             << setw(NUM_W) << stock_needed
             << setw(NUM_W) << fixed << setprecision(2) << cost_per_unit
             << setw(NUM_W) << fixed << setprecision(2) << profit_per_unit
             << setw(NUM_W) << fixed << setprecision(2) << total_profit
             << setw(NUM_W) << fixed << setprecision(2) << loss
             << endl;
    }

    cout << string(NAME_W + NUM_W * 6, '=') << endl;
    setColor(7);
}

void updateStock(int &garment_count, string names[], int units[], int sold[], int stock_left[])
{    setColor(10);
    if (garment_count == 0) {
        cout << "\nINVENTORY EMPTY: Cannot update stock.\n";
        return;
    }
    
    string update_name;
    int additional_sold;
    
    cout << "\n--- 3. UPDATE UNITS SOLD ---\n";
    cout << "Enter Garment Name to update stock for (no spaces): ";
    cin >> update_name;

    int found_index = -1;
    for (int i = 0; i < garment_count; i++)
    {
        if (names[i] == update_name)
        {
            found_index = i;
            break;
        }
    }

    if (found_index != -1)
    {
        cout << "Current units sold for " << update_name << " is: " << sold[found_index] << endl;
        cout << "Enter ADDITIONAL units sold since last entry: ";
        cin >> additional_sold;
        
        if (sold[found_index] + additional_sold > units[found_index]) {
            cout << "WARNING: Total units sold exceeds total units received. Update cancelled.\n";
        } else {
            sold[found_index] += additional_sold; 
            cout << "\nSUCCESS: Total units sold updated to " << sold[found_index] << " for " << update_name << ".\n";
        }
    }
    else
    {
        cout << "\nERROR: Garment '" << update_name << "' not found.\n";
    }
    setColor(7);
}
void updateStockArray(int &garment_count, int stock_left[], int units[], int sold[])
{
    for (int i = 0; i < garment_count; i++)
    {
        stock_left[i] = units[i] - sold[i];
    }
}

void delete_garment(int &garment_count, string names[], int units[], double whole_sale[], double shipping[], double retail_price[], int sold[])
{    setColor(11);
    if (garment_count == 0) {
        cout << "\nINVENTORY EMPTY: Nothing to delete.\n";
        return;
    }

    string delete_name;
    cout << "\n--- 4. DELETE GARMENT RECORD ---\n";
    cout << "Enter Garment Name to delete (no spaces): ";
    cin >> delete_name;

    int delete_index = -1;
    for (int i = 0; i < garment_count; i++)
    {
        if (names[i] == delete_name)
        {
            delete_index = i;
            break;
        }
    }

    if (delete_index != -1)
    {
        for (int i = delete_index; i < garment_count - 1; ++i) 
        {
            names[i] = names[i+1];
            units[i] = units[i+1];
            whole_sale[i] = whole_sale[i+1];
            shipping[i] = shipping[i+1];
            retail_price[i] = retail_price[i+1];
            sold[i] = sold[i+1];
        }
        
        garment_count--; 

        cout << "\nSUCCESS: Garment record for '" << delete_name << "' has been deleted.\n";
    }
    else
    {
        cout << "\nERROR: Garment '" << delete_name << "' not found.\n";
    }
    setColor(7);
}

void view_customers(string userNames[], string userPasswords[], string userRoles[], string userHistory[], int userCount){
    setColor(4);
    cout << "--- CUSTOMER PURCHASE HISTORY (ADMIN VIEW) ---" << endl;

    const int NAME_W = 20;
    const int PASS_W = 20;
    const int ROLE_W = 10;
    const int HIST_W = 40;

    cout << string(NAME_W + PASS_W + ROLE_W + HIST_W, '=') << endl;
    cout << left
         << setw(NAME_W) << "USERNAME"
         << setw(PASS_W) << "PASSWORD"
         << setw(ROLE_W) << "ROLE"
         << setw(HIST_W) << "PURCHASE HISTORY"
         << endl;
    cout << string(NAME_W + PASS_W + ROLE_W + HIST_W, '=') << endl;

    bool found = false;

    for(int i = 0; i < userCount; i++){
        if(userRoles[i] == "user"){
            cout << left
                 << setw(NAME_W) << userNames[i]
                 << setw(PASS_W) << userPasswords[i]
                 << setw(ROLE_W) << userRoles[i];

            if(userHistory[i] == "")
                cout << setw(HIST_W) << "No purchases";
            else
                cout << setw(HIST_W) << userHistory[i];

            cout << endl;
            found = true;
        }
    }

    if(!found){
        cout << "No customers found." << endl;
    }

    cout << string(NAME_W + PASS_W + ROLE_W + HIST_W, '=') << endl;
    setColor(7);
}

int user_menu()
{   
    setColor(10);
    printMenuHeader("login menu","user menu");
    cout<<"~--------------------------------------~"<<endl;
    cout<<"|             USER MENU                |"<<endl;
    cout<<"~--------------------------------------~"<<endl;
    cout<<"| 1. View available garments           |"<< endl;
    cout<<"| 2. View catogories                   |"<<endl;
    cout<<"| 3. Add to cart                       |"<<endl;
    cout<<"| 4. Make a Purchase                   |"<< endl;
    cout<<"| 5. View Purchase History             |"<< endl;
    cout<<"| 6. Update amount                     |" << endl;
    cout<<"| 7. Generate Receipt                  |"<<endl;
    cout<<"| 8. Exit to main menu                 |"<<endl;
    cout<<"~--------------------------------------~"<<endl;
    int choice_local;
    cout<<"Enter your choice (1-8): "<<endl;
    cin>>choice_local;
    setColor(7);
    return choice_local;
}

void user_interface(int &garment_count,string &day,string names[], int stock_left[], double retail_price[], int units[], int sold[], string types[], float &amount, float &change, float &discount, int &free_items, string &garment_name, int &quantity, double &total_price, int &cart_idx, string cart[], int idx, string userHistory[])
{   
    clearScreen();
    print_header();

    int choice = 0;
    while (choice != 8) {
        clearScreen();
        print_header();
        sort_garments_by_units(garment_count, names, stock_left, retail_price, units, sold, types);

        choice = user_menu();

        if (choice == 1) {
            view_garments(garment_count, names, stock_left, retail_price);
        } else if (choice == 2) {
            view_catogories(garment_count, types, names, retail_price, stock_left);
        }else if(choice ==3){
            add_to_cart(garment_name, quantity, total_price, garment_count, names, units, retail_price, sold, stock_left, cart_idx, cart);
        }
        else if (choice == 4) {
            make_purchase(garment_name, day, quantity, total_price, garment_count, names, units, retail_price, sold, stock_left, cart_idx, cart, idx, userHistory, types, free_items);
        } else if (choice == 5) {
            view_purchase_history(userHistory, idx, quantity, total_price);
        } else if (choice == 6) {
            update_amount(total_price, amount, change);
        } else if (choice == 7) {
            receipt_generation(garment_name, quantity, total_price, amount, change, discount, day, free_items);
        } else if (choice == 8) {
            break;
        } else {
            cout << "Invalid choice" << endl;
        }
        clearScreen();
    }
}

void view_garments(int garment_count, string names[], int stock_left[], double retail_price[]){
    setColor(6);
    const int NAME_W = 30;
    const int NUM_W  = 10;

    cout << string(NAME_W + NUM_W * 2, '=') << endl;
    cout << left << setw(NAME_W) << "NAME" << right << setw(NUM_W) << "QUANTITY" << setw(NUM_W) << "PRICE" << endl;
    cout << string(NAME_W + NUM_W * 2, '=') << endl;

    for(int i=0;i<garment_count;i++){
        cout << left << setw(NAME_W) << names[i]
             << right << setw(NUM_W) << stock_left[i]
             << setw(NUM_W) << fixed << setprecision(2) << retail_price[i]
             << endl;
    }
    cout << string(NAME_W + NUM_W * 2, '=') << endl;
    setColor(7);
}

void view_catogories(int &garment_count,string types[],string names[],double retail_price[],int stock_left[]){
    string category;
    setColor(13);
    cout<<"--- GARMENT CATEGORIES ---"<<endl;
    for(int i=0;i<garment_count;i++){
        cout<<types[i]<<" : "<<names[i]<<endl;
    }
    cout<<"Enter your required category:"<<endl;
    cin>>category;
    cout<<"..................................................."<<endl;
    const int NAME_W = 30;
    const int NUM_W  = 10;
    cout << left << setw(NAME_W) << "NAME" << right << setw(NUM_W) << "QUANTITY" << setw(NUM_W) << "PRICE" <<"| "<<endl;
    cout<<"..................................................."<<endl;
    
    bool found = false;
    for(int i=0;i<garment_count;i++){
        if(category==types[i]){
            cout << left << setw(NAME_W) << names[i] << right << setw(NUM_W) << stock_left[i] << setw(NUM_W) << fixed << setprecision(2) << retail_price[i] <<"|" << endl;
            found = true;
        }
    }
    
    if(!found){
        cout << "No items found in this category." << endl;
    }
    
    cout<<"..................................................."<<endl;
    setColor(7);
}

void add_to_cart(string &garment_name, int &quantity, double &total_price, int &garment_count, string names[], int units[], double retail_price[], int sold[], int stock_left[],int &cart_idx,string cart[]){
    setColor(1);
    updateStockArray(garment_count, stock_left, units, sold);
    char continueAdding = 'y';
    
    while(continueAdding == 'y' || continueAdding == 'Y') {
        cout<<"Enter garment name to add to cart: ";
        cin.ignore();
        getline(cin, garment_name);
        cout<<"Enter quantity: ";
        cin>>quantity;

        bool found = false;
        int idx = -1;

        for(int i=0; i<garment_count; i++) {
            if(garment_name == names[i]) {
                found = true;
                idx = i;
                break;
            }
        }

        if(found && quantity > 0 && quantity <= stock_left[idx]) {
            for(int j = 0; j < quantity; j++){
                if(cart_idx < 50){
                    cart[cart_idx] = garment_name;
                    cart_idx++;
                }
            }
            cout << "Added " << quantity << " " << garment_name << "(s) to cart!" << endl;
        } else if(!found) {
            cout << "Item not found!" << endl;
        } else {
            cout << "Invalid quantity or insufficient stock!" << endl;
        }

        cout << "Add more items or delete items? (y/n/d): ";
        cin >> continueAdding;
        if(continueAdding == 'd' || continueAdding == 'D'){
            if(cart_idx == 0){
                cout<<"Cart is empty! Nothing to delete."<<endl;
            } else {
                string delete_item;
                cout<<"Enter the name of the item to delete from cart: ";
                cin.ignore();
                getline(cin, delete_item);
                
                int delete_count = 0;
                for(int k = 0; k < cart_idx; ) {
                    if(cart[k] == delete_item) {
                        for(int m = k; m < cart_idx - 1; m++) {
                            cart[m] = cart[m + 1];
                        }
                        cart_idx--;
                        delete_count++;
                    } else {
                        k++;
                    }
                }
                
                if(delete_count > 0) {
                    cout << "Removed " << delete_count << " " << delete_item << "(s) from cart." << endl;
                } else {
                    cout << "Item not found in cart!" << endl;
                }
            }
            cout << "Continue adding items? (y/n): ";
            cin >> continueAdding;
        }
        
    }
    
    cout << "Total items in cart: " << cart_idx << endl;
    setColor(7);
}
void make_purchase(string &garment_name,string &day, int &quantity,double &total_price, int &garment_count, string names[], int units[], double retail_price[], int sold[], int stock_left[],int &cart_idx,string cart[], int idx, string userHistory[], string types[],int &free_items){
    setColor(12);
    if(cart_idx == 0){
        cout<<"Cart is empty! Please add items first."<<endl;
        return;
    }

    total_price = 0.0;
    
    // Calculate total from cart
    for(int a=0; a<cart_idx; a++) {
        for(int i=0; i<garment_count; i++){
            if(names[i]==cart[a]) {
                total_price += retail_price[i];
                break;
            }
        }
    }

    cout<<"Enter the day of purchase: ";
    cin>>day;
    
    // Apply day discounts
    if(day=="Sunday" || day=="sunday"){
        total_price *= 0.90;
        cout<<"A 10% discount has been applied for Sunday purchases."<<endl;
    }
    else if(day=="Saturday" || day=="saturday"){
        total_price *= 0.95;
        cout<<"A 5% discount has been applied for Saturday purchases."<<endl;
    }
    //  buy 2 get 1 free
    sort_garments_by_units(garment_count, names, stock_left, retail_price, units, sold, types);
    if(cart_idx>=3){
         free_items = cart_idx / 3;
        double cheapest_price = retail_price[0];
        total_price -= cheapest_price * free_items;
        cout<<"Buy 2 Get 1 Free applied! You get "<<free_items<<" item(s) free."<<endl;
    }

    // Update stock for all cart items
    for(int a=0; a<cart_idx; a++) {
        for(int i=0; i<garment_count; i++){
            if(names[i]==cart[a]) {
                sold[i]++;
                stock_left[i] = units[i] - sold[i];
                break;
            }
        }
    }

    quantity = cart_idx;
    garment_name = "Multiple Items";
    
    cout<<"Purchase successful! Total items: "<<cart_idx<<endl;
    cout<<"Total price: $"<<fixed<<setprecision(2)<<total_price<<endl;


    for(int a=0; a<cart_idx; a++) {
        userHistory[idx] += cart[a];
        if(a != cart_idx - 1){
             userHistory[idx] += ",";
        }
         else
         userHistory[idx] += ".";
    } // shirt,pants.
    // Clear cart
    cart_idx = 0;
    setColor(7);
}
void view_purchase_history(string userHistory[], int idx, int quantity, double total_price)
{
    setColor(14);
    cout << "--- PURCHASE HISTORY ---" << endl;

    if (userHistory[idx] == "")
    {
        cout << "No purchase history available" << endl;
        setColor(7);
        return;
    }

    const int NAME_W = 30;
    const int NUM_W = 12;

    cout << left << setw(NAME_W) << "Garment Name"
         << right << setw(NUM_W) << "Quantity"
         << setw(NUM_W) << "Total Price" << endl;

    cout << string(NAME_W + NUM_W * 2, '-') << endl;

    string item = "";

    // Print each garment separately
    for (char ch : userHistory[idx])
    {
        if (ch == ',' || ch == '.')
        {
            cout << left << setw(NAME_W) << item
                 << right << setw(NUM_W) << 1
                 << setw(NUM_W) << "-" << endl;
            item = "";
        }
        else
        {
            item += ch;
        }
    }

    cout << string(NAME_W + NUM_W * 2, '-') << endl;
    cout << left << setw(NAME_W) << "TOTAL"
         << right << setw(NUM_W) << quantity
         << setw(NUM_W) << fixed << setprecision(2) << total_price << endl;

    setColor(7);
}

float update_amount(double &total_price, float &amount, float &change){
    cout<<"Enter the amount you have: ";
    cin>>amount;
    
    if(amount<total_price){
        cout<<"Insufficient amount. Please pay the full amount of $"<<total_price<<endl;
        change = 0.0;
    }
    else if(amount==total_price){
        cout<<"Payment successful! No change due."<<endl;
        change = 0.0;
    }
    else if (amount<0){
        cout<<"Invalid amount entered."<<endl;
        change = 0.0;
    }
    else if (amount==0){
        cout<<"No purchase made."<<endl;
        change = 0.0;
    }
    else{
        change = amount - total_price;
        cout<<"Payment successful! Your change is $"<<change<<endl;
    }
    
    return change;
}
void receipt_generation(string & garment_name, int &quantity, double &total_price, float &amount, float &change, float &discount, string &day, int &free_items)
    {
        setColor(1);
        cout << "\nGenerating receipt...\n";
        if(total_price == 0.0){
            cout << "No purchase made. Receipt cannot be generated.\n";
            return;
        }
        if(amount==0 && total_price>0){
            cout<<"Go to update amount and pay your bill"<<endl;
            return;

        }

        const int LABEL_W = 22;
        const int VAL_W = 18;
        const int TOTAL_W = LABEL_W + VAL_W + 4;

        cout << string(TOTAL_W, '*') << endl;
        cout << "*" << setw(TOTAL_W - 15) << right << "PURCHASE RECEIPT";
        cout << setw(14) << "|" << endl;
        cout << string(TOTAL_W, '*') << endl;

        cout << left << setw(LABEL_W) << "Garment Name:" << right << setw(VAL_W) << garment_name;
        cout << setw(4) << "|" << endl;
        cout << left << setw(LABEL_W) << "Quantity:" << right << setw(VAL_W) << quantity;
        cout << setw(4) << "|" << endl;
        cout << left << setw(LABEL_W) << "Total Price:" << right << setw(VAL_W) << fixed << setprecision(2) << total_price;
        cout << setw(4) << "|" << endl;
        cout << left << setw(LABEL_W) << "Amount Paid:" << right << setw(VAL_W) << fixed << setprecision(2) << amount;
        cout << setw(4) << "|" << endl;
        cout << left << setw(LABEL_W) << "Change Given:" << right << setw(VAL_W) << fixed << setprecision(2) << change;
        cout << setw(4) << "|" << endl;
        cout << left << setw(LABEL_W) << "Discount (%):" << right << setw(VAL_W) << fixed << setprecision(2) << discount;
        cout << setw(4) << "|" << endl;
        cout << left << setw(LABEL_W) << "Day of Purchase:" << right << setw(VAL_W) << day;
        cout << setw(4) << "|" << endl;
        cout << left << setw(LABEL_W) << "Offer (free):" << right << setw(VAL_W) << free_items;
        cout << setw(4) << "|" << endl;
        cout << string(TOTAL_W, '*') << endl;
        cout << "*" << setw(TOTAL_W - 2) << left << " Thank you for shopping with us!" << "*" << endl;
        cout << string(TOTAL_W, '*') << endl;

        setColor(7);
    }
void sort_garments_by_units(int &garment_count, string names[], int stock_left[], double retail_price[], int units[], int sold[], string types[])
   {

        for (int i = 0; i < garment_count - 1; ++i)
        {
            int min_idx = i;
            for (int j = i + 1; j < garment_count; ++j)
            {
                if (units[j] < units[min_idx])
                    min_idx = j;
            }
            if (min_idx != i)
            {   
                swap(units[i], units[min_idx]);
                swap(names[i], names[min_idx]);
                swap(stock_left[i], stock_left[min_idx]);
                swap(retail_price[i], retail_price[min_idx]);
                swap(sold[i], sold[min_idx]);
                swap(types[i], types[min_idx]);
            }
        }
    }
 
    // --- File Handling Functions ---

    // int saveData(int &userCount,string &file_name,string userNames[],string userPasswords[],string userRoles[],int &userCapacity){
    //     ofstream file(file_name);
    //     if(file.fail()){
    //         cout<<"Error opening file for writing."<<endl;
    //         return 1;
    //     }
    //     file<<userCount<<endl;
    //     for(int i=0;i<userCount;i++){
    //         file<<userNames[i]<<","<<userPasswords[i]<<","<<userRoles[i]<<endl;
    //     }
    //     file.close();
    //     cout<<"Data saved successfully to "<<file_name<<endl;
    //     return 0;
    // }
    // int loadData(int &userCount,string &file_name,string userNames[],string userPasswords[],string userRoles[],int &userCapacity){
    //     ifstream file(file_name);
    //    if(file.fail()){
    //     cout<<"Error opening file for reading."<<endl;
    //     return 1;//error
    //    }
    //    file>>userCount;//read user count(no of users)
    //    for(int i=0;i<userCount;i++){
    //     string line;
    //     file>>line;
    //     // reads a line (CSV) 
    //     size_t pos1=line.find(",");
    //     size_t pos2=line.find(",",pos1+1);//finds coma positions to split line into three parts
    //     userNames[i]=line.substr(0,pos1);
    //     userPasswords[i]=line.substr(pos1+1,pos2-pos1-1);
    //     userRoles[i]=line.substr(pos2+1);
    //    // names[i]=line.substr(0,pos1);
    //    //stock_left[i]=line.substr(pos1+1,pos2-pos1-1);
    //    //retail_price[i]=line.substr(pos2+1);


    //    }
    //    return 0;//success
    //    file.close();
    // }
