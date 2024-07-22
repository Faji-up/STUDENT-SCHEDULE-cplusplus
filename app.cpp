#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <chrono> // For time calculations
#include <thread>
#include <sstream> //For getting the first word in getline string
#include <cstring> //For strptime function
#include <ctime> // For getting current time
#include <algorithm> // For find_if
#include <cstdlib> // For exit function
#include <unistd.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>


using namespace std;

//FOR STUDENT
bool noAccount = false;
bool exitP = false;
int user = 0;
int adminUser = 0;
int userStudent = 0;
int userAdmin = 0;
int accounts = 0;
int accountA = 0;
bool transaction = true; //IF TRUE THE LOADING FUNCTION WILL BE DISPLAYED ELSE FALSE WILL NOT DISPLAY
string currentUser = " ";
int activeUserIndex = 0;
int dayFlag,febDay=28,nextMonthDay;
class Calendar;
FILE *fp;

void loading() {
    // Loading Design
    int animateSymbol = 0;
    string arrSymbols[4] = {"\\", "|", "/", "-"};

    cout << "\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    for (int x = 0; x <= 3; x++) {
        cout << "\t\t\t\t\t\tLoading";
        for (int j = 0; j <= x; j++) {
            cout << " . ";
        }
        cout << " " << arrSymbols[animateSymbol] << "\r";
        cout.flush();

        animateSymbol++;

        if (animateSymbol == 4) {
            animateSymbol = 0;
        }

        for (int h = 0; h <= 30000; h++) {
            for (int g = 0; g <= 10000; g++) {
            }
        }
    }
}

// Event structure
struct Event {
	string title;
    string description;
    string date;
};

struct account {
	string name;
	string password;
};

struct info {
	int age;
	string role;
	string yAndC;
};

//VECTOR FOR CREATING AN ACCOUNT/INFO
vector<string>studentYAndC;
vector<int>age;
vector<account>storeAccount;
vector<account>storeAccountA;
vector<info>userInfo;
vector<vector<Event>>eventInfo;
account activeUser;
map<string, vector<Event>> events;
class Calendar {
	private:


		// A function where we can save event to file
        void saveEventsToFile(const string& userName, const vector<Event>& events) {
           ofstream file(userName + "_events.txt");
           if (file.is_open()) {
             for (const auto& event : events) {
                 file << event.title << "," << event.description << "," << event.date << endl;
             }
             file.close();
            } else {
                cout << "Unable to save events to file." << endl;
           }
        }

	public:

