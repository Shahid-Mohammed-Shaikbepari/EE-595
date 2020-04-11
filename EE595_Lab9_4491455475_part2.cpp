// code to generate random route was taken from https://www.geeksforgeeks.org/generate-a-random-permutation-of-1-to-n/
// C++ implementation of the approach
#include <bits/stdc++.h>
#include <math.h>
#define T0  80
#define beta  0.9
#define minTemp  0.00001
#define iterationCheck 80000
using namespace std;

// Function to return the next random number
int getNum(vector<int>& v)
{

    // Size of the vector
    int n = v.size();

    // Generate a random number
    srand(time(NULL));

    // Make sure the number is within
    // the index range
    int index = rand() % n;

    // Get random number from the vector
    int num = v[index];

    // Remove the number from the vector
    swap(v[index], v[n - 1]);
    v.pop_back();

    // Return the removed number
    return num;
}

// Function to generate n non-repeating random numbers
int *generateRandom(int n)
{
    vector<int> v(n);

    // Fill the vector with the values
    // 1, 2, 3, ..., n
    for (int i = 0; i < n; i++)
        v[i] = i + 1;

    // While vector has elements
    // get a random number from the vector and print it
    int *arr = (int *) malloc(n*sizeof(int));
    int Index = 0;
    while (v.size()) {
        arr[Index] = getNum(v);
        Index++;
    }
    return arr;
}

struct Data{
    int **coordinates;
    int V;
};

Data *ReadData(string filename){
    ifstream ipfile;

    ipfile.open(filename);

    string str;
    string delimeter = " ";
    int i = 0;
    int V = 0;
    int **coordinates;
    while(getline(ipfile, str)){
        // declaring a char array and copying str into it
        char sh[str.size() + 1] ;
        //copy is taken from https://www.techiedelight.com/convert-string-char-array-cpp/
        copy(str.begin(), str.end(), sh);
        sh[str.size()] = '\0';
        //strtok is taken from https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
        char* token1 = strtok(sh, " ");
        //strncmp is taken from http://www.cplusplus.com/reference/cstring/strncmp/
        if(V == 0) {
            V = stoi(token1);
            // allocating memory for the 2D array to store the coordinates of cities
            coordinates = (int **)malloc(V * sizeof(int *));
            for (int i=0; i<V; i++)
                coordinates[i] = (int *)malloc(4 * sizeof(int));
        }
        else {
            int j = 0;
            while (token1 != NULL) {
                coordinates[i][j] = stoi(token1);
                j++;
                token1 = strtok(NULL, " ");
            }
            i++;
        }
    }
    Data *data1 = (Data *) malloc(sizeof(Data));
    data1->coordinates = coordinates;
    data1->V = V;
    return data1;
}

int getDistance(int i, int j, int** coordinates){
    int sum = 0;
    //i-1, j-1 cause the i, j values are in range [1,10]
    int x1 = coordinates[i-1][1];
    int y1 = coordinates[i-1][2];
    int z1 = coordinates[i-1][3];
    int x2 = coordinates[j-1][1];
    int y2 = coordinates[j-1][2];
    int z2 = coordinates[j-1][3];

    sum = pow((x1 - x2), 2) + pow((y1 - y2), 2) + pow((z1 - z2), 2);
    return sqrt(sum);

}

int costFunction(int *route, int **coordinates, int n){
    int dist = 0;
    // calculating distances between 1 to n routes, i.e. 1-2, 2-3, etc..

    for (int i = 0 ; i < n-1 ; i++){
        //cout << *(route + i) << " " << *(route+ i + 1) << endl;
        dist += getDistance( *(route + i), *(route+ i + 1), coordinates);
    }
    //calculating distances between 1 to n routes finally
    //cout << *(route) << " jj"<< *(route+ n- 1) << endl;
    dist += getDistance(*(route), *(route + n-1), coordinates);

    return dist;
}

