#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
/*
This program is a Multiple-Choice Test Grader.
Authors:Ercan Tunç Güçlü    Evren Korkmaz   Emre Balikci  Enes Recep Çınar    
*/
//Declaring global variables
int SIZE = 0;
int admin_account_size=3;
int student_account_size;
int user_element;
//Declaring structs
struct Questions
{
    char question[100];
    char option[100];
    char trueanswers;
};

struct Student
{
    char name[50];
    int number;
    int grade;
    int password;

}std;

struct Account
{
    char name[20];
    int password;
};

//Function prototypes
void extraGettingQuestions(FILE *true_answers,FILE *questions, struct Questions questionList[]);
void gettingQuestions(FILE *true_answers,FILE *questions, struct Questions questionList[]);
void displayQuestions(struct Questions questionList[]);
void addQuestion(FILE *true_answers,FILE *questions, struct Questions questionList[]);
void deleteQuestion(FILE *true_answers,FILE *questions, struct Questions questionList[]);
void updateQuestion(FILE *true_answers,FILE *questions, struct Questions questionList[]);
int randomquestion(FILE *questions,struct Questions questionsList[],struct Student stu_account[]);
void histogram(FILE *fl,struct Student std[]);
void seetopfive(FILE *fl,struct Student std[]);

int adminfunction(struct Account admin_account[]);
void userRegister(FILE *fl,struct Student std[],FILE *user);
int userLogin(struct Student stu_account[],FILE *fl);
void getting_admin_Accounts(FILE *admin,struct Account admin_account[]);
void getting_stu_Accounts(FILE *stu,struct Student stu_account[]);
void show_score(struct Student stu_account[]);

