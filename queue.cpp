#include <iostream>
#include <string>
using namespace std;

// Queue Class Definition
class Queue
{
public:
    Queue(int QueueSize);
    ~Queue();
    void Insert(string Value);
    string Remove();
    string First();
    void Display();

private:
    string* Array;
    int Front;
    int Rear;
    int Count;
    int ArraySize;
};

// Queue Implementation
Queue::Queue(int QueueSize)
{
    Array = new string[QueueSize];
    ArraySize = QueueSize;
    Front = 0;
    Rear = ArraySize - 1;
    Count = 0;
}

Queue::~Queue()
{
    delete[] Array;
}

void Queue::Insert(string Value)
{
    if (Count >= ArraySize)
    {
        cout << "Waiting list is FULL!\n";
        return;
    }
    Rear = (Rear + 1) % ArraySize;
    Array[Rear] = Value;
    Count++;
}

string Queue::Remove()
{
    if (Count == 0)
    {
        cout << "Waiting list is empty!\n";
        return "";
    }
    string Temp = Array[Front];
    Front = (Front + 1) % ArraySize;
    Count--;
    return Temp;
}

string Queue::First()
{
    if (Count == 0)
    {
        return "";
    }
    return Array[Front];
}

void Queue::Display()
{
    if (Count == 0)
    {
        cout << "Waiting list is empty!\n";
        return;
    }
    int index = Front;
    for (int i = 0; i < Count; i++)
    {
        cout << Array[index] << endl;
        index = (index + 1) % ArraySize;
    }
}

// EventManagement Implementation Continues
class EventManagement
{
public:
    EventManagement(int maxCapacity, int waitingListSize);
    ~EventManagement();
    void RegisterParticipant(string name);
    void CancelRegistration(string name);
    void DisplayParticipants();
    void DisplayWaitingList();

private:
    int maxCapacity;
    string* participants;
    int participantCount;
    Queue waitingList;
};

EventManagement::EventManagement(int maxCapacity, int waitingListSize)
    : maxCapacity(maxCapacity), waitingList(waitingListSize)
{
    participants = new string[maxCapacity];
    participantCount = 0;
}

EventManagement::~EventManagement()
{
    delete[] participants;
}

void EventManagement::RegisterParticipant(string name)
{
    if (participantCount >= maxCapacity)
    {
        cout << name << " added to the waiting list.\n";
        waitingList.Insert(name);
    }
    else
    {
        participants[participantCount++] = name;
        cout << name << " successfully registered.\n";
    }
}

void EventManagement::CancelRegistration(string name)
{
    int index = -1;
    for (int i = 0; i < participantCount; i++)
    {
        if (participants[i] == name)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        for (int i = index; i < participantCount - 1; i++)
        {
            participants[i] = participants[i + 1];
        }
        participantCount--;
        cout << name << " has been removed from the participants list.\n";

        if (waitingList.First() != "")
        {
            string nextParticipant = waitingList.Remove();
            participants[participantCount++] = nextParticipant;
            cout << nextParticipant << " has been moved from the waiting list to the participants list.\n";
        }
    }
    else
    {
        cout << name << " is not registered.\n";
    }
}

void EventManagement::DisplayParticipants()
{
    cout << "Participants list:" << endl;
    for (int i = 0; i < participantCount; i++)
    {
        cout << participants[i] << endl;
    }
}

void EventManagement::DisplayWaitingList()
{
    cout << "Waiting list:" << endl;
    waitingList.Display();
}

int main()
{
    EventManagement event(3, 5);

    event.RegisterParticipant("Alice");
    event.RegisterParticipant("Bob");
    event.RegisterParticipant("Charlie");
    event.RegisterParticipant("David");
    event.RegisterParticipant("Eve");

    event.DisplayParticipants();
    event.DisplayWaitingList();

    cout << endl;
    event.CancelRegistration("Bob");

    event.DisplayParticipants();
    event.DisplayWaitingList();

    return 0;
}
