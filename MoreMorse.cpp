	

			/****************************************************************\
		       |**		   	      -=======-				**|
		     <(***			   |   PROJECT   |			***)>
		       |**				=====				**|
			\****************************************************************/




			/****************************************************************\
		       |		   HEADER FILES USED IN PROJECT			  |
			\****************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstdio>
#include <cstring>
#include "troll"	//  Header for intro(), msgroll().
#include "cmorse"	//  Header for controlling GPIO pin.


using namespace std;


			/****************************************************************\
		       |		   CLASS USED IN PROJECT			  |
			\****************************************************************/


class info
{
    private:
        char Msg[50];
        char FullDate[50];
    public:
        char label[30];
        void getinfo();
        void seeinfo();
        char* passMsg();   
};

char* info::passMsg()
{
	return Msg;
}
		
void info::seeinfo()
{
   	 cout<<"\n\n\t Message label : "<<label
       	     <<"\n\n\t Message entered on : "<<FullDate
             <<"\n\n\t "<<Msg<<"\n";
}

void info::getinfo()
{
   	 time_t rawtime;
  	 tm *timeinfo;
   	 time (&rawtime);
 	 timeinfo = localtime(&rawtime);
  	 strftime (FullDate,50,"%c",timeinfo);

  	 cout<<"   Enter your message : ";
  	 cin.getline(Msg,50);

 	 cout<<"\n   Enter a label for this message :  ";
 	 cin.getline(label,30);
    
  	 blinkstring(Msg);
	
}


			/****************************************************************\
		       |	GLOBAL DECLARATION OF STREAM OBJECT, CLASS OBJECT	  |
			\****************************************************************/


info st;
fstream fp;


			/****************************************************************\
		       |		   FUNCTION TO WRITE TO FILE			  |
			\****************************************************************/


void entermsg()
{
    	cout<<"\n\n\t\t Enter Message\n "
            <<"\t\t~--------------~\n\n";
   	 fp.open("info.dat",ios::app);
   	 st.getinfo();
   	 fp.write((char*)&st,sizeof(st));
   	 fp.close();
   	 cout<<"\n\n   Message Logged!";
}


			/****************************************************************\
		       |		   FUNCTION TO READ FROM FILE			  |
			\****************************************************************/


void viewmsg()
{
    char choice,ch,LABEL[30];
    int flag=1;
    while(ch!='n'&&ch!='N')
    {
        cout<<"\n\n\t\t\t\t  View Message\n "
            <<"\t\t\t\t~--------------~\n\n";
        cout<<"\n\n\t  Choose Option : "
            <<"\n\n   1. View all messages till date."
            <<"\n\n   2. View a message with its label. \n";
        cin>>choice;
        cin.ignore();
        switch(choice)
        {
            case '1':   fp.open("info.dat",ios::in);
                        while(fp.read((char*)&st,sizeof(st)))
                        {
                            st.seeinfo();
                        }
                        fp.close();
                    break;
			
            case '2':
                        cout<<"\n\n Enter label to search for : ";
                        cin.getline(LABEL,30);
                        fp.open("info.dat",ios::in);
                        while(fp.read((char*)&st,sizeof(st)))
                        {
                            if(strcmp(LABEL,st.label)==0)
                            {
                                flag=0;
                                st.seeinfo();
                                char ch;
                                cout<<" Display message in morse? (Y/N)";
                                cin>>ch;
                                cin.ignore();
                                if(ch=='y'||ch=='Y')
				{	
					blinkstring(st.passMsg());
				}
                            }
                        }
                        if(flag)
                            cout<<" No such entry!  ";

                        fp.close();
                    break;
			
            default:    cout<<"Wrong choice ";
        }
        cout<<"\n\n\tWant to go back to the previous menu ? (Y/N) \n";
        cin>>ch;
        cin.ignore();
        system("clear");
    }
}


			/****************************************************************\
		       |		FUNCTION TO DELETE ENTRY FROM FILE		  |
			\****************************************************************/


void deleteemsg()
{
    char LABEL[30];
    fstream fp2;

    cout<<"\n\n\t\t\t\t Delete Message\n "
        <<"\t\t\t\t~--------------~\n\n";
    cout<<"\n\n   Please Enter the label of the message you want to delete : ";
    cin.getline(LABEL,30);

    fp.open("info.dat",ios::in);
    fp2.open("Temp.dat",ios::out);

    while(fp.read((char*)&st,sizeof(st)))
    {
        if(strcmp(st.label,LABEL))
        {
            fp2.write((char*)&st,sizeof(st));
        }
    }

    fp2.close();
    fp.close();
    remove("info.dat");
    rename("Temp.dat","info.dat");
    cout<<"\n\n\tEntry removed...\n";

}


			/****************************************************************\
		       |		 	  MAIN FUNCTION				  |
			\****************************************************************/


int main()
{
	setgpiopin(1);
	intro();
    	char ch,choice;
	while(ch!='n'&&ch!='N')
    	{
        	cout<<"\n\n\t\t\t         <==========>\n"
            	    <<"\t\t\t\t     MENU\n"
		    <<"\t\t\t         <==========>\n\n\n"
		    <<"\t  1. Enter new message. "
		    <<"\n\n\t  2. View earlier messages. "
		    <<"\n\n\t  3. Delete earlier messages. "
		    <<"\n\n\t  4. Quit";
		cout<<"\n\n\t\t\tEnter choice (1-4): ";
		cin>>choice;
		cin.ignore();
		switch(choice)
		{
		    case '1':   system("clear");
				msgroll("LOADING...",2);
				entermsg();
			    break;
		    case '2':   system("clear");
				msgroll("LOADING...",2);
				viewmsg();
			    break;
		    case '3':   system("clear");
				msgroll("LOADING...",2);
				deleteemsg();
			    break;
		    case '4':   system("clear");
				system("sl");
				cout<<"\t\t\t\tTHANK YOU!! \n";
				system("sleep 1s");
				exit(0);
		    default:    cout<<"\n\tWrong choice! ";
		}
		cout<<"\n\n\tWant to go back to the main menu?  (Y/N) ?";
		cin>>ch;
		cin.ignore();
		system("clear");
	}
	system("sl");
    	cout<<"\t\t\t\tTHANK YOU!! \n";
	system("sleep 1s");
}


			/****************************************************************\
		       |		 	     THE END				  |
			\****************************************************************/

