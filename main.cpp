/* 
 * File:   main.cpp
 * Author: Oscar kai
 *
 * Created on May 8, 2019, 12:09 AM
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

#define DEBUG 0 //print details for debug

#define FCFS 0  //first come first-served scheduling
#define SJN 0   //shortest-job-next scheduling
#define SRTFS 0 //shortest-remaining-time-first scheduling
#define PS 0    //priority scheduling
#define RR 0    //round-robin scheduling

#define QUAN_TIME 3 //quantum time

using namespace std;

typedef struct _process{
    string id;
    int priority;
    int burst_time;
    int arr_time;
    int waiting_time;
    int ta_time;
    int response_time;
    bool response;  //for calculate response time, true after first burst time -1
    
} PD;

struct priority_sort{
    bool operator()(const _process& PD1, const _process& PD2){
        return (PD1.priority < PD2.priority);
    }
};

struct burst_sort{
    bool operator()(const _process& PD1, const _process& PD2){
        return (PD1.burst_time < PD2.burst_time);
    }
};

typedef enum{Idle, Busy, ContextSwitch}STATUS;

typedef struct _cpu{
    PD thread1;
    STATUS status;
} CPU;

int average(vector<PD> Processes){
}

int main(){
    string filename;
    string data;
    vector<PD> Processes;
    vector<PD> Waiting_Processes;
    unsigned int count;     // count for process list
    unsigned int t = 0;     // time

    int job_done = 0;
    float throughput = 0.0;
    
    filename = "data_1.txt";
    ifstream input_file;
    input_file.open(filename); //open input file for read 
    
    while(input_file >> data){
        // input_file data format: PID priority burst arrival
        if(data.find("P") == 0){
            PD temp_pd;
            temp_pd.id = data;

            input_file >> data;
            temp_pd.priority = stoi(data);

            input_file >> data;
            temp_pd.burst_time = stoi(data);

            input_file >> data;
            temp_pd.arr_time = stoi(data);

            temp_pd.waiting_time = 0;
            temp_pd.ta_time = 0;
            temp_pd.response_time = 0;
            temp_pd.response = false;
            Processes.push_back(temp_pd);
        }
    }
    
    //=========================start simulation===============================//
    
    CPU cpu1; //make a virtual cpu
    
    count = 0; //count for Processes
    t = 0;     //time 
    Waiting_Processes.clear();


    int context_switch = 0; //number of context switch
    int quantum = QUAN_TIME;        //quantum time    

    cpu1.status = Idle; //initial cpu1 are in Idle status  

    //write dynamic throughput output 
    ofstream throughput_output;
    throughput_output.open("throughput_1.txt"); //open output file for write
    throughput_output << "time\tjob done\tthroughput" << endl;
    while(true){
   
        while(Processes[count].arr_time == t){
            Waiting_Processes.push_back(Processes[count]);
            if(count < Processes.size()) count++;
        }
        
#if SRTFS == 1 || SJN == 1      
        sort(Waiting_Processes.begin(), Waiting_Processes.end(), burst_sort());
#elif PS == 1
        sort(Waiting_Processes.begin(), Waiting_Processes.end(), priority_sort());
#endif        
        // process in thread, burst time -1
        if(cpu1.status == Busy){
                
            cpu1.thread1.burst_time -= 1; 
            
            //the process first time being executed
            if(cpu1.thread1.response == false) {
                //calculate response time
                cpu1.thread1.response_time = t - cpu1.thread1.arr_time;
                cpu1.thread1.response = true;
            }
#if RR == 1            
            quantum -= 1;            
            //check one more condition for round robin quantum == 0 
            if(cpu1.thread1.burst_time == 0 || quantum == 0) {
#elif SRTFS == 1
            if(cpu1.thread1.burst_time == 0 || cpu1.thread1.burst_time > Waiting_Processes[0].burst_time) {      
#endif
                if(cpu1.thread1.burst_time == 0) {

                    job_done += 1; //job done ++
                    //turnaround time = finish time - arrive time
                    cpu1.thread1.ta_time = t - cpu1.thread1.arr_time;

                    //write back waiting time and burst time
                    for(int i = 0; i < Processes.size(); i ++){
                        if(cpu1.thread1.id == Processes[i].id){
                            Processes[i].ta_time = cpu1.thread1.ta_time;
                            //waiting time = turn around time - burst time
                            Processes[i].waiting_time = Processes[i].ta_time - Processes[i].burst_time;
                            Processes[i].response_time = cpu1.thread1.response_time;
                        }
                    }
                    
                    if(Waiting_Processes.size() == 0) cpu1.status = Idle; //let cpu in status state
                    else {
                            quantum = QUAN_TIME; //reset quantum time for new loaded processs

                            cpu1.thread1 = Waiting_Processes.front();
                            Waiting_Processes.erase(Waiting_Processes.begin());

                            cpu1.status = Busy;  
                    }
                }
#if RR == 1 || SRTFS == 1                
                else {
                    cpu1.status = ContextSwitch;   
                }      
            }
#endif            
        }        
        else if(cpu1.status == Idle){
            //load process in waiting queue into cpu1
            if(!Waiting_Processes.empty()){

                quantum = QUAN_TIME; //reset quantum time for new loaded processs

                cpu1.thread1 = Waiting_Processes.front();
                Waiting_Processes.erase(Waiting_Processes.begin());

                cpu1.status = Busy;    
            }
        }
        else if(cpu1.status == ContextSwitch){
            
            context_switch += 1; //record number of context switch
#if DEBUG == 1            
            cout <<"push back " << cpu1.thread1.id << " b:" << cpu1.thread1.burst_time ;
#endif
            //Context Switch 
            Waiting_Processes.push_back(cpu1.thread1);
            cpu1.thread1 = Waiting_Processes.front();
            Waiting_Processes.erase(Waiting_Processes.begin());
#if DEBUG == 1
            cout << " cpu get " << cpu1.thread1.id << " b:" << cpu1.thread1.burst_time  << endl;;
#endif

#if RR == 1            
            quantum = QUAN_TIME;
#endif            
            cpu1.status = Busy;
        }

#if DEBUG == 1
        cout << "t=" << t << " ";
        if(cpu1.status == ContextSwitch) cout << "Switch\t";
        else if(cpu1.status == Busy) cout << "Busy\t";
        else cout << "Idle\t";
        cout << cpu1.thread1.id << ":" <<cpu1.thread1.burst_time << " " ;        
        cout << "q.size="<< Waiting_Processes.size() << " j.done= " << job_done;
#if RR == 1
        cout << " quantum=" << quantum ;
#endif
#if SRTFS == 1
        cout << " c.switch=" << context_switch << endl;
#endif
#endif        
        //while loop terminate condition
        if(Waiting_Processes.empty() && cpu1.status == Idle && count == Processes.size()) break;
        
        throughput = (t == 0)? 0 : (float)job_done/t; //calculate current throughput
        throughput_output << t << "\t" << job_done << "\t" << throughput << endl;
        t++;
    }
    throughput_output.close();
    
    //=====================output details=====================================//
    cout << endl; 
    cout << filename << endl;
#if FCFS == 1
    cout << "First-Come, First-Served(FCFS) Scheduling" << endl;
#elif SJN == 1
    cout << "Shortest-Job-Next(SJN) Scheduling" << endl;
#elif SRTFS == 1
    cout << "Shortest-Remaining-Time-First Scheduling" << endl;
#elif PS == 1
    cout << "Proiority Scheduling" << endl;
#elif RR == 1
    cout << "Round-Robin Sceduling" << endl;
#endif                
    cout << "=========================================" << endl;
    cout << "Total context switch = " << context_switch << endl;
    cout << "Total time taken = " << t << endl;
    cout << "Average throughput = " << throughput << endl;

    
    float avg_waiting_time = 0;
    float avg_ta_time = 0;
    float avg_response_time = 0;
    for(int i = 0; i < Processes.size(); i++){
        avg_waiting_time += (float)Processes[i].waiting_time;
        avg_ta_time += (float)Processes[i].ta_time;
        avg_response_time += (float)Processes[i].response_time;
    }
    avg_waiting_time = avg_waiting_time/Processes.size();
    avg_ta_time = avg_ta_time/Processes.size();
    avg_response_time = avg_response_time/Processes.size();

    cout << "Average waiting time = " << avg_waiting_time << endl;
    cout << "Average turn around time = " << avg_ta_time << endl;
    cout << "Average response time = " << avg_response_time << endl;
    cout << "=========================================" << endl;

    //===================write output file====================================// 
    ofstream output_file;
    output_file.open("output_1.txt"); //open output file for write
    output_file << "id\tprio\tburst\tarrive\twaiting\tta time\tresponse" << endl;
    for(int i = 0; i < Processes.size(); i ++){
        output_file << Processes[i].id << "\t" << Processes[i].priority << "\t";
        output_file << Processes[i].burst_time << "\t" << Processes[i].arr_time << "\t";
        output_file << Processes[i].waiting_time << "\t" << Processes[i].ta_time << "\t";
        output_file << Processes[i].response_time << endl;
    }
    output_file.close();
    
    return 0;
}