int main()
{
    //Variable declaration
    FILE *fl;
    FILE *user;
    FILE *questions;
    FILE *true_answers;
    struct Questions questionList[100];//Declaring struct arrays
    struct Account admin_account[3];
    struct Student std[100];
    FILE *account_fptr;//Declaring file pointer
    int login,instructorlogin,studentlogin,flag;

    //We call these functions to get student and teacher's names and passwords from files and we put them to structs
    getting_admin_Accounts(account_fptr,admin_account);
    getting_stu_Accounts(account_fptr,std);
    printf("***MULTIPLE-CHOICE TEST GRADER***\n\n\n");
    while (login!=4){   //While choice isn't equal to 4 because 4 means EXIT
    printf("**********************************\n");
    printf("**\tOPTIONS\t\t\t**\n**\t1)Login as Instructor\t**\n**\t2)Login as Student\t**\n**\t3)Register\t\t**\n**\t4)EXIT\t\t\t**\n");//OPTIONS
    printf("**********************************\n");
    scanf("%d",&login);//User enters a choice
    system("cls");//To make program look more tidy

    extraGettingQuestions(true_answers,questions, questionList);//To find how many numbers there are and make SIZE equal to it

    switch (login)
    {

    case 1:                 //Instructor
       flag= adminfunction(admin_account);//admin function returns 1 or 0. 1 means user entered correct id and password.
        if(flag == 1)
        {
            system("cls");//To make program look more tidy
            do
            {
                printf("**********************************\n");                 //Instructor Menu
                printf("\tWhat do you want to do?\n\n");
                printf("\t1) See all Questions\n");
                printf("\t2) Add new Question\n");
                printf("\t3) Delete a Question\n");
                printf("\t4) Update a Question\n");
                printf("\t5) See TOP-5 Students\n");
                printf("\t6) See Histogram\n");
                printf("\t7) Logout\n");
                printf("**********************************\n");
                scanf("%d",&instructorlogin);   //User enters a choice
                system("cls");
                switch (instructorlogin)
                {
                case 1://If Instructor enters 1 he/she sees all questions

                    gettingQuestions(true_answers,questions, questionList);//we get questions to struct arrays
                    displayQuestions(questionList);//display questions
                    break;

                case 2://If Instructor enters 2 he/she can add a new question

                    gettingQuestions(true_answers,questions, questionList);//We get questions to struct arrays
                    addQuestion(true_answers,questions, questionList);//Call add fnc
                    break;

                case 3://If Instructor enters 3 he/she can delete a question


                    gettingQuestions(true_answers,questions, questionList);//We get questions to struct arrays
                    displayQuestions(questionList);//first show all questions
                    deleteQuestion(true_answers,questions, questionList);//Call delete fnc

                    break;

                case 4://IF user enters 4 he/she update a question.To do this we first call delete fnc and then add fnc

                    gettingQuestions(true_answers,questions, questionList);//We get questions to struct arrays
                    updateQuestion(true_answers,questions, questionList);//Call update fnc
                    break;

                case 5://If user enters 5 he/she sees top-5 students

                    gettingQuestions(true_answers,questions, questionList);//We get questions to struct arrays
                    seetopfive(fl,std);//Call seetopfive fnc
                    break;

                case 6://If user enters 6 he/she sees a histogram

                    gettingQuestions(true_answers,questions, questionList);//We get questions to struct arrays
                    histogram(fl,std);//Call histogrm fnc
                    break;

                case 7://If user enters 7 he/she logs out
                    system("cls");
                    printf("BYE BYE\n");

                    break;

                default://If user doesn't enter any of these choice print Enter a Valid Choice. And send him to begining of loop.
                    printf("Enter a Valid Choice\n");

                }
            }while(instructorlogin != 7);
        }
        else//If flag isn't equal to 1
        {
            printf("Try Again!\n");
        }


        break;

    case 2://If user chooses 2 he/she enters as a student
        getting_stu_Accounts(account_fptr,std);          //we get student accounts to struct arrays
        flag=userLogin(std,fl);//userLogin fnc returns 1 or 0. 1 means user entered correct id and password.
        if(flag==1)//If user enters true id and password
        {
            system("cls");
            do
        {                                                                               //student menu
            printf("**********************************\n");
            printf("\tWhat do you want to do\n");
            printf("\t 1)Bring me a Test\n");
            printf("\t 2)Show my Score\n");
            printf("\t 3) Logout\n");
            printf("**********************************\n");
            scanf("%d",&studentlogin);//User enters a choice
            switch (studentlogin)
                {
                case 1://If user enters 1 he/she make a test
                    gettingQuestions(true_answers,questions, questionList);//We get questions to struct arrays
                    randomquestion(questions,questionList,std);               //call randomquesiton fnc
                    break;
                case 2://If user enters 2 he/she sees his/her score
                    gettingQuestions(true_answers,questions, questionList);//We get questions to struct arrays
                    show_score(std);            //call show score fnc
                    break;
                case 3://If user enters 3 he/she logs out
                    system("cls");
                    printf("BYE BYE\n");
                    break;
                default://If user enters an invalid choice he/she enters again
                    printf("Enter a Valid Choice\n");
                    break;
                }
            }while(studentlogin != 3);//Loop continues if student doesn't choose 3(log out)
        }

            else//I userlogin fnc returns 0
            {
                printf("Try again\n\n");
            }
            break;
        case 3://If user enters 3 he/she chooses to register
            printf("**********************************\n");
            printf("Register:\n");
            userRegister(fl,std,user);//Call register fnc
            printf("**********************************\n");
            break;

        case 4://If user chooses 4 he/she exits the program
            printf("***BYE BYE***");
            break;

        default://If user enters an invalid choice he/she enters it again
            printf("Please enter valid choice\n");
            break;
}
    }
    return 0;
}

void extraGettingQuestions(FILE *true_answers,FILE *questions, struct Questions questionList[])//The difference this function from gettingquestions function is this one finds size
{
    //Variable declaration
    int i=0;

    questions = fopen("Questions.txt","r");//open file in read mode

    while(!feof(questions))
    {
        fgets(questionList[i].question,250,questions);//get a line and make it "i." question element of struct array
        fgets(questionList[i].option,250,questions);//get a line and make it "i." option element of struct array
        i++;//Increment i
    }
    SIZE=i;//After the action occured up there "i" is now the number of questions and we make SIZE equal to it
    fclose(questions);//close file

    true_answers=fopen("trueanswers.txt","r");//open file

    if(true_answers==NULL)
    {
        printf("File can not be opened");
    }
    else
    {
        i=0;
        while(!feof(true_answers))
        {
            questionList[i].trueanswers=fgetc(true_answers);//get a letter from file(answers in file are like"bcdabdca") and make it "i." trueanswer element of struct array
            i++;//Increment i
        }

    }
    fclose(true_answers);//close file
    SIZE = SIZE-2;
}

