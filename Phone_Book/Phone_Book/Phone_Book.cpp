#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct Contact {
    string first_name, last_name, number;
};
fstream dataSaver;
Contact* mainContacts = NULL;
int usersCounter = 0;

void addContactFromFile(Contact newUser) {
    Contact* temp = new Contact[usersCounter + 1];
    for (int i = 0; i < usersCounter; i++) {
        // taking a copy of main array in temp
        temp[i] = mainContacts[i];
    }
    temp[usersCounter] = newUser; // inserting new user in last index
    delete[] mainContacts;
    mainContacts = temp;
    usersCounter++;
}

void addContact() {
    vector <string> contact_name;
    string full_name, temp_str;
    Contact newUser;
    cout << "Enter Contact Name: " << endl;
    cin.get();
    getline(cin, full_name);
    cout << "Enter Contact Number: " << endl;
    cin >> newUser.number;
    stringstream ss(full_name);
    while (ss >> temp_str)  // separates Line by delimiter ' '
        contact_name.push_back(temp_str);
    newUser.first_name = contact_name[0];
    newUser.last_name = contact_name[1];
    Contact* temp = new Contact[usersCounter + 1];
    for (int i = 0; i < usersCounter; i++) {
        // taking a copy of main array in temp
        temp[i] = mainContacts[i];
    }
    temp[usersCounter] = newUser; // inserting new user in last index
    delete[] mainContacts;
    mainContacts = temp;
    usersCounter++;
}

void deleteContact() {
start:
    string full_name, number;
    cout << "1- Delete Contact by Name: \n"
        "2- Delete Contact by Number : \n";
    int input;
    cin >> input;
    switch (input) {
    case 1:
        cout << "Enter Contact Name: \n";
        cin.get();
        getline(cin, full_name);
        break;
    case 2:
        cout << "Enter Contact Number: \n";
        cin >> number;
        break;
    default:
        cout << "Invalid Input\n";
        goto start;
    }
    if (usersCounter == 0) {
        cout << "Not Found\n";
        return;
    }
    Contact* temp = new Contact[usersCounter - 1];
    int tempCounter = 0;
    bool found = false;
    if (input == 1) {
        for (int i = 0; i < usersCounter; i++) {
            if (mainContacts[i].first_name + " " + mainContacts[i].first_name == full_name) {
                found = true;
                continue;
            }
            temp[tempCounter] = mainContacts[i];
            tempCounter++;
        }

    }
    else if (input == 2) {
        for (int i = 0; i < usersCounter; i++) {
            if (mainContacts[i].number == number) {
                found = true;
                continue;
            }
            temp[tempCounter] = mainContacts[i];
            tempCounter++;
        }
    }
    if (!found) {
        cout << "Not Found\n";
        return;
    }
    delete[] mainContacts;
    mainContacts = temp;
    usersCounter--;
}

Contact searchContact() {
start:
    string name, number;
    cout << "1- Search Contact by Name: \n"
        "2- Search Contact by Number : \n";
    int input;
    cin >> input;
    switch (input) {
    case 1:
        cout << "Enter Contact Name: \n";
        cin.get();
        getline(cin, name);
        for (int i = 0; i < usersCounter; i++) {
            if (mainContacts[i].first_name == name) {
                return mainContacts[i];
            }
        }
        break;
    case 2:
        cout << "Enter Contact Number: \n";
        cin >> number;
        for (int i = 0; i < usersCounter; i++) {
            if (mainContacts[i].number == number) {
                return mainContacts[i];
            }
        }
        break;
    default:
        cout << "Invalid Input\n";
        goto start;
    }
    Contact notFound;
    notFound.first_name = "Not Found";
    return notFound;

}

void listAllContacts() {
    for (int i = 0; i < usersCounter; i++)
        cout << i + 1 << "- " << mainContacts[i].first_name << " " << mainContacts[i].last_name << " "
        << mainContacts[i].number << endl;
}

void split_Line(string line) {
    if (line == "")
        return;
    string temp;
    vector<string> contactData;   // queue to push each word in the Line separated
    stringstream ss(line);
    while (ss >> temp)  // separates Line by delimiter ' '
        contactData.push_back(temp);
    Contact user;
    user.first_name = contactData[0];
    user.last_name = contactData[1];
    user.number = contactData[2];
    addContactFromFile(user);
}

void loadFileData() {
    string line;
    dataSaver.open("Saved-Data.txt", ios::in);
    while (!dataSaver.eof()) {
        getline(dataSaver, line);
        split_Line(line);
    }
    dataSaver.close();
}

void saveDataToFile() {
    dataSaver.open("Saved-Data.txt", ios::out);
    for (int i = 0; i < usersCounter; i++) {
        dataSaver << mainContacts[i].first_name << " " << mainContacts[i].last_name << " " << mainContacts[i].number << endl;
    }
    dataSaver.close();

}

int main() {
    loadFileData();
    while (true) {
        cout << "1- Add Contact\n"
            "2- Delete Contact\n"
            "3- Search Contact\n"
            "4- List all Contacts\n"
            "5- End\n";
        int input;
        cin >> input;
        switch (input) {
        case 1:
            addContact();
            cout << "---------------------------" << endl;
            break;
        case 2:
            deleteContact();
            cout << "---------------------------" << endl;
            break;
        case 4:
            listAllContacts();
            cout << "---------------------------" << endl;
            break;
        case 5:
            saveDataToFile();
            return 0;
        case 3:
            Contact searchedUser = searchContact();
            if (searchedUser.first_name == "Not Found") {
                cout << "Not Found" << endl;
            }
            else {
                cout << searchedUser.first_name << " " << searchedUser.number << endl;
            }
            cout << "---------------------------" << endl;
            break;
        }
    }

}