int *MySwap(int *routeArray, int *newRouteArray, int index1, int index2, int n ){

    //memcpy was taken from http://www.cplusplus.com/reference/cstring/memcpy/
    // memcpy(dest, src, size)
    memcpy(newRouteArray, routeArray, sizeof(int) * n);
    int temp = *(newRouteArray + index1);
    *(newRouteArray + index1) = *(newRouteArray + index2);
    *(newRouteArray + index2) = temp;
    return newRouteArray;
}

bool areEqual(int arr1[], int arr2[], int n)
{
    // Linearly compare elements
    for (int i = 0; i < n; i++)
        if (arr1[i] != arr2[i])
            return false;

    // If all elements were same.
    return true;
}

struct result {
    double cost;
    int *finalRoute;
    double temp0;
};

result *SimulatedAnnealing(int n, int **coordinates, int *random_route_array){

    double Tk = T0;
    double T_k1 = 0;
    double probFun = 0;
    double delta = 0;
    double OldCost = 0;
    double newCost = 0;
    int iterationCount = 0;
    double p = 0.8;
    double deltaSum = 0;
    int deltaCounter = 0;
    double temp0 = 0;
    srand(time(NULL));
    int *newRouteArray = (int *) malloc(n*sizeof(int));

    while (Tk > minTemp) {
        iterationCount++;
        //define cost fun
        T_k1 = beta*Tk;
        Tk = T_k1;

        OldCost = costFunction(random_route_array, coordinates, n);
        // Make sure the number is within
        // the index range
        int randomCityIndex1 = rand() % n;
        int randomCityIndex2 = rand() % n;

        while (randomCityIndex1 == randomCityIndex2) {
            randomCityIndex2 = rand() % n;
        }
        newRouteArray = MySwap(random_route_array, newRouteArray, randomCityIndex1, randomCityIndex2, n);

        newCost = costFunction(newRouteArray, coordinates, n);
        //cout << "oldcost " << OldCost << " newCost " << newCost << endl;

        delta = (newCost - OldCost) / OldCost;

        if (delta <= 0) {
            // alloting new route to old route s = s` memcpy(dest, src, size)
            memcpy(random_route_array, newRouteArray, sizeof(int) * n);

        } else {

            probFun = exp((-delta)/Tk);
            //taken from https://stackoverflow.com/questions/9878965/rand-between-0-and-1
            double r = ((double) rand() / (RAND_MAX)) ;
//            if(p > r){
//                deltaSum += (newCost - OldCost);
//                deltaCounter++;
//            }

            if(probFun > r ){
                // alloting new route to old route s = s` memcpy(dest, src, size)
                memcpy(random_route_array, newRouteArray, sizeof(int) * n);
//                deltaSum += delta;
//                deltaCounter++;
            }
        }
        //if we reach to 80_000 iterations we check if the optimum solution is changed or not,
        // if not changed then we break the loop and declare the solution as existing route
        if(iterationCount >= iterationCheck){
            iterationCount = 0;
            if(areEqual(random_route_array, newRouteArray, n))
                break;
        }
    }
    //double avgDelta = deltaSum/deltaCounter;
    //cout << " deltaSum " << deltaSum << " avgDelta " << avgDelta << " DeltaCounter " << deltaCounter;
    //temp0 = (-avgDelta)/log(p);
    result *res = new result;
    res->cost = OldCost;
    res->finalRoute = random_route_array;
    //res->temp0 = temp0;

    return res;
}


int main()
{
    ofstream opfile;
    opfile.open("output.txt");
    // read the data from the file and get the
    // number of cities and coordinates of the cities
    Data* data = ReadData("input.txt");
    int n = data->V;
    int *random_route_array = generateRandom(n);
    result *res = SimulatedAnnealing(n, data->coordinates, random_route_array);
    int *finalRoute = res->finalRoute;
    double finalCost = res->cost;
    opfile << "Final Distance of SA Method: " << finalCost << endl;
    for(int i=0 ; i< n; i++){
        opfile << *(finalRoute + i)  << endl;
    }
    opfile << *(finalRoute) << endl;
    opfile.close();
    //CoolingSchedule();
    return 0;
}