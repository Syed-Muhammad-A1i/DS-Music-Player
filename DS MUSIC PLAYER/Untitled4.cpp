#include<iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <conio.h>
#include<windows.h>
#include<mmsystem.h>
#include<fstream>
#include<unistd.h>
#include<string>
#include <sstream>
#include "MR 2.cpp"

using namespace std;

int serial_number=0;

//void menu();

class node{
	public:
		int key;
		node *prev;
		node *next;
		string name;
		int repeat;
		
		node(int number,string name){
			key = number;
			prev = NULL;
			next = NULL;
			repeat = 0;
			this->name=name;
		}
	
	
};
class Queue{
	public:
		string name;
		string pname;
		int key;
		Queue *next;
		Queue *front= NULL;
        Queue *rear=NULL;
        
    void enQueue(node* n){
	    Queue *temp= new Queue;
	    temp->name=n->name;
	    temp->key=n->key;
	    temp->next=NULL;
	    
        if(rear==NULL){
            front=rear=temp;
        }
        else
        {
            rear->next=temp;
            rear=temp;
        }
        Filing(n,n->name);
        
	}
	void Filing(node *l,string name){
		if(l->key==0)
		{
			ofstream list;
			list.open("PL.txt");
			list << l->key << "\n" ;
			list.close();
			ofstream sl;
			sl.open("PL NAMES.txt");
			sl << l->name << "\n" ;
			sl.close();
			 
			return;
		}
		ofstream list;
		list.open("PL.txt",ios::app);
		list << l->key<< "\n"  ;
		list.close();
		ofstream sl;
		sl.open("PL NAMES.txt",ios::app);
		sl << name << "\n" ;
		sl.close();
	}
		
	Queue* deQueue(){
		Queue *temp=front;
	    if(front==NULL){
	        cout<<"Queue is empty"<<endl;
	        return NULL;
	    }
	    else
	    {
	       front=front->next;
	       //delete(temp);
	       
	       return temp;
	    }
	}
	void displayQueue()
	{
		Queue *temp=front;
		while(temp!=rear->next)
		{
			cout << temp->name << endl;
		    temp=temp->next;
		}
	
		cout<<"\n";
	}
	
	void playNow(Queue* node) //play
	{
	    cout<<"-------Currently Playing "<<node->name<<"---------"<<endl;
	}
	
	void addToPlaylist(node* song)
	{
	        enQueue(song);
	}
	
	void streamPlaylist(int songscount)
	{
	    int i=0;
	    if(front==NULL)
		{
	        cout<<"No song to play"<<endl;
	    }
	    else
	    {
	        while(i<songscount)
			{
	            Queue* getSong=deQueue();
	            playNow(getSong);
	            i++;
	        }
	    }
	}
	};

Queue q1;

class Linklist{
	
	public:
		node *head;
		Linklist(){
			head=NULL;
		}
		int getrepeat(int key){
			node* temp=head;
			while (temp->key!=key||temp->next!=head){
				temp=temp->next;
			}
			return temp->repeat; 
		}
		node *gethead(){
			return head;  
		}
		
		void Filing(node *l,string name){
			if(l->key==0)
			{
				ofstream list;
				list.open("list.txt");
				list << l->key << "\n" ;
				list.close();
				ofstream sl;
				sl.open("SONG NAMES.txt");
				sl << name << "\n" ;
				sl.close();
				 
				return;
			}
			ofstream list;
			list.open("list.txt",ios::app);
			list << l->key<< "\n"  ;
			list.close();
			ofstream sl;
			sl.open("SONG NAMES.txt",ios::app);
			sl << name << "\n" ;
			sl.close();
		}
		
		void Insert(int number,string name){
			node *nn=new node(number,name);
		
			
			if (head == NULL){
				head = nn;
				nn->next=head;
				nn->prev=nn;
				Filing(nn,name);
				serial_number++;
				return;	
			}
			else{
				node *last = head;
	 	
			 	while (last->next != head)
			 	{
			 		last = last->next;
				}
				 
				Filing(nn,name);
				last->next=nn;
				nn->prev = last;
				nn->next=head;
				serial_number++;
			}
			
			
			
		}
		
		
		void make_LL(int number,string name){
			node *nn=new node(number,name);
			
			if (head == NULL){
				head = nn;
				nn->next=head;
				nn->prev=nn;

				return;	
			}
			else{
				node *last = head;
	 	
			 	while (last->next != head)
			 	{
			 		last = last->next;
				}
				 

				last->next=nn;
				nn->prev = last;
				nn->next=head;
				head->prev=nn;
				serial_number = ++number;
			}
			
			
			
		}
		
