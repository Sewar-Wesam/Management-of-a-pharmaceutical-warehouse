#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

Student name: Sewar AbuEid
Student ID: 1200043

*/

/* Define the structure for each node which indicates
the medicines with their relevant information
*/
struct MED
{

    char name[15];// to store the name of the medicine
    char active_ingredient[5];// amount of active ingredient
    char category[20];
    char indication[20];
    char disease[100]; // store all disease in one large array of character then I will split them
    char expire_date[10];
    char count[5]; // quantity of this medicine
    char company[30];
    struct MED* Left;
    struct MED* Right;
};
struct MED* medicine;


// the structure of each element in the hash table is

struct HashNode
{

    char name[15];
    char active_ingredient[5];
    char category[20];
    char indication[20];
    char disease[100]; // store all disease in one large array of character then I will split them
    char expire_date[10];
    char count[5];
    char company[30];
    int available;// this element is to declare whether this node in the hash table is empty or not

};

// declare array of structure hash nodes and call it hashTable
struct HashNode* HashTable[11]; // 11 is the size of the origin hash table

// important information for the Hashing phase

int size_of_original_hash_Table=11;// global integer to indicate the size of the hash table
int counter=0; // to count the full spot in the hash table to determine when to rehash

// Declaration methods that treat with BST trees
struct MED* MakeEmpty();
struct MED* Insert(char name1[],char active_ingredient1[],char category1[],char indication1[],
                   char disease1[],char exp_Date1[],char count1[],char company[],struct MED* medicine1);
struct MED* Find( char name[], struct MED* T );
struct MED* FindMin(struct MED* T);
struct MED* Delete(char name1[15],struct MED* medicine);

////////////////////////////////////////////////

// Declaration of My Own Functions
void ReadFile();
void printMedicines(struct MED* T);
void InsertFromUser();
void UpdateInfo();
void Update_Quantity();
void Same_Category(char category[], struct MED* T);
void delete_same_company(char company1[], struct MED* T);
void SaveToFile(FILE* fptr,struct MED* medicine);
void same_disease(char diseaseToSearch[20],struct MED* T);
//hash phase function declaration
void HashMenu();
int IsPrime(int x);
int New_Size(int Previous_Size);
int indixing(char name[],int size);
int indixing2(char name[],struct HashNode* hash2[]);
void Initialize_Hashing();
void ReadFileForHashing();
void Insert_File_To_Hash(char name[], char active_Ingredeint[], char category[],
                         char indication[], char disease[], char expiry_date[], char count[],char company[]);
void Rehashing();
void Hash_Print(int size);
void Used_Function();
void Insert_record();
void Search_In_Hashing();
void Delete_cell_Hash();

/////////////////////////////////////

struct MED* MakeEmpty(struct MED* T)
{
    if(T!=NULL)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
};

struct MED* Insert(char name1[],char active_ingredient1[],char category1[],char indication1[],
                   char disease1[],char exp_Date1[],char count1[],char company[],struct MED* medicine)
{
    if(medicine==NULL)
    {
        // create and return a 1-node tree
        medicine=(struct MED*)malloc(sizeof(struct MED));
        if(medicine==NULL)
            printf("Out Of space!\n");
        else
        {
            strcpy(medicine->name,name1);
            strcpy(medicine->active_ingredient,active_ingredient1);
            strcpy(medicine->category,category1);
            strcpy(medicine->indication,indication1);
            strcpy(medicine->disease,disease1);
            strcpy(medicine->expire_date,exp_Date1);
            strcpy(medicine->count,count1);
            strcpy(medicine->company,company);
            medicine->Left=medicine->Right=NULL;
        }
    }

    else if(strcmp(name1,medicine->name)<0)
        medicine->Left=Insert(name1,active_ingredient1,category1,indication1,disease1,exp_Date1
                              ,count1,company,medicine->Left);


    else if(strcmp(name1,medicine->name)>0)
        medicine->Right=Insert(name1,active_ingredient1,category1,indication1,disease1,exp_Date1
                               ,count1,company,medicine->Right);


    return medicine;

}

struct MED* Find( char name[], struct MED* T )
{

    if( T == NULL )
        return NULL;//If the tree is empty or the medicine is not in the tree
    if( strcmp(name,T->name)<0 )
        return Find(name, T->Left );
    else if( strcmp(name,T->name)>0 )
        return Find( name, T->Right );
    else
        return T;
}

struct MED* FindMin(struct MED* T)
{

