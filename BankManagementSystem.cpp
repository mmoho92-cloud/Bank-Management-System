#include <string>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cctype>
#include <vector>
#include <fstream>
using namespace std;

string current_user;
enum en_main_choices { list_clients = 1, add_new_client = 2, delete_client = 3, update_client = 4, find_client = 5, transactions = 6, mange_users = 7, logout = 8 };
enum en_trans_choices { diposit = 1, withdraw = 2, totalbalance = 3, back = 4 };
enum en_permissions
{
    p_all = -1,
    p_list_clients = 1,
    p_add_new_client = 2,
    p_delete_client = 4,
    p_update_client = 8,
    p_find_client = 16,
    p_transactions = 32,
    p_manage_users = 64
};
enum en_mange_users_choices { list_users = 1, add_new_user = 2, delete_user = 3, update_user = 4, find_user = 5, main_menue = 6 };
const string clients_file = "clients.txt";
const string users_file = "users.txt";
struct st_client_info
{
    string account_number;
    string pin;
    string full_name;
    string phone_number;
    double account_balance;
    bool mak_to_delet = false;
};
struct st_user_info
{
    string user_name;
    string password;
    int permissions;
    bool mak_to_delet = false;
};

void login_screen();

void print_transaction_menue();

void print_main_screen();

void print_user_mange_screen();

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

st_client_info convert_string_into_struct_clients(string line, string Seperator = "#//#")
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

st_user_info convert_string_into_struct_users(string line, string Seperator = "#//#")
{
    vector<string> v_user_info = split_string(line, Seperator);
    st_user_info user;

    user.user_name = v_user_info[0];
    user.password = v_user_info[1];
    user.permissions = stoi(v_user_info[2]);

    return user;
}

vector <st_client_info> load_data_from_file_to_vector_clients(string file_name)
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
            client_info = convert_string_into_struct_clients(line);
            v_file_content.push_back(client_info);
        }
        my_file.close();
    }
    return v_file_content;
}

