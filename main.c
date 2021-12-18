#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#define TXT 1024
#define WORD 30

#define TRUE 1
#define FALSE 0

char word[WORD];
char text[TXT];

int gimetry_sum(char* w, int len){

    int counter = 0;
    for(int l = 0; l < len; l++){
        char c = tolower(w[l]);
        if(c > 'z' || c < 'a'){
            continue;
        }
        counter = counter + c-96;
    }
    return counter;
}

void atbash(char* a, char* out){

    for(int i=0; i<WORD; i++){
        char new = a[i];

        if(isalpha(new)!=0){
            if(isupper(new)){
                new = 'Z' - (a[i] - 'A');
            }
            else{
                new = 'z' - (a[i] - 'a');
            }
        }
        out[i] = new;
    }
}

int exist(char* s){
    int len_s = strlen(s);
    int len_w = strlen(word);
    int flag = 1;
    if(len_s < len_w){
        return 0;
    }
    for(int i = 0; i < len_w; i++){
        for(int j = 0; j < len_s; j++){
            if(word[i] == s[j]){ //if this char is exist in the given word (char --> 0)
                s[j] = 0;
                flag = 1;
                break; //i dont want to put 0 in double same char
            }
            else{
                flag = 0;
            }
        }
        if(flag == 0){
            return 0;
        }
    }
    return 1;
}

void reverse_str(char* a, char* out){

    int len = strlen(a);
    for(int i=0; i<len; i++){
        out[i] = a[len-1-i];
    }
    out[len] = '\0';
}

void clear_white(char* a, char* b){
    int len_a = strlen(a);
    int a_i=0;
    int b_i=0;
    while(a_i<=len_a){
        if(a[a_i] == ' ' || a[a_i] == '\n' || a[a_i] == '\t') {
            a_i++;
            continue;
        }
        b[b_i++] = a[a_i++];
    }
}

int compare_str(char* a, char* b){
    int len_a = strlen(a);
    int len_b = strlen(b);
    if(len_b != len_a) return FALSE;
    for(int i=0; i<len_a; i++){
        if(a[i] != b[i]) return FALSE;
    }
    return TRUE;
}

void get_word(){
    for(int i = 0; i < WORD; i++){ // gets the word
        char c;
        scanf("%c", &c);
        if(c != ' ' && c != '\n' && c != '\t'){
            word[i] = c;
        }
        else{
            word[i] = '\0';
            break;
        }
    }
}

void get_text(){
    for(int i = 0; i < TXT; i++){ // gets the text
        char c;
        scanf("%c", &c);
        if(c != '~'){
            text[i] = c;
        }
        else{
            break;
        }
    }
}

void print_gematria(){
    int text_len=strlen(text);
    int word_len=strlen(word);

    printf("Gematria Sequences: ");
    int word_gim = gimetry_sum(word, word_len);
    int first_print=1;
    for(int i = 0; i < text_len-1; i++){
        if(isalpha(text[i])==0) continue;

        for(int j = i; j < text_len; j++){
            if(isalpha(text[j])==0) continue;

            if(text[j] == '\0') break; // End of text

            int sub_len = j-i+1;
            int sub_gim = gimetry_sum(text+i, sub_len);
            if(sub_gim == word_gim){
                if(first_print==0){ printf("~"); }
                for(int x=0; x<sub_len; x++) {printf("%c", text[x+i]);}
                first_print=0;
            }
            if(sub_gim > word_gim){
                break;
            }
        }
    }
}

void print_atbash(){
    
    int text_len=strlen(text);
    printf("\nAtbash Sequences: ");
    char word_at[WORD];
    atbash(word, word_at);
    char word_at_r[WORD];
    reverse_str(word_at, word_at_r);
    int first_print=1;

    for(int i = 0; i < text_len-1; i++){
        for(int j = i+1; j < text_len; j++){
            
            if(text[j] == '\0'  || text[j]== '~') break; // End of text

            char *sub = (char*) malloc((j-i+2)*sizeof(char));
            strncpy(sub, text+i, j-i+1);
            sub[j-i+1] = '\0';

            char sub_at[WORD];
            char sub_at_clean[WORD];
            char sub_at_r[WORD];
            char sub_at_r_clean[WORD];
        
            atbash(sub, sub_at);
            clear_white(sub_at, sub_at_clean);
            reverse_str(sub_at, sub_at_r);
            clear_white(sub_at_r, sub_at_r_clean);

            if(compare_str(word_at_r, sub_at_clean)){
                if(first_print==0){ printf("~"); }
                printf("%s", sub_at_clean);
                first_print = 0;
            }
            if(compare_str(word_at, sub_at_r_clean)){
                if(first_print==0){ printf("~"); }
                printf("%s", sub_at_r_clean);
                first_print = 0;
            }

            free(sub);
        }
    }
}

void print_anagram(){

    int text_len=strlen(text);
    int first_print=1;
    printf("\nAnagram Sequences: ");
    for(int i = 0; i < text_len-1; i++){
        if(isalpha(text[i])==0) continue;
        
        for(int j = i+1; j < text_len; j++){
            if(isalpha(text[j])==0) continue;

            if(text[j] == '\0') break; // End of text

            char *sub = (char*) malloc((j-i+2)*sizeof(char));
            strncpy(sub, text+i, j-i+2);
            sub[j-i+1] = '\0';
            int len = strlen(sub);
            char *sub2 = (char*) malloc((len+2)*sizeof(char));
            strcpy(sub2, sub);
            int flag = 1;
            if(exist(sub)==1){ // if all the chars in sub word exist in the input word
                for(int i = 0; i < len; i++){ //check if all the array is 0
                    if(sub[i] != 0 && sub[i] != ' ' && sub[i] != '\n' && sub[i] != '\t'){
                        flag = 0;
                        break;
                    }
                }
            }
            else{
                flag = 0;
            }
            if(flag == 1){
                if(first_print==0){ printf("~"); }
                printf("%s", sub2);
                first_print=0;
            }

            free(sub);
            free(sub2);
        }
    }
}


int main(){
    get_word();
    get_text();
    print_gematria();
    print_atbash();
    print_anagram();

    return 0;
}