void gettingQuestions(FILE *true_answers,FILE *questions, struct Questions questionList[])
{
    int i=0;

    questions = fopen("Questions.txt","r");//open file

    while(!feof(questions))
    {


        fgets(questionList[i].question,250,questions);//get a line and make it "i." question element of struct array
        fgets(questionList[i].option,250,questions);//get a line and make it "i." option element of struct array
        i++;
    }
    fclose(questions);

    true_answers=fopen("trueanswers.txt","r");//open file

    if(true_answers==NULL)
    {
        printf("File can not be opened");
    }
    else
    {
        i=0;
        while(!feof(true_answers))
        {
            questionList[i].trueanswers=fgetc(true_answers);//get a letter from file(answers in file are like"bcdabdca") and make it "i." trueanswer element of struct array
            i++;//Increment i
        }
        fclose(true_answers);//close file
    }

}

void displayQuestions(struct Questions questionList[])
{
    //variable declaration
    int i;
    for(i = 0 ; i <= SIZE ; i++)//Loop continue while i is less than SIZE
    {
        printf("%d %s\n%s\n",i+1,questionList[i].question,questionList[i].option);//print "i." question and option elements of questionlist struct array's
    }
}

void addQuestion(FILE *true_answers,FILE *questions,struct Questions questionList[])
{
    //Declaring arrays
    char getQuestion[100];
    char option1[100];
    char option2[100];
    char option3[100];
    char option4[100];
    char trueanswer;
    questions = fopen("Questions.txt","a+");//open file at append mode

    if(questions == NULL)
    {
        printf("File can not be opened");
    }
    else
    {

        getchar();
        printf("Now add question.\n");//Inform user

        printf("Enter question\n");
        gets(getQuestion);//get question

        printf("Enter options\n");
        printf("A)");
        gets(option1);
        printf("B)");
        gets(option2);
        printf("C)");                     //get answers
        gets(option3);
        printf("D)");
        gets(option4);

        fprintf(questions,"%s\na) %s b) %s c) %s d) %s\n",getQuestion,option1,option2,option3,option4);//print them to file

        SIZE++;//increase size because we add a question

        fclose(questions);//close file
    }

    true_answers=fopen("trueanswers.txt","a");//open file at append mode
    if(true_answers==NULL)
    {
        printf("File can not be opened");
    }
    else
    {
        printf("Enter correct answer\n");//inform user
        scanf("%c",&trueanswer);//get true answer from user

        fprintf(true_answers,"%c ",trueanswer);//print answer to file

        gettingQuestions(true_answers,questions, questionList);//call gettinQuestionss fnc to put questions,options,and trueanswers to struct arrays
    }

    fclose(true_answers);//close file

}

void deleteQuestion(FILE *true_answers,FILE *questions, struct Questions questionList[])
{
    //variable declaration
    int i,question_to_delete;

    gettingQuestions(true_answers,questions, questionList);//call gettingQuestions fnc
    displayQuestions(questionList);//Call display questions fnc to show them to user before he/she chooses one to delete


    printf("Which question do you want to delete?\n");//ask user which one he/she wants to delete
    scanf("%d",&question_to_delete);//user enters a question number

    while(1)
    {       //check if user enters a valid number,else make him/her enter again
        if(question_to_delete<1 || question_to_delete>SIZE+1)
        {
            printf("Enter a question number which exists!\n");
            scanf("%d",&question_to_delete);
        }
        else
        {
            break;
        }
    }


    for(i = question_to_delete ; i <= SIZE ; i++)//loop continues from users question number which he/she want to delete to SIZE
    {
        strcpy(questionList[i-1].question,questionList[i].question);//copy next question to previous one
        strcpy(questionList[i-1].option,questionList[i].option);//copy next options to previous one
        questionList[i-1].trueanswers=questionList[i].trueanswers;////copy next true answer to previous one
    }

    SIZE--;//decrement size
    questions=fopen("Questions.txt","w");//open file at write mode
    for(i = 0 ; i <= SIZE ; i++)
    {

        fprintf(questions,"%s%s",questionList[i].question,questionList[i].option);//print it to file
    }
    fclose(questions);//close file

    true_answers=fopen("trueanswers.txt","w");//open file at write mode

    if(true_answers==NULL)
    {
        printf("File can not be opened");
    }
    else
    {
        for(i=0;i<=SIZE;i++)
        {
            fprintf(true_answers,"%c",questionList[i].trueanswers);//write answers to file
        }

        gettingQuestions(true_answers,questions, questionList);//get them to struct arrays
        fclose(true_answers);//close file
    }
}


