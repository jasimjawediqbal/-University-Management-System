#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>

using namespace std;

// Function to validate integer input
int getValidatedChoice() {
    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number." << endl;
        } else {
            return choice;
        }
    }
}

// Function to generate a new ID based on file content
int generateID(const string& fileName) {
    int id = 1;
    ifstream file(fileName.c_str());
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            id++;
        }
        file.close();
    }
    return id;
}

// Function to validate non-empty input
bool validateInput(const string& input) {
    if (input.empty()) {
        cout << "Input cannot be empty!" << endl;
        return false;
    }
    return true;
}

// Function to validate name input (no numbers)
bool validateName(const string& name) {
    for (int i = 0; i < name.length(); i++) {
        if (isdigit(name[i])) {
            cout << "Name cannot contain numbers!" << endl;
            return false;
        }
    }
    return true;
}

// Function to validate date input (YYYY-MM-DD)
bool validateDate(const string& date) {
    if (date.length() != 10) {
        cout << "Invalid date format! Please use YYYY-MM-DD." << endl;
        return false;
    }
    for (int i = 0; i < 4; i++) {
        if (!isdigit(date[i])) {
            cout << "Invalid date format! Please use YYYY-MM-DD." << endl;
            return false;
        }
    }
    if (date[4] != '-' || date[7] != '-') {
        cout << "Invalid date format! Please use YYYY-MM-DD." << endl;
        return false;
    }
    for (int i = 5; i < 7; i++) {
        if (!isdigit(date[i])) {
            cout << "Invalid date format! Please use YYYY-MM-DD." << endl;
            return false;
        }
    }
    for (int i = 8; i < 10; i++) {
        if (!isdigit(date[i])) {
            cout << "Invalid date format! Please use YYYY-MM-DD." << endl;
            return false;
        }
    }
    return true;
}

// Function to validate phone number input
bool validatePhoneNumber(const string& phoneNumber) {
    if (phoneNumber.length() != 11) {
        cout << "Invalid phone number! Please use 10 digits." << endl;
        return false;
    }
    for (int i = 0; i < phoneNumber.length(); i++) {
        if (!isdigit(phoneNumber[i])) {
            cout << "Invalid phone number! Please use 10 digits." << endl;
            return false;
        }
    }
    return true;
}

// Function to validate email input (local-part@domain)
bool validateEmail(const string& email) {
    size_t atPos = email.find('@');
    if (atPos == string::npos) {
        cout << "Invalid email format! Please use email@gmail.com" << endl;
        return false;
    }
    string localPart = email.substr(0, atPos);
    string domain = email.substr(atPos + 1);
    if (localPart.empty() || domain.empty()) {
        cout << "Invalid email format! Please use email@gmail.com" << endl;
        return false;
    }
    return true;
}

// Function to validate gender input (male or female)
bool validateGender(const string& gender) {
    string lowerGender = gender;
    transform(lowerGender.begin(), lowerGender.end(), lowerGender.begin(), ::tolower);
    if (lowerGender != "male" && lowerGender != "female") {
        cout << "Invalid gender! Please enter male or female." << endl;
        return false;
    }
    return true;
}

// Function to write data to a file
void writeDataToFile(const string& fileName, const string& data, int id, const string& DOB, const string& Gender, const string& email, const string& phoneNumber, const string& address) {
    ofstream file(fileName.c_str(), ios::app);
    if (file.is_open()) {
        file << id << " " << data << " " << DOB << " " << Gender << " " << email << " " << phoneNumber << " " << address << endl;
        file.close();
        cout << "Successfully added " << data << " with ID " << id << endl;
    } else {
        cout << "Unable to open file for writing." << endl;
    }
}
// Function to read data from a file
string readDataFromFile(const string& fileName) {
    ifstream file(fileName.c_str());
    string data;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            data += line + "\n";
        }
        file.close();
    } else {
        cout << "Unable to open file for reading." << endl;
    }
    return data;
}

// Function to update data in a file
void updateDataInFile(const string& fileName, int id, const string& newData, const string& newDOB, const string& newGender, const string& newEmail, const string& newPhoneNumber, const string& newAddress) {
    vector<string> lines;
    ifstream file(fileName.c_str());
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }
    ofstream fileOut(fileName.c_str());
    if (fileOut.is_open()) {
        for (int i = 0; i < lines.size(); i++) {
            int lineID;
            string lineData;
            stringstream ss(lines[i]);
            ss >> lineID >> ws;
            getline(ss, lineData);
            if (lineID == id) {
                fileOut << id << " " << newData << " " << newDOB << " " << newGender << " " << newEmail << " " << newPhoneNumber << " " << newAddress << endl;
            } else {
                fileOut << lines[i] << endl;
            }
        }
        fileOut.close();
        cout << "Successfully updated data with ID " << id << endl;
    }
}

