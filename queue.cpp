#include <iostream>
using namespace std;

class EventManager {
    int maxCapacity;
    char registered[100][50];
    char waitingList[100][50];
    int regCount = 0;
    int waitCount = 0;

public:
    EventManager(int capacity) : maxCapacity(capacity) {}

    void copyName(char* dest, const char* src) {
        int i = 0;
        while (src[i] != '\0') {
            dest[i] = src[i];
            ++i;
        }
        dest[i] = '\0';
    }

    void shiftLeft(char arr[][50], int& count) {
        for (int i = 0; i < count - 1; ++i) {
            copyName(arr[i], arr[i + 1]);
        }
        --count;
    }

    void addParticipant(const char* name) {
        if (regCount < maxCapacity) {
            copyName(registered[regCount++], name);
            cout << name << " registered successfully!\n";
        }
        else {
            copyName(waitingList[waitCount++], name);
            cout << "Event full. " << name << " added to waiting list.\n";
        }
    }

    void cancelRegistration() {
        if (regCount == 0) {
            cout << "No registered participants to cancel.\n";
            return;
        }

        cout << "Cancelling registration for " << registered[0] << ".\n";
        shiftLeft(registered, regCount);

        if (waitCount > 0) {
            copyName(registered[regCount++], waitingList[0]);
            cout << waitingList[0] << " moved from waiting list to registered list.\n";
            shiftLeft(waitingList, waitCount);
        }
    }

    void displayList(char list[][50], int count, const char* title) {
        if (count == 0) {
            cout << "No participants in " << title << ".\n";
            return;
        }

        cout << title << ":\n";
        for (int i = 0; i < count; ++i) {
            cout << list[i] << endl;
        }
    }

    void displayRegistered() { displayList(registered, regCount, "Registered Participants"); }
    void displayWaitingList() { displayList(waitingList, waitCount, "Waiting List"); }
};

int main() {
    int capacity;
    cout << "Enter event capacity: ";
    cin >> capacity;

    EventManager eventManager(capacity);

    int choice = 0;
    char name[50];

    while (choice != 5) {
        cout << "\n1. Register Participant\n2. Cancel Registration\n3. View Registered Participants\n4. View Waiting List\n5. Exit\nChoice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Enter name: ";
            cin.getline(name, 50);
            eventManager.addParticipant(name);
        }
        else if (choice == 2) {
            eventManager.cancelRegistration();
        }
        else if (choice == 3) {
            eventManager.displayRegistered();
        }
        else if (choice == 4) {
            eventManager.displayWaitingList();
        }
        else if (choice == 5) {
            cout << "Exiting.\n";
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