void histogram(FILE *fl,struct Student std[])
// this function aim is print on screen the class histogram table
{
    // variable declaration
    int classSize=0,aa=0,bb=0,cc=0,dd=0,ff=0,i;

    fl=fopen("studentscores.txt","r");  // open student score text file

    if(fl==NULL)// control the text file
    {
        printf("File can not be opened");
    }

    while(!feof(fl)){

        // this while when end of the file read the student number,name and grade and write on std struct
        fscanf(fl,"%d %s %d",&std[classSize].number,std[classSize].name,&std[classSize].grade);
        classSize++; // this variable determine the class size
    }


    for(i=0;i<classSize;i++){                    // this for control the all student grade and determine
        if(std[i].grade<60&&std[i].grade>=0)    // the grade class for example AA,BB,CC...
            ff++;

        if(std[i].grade<70&&std[i].grade>=60)
            dd++;

        if(std[i].grade<80&&std[i].grade>=70)
            cc++;

        if(std[i].grade<90&&std[i].grade>=80)
            bb++;

        if(std[i].grade<=100&&std[i].grade>=90)
            aa++;
    }


    printf("Grade\tstd\tbar chart\n"); // histogram title
    printf("A\t%d\t",aa);
    for(i=0;i<aa;i++)           // this part print the
        printf("*");           // grades class on screen
    printf("\n");

    printf("B\t%d\t",bb);
    for(i=0;i<bb;i++)
        printf("*");
    printf("\n");

    printf("C\t%d\t",cc);
    for(i=0;i<cc;i++)
        printf("*");
    printf("\n");

    printf("D\t%d\t",dd);
    for(i=0;i<dd;i++)
        printf("*");
    printf("\n");

    printf("F\t%d\t",ff);
    for(i=0;i<ff;i++)
        printf("*");
    printf("\n");
}

