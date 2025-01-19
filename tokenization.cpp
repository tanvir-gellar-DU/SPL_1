#include<bits/stdc++.h>
using namespace std;
struct Token{
    string name;
    string type;
    int id;
};
Token token[10000];
enum TokenID {
    // Type Specifiers
    TYPE_INT = 81,
    TYPE_FLOAT,
    TYPE_BOOL,
    TYPE_VOID,
    TYPE_DOUBLE,

    // Keywords
    KW_IF = 10,
    KW_ELSE,
    KW_WHILE,
    KW_FOR,
    KW_RETURN,
    KW_BREAK,
    KW_CONTINUE,

    // Literals
    LIT_INT = 3,
    LIT_FLOAT,
    LIT_BOOL,
    LIT_STRING,

    // Operators
    OP_ADDITION = 46,
    OP_SUBTRACTION,
    OP_MULTIPLICATION,
    OP_DIVISION,
    OP_ASSIGNMENT,

    // Punctuation
    PUNC_SEMICOLON = 36,
    PUNC_COMMA,
    PUNC_OPEN_BRACE,
    PUNC_CLOSE_BRACE,
    PUNC_OPEN_PAREN,
    PUNC_CLOSE_PAREN,
    PUNC_OPEN_BRACKET,
    PUNC_CLOSE_BRACKET,
};
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
string keyword[11]={"for","while","if","else","switch","do","case","break","continue","return","struct"};

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
    if(str[0]>='0' && str[0]<='9')
    return false;
    for(int i=0;i<str.size();i++)
    {
    if(str[i]>='A'&& str[i]<= 'Z' || str[i]>='a'&& str[i]<='z' )

    flag =true;
    if(str[i]>='0' && str[i]<='9' || str[i]== '_')
    flag =true;
    else { 
        flag=false;
        break;}

    }

    if (flag) return true;
    else return false;
}
bool is_loop_keyword(string str) {
    if(str == "for" || str == "while" || str == "do")
    return true;
    else 
    return false;
}
bool is_conditional_keyword(string str) {
     if(str == "if" || str == "else" || str == "switch" || str == "case")
     return true;
     else
     return false;
}
bool is_control_keyword(string str) {
    if(str == "break" || str == "continue" || str == "return")
    return true;
    else
    return false;
}
char* str_repeat(char c, int count) {
    char* result = new char[count + 1]; // Allocate memory
    for (int i = 0; i < count; ++i) {
        result[i] = c;
    }
    result[count] = '\0'; // Null-terminate the string
    return result;
}
int main()
{
    FILE *input_file,*output_file;
     char input_filename[10000], output_filename[10000];
     input_file=fopen("input.txt","r");

     if (input_file == NULL)
     {
     cout<< "Error: Could not open input file.\n";
     return 1;
     }
     output_file=fopen("sourecode.txt","w");

    if (output_file == NULL)
     {
     cout<< "Error: Could not open output file.\n";
     return 1;
     }
     const char *titleOfProject = "ProbStat Prodigy: Data Meets Decision";
    int boxWidth = strlen(titleOfProject) + 6;

    fprintf(output_file, "\n\n\t\t+%s+\n", str_repeat('-', boxWidth - 2));
    fprintf(output_file, "\t\t|%s|\n", str_repeat(' ', boxWidth - 2));
    fprintf(output_file, "\t\t|  %s%s|\n", titleOfProject, str_repeat(' ', boxWidth - 4 - strlen(titleOfProject)));
    fprintf(output_file, "\t\t|%s|\n", str_repeat(' ', boxWidth - 2));
    fprintf(output_file, "\t\t+%s+\n", str_repeat('-', boxWidth - 2));

    removeAllcomments(input_file,output_file);

    fclose(input_file);
    fclose(output_file);
    cout <<"comments have been removed successfully.\n";

    string str="";
    ifstream input;
    ofstream output;

    char ch;
    int token1 =0;

    input.open("sourcecode.txt");
    output.open("TOKENS.txt");
char prev_char = '@';

while (input.get(ch)) {  
    if (ch == '\n' || ch == ' ' || ch == '\t') {  
        if (is_type_specifier(str) == true) {  
            token[token1].name = str;
            token[token1].type = "is_type_specifier";

            if (str == "int") {
                token[token1].id = TYPE_INT;
            }
            else if (str == "float") {
                token[token1].id = TYPE_FLOAT;
            }
            else if (str == "bool") {
                token[token1].id = TYPE_BOOL;
            }
             else if (str == "void") {
                token[token1].id = TYPE_VOID;
            }
             else if (str == "double") {
                token[token1].id = TYPE_DOUBLE;
            }

            str = "";  
            token1++;   
        }
    }
    else {
        str += ch;  
    }
}

input.close();  
output.close(); 


    return 0;
}
