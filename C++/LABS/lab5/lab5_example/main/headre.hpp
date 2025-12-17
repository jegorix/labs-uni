#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "../models/include/Human.hpp"
#include "../models/include/Teacher.hpp"
#include "../models/include/CommissionMember.hpp"
#include "../models/include/TeacherCommissionMember.hpp"
#include "../templates/include/Deque.hpp"
#include "../exceptions/include/InputHandler.hpp"
#include "../exceptions/include/Date.hpp"
using namespace std;

Language currentLang = Language::ENGLISH;

void drawMenu(const string& title, const string options[], int numOptions) {
    int max_len = title.length();
    for (int i = 0; i < numOptions; i++) {
        if (options[i].length() > max_len) max_len = options[i].length();
    }
    max_len += 4;
    cout << "+" << string(max_len, '-') << "+" << endl;
    cout << "| " << title << string(max_len - title.length() - 1, ' ') << "|" << endl;
    cout << "+" << string(max_len, '-') << "+" << endl;
    for (int i = 0; i < numOptions; i++) {
        cout << "| " << options[i] << string(max_len - options[i].length() - 1, ' ') << "|" << endl;
    }
    cout << "+" << string(max_len, '-') << "+" << endl;
}

void addObject(Deque<Human*>& deque) {
    string sideOptions[2] = {"1. Add to Front", "2. Add to Back"};
    drawMenu("Select Side", sideOptions, 2);
    
    // Использование safeInputNumeric<int>
    int sideChoice = safeInputNumeric<int>(cin, 1, 2, "Enter choice (1-2): ");
    
    string typeOptions[3] = {"1. Teacher", "2. Commission Member", "3. Teacher Commission Member"};
    drawMenu("Select Type", typeOptions, 3);
    
    // Использование safeInputNumeric<int>
    int typeChoice = safeInputNumeric<int>(cin, 1, 3, "Enter choice (1-3): ");
    
    Human* object;
    if (typeChoice == 1) {
        UniversityTeacher* teacher = new UniversityTeacher();
        cin >> *teacher;
        object = teacher;
    } else if (typeChoice == 2) {
        CommissionMember* commissionMember = new CommissionMember();
        cin >> *commissionMember;
        object = commissionMember;
    } else {
        TeacherCommissionMember* teacherCommissionMember = new TeacherCommissionMember();
        cin >> *teacherCommissionMember;
        object = teacherCommissionMember;
    }
    
    if (sideChoice == 1) {
        deque.pushFront(object);
    } else {
        deque.pushBack(object);
    }
}

void removeObject(Deque<Human*>& deque) {
    string options[2] = {"1. Remove from Front", "2. Remove from Back"};
    drawMenu("Remove Object", options, 2);
    
    // Использование safeInputNumeric<int>
    int choice = safeInputNumeric<int>(cin, 1, 2, "Enter choice (1-2): ");
    
    if (deque.isEmpty()) {
        cout << "Deque is empty." << endl;
        return;
    }
    
    if (choice == 1) {
        delete deque.peekFirst();
        deque.popFront();
        cout << "Removed from front." << endl;
    } else {
        delete deque.peekLast();
        deque.popBack();
        cout << "Removed from back." << endl;
    }
}

