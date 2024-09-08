#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <thread>
#include <chrono>
using namespace std;
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define RESET "\033[0m"

long double initialDeposit;
string tempPassword;
string checker;
char c;
bool b=true;
void pointer(int x)
{
    int count=x;
    string dots=".........";
    cout << "\033[?25l";
    int size=dots.size();
    for(int i=0; i<count; i++)
    {
        for (int i=0; i<size; i++)
        {
            char c=dots[i];
            cout <<YELLOW << c <<RESET;
            this_thread::sleep_for(chrono::milliseconds(80));
        }
        this_thread::sleep_for(chrono::milliseconds(20));
        for (int i=size-1; i>=0; i--)
        {
            cout << "\b \b" ;
            this_thread::sleep_for(chrono::milliseconds(80));
        }

    }
    for (int i=0; i<size; i++)
    {
        char c=dots[i];
        cout <<YELLOW << c <<RESET;
        this_thread::sleep_for(chrono::milliseconds(80));
    }
    this_thread::sleep_for(chrono::milliseconds(100));
    cout<<endl;
    char a = 176, b = 219;
    for (int i = 0; i <= 30; i++)
    {
        cout << "\r";
        for (int j = 0; j < i; j++)
            cout <<YELLOW << b <<RESET;

        for (int j = i; j < 30; j++)
            cout <<WHITE << a <<RESET;
        cout <<YELLOW<< (i * 100) / 30<< "%" <<RESET ;
        this_thread::sleep_for(chrono::milliseconds(80));
    }
    this_thread::sleep_for(chrono::milliseconds(50));
    cout<<endl;
    cout << "\033[?25h";
}
void brightenText(const string& text, int iterations, int delay)
{
    cout << "\033[?25l";
    // Initial ANSI escape code for background color (black)
    string bgEscape = "\033[48;5;0m";

    // ANSI escape codes for foreground color (black to white)
    string fgEscapeStart = "\033[38;5;";
    string fgEscapeEnd = "m";

    // Loop to increase brightness gradually
    for (int i = 0; i <= iterations; ++i)
    {
        // Calculate the color code for increased brightness (black to white)
        int colorCode = 232 + i * (256-232) / iterations;

        // Construct the ANSI escape code for foreground color
        string fgEscape = fgEscapeStart + to_string(colorCode) + fgEscapeEnd;

        // Print text with background color and increasing brightness
        cout <<"\r" << bgEscape << fgEscape << text;

        // Sleep to control the speed of the effect
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}
class Account
{
private:
    string accHolderName;
    string password;
    string address;
    long long int accNum;
    double balance;
public:
    void setValues(int index)
    {
        accNum = index + 1;
        cout <<endl<< "Enter details for account no. " << accNum << endl;
        cout << "Enter Account holder's name:";
        getline(cin, accHolderName);
        cout << "Enter a strong password:";
        getline(cin, password);
        cout <<YELLOW<< "Remember your password; it will be needed." <<RESET<< endl;
        cout << "Enter your address :";
        getline(cin, address);
        do
        {
            int dotCounter=0;
            cout << "Enter amount for the initial deposit: ";
            checker.clear();
            getline(cin,checker);
            for(int i=0; i<checker.size(); i++)
            {
                c=checker[i];
                if(isdigit(c)  || c=='.' )
                {
                    b=true;
                    if(checker.size()>20 || checker[0]=='.' || checker[checker.size()-1]=='.' )
                    {
                        b=false;
                        cout << "Invalid choice, ";
                        break;
                    }
                    if(c=='.')
                    {
                        dotCounter++;
                    }
                }
                else
                {
                    cout << "Invalid choice, ";
                    b=false;
                    break;
                }
            }
            if(dotCounter>1)
            {
                cout << "Invalid choice, ";
                b=false;
            }
        }
        while(b==false);
        balance=stold(checker);
        time_t currentTime = time(nullptr);
        char date[100];
        strftime(date,100, "Created on %I:%M:%S%p  %d-%m-%Y ", localtime(&currentTime));
        cout << "\033[?25l";
        string message = "Creating account";
        int size=message.size();
        for (int i=0; i<size; i++)
        {
            char c=message[i];
            cout<<YELLOW<<c<<RESET;
            this_thread::sleep_for(chrono::milliseconds(60));
        }
        cout << "\033[?25h";
        pointer(1);
        cout<<RESET;
        message = "Your account is successfully created.";
        size=message.size();
        for (int i=0; i<size; i++)
        {
            char c=message[i];
            cout<<YELLOW<<c<<RESET;
            this_thread::sleep_for(chrono::milliseconds(40));
        }
        cout<<endl;
        ofstream file("myAccounts.txt", ios::app);
        file << accNum << endl;
        file << accHolderName << endl;
        file << address << endl;
        file << password << endl;
        file <<fixed<<setprecision(6)<< balance << endl;
        file<<date<<endl;
        string fileName=to_string(accNum) +".txt";
        ofstream outfile(fileName);
        outfile<<endl<<date<<endl;
        outfile<<"Initial valance :"<<fixed<<setprecision(6)<<balance<<"$";
    }
};
void getValues(int index, vector<string> details)
{
    int start = (index * 6) - 3;
    tempPassword = details[start];
    string enteredPass;
    cout << "Enter your password :";
    getline(cin, enteredPass);
    if (enteredPass == tempPassword)
    {
        int infoIndex = ((index - 1) * 6);
        cout <<YELLOW<< "Account no: " << details[infoIndex] << endl;
        cout << "Name: " << details[infoIndex + 1] << endl;
        cout << "Address: " << details[infoIndex + 2] << endl;
        cout << "Password: " << details[infoIndex + 3] << endl;
        cout << "Current Balance: " << details[infoIndex + 4]<<"$" << endl;
        cout<<details[infoIndex+5]<<RESET<<endl;
    }
    else
    {
        cout<<RED<<"Wrong password"<<RESET<<endl;
    }
}
void Menu()
{
    cout << CYAN << " 1" << RESET << ". Create account";
    cout << CYAN << "       2" << RESET << ". Print details\n";
    cout << CYAN << " 3" << RESET << ". Deposit";
    cout << CYAN << "              4" << RESET << ". Withdraw\n";
    cout << CYAN << " 5" << RESET << ". Admin access";
    cout << CYAN << "         6" << RESET << ". Transfer money\n";
    cout << CYAN << " 7" << RESET << ". Account update";
    cout << CYAN << "       8" << RESET << ". Transaction history\n";
    cout << CYAN << " 9" << RESET << ". Account delete";
    cout << CYAN <<"      10" << RESET << ". Menu \n";
    cout << CYAN <<"11" << RESET << ". End Program "<< endl;
}
int main()
{
    int choice, accNum, adminChoice, transferRecipient;
    const string adminPass = "123123.add";
    string enteredAdminPass;
    string userDecision;
    string temp;
    vector<string> accDetails;
    Account tempAcc;
    ifstream file("myAccounts.txt");
    accDetails.clear();
    while(getline(file,temp))
    {
        accDetails.push_back(temp);
    }
    file.close();
    int totalAccounts = (accDetails.size()) / 6;
    cout << "\033[?25l";
        string message = "WELCOME TO JAST CLUB";
        int size=message.size();
        for (int i=0; i<size; i++)
        {
            char c=message[i];
            cout <<GREEN << c <<RESET;
            this_thread::sleep_for(chrono::milliseconds(60));
        }
        cout << "\033[?25h";
        this_thread::sleep_for(chrono::milliseconds(100));
        cout<<endl;
    Menu();
    do
    {
        do
        {
            cout <<RED <<"Main menu - "<<RESET<< "Enter your choice ("<<RED<<"1 "<<RESET<<"to"<<RED<<" 11"<<RESET<<"): ";
            checker.clear();
            getline(cin,checker);
            for(int i=0; i<checker.size(); i++)
            {
                c=checker[i];
                if(isdigit(c) )
                {
                    b=true;
                    if(checker.size()>20)
                    {
                        b=false;
                        cout << "Invalid choice, try again ";
                        break;
                    }
                }
                else
                {
                    cout << "Invalid choice, try again "<<endl;
                    b=false;
                    break;
                }
            }
        }
        while(b==false);
        choice=stoi(checker);
        switch (choice)
        {
        case 1:
            tempAcc.setValues(totalAccounts);
            totalAccounts++;
            break;
        case 2:
        {
            do
            {
                cout << "Insert the account no. : ";
                checker.clear();
                getline(cin,checker);
                for(int i=0; i<checker.size(); i++)
                {
                    c=checker[i];
                    if(isdigit(c) )
                    {
                        b=true;
                        if(checker.size()>9)
                        {
                            b=false;
                            cout << "Invalid choice, ";
                            break;
                        }
                    }
                    else
                    {
                        cout << "Invalid choice, ";
                        b=false;
                        break;
                    }
                }
            }
            while(b==false);
            accNum=stoi(checker);
            if(accNum<=(accDetails.size())/6)
            {
                int passIndex=(accNum*6)-3;
                if(accDetails[passIndex+1]!="Deleted account !75@766*56%S$90404!")
                {

                    getValues(accNum, accDetails);
                }
                else
                {
                    cout<<RED<<"This account is deleted"<<RESET<<endl;
                }
            }
            else
            {
                cout<<"Account is not available"<<endl;
            }
        }
        break;
        case 3:
        {
            long double tempBalance;
            string line;
            do
            {
                cout << "Insert the account no. : ";
                checker.clear();
                getline(cin,checker);
                for(int i=0; i<checker.size(); i++)
                {
                    c=checker[i];
                    if(isdigit(c) )
                    {
                        b=true;
                        if(checker.size()>20)
                        {
                            b=false;
                            cout << "Invalid choice, ";
                            break;
                        }
                    }
                    else
                    {
                        cout << "Invalid choice, ";
                        b=false;
                        break;
                    }
                }
            }
            while(b==false);
            accNum=stoi(checker);

            if(accNum>0 && accNum<=(accDetails.size())/6)
            {
                int index = (accNum * 6) - 2;
                int passIndex=(accNum*6)-3;
                if(accDetails[passIndex+1]!="Deleted account !75@766*56%S$90404!")
                {
                    tempBalance=stold(accDetails[index]);
                    long double depositAmount;
                    cout<<RED<<"If you don't want to deposit , enter 0 to return main menu"<<RESET<<endl;
                    do
                    {
                        int dotCounter=0;
                        cout << "Enter amount for deposit: ";
                        checker.clear();
                        getline(cin,checker);
                        for(int i=0; i<checker.size(); i++)
                        {
                            c=checker[i];
                            if(isdigit(c)  || c=='.' )
                            {
                                b=true;
                                if(checker.size()>20 || checker[0]=='.' || checker[checker.size()-1]=='.')
                                {
                                    b=false;
                                    cout << "Invalid choice, ";
                                    break;
                                }
                                if(c=='.')
                                {
                                    dotCounter++;
                                }
                            }
                            else
                            {
                                cout << "Invalid choice, ";
                                b=false;
                                break;
                            }
                        }
                        if(dotCounter>1)
                        {
                            cout << "Invalid choice, ";
                            b=false;
                        }
                    }
                    while(b==false);
                    depositAmount=stold(checker);
                    if (depositAmount > 0)
                    {
                        tempBalance = tempBalance + depositAmount;
                        time_t currentTime = time(nullptr);
                        char date[100];
                        strftime(date,100, "On %I:%M:%S%p  %d-%m-%Y ", localtime(&currentTime));
                        cout <<fixed<<setprecision(6)<<depositAmount<< "$ is deposited Successfully"<<endl;
                        accDetails[index] = to_string(tempBalance);

                        ofstream outFile("myAccounts.txt", ios::trunc);
                        for (int i = 0; i < accDetails.size(); i++)
                        {
                            outFile << accDetails[i] << endl;
                        }
                        string fileName=to_string(accNum)+".txt";
                        ofstream trhistory(fileName,ios::app);
                        trhistory<<endl<<endl<<date<<endl<<"Deposited :"<<fixed<<setprecision(6)<<depositAmount<<"$";
                        trhistory<<endl<<"new balance is :"<<fixed<<setprecision(6)<<tempBalance<<"$";
                    }
                    else
                    {
                        cout<<"Invalid amount"<<endl;
                    }
                }
                else
                {
                    cout<<"This account is deleted"<<endl;
                }
            }
            else
            {
                cout<<"Account is not available"<<endl;
            }
        }
        break;
        case 4:
        {
            long double tempBalance;
            string line;
            do
            {
                cout << "Insert the account no. : ";
                checker.clear();
                getline(cin,checker);
                for(int i=0; i<checker.size(); i++)
                {
                    c=checker[i];
                    if(isdigit(c) )
                    {
                        b=true;
                        if(checker.size()>9)
                        {
                            b=false;
                            cout << "Invalid choice, ";
                            break;
                        }
                    }
                    else
                    {
                        cout << "Invalid choice, ";
                        b=false;
                        break;
                    }
                }
            }
            while(b==false);
            accNum=stoi(checker);
            int passIndex = (accNum * 6) - 3;
            if(accNum>0 && accNum<=(accDetails.size())/6)
            {
                if(accDetails[passIndex+1]!="Deleted account !75@766*56%S$90404!")
                {
                    int index = accNum * 6 - 2;
                    tempPassword = accDetails[passIndex];
                    string enteredPass;
                    cout << "Enter your password :";
                    getline(cin, enteredPass);
                    if (enteredPass == tempPassword)
                    {
                        tempBalance=stold(accDetails[index]);
                        cout<< fixed << setprecision(6)<<"Current Balance :"<<tempBalance<<"$"<<endl;
                        long double withdrawalAmount;
                        cout<<RED<<"If you don't want to withdraw , enter 0 or bigger amount than current balance to return main menu"<<RESET<<endl;

                        do
                        {
                            int dotCounter=0;
                            cout << "Enter amount for withdraw : ";
                            checker.clear();
                            getline(cin,checker);
                            for(int i=0; i<checker.size(); i++)
                            {
                                c=checker[i];
                                if(isdigit(c)  || c=='.' )
                                {
                                    b=true;
                                    if(checker.size()>20 || checker[0]=='.' || checker[checker.size()-1]=='.')
                                    {
                                        b=false;
                                        cout << "Invalid choice, ";
                                        break;
                                    }
                                    if(c=='.')
                                    {
                                        dotCounter++;
                                    }
                                }
                                else
                                {
                                    cout << "Invalid choice, ";
                                    b=false;
                                    break;
                                }
                            }
                            if(dotCounter>1)
                            {
                                cout << "Invalid choice, ";
                                b=false;
                            }
                        }
                        while(b==false);
                        withdrawalAmount=stold(checker);
                        if (withdrawalAmount > 0 && withdrawalAmount <= tempBalance)
                        {
                            tempBalance = tempBalance - withdrawalAmount;
                            time_t currentTime = time(nullptr);
                            char date[100];
                            strftime(date,100, "On %I:%M:%S%p  %d-%m-%Y ", localtime(&currentTime));
                            cout << fixed << setprecision(6)<<withdrawalAmount<< "$ is withdrawn Successfully"<<endl;
                            cout << fixed << setprecision(6) << "Current Balance :" << tempBalance<<"$"<<endl;
                            accDetails[index] = to_string(tempBalance);
                            ofstream outFile("myAccounts.txt", ios::trunc);
                            for (int i = 0; i < accDetails.size(); i++)
                            {
                                outFile << accDetails[i] << endl;
                            }
                            string fileName=to_string(accNum)+".txt";
                            ofstream trhistory(fileName,ios::app);
                            trhistory<<endl<<endl<<date<<endl<<"withdrawn :" << fixed << setprecision(6) <<withdrawalAmount<<"$";
                            trhistory<<endl<<"new balance is :" << fixed << setprecision(6) <<tempBalance<<"$";
                        }
                        else
                        {
                            cout<<"Invalid amount, withdrawal amount can't be bigger than current balance"<<endl;
                        }
                    }
                    else
                    {
                        cout<<"Incorrect password"<<endl;
                    }
                }
                else
                {
                    cout<<"This account is deleted"<<endl;
                }
            }
            else
            {
                cout<<"Account is not available"<<endl;
            }
        }
        break;
        case 5:
        {
            cout << "\033[?25l";
            cout << "Enter admin password : ";
            cin >> enteredAdminPass;
            if (enteredAdminPass == adminPass)
            {
                cout << "\033[?25l";
                string text = "------ Welcome Admin -----";

                brightenText(text, 20, 40);
                this_thread::sleep_for(chrono::milliseconds(1000));
                cout<<endl<<"1. print full account's list \n2. print specific account details  "<<endl;
                while (cin.get() != '\n') {}
                do
                {
                    cout <<"Admin - Enter your choice: ";
                    checker.clear();
                    cout << "\033[?25h";
                    getline(cin,checker);
                    for(int i=0; i<checker.size(); i++)
                    {
                        c=checker[i];
                        if(isdigit(c))
                        {
                            b=true;
                            if(checker.size()>9)
                            {
                                b=false;
                                cout << "Invalid choice, ";
                                break;
                            }
                        }
                        else
                        {
                            cout << "Invalid choice, try again"<<endl;
                            b=false;
                            break;
                        }
                    }
                }
                while(b==false);
                adminChoice=stoi(checker);
                if(adminChoice==1)
                {
                    cout << "\033[?25l";
                    string message = "Preparing list.........";
                    int size=message.size();
                    for (int i=0; i<size; i++)
                    {
                        char c=message[i];
                        cout <<YELLOW << c <<RESET;
                        this_thread::sleep_for(chrono::milliseconds(60));
                    }
                    cout<<endl;
                    message = "Fetching data";
                    size=message.size();
                    for (int i=0; i<size; i++)
                    {
                        char c=message[i];
                        cout <<YELLOW << c <<RESET;
                        this_thread::sleep_for(chrono::milliseconds(60));
                    }
                    pointer(1);
                    cout<<endl<<"Full account list :"<<endl;
                    int counter=0;
                    for(int i=0; i<accDetails.size(); i++)
                    {
                        if(i%6==0)
                        {
                            cout<<YELLOW<<"Account no. "<<accDetails[i]<<RESET<<endl;
                        }
                        else if(i%6==1)
                        {
                            cout<<CYAN<<"Account name : "<<accDetails[i]<<RESET<<endl;
                        }
                        else if(i%6==2)
                        {
                            cout<<CYAN<<"Address : "<<accDetails[i]<<RESET<<endl;
                        }
                        else if(i%6==3)
                        {
                            cout<<CYAN<<"Password : "<<accDetails[i]<<RESET<<endl;
                        }
                        else if(i%6==4)
                        {
                            cout<<CYAN<<"Current Balance : "<<accDetails[i]<<RESET<<endl;
                        }
                        else
                        {
                            cout<<CYAN<<accDetails[i]<<RESET<<endl;
                        }
                        counter++;
                        if(counter==6)
                        {
                            this_thread::sleep_for(chrono::milliseconds(100));
                            counter=0;
                        }
                    }
                }
                else if(adminChoice==2)
                {
                    do
                    {
                        cout << "Enter account no. : ";
                        checker.clear();
                        getline(cin,checker);
                        for(int i=0; i<checker.size(); i++)
                        {
                            c=checker[i];
                            if(isdigit(c))
                            {
                                b=true;
                                if(checker.size()>9)
                                {
                                    b=false;
                                    cout << "Invalid choice, ";
                                    break;
                                }
                            }
                            else
                            {
                                cout << "Invalid choice, try again"<<endl;
                                b=false;
                                break;
                            }
                        }
                    }
                    while(b==false);
                    adminChoice=stoi(checker);
                    if(adminChoice<=(accDetails.size())/6)
                    {
                        int index = (adminChoice - 1) * 6;
                        cout <<CYAN<< "Account no: " << accDetails[index] << endl;
                        cout << "Name: " << accDetails[index + 1] << endl;
                        cout << "Address: " << accDetails[index + 2] << endl;
                        cout << "Password: " << accDetails[index + 3] << endl;
                        cout << "Current Balance: " << accDetails[index + 4] <<"$"<< endl;
                        cout<<accDetails[index+5]<<RESET<<endl;
                    }
                    else
                    {
                        cout<<"Account is not available"<<endl;
                    }
                }
                else
                {
                    cout<<"Invalid choice"<<endl;
                }
            }
            else
            {
                cout << "\033[?25h";
                while (cin.get() != '\n') {}
                cout << "Incorrect password"<<endl;
            }
            cout << "\033[?25h";
        }
        break;
        case 6:
        {
            long double senderBalance;
            long double recipientBalance;
            long double transferAmount;

            do
            {
                cout <<"Enter sender account no. : ";
                checker.clear();
                getline(cin,checker);
                for(int i=0; i<checker.size(); i++)
                {
                    c=checker[i];
                    if(isdigit(c))
                    {
                        b=true;
                        if(checker.size()>9)
                        {
                            b=false;
                            cout << "Invalid choice, ";
                            break;
                        }
                    }
                    else
                    {
                        cout << "Invalid choice, try again"<<endl;
                        b=false;
                        break;
                    }
                }
            }
            while(b==false);
            accNum=stoi(checker);
            if(accNum>0 && accNum<=(accDetails.size())/6)
            {
                int senderIndex = accNum * 6 - 2;
                tempPassword = accDetails[senderIndex-1];
                if(accDetails[senderIndex]!="Deleted account !75@766*56%S$90404!")
                {
                    string enteredPass;
                    cout << "Enter your password :";
                    getline(cin, enteredPass);

                    if (enteredPass == tempPassword)
                    {
                        senderBalance=stold(accDetails[senderIndex]);
                        cout<< fixed << setprecision(6)<<"Current Balance :"<<senderBalance<<"$"<<endl;
                        do
                        {
                            cout << "Enter the receiver account no. :";
                            checker.clear();
                            getline(cin,checker);
                            for(int i=0; i<checker.size(); i++)
                            {
                                c=checker[i];
                                if(isdigit(c))
                                {
                                    b=true;
                                    if(checker.size()>9)
                                    {
                                        b=false;
                                        cout << "Invalid choice, ";
                                        break;
                                    }
                                }
                                else
                                {
                                    cout << "Invalid choice, try again"<<endl;
                                    b=false;
                                    break;
                                }
                            }
                        }
                        while(b==false);
                        transferRecipient=stoi(checker);
                        if(transferRecipient>0 && transferRecipient<=(accDetails.size())/6)
                        {
                            int recipientIndex = transferRecipient * 6 - 2;
                            if(accDetails[recipientIndex]!="Deleted account !75@766*56%S$90404!")
                            {
                                recipientBalance=stold(accDetails[recipientIndex]);
                                cout<<RED<<"If you don't want to transfer , enter 0 or bigger amount than current balance to return main menu"<<RESET<<endl;
                                do
                                {
                                    int dotCounter=0;
                                    cout << "Enter amount to transfer : ";
                                    checker.clear();
                                    getline(cin,checker);
                                    for(int i=0; i<checker.size(); i++)
                                    {
                                        c=checker[i];
                                        if(isdigit(c)  || c=='.' )
                                        {
                                            b=true;
                                            if(checker.size()>20 || checker[0]=='.' || checker[checker.size()-1]=='.')
                                            {
                                                b=false;
                                                cout << "Invalid choice, ";
                                                break;
                                            }
                                            if(c=='.')
                                            {
                                                dotCounter++;
                                            }
                                        }
                                        else
                                        {
                                            cout << "Invalid choice, ";
                                            b=false;
                                            break;
                                        }
                                    }
                                    if(dotCounter>1)
                                    {
                                        cout << "Invalid choice, ";
                                        b=false;
                                    }
                                }
                                while(b==false);
                                transferAmount=stold(checker);

                                if (transferAmount > 0 && transferAmount <= senderBalance)
                                {
                                    senderBalance = senderBalance - transferAmount;
                                    recipientBalance = recipientBalance + transferAmount;

                                    cout <<transferAmount<< "$ is transfered Successfully"<<endl;
                                    cout << fixed << setprecision(6) << "Current Balance :" << senderBalance<<"$"<<endl;
                                    accDetails[senderIndex] = to_string(senderBalance);
                                    accDetails[recipientIndex] = to_string(recipientBalance);
                                    ofstream outFile("myAccounts.txt", ios::trunc);
                                    for (int i = 0; i < accDetails.size(); i++)
                                    {
                                        outFile << accDetails[i] << endl;
                                    }
                                    string fileName=to_string(transferRecipient)+".txt";
                                    ofstream trhistory(fileName,ios::app);
                                    time_t currentTime = time(nullptr);
                                    char date[100];
                                    strftime(date,100, "On %I:%M:%S%p  %d-%m-%Y ", localtime(&currentTime));
                                    trhistory<<endl<<endl<<date<<endl<<"Received " << fixed << setprecision(6) <<transferAmount<<"$ from account no. "<<accNum;
                                    trhistory<<endl<<"new balance is :" << fixed << setprecision(6) <<recipientBalance<<"$";
                                    fileName=to_string(accNum)+".txt";
                                    ofstream trhistory1(fileName,ios::app);
                                    time_t currentTime1 = time(nullptr);
                                    char date1[100];
                                    strftime(date1,100, "On %I:%M:%S%p  %d-%m-%Y ", localtime(&currentTime1));
                                    trhistory1<<endl<<endl<<date1<<endl<<"Transferred " << fixed << setprecision(6)  <<transferAmount<<"$ to account no. "<<transferRecipient;
                                    trhistory1<<endl<<"new balance is :" << fixed << setprecision(6) <<senderBalance<<"$";
                                }
                                else
                                {
                                    cout<<"Invalid amount to transfer, amount bigger than current balance or less than 1 can't be transferred"<<endl;
                                }
                            }
                            else
                            {
                                cout<<"This account is deleted"<<endl;
                            }
                        }
                        else
                        {
                            cout<<"Account is not available"<<endl;
                        }
                    }
                    else
                    {
                        cout<<"Incorrect password"<<endl;
                    }
                }
                else
                {
                    cout<<"Account is deleted"<<endl;
                }
            }
            else
            {
                cout<<"Account is not available"<<endl;
            }
        }
        break;
        case 7:
        {
            do
            {
                cout << "Insert the account no. : ";
                checker.clear();
                getline(cin,checker);
                for(int i=0; i<checker.size(); i++)
                {
                    c=checker[i];
                    if(isdigit(c))
                    {
                        b=true;
                        if(checker.size()>9)
                        {
                            b=false;
                            cout << "Invalid choice, ";
                            break;
                        }
                    }
                    else
                    {
                        cout << "Invalid choice, try again"<<endl;
                        b=false;
                        break;
                    }
                }
            }
            while(b==false);
            accNum=stoi(checker);
            int passIndex = (accNum * 6) - 3;
            if(accNum<=(accDetails.size())/6)
            {
                if(accDetails[passIndex+1]!="Deleted account !75@766*56%S$90404!")
                {
                    int index = (accNum-1) * 6;
                    tempPassword = accDetails[passIndex];
                    string enteredPass;
                    cout << "Enter your password :";
                    getline(cin, enteredPass);
                    if (enteredPass == tempPassword)
                    {
                        time_t currentTime = time(nullptr);
                        char date[100];
                        strftime(date,100, "Updated on %I:%M:%S%p  %d-%m-%Y ", localtime(&currentTime));
                        cout<<"Enter new Name :";
                        getline(cin,accDetails[index+1]);
                        cout<<"Enter new Address :";
                        getline(cin,accDetails[index+2]);
                        cout<<"Enter new Password :";
                        getline(cin,accDetails[index+3]);
                        string Date;
                        Date=accDetails[index+5]+", "+date;
                        accDetails[index+5]=Date;
                        ofstream outFile("myAccounts.txt", ios::trunc);
                        for (int i = 0; i < accDetails.size(); i++)
                        {
                            outFile << accDetails[i] << endl;
                        }
                        cout<<"Account is updated successfully"<<endl;
                    }
                    else
                    {
                        cout<<"Incorrect password"<<endl;
                    }
                }
                else
                {
                    cout<<"This account is deleted"<<endl;
                }
            }
            else
            {
                cout<<"Account is not available"<<endl;
            }
        }
        break;
        case 8:
        {
            do
            {
                cout << "Insert the account no. : ";
                checker.clear();
                getline(cin,checker);
                for(int i=0; i<checker.size(); i++)
                {
                    c=checker[i];
                    if(isdigit(c))
                    {
                        b=true;
                        if(checker.size()>20)
                        {
                            b=false;
                            cout << "Invalid choice, ";
                            break;
                        }
                    }
                    else
                    {
                        cout << "Invalid choice, try again"<<endl;
                        b=false;
                        break;
                    }
                }
            }
            while(b==false);
            accNum=stoi(checker);
        }
        if(accNum<=(accDetails.size())/6)
        {
            int passIndex=(accNum*6)-3;
            if(accDetails[passIndex+1]!="Deleted account !75@766*56%S$90404!")
            {
                string tempPassword;
                cout<<"Enter Password :";
                getline(cin,tempPassword);
                if( tempPassword==accDetails[passIndex])
                {
                    string temp;
                    string fileName=to_string(accNum)+".txt";
                    ifstream trhistory (fileName);
                    while(getline(trhistory,temp))
                    {
                        cout<<temp<<endl;
                    }
                    trhistory.close();
                }
                else
                {
                    cout<<"Incorrect password"<<endl;
                }
            }
            else
            {
                cout<<"This account is deleted"<<endl;
            }
        }
        else
        {
            cout<<"Account is not available"<<endl;
        }
        break;
        case 9:
        {
            do
            {
                cout << "Insert the account no. : ";
                checker.clear();
                getline(cin,checker);
                for(int i=0; i<checker.size(); i++)
                {
                    c=checker[i];
                    if(isdigit(c))
                    {
                        b=true;
                        if(checker.size()>9)
                        {
                            b=false;
                            cout << "Invalid choice, ";
                            break;
                        }
                    }
                    else
                    {
                        cout << "Invalid choice, try again"<<endl;
                        b=false;
                        break;
                    }
                }
            }
            while(b==false);
            accNum=stoi(checker);
            int passIndex = (accNum * 6) - 3;
            if (accNum <= (accDetails.size()) / 6)
            {
                time_t currentTime = time(nullptr);
                char date[100];
                strftime(date,100, "Deleted on: %I:%M:%S%p  %d-%m-%Y ", localtime(&currentTime));
                if(accDetails[passIndex+1]!="Deleted account !75@766*56%S$90404!")
                {
                    int index = (accNum - 1) * 6;
                    int index1 = (accNum * 6) - 2;
                    tempPassword = accDetails[passIndex];
                    string enteredPass;
                    cout << "Enter your password :";
                    getline(cin, enteredPass);
                    if (enteredPass == tempPassword)
                    {
                        long double tempBalance = stold(accDetails[index1]);
                        if (tempBalance == 0)
                        {
                            ofstream outFile("myAccounts.txt", ios::trunc);
                            for (int i = 0; i <= index; i++)
                            {
                                outFile << accDetails[i] << endl;
                            }
                            for(int i=index+1; i<=index1; i++)
                            {
                                outFile<<"Deleted account !75@766*56%S$90404!"<<endl;
                            }
                            outFile<<date<<endl;
                            for (int i = index1 + 2; i < accDetails.size(); i++)
                            {
                                outFile << accDetails[i] << endl;
                            }
                            accDetails.clear();
                            ifstream file("myAccounts.txt");
                            while (getline(file, temp))
                            {
                                accDetails.push_back(temp);
                            }

                            string filename = to_string(accNum) + ".txt";
                            remove(filename.c_str());
                            string message = "deleting account";
                            int size=message.size();
                            cout << "\033[?25l";
                            for (int i=0; i<size; i++)
                            {
                                char c=message[i];
                                cout <<YELLOW << c <<RESET;
                                this_thread::sleep_for(chrono::milliseconds(60));
                            }
                            cout << "\033[?25h";
                            pointer(1);
                            message = "Account has been deleted successfully";
                            size=message.size();
                            for (int i=0; i<size; i++)
                            {
                                char c=message[i];
                                cout <<RED << c <<RESET;
                                this_thread::sleep_for(chrono::milliseconds(40));
                            }
                            cout<<endl;
                        }
                        else
                        {
                            cout << "Account can't be deleted now, please make a withdrawal or transfer all your money " << endl;
                        }
                    }
                    else
                    {
                        cout << "Incorrect password" << endl;
                    }
                }
                else
                {
                    cout<<"This account is deleted "<<endl;
                }
            }
            else
            {
                cout << "Account is not available" << endl;
            }
        }
        break;
        case 10:
            Menu();
            break;
        case 11:
        {
            string message = "Terminating program";
            int size=message.size();
            cout << "\033[?25l";
            for (int i=0; i<size; i++)
            {
                char c=message[i];
                cout <<YELLOW << c <<RESET;
                this_thread::sleep_for(chrono::milliseconds(60));
            }
            cout << "\033[?25h";
            pointer(1);
            message = "The program has terminated successfully";
            size=message.size();
            for (int i=0; i<size; i++)
            {
                char c=message[i];
                cout <<YELLOW << c <<RESET;
                this_thread::sleep_for(chrono::milliseconds(40));
            }
            cout<<endl;
        }
        break;
        default:
            cout <<RED<< "Invalid choice, try again :" <<RESET<< endl;
        }
        accDetails.clear();
        ifstream file("myAccounts.txt");
        if(file.is_open())
        {
            while (getline(file, temp))
            {
                accDetails.push_back(temp);
            }
            file.close();
        }
    }
    while (choice!= 11);
    return 0;
}
