#include "process.h"

struct CompareATime
{
    bool operator()(Process const &p1, Process const &p2)
    {
        return p1.atime > p2.atime;
    }
};

struct ComparePTime
{
    bool operator()(Process const &p1, Process const &p2)
    {
        return p1.ptime > p2.ptime;
    }
};

void scheduler(Process *ps, unsigned int len, int algo)
{
    ofstream log("log.txt", std::ios_base::app); // append to log file
    ofstream out("out.txt");                        // create out file
    // get run date
    time_t now = time(0);
    char *dt = ctime(&now);

    log << "\n===================== Start Logging =====================\n\t" << dt << endl;
    switch (algo)
    {
    case 1:
    {
        // create two queues one for get (A) and the another for (B)
        priority_queue<Process, vector<Process>, CompareATime> q1, q2;
        for (int i = 0; i < len; ++i)
        {
            q1.push(ps[i]);
            q2.push(ps[i]);
        }
        // (A) print names of processes by order
        for (int i = 0; i < len; ++i)
        {            
            Process p = q2.top();

            out<<p.getName();
            q2.pop();
        }
        out<<endl;

        // (B) print processes details by order
        for (int i = 0; i < len; ++i)
        {
            Process p = q1.top();

            int response, turnaround, delay, atime, ptime;
            p.getTime(atime, ptime);
            int static current = atime ; // current instance of time
            response=delay=current-atime>0? current-atime : 0;
            current += ptime;
            turnaround=delay+ptime;
            out << p.getName() << ": (response=" << response << 
            ", turnaround=" << turnaround << 
            ", delay=" << delay << ")\n";
            log << p << endl;
            q1.pop();
        }
        break;
    }
    default:
        throw invalid_argument("received invalid Algo number");
        break;
    }
}