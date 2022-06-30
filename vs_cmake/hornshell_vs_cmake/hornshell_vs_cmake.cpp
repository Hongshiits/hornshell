// hornshell_vs_cmake.cpp : Defines the entry point for the application.
//

#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<windows.h>


using namespace std;

//split
#include"h_split.h"


//func menu
vector<string> base_func_name;
vector<string(*)(vector<string>)> base_func_addr;

//var
#include"h_var.h"



//func
#include"h_func.h"
//#include"horn_nps_conn.h"


//func init

int init_map() {
    setup_lib_basic(base_func_name, base_func_addr);
    init_varsys_func(base_func_name, base_func_addr);
    //setup_nps_func(base_func_name,base_func_addr);
    return 100;
}

//finder(focous)

//#include"h_finder.h"




//shell (entrence)

string shell(string cm_shell_str) {


    vector<string> cm_shell_vec(horn_split_v2(cm_shell_str));
    vector<string> cm_funcname_vec(horn_split_v2(cm_shell_vec[0]));
    vector<string> cm_para_vec(cm_shell_vec.begin() + 1, cm_shell_vec.end());

    for (int i = 0;i < cm_para_vec.size();i++) {
        cout << "vstr " << cm_para_vec[i] << endl;
    }
    //horn_finder(cm_funcname_vec);
    string(*back_addr)(vector<string>) = 0;
    string addr_str = cm_funcname_vec[0];
    back_addr = horn_finder(cm_funcname_vec);    //finder 

    cout << "backaddr:" << back_addr << endl;
    //back_addr=atoi(addr_str.c_str());
    string func_back;


    if (back_addr != 0) {
        cout << "exe func addr" << back_addr << endl;


        try
        {
            string(*execute_func)(vector<string>) = (string(*)(vector<string>))back_addr;

            func_back = execute_func(cm_para_vec);
        }
        catch (const std::exception&)
        {
            cout << "execute erro";
        }

        
        

        cout << "func message:" << func_back << endl;

    }
    else {
        cout << "Failed excution" << endl;
    }


    return func_back;

}





//keep
vector<string> cmd_stat;
void exestat() {
    while (1) {
        while (!cmd_stat.empty()) {
            cout << "keep executer:" << cmd_stat[0] << endl;
            shell(cmd_stat[0]);
            //free(&cmd_stat[0]);
            
            cmd_stat.erase(cmd_stat.begin());
        }
    }
}

void start_exestat() {
    thread thr_exestat(exestat);
    thr_exestat.detach();
}


void push_cmd(string cmd_input) {
    cmd_stat.push_back(cmd_input);
}








//interface(change with scence)

int main() {

    cout << "Hornshell dev version period dc6" << endl
        << "Compile 2022 April,Look at the sun rising" << endl
        << "buid MSVC(Visual Studio 2019 16.11.0)" << endl
        << "Thread model: posix" << endl
        << "x86_64-windows" << endl
        << "Debug version" << endl;

    cout << "init map stuation:" << init_map() << endl;
    start_exestat();
    push_cmd("func_menu");
    shell("func_menu");





    while (1) {
        string cm_str;
        cout << shell << "<";
        getline(cin, cm_str);
        if (cm_str.empty()) {
            continue;
        }
        cout << "cmd:" << cm_str << endl;
        
        cout << shell(cm_str);
        
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
