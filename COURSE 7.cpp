#include <string>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cctype>
#include <vector>
#include <fstream>
using namespace std;

enum en_main_choices { list_clients = 1, add_new_client = 2, delete_client = 3, update_client = 4, find_client = 5, transactions = 6, exitt = 7 };
enum en_trans_choices { diposit = 1, withdraw = 2, totalbalance = 3, back = 4 };
const string file_name = "problem_47.txt";
struct st_client_info
{
    string account_number;
    string pin;
    string full_name;
    string phone_number;
    double account_balance;
    bool mak_to_delet = false;
};

void print_transaction_menue();
void print_main_screen();

vector <string> split_string(string s1, string delim = " ")
{
    vector<string> v_string;

    short pos = 0;
    string s_word;

    while ((pos = s1.find(delim)) != std::string::npos)
    {
        s_word = s1.substr(0, pos);
        if (s_word != "")
        {

            v_string.push_back(s_word);

        }
        s1.erase(0, pos + delim.length());
    }
    if (s1 != "")
    {

        v_string.push_back(s1);
    }
    return v_string;
}

st_client_info convert_string_into_struct(string line, string Seperator = "#//#")
{
    vector<string> v_client_info = split_string(line, Seperator);
    st_client_info client;

    client.account_number = v_client_info[0];
    client.pin = v_client_info[1];
    client.full_name = v_client_info[2];
    client.phone_number = v_client_info[3];
    client.account_balance = stod(v_client_info[4]);
    return client;
}

vector <st_client_info> load_data_from_file_to_vector(string file_name)
{
    fstream my_file;
    vector <st_client_info> v_file_content;
    my_file.open(file_name, ios::in);

    if (my_file.is_open())
    {
        string line;
        st_client_info client_info;
        while (getline(my_file, line))
        {
            client_info = convert_string_into_struct(line);
            v_file_content.push_back(client_info);
        }
        my_file.close();
    }
    return v_file_content;
}

void print_client_record_tablo(st_client_info client)
{
    cout << "| " << setw(15) << left << client.account_number;
    cout << "| " << setw(10) << left << client.pin;
    cout << "| " << setw(40) << left << client.full_name;
    cout << "| " << setw(12) << left << client.phone_number;
    cout << "| " << setw(12) << left << client.account_balance;
}