void modifyObject(Deque<Human*>& deque) {
    string sideOptions[2] = {"1. Modify First", "2. Modify Last"};
    drawMenu("Select Object to Modify", sideOptions, 2);
    
    // Использование safeInputNumeric<int>
    int sideChoice = safeInputNumeric<int>(cin, 1, 2, "Enter choice (1-2): ");
    
    if(deque.isEmpty()) {
        cout << "Deque is empty." << endl;
        return;
    }
    
    Human* human = (sideChoice == 1) ? deque.peekFirst() : deque.peekLast();
    
    string modifyOptions[2] = {"1. Change All Data", "2. Change Specific Field"};
    drawMenu("Modify Options", modifyOptions, 2);
    
    // Использование safeInputNumeric<int>
    int modifyChoice = safeInputNumeric<int>(cin, 1, 2, "Enter choice (1-2): ");
    
    if(modifyChoice == 1) {
        TeacherCommissionMember* tcm = dynamic_cast<TeacherCommissionMember*>(human);
        UniversityTeacher* teacher = dynamic_cast<UniversityTeacher*>(human);
        CommissionMember* cm = dynamic_cast<CommissionMember*>(human);
        
        if(tcm) {
            cin >> *tcm;
        } else if(teacher) {
            cin >> *teacher;
        } else if(cm) {
            cin >> *cm;
        } else {
            cin >> *human;
        }
        return;
    }
    
    int fieldChoice;
    TeacherCommissionMember* tcm = dynamic_cast<TeacherCommissionMember*>(human);
    
    if(tcm) {
        string fieldOptions[11] = {
            "1. First Name", "2. Last Name", "3. Middle Name", "4. Birthday",
            "5. Position", "6. Degree", "7. Specialty", "8. Add Scientific Work", 
            "9. Replace All Scientific Works", "10. Add Commission Work", 
            "11. Replace All Commission Works"
        };
        drawMenu("Select Field", fieldOptions, 11);
        
        // Использование safeInputNumeric<int>
        fieldChoice = safeInputNumeric<int>(cin, 1, 11, "Enter choice (1-11): ");
        
    } else if(dynamic_cast<UniversityTeacher*>(human)) {
        string fieldOptions[9] = {
            "1. First Name", "2. Last Name", "3. Middle Name", "4. Birthday",
            "5. Position", "6. Degree", "7. Specialty", "8. Add Scientific Work", 
            "9. Replace All Scientific Works"
        };
        drawMenu("Select Field", fieldOptions, 9);
        
        // Использование safeInputNumeric<int>
        fieldChoice = safeInputNumeric<int>(cin, 1, 9, "Enter choice (1-9): ");
        
    } else if(dynamic_cast<CommissionMember*>(human)) {
        string fieldOptions[9] = {
            "1. First Name", "2. Last Name", "3. Middle Name", "4. Birthday",
            "5. Commission Name", "6. Appointment Date", "7. Certificate Number", 
            "8. Add Autobiography", "9. Replace All Autobiography"
        };
        drawMenu("Select Field", fieldOptions, 9);
        
        // Использование safeInputNumeric<int>
        fieldChoice = safeInputNumeric<int>(cin, 1, 9, "Enter choice (1-9): ");
        
    } else {
        string fieldOptions[4] = {
            "1. First Name", "2. Last Name", "3. Middle Name", "4. Birthday"
        };
        drawMenu("Select Field", fieldOptions, 4);
        
        // Использование safeInputNumeric<int>
        fieldChoice = safeInputNumeric<int>(cin, 1, 4, "Enter choice (1-4): ");
    }
    
    try {
        human->updateField(fieldChoice);
        cout << "Field updated successfully." << endl;
    } catch (const InputException& e) {
        cout << "Error updating field: " << e.what() << endl;
    }
}

void peekObject(Deque<Human*>& deque) {
    string options[2] = {"1. Peek First", "2. Peek Last"};
    drawMenu("Peek Object", options, 2);
    
    // Использование safeInputNumeric<int>
    int choice = safeInputNumeric<int>(cin, 1, 2, "Enter choice (1-2): ");
    
    if (deque.isEmpty()) {
        cout << "Deque is empty." << endl;
        return;
    }
    
    Human* human = (choice == 1) ? deque.peekFirst() : deque.peekLast();
    
    if (!deque.isEmpty()) {
        TeacherCommissionMember tcm;
        tcm.printHeader();
        human->printTable();
    }
}

void printDeque(Deque<Human*>& deque) {
    if (deque.isEmpty()) {
        cout << "Deque is empty." << endl;
        return;
    }

    if (!deque.isEmpty()) {
        TeacherCommissionMember tcm;
        tcm.printHeader();
        
        Deque<Human*> temp;
        while (!deque.isEmpty()) {
            Human* human = deque.peekFirst();
            deque.popFront();
            human->printTable();
            temp.pushBack(human);
        }

        while (!temp.isEmpty()) {
            Human* human = temp.peekLast();
            temp.popBack();
            deque.pushFront(human);
        }
    }
}

