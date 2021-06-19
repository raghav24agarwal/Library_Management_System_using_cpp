#include<fstream>// file handling
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<iomanip>//setw(n)
#include<iostream>
#include<stdlib.h>//system (cls),
//#include<algorithm>
#include<windows.h>

using namespace std;

class book
{ 
 	private:

    string bno;//book number
    string bname;//book name
    string aname;//book author

 	public:

    void create_book()//entering book details
    {
        system("cls");
        cout<<"\nNEW BOOK ENTRY...\n";

        cout<<"\nEnter The book no.";
        cin>>bno;//There will be no spaces in book name so simpy do cin
        
        cout<<"\n\nEnter The Name of The Book ";
        cin.ignore();
        getline(cin,bname);
        
        cout<<"\n\nEnter The Author's Name ";
        //cin.ignore();
        getline(cin,aname);
        
        cout<<"\n\n\nBOOK CREATED.....";
    }



    void show_book()//showing book details
    {
        cout<<"\nBook no. : "<<bno;
        cout<<"\nBook Name : "<<bname;
        cout<<"\nAuthor Name : "<<aname;
        
    }

    void modify_book()//correction in details
    {
        cout<<"\nBook no. : "<<bno;
        cout<<"\nModify Book Name : ";
        cin.ignore();
        getline(cin,bname);

        cout<<"\nModify Author's Name of Book : ";
        cin.ignore();
        getline(cin,aname);

    }

    string retbno()//return book number
    {
        return bno;
    }

    void report()//used in printing all book details in same line having 30 spaces in between
    {
        
        cout<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl;// set width funtion in iomanip library for providing the n no of spaces in output
    }


}; //class book ends here



class student
{
	private:

    string admno;//admission no
    string name;//student name
    string stbno;//student book number
    int token;//only one book can be issued at one time

	public:

    void create_student()//new student registration
    {
        system("cls");
        cout<<"\nNEW STUDENT ENTRY...\n";

        cout<<"\nEnter The admission no. ";
        cin>>admno;//wont have any spaces

        cout<<"\n\nEnter The Name of The Student ";
        cin.ignore();
        getline(cin,name);

        token=0;//represents no of books
        stbno[0]='\0';//student book number at the time of student registration will be NULL
        cout<<"\n\nStudent Record Created..";
    }

    void show_student()//show the student info
    {
        cout<<"\nAdmission no. : "<<admno;
        cout<<"\nStudent Name : "<<name;
        
        cout<<"\nNo of Book issued : "<<token;
        if(token==1)
            cout<<"\nBook No "<<stbno;
    }

    void modify_student()//modify student info
    {
        cout<<"\nAdmission no. : "<<admno;
        //cout<<"\nModify Student Name : "<<name;
        cout<<"\nModify Student Name : ";
        cin.ignore();
        getline(cin,name);
        
    }

    string retadmno()
    {
        return admno;
    }

    string retstbno()
    {
        return stbno;
    }

    int rettoken()
    {
        return token;
    }

    void addtoken()//issue book
    {token=1;}

    void resettoken()//deposit book
    {token=0;}

    void getstbno(string t)
    {
        stbno = t;
    }

    void report()//ise call karenge all student display funtion mein usi k according width is set
    {cout<<"\t"<<admno<<setw(20)<<name<<setw(10)<<token<<endl;}

};//class student ends here



fstream fp;// file object fp for  writing student and book information into file
book bk;//class book ka object
student st;//class student ka object


void write_book()//function for creating file for book
{
    char ch;//choice
    fp.open("book.dat",ios::out|ios::app);
	//ios::out  opens a text file for writing.
    // ios::app    opens a text file for appending.
	//Open for output operations|All output operations are performed at the end of the file, appending the content to the current content of the file.
    

    do//ek baar toh file banegi
    {                                       
        system("cls");//clear screen
        bk.create_book();//calling create book

        fp.write((char*)&bk,sizeof(book));////Calling the write() function to write an object to a file/////ofstream_ob.write( (char *) & ob1, sizeof(ob1));
		/*  fstream fout;
        	fout.write( (char *) &obj, sizeof(obj) );*/

        cout<<"\n\nDo you want to add more record..(y/n?)";
        cin>>ch;//enter choice
    }
    while(ch=='y'||ch=='Y');
    fp.close();//closing file
}