// Function to delete data from a file
void deleteDataFromFile(const string& fileName, int id) {
    vector<string> lines;
    ifstream file(fileName.c_str());
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }
    ofstream fileOut(fileName.c_str());
    if (fileOut.is_open()) {
        for (int i = 0; i < lines.size(); i++) {
            int lineID;
            string lineData;
            stringstream ss(lines[i]);
            ss >> lineID >> ws;
            getline(ss, lineData);
            if (lineID != id) {
                fileOut << lines[i] << endl;
            }
        }
        fileOut.close();
        cout << "Successfully deleted data with ID " << id << endl;
    }
}
bool validateSubject(const string& subject) {
    for (int i = 0; i < subject.length(); i++) {
        if (!isalpha(subject[i])) {
            return false;
        }
    }
    return true;
}
	void addMarksToFile(const string& fileName, int id, const string& subject, const string& marks) {
    if (!validateSubject(subject)) {
        cout << "Invalid subject! Please enter only alphabets." << endl;
        return;
    }
    vector<string> lines;
    ifstream file(fileName.c_str());
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }
    ofstream fileOut(fileName.c_str());
    if (fileOut.is_open()) {
        for (int i = 0; i < lines.size(); i++) {
            int lineID;
            string lineData;
            stringstream ss(lines[i]);
            ss >> lineID >> ws;
            getline(ss, lineData);
            if (lineID == id) {
                fileOut << lines[i] << " " << subject << " " << marks << endl;
            } else {
                fileOut << lines[i] << endl;
            }
        }
        fileOut.close();
        cout << "Successfully added marks to student with ID " << id << endl;
    }
}
// Function to search student by ID
void searchStudentByID(const string& fileName, int id) {
    ifstream file(fileName.c_str());
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            int lineID;
            string lineData;
            stringstream ss(line);
            ss >> lineID >> ws;
            getline(ss, lineData);
            if (lineID == id) {
                cout << "Student found with ID " << id << ":" << endl;
                cout << line << endl;
                return;
            }
        }
        file.close();
        cout << "Student not found with ID " << id << endl;
    }
}

// Function to search faculty by ID
void searchFacultyByID(const string& fileName, int id) {
    ifstream file(fileName.c_str());
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            int lineID;
            string lineData;
            stringstream ss(line);
            ss >> lineID >> ws;
            getline(ss, lineData);
            if (lineID == id) {
                cout << "Faculty found with ID " << id << ":" << endl;
                cout << line << endl;
                return;
            }
        }
        file.close();
        file.close();
        cout << "Faculty not found with ID " << id << endl;
    }
}

// Function to sort students by name
void sortStudentsByName(const string& fileName) {
    vector<string> lines;
    ifstream file(fileName.c_str());
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }
    sort(lines.begin(), lines.end());
    ofstream fileOut(fileName.c_str());
    if (fileOut.is_open()) {
        for (int i = 0; i < lines.size(); i++) {
            fileOut << lines[i] << endl;
        }
        fileOut.close();
        cout << "Students sorted by name successfully." << endl;
    }
}

// Function to sort faculty by name
void sortFacultyByName(const string& fileName) {
    vector<string> lines;
    ifstream file(fileName.c_str());
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }
    sort(lines.begin(), lines.end());
    ofstream fileOut(fileName.c_str());
    if (fileOut.is_open()) {
        for (int i = 0; i < lines.size(); i++) {
            fileOut << lines[i] << endl;
        }
        fileOut.close();
        cout << "Faculty sorted by name successfully." << endl;
    }
}

// Base class for menu options
class Menu {
public:
    virtual void display() = 0;
};

