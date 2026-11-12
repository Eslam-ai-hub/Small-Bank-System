#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

enum enTransactionMenueOption
{
    eDeposit = 1,
    eWithdraw = 2,
    eShowTotalBalances = 3,
    eShowManinMenue = 4
};

enum enMainMenueOptions
{
    eListClients = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eShowTransactionsMenue = 6,
    eMangeUsers = 7,
    eLogout = 8
};

enum enMangeUsers
{
    eListUsers = 1,
    eAddNewUser = 2,
    eDeleteUser = 3,
    eUpdateUser = 4,
    eFindUser = 5,
    eMainMenue = 6
};

enum enPermissions
{
    pAll = -1,
    pListClients = 1,
    pAddNewClient = 2,
    pDeleteClient = 4,
    pUpdateClient = 8,
    pFindClient = 16,
    pShowTransactionsMenue = 32,
    pMangeUsers = 64
};

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};
struct sUser
{
    string Username;
    string Password;
    short Permissions;
    bool MarkForDelete = false;
};

sUser CurrentUser;

void ShowMainMenue();
void ShowTransactionsMenue();
void ShowMangeUsersScreen();
void Login(); 
int GivePermissions();


vector<string> SplitString(string S, string delim)
{
    vector<string> vString;
    size_t pos = 0;
    string sWord;

    while ((pos = S.find(delim)) != std::string::npos)
    {
        sWord = S.substr(0, pos);
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S.erase(0, pos + delim.length());
    }

    if (S != "")
    {
        vString.push_back(S);
    }
    return vString;
}

sClient ConvertLineToRecord(string Line, string Seperator = "#//#")
{
    sClient Client;
    vector<string> vClientData;
    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);

    return Client;
}

sUser CovertLineToRecordTwo(string Line, string Seperator = "#//#")
{
    sUser User; 
    vector<string> vUser;
    vUser = SplitString(Line, Seperator);

    User.Username = vUser[0];
    User.Password = vUser[1];
    User.Permissions = stoi(vUser[2]);

    return User;

}

vector<sClient> LoadCleintsDataFromFile(string FileName)
{
    vector<sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            vClients.push_back(Client);
        }

        MyFile.close();
    }
    return vClients;
}

vector<sUser> LoadUsersDataFromFile(string FileName)
{
    vector<sUser> vUser;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        sUser User;

        while (getline(MyFile, Line))
        {
            User = CovertLineToRecordTwo(Line);
            vUser.push_back(User);
        }

        MyFile.close();
    }
    return vUser;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}

string ConvertRecordToLineTwo(sUser User, string Seperator = "#//#")
{
    string stUser = "";
    stUser += User.Username + Seperator;
    stUser += User.Password + Seperator;
    stUser += to_string(User.Permissions) ;
    return stUser;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
    vector<sClient> vClients;

    fstream MyFile;

    MyFile.open(FileName, ios::in); // Read Mode

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);

            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }

            vClients.push_back(Client);
        }

        MyFile.close();
    }

    return false;
}

sClient ReadNewClient()
{
    sClient Client;

    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber
            << "] already exists, Enter another Account Number? ";

        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

void PrintClientRecordLine(sClient Client)
{
    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(10) << Client.PinCode;
    cout << "| " << left << setw(40) << Client.Name;
    cout << "| " << left << setw(12) << Client.Phone;
    cout << "| " << left << setw(12) << Client.AccountBalance;
}

void PrintUserRecordLine(sUser User)
{
    cout << "| " << left << setw(15) << User.Username;
    cout << "| " << left << setw(10) << User.Password;
    cout << "| " << left << setw(40) << User.Permissions;
    
}

void PrintClientRecordBalancesLine(sClient Client)
{
    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(40) << Client.Name;
    cout << "| " << left << setw(12) << Client.AccountBalance;
}

void ShowAllClientsScreen()
{
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________________________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________________________________________________________\n" << endl;

    if (vClients.size() == 0)
    {
        cout << "\t\t\t\tNo Clients Available In the System!";
    }
    else
    {
        for (sClient Client : vClients)
        {
            PrintClientRecordLine(Client);
            cout << endl;
        }
    }

    cout << "\n_______________________________________________________________________________________________________\n" << endl;
}

void ShowTotalBalances()
{
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________________________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________________________________________________________\n" << endl;

    double TotalBalances = 0;

    if (vClients.size() == 0)
    {
        cout << "\t\t\t\tNo Clients Available In the System!";
    }
    else
    {
        for (sClient Client : vClients)
        {
            PrintClientRecordBalancesLine(Client);
            TotalBalances += Client.AccountBalance;
            cout << endl;
        }
    }

    cout << "\n_______________________________________________________________________________________________________\n" << endl;
    cout << "\n\n\n\n\nTotal Balances = " << TotalBalances;
}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";
}

