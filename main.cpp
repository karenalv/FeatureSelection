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
    if(!file){
        cout << "Error: Can't open"<<filename<<endl;
        exit(1);
    }
    vector<DataPoint> dataset;
    string line;

    while (getline(file, line)){ //read line by line
        stringstream ss(line);
        DataPoint data;
        ss >>data.label; //clas lable
        double value;
        while (ss >> value){ //read feature vals
            data.features.push_back(value);
        }
        dataset.push_back(data);
    }
    file.close();
    return dataset;
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
    
    return 0;
}