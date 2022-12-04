#include <stdio.h>
#include<iostream>
#include <string.h>
#include<stdlib.h>
#include<vector>
#include<algorithm>
using namespace std;
struct Task{
	int id;                 // 任务id
	int pri;                // 优先级
	int release_time;       //释放时间
    int excute_time;        //执行时间
	   
}; 
//由于使用sort排名需要提供bool cmp()函数，所以下面定义cmp函数
bool  cmp(Task a,Task b);
void init();
void out_cal();
void TaPSA();
void result_print();
void cal_p(int num);
void graph_update(int id);
int check_row(int id);
int max_set(int id);

const int task_num = 5;               //任务数量
vector<Task> tasks,task_last_cycle;
//int prio[10] = {-1 , 3, 8, 5, 2, 8, 4, 10, 1};
int prio[task_num + 1] = {-1};
int task_excute_time[task_num + 1] = {0, 1, 1, 2, 1, 1};
int graph[task_num + 1][task_num + 1];
int graph_temp[task_num + 1][task_num + 1];
int out[task_num + 1] = {0};


int main(){

    init();
    cal_p(task_num);
    for(int i = 1; i<= task_num; i++)
        cout<<prio[i]<<"  ";
    cout<<endl;
    TaPSA();
	//sort(首位元素地址，末尾元素地址加一，cmp) 
    
    result_print();


	return 0;
}

void init()
{
    memset(graph,0,sizeof(graph));
    memset(prio, -1, sizeof(prio));
    memset(out,0,sizeof(out));

    graph[1][4] = 1;
    graph[1][5] = 1;
    graph[2][4] = 1;
    graph[2][5] = 1;
    graph[3][5] = 1;
  

    memcpy(graph_temp, graph, sizeof(graph));
   
    out_cal();
    for(int i = 0; i <= task_num; i++)
    {
        Task temp;
        temp.id = i;
        temp.pri = prio[i];
        temp.excute_time = task_excute_time[i];
        temp.release_time = 0;
        if(i == 2)
            temp.release_time = 3;
        tasks.push_back(temp);
    }
}

void TaPSA()
{
    sort(tasks.begin() + 1, tasks.begin() + task_num , cmp);

}
void cal_p(int num)
{
    int temp = num;
    while(temp)
    {
        for(int i = 1; i <= num; i++)
        {   
            if(prio[i] == -1)
            {
                if(check_row(i))    
                {
                    prio[i] = tasks[i].excute_time + out[i] + max_set(i);
                  //  cout<<"消除"<<i<<"  "<<tasks[i].excute_time<<" "<<out[i]<<endl;
                    tasks[i].pri = prio[i];
                    graph_update(i);
                    temp--;
                }
            }
        }
    }
}

void graph_update(int id)
{
    for(int i = 1; i <= task_num; i++)
    {
        graph_temp[i][id] = 0;
    }
}
int max_set(int id)
{
    if(!out[id])
        return 0;
    else
    {
        int max_prio = -1;
        for(int j = 1; j <= task_num; j++)
        {
            if(graph[id][j])
            {
                if(prio[j] > max_prio)
                    max_prio = prio[j];
            }
        }
        return max_prio;
    }
}
void out_cal()
{
    int sum;
    for(int i = 1; i <=task_num; i++)
    {
        sum = 0;
        for(int j = 1; j <= task_num; j++)
        {
            if(graph[i][j])
                sum++;
        }
        out[i] = sum;
    }

}
int check_row(int id)               //检查可清除图
{
    int res = 1;
    for(int j = 1; j <= task_num; j++)
    {
        if(graph_temp[id][j])
        {    
            res = 0;
            break;
        }
    }
    return res;
}
void result_print ()
{
    for(int i = 1; i <= task_num ; i++)
    {
        //cout<<tasks[i].id <<"  " << tasks[i].pri << "  "<<tasks[i].release_time<<" "<<tasks[i].excute_time<<endl;
        cout<<tasks[i].id <<"  ";
    }
}


bool  cmp(Task a,Task b){
	if(a.pri!=b.pri) 
        return a.pri>b.pri;//从大到小a>b,从小到大a<b        ///优先级从小到大
	else if(a.release_time != b.release_time) 
        return a.release_time<b.release_time;              //   释放时间由早到晚
    else if(a.excute_time != b.excute_time)
        return a.excute_time > b.excute_time;
    else
        return a.id < b.id; 
	
}
void graph_print()
{
    for(int i = 1; i<=task_num; i++)
    {
        for(int j =1; j<=task_num;j ++)
            cout<<graph_temp[i][j]<<" ";
        cout<<endl;
    }
}