    if(T!=NULL)
        while(T->Left!=NULL)
            T=T->Left;

    return T;
};

// Delete function
struct MED* Delete(char name1[15],struct MED* medicine)
{

    struct MED* temp;
    if(medicine==NULL)
    {

        printf("Sorry! but this medicine has not been founded!\n you can check the name and try again\n");
    }
    else if(strcmp(name1,medicine->name)<0)
    {
        // Go to search in the left subtree,because the alphabetical is smaller
        medicine->Left=Delete(name1,medicine->Left);
    }
    else if(strcmp(name1,medicine->name)>0)
    {
        // Go to search in the right subtree because the alphabetical is larger
        medicine->Right=Delete(name1,medicine->Right);
    }
    else if(medicine->Right && medicine->Left)
    {

        // this node in the tree has two children
        // Now,we must replace this node with smallest node in the right subtree
        temp=FindMin(medicine->Right);
        // copy all information in temp node to the node that will be deleted
        strcpy(medicine->name,temp->name);
        strcpy(medicine->active_ingredient,temp->active_ingredient);
        strcpy(medicine->category,temp->category);
        strcpy(medicine->indication,temp->indication);
        strcpy(medicine->disease,temp->disease);
        strcpy(medicine->expire_date,temp->expire_date);
        strcpy(medicine->count,temp->count);
        strcpy(medicine->company,temp->company);
        medicine->Right=Delete(medicine->name,medicine->Right);
    }
    else
    {
        // this node has one or zero child
        temp=medicine;
        if(medicine->Left==NULL)
            // also this node handled zero child
            medicine=medicine->Right;
        else if(medicine->Right==NULL)
            medicine=medicine->Left;
        free(temp);
    }
    return medicine;


};

int main()
{
    int x;
    printf("\n\nWelcome in our System!\n\n ");
    printf("Please Enter your choice:\n");
    printf("1-Read Medicine File to start your managment!\n");
    printf("2-Insert a new medicine\n");
    printf("3-Update Information for a medicine\n");
    printf("4-Update the quantity of a given medicine\n");
    printf("5-List The medicines\n");// In alphabetical order
    printf("6-List all medicines of same category\n");
    printf("7-List all medicines that treat a specific disease\n");
    printf("8-Delete a medicine\n");
    printf("9-Delete all medicines from a specific company\n");
    printf("10-Save Information into a file\n");
    printf("11-Go to Hashing phase\n");
    printf("12-Exit\n");
    scanf("%d",&x);
    while(x!=12)
    {
        if(x==1)
        {
            medicine=MakeEmpty(NULL);
            ReadFile();

        }
        else if(x==2)
        {
            InsertFromUser();
        }
        else if(x==3)
        {
            UpdateInfo();
        }
        else if(x==4)
        {
            Update_Quantity();
        }
        else if(x==5)
        {
            printMedicines(medicine);
        }
        else if(x==6)
        {
            char category1[20];
            printf("what is the category that you are search for?\n");
            scanf("%s",&category1);
            printf("The List of Medicines for %s category is\n",category1);
            printf("-------------------------------------------\n");
            Same_Category(category1,medicine);
        }
        else if(x==7)
        {
            char diseseToSearch[20];
            char temp;
            printf("What is the disease that you search about it?\n ");
            scanf("%c",&temp); // temp statement to clear buffer
            scanf("%[^\n]",diseseToSearch);
            // scanf("%s",&diseseToSearch);
            printf("We are searching for a medicine for %s........\n",diseseToSearch);
            same_disease(diseseToSearch,medicine);
        }
        else if(x==8)
        {
            char name_to_delete[15];
            printf("Enter the name of medicine that you want to delete it:\n");
            scanf("%s",&name_to_delete);
            Delete(name_to_delete,medicine);
            printf("The medicine : %s is deleted you can check by print all medicines\n",name_to_delete);
            printf("If you want to print the list print 5\n");
            // Delete Medicine
        }
        else if(x==9)
        {
            char comp[30];
            char temp;
            printf("which company that you want to delete its medicines?\n");
            scanf("%c",&temp); // temp statement to clear buffer
            scanf("%[^\n]",comp);
            printf("We will delete %s medicines...........\n ",comp);
            delete_same_company(comp,medicine);
            printf("The medicines of %s company have been deleted \n",comp);
            printf("you can make check by press number 5\n");
        }
        else if(x==10)
        {
            FILE* fptr;
            fptr=fopen("Pharmacy.txt","w");
            SaveToFile(fptr,medicine);
            fclose(fptr);
        }
        else if(x==11)
        {
            HashMenu();
        }
        printf("Please Enter your choice:\n");
        printf("1-Read Medicine File to start your managment!\n");
        printf("2-Insert a new medicine\n");
        printf("3-Update Information for a medicine\n");
        printf("4-Update the quantity of a given medicine\n");
        printf("5-List The medicines\n");// In alphabetical order
        printf("6-List all medicines of same category\n");
        printf("7-List all medicines that treat a specific disease\n");
        printf("8-Delete a medicine\n");
        printf("9-Delete all medicines from a specific company\n");
        printf("10-Save Information into a file\n");
        printf("11-Go to Hashing phase\n");
        printf("12-Exit\n");
        scanf("%d",&x);
    }

    return 0;
}