vector <st_user_info> load_data_from_file_to_vector_users(string file_name)
{
    fstream my_file;
    vector <st_user_info> v_file_content;
    my_file.open(file_name, ios::in);

    if (my_file.is_open())
    {
        string line;
        st_user_info user_info;
        while (getline(my_file, line))
        {
            user_info = convert_string_into_struct_users(line);
            v_file_content.push_back(user_info);
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
    vector <st_client_info> v_clients = load_data_from_file_to_vector_clients(clients_file);
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

void print_user_record_tablo(st_user_info user)
{
    cout << "| " << setw(15) << left << user.user_name;
    cout << "| " << setw(10) << left << user.password;
    cout << "| " << setw(40) << left << user.permissions;

}

void print_all_user_data__()
{
    vector <st_user_info> v_users = load_data_from_file_to_vector_users(users_file);
    cout << "\n\t\t\t\t\tuser List (" << v_users.size() << ")user(s).";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "user name";
    cout << "| " << left << setw(10) << "password";
    cout << "| " << left << setw(40) << "permissions";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (st_user_info user : v_users)
    {
        print_user_record_tablo(user);
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

            Client = convert_string_into_struct_clients(Line);
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

bool user_exists_by_user_name(string account_number, string file_name)
{

    vector <st_user_info> users;

    fstream MyFile;
    MyFile.open(file_name, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        st_user_info user;

        while (getline(MyFile, Line))
        {

            user = convert_string_into_struct_users(Line);
            if (user.user_name == account_number)
            {
                MyFile.close();
                return true;
            }


            users.push_back(user);
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
    while (client_exists_by_account_number(client.account_number, clients_file))
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

int get_permissions()
{
    int permissions = 0;
    char answer;

    cout << "\nShow Client List? y/n? ";
    cin >> answer;
    if (tolower(answer) == 'y')
        permissions |= 1;

    cout << "\nAdd New Client? y/n? ";
    cin >> answer;
    if (tolower(answer) == 'y')
        permissions |= 2;

    cout << "\nDelete Client? y/n? ";
    cin >> answer;
    if (tolower(answer) == 'y')
        permissions |= 4;

    cout << "\nUpdate Client? y/n? ";
    cin >> answer;
    if (tolower(answer) == 'y')
        permissions |= 8;

    cout << "\nFind Client? y/n? ";
    cin >> answer;
    if (tolower(answer) == 'y')
        permissions |= 16;

    cout << "\nTransactions? y/n? ";
    cin >> answer;
    if (tolower(answer) == 'y')
        permissions |= 32;

    cout << "\nManage Users? y/n? ";
    cin >> answer;
    if (tolower(answer) == 'y')
        permissions |= 64;

    return permissions;
}

st_user_info read_new_user()
{

    st_user_info user;
    char con = ' ';
    cout << "Enter username? ";
    getline(cin >> ws, user.user_name);
    while (user_exists_by_user_name(user.user_name, users_file))
    {
        cout << "\nuser with [" << user.user_name << "] already exists, Enter another username? ";
        getline(cin >> ws, user.user_name);
    }
    cout << "Enter Password? ";
    getline(cin, user.password);
    cout << "do you want give this user full permisons? (y/n)";
    cin >> con;
    if (tolower(con) != 'y')
    {
        user.permissions = get_permissions();
    }
    else
    {
        user.permissions = -1;
    }
    return user;
}

string convert_struct_into_string_clints(st_client_info st_client, string sepretur = "#//#")
{
    string client;
    client += st_client.account_number + sepretur;
    client += st_client.pin + sepretur;
    client += st_client.full_name + sepretur;
    client += st_client.phone_number + sepretur;
    client += to_string(st_client.account_balance);
    return client;
}

string convert_struct_into_string_users(st_user_info st_user, string sepretur = "#//#")
{
    string user;
    user += st_user.user_name + sepretur;
    user += st_user.password + sepretur;
    user += to_string(st_user.permissions);

    return user;
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
    write_record_to_file(clients_file, convert_struct_into_string_clints(st_client_info));

}

void add_user()
{
    st_user_info st_user_info = read_new_user();
    write_record_to_file(users_file, convert_struct_into_string_users(st_user_info));

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

void add_user__addscreen()
{
    char conformation = 'Y';
    while (toupper(conformation) == 'Y')
    {

        cout << " -----------------------------------------------\n";
        cout << "            adding new user                   \n";
        cout << " -----------------------------------------------\n";
        cout << "Adding New Users:\n\n";
        add_user();
        cout << "\nuser Added Successfully, do you want to ad more users ? Y / N ? ";
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

string read_user_name()
{
    string search;
    cout << "enter username you want to search : ";
    cin >> search;
    return search;
}

void load_data_from_vector_into_file_clients(string file_name, vector <st_client_info> v_client)
{
    fstream my_file;

    my_file.open(file_name, ios::out);
    if (my_file.is_open())
    {
        for (st_client_info& st_client : v_client)
        {
            my_file << convert_struct_into_string_clints(st_client) << endl;
        }
    }

    my_file.close();
}

void load_data_from_vector_into_file_users(string file_name, vector <st_user_info> v_user)
{
    fstream my_file;

    my_file.open(file_name, ios::out);
    if (my_file.is_open())
    {
        for (st_user_info& st_user : v_user)
        {
            my_file << convert_struct_into_string_users(st_user) << endl;
        }
    }

    my_file.close();
}

bool search_for_client(string search, st_client_info& client)
{
    vector <st_client_info> file_content = load_data_from_file_to_vector_clients(clients_file);

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

bool search_for_user(string search, st_user_info& user)
{
    vector <st_user_info> file_content = load_data_from_file_to_vector_users(users_file);

    for (int i = 0; i < file_content.size(); i++)
    {
        if (search == file_content[i].user_name)
        {
            user = file_content[i];
            return true;
        }
    }
    return false;


}

void delete_record_from_file_clients(string file_name, string record)
{
    vector < st_client_info > v_client;
    v_client = load_data_from_file_to_vector_clients(file_name);

    for (int i = 0; i < v_client.size(); i++)
    {
        if (v_client[i].account_number == record)
        {
            v_client.erase(v_client.begin() + i);
            break;
        }
    }
    load_data_from_vector_into_file_clients(file_name, v_client);
}

void delete_record_from_file_users(string file_name, string record)
{
    vector < st_user_info > v_user;
    v_user = load_data_from_file_to_vector_users(file_name);

    for (int i = 0; i < v_user.size(); i++)
    {
        if (v_user[i].user_name == record)
        {
            v_user.erase(v_user.begin() + i);
            break;
        }
    }
    load_data_from_vector_into_file_users(file_name, v_user);
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

void print_user_info(st_user_info st_user_info)
{
    cout << "\nThe following are the user details:\n";
    cout << "\nuser name: " << st_user_info.user_name << endl;
    cout << "\npassword : " << st_user_info.password << endl;
    cout << "\npermissions : " << st_user_info.permissions << endl;

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
            delete_record_from_file_clients(clients_file, account_number);
            cout << "\nthe user has been deleted\n";
        }
    }
    else
    {
        cout << "\nThe user you loking for(" << account_number << ")is not avilable\n";
    }
}

void delete_user_from_file__delete_screen()
{
    string user_name = read_user_name();
    st_user_info st_user;
    cout << "----------------------------------------\n";
    cout << "             delete user              \n";
    cout << "----------------------------------------\n";
    char con = 'y';
    if (search_for_user(user_name, st_user))
    {
        print_user_info(st_user);
        cout << "\ndo you want to delete this account ? (y/n)\n";
        cin >> con;
        if (tolower(con) == 'y')
        {
            delete_record_from_file_users(users_file, user_name);
            cout << "\nthe user has been deleted\n";
        }
    }
    else
    {
        cout << "\nThe user you loking for(" << user_name << ")is not avilable\n";
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

bool find_user_by_user_name(string user_name, vector  <st_user_info> v_users, st_user_info& user)
{
    for (st_user_info C : v_users)
    {
        if (C.user_name == user_name)
        {
            user = C;
            return true;
        }
    }
    return false;
}

bool find_user_by_user_name_and_password(string user_name, string password, vector  <st_user_info> v_users)
{
    for (st_user_info C : v_users)
    {
        if (C.user_name == user_name && C.password == password)
        {
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

st_user_info change_user_record(string user_name)
{
    st_user_info user;
    user.user_name = user_name;
    cout << "\n\nEnter password? ";
    getline(cin >> ws, user.password);
    cout << "permissions ? ";
    user.permissions = get_permissions();

    return user;
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
                DataLine = convert_struct_into_string_clints(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return v_clients;
}

vector <st_user_info> save_user_data_to_file(string FileName, vector<st_user_info> v_users)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    string DataLine;
    if (MyFile.is_open())
    {
        for (st_user_info C : v_users)
        {
            if (C.mak_to_delet == false)
            {
                DataLine = convert_struct_into_string_users(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return v_users;
}

bool update_client_by_account_number__updatescreen()

{
    cout << "----------------------------------------\n";
    cout << "             update client              \n";
    cout << "----------------------------------------\n";
    string accountNumber = read_account_number();
    vector <st_client_info> v_clients = load_data_from_file_to_vector_clients(clients_file);
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
            save_cleints_data_to_file(clients_file, v_clients);
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

bool update_user_by_user_name__updatescreen()

{
    cout << "----------------------------------------\n";
    cout << "             update user              \n";
    cout << "----------------------------------------\n";
    string user_name = read_user_name();
    vector <st_user_info> v_users = load_data_from_file_to_vector_users(users_file);
    st_user_info user;
    char answer = 'n';


    if (find_user_by_user_name(user_name, v_users,
        user))
    {
        print_user_info(user);
        cout << "\n\nAre you sure you want update this user? y/n ? ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            for (st_user_info& C : v_users)
            {
                if (C.user_name == user_name)
                {
                    C = change_user_record(user_name);
                    break;
                }
            }
            save_user_data_to_file(users_file, v_users);
            cout << "\n\user Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nuser with username (" << user_name
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

void search_user__findscreen()
{
    cout << "----------------------------------------\n";
    cout << "             find user              \n";
    cout << "----------------------------------------\n";
    string user_name = read_user_name();
    st_user_info st_user;

    if (search_for_user(user_name, st_user))
    {
        print_user_info(st_user);
    }
    else
    {
        cout << "\nThe user you loking for(" << user_name << ")is not avilable\n";
    }


}

void end_screen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}

void logout_scren__logoutscreen()
{

    char con;

    cout << " -----------------------------------------------\n";
    cout << "                     LOGOUT                     \n";
    cout << " -----------------------------------------------\n";
    cout << "\ndo you want to login with another username ? (y/n)\n";
    cin >> con;
    if (tolower(con) == 'y')
    {
        login_screen();
    }
    else
    {
        end_screen();
    }


}

void print_login_header()
{
    cout << " -----------------------------------------------\n";
    cout << "                     LOGIN                      \n";
    cout << " -----------------------------------------------\n";
}

short read_main_menue_option()
{
    cout << "Select an option [1 - 8]: ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

short read_user_mange_menue_option()
{
    cout << "Select an option [1 - 6]: ";
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

void go_back_to_users_mange_menu()
{
    cout << "\n\nPress any key to go back to mange menu...";
    system("pause>0");
    system("cls");
    print_user_mange_screen();
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

    vector <st_client_info> v_clients = load_data_from_file_to_vector_clients(clients_file);
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
    vector <st_client_info> v_clients = load_data_from_file_to_vector_clients(clients_file);
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
        save_cleints_data_to_file(clients_file, v_clients);
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
    vector<st_client_info> v_clients = load_data_from_file_to_vector_clients(clients_file);
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

        save_cleints_data_to_file(clients_file, v_clients);
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
    cout << "Select an option [1 - 4]: ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

void print_transaction_menue()
{
    system("cls");

    cout << "======================================================\n";
    cout << "                  TRANSACTIONS                        \n";
    cout << "======================================================\n";
    cout << "                     Main Menu                        \n";
    cout << "------------------------------------------------------\n";
    cout << "  [1] Deposit                                        \n";
    cout << "  [2] Withdraw                                       \n";
    cout << "  [3] Total Balances                                 \n";
    cout << "  [4] Back to Main Menu                              \n";
    cout << "======================================================\n";

    trans_menue_option(
        en_trans_choices(read_trans_menu_option())
    );
}
void show_access_denied_message()
{
    cout << "\n------------------------------------\n";
    cout << "Access Denied,\n";
    cout << "You don't have permission to do this.\n";
    cout << "Please contact your admin.\n";
    cout << "------------------------------------\n";
}

st_user_info get_user_by_username(string user_name)
{
    vector <st_user_info> file_content = load_data_from_file_to_vector_users(users_file);
    st_user_info user1;

    for (int i = 0; i < file_content.size(); i++)
    {
        if (user_name == file_content[i].user_name)
        {
            user1 = file_content[i];

        }
    }
    return user1;


}

void mein_menue_option(en_main_choices main_menu, st_user_info user)
{

    switch (main_menu)
    {
    case en_main_choices::list_clients:
    {
        if (user.permissions == en_permissions::p_all || (user.permissions & en_permissions::p_list_clients))
        {
            system("cls");
            print_all_clients_data__();
            go_back_to_main_menu();
        }
        else
        {
            show_access_denied_message();
            go_back_to_main_menu();
        }

        break;
    }
    case en_main_choices::add_new_client:
    {
        if (user.permissions == en_permissions::p_all || (user.permissions & en_permissions::p_add_new_client))
        {
            system("cls");
            add_clients__addscreen();
            go_back_to_main_menu();
        }
        else
        {
            show_access_denied_message();
            go_back_to_main_menu();
        }

        break;
    }
    case en_main_choices::delete_client:
    {
        if (user.permissions == en_permissions::p_all || (user.permissions & en_permissions::p_delete_client))
        {
            system("cls");
            delete_clients_from_file__delete_screen();
            go_back_to_main_menu();
        }
        else
        {
            show_access_denied_message();
            go_back_to_main_menu();
        }

        break;
    }
    case en_main_choices::update_client:
    {
        if (user.permissions == en_permissions::p_all || (user.permissions & en_permissions::p_update_client))
        {
            system("cls");
            update_client_by_account_number__updatescreen();
            go_back_to_main_menu();
        }
        else
        {
            show_access_denied_message();
            go_back_to_main_menu();
        }
        break;
    }
    case en_main_choices::find_client:
    {
        if (user.permissions == en_permissions::p_all || (user.permissions & en_permissions::p_find_client))
        {
            system("cls");
            search_client__findscreen();
            go_back_to_main_menu();
        }
        else
        {
            show_access_denied_message();
            go_back_to_main_menu();
        }
        break;
    }
    case en_main_choices::transactions:
    {
        if (user.permissions == en_permissions::p_all || (user.permissions & en_permissions::p_transactions))
        {
            system("cls");
            print_transaction_menue();
            go_back_to_main_menu();
        }
        else
        {
            show_access_denied_message();
            go_back_to_main_menu();
        }
        break;
    }
    case en_main_choices::mange_users:
    {
        if (user.permissions == en_permissions::p_all || (user.permissions & en_permissions::p_manage_users))
        {
            system("cls");
            print_user_mange_screen();
        }
        else
        {
            show_access_denied_message();
            go_back_to_main_menu();
        }
        break;
    }
    case en_main_choices::logout:
    {

        system("cls");
        logout_scren__logoutscreen();


        break;
    }
    }

}

void users_mange_menue_option(en_mange_users_choices mange_users_menu)
{
    switch (mange_users_menu)
    {
    case en_mange_users_choices::list_users:
    {
        system("cls");
        print_all_user_data__();
        go_back_to_users_mange_menu();
        break;
    }
    case en_mange_users_choices::add_new_user:
    {
        system("cls");
        add_user__addscreen();
        go_back_to_users_mange_menu();
        break;
    }
    case en_mange_users_choices::delete_user:
    {
        system("cls");
        delete_user_from_file__delete_screen();
        go_back_to_users_mange_menu();
        break;
    }
    case en_mange_users_choices::update_user:
    {
        system("cls");
        update_user_by_user_name__updatescreen();
        go_back_to_users_mange_menu();
        break;
    }
    case en_mange_users_choices::find_user:
    {
        system("cls");
        search_user__findscreen();
        go_back_to_users_mange_menu();
        break;
    }
    case en_mange_users_choices::main_menue:
    {
        system("cls");
        go_back_to_main_menu();
        break;
    }
    }

}

void print_main_screen()
{
    system("cls");

    cout << "======================================================\n";
    cout << "               BANK MANAGEMENT SYSTEM                 \n";
    cout << "======================================================\n";
    cout << "                      Main Menu                       \n";
    cout << "------------------------------------------------------\n";
    cout << "  [1] Show Client List                               \n";
    cout << "  [2] Add New Client                                 \n";
    cout << "  [3] Delete Client                                  \n";
    cout << "  [4] Update Client Information                      \n";
    cout << "  [5] Find Client                                    \n";
    cout << "  [6] Transactions                                   \n";
    cout << "  [7] Manage Users                                   \n";
    cout << "  [8] Logout                                         \n";
    cout << "======================================================\n";

    mein_menue_option(en_main_choices(read_main_menue_option()), get_user_by_username(current_user));
}
void print_user_mange_screen()
{
    system("cls");

    cout << "======================================================\n";
    cout << "                 USER MANAGEMENT                      \n";
    cout << "======================================================\n";
    cout << "                     Main Menu                        \n";
    cout << "------------------------------------------------------\n";
    cout << "  [1] Show User List                                 \n";
    cout << "  [2] Add New User                                   \n";
    cout << "  [3] Delete User                                    \n";
    cout << "  [4] Update User Information                        \n";
    cout << "  [5] Find User                                      \n";
    cout << "  [6] Back to Main Menu                              \n";
    cout << "======================================================\n";

    users_mange_menue_option(
        en_mange_users_choices(read_user_mange_menue_option())
    );
}
void login_screen()
{
    string user_name;
    string password;
    vector <st_user_info> v_user = load_data_from_file_to_vector_users(users_file);
    system("cls");
    print_login_header();
    cout << endl;
    cout << "plaese enter username:\n\n";
    cin >> user_name;
    cout << "\nplease enter the password ";
    cin >> password;
    while (!find_user_by_user_name_and_password(user_name, password, v_user))
    {
        cout << "you have entred wrong username or password . try again. \n";
        system("pause>0");
        system("cls");
        print_login_header();
        cout << "plaese enter username:\n\n";
        cin >> user_name;
        cout << "\nplease enter the password ";
        cin >> password;

    }
    current_user = user_name;
    print_main_screen();

}




int main()
{
    system("title Bank Management System");
    login_screen();

    system("pause>0");
    return 0;
}
