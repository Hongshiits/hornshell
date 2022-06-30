#include<string>
#include<cstring>
#include<vector>
#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<thread>
#include<signal.h>
#include<setjmp.h>
#include<stdarg.h>
#include<fstream>
using namespace std;





//split
//#include"h_split.h"


//func menu
vector<string> base_func_name;
vector<long> base_func_addr;

//var
#include"h_var.h"



//func
//#include"h_func.h"
//#include"horn_nps_conn.h"
#include"demo/rasp-interface/app_head.h"


//shell (entrence)
#include"h_shell.h"

//func init

int init_map(){
	setup_lib_basic(base_func_name,base_func_addr);
	init_varsys_func(base_func_name,base_func_addr);
	//setup_nps_func(base_func_name,base_func_addr);
    setup_lib_shell(base_func_name,base_func_addr);
    setup_lib_app(base_func_name,base_func_addr);
	return 100;
}

//finder(focous)

//#include"h_finder.h"



//start execute


void start_execute(vector<string> &cmd_stat_inner){  
    ifstream in("start.hsbat");
    string strbat;
    if (in)
    {
	    while (getline(in,strbat)){
		    cmd_stat_inner.push_back(strbat);
	    }
    }else{
	    cout << "no such file" << endl;
    }
}






//interface(change with scence)

int main(){

    cout<<"Hornshell dev version period dc7 Linux with thread safe"<<endl
    <<"Compile 2022 May,Listening to rain."<<endl
    <<"buid G++ gcc version 9.3.0 (Ubuntu 9.3.0-17ubuntu1~20.04/WSL)"<<endl
    <<"Thread model: posix"<<endl
    <<"x86_64-linux-gnu"<<endl
    <<"Debug version"<<endl;

	cout<<"init map stuation:"<<init_map()<<endl;
	//shell("func_menu");


    thread exestat_nthr(exestat);
    exestat_nthr.detach();
    cout<<"keep executer enabled"<<endl;
    cmd_stat.push_back("func_menu");
    
    start_execute(cmd_stat);

	while(1){
        TRY
        
        try{
            string cm_str;
            cout<<(long)shell<<"<";
            getline(cin,cm_str);
            cout<<"cmd:"<<cm_str<<endl;
            if(cm_str[0]=='\n'||cm_str[0]==' '||cm_str[0]==NULL){
                continue;
            }
            shell(cm_str);
        }catch(exception &e){
            cout<<"exception"<<endl;
        }
    
    
        END_TRY
    

    
	}



	/*
	while(1){
        string in_str;
        getline(cin,in_str);
        vector<string> out_str(horn_split_v2(in_str));
        for(int i=0;i<out_str.size();i++){
            cout<<out_str[i]<<endl;
        }


	}
    */


    return 0;
}

