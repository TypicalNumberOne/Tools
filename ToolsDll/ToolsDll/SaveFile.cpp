#include "pch.h" //DLL标准
#include <utility> //DLL标准
#include <limits.h> //DLL标准

#include "SaveFile.h"

using StringHandling::CStringToLPCWSTR;;

//-----------------------------------------------------------------------------class BasicOperation

template<typename T>
void output(T value, const int& i)
{
    cout << value;

    if (i == 1) {
        cout << endl;
    }
}

string emptyString(string& text)
{
    return text = "";
}

string completeString(string& text, char& charNumbers) {
    string numbers = {};
    char slash = charNumbers; //charNumbers：char 字符对应的ASCLL 值

    cout << text << endl; //打印传入的字符，与修改后的字符做对比

    for (int i = 0; i < (int)text.length() + 1; i++) {
        text[i] = getchar();
        if (text[i] == slash) {
            numbers = slash;
            numbers[i] = text[i];
        }
        numbers[i] = text[i];
    }
    cout << numbers << endl; //修改后的字符

    return numbers;
}

void consoleCommand(string command) {
    system(command.c_str()); //c_str() 将string 转换为const char*
}

//-----------------------------------------------------------------------------class FileOperations

int FileOperations::copyFileSteam(CString path, CString project_Path, CString program_Suffix) {
    //replace(Path.begin(), Path.end(), '\'', '\\');
    CString programCompletion_Path = path + program_Suffix;
    CString project_Paths = project_Path + program_Suffix;
    BOOL bMoveOK = MoveFile(programCompletion_Path, project_Paths);

    //文件移动成功
    if (bMoveOK) {
        //printf("移动成功！\n, 路径为：%s", (string*)&programCompletion_Path);
        return 0;
    }
    //文件移动失败
    else {
        //printf("目标已被移动！\n, 路径为：%s", (string*)&programCompletion_Path);
        return 1;
    }
}

int FileOperations::copyFileSteamReduction(CString path, CString project_Path, CString program_Suffix) {
    CString programCompletion_Path = path + program_Suffix;
    CString project_Paths = project_Path + program_Suffix;
    BOOL bMoveOK = MoveFile(programCompletion_Path, project_Paths);

    //文件移动成功
    if (bMoveOK) {
        //printf("还原成功！已将目标移动回原位！\n\n");
        return 0;
    }
    //文件移动失败
    else {
        //printf("还原失败！目标已不再原位置！\n\n");
        return 1;
    }
}

void FileOperations::GetFilePath() {
    CString configFile_Path, str; //配置文件路径
    string path; //文件路径
    //实例 文件流对象 in
    fstream in;

    configFile_Path = file_PathAndName + file_Suffix; //配置文件路径
    in.open(configFile_Path, ios::in);//打开配置文件
    if (!in.fail()) {
        //从配置文件中，获取 steam.exe的位置
        getline(in, path);
        program_Path = path.c_str();
        //printf("\n从配置文件中获取到的 程序路径：\n\t%s", program_Path.GetString());

        in.close();  //关闭文件
        //printf("\n......配置文件内容读取完成！");
    }
    else {
        //cout << "\n配置文件打开失败！(程序与配置文件可能不在同一目录下...\n";
    }
}
/*
void FileOperations::GetProgramPath(ToolsConfigFile& ToolsCfgF) {
    LPWSTR buff;//用于存放获取的路径信息。
    buff = (LPWSTR)CStringToLPCWSTR(ToolsCfgF.ToolsEXEFilePath);
    //第一个参数为句柄，NULL则指向当前程序。第二个参数用于存放地址的指针，第三个参数，系统自带的宏定义。不用管。
    GetModuleFileName(NULL, buff, MAX_PATH);
    string project_Path = (LPSTR)buff;//project_ProgramPath 项目路径
    //注意：第三步reversefind()函数中使用的是单引号。

    GetFilePath();

    /*
    char buff[MAX_PATH];//用于存放获取的路径信息。

    GetModuleFileName(NULL,buff,MAX_PATH);
    //第一个参数为句柄，NULL则指向当前程序。第二个参数用于存放地址的指针，第三个参数，系统自带的宏定义。不用管。

    CString str=buff;
    //将buff存放的路径赋给字符串str,此时buff值如：“E:\MyTest\Debug\****.exe”

    int pos=str.ReverseFind('\\');
    //查找倒数最后一个“\\”符号

    str=str.Left(pos+1);
    //str只获取exe所在文件夹路径; str为："E:\MyTest\Debug\"

    //注意：第三步reversefind()函数中使用的是单引号。
    /
}
*/

