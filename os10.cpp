#include<iostream>
using namespace std;

class os10
{
private:
    int noOfProcess,end_time,queue1_size,queue2_size,total_time,QT;
    struct processes
    {
        int burst_time;
        int arrival_time;
        int rbt;
        int completed_time;
        int id;
        bool placed;
    }*process,*queue1,*queue2;
public:
    os10();
    void get_input();
    void processIN();
    void put_result();
    void clear();
    void sort(int sel);
    void shortest_job_first(int sel);
    ~os10();
};

os10::os10()
{   
    {
        end_time=0;
        total_time=0;
        QT=2;
        get_input();
        cout<<"Input check";
         processIN();
         put_result();
    }
}

void os10::get_input(){
    cout<<"enter number of process:";
    cin>>noOfProcess;
    queue2_size=noOfProcess;
    process = new processes[noOfProcess];
    queue1 = new processes[noOfProcess];
    queue2 = new processes[noOfProcess];
    for(int i = 0; i < noOfProcess; i++)
    {
        cout<<"enter arrival time and burst time:\n";
        cin>>process[i].arrival_time>>process[i].burst_time;
        process[i].rbt = process[i].burst_time;
        process[i].id = i;
        process[i].placed = false;
        total_time+=process[i].burst_time;
        if(process[i].arrival_time==0){
        queue2[queue2_size]=process[i];
        queue2_size++;
        process[i].placed = true;
        }
    }
}

void os10::processIN(){
    //cout<<"check1";
    //do{
    clear();
    sort(1);
    sort(2);
    for(int i=0;i<noOfProcess;i++){
        if(process[i].placed==false){
            if(process[i].arrival_time<=end_time){
                queue2[queue2_size]=process[i];
                queue2_size++;
            }
        }
    }
    cout<<"\ncheck1"<<queue2_size;
    if(queue1[0].rbt!=0){
       shortest_job_first(1);
       cout<<"\ncheckq1"<<"\n";
    }
    else{
    cout<<"\ncheckq2"<<"\n";
       shortest_job_first(2);
    }
    for(int i = 0; i < queue2_size; i++)
    {
        cout<<"\nsus1\n";
        if((end_time-queue2[i].arrival_time)>=4){
            queue1[queue1_size]=queue2[i];
            for(int j=i;j<queue2_size-1;j++){
                if(j!=queue2_size){
                    queue2[j]=queue2[j+1];
                }
                else{
                    
                }
            }
        }
    }
    cout<<"\net"<<end_time<<".\n";
   // }while(total_time>end_time);
}

void os10::put_result(){
    for(int i = 0; i < noOfProcess; i++)
    {
        cout<<"P"<<i+1<<" | "<<process[i].arrival_time<<" | "<<process[i].burst_time<<" | "
        <<(process[i].completed_time-process[i].arrival_time-process[i].burst_time)
        <<" | "<<(process[i].completed_time-process[i].arrival_time)<<"\n";
    }
    
}

void os10::clear(){
    for(int i = 0; i < queue1_size; i++)
    {
        cout<<"\nsus21\n";
        if(queue1[i].rbt<=0){
            if(i!=queue1_size-1){
            for(int j = i; j <= queue1_size; j++)
            {
                cout<<"\nsus2\n";
                queue1[i]=queue1[i+1];
            }
            }
        if(queue1_size>0)
           queue1_size--; 
        }
    }
    for(int i = 0; i < queue2_size; i++)
    {
        cout<<"\nsus31\n";
        if(queue2[i].rbt<=0){
             if(i!=queue1_size-1){
            for(int j = i; j <= queue2_size; j++)
            {
                cout<<"\nsus3\n";
                queue2[i]=queue2[i+1];
            }
             }
        if(queue2_size>0)
           queue2_size--; 
        }
    }
}

void os10::sort(int sel){
    int size;
    processes temp;
    if (sel == 1) {
        size = queue1_size;
    for(int i=0;i<size;i++)
    {
        cout<<"\nsus4\n";
      for(int j=0;j<size;j++)
      {
          cout<<"\nsus5\n";
        if(queue1[i].rbt<queue1[j].rbt){
          temp = queue1[i];
          queue1[i]=queue1[j];
          queue1[j]=temp;
        }
       }
    }
    }
    else {
    size = queue2_size;
    for(int i=0;i<size;i++)
    {
        cout<<"\nsus6\n";
      for(int j=0;j<size;j++)
      {
          cout<<"\nsus7\n";
        if(queue2[i].rbt<queue2[j].rbt){
          temp = queue2[i];
          queue2[i]=queue2[j];
          queue2[j]=temp;
        }
       }
    }
    }

}

void os10::shortest_job_first(int sel){
    int shortest_rbt = queue1[0].rbt;
    int temp_index =0;
    int close_AT=(queue2[0].arrival_time-end_time);
    for(int i=0; i<=queue1_size; i++){
        cout<<"\nsus8\n";
        if(((queue1[i].arrival_time-end_time)>0)&&(queue1[i].arrival_time-end_time)<close_AT){
            close_AT=(queue1[i].arrival_time-end_time);
        }
    }
    for(int i=0; i<=queue2_size; i++){
        cout<<"\nsus9\n";
        if(((queue2[i].arrival_time-end_time)>0)&&(queue2[i].arrival_time-end_time)<close_AT){
            close_AT=(queue2[i].arrival_time-end_time);
        }
    }
    cout<<"\nclose"<<close_AT<<"\n"; 
    if(sel==1){
        // if(queue1_size>0){
        // for(int i = 1; i < queue1_size; i++)
        // {
        //     if(shortest_rbt>queue1[i].rbt){
        //         shortest_rbt=queue1[i].rbt;
        //         temp_index=i;
        //     }
        // }
        // }
        if(close_AT<=QT&&close_AT!=0){
            if(queue1[temp_index].rbt>=close_AT){
                end_time+=close_AT;
                queue1[temp_index].rbt-=close_AT;
            }
            else
            {
                end_time+=queue1[temp_index].rbt;
                queue1[temp_index].rbt-=queue1[temp_index].rbt;
            }
        }
        else{
            if(queue1[temp_index].rbt>=QT){
                end_time+=QT;
                queue1[temp_index].rbt-=QT;
            }
            else
            {
                end_time+=queue1[temp_index].rbt;
                queue1[temp_index].rbt-=queue1[temp_index].rbt;
            }
        }
        process[queue1[temp_index].id].completed_time=end_time;
    }
    else{
        // if(queue2_size>0){
        // for(int i = 1; i < queue2_size; i++)
        // {
        //     if(shortest_rbt>queue2[i].rbt){
        //         shortest_rbt=queue2[i].rbt;
        //         temp_index=i;
        //     }
        // }
        // cout<<"check for temp"<<temp_index<<"/n";
        // }
        if(close_AT<=QT&&close_AT!=0){
            if(queue2[temp_index].rbt>=close_AT){
                end_time+=close_AT;
                queue2[temp_index].rbt-=close_AT;
            }
            else
            {
                end_time+=queue2[temp_index].rbt;
                queue2[temp_index].rbt-=queue2[temp_index].rbt;
            }
        }
        else{
            cout<<"\nq2"<<queue2[temp_index].rbt<<"kk\n";
            if(queue2[temp_index].rbt>=QT){
                end_time+=QT;
                queue2[temp_index].rbt-=QT;
            }
            else
            {
                end_time+=queue2[temp_index].rbt;
                queue2[temp_index].rbt-=queue2[temp_index].rbt;
            }
        }
        process[queue2[temp_index].id].completed_time=end_time;
    } 
}

os10::~os10()
{
}

main(){
    os10 obj;
}