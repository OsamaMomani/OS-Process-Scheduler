#include "process.h"

bool *Process::pidStore= new bool[1000]; // assuming 1000 is the maximum number of pids
//The maximum value of the pid on a linux system can be found $cat /proc/sys/kernel/pid_max
int main(){
    freopen("in.txt","r",stdin);

    int n;
    cin>>n;

    Process *ps= new Process [n];
    for(int i=0; i<n; ++i){
        string name;
        int atime, ptime;
        cin>>name>>atime>>ptime;
        ps[i].init(name, atime, ptime);
    }
    scheduler(ps, n, 1);

}