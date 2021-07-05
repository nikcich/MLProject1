#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <chrono>

using namespace std;

float sum_numeric_vector(vector<float> vec);
float mean_numeric_vector(vector<float> vec);
float median_numeric_vector(vector<float> vec);
float range_numeric_vector(vector<float> vec);
float covariance(vector<float> rm, vector<float> medv);
float correlation(vector<float> rm, vector<float> medv);

int main(){
    ifstream myfile("titanic_project.csv");

    vector<int> pclass;
    vector<int> survived;
    vector<int> sex;
    vector<float> age;

    if(myfile.is_open()){
        string col1; // to store input column 1

        getline(myfile, col1, ','); // blank string
        getline(myfile, col1, ','); // pclass string
        getline(myfile, col1, ','); // survived string
        getline(myfile, col1, ','); // sex string
        getline(myfile, col1, '\n'); // age string

        while(getline(myfile, col1, ',')){
            string col2;
            string col3;
            string col4;
            string col5;

            getline(myfile, col2, ',');
            getline(myfile, col3, ',');
            getline(myfile, col4, ',');
            getline(myfile, col5, '\n');

            pclass.push_back(stoi(col2));
            survived.push_back(stoi(col3));
            sex.push_back(stoi(col4));
            age.push_back(stof(col5));

            // << col2 << " " << col3 << " " << col4 << " " << col5 << endl;
        }
        //cout << col1 << endl;
    }

    //float sum = sum_numeric_vector(rm);
    //float mean = mean_numeric_vector(rm);
    //float median = median_numeric_vector(rm);
    //float range = range_numeric_vector(rm);



    return 0;
}

float sum_numeric_vector(vector<float> vec){
    float sum = 0.0000; // assign 0 to sum var
    for(vector<float>::iterator it = vec.begin(); it != vec.end(); ++it){ // uses iterator to iterator over vector
        sum += *it; // sums the vector
    }
    return sum; // returns the sum
}

float mean_numeric_vector(vector<float> vec){
    int element_number = vec.size(); // size of vector/ number of elements
    float sum = sum_numeric_vector(vec); // sums the vector
    float mean = sum/element_number; // gets the sum / elements
    return mean; // returns mean
}

float median_numeric_vector(vector<float> vec){
    if(vec.size() == 0) return 0; // if empty vector return 0 (technically wouldn't exist though)
    else{
        sort(vec.begin(), vec.end()); // sorts the vector
        int vecSize = vec.size(); // vector size
        if( vecSize % 2 == 0){ // if divisible by 2
            return((vec[vecSize / 2 - 1] + vec[vecSize /  2])/2); // returns the average of 2 middle elements
        }else{ // if not divisible by 2
            return vec[vecSize/2]; // returns the middle elements
        }
    }
}

float range_numeric_vector(vector<float> vec){
    sort(vec.begin(), vec.end()); // sorts vector
    return vec.back() - vec.front(); // returns difference of largest and smallest elements
}

float covariance(vector<float> rm, vector<float> medv){
    float mean_rm = mean_numeric_vector(rm); // mean of rm
    float mean_medv = mean_numeric_vector(medv); // mean of medv

    int rm_medv_size = rm.size(); // size of the 2 vectors

    float top_sum = 0.0000; // sum start at 0
    for(int i = 0; i < rm_medv_size; i++){ // loop through the vectors
        float x_paren = rm[i] - mean_rm; // calculate the difference of current and mean
        float y_paren = medv[i] - mean_medv; // calculate difference of current and mean
        float top = x_paren * y_paren; // multiply the two together
        top_sum += top; // add to sum
    }

    return top_sum / (rm_medv_size-1); // return the sum/size-1
}

float correlation(vector<float> rm, vector<float> medv){
    float cov = covariance(rm, medv); // covariance of rm and medv
    float var_rm = covariance(rm,rm); // variance of rm
    float var_medv = covariance(medv, medv); // variance of medv
    float bottom = sqrt(var_rm) * sqrt(var_medv); // Sigma = sqrt of variance

    return cov/bottom; // return covariance/sigmaXsigmaY
}

