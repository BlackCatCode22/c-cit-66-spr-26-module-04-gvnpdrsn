//zooPractice.cpp
// Created by GP on 3/6/2026.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;



class Animal {

protected:
    string id;
    string name;
    string species;
    int age;
    string birthSeason;
    string color;
    string sex;
    int weight;
    string origin;

public:

    Animal(string i,string n,string s,int a,string b,string c,string sx,int w,string o){
        id=i;
        name=n;
        species=s;
        age=a;
        birthSeason=b;
        color=c;
        sex=sx;
        weight=w;
        origin=o;
    }

    string getSpecies(){ return species; }
    string getName(){ return name; }
    int getAge(){ return age; }

    void setName(string n){ name=n; }
    void setAge(int a){ age=a; }

    virtual void print(ofstream &out){

        cout<<id<<"; "<<name<<"; "<<age<<" years old; "
            <<birthSeason<<" birth; "<<color<<"; "
            <<sex<<"; "<<weight<<" pounds; from "<<origin<<endl;

        out<<id<<"; "<<name<<"; "<<age<<" years old; "
           <<birthSeason<<" birth; "<<color<<"; "
           <<sex<<"; "<<weight<<" pounds; from "<<origin
           <<"; arrived Sept 2022"<<endl;
    }

    virtual ~Animal(){}
};

class Hyena : public Animal{

public:
    Hyena(string id,string name,int age,string birth,string color,string sex,int weight,string origin)
    : Animal(id,name,"Hyena",age,birth,color,sex,weight,origin){}

    void laugh(){
        cout<<"The Hyena "<<name<<" laughs."<<endl;
    }
};

class Lion : public Animal{

public:
    Lion(string id,string name,int age,string birth,string color,string sex,int weight,string origin)
    : Animal(id,name,"Lion",age,birth,color,sex,weight,origin){}

    void roar(){
        cout<<"The Lion "<<name<<" is the king of the jungle."<<endl;
    }
};

class Tiger : public Animal{

public:
    Tiger(string id,string name,int age,string birth,string color,string sex,int weight,string origin)
    : Animal(id,name,"Tiger",age,birth,color,sex,weight,origin){}

    void growl(){
        cout<<"The Tiger "<<name<<" thinks its grrrrreat."<<endl;
    }
};

class Bear : public Animal{

public:
    Bear(string id,string name,int age,string birth,string color,string sex,int weight,string origin)
    : Animal(id,name,"Bear",age,birth,color,sex,weight,origin){}

    void hibernate(){
        cout<<"The Bear "<<name<<" is going into hibernation."<<endl;
    }
};


int main(){

    vector<Animal*> animals;
    map<string,int> count;

    vector<string> hyenaNames={"Shenzi","Banzai","Ed","Zig"};
    vector<string> lionNames={"Scar","Mufasa","Simba","Kiara"};
    vector<string> tigerNames={"Tony","Tigger","Amber","Cosimia"};
    vector<string> bearNames={"Yogi","Smokey","Paddington","Baloo"};

    int hy=0,li=0,ti=0,be=0;

    ifstream inFile("C:/cStuff/arrivingAnimals.txt");
    ofstream outFile("C:/cStuff/newAnimals.txt");

    if(!inFile){
        cout<<"File error"<<endl;
        return 1;
    }

    cout<<"Processing Animals...\n"<<endl;

    string line;

    while(getline(inFile,line)){

        int age,weight;
        string sex,species;
        string birthSeason="unknown";
        string color;
        string origin;

        string part1,part2,part3,part4,part5;
        stringstream ss(line);

        getline(ss,part1,',');
        getline(ss,part2,',');
        getline(ss,part3,',');
        getline(ss,part4,',');
        getline(ss,part5);

        string year,oldWord;
        stringstream first(part1);
        first>>age>>year>>oldWord>>sex>>species;

        if(part2.find("spring")!=string::npos) birthSeason="spring";
        if(part2.find("summer")!=string::npos) birthSeason="summer";
        if(part2.find("fall")!=string::npos) birthSeason="fall";
        if(part2.find("winter")!=string::npos) birthSeason="winter";

        int pos=part3.find(" color");
        if(pos!=-1)
            color=part3.substr(0,pos);

        string pounds;
        stringstream weightStream(part4);
        weightStream>>weight>>pounds;

        origin=part5.substr(5);

        if(species=="hyena"){
            string id="Hy0"+to_string(hy+1);
            animals.push_back(new Hyena(id,hyenaNames[hy],age,birthSeason,color,sex,weight,origin));
            hy++;
            count["Hyena"]++;
        }

        if(species=="lion"){
            string id="Li0"+to_string(li+1);
            animals.push_back(new Lion(id,lionNames[li],age,birthSeason,color,sex,weight,origin));
            li++;
            count["Lion"]++;
        }

        if(species=="tiger"){
            string id="Ti0"+to_string(ti+1);
            animals.push_back(new Tiger(id,tigerNames[ti],age,birthSeason,color,sex,weight,origin));
            ti++;
            count["Tiger"]++;
        }

        if(species=="bear"){
            string id="Be0"+to_string(be+1);
            animals.push_back(new Bear(id,bearNames[be],age,birthSeason,color,sex,weight,origin));
            be++;
            count["Bear"]++;
        }
    }


    cout<<"ANIMAL REPORT\n"<<endl;

    cout<<"Hyena Habitat"<<endl;
    outFile<<"Hyena Habitat\n\n";

    for(auto a:animals)
        if(a->getSpecies()=="Hyena")
            a->print(outFile);

    cout<<"Total Hyenas: "<<count["Hyena"]<<"\n"<<endl;
    outFile<<"\nTotal Hyenas: "<<count["Hyena"]<<"\n\n";


    cout<<"Lion Habitat"<<endl;
    outFile<<"Lion Habitat\n\n";

    for(auto a:animals)
        if(a->getSpecies()=="Lion")
            a->print(outFile);

    cout<<"Total Lions: "<<count["Lion"]<<"\n"<<endl;
    outFile<<"\nTotal Lions: "<<count["Lion"]<<"\n\n";


    cout<<"Tiger Habitat"<<endl;
    outFile<<"Tiger Habitat\n\n";

    for(auto a:animals)
        if(a->getSpecies()=="Tiger")
            a->print(outFile);

    cout<<"Total Tigers: "<<count["Tiger"]<<"\n"<<endl;
    outFile<<"\nTotal Tigers: "<<count["Tiger"]<<"\n\n";


    cout<<"Bear Habitat"<<endl;
    outFile<<"Bear Habitat\n\n";

    for(auto a:animals)
        if(a->getSpecies()=="Bear")
            a->print(outFile);

    cout<<"Total Bears: "<<count["Bear"]<<"\n"<<endl;
    outFile<<"\nTotal Bears: "<<count["Bear"]<<"\n\n";

    cout<<"Report written to newAnimals.txt"<<endl;

    for(auto a:animals)
        delete a;

    return 0;
}