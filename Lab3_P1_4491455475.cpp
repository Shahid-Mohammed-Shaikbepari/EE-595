#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;
class Number{
private:
    int value;
public:
    void set_value(int value){
        this->value = value;
    }
    int get_value(){
        return value;
    }
};
class NumberSet{
public:
    Number objects[10];

    bool check_independence(NumberSet set){
        for(int i=0; i< 10; i++){
            for(int j=0; j<10; j++){
                if(this->objects[i].get_value() == set.objects[j].get_value()){
                    return false;
                }
            }
        }
        return true;
    }

};

int main() {
    ifstream file;
    file.open("input.txt");
    ofstream opfile;
    opfile.open("output.txt");
    NumberSet numberSetarr[20];
    string str;
    string delimeter = " ";
    int arrIndex = 0;
    // to read the file and store
    while (getline(file, str)){
        size_t pos = 0;
        string token;
        int row_index = 0;
        while ((pos = str.find(delimeter)) != std::string::npos){
            token = str.substr(0,pos);
            int val = stoi(token);
            Number num;
            num.set_value(val);
            numberSetarr[arrIndex].objects[row_index] = num;
            row_index++;
            str.erase(0, pos + delimeter.length());
        }
        int tmpval = stoi(str);
        Number num;
        num.set_value(tmpval);
        numberSetarr[arrIndex].objects[row_index] = num;
        arrIndex++;
    }

//to check the independence
bool flag = false;
    for(int i = 0; i< 20; i++){
        for(int j = i+ 1; j < 20 ; j++){
            if(numberSetarr[i].check_independence(numberSetarr[j])){
                opfile << "Y" << endl;
                flag = true;
                break;
            }
        }
        if(flag)
        break;
    }
    if(!flag)
        opfile << "N" << endl;



file.close();
opfile.close();
    return 0;
}

