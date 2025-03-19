#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>
#include <cmath>
#include <limits>

using namespace std;


struct DataPoint{
    int label; //class 1 or 2 dep on first column of data set
    vector<double> features;  //feature vals
    double operator[](int index) const {
        return features[index];  //objToClassify[i] instead of objToClassify.features[i]
    }
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


// funct print out first 2 lines in the dataset for debugging
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

double findDistance(const DataPoint& objToClassify, const DataPoint& dataPoint, const set<int>& currFeat){
    double sum=0.0;
    for (int feat : currFeat){
        sum +=pow(objToClassify[feat-1] -dataPoint[feat-1], 2);
    }
    return sqrt(sum);
}

//using psdueo code and structure from Prof Eamonn's project 2 briefing
double crossValidation(const vector<DataPoint>& dataset, const set<int>& currFeat, int addFeat){
    int correctlyClassified=0;
    for(int i =0; i< dataset.size();i++){
        const DataPoint& objToClassify = dataset[i]; 
        int objLabel = objToClassify.label;
        //cout<< "Looping over i, at the "<< i +1<< " location"<<endl;
        //cout<< "The object is in class "<< objLabel<<endl;
        double nnLabel = -1;
        double nnDistance = numeric_limits<double>::infinity();
        double nnLocation = numeric_limits<double>::infinity();
        for(int j=1; j< dataset.size(); j++){
            //cout<< "Ask if "<< i<< " is nearest neighbor with "<< j<< endl;
            if(i !=j){
                double distance = findDistance(objToClassify, dataset[j], currFeat);
                if(distance < nnDistance){
                    nnDistance = distance;
                    nnLocation = j;
                    nnLabel = dataset[nnLocation].label;
                }
            }
        }
        //cout<< "Object "<< i<< " is class "<< objToClassify.label<<endl;
        //cout<< "Its nearest neighbor is "<< nnLocation<<" which is in class "<< nnLabel <<endl;
        if(objLabel == nnLabel){
            correctlyClassified = correctlyClassified +1;
        }
    }
    double accuracy = static_cast<double>(correctlyClassified)/dataset.size();
    cout<< "Accuracy: "<< accuracy<<endl;
    return accuracy;
}

//using pseudo code and structure from Prof Eamonn's project 2 briefing
void forwardSearch(const vector<DataPoint>& dataset){
    cout<< "Running Forward Search"<<endl;
    set<int>currFeatures;//empty set to start 
    int numFeatures= dataset[0].features.size();
    double bestAccuracy =0.0;

    for(int i=1; i<=numFeatures; i++){
        cout<< "On the "<< i<< "th level of the search tree"<<endl;
        int addFeat = -1;
        double currAccuracy =0.0; //current accuracy
        for(int j=1; j<=numFeatures; j++){
            if(currFeatures.find(j) == currFeatures.end()){
                cout<< "--Considering adding feature"<<j<< endl;
                set<int> tempSet = currFeatures;  //DEBUG
                tempSet.insert(j); //DEBUG
                double accuracy= crossValidation(dataset, tempSet, j);
                cout << "Accuracy after adding feature " << j << ": " << accuracy << endl; //DEBUG
                if(accuracy > currAccuracy){
                    currAccuracy= accuracy;
                    addFeat= j;
                }
            }
        }
        if (addFeat != -1 && currAccuracy > bestAccuracy) {
            currFeatures.insert(addFeat);  // Add the feature to the set
            bestAccuracy = currAccuracy;  // Update the best accuracy
            cout << "On level " << i << " I added feature " << addFeat << " to current set" << endl;
        }
    }
    cout << "Features added during Forward Search: ";
    for (int feature : currFeatures) {
        cout << feature << " ";
    }
    cout << endl;
    cout<< "End of Forward Search"<<endl;
}

//using pseudo code and structure from Prof Eamonn's project 2 briefing
void backwardsElimination(const vector<DataPoint>& dataset){
cout<< "Running Backwards Elimination"<<endl;
    int numFeatures= dataset[0].features.size();
    set<int>currFeatures; //empty set to start 
    for(int i = 1; i<=numFeatures; i++){///adding features to the beginign so can delete
        currFeatures.insert(i);
    }
    double bestAccuracy=0.0;

    for(int i=numFeatures; i>=1; i--){ // legit jsut opp of fowrads search
        cout<< "On the "<< i<< "th level of the search tree"<<endl;
        int deleteFeat = -1;
        double currAccuracy =0.0; //current accuracy
        for(int j=1; j<=numFeatures; j++){
            if(currFeatures.find(j) !=currFeatures.end()){
                cout<< "--Considering removing feature"<<j<< endl;
                set<int> tempSet = currFeatures;  // Make a temporary copy of current features
                tempSet.erase(j);
                double accuracy= crossValidation(dataset, currFeatures, j);
                cout << "Accuracy after removing feature " << j << ": " << accuracy << endl;
                if(accuracy > currAccuracy){
                    currAccuracy= accuracy;
                    deleteFeat = j;
                }
            }
        }
        if(deleteFeat != -1){
            currFeatures.erase(deleteFeat);
            bestAccuracy = currAccuracy;
            cout<<"On level "<< i << " I removed feature "<< deleteFeat<<endl;
        }
    }
    cout << "Features remaining after Backwards Elimination: ";
    for (int feature : currFeatures) {
        cout << feature << " ";
    }
    cout << endl;
    cout<< "End of Backwards Elimination"<<endl;
}


int main(){
    cout<< "Feature Selection with Nearest Neighbor"<<endl;
    cout<< "Please choose which search you would like to try:"<<endl;
    cout<< "1. Forward Search"<<endl<< "2.Backwards Elimination"<<endl;
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
        forwardSearch(dataset);
    }else if( userInput ==2){
        //BACKWARDS ELIMINATION
        backwardsElimination(dataset);
    }else{
        cout<< "Invalid input"<<endl;
        return 0;
    }

    //printSampleData(dataset);//for debugign

    return 0;
}




