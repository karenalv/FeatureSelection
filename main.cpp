#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

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
    int dtset;
    cin>> dtset;
    cout<<endl;

    string filename;
    if(dtset==1){
        filename="CS170_Small_Data__74.txt";
    } 
    else if(dtset==2){
        filename="CS170_Large_Data__119.txt";
    } 
    else{
        cout<< "Invalid dataset choice"<<endl;
        return 0;
    }

    ifstream file(filename);
    if(!file){
        cerr<< "Error: can't open file "<< filename<<endl;
        return 1;
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