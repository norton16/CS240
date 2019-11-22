/*
 * Name, hw3.c, CS 24000, Fall 2019
 * Last updated Sept, 2019
 */

// PROVIDED TO STUDENTS

/*DO NOT CHANGE----------BEGIN*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"hashtable.h"

int main() {
    char ch;
    char name[100];
    struct hash_table_element* hash_table = 0;
    int table_size, new_table_size;
    while (1) {
        printf("\nWelcome to Hashtable\n");
        printf("--------------------\n");
        printf("A-Initialize hash table\n");
        printf("B-Compute hash value\n");
        printf("C-Insert name\n");
        printf("D-Load names from file\n");
        printf("E-Delete name\n");
        printf("F-Search name\n");
        printf("G-Number of empty elements\n");
        printf("H-Average list length\n");
        printf("I-Maximum list length\n");
        printf("J-Resize hash table (Extra Credit)\n");
        printf("K-Display hash table\n");
        printf("L-Delete hash table\n");
        printf("M-Exit\n");
        printf("--------------------\n");
        printf("Select an option: ");
        scanf("%c",&ch);
        getchar();
        if (ch != 'M' && ch != 'A' && hash_table == NULL) {
            printf("Initialize hash table first\n");
            exit(0);
        }
        switch (ch) {
            case 'A':
                printf("Input number of hash table elements: ");
                scanf("%d", &table_size);
                getchar();
                hash_table =  init_hash_table(table_size);
                break;
            case 'B':
                printf("Enter the name whose hash value to compute: ");
                scanf("%s", name);
                getchar();        
                printf("hash value: %d\n", get_hash(name, table_size));
                break;
            case 'C':
                printf("Enter the name to insert: "); 
                scanf("%s", name);
                getchar();
                insert_name(hash_table, table_size, name);
                printf("Inserted name: %s\n", name);
                break;
            case 'D':
                printf("Enter the name of the input file: ");
                scanf("%s", name);
                getchar();
                load_from_file(hash_table, table_size, name);
                break;
            case 'E':
                printf("Enter the name to delete: ");
                scanf("%s", name);
                getchar();
                if (delete_name(hash_table, table_size, name)) {
                    printf("Deleted name: %s\n", name);
                }
                else {
                    printf("Name not found: %s\n", name);
                }
                break;
            case 'F':
                printf("Enter the name to search: ");
                scanf("%s", name);
                getchar();
                if (search_in_hash_table(hash_table, table_size, name)) {
                    printf("Found name: %s\n", name);
                }
                else {
                    printf("Name not found: %s\n", name);
                }
                break;
            case 'G':
                printf("Number of empty hash table elements: %d\n",
                    compute_stats_empty(hash_table, table_size));
                break;
            case 'H':
                printf("Average list length: %.2f\n",
                    compute_stats_average(hash_table, table_size));
                break;
            case 'I':
                printf("Length of longest list: %d\n",
                    compute_stats_max(hash_table, table_size));
                break;
            case 'J':
                printf("Enter the new number of hash table elements: ");
                scanf("%d", &new_table_size);
                getchar();
                hash_table = resize_hash_table(hash_table, table_size, new_table_size);
                table_size = new_table_size;
                break;
            case 'K':
                display(hash_table, table_size);
                break;
            case 'L':
                free_hashtable(hash_table, table_size);
                break;
            case 'M':
                exit(0);
            default:
                printf("You have entered wrong option!\n");
                break;
        }
    }
}


void load_from_file(struct hash_table_element* hash_table, int size, char *filename) {
    FILE* fp= fopen(filename,"r");
    assert(fp);
    int num=0;
    fscanf(fp, "%d\n", &num);
    for(int i=0;i<num;i++){
        char name[100];
        fscanf(fp, "%s",name);
        insert_name(hash_table, size, name);
   }
    fclose(fp);
}

void display(struct hash_table_element* hash_table, int table_size) {
    struct sll_node *ptr;
    printf("\nData in Hash Table:\n");
    for (int i = 0; i < table_size; i++) {
        printf("Index %d:", i);
        if (hash_table[i].head == NULL) {
            printf("NULL\n");            
            continue;
        }
        ptr = hash_table[i].head;
        while (ptr != NULL) {
            printf(" %s ->", ptr->name);
            ptr = ptr->next;
        }
        printf(" NULL\n");
    }
}

/*DO NOT CHANGE----END*/
// END PROVIDED TO STUDENTS


// PART 1
struct hash_table_element* init_hash_table(int table_size){
    // write your code here
    struct hash_table_element* table;
    table = (struct hash_table_element*)malloc(table_size * sizeof(struct hash_table_element)); 
    for(int i = 0; i < table_size; i++){
        table[i].head = NULL;
    }
    return table; // feel free to modify this line 
}

// PART 2
int get_hash(char* name, int table_size) {
    // write your code here
    int total = 0;
    int i = 0;
    while(name[i] != '\0'){
        total += name[i];
        i++;
    }
    return ((total * total) % table_size); // feel free to modify this line
}