void write_student()//function for creating file for student
{
    char ch;
    fp.open("student.dat",ios::out|ios::app);
    do
    {
        st.create_student();
        fp.write((char*)&st,sizeof(student));
        cout<<"\n\ndo you want to add more record..(y/n?)";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    fp.close();
}



//***************************************************************
//        function to read specific record from file
//****************************************************************



void display_spb(string n)//isme jo file pehle ban chuki use read karenge
{	//n here is book number
    cout<<"\nBOOK DETAILS\n";
    int flag=0;
   //stoi is used to convert string to int
    fp.open("book.dat",ios::in);//ios::in   opens a text file for reading.
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(n.compare(bk.retbno())==0)//agr no of book by funtion return book and entered by the user are same then only show book
        {
            bk.show_book();
             flag=1;
        }
    }
    
    fp.close();
    if(flag==0)//means wrong book number entered
        cout<<"\n\nBook does not exist";
    getch();
}



void display_sps(string n)//checking of student id if present in file or not 
{
    cout<<"\nSTUDENT DETAILS\n";
    int flag=0;
    fp.open("student.dat",ios::in);
    while(fp.read((char*)&st,sizeof(student)))
    {
        if(n.compare(st.retadmno())==0)//if returned admission number and string entered are equal 
        {
        	string str = st.retadmno();
        
            st.show_student();
            flag=1;
    	}
	}
    
    fp.close();
    if(flag==0)
    	cout<<"\n\nStudent does not exist";
     getch();
}




//***************************************************************
//        function to modify record of file
//****************************************************************




void modify_book()
{
    string n;
    int found=0;
    system("cls");
    cout<<"\n\n\tMODIFY BOOK REOCORD.... ";
    cout<<"\n\n\tEnter The book no. of The book";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);//open karenge file fp in read and write both modes
    while(fp.read((char*)&bk,sizeof(book)) && found==0)//jabtak book ka size hai and jabtak mil na jaye book
    {
        if (n.compare(bk.retbno())==0)//isse humara cursor aaega book no k end tak

        {
            bk.show_book();
            cout<<"\nEnter The New Details of book"<<endl;
            bk.modify_book();
            int pos=-1*sizeof(bk);//isse hum cursor ko le jaege ek book object peeche usse modify krne ke liye
            /*fs.seekp(-2, std::ios_base::cur); 
            Seek back two characters. Position at the s in Patches.*/



            fp.seekp(pos,ios::cur);// to reposition the cursor one object back from current position.
                
            fp.write((char*)&bk,sizeof(book));//book details firse write krr denge
            cout<<"\n\n\t Record Updated";
            found=1;
        }
    }

    fp.close();
    if(found==0)
        cout<<"\n\n Record Not Found ";//wrong book no entered
    getch();
}



void modify_student()
{
    string n;
    int found=0;
    system("cls");
    cout<<"\n\n\tMODIFY STUDENT RECORD... ";
    cout<<"\n\n\tEnter The admission no. of The student";
    cin>>n;
    fp.open("student.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
        if(n.compare(st.retadmno())==0)
        {
            st.show_student();
            cout<<"\nEnter The New Details of student"<<endl;
            st.modify_student();
            int pos=-1*sizeof(st);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&st,sizeof(student));
            cout<<"\n\n\t Record Updated";
            found=1;
        }
    }
    
    fp.close();
    if(found==0)
        cout<<"\n\n Record Not Found ";


    getch();
}




//***************************************************************
//        function to delete record of file
//****************************************************************


void delete_student()
{
    
    string n;
    int flag=0;    
    system("cls");
    cout<<"\n\n\n\tDELETE STUDENT...";
    cout<<"\n\nEnter The admission no. of the Student You Want To Delete : ";
    cin>>n;
    fp.open("student.dat",ios::in|ios::out);//previous student file
    fstream fp2;//temporary file object created
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);//Seek to beginning of the file.
    while(fp.read((char*)&st,sizeof(student)))
    {
        if(n.compare(st.retadmno())!=0)
        {
			fp2.write((char*)&st,sizeof(student));
            flag=1;
        }

    }
        
               
    fp2.close();
    fp.close();
    remove("student.dat");//file deleted
    rename("Temp.dat","student.dat");
    if(flag==1){
        cout<<"\n\n\tRecord Deleted ..";}
    else{
        cout<<"\n\nRecord not found";}
    getch();
}



