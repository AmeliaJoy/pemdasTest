
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
struct parenthesesPair{
    int parLeft;
    int parRight;
    int priority;
};
bool compare(parenthesesPair a, parenthesesPair b)
{
    return b.priority<a.priority;
}
double calculate(std::vector<std::string> equationArray, parenthesesPair subVector)
{
    std::vector<std::string> subArray(equationArray.begin()+subVector.parLeft+1,equationArray.begin()+subVector.parRight);
    for (int i = 0; i < subArray.size(); i++)
    {
        
        if(subArray.at(i) == "/")
        {
            ///in real code, check if i-1 and i+1 in headers list
            subArray.at(i-1) = std::to_string(std::stod(subArray.at(i-1))/std::stod(subArray.at(i+1)));
            subArray.erase(subArray.begin()+i,subArray.begin()+i+2);
            i--;
        }
        if(subArray.at(i) == "*")
        {
            ///in real code, check if i-1 and i+1 in headers list
            subArray.at(i-1) = std::to_string(std::stod(subArray.at(i-1))*std::stod(subArray.at(i+1)));
            subArray.erase(subArray.begin()+i,subArray.begin()+i+2);
            i--;
        }
    }
    for (int i = 0; i < subArray.size(); i++)
    {
        
        if(subArray.at(i) == "-")
        {
            ///in real code, check if i-1 and i+1 in headers list
            subArray.at(i-1) = std::to_string(std::stod(subArray.at(i-1))-std::stod(subArray.at(i+1)));
            subArray.erase(subArray.begin()+i,subArray.begin()+i+2);
            i--;
        }
        if(subArray.at(i) == "+")
        {
            ///in real code, check if i-1 and i+1 in headers list
            subArray.at(i-1) = std::to_string(std::stod(subArray.at(i-1))+std::stod(subArray.at(i+1)));
            subArray.erase(subArray.begin()+i,subArray.begin()+i+2);
            i--;
        }
    }
    for (int i = 0; i < subArray.size(); i++)
    {
        std::cout<<subArray.at(i);
    }//here, check if ( is actually (- if not, run respective func
    std::cout<<'\n';
    return std::stod(subArray.at(0));
};
int main()
{
    int parenthesesNum = 0;
    std::vector<std::string> parentheses{"(","(","3","+","1","*","2",")","-","(","3",")",")"};
    std::vector<int> parenthesesID;
    std::vector<parenthesesPair> parenthesesPairs;
    parenthesesPair toPush;
    for (int i = 0; i < parentheses.size(); i++)
    {
        if(parentheses.at(i)=="(")
        {
            parenthesesNum++;
            parenthesesID.push_back(i);
        }
        if(parentheses.at(i)==")")
        {
            parenthesesNum--;
            std::cout << "this ) at "<<i<< " matches with the ( at id " << parenthesesID.at(parenthesesNum)<<" with priority "<< parenthesesNum<<"\n";
            toPush.parLeft = parenthesesID.at(parenthesesNum);
            toPush.parRight = i;
            toPush.priority = parenthesesNum;
            parenthesesPairs.push_back(toPush);
            parenthesesID.pop_back();    
        }
    }
    for (int i = 0; i < parentheses.size(); i++)
    {
        std::cout<<parentheses.at(i);
    }
    std::cout<<"\n";
    std::sort(parenthesesPairs.begin(),parenthesesPairs.end(),compare);
    for (std::vector<parenthesesPair>::iterator it=parenthesesPairs.begin(); it!=parenthesesPairs.end(); ++it)
    {
        parentheses.at(it->parLeft)=std::to_string(calculate(parentheses,*it));
        parentheses.erase(parentheses.begin()+it->parLeft+1,parentheses.begin()+it->parRight+1);
        for (std::vector<parenthesesPair>::iterator jt=parenthesesPairs.begin(); jt!=parenthesesPairs.end(); ++jt)
        {
            if(jt->parLeft > it->parRight)
                jt->parLeft -= it->parRight-it->parLeft;
            if(jt->parRight > it->parRight)
                jt->parRight -= it->parRight-it->parLeft;
        }
    }
    std::cout << (float)std::clock()/CLOCKS_PER_SEC;
}