		void file_to_LL(){
			fstream newfile;
			fstream sname;
			sname.open("SONG NAMES.txt",ios::in);
			
				newfile.open("list.txt",ios::in); 
			    if (newfile.is_open()&&sname.is_open()){ 
					string tp;
			   	  	string n;
			    	while(getline(newfile, tp)){ 
					getline(sname,n);
					int num;	
					stringstream ss;  // typecasting string int a integer
					ss << tp;
				   	ss >> num;
					make_LL(num,n);
		        	
			      }
			      sname.close();
			      newfile.close(); //close the file object.
			  }
		}
		
		void print(){
			node* temp=head;
			while(temp->next!=head){
				cout << temp->key << "   " << temp->name << endl;
				temp=temp->next;
			}
			cout << temp->key << "   " << temp->name << endl;
				
		}
		void Play(node *head){
		int sng,c=0;
		node *temp = head;
		node* d=head;
		print();
	
		cout << "\nEnter the option: ";
		cin >> sng;
		while((temp->key!=sng || temp->next==head))
		{
			temp = temp->next;
		}
		Playingtracks(temp,1);
	}
	
	
	void Playingtracks(node *temp,int n){
			
		if(n!=0){		
			while(1){
				switch (temp->key){
					case 1:{
						cout << "Now playing (Thankyou,next.) ...\n";
						mciSendString("open \"Thank u,next.MP3\" type mpegvideo alias mp3", NULL, 0, NULL);
						mciSendString("play mp3", NULL, 0, NULL);
						temp->repeat++;
						display_panel(temp);					
						break;
					}
					case 2:{
						cout << "Now playing (ROVER) ...\n";
						mciSendString("open \"Rover.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
						mciSendString("play mp3", NULL, 0, NULL);
						temp->repeat++;
						display_panel(temp);					
						break;
					}
					case 3:{
						cout << "Now playing (Dinero) ...\n";
						mciSendString("open \"dineros.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
						mciSendString("play mp3", NULL, 0, NULL);
						temp->repeat++;
						display_panel(temp);
						break;
					}
					case 4:{
						cout << "Now playing (Little Do You Know) ...\n";
						mciSendString("open \"Little Do You Know _.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
						mciSendString("play mp3", NULL, 0, NULL);
						temp->repeat++;
						display_panel(temp);
						break;
					}
					case 5:{
						cout << "Now playing (Mood) ...\n";
						mciSendString("open \"Mood.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
						mciSendString("play mp3", NULL, 0, NULL);
						temp->repeat++;
						display_panel(temp);
						break;
					}
					case 6:{
						cout << "Now playing (Pillow Talk) ...\n";
						mciSendString("open \"PillowTalk.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
						mciSendString("play mp3", NULL, 0, NULL);
						temp->repeat++;
						display_panel(temp);
						break;
					}
					case 7:{
						cout << "Now playing (Obsessed) ...\n";
						mciSendString("open \"Obsessed.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
						mciSendString("play mp3", NULL, 0, NULL);
						temp->repeat++;
						display_panel(temp);
						break;
					}
					case 8:{
						cout << "Now playing (Sexy And I Know it) ...\n";
						mciSendString("open \"SexyandIKnowIt.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
						mciSendString("play mp3", NULL, 0, NULL);
						temp->repeat++;
						display_panel(temp);
						break;
					}
					case 9:{
						cout << "Now playing (Beggin') ...\n";
						mciSendString("open \"Beggin'.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
						mciSendString("play mp3", NULL, 0, NULL);
						temp->repeat++;
						display_panel(temp);
						break;
					}
					case 10:{
						cout << "Now playing (Sorry) ...\n";
						mciSendString("open \"SORI.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
						mciSendString("play mp3", NULL, 0, NULL);
						temp->repeat++;
						display_panel(temp);
						break;
					}
					default:{
						
						break;
					}
						
				}
				break;
			}
		}
	
	}
	void display_panel(node* temp)
	{
					
		system("cls");
		cout << "Now playing ("<<temp->name<<") ...\n";
		cout <<" \t  <- \t  || \t   ->  \t   :"<<endl;
		cout <<"\tPREV(A)\tPAUSE(W) NEXT(D) OPTIONS";
		cout<<endl;
	
	char c;
	char pl;
	int k;
	char opt;
	while(k!=2){
	    switch((c=getch())) {
	    	
	        case 'A':{
	        	mciSendString("close mp3", NULL, 0, NULL);
	        	cout << endl << "prev" << endl; 
	             temp=temp->prev;
	            Playingtracks(temp,1);
				break;
			}
	            
	            
	        case 'D':{
	        	mciSendString("close mp3", NULL, 0, NULL);
	        	cout << endl << "NEXT" << endl;  
	        	temp=temp->next;
	            Playingtracks(temp,1);
				break;
			}
	            
	            
	        case 'W':{
         		cout << endl << "PAUSED" << endl; 
         		mciSendString("pause mp3", NULL, 0, NULL);
         		loop:
				cout <<" \t  <- \t  > \t   ->  \t   :"<<endl;
				cout <<"\tPREV(A)\tPAUSE(W) NEXT(D) OPTIONS"<<endl;
				char cc=getch();
         		if(cc=='W')
         		{
         		mciSendString("play mp3", NULL, 0, NULL);	
				}
				else
				goto loop;
        		
				break;
			 }
	        
	            
	        case ':':{
	        	cout << endl << "OPTIONS" << endl;  
	        	cout<<"1.ADD TO PLAYLIST (P)\n2.Exit Player (E)\n";
	        	
				switch((opt=getch())) 
				{
	        		case 'P':{
	        			cout<<"Enter playlist name: ";
	        			
	        			q1.addToPlaylist(temp);
	        
	        			cout << endl << "SONG ADDED TO PLAYLIST" << endl;
						break;
					}
	            
	            	case 'E':{
	            		cout << endl << "Exiting..." << endl;
	            		mciSendString("close mp3", NULL, 0, NULL);
	            		menu();
						break;
					}
				
				}
			}
	        default:{
				break;
			}
	        break;    
	            
	    }
        
	   
	
	}
	}
	void Track_repeat()
	{
		node* R=head;
		LL obj1;
		while(R->next!=head)
		{
			obj1.mostlistenedsong(R->repeat,R->key);
			R=R->next;
		}
		obj1.sorting();
	
		obj1.reverse();
		obj1.printnodes();
		cout<<endl;
		rpNode* MR_=new rpNode;
		MR_=obj1.mostrepeated();
		
		R=head;
		while(R->next!=head)
		{
			if(MR_->key==R->key)
			{
			cout<<"Most repeated song is: "<<R->name<<" ("<<R->key<<")";	
			}
			R=R->next;
		}
	}
	
	void menu(){
		system("cls");
		int opt;
		cout << "\n1. Play a Song.\n";
	
		cout << "2. View a Playlist.\n";
		cout << "3. View Mostplayed Songs.\n";
		cout << "4. Exit.\n";
		cout << "Enter the option : ";
		cin>> opt;
		
		switch (opt){
			case 1:{
				//playsong
					Play(head);
	
				break;
			}
			case 2:{
				//viewplaylist
				system("cls");
				cout<<endl<<"PLAYLIST"<<endl<<endl;
				q1.displayQueue();
				sleep(5);
				menu();
				
				break;
			}
			
			case 3:{
				
				//mostplayedsongs
				Track_repeat();
				sleep(5);
				menu();
				break;
			}
			case 4:{
				//exit
				exit(1);
				break;
			}
			
			default:{
				cout << "Enter the correct option\n";
				break;
			}
			
		}	
		
		
		return;
	}
	

};
int main(){
	Linklist obj;
	obj.file_to_LL();
	obj.print();
	obj.menu();
//	obj.Play(obj.gethead());
//	obj.Track_repeat();
}