int FileOperations::copyFile(char* SourceFile, char* NewFile, void (*CerrPrint)())
{
    ifstream in;
    ofstream out;

    in.open(SourceFile, ios::binary);//打开源文件
    if (in.fail()) { //打开源文件失败
        CerrPrint();

        in.close();
        out.close();
        return 0;
    }
    out.open(NewFile, ios::binary);//创建目标文件 
    if (out.fail()) { //创建文件失败
        CerrPrint();

        out.close();
        in.close();
        return 0;
    }
    else { //复制文件
        out << in.rdbuf();
        out.close();
        in.close();
        return 1;
    }
}

void FileOperations::copyFile_Run()
{
    char source[256], NewFile[256];
    //cout << "请输入要复制的文件路径:" << endl;
    cin >> source;
    //cout << "请输入新文件的路径:" << endl;
    cin >> NewFile;
    if (copyFile(source, NewFile)) {
        cout << "文件已成功复制..." << endl;
    }
    else {
        cout << "文件复制失败..." << endl;
    }
    
    //cin.get();
}

void FileOperations::deleteFile()
{
    char source[256];//文件路径
    //cout << "请输入要删除的文件路径:" << endl;
    cin >> source;

    string tmp = (string)source;
    LPCSTR target = tmp.c_str();

    if (!_access(target, 0)) //函数 _access 判断文件是否存在
        if (DeleteFileA(target)) { //删除成功
            //cout << source << " 已成功删除." << endl;
        }
        else { //无法删除:文件只读或无权限执行删除
            //cout << source << " 无法删除:文件为只读属性或无删除权限." << endl;
        }   //执行 删除文件
    else//文件不存在
        //cout << source << " 不存在,无法删除." << endl;

    cin.get();

    /* _access(char *,int) 判断文件是否存在
    存在 返回0;不存在 返回-1.
    _access(const char *path,int mode)
    mode的值:
    00 是否存在
    02 写权限
    04 读权限
    06 读写权限

    if (!_access(source, 0)){ //如果文件存在:文件为只读无法删除
        //去掉文件只读属性
        SetFileAttributes(source, 0);
        if (DeleteFile(source)){ //删除成功
            cout << source << " 已成功删除." << endl;
        }
        else { //无法删除:文件只读或无权限执行删除
            cout << source << " 无法删除:文件为只读属性或无删除权限." << endl;
        }
    }
    */
}

int FileOperations::copyFile(char* SourceFile, char* NewFile)
{
    ifstream in;
    ofstream out;

    in.open(SourceFile, ios::binary);//打开源文件
    if (in.fail()) { //打开源文件失败
        in.close();
        out.close();
        return 0;
    }
    out.open(NewFile, ios::binary);//创建目标文件 
    if (out.fail()) { //创建文件失败
        out.close();
        in.close();
        return 0;
    }
    else { //复制文件
        out << in.rdbuf();
        out.close();
        in.close();
        return 1;
    }
}

void FileOperations::saveData(string& filePath, string& fileName, string& fileSuffixConfig)
{
    string FilePath;
    ofstream f;
    //BasicOperation Bo;

   FilePath = fileName + filePath + fileSuffixConfig.c_str(); //文件位置

   if (!f.fail()) {
       f.open(FilePath, ios::out);//建立文件
       f.close();  //关闭文件
       //Bo.output("......读写完成");
   }
}