void ReadFile()
{
    FILE* fptr;
    fptr=fopen("Meds.txt", "r");// open the File in read mode

    char line[500];// array of characters to store the complete line
    char info[8][30];// to store the information about each medicine in each itteration

    while (fgets(line, sizeof(line), fptr))
    {

        char * token = strtok(line, ":");// we will split the information according to this char

        for(int i=0; i<8; i++)
        {
            strcpy(info[i],token);
            token = strtok(NULL, ":");
        }
        // insert the medicine into the tree
        medicine= Insert(info[0], info[1], info[2], info[3], info[4], info[5], info[6],info[7],medicine);
    }
    // close the file
    fclose(fptr);
}


void printMedicines(struct MED* T)
{

    if( T != NULL)
    {
        printMedicines( T->Left );// use recursion to print all nodes(medicines) in the tree

        printf("Name: %s\t", T->name);
        printf("Active ingredient: %s\t", T->active_ingredient);
        printf("Category: %s\t", T->category);
        printf("indication: %s :%s\n", T->indication,T->disease);
        printf("Expiry Date: %s\t", T->expire_date);
        printf("quantity: %s\t",T->count);
        printf("Company: %s\n", T->company);
        printf("------------------------------------------>>>>>>>>>>>>\n");

        printMedicines( T->Right ); // use recursion to print all nodes(medicines) in the tree
    }
}

void InsertFromUser()
{

    char name1[15];
    char category1[20];
    char indication1[20];
    char disease1[100];
    char exp_Date1[10];
    char active_ingredeint1[5];
    char count[5];
    char company[30];
    char temp;// to take string with spaces
    char temp2;// also to take string with space

// ask the user to enter the information about the medicine that he/she wants to add

    printf("Dear User! Insert information as will be shown to add a new medicine:\n");
    printf("---->> \n");
    printf("What is the name of the medicine?\n");
    scanf("%s",&name1);
    printf("What is the amount of active ingredient?\n");
    scanf("%s",&active_ingredeint1);
    printf("What is the category of the medicine?\n");
    scanf("%s",&category1);
    printf("What is the indication of the medicine?\n");
    scanf("%c",&temp); // temp statement to clear buffer
	scanf("%[^\n]",indication1);
    printf("disease for this medicine?\n");
    scanf("%s",&disease1);
    printf("expiry date:\n");
    scanf("%s",&exp_Date1);
    printf("quantity of the medicine?\n");
    scanf("%s",&count);
    printf("Company of this medicine?\n");
    scanf("%c",&temp2); // temp statement to clear buffer
	scanf("%[^\n]",company);

    medicine=Insert(name1,active_ingredeint1,category1,indication1,disease1,exp_Date1,count,company,
                    medicine);

}