	//To add all events
 void addEvent(const string& userName, const Event& eventAdd) {
    events[userName].push_back(eventAdd);

    saveEventsToFile(userName, events[userName]);
    eventInfo.push_back(events[userName]);
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tAdding Event." << endl;
    sleep(1);
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEvent added successfully!" << endl;
    sleep(1);
    system("cls");
}

// Function to load events from a file for a given user
vector<Event> loadEventsFromFile(const string& userName) {
    vector<Event> loadedEvents;
    ifstream file(userName + "_events.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string title, description, date;
            getline(ss, title, ',');
            getline(ss, description, ',');
            getline(ss, date);
            loadedEvents.push_back({title, description, date});
        }
        file.close();
    } else {
        cout << "No events found for this user." << endl;
        // It's advisable to handle the case where the file couldn't be opened
    }
    return loadedEvents;
}

    // View all events
    void viewEvents(const string& userName) {
    	events[userName] = loadEventsFromFile(userName);
        if (events.empty() || events.find(userName) == events.end()) {
            cout << "\t\t\t\t==================================================" << endl;
            cout << "\t\t\t\t\a              No events found." << endl;
            cout << "\t\t\t\t==================================================" << endl;
            sleep(1);
            system("cls");
            return;
        }
        system("cls");
        cout << "\n\n\n\n\n\n\n\n";
        cout << "\t\t\t\t==================================================" << endl;
        cout << "\t\t\t\t           Events in the calendar:" << endl;
        cout << "\t\t\t\t==================================================" << endl;
        for (const auto& schedEvent : events[userName]){

            cout << "\t\t\t\t           Title: " << schedEvent.title << endl;
            cout << "\t\t\t\t           Date: " << schedEvent.date << endl;
            cout << "\t\t\t\t           Description: " << schedEvent.description << endl;
            cout << "\t\t\t\t--------------------------------------------------" << endl;
        }
        cin.ignore();
        cout << "\t\t\t\t                    [ENTER]                       ";
        cin.get();
        system("cls");
    }


    // Delete event by title
    void deleteEvent(const string&userName, const string& title) {
        auto& userEvents = events[userName];
            auto it = find_if(userEvents.begin(), userEvents.end(), [&](const Event& event) {
                return event.title == title;
            });

            if (it != userEvents.end()) {
                userEvents.erase(it);
                system("cls");
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tDeleting Event ." << endl;
                this_thread::sleep_for(chrono::seconds(1));
                system("cls");
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEvent deleted successfully." << endl;
                this_thread::sleep_for(chrono::seconds(1));
                system("cls");
                saveEventsToFile(userName, events[userName]);
            } else {
                cout << "\t\t\t\t==================================================" << endl;
                cout << "\t\t\t\t\a               Event not found." << endl;
                cout << "\t\t\t\t==================================================" << endl;
                sleep(1);
                system("cls");
            }
    }

    // Check if event is coming soon and display notification
    void checkForNotification() {
        // Get current time
       /* time_t now = time(nullptr);

        for (const auto& event : events) {
            // Convert event date string to time structure
            struct tm tm_event = {};
            strptime(event.date.c_str(), "%Y-%m-%d %H:%M", &tm_event);
            time_t eventTime = mktime(&tm_event);

            // Calculate difference in minutes
            int diffMinutes = difftime(eventTime, now) / 60;

            // If event is within 15 minutes, display notification
            if (diffMinutes > 0 && diffMinutes <= 15) {
                cout << "Notification: Event '" << event.title << "' is coming up in " << diffMinutes << " minutes!" << endl;
                // Simulate notification by sleeping for 2 seconds
                this_thread::sleep_for(chrono::seconds(2));
            }
        }*/
    }

    void sOrA() {
       info roleInfo;
       string roleUser;
       if(transaction == true) {
          loading();
	      system("cls");
          cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tThank you for waiting!" << endl;
          sleep(2);
        }
        transaction = false;
	    do{
	       system("cls");
	       cout << "\n\n\n\n\n\n\n\n";
           cout << "\t\t\t\t==================================================" << endl;
           cout << "\t\t\t\t\t\tSCHEDULING SYSTEM" << endl;
           cout << "\t\t\t\t==================================================" << endl << endl;
           cout << "\t\t\t\t__________________________________________________" << endl << "\t\t\t\t=\t\t\t\t\t\t =" << endl;
           cout << "\t\t\t\t=\t\t[A] Admin.\t\t\t =\n\t\t\t\t=\t\t[S] Student.\t\t\t =\n\t\t\t\t=\t\t[E] Exit.\t\t\t =\n";
           cout << "\t\t\t\t__________________________________________________" << endl << endl;
           cout << "\t\t\t\t\t   Please enter your role: ";
           cin >> roleUser;
           if(roleUser == "A" || roleUser == "a") {
              roleInfo.role = "Admin";
            } else if(roleUser == "S" || roleUser == "s") {
              roleInfo.role = "Student";
            }else if(roleUser == "E" || roleUser == "e") {
            	cout << "\t\t\t\t==================================================" << endl;
                cout << "\t\t\t\t                     Exit" << endl;
                cout << "\t\t\t\t==================================================" << endl;
                exitP = true;
                return;
            } else {
             	cout << "\t\t\t\t==================================================" << endl;
                cout << "\a\t\t\t\t\tInvalid input please try again." << endl;
                cout << "\t\t\t\t==================================================" << endl;
                sleep(3);
           }
           userInfo.push_back(roleInfo);

          // user++;

         if(roleUser == "S" || roleUser == "s") {
            userStudent++;
         }

        } while(!(roleUser == "A" || roleUser == "a" || roleUser == "S" || roleUser == "s" || roleUser == "E" || roleUser == "e"));
    }

    void createAccount() { //FOR USER
    char press;
    account create;
    info accountInfo;
    string firstName;

    cout << "\n\n\n\n\n\n\n\n" << endl;
    cout << "\t\t\t\t==================================================" << endl;
    cout << "\t\t\t\t\t        CREATE ACCOUNT" << endl;
    cout << "\t\t\t\t==================================================" << endl;

    cout << "\t\t\t\tEnter your name: ";
    getline(cin, create.name);
    if (create.name.empty()) {
        cout << "\t\t\t\tName cannot be empty. Please try again." << endl;
        return;
    }

    istringstream iss(create.name);
    iss >> firstName;

    cout << "\t\t\t\tEnter your password: ";
    getline(cin, create.password);
    if (create.password.empty()) {
        cout << "\t\t\t\tPassword cannot be empty. Please try again." << endl;
        return;
    }

    storeAccount.push_back(create);

    cout << "\t\t\t\t==================================================" << endl;
    cout << "\t\t\t\t\t\t    [ENTER]";
    cin.get(press);
    system("cls");

    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t  Successfully created account!" << endl;
    sleep(1);
    system("cls");

    cout << "\n\n\n\n\n\n\n" << endl;
    cout << "\t\t\t\t==================================================" << endl;
    cout << "\t\t\t\t\t\t   Welcome " << firstName << "." << endl;
    cout << "\t\t\t\t==================================================" << endl;
    cout << "\t\t\t\t    Please input additional info. Thank you." << endl;
    cout << "\t\t\t\t==================================================" << endl;

    cout << "\t\t\t\tEnter your age: ";
    cin >> accountInfo.age;
    if (accountInfo.age <= 0 || accountInfo.age > 150) {
        cout << "\t\t\t\tInvalid age. Please enter a valid age." << endl;
        return;
    }
    int studAge = accountInfo.age;
    cin.ignore();

    cout << "\t\t\t\tEnter your year, course, & section[BSIT 1E]: ";
    getline(cin, accountInfo.yAndC);
    if (accountInfo.yAndC.empty()) {
        cout << "\t\t\t\tY/C/S cannot be empty. Please try again." << endl;
        return;
    }

    string studYAndC = accountInfo.yAndC;
    studentYAndC.push_back(studYAndC);
    userInfo.push_back(accountInfo);

    system("cls");
    loading();
    system("cls");

    cout << "\n\n\n\n\n\n\n" << endl;
    cout << "\n\n\t\t\t\t==================================================" << endl;
    cout << "\t\t\t\t               STUDENT PROFILE" << endl;
    cout << "\t\t\t\t==================================================" << endl;
    cout << "\t\t\t\t             Name: " << storeAccount.back().name << endl;
    cout << "\t\t\t\t             Age: " << userInfo.back().age << endl;
    cout << "\t\t\t\t             Y\\C\\S: " << userInfo.back().yAndC << endl;
    cout << "\t\t\t\t==================================================" << endl;

    cout << "\t\t\t\t          [Press any key to continue]";
    cin.get(press);

    system("cls");

     }

    int logIn() { //FOR USER
    	account login;
    	char back;
     	bool isLoggedIn = false;
    	do{
    	  system("cls");
    	  do{
     	  	cout << "\n\n\n\n\n\n\n\n\n\n";
    	  	cout << "\t\t\t\t==================================================" << endl;
            cout << "\t\t\t\t                 Back[Y/N]: ";
            cin >> back;
            cout << "\t\t\t\t==================================================" << endl;
            if(back == 'Y' || back == 'y') {
              cout << "\t\t\t\t                Back..." << endl;
              cout << "\t\t\t\t==================================================" << endl;
              accounts=0;
              return 0;
            } else if(back == 'N' || back == 'n') {
              cout << "\t\t\t\t                Continue..." << endl;
              cout << "\t\t\t\t==================================================" << endl;
              accounts=1;
            } else {
              cout << "\a\t\t\t\t               Invalid input..." << endl;
              cout << "\t\t\t\t==================================================" << endl;
              system("cls");
            }
    	  } while(!(back == 'Y' || back == 'y' || back == 'N' || back == 'n'));

   	    if(back == 'Y' || back == 'y') {
            return 0;
        } else if (back == 'N' || back == 'n' ) {
         	cin.ignore();
        	cout << "\t\t\t\t     Enter your name: ";
	        getline(cin, login.name);
	        currentUser=login.name;
        	cout << "\t\t\t\t     Enter your password: ";
        	getline(cin, login.password);
        	cout << "\t\t\t\t==================================================" << endl;
        	cout << "\t\t\t\t                  [ENTER]";
        	cin.get();
        	system("cls");
        	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tLog In.";
        	sleep(1);
        	int index = 0;
        	system("cls");
               for (const account& names : storeAccount) {
                   if (names.name == login.name && names.password == login.password) {
                       cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tSuccessfully logged in!" << endl;
                       isLoggedIn = true;
                       activeUser = names;
                        return 1;
                       break;
                   }
                   activeUserIndex++;
               }
        }

            if(user == 0) {
            	system("cls");
            	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t==================================================" << endl;
                cout << "\a\t\t\t\t  No user found yet. Please create an account first." << endl;
                cout << "\t\t\t\t==================================================" << endl;
                noAccount = true;
                return 0;
            }

            else if(!isLoggedIn) {
               system("cls");
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t==================================================" << endl;
                cout << "\a\t\t\t\t           No account found." << endl;
                cout << "\t\t\t\t==================================================" << endl;
                return 0;
            }

        } while (!isLoggedIn);

            sleep(1);
    }

    void createAccountA() { //FOR ADMIN
        adminUser++;
        system("cls");
     	char press;
    	account create;
    	info accountInfo;
    	cin.ignore();

    	cout << "\n\n\n\n\n\n\n\n" << endl;
    	cout << "\t\t\t\t==================================================" << endl;
    	cout << "\t\t\t\t\t        CREATE ACCOUNT" << endl;
    	cout << "\t\t\t\t==================================================" << endl;
	    cout << "\t\t\t\tEnter your name: ";
    	getline(cin, create.name);
    	cout << "\t\t\t\tEnter your password: ";
    	getline(cin, create.password);
        storeAccountA.push_back(create);
       cout << "\t\t\t\t==================================================" << endl;
       cout << "\t\t\t\t\t\t    [ENTER]";
       cin.get(press);
       system("cls");
       cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t  Succesfully creating account!" << endl;
       sleep(1);
       system("cls");

     }

    void logInA() { //FOR ADMIN
    	account login;
    	char back;
     	bool isLoggedIn = false;
    	do{
    	  system("cls");
    	  do{
     	  	cout << "\n\n\n\n\n\n\n\n\n\n";
    	  	cout << "\t\t\t\t==================================================" << endl;
            cout << "\t\t\t\t                 Back[Y/N]: ";
            cin >> back;
            cout << "\t\t\t\t==================================================" << endl;
            if(back == 'Y' || back == 'y') {
              cout << "\t\t\t\t                Back..." << endl;
              cout << "\t\t\t\t==================================================" << endl;
              accountA=0;
              break;
            } else if(back == 'N' || back == 'n') {
              cout << "\t\t\t\t                Continue..." << endl;
              cout << "\t\t\t\t==================================================" << endl;
              accountA=1;
            } else {
              cout << "\a\t\t\t\t               Invalid input..." << endl;
              cout << "\t\t\t\t==================================================" << endl;
              system("cls");
            }
    	  } while(!(back == 'Y' || back == 'y' || back == 'N' || back == 'n'));

   	    if(back == 'Y' || back == 'y') {
            break;
        } else if (back == 'N' || back == 'n' ) {
         	cin.ignore();
        	cout << "\t\t\t\t     Enter your name: ";
	        getline(cin, login.name);
	        currentUser=login.name;
        	cout << "\t\t\t\t     Enter your password: ";
        	getline(cin, login.password);
        	cout << "\t\t\t\t==================================================" << endl;
        	cout << "\t\t\t\t                  [ENTER]";
        	cin.get();
        	system("cls");
        	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tLog In.";
        	sleep(1);
        	system("cls");
               for (const account& names : storeAccountA) {
                   if (names.name == login.name && names.password == login.password) {
                       cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tSuccessfully logged in!" << endl;
                       isLoggedIn = true;
                       break;
                   }
               }
        }

            if(adminUser == 0) {
            	system("cls");
            	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t==================================================" << endl;
                cout << "\a\t\t\t\t  No user found yet. Please create an account first." << endl;
                cout << "\t\t\t\t==================================================" << endl;
                noAccount = true;
                break;
            }

            else if(!isLoggedIn) {
               system("cls");
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t==================================================" << endl;
                cout << "\a\t\t\t\t           No account found." << endl;
                cout << "\t\t\t\t==================================================" << endl;
            }

        } while (!isLoggedIn);

            sleep(1);
    }

};

