#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<Arduino.h>

bool horn_cmpstr_ard(string a_ch,char b_ch[])
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

string h_pinmode(vector<string> cmdstr){
    if(cmdstr.size()<2){
        return "Missing Parameter";
    }
    uint8_t pin=atoi(cmdstr[0].c_str());
    uint8_t mode_in;
    if(horn_cmpstr_ard(cmdstr[1],"INPUT")){
        mode_in=INPUT;
    }else if(horn_cmpstr_ard(cmdstr[1],"OUTPUT")){
        mode_in=OUTPUT;
    }else{
        return "illegal mode";
    }
    pinMode(pin,mode_in);
    return "OK";
}
string h_pinwrite(vector<string> cmdstr){
    if(cmdstr.size()<2){
        return "Missing Parameter";
    }
    uint8_t pin=atoi(cmdstr[0].c_str());
    uint8_t mode_in;
    if(horn_cmpstr_ard(cmdstr[1],"HIGH")){
        mode_in=HIGH;
    }else if(horn_cmpstr_ard(cmdstr[1],"LOW")){
        mode_in=LOW;
    }else{
        return "illegal mode";
    }
    digitalWrite(pin,mode_in);
    return "OK";
}



string serial_bridge(vector<string> cmdstr){
    Serial2.begin(115200);
    while(1){
        if(Serial.available()>0){
            Serial2.write(Serial.read());
        }
        if(Serial2.available()>0){
            Serial.write(Serial2.read());
        }
    }
    return "FAIL";
}

void setup_lib_arduino(vector<string> &base_func_name,vector<long> &base_func_addr){
    base_func_name.push_back("pinmode");
    base_func_addr.push_back((long)h_pinmode);

    base_func_name.push_back("pinwrite");
    base_func_addr.push_back((long)h_pinwrite);

    base_func_name.push_back("serial_bridge");
    base_func_addr.push_back((long)serial_bridge);
}