void UpdateInfo()
{

    struct MED* temp;
    char name1[15];
    char name2[15]; //to store the updated name
    char category1[20];
    char indication1[20];
    char disease1[]="";
    char expire_date1[10];
    char company1[30];
    char count1[5];
    char active_ingredient1[5];
    int choice;
    printf("Enter the name of the medicine that you want to update its Information\n");
    scanf("%s",&name1);
    temp=Find(name1,medicine);
    if(temp==NULL)
    {
        printf("Sorry!\n This medicine is not here!\n");
    }
    else
    {
        printf("%s is here , you can update this medicine\n",temp->name);
        printf("select the field that you want to modify it\n");
        printf("1-medicine name\n");
        printf("2-active ingredient\n");
        printf("3-medicine category\n");
        printf("4-medicine indication\n");
        printf("5-expiry date\n");
        printf("6-medicine quantity\n");
        printf("7-medicine company\n");
        printf("8-Update All information\n");
        scanf("%d",&choice);

        if(choice==1){
            printf("Enter the new name\n");
            scanf("%s",&name2);
            //strcpy(temp->name,name2);// I delete this line because it does not achieve alphabetical
            Insert(name2,temp->active_ingredient,temp->category,temp->indication,temp->disease,
                   temp->expire_date,temp->count,temp->company,medicine);
                   Delete(temp->name,medicine);
        }
       else if(choice==2){

            printf("Enter the new active ingredient \n");
            scanf("%s",&active_ingredient1);
            strcpy(temp->active_ingredient,active_ingredient1);

       }
       else if(choice==3){
            printf("Enter the new category\n");
            scanf("%s",&category1);
            strcpy(temp->category,category1);
       }

      else if(choice==4){
            printf("Enter the new indication\n");
            scanf("%s",&indication1);
            strcpy(temp->indication,indication1);
      }

      else if(choice==5){

            printf("Enter the new expire date\n");
            scanf("%s",&expire_date1);
            strcpy(temp->expire_date,expire_date1);
      }

       else if(choice==6){

            printf("Enter the new quantity \n");
            scanf("%s",&count1);
            strcpy(temp->count,count1);
       }

      else if(choice==7){
            printf("Enter the new company\n");
            scanf("%s",&company1);
            strcpy(temp->company,company1);
      }

      else if (choice==8){
            // This case if the user want to update all information about the medicine

            // The first step is to delete the origin node(origin medicine)
            Delete(temp->name,medicine);
            // then we will ask the user to insert the new information
            printf("name:\n");
            scanf("%s",&name2);
            printf("active ingredient\n");
            scanf("%s",&active_ingredient1);
            printf("category\n");
            scanf("%s",&category1);
            printf("indication\n");
            scanf("%s",&indication1);
            printf("expiry date\n");
            scanf("%s",&expire_date1);
            printf("new quantity:\n");
            scanf("%s",&count1);
            printf("new company:\n");
            scanf("%s",&company1);
            Insert(name2,active_ingredient1,category1,indication1,disease1,expire_date1,count1
                   ,company1,medicine);

      }
       else{
            printf("check your selection and try again\n");
       }

        printf("\nUpdating has finished!\n you can check this by List all medicines\npress 5 to check\n");
    }
    return 0;
}

void Update_Quantity()
{

    struct MED* temp;
    char new_quantity[5];
    char name1[15];

    printf("Enter the name of the medicine that you want to update its quantity\n");
    scanf("%s",&name1);
    temp=Find(name1,medicine);
    if(temp==NULL)
    {
        printf("Sorry! But this medicine is not here!\n");

        // give the user a suggestion to insert this medicine in the system==in the tree
        printf("Dear Client you can Insert this medicine by choose selection number 2 in the main menu\n\n");
    }
    else
    {
        printf("Enter the new Quantity\n");
        scanf("%s",&new_quantity);
        strcpy(temp->count,new_quantity);
        printf("Quantity has been Updated for %s to be %s\n",temp->name,temp->count);
        printf("you can check by print the list of the medicines\n");
    }

    return 0;
}

void Same_Category(char category[], struct MED* T)
{
    if(T!= NULL)
    {
        Same_Category(category,T->Left); // use recursion to implement this function

        if(strcmp(category,T->category)==0)
        {
            // print the medicine with its relevant information because it is of the same category
            printf("->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->->\n");
            printf("name: %s\t",T->name);
            printf("active ingredient: %s\t",T->active_ingredient);
            printf("category: %s\t",T->category);
            printf("indication: %s:%s\t",T->indication,T->disease);
            printf("expiry Date: %s\t",T->expire_date);
            printf("quantity: %s\t",T->count);
            printf("Company: %s\n",T->company);
        }

        Same_Category(category,T->Right); // use recursion to implement this function
    }
    return 0;
}

void delete_same_company(char company1[], struct MED* T)
{
    if(T!= NULL)
    {
        delete_same_company(company1,T->Left);// use recursion to implement this function

        char comp[30];
        strcpy(comp,strtok(T->company,"\n"));
        if(strcmp(company1,comp)==0)
        {
            Delete(T->name,medicine);
        }

        delete_same_company(company1,T->Right);  // use recursion to implement this function
    }
    return 0;
}