void updateUserEvent(int& numStudent) {
if (numStudent < 1 || numStudent > storeAccount.size()) {
        cout << "Invalid student number. Please try again." << endl;
        return;
    }

    string eventName;
    cout << "\t\t\t\tEnter the event title you want to update: ";
    cin.ignore();
    getline(cin, eventName);

    auto& userEvents = events[storeAccount[numStudent-1].name];
    if (userEvents.empty()) {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n";
        cout << "\t\t\t\t==================================================" << endl;
        cout << "\t\t\t\t               No events available." << endl;
        cout << "\t\t\t\t==================================================" << endl;
        system("cls");
        return;
    }

    for (auto& event : userEvents) {
        if (event.title == eventName) {
            cout << "\t\t\t\tUpdating event: " << event.title << endl;
            cout << "\t\t\t\tEnter new title (or press enter to keep it the same): ";
            string newTitle;
            getline(cin, newTitle);
            if (!newTitle.empty()) {
                event.title = newTitle;
            }

            cout << "\t\t\t\tEnter new date (or press enter to keep it the same): ";
            string newDate;
            getline(cin, newDate);
            if (!newDate.empty()) {
                event.date = newDate;
            }

            cout << "\t\t\t\tEnter new description (or press enter to keep it the same): ";
            string newDescription;
            getline(cin, newDescription);
            if (!newDescription.empty()) {
                event.description = newDescription;
            }

            cout << "Event updated successfully." << endl;
            sleep(1);
            system("cls");

            ofstream file(storeAccount[numStudent-1].name + "_events.txt");
            if (file.is_open()) {
                for (const auto& event : userEvents) {
                    file << event.title << "," << event.description << "," << event.date << endl;
                }
                file.close();
            } else {
                cout << "Unable to save events to file." << endl;
            }
            return;
        }
    }

    cout << "Event not found." << endl;
}

