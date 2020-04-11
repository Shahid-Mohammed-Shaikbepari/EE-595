#include <iostream>



bool sameside(int arr[]){
    return (((arr[1] - arr[3]) * (arr[4] - arr[0]) + (arr[2] - arr[0]) * (arr[5] - arr[1])) *
           ((arr[1] - arr[3]) * (arr[5] - arr[0]) + (arr[2] - arr[0]) * (arr[6] - arr[1]))) < 0;

}
//((y1−y2)(ax−x1)+(x2−x1)(ay−y1))((y1−y2)(bx−x1)+(x2−x1)(by−y1))<0
//reference: math.stackexchange.com
int main() {
    int arr[7] = {-1, -1, 5, 0, 2, 3, -12};
    bool res = sameside(arr);
    if(res)
        std::cout << "true" << std::endl;
    else
        std::cout << "false" << std::endl;
    return 0;
}