// PART 3
void insert_name(struct hash_table_element* hash_table, 
                 int size, char *name) {
    // write your code here
    //hash_table = (struct hash_table_element*)malloc((size * sizeof(struct hash_table_element))); 
    
    int i = 0;
    while(name[i] != '\0'){
        i++;
    }
    char* n = (char*)malloc(i * sizeof(char));
    for(int j = 0; j<i; j++){
        n[j] = name[j];
    }

    struct sll_node* node = (struct sll_node*)malloc(sizeof(struct sll_node)); 
    //name is inserted in new node of linked list
    node->name = n;
    node->next = hash_table[get_hash(n, size)].head;
    hash_table[get_hash(n, size)].head = node;
}


// PART 4
int delete_name(struct hash_table_element* hash_table, 
                int table_size, char* name) {
    // write your code here
    struct sll_node* temp = hash_table[get_hash(name, table_size)].head; 
    struct sll_node* prev = (struct sll_node*)malloc(sizeof(struct sll_node));
    
    if (temp != NULL && strcmp(temp->name, name) == 0){ 
        hash_table[get_hash(name, table_size)].head = temp->next;   
        free(temp);               
        return 1; 
    } 
 
    while (temp != NULL){   
        if(strcmp(temp->name, name) == 0){
            prev->next = temp->next;
            free(temp); 
            return 1;  
        }
        prev = temp; 
        temp = temp->next; 
    } 
     return 0;
     free(temp);
     free(prev);
}

// PART 5
int search_in_hash_table(struct hash_table_element* hash_table, int table_size, char* name) {
    // write your code here
    struct sll_node* temp = hash_table[get_hash(name, table_size)].head; 

    int found = 0;
    while (temp != NULL) 
    { 
        if(strcmp(temp->name, name) == 0){
            found++;
        }
        temp = temp -> next;
    } 
    if(found > 0){
        return 1;
    }
    else{
        return 0;
    }
}

// PART 6
int compute_stats_empty(struct hash_table_element* hash_table, int table_size){
    // write your code here
    //struct sll_node* temp = hash_table[get_hash(name, table_size)].head; 

    int found = 0;
    for(int i = 0; i<table_size; i++){
        if(hash_table[i].head == NULL)
        found++;
    }
    return found; // feel free to modify this line    
}

// PART 7
float compute_stats_average(struct hash_table_element* hash_table, int table_size){
    // write your code here
    struct sll_node* temp; 
    int found = 0;
    int length = 0;
    for(int i = 0; i<table_size; i++){
        if(hash_table[i].head != NULL){
             temp = hash_table[i].head;
              while (temp != NULL) 
                { 
                    temp = temp->next;
                    length++;
                }
                 found++;
                }            
        }   
    float avg = ((length/((float)found)));
    return avg; // feel free to modify this line       
    //return 0.0f; // feel free to modify this line
}

// PART 8
int compute_stats_max(struct hash_table_element* hash_table, int table_size){
    // write your code here
    struct sll_node* temp; 
    int found = 0;
    int length = 0;
    int max = 0;
    for(int i = 0; i<table_size; i++){
        if(hash_table[i].head != NULL){
             temp = hash_table[i].head;
              while (temp != NULL) 
                { 
                    temp = temp->next;
                    length++;
                }
                if(length > max){
                    max = length;
                }
                length = 0;
                found++;
                }            
        }   
    return max;
}


// PART 9
void free_hashtable(struct hash_table_element* hash_table, int table_size){
    // write your code here
   struct sll_node* temp;
   struct sll_node* n; 
  
  for(int i = 0; i < table_size; i++){
    temp = hash_table[i].head;
   while (temp != NULL){ 
        n = temp->next;
        free(temp->name); 
       free(temp); 
       temp = n; 
   }
  } 
    free(temp);
    free(n);
   free(hash_table);
}


// EXTRA CREDIT
struct hash_table_element* resize_hash_table(struct hash_table_element* old_table, int old_size, int new_size){
    // write your code here    
   // old_table = (struct hash_table_element*)malloc(old_size * sizeof(struct hash_table_element)); 
     struct hash_table_element* newtable = 
     (struct hash_table_element*)realloc(old_table, sizeof(struct hash_table_element) * new_size);
    struct sll_node* temp;
    struct sll_node* temp2;
     struct sll_node* n; 
     struct sll_node* n2; 

    int l = 0;
    if(new_size > old_size){
        l = old_size;
    }
    else{
        l = new_size;
    }

  for(int i = 0; i < l; i++){
    temp = old_table[i].head;
    temp2 = newtable[i].head;
   while (temp != NULL && temp2 != NULL){ 
        n = temp->next;
        n2 = temp2->next;
        temp2->name = temp->name;
        //cd ..free(temp->name); 
       free(temp); 
       temp = n;
       temp2 = n2; 
   }
  } 
    return newtable; // feel free to modify this line 
    //free(old_table);
}