void deleteUserEvent(int& numStudent) {
   if (numStudent < 1 || numStudent > storeAccount.size()) {
        cout << "Invalid student number. Please try again." << endl;
        return;
    }

    string eventName;
    cout << "\t\t\t\tEnter the event title you want to delete: ";
    cin.ignore();
    getline(cin, eventName);

    auto& userEvents = events[storeAccount[numStudent-1].name];
    auto it = remove_if(userEvents.begin(), userEvents.end(), [&](const Event& event) {
        return event.title == eventName;
    });

    if (it != userEvents.end()) {
        userEvents.erase(it, userEvents.end());
        cout << "Event deleted successfully." << endl;
    } else {
        cout << "Event not found." << endl;
    }
}

void getUserEvents(int& numStudent) {
    if (numStudent < 1 || numStudent > storeAccount.size()) {
        cout << "Invalid student number. Please try again." << endl;
        return;
    }

    cout << "\n\n\n\n\n\n\n\n";
    cout << "\t\t\t\t==================================================" << endl;
    cout << "\t\t\t\t\t\tName: " << storeAccount[numStudent-1].name << endl;
    cout << "\t\t\t\t\t\tAge: " << age[numStudent-1] << endl;
    cout << "\t\t\t\t\t\tCourse, year, section: " << studentYAndC[numStudent-1] << endl;

    if (events[storeAccount[numStudent-1].name].size() > 0) {
        cout << "\t\t\t\t==================================================" << endl;
        cout << "\t\t\t\t\t\tStudent Schedule" << endl;
        cout << "\t\t\t\t==================================================" << endl;

        for (const auto& schedEvent : events[storeAccount[numStudent-1].name]) {
            cout << "\t\t\t\tEvent title: " << schedEvent.title << endl;
            cout << "\t\t\t\tDate: " << schedEvent.date << endl;
            cout << "\t\t\t\tEvent description: " << schedEvent.description << endl;
            cout << "\t\t\t\t==================================================" << endl;
        }
    } else {
        cout << "\t\t\t\t==================================================" << endl;
        istringstream iss(storeAccount[numStudent-1].name);
        string firstName1;
        iss >> firstName1;
        cout << "\t\t\t\t\tNo schedule found in " << firstName1 << "'s account. " << endl;
        cout << "\t\t\t\t==================================================" << endl;
    }
}
int getStudent(int& numStudent) {
    if (numStudent < 1 || numStudent > storeAccount.size()) {
        cout << "Invalid student number. Please try again." << endl;
        return -1;
    }

    char choiceA;
    bool validChoice = false;

    do {
        cout << "\n\n\n\n\n\n\n\n";
        cout << "\t\t\t\t==================================================" << endl;
        cout << "\t\t\t\tUser : " << storeAccount[numStudent-1].name << endl;
        cout << "\t\t\t\t==================================================" << endl;
        cout << "\t\t\t\t|            1. View Events                      |" << endl;
        cout << "\t\t\t\t|            2. Update Event                     |" << endl;
        cout << "\t\t\t\t|            3. Delete Event                     |" << endl;
        cout << "\t\t\t\t|            4. Exit                             |" << endl;
        cout << "\t\t\t\t==================================================" << endl;
        cout << "\t\t\t\tEnter your choice: ";
        cin >> choiceA;

        switch(choiceA) {
            case '1':
                getUserEvents(numStudent);
                validChoice = true;
                break;
            case '2':
                updateUserEvent(numStudent);
                validChoice = true;
                break;
            case '3':
                deleteUserEvent(numStudent);
                validChoice = true;
                break;
            case '4':
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!validChoice);

    return 1;
}


void printSpace(int monthday , int *setD)
{
    int i;
    for(i=1 ; i< monthday ; i++)
       {
            printf("    ");
            fprintf(fp,"    ");
           ++(*setD);
       }
}
void print4months(int firstDayOfMonth, int callcount)
{
    int j=1,c,d,k,l;
    int month1date=1,month2date=1,month3date=1,month4date=1;
    int month1end,month2end, month3end,month4end;
    int month1day,month2day,month3day,month4day;
    month1day = firstDayOfMonth;
    switch(callcount)  //finding 4 months parameter
    {
    case 1:
        month1end = 31;
        month2end = febDay;
        month3end = 31;
        month4end = 30;



        break;
    case 2:
        month1end = 31;
        month2end = 30;
        month3end = 31;
        month4end = 31;


        break;
    case 3:
        month1end = 30;
        month2end = 31;
        month3end = 30;
        month4end = 31;


        break;

    }
    month2day = ((month1end)%7+ month1day)%7;
        if(month2day==0)
            month2day =7;
        month3day = ((month2end)%7+ month2day)%7;

        if(month3day==0)
            month3day =7;
        month4day = ((month3end)%7+ month3day)%7;

        if(month4day==0)
            month4day =7;
        nextMonthDay = ((month4end)%7+ month4day)%7;

        if(nextMonthDay==0)
            nextMonthDay=7;

    while(j<7)// for 5 lines
    {k=0;
        for(c=1;c<5;c++) // for 4 months
        {l=1;
            for(d=0 ; d< 7 ; d++)
            {
                if (j ==1&&l==1)           //to print space when month begins
                { l--;

                    switch(c)
                    {
                    case 1: printSpace(month1day,&d); break;
                    case 2: printSpace(month2day,&d); break;
                    case 3: printSpace(month3day,&d); break;
                    case 4: printSpace(month4day,&d); break;

                    }
                }

                switch(c)           //starting to print date
                {
                case 1:
                    if(month1date<=month1end)
                    {
                        printf("%4d", month1date);
                        fprintf(fp,"%4d", month1date);
                        ++month1date;
                    }
                    else
                    {
                        printf("    ");
                        fprintf(fp,"    ");
                    }
                    break;
                case 2:
                    if(month2date<=month2end)
                    {
                        printf("%4d", month2date);
                        fprintf(fp,"%4d", month2date);
                        ++month2date;
                    }
                    else
                    {
                        printf("    ");
                        fprintf(fp,"    ");
                    }
                    break;
                case 3:
                    if(month3date<=month3end)
                    {
                        printf("%4d", month3date);
                        fprintf(fp,"%4d", month3date);
                        ++month3date;
                    }
                    else
                    {
                        printf("    ");
                        fprintf(fp,"    ");
                    }
                    break;
                case 4:
                    if(month4date<=month4end)
                    {
                        printf("%4d", month4date);
                        fprintf(fp,"%4d", month4date);
                        ++month4date;
                    }
                    else
                    {
                        printf("    ");
                        fprintf(fp,"    ");
                    }
                    break;

                }

            }

            if(k<3)
             {
                printf("\t\t    ");
                fprintf(fp,"\t\t    ");
                ++k;
             }

        }


        printf("\n");
        fprintf(fp,"\n");

        ++j;
    }




}


int firstDayOfYear(int year)
{
    int x= (((year-1)*365+(year-1)/4-(year-1)/100+(year-1)/400)+1)%7;
    if (x==0)
        return 7;
    return x;
}

int ifleapyear(int year)
{
    return (((year % 4 == 0) && (year % 100 != 0)) ||
             (year % 400 == 0)); // 0 for normal and 1 for a leap year
}

void calendarAPP(){

   FILE* fp = fopen("calenderRecords.txt", "a");
    if (!fp) {
        cout << "Error opening file." << endl;
        return;
    }

    int i, j, year;
    bool validYear = false;

    while (!validYear) {
        cout << "\n\n\t\t\t\t\tEnter a year (1950 - 2100): ";
        fprintf(fp, "\t\t\t\t\tEnter a year (1950 - 2100): ");
        if (scanf("%d", &year) != 1) {
            cout << "Invalid input. Please enter a valid year between 1950 and 2100." << endl;
            fprintf(fp, "Invalid input.\n");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (year < 1950 || year > 2100) {
            cout << "Year out of range. Please enter a year between 1950 and 2100." << endl;
            fprintf(fp, "Year out of range.\n");
        } else {
            validYear = true;
        }
    }

    fprintf(fp, "%d\n", year);
    int dayFlag = firstDayOfYear(year);
    int febDay = ifleapyear(year) ? 29 : 28;

    printf("\t\t\t        \t\t\t\t\t\tYEAR:%d\n", year);
    fprintf(fp, "\t\t\t        \t\t\t\t\t\tYEAR:%d\n", year);

    for (i = 0; i < 3; i++) {
        switch (i) {
            case 0:
                printf("            JANUARY                                     FEBRUARY                                         MARCH                                          APRIL          \n");
                fprintf(fp, "            JANUARY                                     FEBRUARY                                         MARCH                                          APRIL          \n");
                break;
            case 1:
                printf("              MAY                                         JUNE                                            JULY                                         AUGUST          \n");
                fprintf(fp, "              MAY                                         JUNE                                            JULY                                         AUGUST          \n");
                break;
            case 2:
                printf("           SEPTEMBER                                    OCTOBER                                         NOVEMBER                                      DECEMBER         \n");
                fprintf(fp, "           SEPTEMBER                                    OCTOBER                                         NOVEMBER                                      DECEMBER         \n");
                break;
        }

        for (j = 0; j < 3; j++) {
            printf("   M   T   W   T   F   S   S\t\t    ");
            fprintf(fp, "   M   T   W   T   F   S   S\t\t    ");
        }
        printf("   M   T   W   T   F   S   S\n");
        fprintf(fp, "   M   T   W   T   F   S   S\n");

        switch (i) {
            case 0:
                print4months(dayFlag, 1);
                printf("\n");
                fprintf(fp, "\n");
                break;
            case 1:
                print4months(dayFlag, 2);
                printf("\n");
                fprintf(fp, "\n");
                break;
            case 2:
                print4months(dayFlag, 3);
                printf("\n");
                fprintf(fp, "\n");
                break;
        }
    }
    fclose(fp);
}

int app(){
    Calendar calendar;
    int option, numStudent, choice, options;
    char yOrN;

    do {
        calendar.sOrA();

        if (exitP) {
            break;
        }

        if (userInfo.back().role == "Admin") {
            do {
                system("cls");
                cout << "\n\n\n\n\n\n\n\n";
                cout << "\t\t\t\t==================================================" << endl;
                cout << "\t\t\t\t|\t[1]Create account.\t\t\t |" << endl;
                cout << "\t\t\t\t|\t[2]Log in.\t\t\t\t |" << endl;
                cout << "\t\t\t\t|\t[3]Back.\t\t\t\t |" << endl;
                cout << "\t\t\t\t|\t[4]Exit.\t\t\t\t |" << endl;
                cout << "\t\t\t\t==================================================" << endl;
                cout << "\t\t\t\tPlease select an option: ";
                while (!(cin >> options) || options < 1 || options > 4) {
                    cout << "\t\t\t\tInvalid input. Please enter a number between 1 and 4: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                if (options == 1) {
                    system("cls");
                    calendar.createAccountA();
                    system("cls");
                } else if (options == 2) {
                    calendar.logInA();
                    int choiceA;
                    if (accountA > 0) {
                        do {
                            cout << "\n\n\n\n\n\n\n\n";
                            cout << "\t\t\t\t==================================================" << endl;
                            cout << "\t\t\t\t                     Admin                        " << endl;
                            cout << "\t\t\t\t==================================================" << endl;
                            cout << "\t\t\t\t|            1. View Users                       |" << endl;
                            cout << "\t\t\t\t|            2. Calendar                         |" << endl;
                            cout << "\t\t\t\t|            3. Log out                          |" << endl;
                            cout << "\t\t\t\t==================================================" << endl;
                            cout << "\t\t\t\tEnter your choice: ";
                            while (!(cin >> choiceA) || choiceA < 1 || choiceA > 3) {
                                cout << "\t\t\t\tInvalid input. Please enter a number between 1 and 3: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }

                            switch (choiceA) {
                                case 1:
                                    if (!storeAccount.empty()) {
                                        char enter1;
                                        do {
                                            system("cls");
                                            cout << "\n\n\n\n\n\n\n\n";
                                            cout << "\t\t\t\t==================================================" << endl;
                                            cout << "\t\t\t\t                   ADMIN" << endl;
                                            cout << "\t\t\t\t==================================================" << endl;
                                            cout << "\t\t\t\t            List of student users" << endl;
                                            cout << "\t\t\t\t==================================================" << endl;
                                            for (int x = 0; x < user; x++) {
                                                cout << "\t\t\t\t\t\t[" << x + 1 << "] " << storeAccount[x].name << endl;
                                                cout << "\t\t\t\t__________________________________________________" << endl;
                                            }
                                            cout << "\t\t\t\tEnter the number of student: ";
                                            while (!(cin >> numStudent) || numStudent < 1 || numStudent > user) {
                                                cout << "\t\t\t\tInvalid input. Please enter a valid student number: ";
                                                cin.clear();
                                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                            }
                                            system("cls");
                                            getStudent(numStudent);
                                            cout << "\t\t\t\t                     [ENTER]";
                                            cin.get(enter1);
                                            cin.ignore();
                                            system("cls");
                                            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tWant to see more student schedule record?[Y/N]: ";
                                            cin >> yOrN;

                                            if (yOrN == 'N' || yOrN == 'n') {
                                                break;
                                            } else if (yOrN != 'Y' && yOrN != 'y') {
                                                cout << "Invalid input please try again." << endl;
                                            }
                                        } while (yOrN == 'Y' || yOrN == 'y');
                                    } else {
                                        cout << "\t\t\t\t==================================================" << endl;
                                        cout << "\a\t\t\t\t\t     No student record found." << endl;
                                        cout << "\t\t\t\t==================================================" << endl;
                                        sleep(2);
                                        system("cls");
                                    }
                                    break;
                                case 2:
                                    // Handle case 2
                                    break;
                                case 3:
                                    break;
                            }
                        } while (choiceA != 3);
                    }
                } else if (options == 3) {
                    system("cls");
                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t     Returning to role selection." << endl;
                    sleep(1);
                    system("cls");
                } else if (options == 4) {
                    system("cls");
                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tExit .";
                    return 0;
                }
            } while (options != 3 && options != 4);
        }

        if (userInfo.back().role == "Student") {
            do {
                system("cls");
                cout << "\n\n\n\n\n\n\n\n";
                cout << "\t\t\t\t==================================================" << endl;
                cout << "\t\t\t\t                   User[" << user << "]                 " << endl;
                cout << "\t\t\t\t==================================================" << endl;
                cout << "\t\t\t\t|\t[1]Create account.\t\t\t |" << endl;
                cout << "\t\t\t\t|\t[2]Log in.\t\t\t\t |" << endl;
                cout << "\t\t\t\t|\t[3]Back.\t\t\t\t |" << endl;
                cout << "\t\t\t\t|\t[4]Exit.\t\t\t\t |" << endl;
                cout << "\t\t\t\t==================================================" << endl;
                cout << "\t\t\t\tPlease select an option: ";
                while (!(cin >> option) || option < 1 || option > 4) {
                    cout << "\t\t\t\tInvalid input. Please enter a number between 1 and 4: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                if (option == 1) {
                    system("cls");
                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tCreate an account." << endl;
                    sleep(1);
                    system("cls");
                    calendar.createAccount();
                } else if (option == 2) {
                    system("cls");
                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tLog in." << endl;
                    sleep(1);
                    system("cls");

                    system("cls");
                    if (calendar.logIn() == 1) {
                        do {
                            int index = activeUserIndex + 1;
                            cout << "\n\n\n\n\n\n\n\n";
                            cout << "\t\t\t\t==================================================" << endl;
                            cout << "\t\t\t\t           Schedule Management System             " << endl;
                            cout << "\t\t\t\t==================================================" << endl;
                            cout << "\t\t\t\t|            1. Add Event                        |" << endl;
                            cout << "\t\t\t\t|            2. View Events                      |" << endl;
                            cout << "\t\t\t\t|            3. Delete Event                     |" << endl;
                            cout << "\t\t\t\t|            4. Update Event                     |" << endl;
                            cout << "\t\t\t\t|            5. Check for Notification           |" << endl;
                            cout << "\t\t\t\t|            6. Calendar                         |" << endl;
                            cout << "\t\t\t\t|            7. Exit                             |" << endl;
                            cout << "\t\t\t\t|            8. Log out                          |" << endl;
                            cout << "\t\t\t\t==================================================" << endl;
                            cout << "\t\t\t\tEnter your choice: ";
                            while (!(cin >> choice) || choice < 1 || choice > 8) {
                                cout << "\t\t\t\tInvalid input. Please enter a number between 1 and 8: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }

                            switch (choice) {
                                case 1: {
                                    string title, description, date;
                                    system("cls");
                                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t==================================================" << endl;
                                    cout << "\t\t\t\t                 ADD EVENT" << endl;
                                    cout << "\t\t\t\t==================================================" << endl;
                                    cin.ignore();
                                    cout << "\t\t\t\tEnter event title: ";
                                    getline(cin, title);
                                    cout << "\t\t\t\tEnter event description: ";
                                    getline(cin, description);
                                    cout << "\t\t\t\tEnter event date and time (YYYY-MM-DD HH:MM): ";
                                    getline(cin, date);
                                    Event newEvent = {title, description, date};
                                    calendar.addEvent(currentUser, newEvent);
                                    break;
                                }
                                case 2:
                                    calendar.viewEvents(currentUser);
                                    break;
                                case 3: {
                                    string title;
                                    system("cls");
                                    cout << "\n\n\n\n\n\n\n\n";
                                    cout << "\t\t\t\t==================================================" << endl;
                                    cout << "\t\t\t\tEnter event title to delete: ";
                                    cin.ignore();
                                    getline(cin, title);
                                    cout << "\t\t\t\t==================================================" << endl;
                                    calendar.deleteEvent(currentUser, title);
                                    break;
                                }
                                case 4:
                                    updateUserEvent(index);
                                    break;
                                case 5:
                                    system("cls");
                                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tNo notification available yet." << endl;
                                    sleep(1);
                                    system("cls");
                                    break;
                                case 6:
                                    system("cls");
                                    calendarAPP();
                                    cout << "\t\t\t\t\t[E]Exit: ";
                                    char key;
                                    cin >> key;

                                    if (key == 'e' || key == 'E') {
                                        system("cls");
                                    } else {
                                        system("cls");
                                    }
                                    break;
                                case 7:
                                    system("cls");
                                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tExit .";
                                    sleep(1);
                                    system("cls");
                                    return 0;
                                case 8:
                                    system("cls");
                                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tLog out." << endl;
                                    sleep(1);
                                    system("cls");
                                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tBack to role selection." << endl;
                                    sleep(1);
                                    system("cls");
                                    break;
                                default:
                                    cout << "\t\t\t\t==================================================" << endl;
                                    cout << "\a\t\t\t\t               Invalid choice.                    " << endl;
                                    cout << "\t\t\t\t==================================================" << endl;
                                    sleep(2);
                            }
                        } while (choice != 8);
                    }
                } else if (option == 3) {
                    system("cls");
                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tReturning to role selection ." << endl;
                    sleep(1);
                    system("cls");
                    userStudent--;
                    break;
                } else if (option == 4) {
                    system("cls");
                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tExit .";
                    sleep(1);
                    system("cls");
                    break;
                }
            } while (option != 4);
        }
    } while (true);

    return 0;

}
int main () {
	while(true){
        app();
	}
	return 0;
}

