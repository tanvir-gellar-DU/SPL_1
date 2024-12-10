#include<bits/stdc++.h>
using namespace std;
struct Token{
    string name;
    string type;
    int id;
};
Token token[10000];
void removeAllcomments(FILE *input_file,FILE *output_file)
{
    char character,next_character;
    while((character =fgetc(input_file))!= EOF)
    {
        if(character =='/')
        {
            next_character=fgetc(input_file);
            if(next_character =='/')
            {
                while((character== fgetc(input_file) != EOF && character != '\n')){}
                if(character == '\n')
                {
                    fputc(character,output_file);
                }
            } else if(next_character == '*')
            {
                while((character =fgetc(input_file))!= EOF)
                {
                    if(character =='*')
                    {
                         next_character=fgetc(input_file);
                         if(next_character=='/')
                         {
                            break;
                         }
                         else{
                            ungetc(next_character,input_file);
                         }

                    }
                }
            }
        }
    }
} 