void delete_book()
{
    
    string n;
    system("cls");
    cout<<"\n\n\n\tDELETE BOOK ...";
    cout<<"\n\nEnter The Book no. of the Book You Want To Delete : ";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(n.compare(bk.retbno())!=0)  
        
        {
            fp2.write((char*)&bk,sizeof(book));
        }
    }
        
    fp2.close();
    fp.close();
    remove("book.dat");
    rename("Temp.dat","book.dat");
    cout<<"\n\n\tRecord Deleted ..";
    getch();
}



//***************************************************************
//        function to display all students list
//****************************************************************



void display_alls()
{
    system("cls");
    fp.open("student.dat",ios::in);
    if(!fp)
    {
        cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
        getch();
        return;
    }

    cout<<"\n\n\t\tSTUDENT LIST\n\n";
    cout<<"==================================================================\n";
    cout<<"\tAdmission No."<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
    cout<<"==================================================================\n";

    while(fp.read((char*)&st,sizeof(student)))
    {
        st.report();///report print kara rhe
    }
         
    fp.close();
    getch();
}



//***************************************************************
//        function to display Books list
//****************************************************************



void display_allb()
{
    system("cls");
    fp.open("book.dat",ios::in);
    if(!fp)
    {
        cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
        getch();
        return;
    }

    cout<<"\n\n\t\tBook LIST\n\n";
    cout<<"=========================================================================\n";
    cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author\n";
    cout<<"=========================================================================\n";

    while(fp.read((char*)&bk,sizeof(book)))
    {
        bk.report();
    }
    fp.close();
    getch();
}



//***************************************************************
//        function to issue book
//****************************************************************



fstream fp1;


void book_issue()
{
    
    
    string sn,bn;
    int found=0,flag=0;
    system("cls");
    cout<<"\n\nBOOK ISSUE ...";
    cout<<"\n\n\tEnter The student's admission no.";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
        if(sn.compare(st.retadmno())==0)////if student ki id mil gyi
      
        {
            found=1;
            if(st.rettoken()==0)//token value is 0 means no book issued
            {
                cout<<"\n\n\tEnter the book no. ";
                cin>>bn;
                while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
                {
                    
                    if(bn.compare(bk.retbno())==0) //agr book no shi hai book de do
                	{
                        bk.show_book();//show the book
                        flag=1;
                        st.addtoken();//token value 1 krr do jisse fir issue na ho paye
                        st.getstbno(bk.retbno());
                        int pos=-1*sizeof(st);//student ka size multiply -1 means ek object peeche le aaenge pointer
                        fp.seekp(pos,ios::cur);
                        fp.write((char*)&st,sizeof(student));
                        cout<<"\n\n\t Book issued successfully\n\nPlease Note: Write current date in backside of book and submit within 15 days fine Rs. 1 for each day after 15 days period";
                    }
                }
                if(flag==0)
                    cout<<"Book no does not exist";
            }
            else
                cout<<"You have not returned the last book ";

        }
    }
          

    if(found==0)
        cout<<"Student record not exist...";
    getch();
    fp.close();
    fp1.close();
}



//***************************************************************
//        function to deposit book
//****************************************************************




void book_deposit()
{
    
    string sn,bn;
    int found=0,flag=0,day,fine; //flag is for book, found is for student
    system("cls");
    cout<<"\n\nBOOK DEPOSIT ...";
    cout<<"\n\n\tEnter The student's admission no.";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
    	if(sn.compare(st.retadmno())==0)
        {
            found=1;
            if(st.rettoken()==1) //mtlab book issued hai
            {
	            while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
	            {
	            	if(st.retstbno().compare(bk.retbno())==0) 
	           		{
	                	bk.show_book();
		                flag=1;
		                cout<<"\n\nBook deposited in no. of days";
		                cin>>day;
                		if(day>15)
		                {
		                   fine=(day-15)*1;
		                   cout<<"\n\nFine has to deposited Rs. "<<fine;
		                }
                    st.resettoken();//token ko 0 krrdo jisse wo ffirse issue kr paye book
                    int pos=-1*sizeof(st);
                    fp.seekp(pos,ios::cur);
                    fp.write((char*)&st,sizeof(student));
                    cout<<"\n\n\t Book deposited successfully";
            		}
            	}
        		if(flag==0)
            		cout<<"Book no does not exist";
            }
         	else
            	cout<<"No book is issued..please check!!";
        }
    }

    if(found==0)
    cout<<"Student record not exist...";
    getch();
	fp.close();
  	fp1.close();
}