void SaveToFile(FILE* fptr,struct MED* medicine)
{
    if( medicine != NULL)
    {
        SaveToFile(fptr,medicine->Left ); // via recursion we can traverse through all node in the tree

        fprintf(fptr,"%s:", medicine->name);
        fprintf(fptr,"%s:", medicine->active_ingredient);
        fprintf(fptr,"%s:", medicine->category);
        fprintf(fptr,"%s:", medicine->indication);
        fprintf(fptr,"%s:",medicine->disease);
        fprintf(fptr,"%s:", medicine->expire_date);
        fprintf(fptr,"%s:", medicine->count);
        fprintf(fptr,"%s", medicine->company);

        SaveToFile(fptr, medicine->Right );// traverse through the tree via recursion
    }
}

void same_disease(char diseaseToSearch[20],struct MED* T)
{

    /*

    Now,here  I will split the illness of the medicine by the character: (,)
    then compare it with the target illness if it is the same then print this
    medicine with all its relevant information to the customer

    */

    if( T != NULL)
    {
        same_disease(diseaseToSearch, T->Left );
        // inside each node
        char temp[3][30];// array to store the medicine for each node

        char *token = strtok(T->disease, ",");

        for(int i=0; i<3; i++)
        {
            strcpy(temp[i],token);
            token = strtok(NULL, ",");
        }
        // compare the disease of each medicine with the target medicine
        if(strcmp(diseaseToSearch,temp[0])==0 || strcmp(diseaseToSearch,temp[1])==0 ||
                strcmp(diseaseToSearch,temp[2])==0)
        {

            printf("%s Quantity :%s\n",T->name,T->count);
            printf("Active ingredient : %s\n category: %s\n",T->active_ingredient,T->category);
            printf("expire Date: %s\n company: %s\n",T->expire_date,T->company);
            printf("-------------------------------------------------------------->>>\n");
        }

        ///////////////////////
        same_disease(diseaseToSearch, T->Right );
    }
}





///////////////////////////////////////////////////// End of Phase one

///// Start Functions for Hashing phase

void HashMenu()
{

    // This function is to display the menu of the hash phase and treat with each selection

    int selection;

    printf("Hash Phase..........\n\n\n");
    printf("Please Enter your selection number form the following menu\n");
    printf("1-Print Hash table\n");
    printf("2-print the size of hash table\n");
    printf("3-print the used function\n");
    printf("4-Insert a new record to the hash table\n");
    printf("5-search for a medicine in the hash table\n");
    printf("6-Delete a specific record\n");
    printf("7-Save the data back to the File\n");
    printf("8-Back to the main menu\n");

    scanf("%d",&selection);

    while(selection!=8)
    {
        if(selection==1)
        {


            // here we will initialize the hash table and print it
            Initialize_Hashing(); // to initialize the hash table and do the memory allocation
            ReadFileForHashing(); // read the file pharmacy.txt then store the information in the hash table
            Hash_Print(size_of_original_hash_Table); // Finally, we can print the information inside the hash table

        }
        else if(selection==2)
        {
            printf(" The size of the hash table is : %d\n",size_of_original_hash_Table);
        }
        else if(selection==3)
        {
            Used_Function();
        }
        else if(selection==4)
        {
            //Insert a new record from the user

            Insert_record();
        }
        else if(selection==5)
        {
            //search for a specific medicine
            Search_In_Hashing();
        }
        else if(selection==6)
        {
            // Delete a specific record
            Delete_cell_Hash();
        }
        else if(selection==7)
        {
            // Save the Information into a File
            Save_Hash_To_File();
        }

        printf("Please Enter your selection number form the following menu\n");
        printf("1-Print Hash table\n");
        printf("2-print the size of hash table\n");
        printf("3-print the used function\n");
        printf("4-Insert a new record to the hash table\n");
        printf("5-search for a medicine in the hash table\n");
        printf("6-Delete a specific record\n");
        printf("7-Save the data back to the File\n");
        printf("8-Back to the main menu\n");
        scanf("%d",&selection);

    }
}

// This function is to determine whether the number is prime or not

int IsPrime(int x)
{

    int count=0;
    for(int i=1; i<=x; i++)
    {
        if(x%i==0)
            count++;
    }
    if(count>2)
        return 0;
    else
        return 1;

}

int New_Size(int Previous_Size)
{
    int base= Previous_Size*2;
    //int newSize;
    while(IsPrime(base)==0)
    {

        base++;// increment the base to arrive the first prime number greater than twice old size
    }
    return base;
}

// this function is to find the suitable index for the inserted hashing node

