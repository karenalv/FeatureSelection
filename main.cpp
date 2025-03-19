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

//using psdueo code and structure from Prof Eamonn's project 2 briefing
double crossValidation(const vector<DataPoint>& dataset, const set<int>& currFeat, int addFeat){
    int correctClassif=0;
    //cout<< " CAN considered feat " << addFeat<< endl;
    for(int i =0; i<dataset.size();i++){
        const DataPoint& objToClassify=dataset[i];
        int trueClassification = objToClassify.label;
        double nnDistance = numeric_limits<double>::infinity();
        int nnLabel = -1;

        for(int j=0; j< dataset.size(); j++){
            if(j ==i) continue;

            // vector<double> tempFeat = dataset[j].features;
            // for(int k = 0; k<tempFeat.size(); k++){
            //     if((currFeat.count(k+1)) || (k+1 == addFeat)){
            //         tempFeat[k]=0;
            //     }
            // }
            double distance =0.0;
            for(int k=0; k< dataset[j].features.size(); k++){
                if (currFeat.count(k + 1) || k + 1 == addFeat) { // Use only selected features
                    double diff = objToClassify.features[k] - dataset[j].features[k];
                    distance += diff * diff;
                }
            }
            distance= sqrt(distance);
            if(distance < nnDistance){
                nnDistance = distance;
                nnLabel = dataset[j].label;
            }
        }
        if(nnLabel == trueClassification){
            correctClassif++;
        }
    }
    //cout<< "considered feat " << addFeat<< endl;
    return static_cast<double>(correctClassif)/dataset.size();
}

//using pseudo code and structure from Prof Eamonn's project 2 briefing
void forwardSearch(const vector<DataPoint>& dataset){
    cout<< "Running Forward Search"<<endl;
    set<int>currFeatures;//empty set to start 
    int numFeatures= dataset[0].features.size();

    for(int i=1; i<=numFeatures; i++){
        cout<< "On the "<< i<< "th level of the search tree"<<endl;
        int addFeat = -1;
        double currAccuracy =0.0; //current accuracy
        for(int j=1; j<=numFeatures; j++){
            if(currFeatures.find(j) == currFeatures.end()){
                cout<< "--Considering adding feature"<<j<< endl;
                double accuracy= 1; //crossValidation(dataset, currFeatures, j);
                if(accuracy > currAccuracy){
                    currAccuracy= accuracy;
                    addFeat= j;
                }
            }
        }
        if(addFeat != -1) {
            currFeatures.insert(addFeat);  //adding feat to CURRFEAT OMG TOOK FOREVER TO FIGRUE OUT IMMA CRAHSOUT 
        }
        cout<< "On level "<< i << " i added feature "<< addFeat<< " to current set"<<endl;
    }
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

    for(int i=numFeatures; i>=1; i--){ // legit jsut opp of fowrads search
        cout<< "On the "<< i<< "th level of the search tree"<<endl;
        int deleteFeat = -1;
        double currAccuracy =0.0; //current accuracy
        
        for(int j=1; j<=numFeatures; j++){
            if(currFeatures.find(j) !=currFeatures.end()){
                cout<< "--Considering removing feature"<<j<< endl;
                double accuracy= 1; //crossValidation(dataset, currFeatures, j);
                if(accuracy > currAccuracy){
                    currAccuracy= accuracy;
                    deleteFeat = j;
                }
            }
        }
        if(deleteFeat != -1){
            currFeatures.erase(deleteFeat);
            cout<<"On level "<< i << " I removed feature "<< deleteFeat<<endl;
        }
    }
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




