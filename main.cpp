#include <iostream>
#include<fstream>
#include <stdio.h>
using namespace std;
/*
 * SHOPPING APPLICATION
 * */

class Shopping{
private: //default values
    int productCode;
    float productPrice;
    float productDiscount;
    string productName;

public:
    //declair the functions, but doesnt write them yet
    void mainMenu();
    void administrator();
    void buyer();
    void addProduct();
    void removeProduct();
    void editProduct();
    void receipt();
    void displayProduct();

};

void Shopping ::mainMenu() {
    int choice;
    int adminPassword = 123;
    int adminID = 321;
    int userPassword;  //Given by user during login
    int userID;
    bool menu= true;
    do{
        cout << "----- WELCOME TO AWESOME-SHOPPING -------" << endl;
        cout << "1. Buyer" << endl;
        cout << "2. Admin" << endl;
        cout << "3. Exit" << endl;
        cout << "4. Please enter your option: ";
        cin >> choice;
        switch(choice){
            case 1:
                buyer(); break;
            case 2:
                cout << "---- Administrator page -----" << endl;
                cout << "Log in to continue! " << endl;
                cout << "UserID: ";
                cin >> userID;
                cout << "\nPassword: ";
                cin >> userPassword;
                if(userID == adminID && userPassword == adminPassword){
                    cout << "Successfully login! " << endl;
                    administrator(); break; // goes back to main menu
                }
                else{
                    cout << "Invalid userID or Password!" << endl;
                    cout << "Please try again" << endl;
                } break;
            case 3:
                cout << "Goodbye!" << endl;
                menu = false; break;  //Exit main menu
            default:
                cout << "Please enter a valid option from the list!" << endl; break;
        }
    }while(menu);
}
void Shopping ::administrator() {
    int choices;
    bool admin = true;
    do{
        cout << "----- Administrator Menu -----" << endl;
        cout << " 1. See inventory" << endl;
        cout << " 2. Add a product \n" << endl;
        cout << " 3. Modify a product \n" << endl;
        cout << " 4. Delete a product \n" << endl;
        cout << " 5. Go back to the menu \n" << endl;
        cout << "Please enter your choice: " ;
        cin >> choices;
        switch(choices){
            case 1: displayProduct(); break;
            case 2: addProduct(); break;
            case 3: editProduct(); break;
            case 4: removeProduct();break;
            case 5:
                cout << "Back to main menu" << endl;
                admin = false; //goes back to main menu
                break;
            default:
                cout << "Please enter a valid option!" << endl;
        }
    }while(admin);

}
void Shopping ::addProduct() {
    fstream data; //Creat an data object so we can read the file
    int c;
    int tokens = 0;
    float p,d;
    string n;

    cout << " ---- Add New Product ------" << endl;
    cout << "Product code: ";
    cin >> productCode;
    cout << "Enter product name: ";
    cin >> productName; //found in the shopping scope
    cout << "Product price: ";
    cin >> productPrice;
    cout << "Product discount: ";
    cin >> productDiscount;

    //data name of object
    // Opening fileios out opens is writing mode, ios in opens in reading mode
    data.open("productDataBase.txt", ios::in);

    //If this file does not exist, that means we dont have the product, and we add it to out file
    if(!data){
        data.open("productDataBase.txt", ios::app|ios::out); //Opens in writing mode
        //Structure how we want to write into the file
        data << " " << productCode << " " << productName << " " << productPrice << " " << productDiscount << "\n";
        data.close(); //Close the file after we are finished
    }
    //if the file does exist, then we read it
    else{

        //initialize the index of the file
        data >> c >> n >> p >> d;
        //Use the loop to ilterate through the file
        //Illterating through the file to check if the read code from teh file c, matches the production code
        // Checks for duplication , if increase tokens
        while(!data.eof()){
            if(c == productCode){
                tokens++;
            }
            data >> c >> n >> p >> d;
        }
        data.close();
    }

    //If a product already exist hence token >0
    if(tokens > 0){
        mainMenu(); //How does this affect the program?
    }
    else{
        //if product is not in the list, it will be added
        data.open("productDataBase.txt", ios::app|ios::out);
        data << " " << productCode << " " << productName << " " << productPrice << " " << productDiscount << "\n";
        data.close();
    }
    cout << "Product successfully added to the productDataBase.txt" << endl;
}
void Shopping ::editProduct(){
    //creat objects of fstream class
    fstream data, data1;
    int productKey;
    int tokens = 0;
    int codeOfNewProduct;
    float priceNewProduct;
    float discountNewProduct;
    string nameNewProduct;

    cout << "----- Edit Products ----- " << endl;
    cout << "Enter product code: ";
    cin >> productKey;

    //Search for the product via product code
    data.open("productDataBase.txt", ios::in);

    if(!data){
        cout << "File does not exist " << endl;
    }
    else {
        //We save our edited file to productDataBase1. Later we will delete productDataBase,
        // and rename productDataBase1 to productDataBase.
        data1.open("productDataBase1.txt", ios::app | ios::in);

        //initializing a new file by copying it from the old productDataBase.txt
        data >> productCode >> productName >> productPrice >> productDiscount;

        //Loop will ilterate through the productDataBase.txt file
        while(!data.eof()){
            if(productKey == productCode){ //productKey entered by user and is the product we want edited.
                cout << "Please enter the code of the new product: ";
                cin >> codeOfNewProduct;
                cout << "\nEnter name of the product";
                cin >> nameNewProduct;
                cout << "\nEnter price of product: ";
                cin >> priceNewProduct;
                cout << "\nEnter discount: ";
                cin >> discountNewProduct;

                //All data will be updated with data1 obj.

                data1 << " " << codeOfNewProduct << " " << nameNewProduct << " " << priceNewProduct << " " << discountNewProduct << "\n";
                cout << "Record edited! " << endl;
                tokens++;
            }
            else // Non of the productCodes in the files matches the productKey
            {
                data1 << " " << productCode << " " << productName << " " << productPrice << " " << productDiscount <<"\n";
            }
            data >> productCode>> productName >> productPrice >> productDiscount;
        }
        data.close();
        data1.close();

        //Removed the list inside the file, and rename the old file into the new file
        remove("productDataBase.txt");
        rename("productDataBase1.txt", "productDataBase.txt");

    }

    if(tokens == 0)
    {
        cout << "Record not fount, sorry!" << endl;
    }
}
void Shopping ::removeProduct(){

    fstream data, data1;
    int productKey;
    int tokens=0;

    cout << "-----REMOVE PRODUCT----" << endl;
    cout<< "Please enter the code of the product you want to DELETE: ";
    cin >> productKey;
    data.open("productDataBase.txt", ios::in);

    if(!data){ //Check if file does exist
        cout << "File does not exist" << endl;
    }

    else{
        //Opens a new file where we copy all of the old data execpt the product you want to delete.
        data1.open("productDataBase1.txt", ios::app|ios::out);
        data>>productCode>>productName>>productPrice>>productDiscount;
        while(!data.eof()){
            //Product code that was given by the user was found and deleted
            if(productKey == productCode){
                cout << "Product deleted successfully!" << endl;
                tokens++;
            }
            else{
                //product code was not found, and the data1 will be displayed
                cout << "The product code that was given does not exist!" << endl;
                //cout << "Please take a look at out inventory!\n" << endl;
                data1 << " " << productCode << " " << productName << " " << productPrice << " " << productDiscount << "\n";
            }
            data >> productCode >> productName >> productPrice >> productDiscount;
        }
        data.close();
        data1.close();

        //Replace old file with new updated file
        remove("productDataBase.txt");
        rename("productDataBase1.txt","productDataBase");

        if(tokens==0){
            cout << "Record not found!" << endl;
        }
    }
}
void Shopping ::buyer(){
    int choice;
    bool buyer = true;
    do{
        cout << "-------BUYER Menu-----" << endl;
        cout << "\nOptions: " << endl;
        cout << "1. Buy product " << endl;
        cout << "2. Go to main menu" << endl;
        cout << "Please enter your choice: ";
        cin >> choice;
        switch(choice){
            case 1: receipt();break;
            case 2:
                cout << "Back to main menu" << endl;
                buyer = false; break;
            default:
                cout << "Please enter a valid option! " << endl; break;
        }
    }while(buyer);
}
void Shopping ::displayProduct() {
    //Open inventory list
    fstream data;
    data.open("productDataBase.txt", ios::in);
    cout << "Product Code\tName\t\tPrice\tDiscount\n" << endl;
    data>>productCode>> productName>> productPrice >> productDiscount;

    while(!data.eof()){
        cout << productCode << "\t\t" << productName << "\t\t" << productPrice << "\t" << productDiscount <<"\n";
        data>>productCode>>productName>>productPrice>>productDiscount;
    }
    data.close();
}
void Shopping::receipt() {
    fstream data;
    int arrayofCodes[100];
    int arrayofQuantity[100];
    int choices;
    int c=0; //product code the user wants to order
    float amount=0;
    float discount=0;
    float total=0;
    bool shopping = true;

    cout << "--- Receipt ---" << endl;
    data.open("productDataBase.txt", ios::in);
    if(!data){
        cout << "Empty database!" << endl;
    }
    else{
        data.close();

        displayProduct();
        cout << "\nPlease place the order!" << endl;

        do{
            cout << "Enter product code: ";
            cin >> arrayofCodes[c];
            cout << "Enter product quantity" << endl;
            cin >> arrayofQuantity[c];

            // if the product code entered bythe user, matches by the code that is being entered,
            // we display a duplicate code//prevents from buying double up of a product
            for(int i=0; i<c;i++){
                if(arrayofCodes[c]==arrayofCodes[i]){
                    cout << "\nDuplicated product code. Please try again!" << endl;
                }
            }
            c++;
            cout << "Do you want to buy another product?" << endl;
            cout <<"1 yes    2 no" << endl;
            cin >> choices;

            //Goes to the receipt
            if(choices == 2){
                shopping = false;
            }
        }while(shopping);

        cout << "--- Receipt---" << endl;
        cout << "\nProduct Code\t Product name\t Product quantity\t Price \t Amount" << endl;

        for(int i=0;i<c;i++){
            data.open("productDataBase.txt", ios::in);
            data>>productCode>>productName>>productPrice>> productDiscount;

            //Matching if the code entered by the user is arrayofCode[i]
            //if the code is found, then we will add it to the shopping basket
            while(!data.eof()){
                if(productCode==arrayofCodes[i]){
                    amount = productPrice*arrayofQuantity[i];
                    discount = amount - (amount*productDiscount/100);  //Discount is calculated and stored in this variable
                    total = total + discount;
                    cout << "\n" << productCode <<"\t\t"<< productName <<"\t\t"<< arrayofQuantity[i] <<"\t\t"<< amount <<"\t"<< productDiscount;
                }
                data >> productCode >> productName >> productPrice >> productDiscount;
            }
        }
        data.close();
    }
    cout << "\n------------------\n" << endl;
    cout << "\nTotal Amount: " << total << endl;
}
int main() {
    Shopping s;
    s.mainMenu();

    return 0;
}