void PrintUserCard(sUser User)
{
    cout << "\nThe following are the User details:\n";
    cout << "-----------------------------------";
    cout << "\nUsername: " << User.Username;
    cout << "\nPassword: " << User.Password;
    cout << "\nPerimssions: " << User.Permissions;
    cout << "\n-----------------------------------\n";
}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient& Client)
{
    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

bool FindUserByUsername(string Username, vector<sUser> vUser, sUser &User)
{
    for (sUser U : vUser)
    {
        if (U.Username == Username)
        {
            User = U;
            return true;
        }
    }
    return false;
}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

sUser ChangeUserRecord(string Username)
{
    sUser User;
    User.Username = Username;

  
    cout << "Enter Password? ";
    getline(cin,User.Password);
    User.Permissions = GivePermissions();

    return User;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
    for (sClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

bool MarkUserForDeleteByUsername(string Username, vector<sUser>& vUser)
{
    for (sUser& U : vUser)
    {
        if (U.Username == Username)
        {
            U.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

vector<sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out); // overwrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                // we only write records that are not marked for delete.
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}

vector<sUser> SaveUsersDataToFile(string FileName, vector<sUser> vUser)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out); // overwrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (sUser U : vUser)
        {
            if (U.MarkForDelete == false)
            {
                // we only write records that are not marked for delete.
                DataLine = ConvertRecordToLineTwo(U);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vUser;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}

void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        // system("cls");
        cout << "Adding New Client:\n\n";
        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);

            // Refresh Clients
            vClients = LoadCleintsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

bool DeleteUserByUsername(string Username, vector<sUser>& vUser)
{
    sUser User;
    char Answer = 'n';
    string Admin = "Admin";

    if (FindUserByUsername(Username, vUser, User))
    {
        if (User.Username == Admin)
        {
            cout <<"\nYou can't Delete This User.";
            return true;
        }

        PrintUserCard(User);

        cout << "\n\nAre you sure you want delete this User? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            MarkUserForDeleteByUsername(Username, vUser);
            SaveUsersDataToFile(UsersFileName, vUser);

            // Refresh Clients
            vUser = LoadUsersDataFromFile(UsersFileName);

            cout << "\n\nUser  Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nUser with Username (" << Username << ") is Not Found!";
        return false;
    }
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\n\nAre you sure you want update this client? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveCleintsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

bool UpdateUserByAccountNumber(string Username, vector<sUser>& vUser)
{
    sUser User;
    char Answer = 'n';

    if (FindUserByUsername(Username, vUser, User))
    {
        PrintUserCard(User);

        cout << "\n\nAre you sure you want update this User? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            for (sUser &U : vUser)
            {
                if (U.Username == Username)
                {
                    U = ChangeUserRecord(Username);
                    break;
                }
            }

            SaveUsersDataToFile(UsersFileName, vUser);

            cout << "\n\nUser Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nUser with Username (" << Username << ") is Not Found!";
        return false;
    }
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}

string ReadUsername()
{
    string Username = "";
    cout << "\nPlease enter Username? ";
    cin >> Username;
    return Username;
}

void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    AddNewClients();
}

void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}

void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}

bool DepositeBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<sClient> vClient)
{
    char Answer = 'n';

    cout << "\n\nAre you ture you want to perform this transactoin?Y/N?";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
    {
        for (sClient& C : vClient)
        {
            if (AccountNumber == C.AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveCleintsDataToFile(ClientsFileName, vClient);
                cout << "\n\nDone Successfully , New Balance is " << C.AccountBalance;
                return true;
            }
        }
        return false;
    }
}

void ShowDepositeScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;
    vector<sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();

    while (!FindClientByAccountNumber(AccountNumber, vClient, Client))
    {
        cout << "\nClinet with [" << AccountNumber << "] does not exist.\n";
         AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter your Deposit amount?";
    cin >> Amount;

    DepositeBalanceToClientByAccountNumber(AccountNumber, Amount, vClient);
}

void ShowWithdrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;
    vector<sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();

    while (!FindClientByAccountNumber(AccountNumber, vClient, Client))
    {
        cout << "\nClinet with [" << AccountNumber << "] does not exist.\n";
         AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter your Withdraw amount?";
    cin >> Amount; 

    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance;
        cout << "Please enter another amount?";
        cin >> Amount;
    }

    DepositeBalanceToClientByAccountNumber(AccountNumber, Amount*-1, vClient);
}

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();
}

void GoBackToTransactionsMenue()
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause>0");
    ShowTransactionsMenue();
}

void  GoBackToManageMenue()
{
    cout << "\n\nPress any key to go back to Manage Menue...";
    system("pause>0");
    ShowMangeUsersScreen();
}

