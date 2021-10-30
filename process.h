#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <ctime>

using namespace std;

class Process
{
    string name;
    int atime; // arrival time
    int ptime; // processing time
    int pid;
    int state;
    string stateToString;

    /** 
     * 
     * Sets pid to the fisrt available pid from pidStore
     * 
     */
    void setpid()
    {
        for (int i = 0; i < 1000; ++i)
        {
            if (!pidStore[i])
            {
                pidStore[i] = 1;
                pid = i + 100; // assuming that the first 100 pids are reserved for OS
                break;
            }
        }
    }
    void setState(int state)
    {
        switch (state)
        {
        case 0:
            this->state = state;
            stateToString = "terminated";
            pidStore[pid - 100] = 0;
            break;
        case 1:
            this->state = state;
            stateToString = "ready"; // assuming same as creating/new
            break;

        case 2:
            this->state = state;
            stateToString = "running";
            break;

        case 3:
            this->state = state;
            stateToString = "waiting";
            break;

        default:
            throw std::invalid_argument("received invalid state number; valid numbers [0-3]");
            break;
        }
    }

public:
    bool static *pidStore;

    void init (string name, int atime, int ptime)
    {
        this->name = name;
        this->atime = atime;
        this->ptime = ptime;

        setpid(); 
        //In Unix-like operating systems a process gets its PID right after creation 
        //Therefore, the PID sequence may differ from the actual order of execution
        //Check linux/include/linux/pid.h and Wikipedia page on Process identifier        
        
        setState(1);
    }
    /**
     * 
     * print all for debugging
     * 
     */
    friend std::ostream &operator<<(std::ostream &os, const Process &process)
    {
        os << "Name: " << process.name << "\t\t\t\t\t | PID: " << process.pid
           << "\nArrival time: " << process.atime << "\t\t\t | Processing time: " << process.ptime
           << "\npidStore: " << process.pidStore << " | Value: " << *process.pidStore
           << "\nState: " << process.state << " " << process.stateToString;
        return os;
    }
    string getName(){
        return this->name;
    }
    void getTime(int &atime,int &ptime){
        atime=this->atime;
        ptime=this->ptime;
    }
    ~Process(){
        pidStore[pid]=0; // release pid
        setState(0); // terminated
    }
    friend struct CompareATime;
    friend struct ComparePTime;
};

void scheduler(Process *ps, unsigned int len, int algo);
