#include <iostream>
#include <dirent.h>
#include<vector>
#include<string>
using namespace std;




/************************************************************
 * Description:
 *     获取dir目录下具有制定后缀名字的所有文件名，
 * parameter:
 *     src_dir:目录路径，例如 "../test"
 *     ext:后缀名,例如".jpg"
 * return；
 *     vector<string>：包含文件名的数组，
 * https://www.cnblogs.com/nickman/p/14029064.html
 * ***********************************************************/
vector<string> GetFiles(const char *src_dir, const char *ext)
{
    vector<string> result;
    string directory(src_dir);
    string m_ext(ext);
    //printf("ext length:%d\n",m_ext.length());
 
    // 打开目录, DIR是类似目录句柄的东西
    DIR *dir = opendir(src_dir);
    if ( dir == NULL )
    {
        printf("[ERROR] %s is not a directory or not exist!", src_dir);
        return result;
    }
 
    // dirent会存储文件的各种属性
    struct dirent* d_ent = NULL;
 
    // linux每个目录下面都有一个"."和".."要把这两个都去掉
    char dot[3] = ".";
    char dotdot[6] = "..";
 
    // 一行一行的读目录下的东西,这个东西的属性放到dirent的变量中
    while ( (d_ent = readdir(dir)) != NULL )
    {
        // 忽略 "." 和 ".."
        if ( (strcmp(d_ent->d_name, dot) != 0) && (strcmp(d_ent->d_name, dotdot) != 0) )
        {
            // d_type可以看到当前的东西的类型,DT_DIR代表当前都到的是目录,在usr/include/dirent.h中定义的
            if ( d_ent->d_type != DT_DIR)
            {
                string d_name(d_ent->d_name);
                //printf("%s\n",d_ent->d_name);
                if (strcmp(d_name.c_str () + d_name.length () - m_ext.length(), m_ext.c_str ()) == 0)
                {
                    // 构建绝对路径
                    //string absolutePath = directory + string("/") + string(d_ent->d_name);
                    // 如果传入的目录最后是/--> 例如"a/b/", 那么后面直接链接文件名
                    //if (directory[directory.length()-1] == '/')
                    //    absolutePath = directory + string(d_ent->d_name);
                    //result.push_back(absolutePath);
                    result.push_back(string(d_ent->d_name));
                }
            }
        }
    }
 
    // sort the returned files
    sort(result.begin(), result.end());
 
    closedir(dir);
    return result;
}
string app_inter(vector<string>){
    vector<string> file_name(GetFiles(".",".wav"));
    for(int i=0;i<file_name.size();i++){
        string execmd_inner="aplay -t wav ";
        execmd_inner+=file_name[i];
        cout<<execmd_inner<<endl;
        system(execmd_inner.c_str());
    }
    return "OK";
}


void setup_lib_app(vector<string> &base_func_name,vector<long> &base_func_addr){
    base_func_name.push_back("app_play");
    base_func_addr.push_back((long)app_inter); 
}