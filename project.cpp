#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>

using namespace std;

int file_size(FILE**fp1)
{
    fseek(*fp1,0L,2);                //point file pointer to end of source file
    int s=ftell(*fp1);                            //storing file size returned by ftell function
    if(s>(pow(2,30)))                         //checking file size if greater than 1 GB then exit with error message
    {
        cout<<'\t'<<"Maximum size of file should not be greater than 1Gb"<<endl;
        cout<<endl<<'\t'<<"Press Enter to exit"<<endl;
        getch();
        exit(1);                                               //end of program
    }
    rewind(*fp1);                                       //point file pointer again at starting
    return s;
}
void encrypt_file(FILE **fp1,FILE **fp2,int key,int max_size)
{
    char ch;
    int i=10,curr_position,percent;

    //writing key value into new encrypted file//
    putw(key,*fp2);


    cout<<'\t'<<"Password successfully stored in encrypted file.."<<endl;
    cout<<endl<<'\t'<<"File Encryption Started.."<<endl;

    while(1)
    {
        ch=getc(*fp1);             //reading characters one by one
        if(ch==EOF)
        {
            cout<<'\t'<<"File Encrypted Successfully"<<endl;
            return;            //exit if end of file reached
        }
        else
        {
            ch+=key;                                //add key to  character and write it to file
            fputc(ch,*fp2);
            curr_position=ftell(*fp1);
            percent=(i*max_size)/100;
            if(curr_position==percent)
            {
                cout<<endl<<'\t'<<'\t'<<i<<" % data encryption completed.."<<endl;
                i+=10;
            }

        }
    }//end of while loop
}
void decrypt_file(FILE **fp1,FILE **fp2,int max_size)
{
    int key=getw(*fp1);             //reading key stored in encrypted file
    char ch;
    int k,i=10,curr_position,percent;
    cout<<'\t'<<"Enter password :: "<<endl;
    cin>>k;
    if(key==k)
    {
        cout<<endl<<'\t'<<"Password matched!!your File decryption will begin shortly"<<endl;
        while(1)
        {
            ch=fgetc(*fp1);
            if(ch==EOF)
            {
                cout<<endl<<'\t'<<"Your File has been decrypted successfully"<<endl;
                return;
            }

            else
            {
                ch-=k;                                   //perform same operation on every character
                fputc(ch,*fp2);                         // write character to new file
                curr_position=ftell(*fp1);          // store current position of file pointer into some variable
                percent=(i*max_size)/100;           //calculate percentage
                if(curr_position==percent)
                {
                    cout<<'\t'<<'\t'<<i<<" % data decryption completed.."<<endl;
                    i+=10;

                }

            }
        }
    }
    else
    {
        cout<<'\t'<<"Password not matched!!"<<endl;
    }

}

int main(int argc,char *argv[])
{
    FILE *fp1,*fp2;
    char file_name[100];
    int key,opt,i=1,max_size;
    char ch;
    do
    {
        cout<<"                MENU"<<endl;
        cout<<"    Option 1.Encrypt a file "<<endl;
        cout<<"    Option 2.Decrypt a file "<<endl;
        cout<<"    Enter your Option:"<<endl;
        cin>>opt;

        switch(opt)
        {
        case 1:
            fp1=fopen(argv[1],"r");                 //open source file
            if(fp1==NULL)
            {
                cout<<'\t'<<'\t'<<argv[1]<<"Error!! File can't be open"<<endl;
                exit(1);  //exit in case of error
            }
            else
            {
                cout<<'\t'<<argv[1]<<" file found"<<endl;
                max_size=file_size(&fp1);          //check for maximum size and store size of file in some variable


            }
            cout<<endl<<'\t'<<"Enter encrypted file name( ABC.ecrypt )"<<endl;
            fflush(stdin);          // function to empty  memory buffer
            cin.get(file_name,50);              // read file name entered by user
            fp2=fopen(file_name,"w");       //create new file and open it in write mode

            if(fp2!=NULL)
            {
                cout<<'\t'<<file_name<<" File Created Successfully"<<endl;
            }
            cout<<'\t'<<"Enter password for encrypted File:: "<<endl;
            fflush(stdin);
            cin>>key;               //provide a key
            encrypt_file(&fp1,&fp2,key,max_size);
            fclose(fp1);
            fclose(fp2);    //close all file
            cout<<'\t'<<"Press Enter to exit"<<endl;
            getch();
            exit(0);        //end of program

        case 2:
            fp1=fopen(argv[1],"r");                 // open encrypted file in read mode
            cout<<'\t'<<"Enter decrypted file name( ABC.decrypt)"<<endl;
            fflush(stdin);
            cin.get(file_name,50);          //create new decrypted file and open it in read mode
            fp2=fopen(file_name,"w");
            if(fp1==NULL)
            {
                cout<<'\t'<<'\t'<<argv[1]<<"Error!! File can't be open"<<endl;
                exit(1);//exit in case of error
            }
            else
                {
                  cout<<'\t'<<argv[1]<<"file found"<<endl;
                   max_size=file_size(&fp1);        //calculate max size of file and store the size in max_size varaible
                }
            if(fp2==NULL)
            {
                cout<<'\t'<<'\t'<<file_name<<"File cannot be created!!"<<endl;
                exit(1);
            }
            else
             cout<<'\t'<<file_name<<" file created successfully"<<endl;

            decrypt_file(&fp1,&fp2,max_size);           ///call decryption function
            fclose(fp1);
            fclose(fp2);
            cout<<'\t'<<"Press Enter To Exit"<<endl;
            getch();
            exit(0);
        default:
            cout<<'\t'<<"Please Enter a Valid Option"<<endl;

        }

    }while(toupper(ch)=='Y');  /// end of while loop if not y
    getch();
}
