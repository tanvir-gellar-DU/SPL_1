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
                while((character= fgetc(input_file) )!= EOF && character != '\n'){}
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
            }else 
            {
                fputc(character,output_file);
                fputc(next_character,output_file);
            }
        }  else 
        {
            fputc(character,output_file);
        }
    }
} 
string keyword[10]={"for","while","if","else","switch","do","case","break","continue","return","struct"};

bool isNotkey(string str)
{
    int count =0;
    for(int i=0;i<10;i++)
    {
        if(str == keyword[i])
        {
            count=1;
            break;
        }
    }
    if(count == 0) return true;
    else
    return false;
}
bool is_valid_integer(string str)  //digit string
{
    bool flag=false;
    for(int i=0;i<str.size();i++)
    {
        if(str[i]>='0' && str[i]<='9')
        return true;
        else
        {
            flag=false;
            break;
        }
    }
    if(flag== true) 
    return true;
    else
    return false;
}
bool is_valid_float(string str)
{
    int flag1=0,flag2=0;
    for(int i=0;i<str.size();i++)
    {
        
    }

}