// Student menu and sub-menus
class StudentMenu : public Menu {
public:
    void display() {
        int choice;
        cout << "Student Menu" << endl;
        cout << "______________" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. View Students" << endl;
        cout << "3. Update Student" << endl;
        cout << "4. Delete Student" << endl;
        cout << "5. Add Marks to Student" << endl;
        cout << "6. Search Student by ID" << endl;
        cout << "7. Sort Students by Name" << endl;
        cout << "8. Return to Main Menu" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        choice = getValidatedChoice();
        cout << endl;
        string studentName;
        int id;
        string DOB;
        string Gender;
        string email;
        string phoneNumber;
        string address;
        string updateName;
        string newDOB;
        string newGender;
        string newEmail;
        string newPhoneNumber;
        string newAddress;
        string marks;
        switch (choice) {
            case 1:
                cout << "Enter name of Student: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, studentName);
                while (!validateName(studentName)) {
                    getline(cin, studentName);
                }
                cout << "Enter DOB of Student (YYYY-MM-DD): ";
                getline(cin, DOB);
                while (!validateDate(DOB)) {
                    getline(cin, DOB);
                }
                cout << "Enter Gender of Student (male/female): ";
                getline(cin, Gender);
                while (!validateGender(Gender)) {
                    getline(cin, Gender);
                }
                cout << "Enter Email of Student: ";
                getline(cin, email);
                while (!validateEmail(email)) {
                    getline(cin, email);
                }
                cout << "Enter Phone Number of Student: ";
                getline(cin, phoneNumber);
                while (!validatePhoneNumber(phoneNumber)) {
                    getline(cin, phoneNumber);
                }
                cout << "Enter Address of Student: ";
                getline(cin, address);
                if (validateInput(studentName)) {
                    id = generateID("students.txt");
                    writeDataToFile("students.txt", studentName, id, DOB, Gender, email, phoneNumber, address);
                }
                break;
            case 2:
                cout << "List of Students:" << endl;
                cout << "ID|Name|Date Of Birth|Gender|Email|Phone Number|Address\n---------------------------" << endl;
                cout << readDataFromFile("students.txt");
                break;
            case 3:
                cout << "Enter ID of Student to update: ";
                id = getValidatedChoice();
                cout << "Enter new name of Student: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, updateName);
                while (!validateName(updateName)) {
                    getline(cin, updateName);
                }
                cout << "Enter new DOB of Student (YYYY-MM-DD): ";
                getline(cin, newDOB);
                while (!validateDate(newDOB)) {
                    getline(cin, newDOB);
                }
                 cout << "Enter new Gender of Student (male/female): ";
                getline(cin, newGender);
                while (!validateGender(newGender)) {
                    getline(cin, newGender);
                }
                cout << "Enter new Email of Student: ";
                getline(cin, newEmail);
                while (!validateEmail(newEmail)) {
                    getline(cin, newEmail);
                }
                cout << "Enter new Phone Number of Student: ";
                getline(cin, newPhoneNumber);
                while (!validatePhoneNumber(newPhoneNumber)) {
                    getline(cin, newPhoneNumber);
                }
                cout << "Enter new Address of Student: ";
                getline(cin, newAddress);
                if (validateInput(updateName)) {
                    updateDataInFile("students.txt", id, updateName, newDOB, newGender, newEmail, newPhoneNumber, newAddress);
                }
                break;
            case 4:
                cout << "Enter ID of Student to delete: ";
                id = getValidatedChoice();
                deleteDataFromFile("students.txt", id);
                break;
            case 5: {
    cout << "Enter ID of Student to add marks: ";
    id = getValidatedChoice();
    cout << "Enter Subject: ";
    string subject;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, subject);
    cout << "Enter marks, Grade or Remarks: ";
    string marks;
    getline(cin, marks);
    addMarksToFile("students.txt", id, subject, marks);
    break;
}

            case 6:
                cout << "Enter ID of Student to search: ";
                id = getValidatedChoice();
                searchStudentByID("students.txt", id);
                break;
            case 7:
                sortStudentsByName("students.txt");
                break;
            case 8:
                return;
            default:
                cout << "Invalid choice! Please choose a valid option." << endl;
        }
    }
};

