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
    int digit=0,point=0;
    for(int i=0;i<str.size();i++)
    {
        if(str[i]>='0'&& str[i] <='9')
        {
            digit=1;
        }
        
        else if(str[i]=='.')
        {
            point++;
            if (point > 1) return false; 
        }
        else
        {
            return false;
            break;
        }
    }
    if(digit ==1 && point ==1)
    return true;

}
bool is_valid_bool(string str)
{
    string arr[2]={"true","false"};
    for(int i=0;i<2;i++)
    {
        if(str== arr[i])
        return true;
        else return false;
    }
}
bool is_type_specifier(string str)
{
    if (str == "void" || str == "int" || str == "float" || str == "double" ||
        str == "char" || str == "bool" || str == "short" || str == "long")
        {
            return true;
        }
        if (str.back() == '*' && is_type_specifier(str.substr(0, str.size() - 1))) 
        {
        return true;
        }
        return false;
}
bool is_valid_identifier(string str)
{
    bool flag=false;
    for(int i=0;i<str.size();i++)
    {
    if(str[i]>='A'&& str[i]<= 'Z' || str[i]>='a'&& str[i]<='z' )

    flag =true;
    if(str[i]>='0' && str[i]<='9' || str[i]== '_')
    flag =true;
    

    }

    if (flag) return true;
    else return false;
}