int indixing(char name[],int size)
{
    int index,Function;
    int i=0;

    // method number two in Hashing strings slides of Dr. Radi Jarrar
    ////////////////////////////////////////
    Function=((int)name[0]+(int)name[1]*27+(int)name[2]*729)%size;
    ///////////////////////////////////////

    while(i<size)
    {
        index= ((Function + (i*i)) % size);// use the quadratic hashing Formula

        if(HashTable[index]->available==0)
        {
            break;
            // get out to return this value of index because it is empty
        }

        i++;// increment the value of i because this index is occupied
    }
    return index;// return value acts the empty and suitable index to insert the hash node
}
// This function is to find the index for the new hash table
int indixing2(char name[],struct HashNode* hash2[])
{
     /* this function is very similar to indixing1 but its treat with the new
            hash table when we do the rehashing
     */
    int index,Function;
    int i=0;

    // method number two in Dr.Radi Jarrar sildes ((Hashing strings))
    ////////////////////////////
    Function=((int)name[0]+(int)name[1]*27+(int)name[2]*729)%size_of_original_hash_Table;
    ////////////////////////////

    while(i<size_of_original_hash_Table)
    {
        index= ((Function + (i*i)) % size_of_original_hash_Table);// use the quadratic hashing Formula

        if(hash2[index]->available==0)
        {
            break;
            // get out to return this value of index because it is empty
        }
        //printf("Collision!!!!.......\n");
        i++;// increment the value of i because this index is occupied
    }
    return index;// return value acts the empty and suitable index to insert the hash node

}

// this function is to read data from file pharmacy.txt

void Initialize_Hashing()
{

    for(int i=0; i<size_of_original_hash_Table; i++)
    {

        // do the memory allocation for each cell in the hash table
        HashTable[i]=(struct HashNode*)malloc(sizeof(struct HashNode));

        HashTable[i]->available=0; // this cell is available now , you can insert inside it

        // initialize each value with none
        strcpy(HashTable[i]->name,"");
        strcpy(HashTable[i]->active_ingredient,"");
        strcpy(HashTable[i]->category,"");
        strcpy(HashTable[i]->indication,"");
        strcpy(HashTable[i]->disease,"");
        strcpy(HashTable[i]->expire_date,"");
        strcpy(HashTable[i]->count,"");
        strcpy(HashTable[i]->company,"");

    }
}

void ReadFileForHashing()
{

    FILE* fptr;
    char line[500];
    char temp[7][30];
    fptr=fopen("Pharmacy.txt","r");
    if(fptr== NULL)
    {
        printf("Sorry! but the file is not here\n");
    }
    else
    {
        while (fgets(line, sizeof(line), fptr))
        {
            char * token = strtok(line,":");

            for(int i=0; i<8; i++)
            {
                strcpy(temp[i],token);
                token = strtok(NULL, ":");
            }
            Insert_File_To_Hash(temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6],temp[7]);

        }

    }
    fclose(fptr);

}

// via this function we will insert the hashing nodes in the hashTable

void Insert_File_To_Hash(char name[], char active_Ingredeint[], char category[],
                         char indication[], char disease[], char expiry_date[], char count[],char company[])
{
    int index;
    index = indixing(name,size_of_original_hash_Table);

    strcpy(HashTable[index]->name, name);
    strcpy(HashTable[index]->active_ingredient,active_Ingredeint);
    strcpy(HashTable[index]->category,category);
    strcpy(HashTable[index]->indication,indication);
    strcpy(HashTable[index]->disease,disease);
    strcpy(HashTable[index]->expire_date,expiry_date);
    strcpy(HashTable[index]->count,count);
    strcpy(HashTable[index]->company,company);
    HashTable[index]->available=1; // this slot is not available now == it is full

    counter++; // increment the number of full slots

    // check to make rehash or not
    if(counter>=(size_of_original_hash_Table/2) )
    {
        Rehashing();
    }
}

