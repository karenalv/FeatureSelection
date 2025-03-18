#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;


struct DataPoint{
    int label; //class 1 or 2 dep on first column of data set
    vector<double> features;  //feature vals
};

vector<DataPoint> readFile(const string& filename){
    ifstream file(filename);
    if (!file) {
        cout << "Error: Can't open." << filename << endl;
        exit(1);
    }
    vector<DataPoint> dataset;
    string line;
    while (getline(file, line)){  //read line by line
        stringstream ss(line);
        DataPoint data;
        ss>>ws;
        double tempLabel;//mkaes first into double so it doesnt get mistread
        ss >> tempLabel;
        data.label = static_cast<int>(tempLabel);
        double value;
        while (ss >> value){
            data.features.push_back(value);
        }
        dataset.push_back(data);
    }
    file.close();
    return dataset;
}


// Function to print first two data points
void printSampleData(const vector<DataPoint>& dataset){
    cout << "first two lines: ";
    for (size_t i = 0; i < min(dataset.size(), size_t(2)); i++){
        cout << "class:"<< dataset[i].label<< " |features:";
        for (double feature : dataset[i].features) {
            cout << feature << " ";
        }
        cout << endl;
    }
}

void forwardSearch(){
    cout<< "Running Forward Search"<<endl;
    cout<< "End of Forward Search"<<endl;
}


int main(){
    cout<< "Feature Selection with Nearest Neighbor"<<endl;
    cout<< "Please choose which search you would like to try:"<<endl;
    cout<< "1. Forward Search"<<endl<< "2.Backwards Search"<<endl;
    int userInput;
    cin>> userInput;
    cout<<endl;

    cout<< "Please choose which data set you would like to use:"<<endl;
    cout<< "1. Small Dataset"<<endl<< "2. Large Dataset"<<endl;
    int dataChoice;
    cin>> dataChoice;
    cout<<endl;


    vector<DataPoint> dataset;

    if(dataChoice==1){
        dataset = readFile("CS170_Small_Data__74.txt");
    }
    else if(dataChoice==2){
        dataset =readFile("CS170_Large_Data__119.txt");
    }
    else{
        cout<< "Invalid dataset choice."<<endl;
        return 0;
    }
    

    if(userInput==1){
        //FORWARD SEARCH
        forwardSearch();
    }else if( userInput ==2){
        //BACKWARDS SEARCH
        
    }else{
        cout<< "Invalid input"<<endl;
        return 0;
    }
    printSampleData(dataset);

    return 0;
}