// Faculty menu and sub-menus
class FacultyMenu : public Menu {
public:
    void display() {
        int choice;
        cout << "Faculty Menu" << endl;
        cout << "______________" << endl;
        cout << "1. Add Faculty" << endl;
        cout << "2. View Faculty" << endl;
        cout << "3. Update Faculty" << endl;
        cout << "4. Delete Faculty" << endl;
        cout << "5. Search Faculty by ID" << endl;
        cout << "6. Sort Faculty by Name" << endl;
        cout << "7. Return to Main Menu" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        choice = getValidatedChoice();
        cout << endl;
        string facultyName;
        int id;
        string DOB;
        string Gender;
        string email;
        string phoneNumber;
        string address;
        string updateName;
        string newDOB;
        string newGender;
        string newEmail;
        string newPhoneNumber;
        string newAddress;
        switch (choice) {
            case 1:
                cout << "Enter name of Faculty: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, facultyName);
                while (!validateName(facultyName)) {
                    getline(cin, facultyName);
                }
                cout << "Enter DOB of Faculty (YYYY-MM-DD): ";
                getline(cin, DOB);
                while (!validateDate(DOB)) {
                    getline(cin, DOB);
                }
                cout << "Enter Gender of Faculty (male/female): ";
                getline(cin, Gender);
                while (!validateGender(Gender)) {
                    getline(cin, Gender);
                }
                cout << "Enter Email of Faculty: ";
                getline(cin, email);
                while (!validateEmail(email)) {
                    getline(cin, email);
                }
                cout << "Enter Phone Number of Faculty: ";
                getline(cin, phoneNumber);
                while (!validatePhoneNumber(phoneNumber)) {
                    getline(cin, phoneNumber);
                }
                cout << "Enter Address of Faculty: ";
                getline(cin, address);
                if (validateInput(facultyName)) {
                    id = generateID("faculty.txt");
                    writeDataToFile("faculty.txt", facultyName, id, DOB, Gender, email, phoneNumber, address);
                }
                break;
            case 2:
                cout << "List of Faculty:" << endl;
                cout << "ID|Name|Date Of Birth|Gender|Email|Phone Number|Address\n---------------------------" << endl;
                cout << readDataFromFile("faculty.txt");
                break;
            case 3:
                cout << "Enter ID of Faculty to update: ";
                id = getValidatedChoice();
                cout << "Enter new name of Faculty: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, updateName);
                while (!validateName(updateName)) {
                    getline(cin, updateName);
                }
                cout << "Enter new DOB of Faculty (YYYY-MM-DD): ";
                 getline(cin, newDOB);
                while (!validateDate(newDOB)) {
                    getline(cin, newDOB);
                }
                cout << "Enter new Gender of Faculty (male/female): ";
                getline(cin, newGender);
                while (!validateGender(newGender)) {
                    getline(cin, newGender);
                }
                cout << "Enter new Email of Faculty: ";
                getline(cin, newEmail);
                while (!validateEmail(newEmail)) {
                    getline(cin, newEmail);
                }
                cout << "Enter new Phone Number of Faculty: ";
                getline(cin, newPhoneNumber);
                while (!validatePhoneNumber(newPhoneNumber)) {
                    getline(cin, newPhoneNumber);
                }
                cout << "Enter new Address of Faculty: ";
                getline(cin, newAddress);
                if (validateInput(updateName)) {
                    updateDataInFile("faculty.txt", id, updateName, newDOB, newGender, newEmail, newPhoneNumber, newAddress);
                }
                break;
            case 4:
                cout << "Enter ID of Faculty to delete: ";
                id = getValidatedChoice();
                deleteDataFromFile("faculty.txt", id);
                break;
            case 5:
                cout << "Enter ID of Faculty to search: ";
                id = getValidatedChoice();
                searchFacultyByID("faculty.txt", id);
                break;
            case 6:
                sortFacultyByName("faculty.txt");
                break;
            case 7:
                return;
            default:
                cout << "Invalid choice! Please choose a valid option." << endl;
        }
    }
};

// Main menu
class MainMenu : public Menu {
public:
	bool exitProgram = false;
    void display() {
    	StudentMenu studentMenu;
    	FacultyMenu facultyMenu;
        int choice;
        cout << "Main Menu" << endl;
        cout << "___________" << endl;
        cout << "1. Student Menu" << endl;
        cout << "2. Faculty Menu" << endl;
        cout << "3. Exit" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        choice = getValidatedChoice();
        cout << endl;
        switch (choice) {
            case 1:
                
                studentMenu.display();
                break;
            case 2:
                
                facultyMenu.display();
                break;
            case 3:
                cout << "Exiting the program. Goodbye!" << endl;
                exitProgram = true;
                break;
            default:
                cout << "Invalid choice! Please choose a valid option." << endl;
                break;
        }
    }
};

int main() {
    MainMenu mainMenu;
    while (!mainMenu.exitProgram) {
        mainMenu.display();
    }
    return 0;
}

