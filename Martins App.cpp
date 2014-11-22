#include <iostream>
#include <sstream>
#include <fstream>
#include "binheap.h"
#include "graph.h"
#include "path.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <stdio.h> 
const int OBSTACLES = 9;
using namespace std;
template <typename T>
//got function from http://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c
string to_string ( T Number )
  {
     ostringstream ss;
     ss << Number;
     return ss.str();
  }



int main(){
	srand (time(NULL));
	int left = 0;
	int top = 0;
	int id = 0;
	int choice;
	int weights[OBSTACLES]; 
	graph map(OBSTACLES);
	string person = "<img class=\"person\" src=\"person.jpg\">";
	string stairs =  "<img class=\"object\" src=\"stairs.png\">";
	string fence = "<img class=\"object\" src=\"fence.jpg\">";
	string grass = "<img class=\"object\" src=\"grass.png\">";
	string line;
	string connections[OBSTACLES];
	string html = "";
	fstream myfile;
	fstream start;
	fstream end;
	fstream end2;
	myfile.open("objects.html");
	start.open("start.html");
	
	while ( getline (start,line) )
    {
    	html += line+"\n";
    }
    start.close();
	
	for(id = 0; id < OBSTACLES; id++){
		connections[id] = "";
	}
	
	for(id = 0; id < OBSTACLES; id++){
		string html;
		cout<<"Enter what type of obsactle #"<<id<<" is \n1: grass, 2: stairs 3: fence\n";
		cin>>choice;
		switch(choice){
			case (1):
				weights[id] = 1;
				break;
			case (2):
				weights[id] = 6;
				break;
			case (3):
				weights[id] = 7;
				break;
		}
	}
	
	for(id = 0; id < OBSTACLES; id++){
		choice = -2;
		while(choice != -1){
 			cout<<"\nEnter an object "<<id<<" is connected to. -1 If "<<id<<" has no more connections\n";
			cin>>choice;
			if(choice != -1 && choice < OBSTACLES && choice >= 0){
				map.InsertEdge(id,choice,weights[choice]);
				connections[id] += to_string(choice)+",";
			}
		}
		cout<<endl;
	}
	
	
	for(id = 0; id <OBSTACLES; id++){
		
		string cur ="";
		cur = "<div id=\""+to_string(id)+"\" class=\"item\" connection=\""+connections[id]+"\" style=\"left:"+to_string(left)+"px; top:"+to_string(top)+"px;\">"+to_string(id);
		html +=cur;
		if(weights[id] == 1){
			html += grass;
		}
		else if(weights[id] == 6){
			html += fence;
		}
		else if(weights[id] == 7){
			html += stairs;
		}
		html += person;
		html += "</div>\n";
		
	
	
			left = rand() % 900;
			top = rand() % 900;
		
	}
	
	end.open("end.html");
	while ( getline (end,line) )
    {
    	html += line+"\n";
    }
    end.close();
    
    int begin;
    int finish;
    
    cout<<"Where would you like to start?\n";
    cin>>begin;
    cout<<"Where would you like to  finish?\n";
    cin>>finish;
    path route = map.ShortestPath(begin,finish);
    string routstr = "var path = [";
    for(int i =0; i<route.length;i++){
    	if(i != route.length-1)
    		routstr += "\""+to_string(route.location[i])+"\",";
    	else
    		routstr += "\""+to_string(route.location[i])+"\"";
    }
    html += routstr;
    html+= "];\n";
    html +="var end =\""+to_string(finish)+"\";\n";
    
    end2.open("end2.html");
	while ( getline (end2,line) )
    {
    	html += line+"\n";
    }
    end2.close();
    
    
    
	
	myfile<<html;
	myfile.close();
	cin.ignore();
	const string opendoc = "open.bat";
	system(opendoc.c_str());
	
	
	
	
	
	return 0;
}