//***************************************************************
//        INTRODUCTION FUNCTION
//****************************************************************



void intro()
{
    system("cls");
    //gotoxy(35,11);
    cout<<"LIBRARY ";
    //gotoxy(35,14);
    cout<<"MANAGEMENT ";
    //gotoxy(35,17);
    cout<<"SYSTEM";
    cout<<"\n\nMADE BY : RAGHAV AGARWAL";
    cout<<"\n\nCOLLEGE : DIT UNIVERSITY";
    getch();
}



//***************************************************************
//        ADMINISTRATOR MENU FUNCTION
//****************************************************************



void admin_menu()
{
    system("cls");
    int ch2;
    cout<<"\n\n\n\tADMINISTRATOR MENU";

    cout<<"\n\n\t1.CREATE STUDENT RECORD";
    cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORD";
    cout<<"\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
    cout<<"\n\n\t4.MODIFY STUDENT RECORD";
    cout<<"\n\n\t5.DELETE STUDENT RECORD";
    cout<<"\n\n\t6.CREATE BOOK ";
    cout<<"\n\n\t7.DISPLAY ALL BOOKS ";
    cout<<"\n\n\t8.DISPLAY SPECIFIC BOOK ";
    cout<<"\n\n\t9.MODIFY BOOK ";
    cout<<"\n\n\t10.DELETE BOOK ";
    cout<<"\n\n\t11.BACK TO MAIN MENU";
    cout<<"\n\n\tPlease Enter Your Choice (1-11) ";
    cin>>ch2;
    switch(ch2)
    {
            case 1: {
	            		system("cls");
	                	write_student();
	                	break;
	                }

            case 2: {
            			display_alls();
            			break;
            		}

            case 3: {
            			string num;
                     	system("cls");
                   		cout<<"\n\n\tPlease Enter The Admission No. ";
                   		cin>>num;
                   		display_sps(num);
                   		break;
                   	}
            case 4: {
            			modify_student();
            			break;
            		}

            case 5: {
            			delete_student();
            			break;
            		}

        	case 6: {
	        			system("cls");
	            		write_book();
	            		break;
	            	}

        	case 7: {
	        			display_allb();
	        			break;
	        		}

        	case 8: 
                   	{
                   		string num;
                   		system("cls");
                   		cout<<"\n\n\tPlease Enter The book No. ";
                   		cin>>num;
                   		display_spb(num);
                   		break;
                   	}
            
        	case 9: 
        			{
                		modify_book();
                		break;
                	}

        	case 10:{ 
                		delete_book();
                		break;
                	}

        	case 11: return;

        	default:
                	cout<<"\a";
    }
    admin_menu();
}



//***************************************************************
//        MAIN FUNCTION
//****************************************************************


int main()
{
    char ch;
    intro();
    do
    {
        system("cls");//TO CLEAR THE SCREEN IN THE STLIB.H LIBRARY
        cout<<"\n\t KINDLY CHOOSE 1,2,3 OR 4 FOR THE FOLLOWING SERVICES";
        cout<<"\n\n\n\t\t\t\tMAIN MENU";
        
        cout<<"\n\n\t 1. BOOK ISSUE";
        cout<<"\n\n\t 2. BOOK DEPOSIT";
        cout<<"\n\n\t 3. ADMINISTRATOR MENU";
        cout<<"\n\n\t 4. EXIT";
        cout<<"\n\n\t Please Select Your Option (1-4) ";
        ch=getchar();
        switch(ch)
        {
            case '1':
            		{
            			system("cls");
                 		book_issue();
                    	break;
                    }
            case '2':
              		{
              			book_deposit();
                     	break;
                    }

            case '3':
              		{
              			admin_menu();
                 		break;
                 	}
              
            case '4':exit(0);
            
            default :cout<<"\a";
        }

    }while(ch!='4');

    return 0;
}





