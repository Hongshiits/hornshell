#include<vector>
#include<string>
using namespace std;

vector<string> var_name_list;
vector<long> var_addr;




bool horn_cmpstr_varch(string a_ch,char b_ch[])
{
    //cout<<"split cmp"<<a_in.c_str()<<" "<<b_in.c_str()<<endl;
    if(strcmp(a_ch.c_str(),b_ch)!=0){
        //cout<<"cmp False"<<endl;
        return false;
    }else{
        //cout<<"cmp True"<<endl;
        return true;
    }
}
bool horn_cmpstr_varch(string a_ch,string b_ch)
{
    //cout<<"split cmp"<<a_in.c_str()<<" "<<b_in.c_str()<<endl;
    if(strcmp(a_ch.c_str(),b_ch.c_str())!=0){
        //cout<<"cmp False"<<endl;
        return false;
    }else{
        //cout<<"cmp True"<<endl;
        return true;
    }
}


string show_var(vector<string> var_name_str){
    if(horn_cmpstr_varch(var_name_str[0],"all")){
        if(var_name_list.size()<=0){
            cout<<"no var in list"<<endl;
            return "NO VAR";
        }else{
            for(int i=0;i<var_name_list.size();i++){
                cout<<var_name_str[i]<<" "<<var_addr[i]<<endl;
            }
            return "OK";
        }
    }else if(!var_name_str[0].empty()){
        for(int i=0;i<var_name_list.size();i++){
            if(horn_cmpstr_varch(var_name_str[i],var_name_str[0])){
                cout<<var_name_str[i]<<" "<<var_addr[i]<<endl;
                return "OK";
            }
        }
    }else{
        cout<<"empty argue"<<endl;
        return "NO ARGUE";
    }
}

string creat_long_var(vector<string> in_str){
    var_name_list.push_back(in_str[0]);
    long *temp_var=new long;
    var_addr.push_back((long)temp_var);
    return "OK";
}

string set_value(vector<string> str){
    if(str.size()<3){
        return "Missing Parameters";
    }
    string var_name_in=str[1];
    string var_type=str[0];
    string var_value=str[2];
    long var_addr_inner=NULL;
    for(int i=0;i<str.size();i++){
        if(horn_cmpstr_varch(var_name_list[i],var_name_in)){
            var_addr_inner=var_addr[i];
            break;
        }
    }
    if(horn_cmpstr_varch(var_type,"long")){
        long *temp_var;
        temp_var=(long*)var_addr_inner;
        *temp_var=atoi(var_value.c_str());
    }else if(horn_cmpstr_varch(var_type,"string")){
        string *temp_var;
        temp_var=(string*)var_addr_inner;
        *temp_var=var_value;
    }else{
        return "Fail";
    }

    return "OK";
}

string show_value(vector<string> str){
    string var_type=str[0];
    string var_name_inner=str[1];
    long var_addr_inner=NULL;
    for(int i=0;i<str.size();i++){
        if(horn_cmpstr_varch(var_name_list[i],var_name_inner)){
            var_addr_inner=var_addr[i];
            break;
        }
    }
    if(horn_cmpstr_varch(var_type,"long")){
        long *temp_var;
        temp_var=(long*)var_addr_inner;
        cout<<*temp_var<<endl;
    }else if(horn_cmpstr_varch(var_type,"string")){
        string *temp_var;
        temp_var=(string*)var_addr_inner;
        cout<<*temp_var<<endl;
    }else{
        return "Fail";
    }

    return "OK";
}






void init_varsys_func(vector<string> &base_func_name,vector<long> &base_func_addr){
    base_func_name.push_back("show_var");
	base_func_addr.push_back((long)show_var);


    base_func_name.push_back("long_var");
	base_func_addr.push_back((long)creat_long_var);

	base_func_name.push_back("set_value");
	base_func_addr.push_back((long)set_value);

	base_func_name.push_back("show_value");
	base_func_addr.push_back((long)show_value);


}
