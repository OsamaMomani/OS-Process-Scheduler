class Process
{
    string name;
    int atime; // arrival time
    int ptime; // processing time
    bool static *pidStore;
    int pid;
    int state;
    string stateToString;
    Process(string name, int atime, int ptime)
    {
        this->name  = name;
        this->atime = atime;
        this->ptime = ptime;
        setpid();
        setState(1);
    }

    /** 
     * 
     * Sets pid to the fisrt available pid from pidStore
     * 
     */
    void setpid(){
        if (!pidStore) // check if not created yet
            pidStore= new bool[1000];
        
        for(int i=0; i<1000; ++i){
            if(!pidStore[i]){
                pidStore[i]=1;
                pid= i + 100; // assuming that the first 100 pids are reserved for OS
                break;
            }
        }
    }
    void setState(int state){
        switch (state)
        {
        case 0:
            this->state=state;
            stateToString="terminated";
            pidStore[pid-100]=0;
            break;
        case 1:
            this->state=state;
            stateToString="ready";  // assuming same as creating/new
            break;

        case 2:
            this->state=state;
            stateToString="running";
            break;

        case 3:
            this->state=state;
            stateToString="waiting";
            break;

        default:
            throw std::invalid_argument( "received invalid state number; valid numbers [0-3]" );
            break;
        }
    }
};