short ReadTransactoinsOption()
{
    cout << "Choose what do you want to do? [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

void PerfromTransactionsOption(enTransactionMenueOption TransactionMenueOption)
{
    switch (TransactionMenueOption)
    {
    case enTransactionMenueOption::eDeposit:
    {
        system("cls");
        ShowDepositeScreen();
        GoBackToTransactionsMenue();
        break;
    }
    case enTransactionMenueOption::eWithdraw:
        system("cls");
        ShowWithdrawScreen();
        GoBackToTransactionsMenue();
        break;

    case enTransactionMenueOption::eShowTotalBalances:
        system("cls");
        ShowTotalBalances();
        GoBackToTransactionsMenue();
        break;

    case enTransactionMenueOption::eShowManinMenue:
        ShowMainMenue();

    }
}

void ShowTransactionsMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\tTransactions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposite.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";
    PerfromTransactionsOption((enTransactionMenueOption)ReadTransactoinsOption());
}

short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 8]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

bool CheckAccessPermission(short UserPermissions, short RequestedPermission)
{
    if (UserPermissions == pAll || (UserPermissions & RequestedPermission) == RequestedPermission)
    {
        return true;
    }
    else
    {
        cout << "\n-----------------------------------\n";
        cout << "Access Denied! \n";
        cout << "You don't have permissions to do this.\n";
        cout << "Please contact your Admin.\n";
        cout << "-----------------------------------\n";
        return false;
    }
}

short ReadMangeUsersScreen()
{
    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

void ShowListUsersScreen()
{
    vector<sUser> vUser = LoadUsersDataFromFile(UsersFileName);

    cout << "\n\t\t\t\t\tClient List (" << vUser.size() << ") Client(s).";
    cout << "\n_______________________________________________________________________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "User Name.";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(40) << "Permition";
    cout << "\n_______________________________________________________________________________________________________\n" << endl;

    if (vUser.size() == 0)
    {
        cout << "\t\t\t\tNo Clients Available In the System!";
    }
    else
    {
        for (sUser User : vUser)
        {
            PrintUserRecordLine(User);
            cout << endl;
        }
    }

    cout << "\n_______________________________________________________________________________________________________\n" << endl;
}

bool UserExistMyUserName(string Username,string Filename)
{
    
        fstream MyFile;

        MyFile.open(UsersFileName, ios::in); // Read Mode

        if (MyFile.is_open())
        {
            string Line;
            sUser User;

            while (getline(MyFile, Line))
            {
                User = CovertLineToRecordTwo(Line);

                if (User.Username == Username)
                {
                    MyFile.close();
                    return true;
                }
            }

            MyFile.close();
        }

        return false;
}

int GivePermissions()
{
    int Permissions = 0;
    char Answer = 'n';

    cout << "\nDo you want to give this user all permissions?Y/N?";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        return enPermissions::pAll;

    cout << "\nDo you want to give access to:\n";

    cout << "\nShow client list?Y/N?";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
        Permissions |= pListClients;

    cout << "\nAdd New Client?Y/N?";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
        Permissions |= pAddNewClient;

    cout << "\nDelete Client?Y/N?";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
        Permissions |= pDeleteClient;

    cout << "\nUpdate Cleint?Y/N?";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
        Permissions |= pUpdateClient;

    cout << "\nFind Client?Y/N?";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
        Permissions |= pFindClient;

    cout << "\nTransactions?Y/N?";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
        Permissions |= pShowTransactionsMenue;

    cout << "\nManagment users?Y/N?";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
        Permissions |= pMangeUsers;
    return Permissions;
}

sUser ReadNewUser()
{
    sUser User;


    char Answer = 'n';

    do
    {
        cout << "\nAdding New User:\n";
        cout << "\nEnter Username? ";
        getline(cin >> ws, User.Username);

        while (UserExistMyUserName(User.Username, UsersFileName))
        {
            cout << "\nUser with [" << User.Username
                << "] already exists, Enter another User Name? ";

            getline(cin >> ws, User.Username);
        }

        cout << "Enter your Password? ";
        cin >> User.Password;

        User.Permissions = GivePermissions();

        cout << "\nDo you want to add more users?Y/N?";
        cin >> Answer;

    } while (toupper(Answer) == 'Y');


   

    return User;
}

void ShowAddNewUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\Add New User Screen";
    cout << "\n-----------------------------------\n";

    sUser User = ReadNewUser();
    
    AddDataLineToFile(UsersFileName, ConvertRecordToLineTwo(User, "#//#"));

    cout << "\nClient Add Successfully.";
}

void ShowDeleteUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete User Screen";
    cout << "\n-----------------------------------\n";

    vector<sUser> vUser = LoadUsersDataFromFile(UsersFileName);
    string Username = ReadUsername();
    DeleteUserByUsername(Username, vUser);
}

void ShowUpdateUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate User Screen";
    cout << "\n-----------------------------------\n";

    vector<sUser> vUser = LoadUsersDataFromFile(UsersFileName);
    string Username = ReadUsername();
    UpdateUserByAccountNumber(Username, vUser);
}

void ShowFindUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind User Screen";
    cout << "\n-----------------------------------\n";

    sUser User;
    vector<sUser> vUser = LoadUsersDataFromFile(UsersFileName);
    string Username = ReadUsername();

    if (FindUserByUsername(Username, vUser, User))
        PrintUserCard(User);
    else
        cout << "\nUser with Username[" << Username << "] is not found!";
}

void PerfromMainMenueOption(enMangeUsers MangeUsers)
{
    switch (MangeUsers)
    {
    case enMangeUsers::eListUsers:
    {
        system("cls");
        ShowListUsersScreen();
        GoBackToManageMenue();
        break;
    }
    case enMangeUsers::eAddNewUser:
    {
        system("cls");
        ShowAddNewUserScreen();
        GoBackToManageMenue();
        break;
    }
    case enMangeUsers::eDeleteUser:
    {
        system("cls");
        ShowDeleteUserScreen();
        GoBackToManageMenue();
        break;
    }
    case enMangeUsers::eUpdateUser:
    {
        system("cls");
        ShowUpdateUserScreen();
        GoBackToManageMenue();
        break;
    }
    case enMangeUsers::eFindUser:
    {
        system("cls");
        ShowFindUserScreen();
        GoBackToMainMenue();
        break;
    }
    case enMangeUsers::eMainMenue:
    {
        system("cls");
        ShowMainMenue();
        break;
    }
    }
}

void ShowMangeUsersScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\tMange Users Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User .\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menue.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMangeUsers)ReadMangeUsersScreen());
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {
        system("cls");
       
        if (CheckAccessPermission(CurrentUser.Permissions, pListClients))
        {
            ShowAllClientsScreen();
        }
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eAddNewClient:
        system("cls");
       
        if (CheckAccessPermission(CurrentUser.Permissions,pAddNewClient ))
        {
            ShowAddNewClientsScreen();
        }
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eDeleteClient:
        system("cls");
       
        if (CheckAccessPermission(CurrentUser.Permissions, pDeleteClient))
        {
            ShowDeleteClientScreen();
        }
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eUpdateClient:
        system("cls");
       
        if (CheckAccessPermission(CurrentUser.Permissions, pUpdateClient))
        {
            ShowUpdateClientScreen();
        }
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eFindClient:
        system("cls");
        
        if (CheckAccessPermission(CurrentUser.Permissions, pFindClient))
        {
            ShowFindClientScreen();
        }
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eShowTransactionsMenue:
        system("cls");
       
        if (CheckAccessPermission(CurrentUser.Permissions, pShowTransactionsMenue))
        {
            ShowTransactionsMenue();
        }
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eMangeUsers:
        system("cls");
        
        if (CheckAccessPermission(CurrentUser.Permissions, pMangeUsers))
        {
            ShowMangeUsersScreen();
        }
        break;

    case enMainMenueOptions::eLogout:
            system("cls");
            Login();
            break;
    }
}

void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Mange Users.\n";
    cout << "\t[8] Log Out\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

bool CheckUserNameAndPassword(string Username , string Password , string UsersFileName)
{
    fstream MyFile;

    MyFile.open(UsersFileName, ios::in); // Read Mode

    if (MyFile.is_open())
    {
        string Line;
        sUser User;

        while (getline(MyFile, Line))
        {
            User = CovertLineToRecordTwo(Line);
           
            if (User.Password == Password && User.Username == Username)
            {
                MyFile.close();
                return true;
            }
        }

        MyFile.close();
    }

    return false;
}

void Login()
{
    cout << "\n-----------------------------------\n";
    cout << "\tLogin Screen ";
    cout << "\n-----------------------------------\n";

    sUser User;
    vector<sUser> vUsers = LoadUsersDataFromFile(UsersFileName);

    cout << "\nEnter Username? ";
    getline(cin >> ws, User.Username);

    cout << "Enter your Password? ";
    cin >> User.Password;


    while (!CheckUserNameAndPassword(User.Username, User.Password, UsersFileName))
    {
        cout << "\nInvail Username and Password try again\n\n";

        cout << "Enter Username? ";
        getline(cin >> ws, User.Username);

        cout << "\nEnter your Password? ";
        cin >> User.Password;
    }

    for (sUser U : vUsers)
    {
        if (U.Username == User.Username && U.Password == User.Password)
        {
            CurrentUser = U;
            break;
        }
    }

    ShowMainMenue();

}


int main()
{
    Login();
    system("pause>0");
    return 0;
}