void searchInDeque(Deque<Human*>& deque) {
    if (deque.isEmpty()) {
        cout << "Deque is empty." << endl;
        return;
    }

    string searchOptions[5] = {"1. Search by Last Name", "2. Search by First Name", "3. Search by Middle Name", "4. Search by Birthday", "5. Search by Full Match (all fields)"};
    drawMenu("Search Options", searchOptions, 5);
    
    // Использование safeInputNumeric<int>
    int choice = safeInputNumeric<int>(cin, 1, 5, "Enter choice (1-5): ");

    string searchString;
    Date searchDate;
    Date defaultDate(1, 1, 1900);
    
    UniversityTeacher* searchObj = new UniversityTeacher("", "", "", defaultDate, "", "", "");

    if (choice == 1) {
        // Использование safeGetLine
        searchString = safeGetLine(cin, currentLang, "Enter last name to search (English only): ");
        searchObj->setLastName(searchString);
        Human::setSearchMode(LAST_NAME);
    } else if (choice == 2) {
        // Использование safeGetLine
        searchString = safeGetLine(cin, currentLang, "Enter first name to search (English only): ");
        searchObj->setFirstName(searchString);
        Human::setSearchMode(FIRST_NAME);
    } else if (choice == 3) {
        // Использование safeGetLine
        searchString = safeGetLine(cin, currentLang, "Enter middle name to search (English only): ");
        searchObj->setMiddleName(searchString);
        Human::setSearchMode(MIDDLE_NAME);
    } else if (choice == 4) {
        // Использование safeInputDate
        searchDate = safeInputDate(cin, "DD/MM/YYYY", "Enter birthday to search: ");
        searchObj->setBirthday(searchDate);
        Human::setSearchMode(BIRTH_YEAR);
    } else { 
        cout << "Enter criteria for Full Match:" << endl;
        
        // Использование safeGetLine
        searchString = safeGetLine(cin, currentLang, "Enter last name (English only): ");
        searchObj->setLastName(searchString);
        
        // Использование safeGetLine
        searchString = safeGetLine(cin, currentLang, "Enter first name (English only): ");
        searchObj->setFirstName(searchString);
        
        // Использование safeGetLine
        searchString = safeGetLine(cin, currentLang, "Enter middle name (English only): ");
        searchObj->setMiddleName(searchString);
        
        // Использование safeInputDate
        searchDate = safeInputDate(cin, "DD/MM/YYYY", "Enter birthday: ");
        searchObj->setBirthday(searchDate);
        
        Human::setSearchMode(FULL_MATCH); 
    }

    Deque<Human*> searchResults = deque.find(searchObj);
    
    Human::setSearchMode(FULL_MATCH); 
    delete searchObj;
    
    if (searchResults.isEmpty()) {
        cout << "No matches found." << endl;
    } else {
        cout << "Search results (" << searchResults.size() << " found):" << endl;
        printDeque(searchResults); 
    }
}

void clearDeque(Deque<Human*>& deque) {
    while (!deque.isEmpty()) {
        delete deque.peekFirst();
        deque.popFront();
    }
    cout << "Deque cleared." << endl;
}

void sortDequeByField(Deque<Human*>& deque) {
    if (deque.isEmpty()) {
        cout << "Deque is empty. Nothing to sort." << endl;
        return;
    }
    string sortOptions[4] = {"1. Sort by Last Name", "2. Sort by First Name", "3. Sort by Middle Name", "4. Sort by Birth Year"};
    drawMenu("Sort Options", sortOptions, 4);
    
    // Использование safeInputNumeric<int>
    int choice = safeInputNumeric<int>(cin, 1, 4, "Enter choice (1-4): ");

    if (choice == 1) {
        Human::setSearchMode(LAST_NAME);
        cout << "Sorting by Last Name..." << endl;
    } else if (choice == 2) {
        Human::setSearchMode(FIRST_NAME);
        cout << "Sorting by First Name..." << endl;
    } else if (choice == 3) {
        Human::setSearchMode(MIDDLE_NAME);
        cout << "Sorting by Middle Name..." << endl;
    } else if (choice == 4) {
        Human::setSearchMode(BIRTH_YEAR);
        cout << "Sorting by Birth Year..." << endl;
    } else {
        cout << "Invalid choice. Aborting sort." << endl;
        return;
    }

    deque.sort();
    
    Human::setSearchMode(LAST_NAME); 
    
    cout << "Deque sorted successfully." << endl;
    printDeque(deque);
}

void run(){
    Deque<Human*> myDeque;
    int choice;
    string mainMenuOptions[8] = {
        "1. Add Object",
        "2. Remove Object", 
        "3. Modify Object",
        "4. Peek Object",
        "5. Print Deque",
        "6. Search",
        "7. Sort",
        "8. Exit"
    };
    
    do {
        drawMenu("Main Menu", mainMenuOptions, 8);
        
        // Использование safeInputNumeric<int>
        choice = safeInputNumeric<int>(cin, 1, 8, "Enter choice (1-8): ");
        
        switch (choice) {
            case 1: addObject(myDeque); break;
            case 2: removeObject(myDeque); break;
            case 3: modifyObject(myDeque); break;
            case 4: peekObject(myDeque); break;
            case 5: printDeque(myDeque); break;
            case 6: searchInDeque(myDeque); break;
            case 7: sortDequeByField(myDeque); break;
            case 8: clearDeque(myDeque); break;
        }
    } while (choice != 8);
}