void seetopfive(FILE *fl,struct Student std[])
// this function print on screen the more 5 grades on class
{

     // variable declaration
    int i=0,classSize=0,top1=0,top2=0,top3=0,top4=0,top5=0,topCounter=0;

    fl=fopen("studentscores.txt","r");  // open student score text file

    if(fl==NULL)    // control the text file
    {
        printf("File can not be opened");
    }

    while(!feof(fl)){
             // this while when end of the file read the student number,name and grade and write on std struct
        fscanf(fl,"%d %s %d",&std[classSize].number,std[classSize].name,&std[classSize].grade);
        classSize++; // this variable determine the class size
    }


    // this loop determine the first greatest number
    for(i=0;i<classSize;i++){
        if(std[i].grade>topCounter){// if grade greater than top counter, this mean this grade more than another grade
            top1=i; // if grade greater than top counter, top1 variable hold a this array number
            topCounter=std[i].grade;}// last line the this if function. This line hold a high grade because
        }                               // each control the grade this function, must  find the highest than all grade


    topCounter=0; // when finished each loop top counter equal zero because again use another loop
     // this loop determine the second greatest number
    for(i=0;i<classSize;i++){
        if(i!=top1){ // this if prevent the same score for sort
            if(topCounter<std[i].grade){// if grade greater than top counter, this mean this grade more than another grade
                top2=i; // if grade greater than top counter, top1 variable hold a this array number
                topCounter=std[i].grade;}} // last line the this if function. This line hold a high grade because
        else                              // each control the grade this function, must  find the highest than all grade
            continue;}


    topCounter=0; // when finished each loop top counter equal zero because again use another loop
     // this loop determine the third greatest number
    for(i=0;i<classSize;i++){
        if(i!=top1 && i!=top2){// this if prevent the same score for sort
            if(topCounter<std[i].grade){ // if grade greater than top counter, this mean this grade more than another grade
                top3=i;  // if grade greater than top counter, top1 variable hold a this array number
                topCounter=std[i].grade;}} // last line the this if function. This line hold a high grade because
        else                              // each control the grade this function, must  find the highest than all grade
            continue;}


    topCounter=0;// when finished each loop top counter equal zero because again use another loop
     // this loop determine the fourth greatest number
    for(i=0;i<classSize;i++){
        if(i!=top1&&i!=top2&&i!=top3){// this if prevent the same score for sort
            if(topCounter<std[i].grade){  // if grade greater than top counter, this mean this grade more than another grade
                top4=i; // if grade greater than top counter, top1 variable hold a this array number
                topCounter=std[i].grade;}}// last line the this if function. This line hold a high grade because
        else                              // each control the grade this function, must  find the highest than all grade
            continue;}


    topCounter=0;
     // this loop determine the fifth greatest number
    for(i=0;i<classSize;i++){
        if(i!=top1&&i!=top2&&i!=top3&&i!=top4){// this if prevent the same score for sort
            if(topCounter<std[i].grade){ // if grade greater than top counter, this mean this grade more than another grade
                top5=i;  // if grade greater than top counter, top1 variable hold a this array number
                topCounter=std[i].grade;}}// last line the this if function. This line hold a high grade because
        else                              // each control the grade this function, must  find the highest than all grade
            continue;}

    // this part print screen top5 grade
    printf("%d %s %d\n",std[top1].number,std[top1].name,std[top1].grade);
    printf("%d %s %d\n",std[top2].number,std[top2].name,std[top2].grade);
    printf("%d %s %d\n",std[top3].number,std[top3].name,std[top3].grade);
    printf("%d %s %d\n",std[top4].number,std[top4].name,std[top4].grade);
    printf("%d %s %d\n",std[top5].number,std[top5].name,std[top5].grade);

        fclose(fl); // close file
}

void updateQuestion(FILE *true_answers,FILE *questions, struct Questions questionList[])
{
    deleteQuestion(true_answers,questions, questionList);//call delete function to delete one question
    addQuestion(true_answers,questions, questionList);//call add function to add one question



}

