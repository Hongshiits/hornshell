#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<windows.h>
#include<thread>

#include"h_finder.h"



string new_thread(vector<string> cmdstr){
	vector<string> temp_inner_nthr_arg;
	for(int i=1;i<cmdstr.size();i++){
		temp_inner_nthr_arg.push_back(cmdstr[i]);
	}

	vector<string> temp_inner_nthr;
	temp_inner_nthr.push_back(cmdstr[0]);

	thread thr_inner((string (*)(vector<string>))horn_finder(temp_inner_nthr),temp_inner_nthr_arg);

	cout<<"thread running......"<<endl;
	thr_inner.detach();
	return "THREAD END";
}


string addr_func(vector<string> cmdstr){
    string funcaddr_in=cmdstr[0];
    long addr_in=atoi(funcaddr_in.c_str());
    vector<string> cm_para_vec(cmdstr.begin()+1,cmdstr.end());

    cout<<"addr_func:legacy addr func excution"<<endl;
    cout<<"addr_func:exe func addr"<<addr_in<<endl;
	string (*execute_func)(vector<string>)=(string (*)(vector<string>))addr_in;
    string func_back=execute_func(cm_para_vec);
    cout<<"addr_func:func message:"<<func_back<<endl;

    return "OK";
}
/*
string import_dll(vector<string> cmdstr) //import dll
{
    string dll_name=cmdstr[0];
    HMODULE module = LoadLibrary(dll_name.c_str());
    if (module == NULL)
    {
        cout<<"Failed to load "<<dll_name<<endl;
        return "Fail";
    }
    typedef int(*AddFunc)(vector<string>&,vector<long>&);
    AddFunc add;
    add=(AddFunc)GetProcAddress(module,"setup_lib_basic");
    add(base_func_name,base_func_addr);
    return "OK";
}
*/

string func_menu(vector<string> ocmdstr){ //show loaded func
    cout<<"func menu"<<endl;
	for(int i=0;i<base_func_name.size();i++){

		cout<<base_func_name[i]<<" "<<base_func_addr[i]<<endl;
	}
    return "OK";
}

string h_sys(vector<string> cmdstr){ //use system commond line
	string cmdstr_inner=cmdstr[0];
	system(cmdstr_inner.c_str());
	return "OK";
}
string h_asicll(vector<string> out_str){ //show char's asicll
	string a_str=out_str[0];
    int a=(int)a_str[0];
    cout<<a<<endl;
    return "OK";
}
string h_print(vector<string> out_str){ //print string
    cout<<out_str[0]<<endl;
    return "OK";
}
string h_erro(vector<string>){ //pause or stop all program
	cout<<"erro"<<endl;
	string cont_if;
	cin>>cont_if;
	if(cont_if=="Y"){
		return "OK";
	}else{
		return 0;
	}
}


void setup_lib_basic(vector<string> &base_func_name,vector<string(*)(vector<string>)> &base_func_addr){
    base_func_name.push_back("print");
	base_func_addr.push_back(h_print);

	base_func_name.push_back("asicll");
	base_func_addr.push_back(h_asicll);

	base_func_name.push_back("erro");
	base_func_addr.push_back(h_erro);

	base_func_name.push_back("sys");
	base_func_addr.push_back(h_sys);

	//base_func_name.push_back("importdll");
	//base_func_addr.push_back(import_dll);

	base_func_name.push_back("func_menu");
	base_func_addr.push_back(func_menu);

	base_func_name.push_back("addr_func");
	base_func_addr.push_back(addr_func);

	base_func_name.push_back("new_thread");
	base_func_addr.push_back(new_thread);
}
