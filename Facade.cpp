#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<unordered_map>
#include<sstream>
using namespace std;

class Database{
    public:
        Database()=delete;
        static void readFile(const string& fileName){
            ifstream ifs(fileName);
            string name;
            string addr;
            while(!ifs.eof()){
                ifs>>name;
                ifs>>addr;
                cout<<name<<endl;
                cout<<addr<<endl;
            }
        }
        static string getProperty(const string& name){

        }
    private:
        static unordered_map<string,string> prop;
};
unordered_map<string,string> Database::prop;

int main(){
    ifstream input_file("test.cpp");
    if (!input_file.good()) {
        cout << "open fail." << endl;
        return -1;
    } else {
        cout << "open successful." << endl;
    }
    stringstream input_stream;
    input_stream << input_file.rdbuf();
    input_file.close();
    string str;
    while (getline(input_stream, str)) {
        cout << str << endl;
    }
    return 0;
}