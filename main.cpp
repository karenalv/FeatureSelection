#include <iostream>

using namespace std;

int main(){
    cout<< "Feature Selection with Nearest Neighbor"<<endl;
    cout<< "Please choose which search you would like to try:"<<endl;
    cout<< "1. Forward Search"<<endl<< "2.Backwards Search"<<endl;
    int userInput=0;
    cin>> userInput;

    if(userInput==1){
        //FORWARD SEARCH
        cout<< "1. Forward Search"<<endl;
    }else if( userInput ==2){
        //BACKWARDS SEARCH
        cout<< "1. Backwards Search"<<endl;
    }else{
        cout<< "Incorrect input"<<endl;
        return 0;
    }
    
    return 0;
}