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

int gimetry_sum(char w[]){
    int counter = 0;
    for(int l = 0; l < WORD; l++){
        char c = tolower(w[l]);
        if(c == '\0') break;
        if(c > 122 || c < 97){
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

void reverse_str(char* a, char* out){

    int len = strlen(a);
    for(int i=0; i<len; i++){
        out[i] = a[len-1-i];
    }
    out[len] = '\0';
}

void clear_white(char* a, char* b){
    int len_a = strlen(a);
    int len_b = strlen(a);
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

int commper_str(char* a, char* b){
    int len_a = strlen(a);
    int len_b = strlen(b);
    if(len_b != len_a) return FALSE;
    for(int i=0; i<len_a; i++){
        if(a[i] != b[i]) return FALSE;
    }
    return TRUE;
}

void main(){
    char c;
    char t;
    for(int i = 0; i < WORD; i++){
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
    for(int i = 0; i < TXT; i++){
        char c;
        scanf("%c", &c);
        if(c != '~'){
            text[i] = c;
        }
        else{
            break;
        }
    }
    printf("Gematria Sequences: ");
    int word_gim = gimetry_sum(word);
    int first_print=1;
    for(int i = 0; i < TXT-1; i++){
        if(isalpha(text[i])==0) continue;

        for(int j = i+1; j < TXT; j++){
            if(isalpha(text[j])==0) continue;

            if(text[j] == '\0') break; // End of text

            char *sub = (char*) malloc((j-i+1)*sizeof(char));
            strncpy(sub, text+i, j-i+2);
            sub[j-i+1] = '\0';
            int sub_gim = gimetry_sum(sub);            
            if(sub_gim == word_gim){
                if(first_print==0){ printf("~"); }
                printf("%s",sub);
                first_print=0;
            }
            free(sub);
            if(sub_gim > word_gim){
                break;
            }
        }
    }
    printf("\nAtbash Sequences: ");
    char word_at[WORD];
    atbash(word, word_at);
    // printf("%s\n", word_at);
    char word_at_r[WORD];
    reverse_str(word_at, word_at_r);
    // printf("%s\n", word_at_r);
    first_print=1;
    int text_len=strlen(text);
    for(int i = 0; i < text_len-1; i++){
        // if(isalpha(text[i])==0) continue;

        for(int j = i+1; j < text_len; j++){
            // if(isalpha(text[j])a==0) continue;
            // printf("(%c)[%d,%d]", text[j],i,j);
            // if(text[j] == '\0') break; // End of text

            // printf("%d-\n", (j-i+1)*sizeof(char));
            char *sub = (char*) malloc((j-i+2)*sizeof(char));
            strncpy(sub, text+i, j-i+2);
            sub[j-i+1] = '\0';
        
            // printf("(%s)\n", sub);
            // printf("(%p)\n", sub);

            char sub_at[WORD];
            char sub_at_clean[WORD];
            atbash(sub, sub_at);
            // printf("{%s}", sub_at);
            clear_white(sub_at, sub_at_clean);
            // printf("[%s]", sub_at_clean);
            // return;
        
            char sub_at_r[WORD];
            reverse_str(sub_at, sub_at_r);
            char sub_at_r_clean[WORD];
            clear_white(sub_at_r, sub_at_r_clean);


            if(commper_str(word_at, sub_at_clean)){
                if(first_print==0){ printf("~"); }
                printf("%s,", sub_at);
                first_print = 0;
            }
            if(commper_str(word_at, sub_at_r_clean)){
                if(first_print==0){ printf("~"); }
                printf("%s,", sub_at_r);
                first_print = 0;
            }
            

            free(sub);
        }

        // if(text[i] == '~') break; // End of text
    }


    
}
