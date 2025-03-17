#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void forwardSearch(ifstream &file){
    cout<< "Running Forward Search"<<endl;



    cout<< "End of Forward Search"<<endl;
}



int main(int argc, char* argv[]){
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename>";
        return 1;
    }
    ifstream file(argv[1]);
    if (!file) {
        cerr << "Error: Could not open file " << argv[1] << endl;
        return 1;
    }

    cout<< "Feature Selection with Nearest Neighbor"<<endl;
    cout<< "Please choose which search you would like to try:"<<endl;
    cout<< "1. Forward Search"<<endl<< "2.Backwards Search"<<endl;
    int userInput=0;
    cin>> userInput;
    cout<<endl;

    if(userInput==1){
        //FORWARD SEARCH
        forwardSearch(file);
    }else if( userInput ==2){
        //BACKWARDS SEARCH
        
    }else{
        cout<< "Invalid input"<<endl;
        return 0;
    }
    
    file.close();
    return 0;
}