int adminfunction(struct Account admin_account[])
{
    //variable declaration
    char admin_id[50];
    int admin_password;
    int counter=1;
    int i;
    int check=0;
    int id_check;
    int password_check;
    int password_counter,id_counter;

    while(check==0&&counter!=3)//loop continues while user doesn't enter true id and password or he/she enters it wrong for 3 times
    {
        getchar();
        printf("Please Enter ID: ");//get id
        gets(admin_id);
        printf("Please Enter Password: ");//get password
        scanf("%d",&admin_password);


        do{

            for(i=0;i<admin_account_size;i++)
            {
                if(admin_account[i].password==admin_password)//check if passwor is correct if it is make password checker 1 and password counter i
                {
                    password_check=1;
                    password_counter=i;//if user enters his/her own id but he/she enters another one's pasword who is before him/her at struct array he/she used to login anywy.But with this user can't
                }
                if(strcmp(admin_account[i].name,admin_id)==0)//check if id is correct
                {
                    id_check=1;
                    id_counter=i;
                }
            }
            if(id_check!=1 || password_check!=1 || password_counter!=id_counter)//if id check or password check are wrong or password counter and id counter aren't equal make user enter id dand password again
            {
                printf("ID or Password is wrong\nEnter ID again:\n");
                scanf(" %s",admin_id);//user enters id again
                printf("Enter password again:\n");
                scanf("%d",&admin_password);//user enters password again
                counter++;
            }
            if(id_check==1  && password_check==1 && password_counter==id_counter)//if they are correct make check 1
            {
                check=1;
            }
            if(check==1)//if check is 1 return 1 so user can login
            {
                printf("\n\nSUCCESFULLY LOGIN\n\n");
                return 1;
                break;
            }

            if(counter==3)//if counter is 3 user is out of his trying limit
            {
                printf("You entered wrong ID or Password 3 times\nBye Bye");
                return 0;
                break;
            }


        }while(check==0 || counter!=3);
    }
}
void userRegister(FILE *fl,struct Student std[],FILE *user)
//this function create a new acount for students
{
    //variable declaration for this function
    int i,flag=0,classSize=0,user_password,school_num;
    char user_id[30];

    fl=fopen("studentscores.txt","r"); // fisrt open the file read mod

    if(fl==NULL) // check a file
    {
        printf("File can not be opened");
    }

    while(!feof(fl)){
        // this while when end of the file read the student number,name and grade and write on std struct
        fscanf(fl,"%d %s %d",&std[classSize].number,std[classSize].name,&std[classSize].grade);
        classSize++;  // this variable determine the class size
    }
    fclose(fl); // and close file

         // user enter a name student number and password
        printf("Please enter Your Name:\n");
        scanf("%s",user_id);
        printf("Please enter a User Password:\n");
        scanf("%d",&user_password);
        printf("Please enter your school number");
        scanf("%d",&school_num);


            for(i=0;i<classSize;i++){                 // this part check a student number and
                                                     // and if that number  exist
            if (school_num==std[i].number)          // register operation cannot be performed
                flag=1;//flag is control parameter // but this number if that number does not exist
                break;                            // function make a register operation

            }

            if (flag==1){
                // if number is exist the user is informed
                printf("This Student number already taken\n");
                exit(flag==1);
            }


        if (flag==0)
            {     // if number does not exist this part activates
                student_account_size++;//class size addition one student
                fl=fopen("studentscores.txt","a");// student scores file open a append mod

                if(fl==NULL) // check file
                printf("File can not be opened");

                fprintf(fl,"\n%d %s 0",school_num,user_id);  // print the file a student information
                                                            // but this part only write a student name student number and grade
                fclose(fl); // close student scores file   // first grade is always 0

                user = fopen ("UserRegister.txt","a"); //open again file because student information hold 2 different file
                                                      // and user register file open a append mod
                if(userRegister==NULL)//check a userRegister file
                printf("File can not be opened");

                else
                {   //print the userRester file the student name and password
                    fprintf(user,"\n%s %d",user_id,user_password);
                    printf("\t***REGISTER SUCCESFULL***\n");// and user learn a register is SUCCESUll
                    fclose(user); // close a userRegister file
                }
            }
        }

int userLogin(struct Student stu_account[],FILE *fl)
{
    //variable declaration
    char user_id[50];
    int user_password;
    int counter=1;
    int i;
    int check=0;
    int id_check;
    int password_check;
    int id_counter,password_counter;
    int class_size=0;

    fl=fopen("UserRegister.txt","r");//open file at read mode

    if(fl==NULL)
    {
        printf("File can not be opened");
    }
    else
    {
        while(!feof(fl))
        {
            fscanf(fl,"%s",stu_account[i].name);//get name and passwords from file and put them to sturct array
            fscanf(fl,"%d",&stu_account[i].password);
            class_size++;//increase class size so we can find how many students there are
        }
        fclose(fl);//close file



    while(check==0&&counter!=3)
    {
        getchar();
        printf("**********************************\n");
        printf("\tPlease Enter ID: ");
        gets(user_id);//user enters user id
        printf("Please Enter Password: ");
        scanf("%d",&user_password);//user enters password
        do{

            for(i=0;i<class_size;i++)
            {
                if(stu_account[i].password==user_password)//check if password is correct if it is make password checker 1 and password counter i
                {
                    password_check=1;
                    password_counter=i;
                }
                if(strcmp(stu_account[i].name,user_id)==0)//check if id is correct if it is make id checker 1 and id counter i
                {
                    id_check=1;
                    id_counter=i;
                }
            }
            if(id_check!=1 || password_check!=1 || id_counter!=password_counter)//if id check or password check are wrong or password counter and id counter aren't equal make user enter id dand password again
            {
                printf("**********************************\n");
                printf("ID or Password is wrong\nEnter ID again:\n");
                scanf(" %s",user_id);
                printf("Enter password again:\n");
                scanf("%d",&user_password);
                printf("**********************************\n");
                counter++;
            }
            if(id_check==1  && password_check==1 && id_counter==password_counter)//if they are correct make check 1
            {
                check=1;
                user_element=id_counter;//make user_element equal to id counter.id conter is equal to users element number in struct array so we make user_element equal to that user's element number in struct array to use in other functions
            }
            if(check==1)//if check is 1 return 1 so user can login
            {
                printf("**********************************\n");
                printf("\n\nSUCCESFULLY LOGIN\n\n");
                printf("**********************************\n");

                return 1;
                break;
            }

            if(counter==3)//if counter is 3 user is out of his trying limit
            {
                printf("You entered wrong ID or Password 3 times\nBye Bye");
                return 0;
                break;
            }
            password_check=0;
            id_check=0;

        }while(check==0 || counter!=3);

    }
}
}