void Rehashing()
{

    printf("We Are Rehashing now...........\n");
    // swap sizes to set the new size for the new array
    int previous_size= size_of_original_hash_Table;
    size_of_original_hash_Table= New_Size(size_of_original_hash_Table);
    printf("This is the new size while rehashing : %d\n",size_of_original_hash_Table);
    struct HashNode* Hash2[size_of_original_hash_Table];

    // initialize new hash table
    for(int i=0; i<size_of_original_hash_Table; i++)
    {
        // The same steps of  original hash table initialization
        Hash2[i]=(struct HashNode*)malloc(sizeof(struct HashNode));
        Hash2[i]->available=0;

        // initialize each field of the node in hash

        for(int j=0; j<15; j++)
        {
            Hash2[i]->name[j]=NULL;// to delete the name
        }

        for(int j=0; j<5; j++)
        {
            Hash2[i]->active_ingredient[j]=NULL;
            Hash2[i]->count[j]=NULL;
        }

        for(int j=0; j<20; j++)
        {
            Hash2[i]->category[j]=NULL;
            Hash2[i]->indication[j]=NULL;
        }

        for(int j=0; j<100; j++)
        {
            Hash2[i]->disease[j]=NULL;
        }

        for(int j=0; j<10; j++)
        {
            Hash2[i]->expire_date[j]=NULL;
        }
        for(int j=0; j<30; j++)
        {

            Hash2[i]->company[j]=NULL;
        }
    }

         // transfer all cells from the previous hash table to the new one

    for(int i=0; i<previous_size; i++)
    {
        if(HashTable[i]->available ==1) // if this slot is full then transfer its info
        {

            int index2;
            index2=indixing2(HashTable[i]->name,Hash2); // get the index to insert

            strcpy(Hash2[index2]->name,HashTable[i]->name);
            strcpy(Hash2[index2]->active_ingredient,HashTable[i]->active_ingredient);
            strcpy(Hash2[index2]->category,HashTable[i]->category);
            strcpy(Hash2[index2]->indication,HashTable[i]->indication);
            strcpy(Hash2[index2]->disease,HashTable[i]->disease);
            strcpy(Hash2[index2]->expire_date,HashTable[i]->expire_date);
            strcpy(Hash2[index2]->count,HashTable[i]->count);
            strcpy(Hash2[index2]->company,HashTable[i]->company);

            Hash2[index2]->available=1; // This slot now is full in the new hash table
        }

        free(HashTable[i]); // free the original hash table to initialize it again and fill it again
    }
       // initialize the hash table with the new size
    Initialize_Hashing();

       // after initialize the hash table again , now put the info in their new place

    for(int i=0; i<size_of_original_hash_Table; i++)
    {
        strcpy(HashTable[i]->name, Hash2[i]->name);
        strcpy(HashTable[i]->active_ingredient, Hash2[i]->active_ingredient);
        strcpy(HashTable[i]->category, Hash2[i]->category);
        strcpy(HashTable[i]->indication, Hash2[i]->indication);
        strcpy(HashTable[i]->disease, Hash2[i]->disease);
        strcpy(HashTable[i]->expire_date,Hash2[i]->expire_date);
        strcpy(HashTable[i]->count, Hash2[i]->count);
        strcpy(HashTable[i]->company,Hash2[i]->company);
        HashTable[i]->available=Hash2[i]->available;

        // free the cell in the temporary table
        free(Hash2[i]);

    }
    // print the hash table after rehashing it
    printf("Hash table after insert and rehashing is :\n\n");
    printf("------------------------------------------------------------>>>\n");
    Hash_Print(size_of_original_hash_Table);
}

void Hash_Print(int size_of_original_hash_Table)
{
    for(int i=0; i<size_of_original_hash_Table; i++)
    {
        if(HashTable[i]->available==1) // if this slot is full then print it
        {
            printf("This spot is Full with this hash node:\n");
            printf("name:%s>>active ingredient:%s>>category:%s>>indication:%s>>disease:%s>>exp_date:%s>>quantity:%s>>company:%s>>\n",HashTable[i]->name,
                   HashTable[i]->active_ingredient,HashTable[i]->category,
                   HashTable[i]->indication,HashTable[i]->disease,HashTable[i]->expire_date,
                   HashTable[i]->count,HashTable[i]->company);
            printf("--------------------------------------->>>\n");
        }
        else if(HashTable[i]->available==0)
        {
            printf("---EMPTY SPOT\n");
            printf("----------------------------------------->>>\n");
        }
    }
}

void Used_Function()
{

        // print all the information about rehashing function and the method used

    printf("----------------------------------------------------------\n\n");
    printf("In My Project I used Open Addressing Hashing with the following properties:\n");
    printf("------------------------------>>\n");
    printf("Type: Quadratic Hashing\n");
    printf("Function used: h(x)=(Function +(i*i)%%size)\n");
    printf("where the function mean : the value we calculated via hashing string\n");
    printf("method 2 in the slide Edited by Dr.Radi Jarrar\n");
    printf("\n------------------------------------------------------------\n");

}

// This function is to insert record from user to hash table