void print_all_clients_data__()
{
    vector <st_client_info> v_clients = load_data_from_file_to_vector(file_name);
    cout << "\n\t\t\t\t\tClient List (" << v_clients.size() << ")clients(s).";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (st_client_info Client : v_clients)
    {
        print_client_record_tablo(Client);
        cout << endl;
    }
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

bool client_exists_by_account_number(string account_number, string file_name)
{

    vector <st_client_info> vClients;

    fstream MyFile;
    MyFile.open(file_name, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        st_client_info Client;

        while (getline(MyFile, Line))
        {

            Client = convert_string_into_struct(Line);
            if (Client.account_number == account_number)
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

st_client_info read_new_client()
{

    st_client_info client;
    cout << "Enter Account Number? ";
    getline(cin >> ws, client.account_number);
    while (client_exists_by_account_number(client.account_number, file_name))
    {
        cout << "\nClient with [" << client.account_number << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, client.account_number);
    }
    cout << "Enter PinCode? ";
    getline(cin, client.pin);
    cout << "Enter Name? ";
    getline(cin, client.full_name);
    cout << "Enter Phone? ";
    getline(cin, client.phone_number);
    cout << "Enter AccountBalance? ";
    cin >> client.account_balance;
    return client;
}

string convert_struct_into_string(st_client_info st_client, string sepretur = "#//#")
{
    string client;
    client += st_client.account_number + sepretur;
    client += st_client.pin + sepretur;
    client += st_client.full_name + sepretur;
    client += st_client.phone_number + sepretur;
    client += to_string(st_client.account_balance);
    return client;
}

void write_record_to_file(string file_name, string data)
{
    fstream problem_47;

    problem_47.open(file_name, ios::out | ios::app);

    if (problem_47.is_open())
    {
        problem_47 << data << endl;;

        problem_47.close();
    }



}

void add_client()
{
    st_client_info st_client_info = read_new_client();
    write_record_to_file(file_name, convert_struct_into_string(st_client_info));

}

void add_clients__addscreen()
{
    char conformation = 'Y';
    while (toupper(conformation) == 'Y')
    {

        cout << " -----------------------------------------------\n";
        cout << "            adding new client                   \n";
        cout << " -----------------------------------------------\n";
        cout << "Adding New Client:\n\n";
        add_client();
        cout << "\nClient Added Successfully, do you want to ad more clients ? Y / N ? ";
        cin >> conformation;
    }

}

string read_account_number()
{
    string search;
    cout << "enter account number you want to search : ";
    cin >> search;
    return search;
}

void load_data_from_vector_into_file(string file_name, vector <st_client_info> v_client)
{
    fstream my_file;

    my_file.open(file_name, ios::out);
    if (my_file.is_open())
    {
        for (st_client_info& st_client : v_client)
        {
            my_file << convert_struct_into_string(st_client) << endl;
        }
    }

    my_file.close();
}

bool search_for_client(string search, st_client_info& client)
{
    vector <st_client_info> file_content = load_data_from_file_to_vector(file_name);

    for (int i = 0; i < file_content.size(); i++)
    {
        if (search == file_content[i].account_number)
        {
            client = file_content[i];
            return true;
        }
    }
    return false;


}

void delete_record_from_file(string file_name, string record)
{
    vector < st_client_info > v_client;
    v_client = load_data_from_file_to_vector(file_name);

    for (int i = 0; i < v_client.size(); i++)
    {
        if (v_client[i].account_number == record)
        {
            v_client.erase(v_client.begin() + i);
            break;
        }
    }
    load_data_from_vector_into_file(file_name, v_client);
}

void print_client_info(st_client_info st_client_info)
{
    cout << "\nThe following are the client details:\n";
    cout << "\nAccout Number: " << st_client_info.account_number << endl;
    cout << "\nPin Code : " << st_client_info.pin << endl;
    cout << "\nName : " << st_client_info.full_name << endl;
    cout << "\nPhone : " << st_client_info.phone_number << endl;
    cout << "\nAccount Balance: " << st_client_info.account_balance << endl;
}

void delete_clients_from_file__delete_screen()
{
    string account_number = read_account_number();
    st_client_info st_client;
    cout << "----------------------------------------\n";
    cout << "             delete client              \n";
    cout << "----------------------------------------\n";
    char con = 'y';
    if (search_for_client(account_number, st_client))
    {
        print_client_info(st_client);
        cout << "\ndo you want to delete this account ? (y/n)\n";
        cin >> con;
        if (tolower(con) == 'y')
        {
            delete_record_from_file(file_name, account_number);
            cout << "\nthe user has been deleted\n";
        }
    }
    else
    {
        cout << "\nThe user you loking for(" << account_number << ")is not avilable\n";
    }
}

bool find_client_by_account_number(string account_number, vector  <st_client_info> v_clients, st_client_info& client)
{
    for (st_client_info C : v_clients)
    {
        if (C.account_number == account_number)
        {
            client = C;
            return true;
        }
    }
    return false;
}

st_client_info change_client_record(string accountNumber)
{
    st_client_info Client;
    Client.account_number = accountNumber;
    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.pin);
    cout << "Enter Name? ";
    getline(cin, Client.full_name);
    cout << "Enter Phone? ";
    getline(cin, Client.phone_number);
    cout << "Enter AccountBalance? ";
    cin >> Client.account_balance;
    return Client;
}

vector <st_client_info> save_cleints_data_to_file(string FileName, vector<st_client_info> v_clients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    string DataLine;
    if (MyFile.is_open())
    {
        for (st_client_info C : v_clients)
        {
            if (C.mak_to_delet == false)
            {
                DataLine = convert_struct_into_string(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return v_clients;
}

bool update_client_by_account_number__updatescreen()

{
    cout << "----------------------------------------\n";
    cout << "             update client              \n";
    cout << "----------------------------------------\n";
    string accountNumber = read_account_number();
    vector <st_client_info> v_clients = load_data_from_file_to_vector(file_name);
    st_client_info client;
    char Answer = 'n';


    if (find_client_by_account_number(accountNumber, v_clients,
        client))
    {
        print_client_info(client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (st_client_info& C : v_clients)
            {
                if (C.account_number == accountNumber)
                {
                    C = change_client_record(accountNumber);
                    break;
                }
            }
            save_cleints_data_to_file(file_name, v_clients);
            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << accountNumber
            << ") is Not Found!";
        return false;
    }

}

void search_client__findscreen()
{
    cout << "----------------------------------------\n";
    cout << "             find client              \n";
    cout << "----------------------------------------\n";
    string account_number = read_account_number();
    st_client_info st_client;

    if (search_for_client(account_number, st_client))
    {
        print_client_info(st_client);
    }
    else
    {
        cout << "\nThe user you loking for(" << account_number << ")is not avilable\n";
    }


}

void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}

short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 7]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

void go_back_to_main_menu()
{
    cout << "\n\nPress any key to go back to main menu...";
    system("pause>0");
    system("cls");
    print_main_screen();
}

void go_back_to_trans_menu()
{
    cout << "\n\nPress any key to go back to transaction menu...";
    system("pause>0");
    system("cls");
    print_transaction_menue();
}

double calculate_all_total()
{

    vector <st_client_info> v_clients = load_data_from_file_to_vector(file_name);
    st_client_info client;
    double total = 0;



    for (st_client_info& C : v_clients)
    {

        total += C.account_balance;

    }
    return total;
}

void deposit__()
{
    cout << "----------------------------------------\n";
    cout << "             deposit screen             \n";
    cout << "----------------------------------------\n";
    string accountNumber = read_account_number();
    vector <st_client_info> v_clients = load_data_from_file_to_vector(file_name);
    st_client_info client;
    double amount = 0;

    if (find_client_by_account_number(accountNumber, v_clients,
        client))
    {
        cout << " \n account balance is : " << client.account_balance;
        cout << "\n\nhow much you want to deposit ? ";
        cin >> amount;

        for (st_client_info& C : v_clients)
        {
            if (C.account_number == accountNumber)
            {
                C.account_balance += amount;
                break;
            }
        }
        save_cleints_data_to_file(file_name, v_clients);
        cout << "\n\nmoney has deposit Successfully.";
    }
    else
    {
        cout << "\nClient with Account Number (" << accountNumber
            << ") is Not Found!";

    }

}

void withdraw__()
{
    cout << "----------------------------------------\n";
    cout << "             withdraw screen            \n";
    cout << "----------------------------------------\n";

    string accountNumber = read_account_number();
    vector<st_client_info> v_clients = load_data_from_file_to_vector(file_name);
    st_client_info client;
    double amount = 0;

    if (find_client_by_account_number(accountNumber, v_clients, client))
    {
        cout << "\naccount balance is : " << client.account_balance;
        cout << "\n\nhow much you want to withdraw ? ";
        cin >> amount;

        while (amount > client.account_balance)
        {
            cout << "\nAmount exceeds balance.";
            cout << "\nThe maximum amount you can withdraw is : " << client.account_balance;
            cout << "\nPlease enter another amount: ";
            cin >> amount;
        }

        for (st_client_info& C : v_clients)
        {
            if (C.account_number == accountNumber)
            {
                C.account_balance -= amount;
                break;
            }
        }

        save_cleints_data_to_file(file_name, v_clients);
        cout << "\n\nMoney has been withdrawn successfully.";
    }
    else
    {
        cout << "\nClient with Account Number (" << accountNumber << ") is Not Found!";
    }
}

void show_total_balance__()
{

    print_all_clients_data__();
    cout << "\t\t\t\t\ttotal balance is =" << calculate_all_total();
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

void trans_menue_option(en_trans_choices trans_menu)
{
    switch (trans_menu)
    {
    case en_trans_choices::diposit:
    {
        system("cls");
        deposit__();
        go_back_to_trans_menu();
        break;
    }
    case en_trans_choices::withdraw:
    {
        system("cls");
        withdraw__();
        go_back_to_trans_menu();
        break;
    }
    case en_trans_choices::totalbalance:
    {
        system("cls");
        show_total_balance__();
        go_back_to_trans_menu();
        break;
    }
    case en_trans_choices::back:
    {
        system("cls");
        print_main_screen();
        break;
    }

    }

}

short read_trans_menu_option()
{
    cout << "Choose what do you want to do? [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

void print_transaction_menue()
{
    cout << "------------------------------------------------------\n";
    cout << "               transactions menu                      \n";
    cout << "------------------------------------------------------\n";
    cout << "      [1] diposit                                     \n";
    cout << "      [2] withdraw                                    \n";
    cout << "      [3] total balance                               \n";
    cout << "      [4] back to main menu                           \n";
    cout << "------------------------------------------------------\n";
    trans_menue_option(en_trans_choices(read_trans_menu_option()));
}

void mein_menue_option(en_main_choices main_menu)
{
    switch (main_menu)
    {
    case en_main_choices::list_clients:
    {
        system("cls");
        print_all_clients_data__();
        go_back_to_main_menu();
        break;
    }
    case en_main_choices::add_new_client:
    {
        system("cls");
        add_clients__addscreen();
        go_back_to_main_menu();
        break;
    }
    case en_main_choices::delete_client:
    {
        system("cls");
        delete_clients_from_file__delete_screen();
        go_back_to_main_menu();
        break;
    }
    case en_main_choices::update_client:
    {
        system("cls");
        update_client_by_account_number__updatescreen();
        go_back_to_main_menu();
        break;
    }
    case en_main_choices::find_client:
    {
        system("cls");
        search_client__findscreen();
        go_back_to_main_menu();
        break;
    }
    case en_main_choices::transactions:
    {
        system("cls");
        print_transaction_menue();
        go_back_to_main_menu();
        break;
    }
    case en_main_choices::exitt:
    {
        system("cls");
        ShowEndScreen();
        break;
    }
    }

}

void print_main_screen()
{

    cout << "------------------------------------------------------\n";
    cout << "                  MAIN SCREEN                         \n";
    cout << "------------------------------------------------------\n";
    cout << "      [1] show client list                            \n";
    cout << "      [2] add new client                              \n";
    cout << "      [3] delet client                                \n";
    cout << "      [4] upddate client info                         \n";
    cout << "      [5] find client info                            \n";
    cout << "      [6] transaction                                 \n";
    cout << "      [7] exit                                        \n";
    cout << "------------------------------------------------------\n";
    mein_menue_option(en_main_choices(ReadMainMenueOption()));
}



int main()
{
    print_main_screen();

    system("pause>0");
    return 0;
}
