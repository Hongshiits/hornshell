#include<Arduino.h>
#include<string>
#include<cstring>
#include<vector>
#include<iostream>
#include<algorithm>
#include<stdlib.h>
using namespace std;

void h_getline(string &str){
  while(Serial.available()<=0)
  {}
  while(Serial.available()>0){
    str.push_back(Serial.read());
    delay(2);
  }

}


//split
#include"h_split.h"


//func menu
vector<string> base_func_name;
vector<long> base_func_addr;

//var
#include"h_var.h"



//func
#include"h_func.h"
//#include"horn_nps_conn.h"
#include"h_arduino.h"

//func init

int init_map(){
	setup_lib_basic(base_func_name,base_func_addr);
	init_varsys_func(base_func_name,base_func_addr);
	//setup_nps_func(base_func_name,base_func_addr);
  setup_lib_arduino(base_func_name,base_func_addr);
	return 100;
}

//finder(focous)

#include"h_finder.h"




//shell (entrence)

int shell(string cm_shell_str){

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



}





void setup() {
  Serial.begin(115200);

  cout<<"Hornshell dev version period dc6 for ESP32 Arduino"<<endl
    <<"Compile 2022 April,Look at the sun rising"<<endl
    <<"Debug version"<<endl;

	cout<<"init map stuation:"<<init_map()<<endl;
	shell("func_menu");
}

void loop() {
  string cm_str;
  cout<<(long)shell<<"<";
  while(1){
    h_getline(cm_str);
    
    if(cm_str.empty()){
      continue;
    }else{
      break;
    }
  }
  cout<<"cmd:"<<cm_str<<endl;
  shell(cm_str);

}