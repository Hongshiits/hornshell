
#include<string>
#include<cstring>
#include<vector>
#include<iostream>
#include<algorithm>
#include<stdlib.h>



bool horn_cmpstr(char a_ch,char b_ch){
    string a_in;
    string b_in;
    a_in.push_back(a_ch);
    b_in.push_back(b_ch);
    //cout<<"split cmp"<<a_in.c_str()<<" "<<b_in.c_str()<<endl;
    if(strcmp(a_in.c_str(),b_in.c_str())!=0){
        //cout<<"cmp False"<<endl;
        return false;
    }else{
        //cout<<"cmp True"<<endl;
        return true;
    }


}


vector<string> horn_split(string cm_str,char *get_cut_str){
    cout<<"legacy split........"<<endl;

    vector<string> para_vstr;
    char *cut_str=get_cut_str;
    int temp_ind=0,char_num_temp=0;
    string::iterator last_cm_str=cm_str.begin();
    while((cm_str.begin()+temp_ind-1)!=cm_str.end()){

        string temp_str;
        /*
        if(cut_str[temp_ind]=="\""){
        	if(cut_str[0]==get_cut_str[0]){
        		cut_str[0]="\"";
			}else{
				cut_str[0]=" ";
			}
		}
		*/

        if(cm_str[temp_ind]!=cut_str[0]){
            if(cm_str[temp_ind]!=' ')
            {
                temp_str.push_back(cm_str[temp_ind]);
            }
            //cout<<cm_str[temp_ind]<<endl; //
            char_num_temp++;
        }
        else{
            string in_temp_str(last_cm_str,last_cm_str+char_num_temp);
            para_vstr.insert(para_vstr.end(),in_temp_str);
            last_cm_str=last_cm_str+char_num_temp+1;
            char_num_temp=0;

        }
        if((cm_str.begin()+temp_ind)==cm_str.end()){
            string in_temp_str(last_cm_str,last_cm_str+char_num_temp);
            char_num_temp=0;
            para_vstr.insert(para_vstr.end(),in_temp_str);
        }
        temp_ind++;
    }

    //cout<<para_vstr.size()<<endl;
    /*
    for(int i=0;i<para_vstr.size();i++){
        cout<<"vstr "<<para_vstr[i]<<endl;
    }
    */
    return para_vstr;
}


vector<string> horn_split_v2(string cm_str){
    cout<<"split v2:cm_str:"<<cm_str<<endl;

    vector<string> back_str;
    int flag=0;
    while(flag<cm_str.size()){
        string temp;
        while(flag<cm_str.size()){
            if(cm_str[flag]!='\n'&&cm_str[flag]!='\0'){
                if(cm_str[flag]!=' '){

                    if(horn_cmpstr(cm_str[flag],'\"')){
                        //cout<<"split: found \""<<endl;
                        flag++;
                        while(!horn_cmpstr(cm_str[flag],'\"')){
                            temp.push_back(cm_str[flag]);
                            flag++;
                        }
                        flag++;
                        continue;

                    }else{
                        temp.push_back(cm_str[flag]);
                        flag++;
                    }
                }else{
                    flag++;
                    break;
                }
            }else{
                flag++;
                break;
            }
        }
        back_str.push_back(temp);

    }

    return back_str;



}



