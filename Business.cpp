#include <iostream>
#include<conio.h>
#include<windows.h>
#include <string>
#include <iomanip>
using namespace std;
int gotoxy(int x, int y);
string signIn(string &uN,string &uP,string userNames[], string userPasswords[], string userRoles[], int &userCount);
void SignUp(string &uN,string &uP,string &uR,string userNames[], string userPasswords[], string userRoles[], int &userCount,int &userCapacity);
void print_header();
void printMenuHeader(string mainMenu,string subMenu);
int main_menu();
int admin_menu();
int user_menu();
void user_interface(int &garment_count,string &day, string names[], int stock_left[], double retail_price[], int units[], int sold[], string types[], float &amount, float &change, float &discount, int &free_items);
void clearScreen();
void admin_interface(int &garment_count, int MAX_GARMENTS, string names[], int units[], double whole_sale[], double shipping[], double retail_price[], int sold[], int stock_left[]);
void input_garment(int &garment_count, int &MAX_GARMENTS, string names[], int units[], double whole_sale[], double shipping[], double retail_price[], int sold[]);   
void view_profit(int &garment_count, string names[], int units[], double whole_sale[], double shipping[], double retail_price[], int sold[], int stock_left[]);     
void update_stock(int &garment_count, string names[], int units[], int sold[], int stock_left[]);    
void delete_garment(int &garment_count, string names[], int units[], double whole_sale[], double shipping[], double retail_price[], int sold[]); 
void view_garments(int garment_count, string names[], int stock_left[], double retail_price[]);
void setColor(int color); 
void make_purchase(string &garment_name,string &day, int &quantity,double &total_price,int &garment_count, string names[], int units[], double retail_price[], int sold[], int stock_left[]);
void view_purchase_history(string &garment_name, int &quantity,double &total_price);
void view_catogories(int &garment_count,string types[],string names[],double retail_price[],int stock_left[]);
float update_amount(double &total_price);
void receipt_generation(string &garment_name, int &quantity, double &total_price, float &amount, float &change, float &discount, string &day, int &free_items);
void updateStock(int &garment_count, int stock_left[], int units[], int sold[]) {
    for (int i = 0; i < garment_count; i++) {
        stock_left[i] = units[i] - sold[i];
    }
}
// Sort prototype: sorts all parallel arrays ascending by `units`
void sort_garments_by_units(int &garment_count, string names[], int stock_left[], double retail_price[], int units[], int sold[], string types[]);
main(){
    int userCapacity=100;
    int MAX_GARMENTS=100;
    string userNames[userCapacity]={"ali","noor"};
string userPasswords[userCapacity]={"abc12","nf67"};
string userRoles[userCapacity]={"admin","user"};
int userCount=2;
int garment_count=5;
string types[MAX_GARMENTS]={"shirt","pants","jacket","shoes", "shirt"};  
string names[MAX_GARMENTS]={"t-shirt","cargo pants", "leather jacket","sneakers", "Polo-Shirt" };

int units[MAX_GARMENTS]={50,60,30,20,40};
int sold[MAX_GARMENTS]={20,30,10,5,15};
int stock_left[MAX_GARMENTS];
string garment_name;
int quantity;   
double total_price;
string day;
float amount = 0.0;
float change = 0.0;
float discount = 0.0;
int free_items = 0;
double whole_sale[MAX_GARMENTS]={15.0,20.0,50.0,80.0,25.0};      
double shipping[MAX_GARMENTS]={2.0,3.0,5.0,8.0,5.0};       
double retail_price[MAX_GARMENTS]={30.0,45.0,100.0,150.0,25.0};    



        updateStock(garment_count, stock_left, units, sold);
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

            string userRole=signIn(uN,uP, userNames, userPasswords, userRoles, userCount);
            if(userRole!="undefined"){
                if (userRole=="admin")
                {
                    admin_interface(garment_count, MAX_GARMENTS, names, units, whole_sale, shipping, retail_price, sold, stock_left);
                }
                else if (userRole=="user")
                {
                    string day;
                    user_interface(garment_count, day, names, stock_left, retail_price, units, sold, types, amount, change, discount, free_items);
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
            // cout<<"Enter Role (Admin/User): ";
            // cin>>uR;
            uR = "user";
            SignUp(uN,uP, uR, userNames, userPasswords, userRoles, userCount, userCapacity);

        }
        if(option!=1 && option!=2 && option!=3)
         cout<<"Invalid option"<<endl;
        
       
      }
      if(option==3)
      clearScreen();
} 
void setColor(int color) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,color);

}
string signIn(string &uN,string &uP,string userNames[], string userPasswords[], string userRoles[], int &userCount){
    //check if user exists
    for(int i=0;i<userCount;i++)
    {
        if(userNames[i]==uN && userPasswords[i]==uP){
            return userRoles[i];
        }
    }
    return "undefined"; // user does not exists
}
void SignUp(string &uN, string &uP, string &uR,string userNames[], string userPasswords[], string userRoles[], int &userCount,int &userCapacity)
{
    if (userCount < userCapacity)
    {
        for (int idx = 0; idx < userCount; idx++)
        {
            if (userNames[idx] == uN && userPasswords[idx] == uP)
            {
                cout<<"Username already exists"<<endl;
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
    return option;
  setColor(7);

}
void clearScreen()
{
    cout << "Press Any Key to Continue..";
    getch();
    system("cls"); 
}


 
void admin_interface(int &garment_count, int MAX_GARMENTS, string names[], int units[], double whole_sale[], double shipping[], double retail_price[], int sold[], int stock_left[])
{  clearScreen();
    print_header();
     
    int choice = 0;
    while (choice != 5) {
        print_header();
        choice = admin_menu();
        if (choice == 1) {
            input_garment(garment_count, MAX_GARMENTS, names, units, whole_sale, shipping, retail_price, sold);
        } else if (choice == 2) {
            view_profit(garment_count, names, units, whole_sale, shipping, retail_price, sold, stock_left);
        } else if (choice == 3) {
            update_stock(garment_count, names, units, sold, stock_left);
        } else if (choice == 4) {
            delete_garment(garment_count, names, units, whole_sale, shipping, retail_price, sold);
        } else if (choice == 5) {
            // exit to main menu
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
    cout << "  ___  __    _____  ____  _   _  ____  _  _  ___    ____  _  _  _  _  ____  _  _  ____  _____  ____  _  _   ___  _  _  ___  ____  ____  __  __ " << std::endl;
    cout << " / __)(  )  (  _  )(_  _)( )_( )(_  _)( \\( )/ __)  (_  _)( \\( )( \\/ )( ___)( \\( )(_  _)(  _  )(  _ \\( \\/ ) / __)( \\/ )/ __)(_  _)( ___)(  \\/  )" << std::endl;
    cout << "( (__  )(__  )(_)(    )(   ) _ (  _)(_  )  (( (_-   _)(_  )  (  \\  /  )__)  )  (   )(   )(_)(  )   / \\  /  \\__ \\ \\  / \\__ \\  )(   )__)  )    ( " << std::endl;
    cout << " \\___)(____)(_____) (__) (_) (_)(____)(_)\\_)\\___/  (____)(_)\\_)  \\/  (____)(_)\\_) (__) (_____)(_)\\_) (__)  (___/ (__) (___/ (__) (____)(_/\\/\\_)" << std::endl;
    setColor(7);
   
}

void printMenuHeader(string mainMenu,string subMenu){
    string msg=mainMenu +" > "+ subMenu;
    cout<<msg<<endl;
    cout<<"------------------------------"<<endl;
}
int admin_menu()
{  setColor(6);
    printMenuHeader("login menu","admin menu");
    cout<<"~---------------------------------------------~"<<endl;
    cout<<"|            ADMIN MENU                       |"<<endl;
    cout<<"~---------------------------------------------~"<<endl;
    cout<<"| 1. Input new garment data (CREATE)          |"<<endl;
    cout<<"| 2. View Profit and Stock Report (RETRIEVE)  |"<< endl;
    cout<<"| 3. Update units sold for a garment (UPDATE) |" << endl;
    cout<<"| 4. Delete a garment record (DELETE)         |" << endl;
    cout<<"| 5. Exit to Main Menu                        |" << endl;
    cout<<"~---------------------------------------------~"<<endl;
   
    int choice_local;
    cout<<"Enter your choice (1-4): "<<endl;
    cin>>choice_local;
    return choice_local;
    setColor(7);
}
void input_garment(int &garment_count,int &MAX_GARMENTS, string names[], int units[], double whole_sale[], double shipping[], double retail_price[], int sold[])
{
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
}

// 2. RETRIEVE (View Profit and Stock Report)
void view_profit(int &garment_count, string names[], int units[], double whole_sale[], double shipping[], double retail_price[], int sold[], int stock_left[])
{
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
}
// 3. UPDATE (Change Units Sold)
void update_stock(int &garment_count, string names[], int units[], int sold[], int stock_left[])
{
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
}

// 4. DELETE (Delete Garment by Name)
void delete_garment(int &garment_count, string names[], int units[], double whole_sale[], double shipping[], double retail_price[], int sold[])
{
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
        // Manually shift all items after the deleted item one position back
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
}
// Sort garments ascending by units; keeps parallel arrays in sync
void sort_garments_by_units(int &garment_count, string names[], int stock_left[], double retail_price[], int units[], int sold[], string types[])
{
    for (int i = 0; i < garment_count - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < garment_count; ++j) {
            if (units[j] < units[min_idx]) min_idx = j;
        }
        if (min_idx != i) {
            swap(units[i], units[min_idx]);
            swap(names[i], names[min_idx]);
            swap(stock_left[i], stock_left[min_idx]);
            swap(retail_price[i], retail_price[min_idx]);
            swap(sold[i], sold[min_idx]);
            swap(types[i], types[min_idx]);
        }
    }
}
int user_menu()
{   setColor(10);
      printMenuHeader("login menu","user menu");
    cout<<"~--------------------------------------~"<<endl;
    cout<<"|             USER MENU                |"<<endl;
    cout<<"~--------------------------------------~"<<endl;
    cout<<"| 1. View available garments           |"<< endl;
    cout<<"| 2. View catogories                   |"<<endl;
    cout<<"| 3. Make a Purchase                   |"<< endl;
    cout<<"| 4. View Purchase History             |"<< endl;
    cout<<"| 5. Update amount                     |" << endl;
    cout<<"| 6. Generate Receipt                  |"<<endl;
    cout<<"| 7. Exit to main menu                 |"<<endl;
    cout<<"~--------------------------------------~"<<endl;
    int choice_local;
    cout<<"Enter your choice (1-7): "<<endl;
    cin>>choice_local;
    return choice_local;
    setColor(7);
}
void user_interface(int &garment_count,string &day,string names[], int stock_left[], double retail_price[], int units[], int sold[], string types[], float &amount, float &change, float &discount, int &free_items)
{
    string garment_name;
    int quantity;
    double total_price;

    int choice = 0;
    while (choice != 7) {
        clearScreen();
        print_header();
        // keep garments sorted for the user view/purchase
        sort_garments_by_units(garment_count, names, stock_left, retail_price, units, sold, types);

        choice = user_menu();

        if (choice == 1) {
            view_garments(garment_count, names, stock_left, retail_price);
        } else if (choice == 2) {
            view_catogories(garment_count, types, names, retail_price, stock_left);
        } else if (choice == 3) {
            make_purchase(garment_name,day, quantity, total_price, garment_count, names, units, retail_price, sold, stock_left);
        } else if (choice == 4) {
            view_purchase_history(garment_name, quantity, total_price);
        } else if (choice == 5) {
            update_amount(total_price);
        } else if (choice == 6) {
            receipt_generation(garment_name, quantity, total_price, amount, change, discount, day, free_items);
        } else if (choice == 7) {
            // exit to main menu
            break;
        } else {
            cout << "Invalid choice" << endl;
        }

        clearScreen();
    }
}
void view_garments(int garment_count, string names[], int stock_left[], double retail_price[]){
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
    for(int i=0;i<garment_count;i++){
        if(category==types[i]){
            cout << left << setw(NAME_W) << names[i] << right << setw(NUM_W) << stock_left[i] << setw(NUM_W) << fixed << setprecision(2) << retail_price[i] <<"|" << endl;
        }
    }
    cout<<"..................................................."<<endl;
    setColor(7);
}
void make_purchase(string &garment_name,string &day, int &quantity,double &total_price,int &garment_count, string names[], int units[], double retail_price[], int sold[], int stock_left[]){

    cout<<"Enter garment name to purchase: ";
    getline(cin>>ws, garment_name);
    cout<<"Enter quantity (number you will PAY for): ";
    cin>>quantity;
   

    if(garment_count==0){
        cout<<"No garments available"<<endl;
        return;
    }
    if(quantity<=0){
        cout<<"Invalid quantity"<<endl;
        return;
    }

    // find the garment index
    int idx = -1;
    for(int i=0;i<garment_count;i++){
        if(names[i]==garment_name)
        { idx = i;//index of the garment inputted
           break; }
    }
    if(idx == -1){
        cout<<"No such item exists"<<endl;
        return;
    }

    // compute stock and promotion
    stock_left[idx] = units[idx] - sold[idx];
    if(stock_left[idx]<=0){
        cout<<"Out of stock"<<endl;
        return;
    }

    // determine the maximum units value among garments
    int max_units = units[0];
    for (int k = 1; k < garment_count; ++k) {
        if (units[k] > max_units) 
        max_units = units[k];
    }

    // Buy-2-get-1-free applies to any garment whose units equal max_units
    int free_items = 0;
    if (units[idx] == max_units) {
        free_items = quantity / 2; // e.g., paying for 6 gives 3 free
        cout<<"Buy 2 get 1 free offer applied! You get "<<free_items<<" free items."<<endl;
    }
    else{
        cout<<"Buy 2 get 1 free offer is not available for this product";
    }

    int total_items_needed = quantity + free_items; // items to remove from stock

    if(total_items_needed > stock_left[idx]){
        cout<<"Insufficient stock available for this promotion. Available="<<stock_left[idx]
            <<", required (paid+free)="<<total_items_needed<<"\n";
        return;
    }

    // calculate price (charge only for paid quantity)
    total_price = retail_price[idx] * quantity;
    // apply day discounts after promotion price
    cout<<"Enter the day of purchase: ";
    cin>>day;
    if(day=="Sunday" || day=="sunday"){
        total_price *= 0.90; // 10% discount
        cout<<"A 10% discount has been applied for Sunday purchases."<<endl;
    }
    else if(day=="Saturday" || day=="saturday"){
        total_price *= 0.95; // 5% discount
        cout<<"A 5% discount has been applied for Saturday purchases."<<endl;
    }
    else if(day!="Sunday" && day!="saturday" && day!="Saturday" && day!="sunday"){
        cout<<"No discount applied for this day."<<endl;
    }
    else{
        cout<<"invalid input!"<<endl;
    }

    // update sold and stock
    sold[idx] += total_items_needed; // remove both paid and free items from stock
    stock_left[idx] = units[idx] - sold[idx];

    cout<<"Purchase successful! Paid units: "<<quantity
        <<", Free units: "<<free_items
        <<", Total taken: "<<total_items_needed<<"\n";
    cout<<"Total price: $"<<fixed<<setprecision(2)<<total_price<<endl;
}
void view_purchase_history(string &garment_name, int &quantity,double &total_price){
    cout<<"--- PURCHASE HISTORY ---"<<endl;
    if(garment_name==""){
        cout<<"No purchase history available"<<endl;
        return;
    }

    const int NAME_W = 30;
    const int NUM_W  = 12;
    cout << left << setw(NAME_W) << "Garment Name" << right << setw(NUM_W) << "Quantity" << setw(NUM_W) << "Total Price" << endl;
    cout << string(NAME_W + NUM_W*2, '-') << endl;
    cout << left << setw(NAME_W) << garment_name << right << setw(NUM_W) << quantity << setw(NUM_W) << fixed << setprecision(2) << total_price << endl;
}
float update_amount(double &total_price){
   float amount;
   float change=0.0;
    cout<<"Enter the amount you have:";
    cin>>amount;
    if(amount<total_price){
        cout<<"Insufficient amount. Please pay the full amount of $"<<total_price<<endl;
        return change;
    }
    else if(amount==total_price){
        cout<<"Payment successful! No change due."<<endl;
        return change;
    }
    else if (amount<0){
        cout<<"Invalid amount entered."<<endl;
        return change;
    }
    else if (amount==0){
        cout<<"No purchase made."<<endl;
        return change;
    }
    else{
        float change=amount-total_price;
        cout<<"Payment successful! Your change is $"<<change<<endl;
        return change;
    }

}
void receipt_generation(string &garment_name, int &quantity,double &total_price,float &amount,float &change,float &discount,string &day,int &free_items)
{ 
    setColor(1);
    cout << "\nGenerating receipt...\n";

    const int LABEL_W = 22;
    const int VAL_W = 18;
    const int TOTAL_W = LABEL_W + VAL_W + 4;

    cout << string(TOTAL_W, '*') << endl;
    cout << "*" << setw(TOTAL_W-15) << right << "PURCHASE RECEIPT" ;
    cout<<setw(14)<<"|"<< endl;
    cout << string(TOTAL_W, '*') << endl;

    cout << left << setw(LABEL_W) << "Garment Name:" << right << setw(VAL_W) << garment_name ;
    cout<<setw(4)<<"|"<< endl;
    cout << left << setw(LABEL_W) << "Quantity:" << right << setw(VAL_W) << quantity;
    cout<<setw(4)<<"|"<< endl;
    cout << left << setw(LABEL_W) << "Total Price:" << right << setw(VAL_W) << fixed << setprecision(2) << total_price;
    cout<<setw(4)<<"|"<< endl;
    cout << left << setw(LABEL_W) << "Amount Paid:" << right << setw(VAL_W) << fixed << setprecision(2) << amount;
    cout<<setw(4)<<"|"<< endl;
    cout << left << setw(LABEL_W) << "Change Given:" << right << setw(VAL_W) << fixed << setprecision(2) << change ;
    cout<<setw(4)<<"|"<< endl;
    cout << left << setw(LABEL_W) << "Discount (%):" << right << setw(VAL_W) << fixed << setprecision(2) << discount;
    cout<<setw(4)<<"|"<< endl;
    cout << left << setw(LABEL_W) << "Day of Purchase:" << right << setw(VAL_W) << day;
    cout<<setw(4)<<"|"<< endl;
    cout << left << setw(LABEL_W) << "Offer (free):" << right << setw(VAL_W) << free_items ;
    cout<<setw(4)<<"|"<< endl;
    cout << string(TOTAL_W, '*') << endl;
    cout << "*" << setw(TOTAL_W-2) << left << " Thank you for shopping with us!" << "*" << endl;
    cout << string(TOTAL_W, '*') << endl;
    setColor(7);
}
//int gotoxy(int x, int y)
//{
  //  COORD coord;
    //coord.X = x;
    //coord.Y = y;
    //SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
//}

// cart logic
//file handling
//customer history