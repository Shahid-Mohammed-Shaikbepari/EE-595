#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;


class Matrix{
public:
    int value[20][10];
    ifstream ipfile;
    ofstream opfile;
    int FirstNum;
    void ReadData(string filename){
        ipfile.open(filename);
        opfile.open("output.txt");
        string str;
        string delimeter = " ";
        int arrIndex = 0;
        while(getline(ipfile, str)){
            size_t pos = 0;
            string token;
            int row_index = 0;
            while((pos = str.find(delimeter)) != std::string::npos){
                token = str.substr(0,pos);
                int val = stoi(token);
                if(arrIndex == 0 && row_index == 0){
                    FirstNum = val;
                    opfile << "FirstNum: " << FirstNum << endl;
                }
                value[arrIndex][row_index] = val;
                row_index++;
                str.erase(0, pos + delimeter.length());
            }
            int temp = stoi(str);
            value[arrIndex][row_index] = temp;
            arrIndex++;
        }
    }
    void print2DArr(){
//        for(int i = 0; i< 20 ; i++ ){
//            for(int j=0; j<10; j++){
//                cout << value[i][j] << " " ;
//            }
//            cout << endl;
//        }
       // cout << sizeof(value[1])/ sizeof(int) << endl;
    }
    int linear_search(){
        int iterations = 0;
        for(int i = 1; i<20; i++){
            for(int j=0; j<10; j++){
                iterations++;
                if(value[i][j] == FirstNum){
                    opfile << "Using linear search number of iterations: " << iterations << endl;
                    opfile << "Linear search: row where FirstNum was found is: " << i+1 << endl;
                    return i;
                }

            }
        }
        return 0;
    }

//merge sort is taken from https://gist.github.com/mycodeschool/9678029
    void MergeSort(int *A,int n) {
        int mid,i, *L, *R;
        if(n < 2) return; // base condition. If the array has less than two element, do nothing.

        mid = n/2;  // find the mid index.

        // create left and right subarrays
        // mid elements (from index 0 till mid-1) should be part of left sub-array
        // and (n-mid) elements (from mid to n-1) will be part of right sub-array
        L = (int*)malloc(mid*sizeof(int));
        R = (int*)malloc((n- mid)*sizeof(int));

        for(i = 0;i<mid;i++) L[i] = A[i]; // creating left subarray
        for(i = mid;i<n;i++) R[i-mid] = A[i]; // creating right subarray

        MergeSort(L,mid);  // sorting the left subarray
        MergeSort(R,n-mid);  // sorting the right subarray
        Merge(A,L,mid,R,n-mid);  // Merging L and R into A as sorted list.
        free(L);
        free(R);
    }

    void Merge(int *A,int *L,int leftCount,int *R,int rightCount) {
        int i,j,k;

        // i - to mark the index of left aubarray (L)
        // j - to mark the index of right sub-raay (R)
        // k - to mark the index of merged subarray (A)
        i = 0; j = 0; k =0;

        while(i<leftCount && j< rightCount) {
            if(L[i]  < R[j]) A[k++] = L[i++];
            else A[k++] = R[j++];
        }
        while(i < leftCount) A[k++] = L[i++];
        while(j < rightCount) A[k++] = R[j++];
    }

    int binary_search(){
        int iterations = 0;
        int i = 0, mid = 0;
        bool found = false;
        for(i = 1 ; i<20; i++){
           // sort_row(value[i]);
           MergeSort(value[i], 10);
            int l = 0, r = 9;
            while(l<r){
                iterations++;
                 mid = (l + r)/2;
                if(value[i][mid] == FirstNum){
                    opfile << "Using binary search number of iterations: " << iterations << endl;
                    opfile << "Binary search: row where FirstNum was found is: " << i+1 << endl;
                    found = true;
                    break;
                }

                else if(value[i][mid] > FirstNum){
                    r = mid-1;
                } else {
                    l = mid+1;
                }
            }
            if(found)
                break;
        }
        ipfile.close();
        opfile.close();
        return i;
    }
};

int main(){
    Matrix mat;
    mat.ReadData("input.txt");
    //mat.print2DArr();
    //cout << mat.FirstNum << endl;
    mat.linear_search();
    mat.binary_search();
    return 0;

}