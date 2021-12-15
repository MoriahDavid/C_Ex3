#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#define TXT 1024
#define WORD 30
char word[WORD];
char text[TXT];

int gimetry_sum(char word[]){
    int counter = 0;
    for(int l = 0; l < WORD; l++){
        char c = tolower(word[l]);
        if(c < 65 || c > 97){
            continue;
        }
        counter = counter + c-96;
    }
    return counter;
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
        t = scanf("%c", text);
        if(c != '~'){
            text[i] = t;
        }
        else{
            break;
        }
    }
    int word_gim = gimetry_sum(word);
    for(int i = 0; i < TXT; i++){
        for(int j = i+1; j < TXT-1; j++){
            char *sub = (char*) malloc((j-i+1)*sizeof(char));
            strncpy(sub, text+(i, j), j-i+1);
            int sub_gim = gimetry_sum(sub);
            if(sub_gim > word_gim){
                break;
            }
            if(sub_gim == word_gim){
                printf("%s",sub);
            }
        }
    }
    
}