void Insert_record()
{

    int index;
    char name[15];
    char active_ingredient[5];
    char category[20];
    char indication[20];
    char disease[100];
    char expire_date[10];
    char count[5];
    char company[30];

    printf("Dear user to insert a new record in the hash table you must Fill the  following\n information about  the medicine that you want to add\n:");
    printf("Medicine name:\n");
    scanf("%s",&name);
    printf("Active ingredient:\n ");
    scanf("%s",&active_ingredient);
    printf("Medicine category:\n");
    scanf("%s",&category);
    printf("indication:\n");
    scanf("%s",&indication);
    printf("Expire date:\n");
    scanf("%s",&expire_date);
    printf("Quantity:\n");
    scanf("%s",&count);
    printf("Company:\n");
	scanf("%s",&company);


    index=indixing(name,size_of_original_hash_Table);
    printf("The index is %d\n",index);

    // Now we can easily insert the new record in the hash table
    strcpy(HashTable[index]->name, name);
    strcpy(HashTable[index]->active_ingredient,active_ingredient);
    strcpy(HashTable[index]->category,category);
    strcpy(HashTable[index]->indication,indication);
    strcpy(HashTable[index]->disease,disease);
    strcpy(HashTable[index]->expire_date,expire_date);
    strcpy(HashTable[index]->count,count);
    strcpy(HashTable[index]->company,company);
    HashTable[index]->available=1;

    counter++;// increment the value of the counter to check when rehashing is needed

    printf("The number of elements of hashing table %d\n",counter);
    // Now we will check if there is a need for rehashing or not
    if(counter>=(size_of_original_hash_Table/2))
    {
        Rehashing();
    }
    else
    {
        Hash_Print(size_of_original_hash_Table);
    }

}

void Search_In_Hashing()
{
    char name1[30];
    printf("enter the name of medicine you want to search for it:\n");
    scanf("%s",&name1);
    for(int i=0; i< size_of_original_hash_Table; i++)
    {
        if((strcmp(name1, HashTable[i]->name)==0) && (HashTable[i]->available==1))
        {
            printf("This medicine(%s)is available and its in index [%d]\n",HashTable[i]->name,i);
            break;
        }
    }

}

void Delete_cell_Hash()
{
    char name[30];

    printf("Medicine name to delete\n");
    scanf("%s",&name);

    for(int i=0; i< size_of_original_hash_Table; i++)
    {
        if((strcmp(name,HashTable[i]->name)==0)&&(HashTable[i]->available==1))
            // Then this is the cell we search about
        {
            HashTable[i]->available=0; // to show that this cell now it is available to fill again

            for(int j=0; j<15; j++)
            {
                HashTable[i]->name[j]=NULL;// to delete the name
            }

            for(int j=0; j<5; j++)
            {
                HashTable[i]->active_ingredient[j]=NULL; // to delete active ingredient
                HashTable[i]->count[j]=NULL;
            }

            for(int j=0; j<20; j++)
            {
                HashTable[i]->category[j]=NULL; // to delete the category
                HashTable[i]->indication[j]=NULL;
            }

            for(int j=0; j<100; j++)
            {
                HashTable[i]->disease[j]=NULL; // to delete the disease
            }

            for(int j=0; j<10; j++)
            {
                HashTable[i]->expire_date[j]=NULL; // to delete the expire date
            }
            for(int j=0; j<30; j++)
            {
                HashTable[i]->company[j]=NULL; // to delete the Company
            }
            // free the cell
            free(HashTable[i]);

            // print the hash table after deleting
            printf("The Hash table now is :\n");
            Hash_Print(size_of_original_hash_Table);
            break;
        }
    }
    // remove one of the total number of full slots
    counter--;

    printf("The number of full cells in the hash table is %d\n",counter);
}

void Save_Hash_To_File()
{

    FILE* fptr;
    fptr=fopen("Pharmacy.txt","w");

    for(int i=0; i<size_of_original_hash_Table; i++)
    {

           fputs("\n-------------------------------------------------------\n",fptr);

        if(HashTable[i]->available==1)
        {
            fprintf(fptr,"name: %s\n",HashTable[i]->name);
            fprintf(fptr,"active ingredient : %s\n",HashTable[i]->active_ingredient);
            fprintf(fptr,"category: %s\n",HashTable[i]->category);
            fprintf(fptr,"indication: %s\n",HashTable[i]->indication);
            fprintf(fptr,"expire date: %s\n",HashTable[i]->expire_date);
            fprintf(fptr,"company: %s\n",HashTable[i]->company);

        }
        else
        {
            fputs("Empty Spot\n",fptr);
        }

    }

    fclose(fptr);

}
