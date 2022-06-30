
#include<string>
#include<vector>


#include"h_split.h"


void trim(string &s);
//finder(focous)

long horn_finder(vector<string> func_name){
    long back_addr=0;
    for(int i=0;i<func_name.size();i++){
        cout<<"finder func input:"<<func_name[i]<<"."<<endl;
    }
    string check_func=func_name[0];
    trim(check_func);
    //check_func.erase(check_func.end()-1);
    //cout<<"finder: func name "<<check_func<<endl;

	for(int i=0;i<base_func_name.size();i++){
		string find_func_name_temp=base_func_name[i];

		//cout<<"finder checking func:"<<find_func_name_temp<<endl;
		if(0==check_func.compare(find_func_name_temp)){

			back_addr=base_func_addr[i];
			break;

		}

	}
	//cout<<"finder:  backaddr "<<back_addr<<endl;
	return back_addr;
}


 void trim(string &s)
 {
   if(!s.empty()){
         s.erase(0,s.find_first_not_of(" "));
         s.erase(s.find_last_not_of(" ") + 1);
     }
}

