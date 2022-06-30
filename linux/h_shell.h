#include<string>
#include<iostream>
#include<vector>
#include <signal.h>
#include<setjmp.h>
#include"h_func.h"
#include"CException.h"

using namespace std;

int shell(string cm_shell_str){
    
    TRY

    try{
    
    vector<string> cm_shell_vec(horn_split_v2(cm_shell_str));
    vector<string> cm_funcname_vec(horn_split_v2(cm_shell_vec[0]));
    vector<string> cm_para_vec(cm_shell_vec.begin()+1,cm_shell_vec.end());

    for(int i=0;i<cm_para_vec.size();i++){
        cout<<"vstr "<<cm_para_vec[i]<<endl;
    }
    //horn_finder(cm_funcname_vec);
    long back_addr=0;
    string addr_str=cm_funcname_vec[0];
    back_addr=horn_finder(cm_funcname_vec);

    cout<<"backaddr:"<<back_addr<<endl;
    //back_addr=atoi(addr_str.c_str());

    if(back_addr!=0){
        cout<<"exe func addr"<<back_addr<<endl;
        string (*execute_func)(vector<string>)=(string (*)(vector<string>))back_addr;
        string func_back=execute_func(cm_para_vec);

        cout<<"func message:"<<func_back<<endl;

    }else{
        cout<<"Failed excution"<<endl;
    }



    }catch(...){
        cout<<"shell exception!!!!!"<<endl;
    }

    END_TRY

}



vector<string> cmd_stat;
void exestat(){
    while(1){
        while(!cmd_stat.empty()){
            cout<<"keep executer:"<<cmd_stat[0]<<endl;
            shell(cmd_stat[0]);
            //free(&cmd_stat[0]);
            cmd_stat.erase(cmd_stat.begin());
        }
    }
}





//shell func lib


string exebat(vector<string> cmdstr){
	if(cmdstr.size()<1){
		return "Missing Parameters";
	}
	ifstream in(cmdstr[0].c_str());
	string strbat;
	if (in){
    	while (getline(in,strbat)){
	    	shell(strbat);
    	}
	}else{
    	cout << "no such file" << endl;
        return "Fail";
	}
    return "OK";
}

string h_for(vector<string> cmdstr){
    int times=atoi(cmdstr[0].c_str());
    string temp_inner_for_arg;
    for(int i=1;i<cmdstr.size();i++){
	    temp_inner_for_arg+=cmdstr[i]+" ";
    }
    cout<<"for bat:"<<temp_inner_for_arg<<endl;
    if(times<0){
        while(1){
            shell(temp_inner_for_arg);
        }
    }else
    {
        for(int i=0;i<times;i++){
            shell(temp_inner_for_arg);
        }
    }
    return "OK";
}

void setup_lib_shell(vector<string> &base_func_name,vector<long> &base_func_addr){
    base_func_name.push_back("exebat");
	base_func_addr.push_back((long)exebat);

    base_func_name.push_back("for");
    base_func_addr.push_back((long)h_for);
}