void getting_admin_Accounts(FILE *admin,struct Account admin_account[])
{
    admin=fopen("admin.txt","r");//open file at read mode
    int i=0;

    if(admin==NULL)
    {
        printf("File can not be opened.");
    }
    else
    {
        while(!feof(admin))
        {           //get teacher's names and password's from file and put them to struct arrays
            fscanf(admin,"%s",admin_account[i].name);
            fscanf(admin,"%d",&admin_account[i].password);
            i++;//increase i
        }
        fclose(admin);//close file
    }
}

void getting_stu_Accounts(FILE *stu,struct Student stu_account[])
{
    FILE *fp;//declare file pointer
    stu=fopen("UserRegister.txt","r");//open file
    int i=0,j;//variable declaration
    if(stu==NULL)
    {
        printf("File can not be opened");
    }
    else
    {
        while(!feof(stu))
        {           //get student's names and password's from file and put them to struct arrays
            fscanf(stu,"%s",stu_account[i].name);
            fscanf(stu,"%d",&stu_account[i].password);
            i++;//increase i
        }
        fclose(stu);//close file
    }
    student_account_size=i;//i i now equal to student number,so we make it equal to student_account_size
    i=0;//make i equal to 0 beacuse we will use it again

    fp=fopen("studentscores.txt","r");//open file ar read mode
        if(fp==NULL)
        {
            printf("File can not be opened");
        }
        else
        {
            while(!feof(fp))
            {                                               //get student's number name and grade
                fscanf(fp,"%d",&stu_account[i].number);
                fscanf(fp,"%s",stu_account[i].name);
                fscanf(fp,"%d",&stu_account[i].grade);
                printf("%d %s  %d\n",stu_account[i].number,stu_account[i].name,stu_account[i].grade);//we added this to check if we could get them from file
                i++;
            }

        }
                    //we added this to check if we could get it from file
    for (j=0;j<i;j++)
            printf("%s %d\n",stu_account[j].name,stu_account[j].password);
        system("cls");

fclose(fp);
}
int randomquestion(FILE *questions,struct Questions questionsList[],struct Student stu_account[])
{
    FILE *fp;
        srand(time(NULL));//generate random number
        char stuanswer[5];//user enter 5 answer
        int i,a,counter=0;//counter
        i=rand()%6;// create number from 0 to 6
printf("If you press 'e' you will pass that question.After you finish all questions they will be asked to you again.\nThis will happen for all questions just for once.\n\n");
printf("%s%s",questionsList[i].question,questionsList[i].option);//t
scanf(" %c",&stuanswer[0]);//user enter first question's answer
printf("%s%s",questionsList[i+6].question,questionsList[i+6].option);// create number from 6 to 12 and call the question from the struct
scanf(" %c",&stuanswer[1]);//user enter second question's answer
printf("%s%s",questionsList[i+12].question,questionsList[i+12].option);// create number from 12 to 18 and call the question from the struct
scanf(" %c",&stuanswer[2]);//user enter third question's answer
printf("%s%s",questionsList[i+18].question,questionsList[i+18].option);// create number from 18 to 24 and call the question from the struct
scanf(" %c",&stuanswer[3]);//user enter forth question's answer
a=rand()%SIZE;//if user added question or deleted  so, changed the questions size.Therefore,program generate the random from size.
printf(" %s%s",questionsList[a].question,questionsList[a].option);
scanf(" %c",&stuanswer[4]);//user enter fifth question's answer


if(stuanswer[0]=='e')//the question that is left blank when the exam is over calls.
        {
            printf("You have passed 1. questions\n");
            printf("%s%s",questionsList[i].question,questionsList[i].option);//call the questions struct from random
            scanf(" %c",&stuanswer[0]);//user enter answer
        }
if(stuanswer[1]=='e')//the question that is left blank when the exam is over calls
            {
                printf("You have passed 2. questions\n");
                printf("%s%s",questionsList[i+6].question,questionsList[i+6].option);//call the questions struct from random
                scanf(" %c",&stuanswer[1]);//user enter answer
            }
if(stuanswer[2]=='e')//the question that is left blank when the exam is over calls.
            {
                printf("You have passed 3. questions\n");
                printf("%s%s",questionsList[i+12].question,questionsList[i+12].option);//call the questions struct from random
                scanf(" %c",&stuanswer[2]);//user enter answer
            }
if(stuanswer[3]=='e')//the question that is left blank when the exam is over calls.
        {
             printf("You have passed 4. questions\n");
            printf("%s%s",questionsList[i+18].question,questionsList[i+18].option);
            scanf(" %c",&stuanswer[3]);
        }
if(stuanswer[4]=='e')//the question that is left blank when the exam is over calls.
        {
            printf("You have passed 5. questions\n");
            printf(" %s%s",questionsList[a].question,questionsList[a].option);
            scanf(" %c",&stuanswer[4]);
        }
        if(questionsList[i].trueanswers==stuanswer[0])//the user entered the answer,if the answer is the same in questionList
        {
            printf("Your 1. question is true\n");
            counter++;//correct size increasing
        }

        else
        {
            printf("Your 1. question is false..Correct answer- %c\n",questionsList[i].trueanswers);//if false answer,show the true answers
        }

        if(questionsList[i+6].trueanswers==stuanswer[1])//the user entered the answer,if the answer is the same in questionList
        {
            printf("Your 2. question is true\n");
            counter++;//correct size increasing
        }
        else
        {
            printf("Your 2. question is false..Correct answer- %c\n",questionsList[i+6].trueanswers);//if false answer,show the true answers

        }
        if(questionsList[i+12].trueanswers==stuanswer[2])//the user entered the answer,if the answer is the same in questionList
        {
            printf("Your 3. question is true\n");
            counter++;//correct size increasing
        }
        else
        {
            printf("Your 3. question is false..Correct answer- %c\n",questionsList[i+12].trueanswers);//if false answer,show the true answers
        }

        if(questionsList[i+18].trueanswers==stuanswer[3])//the user entered the answer,if the answer is the same in questionList
        {
            printf("Your 4. question is true\n");
            counter++;//correct size increasing
        }
        else
        {
            printf("Your 4. question is false..Correct answer- %c\n",questionsList[i+18].trueanswers);//if false answer,show the true answers
        }

        if(questionsList[i+24].trueanswers==stuanswer[4])//the user entered the answer,if the answer is the same in questionList
        {
             printf("Your 5. question is true\n");
             counter++;//correct size increasing
        }
        else
            printf("Your 5. question is false..Correct answer- %c\n",questionsList[i+24].trueanswers);//if false answer,show the true answers

        printf("Your score is %d\n",counter*20);//counterup to 20 multiplication the correct size.

        stu_account[user_element].grade=counter*20;//in which the user is logged in, if it is written in his notes.
        fp=fopen("studentscores.txt","w");

        if(fp==NULL)
        {
            printf("File can not be opened");
        }

        else
        {
            for(i=0;i<student_account_size;i++)
            {
                fprintf(fp,"%d %s %d\n",stu_account[i].number,stu_account[i].name,stu_account[i].grade);
            }
            fclose(fp);
        }
}

void show_score(struct Student stu_account[])
{
    printf("Name\tNumber\tGrade\n");
    printf("%s\t%d\t%d\n",stu_account[user_element].name,stu_account[user_element].number,stu_account[user_element].grade);//print current user's name number and grade
}
