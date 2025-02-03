#include <bits/stdc++.h>
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
    TYPE_CHAR,
    // Keywords
    KW_IF = 10,
    KW_ELSE,
    KW_SWITCH,
    KW_CASE,
    KW_WHILE,
    KW_FOR,
    KW_DO,
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
    OP_GREATER,
    OP_LESSER,
    OP_NOT,
    OP_GREATEREQUAL,
    OP_LESSEQUAL,
    OP_EQUAL,
    OP_NOTEQUAL,
    // Punctuation
    PUNC_SEMICOLON = 36,
    PUNC_COMMA,
    PUNC_OPEN_ROUNDBRAC,
    PUNC_CLOSE_ROUNDBRAC,
    PUNC_OPEN_CURLYBRAC,
    PUNC_CLOSE_CURLYBRAC,
    PUNC_OPEN_SQUAREBRAC,
    PUNC_CLOSE_SQUAREBRAC,
    ID_IDENT = 28,
    //function
    FUN_FUNC=61,
};

void removeAllcomments(FILE *input_file, FILE *output_file)
{
    char character, next_character;
    while ((character = fgetc(input_file)) != EOF)
    {
        if (character == '/')
        {
            next_character = fgetc(input_file);
            if (next_character == '/')
            {
                while ((character = fgetc(input_file)) != EOF && character != '\n')
                {
                }
                if (character == '\n')
                {
                    fputc(character, output_file);
                }
            }
            else if (next_character == '*')
            {
                while ((character = fgetc(input_file)) != EOF)
                {
                    if (character == '*')
                    {
                        next_character = fgetc(input_file);
                        if (next_character == '/')
                        {
                            break;
                        }
                        else
                        {
                            ungetc(next_character, input_file);
                        }
                    }
                }
            }
            else
            {
                fputc(character, output_file);
                fputc(next_character, output_file);
            }
        }
        else
        {
            fputc(character, output_file);
        }
    }
}

string keyword[11] = {"for", "while", "if", "else", "switch", "do", "case", "break", "continue", "return"};

bool isNotkey(string str){

    int track=0;

   for(int i=0;i<6;i++){
        if(str==keyword[i]){
            track=1;
            break;
        }
    }

    if(track==0) return true;
    else return false;


}

bool is_valid_integer(string str){

    bool track=false;

    for(int i=0; i<str.size(); i++)
    {
        if(str[i]>='0' && str[i]<='9') track=true;
        else
        {
            track=false;
            break;
        }
    }

    if(track==true) return true;
    else return false;

}

bool is_valid_float(string str)
{
    int digit = 0, point = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            digit = 1;
        }

        else if (str[i] == '.')
        {
            point++;
            if (point > 1)
                return false;
        }
        else
        {
            return false;
            break;
        }
    }
    if (digit == 1 && point == 1)
        return true;
    return false;
}
bool is_valid_bool(string str){

   string arr[3]={"true","false"};

   for(int i=0;i<2;i++){
    if(str==arr[i]) return true;
    else return false;
   }
}

bool is_type_specifier(string str){

    if (str == "void" || str == "int" || str == "float" || str == "double" ||
        str == "char" || str == "bool" || str == "short" || str == "long")
    {
        return true;
    }
}

bool is_valid_identifier(string str)
{
     bool track=false;

    if(str[0]>='0' && str[0]<='9') return false;

    for(int i=0;i<str.size();i++){

        if((str[i]>='A' && str[i]<='Z') || (str[i]>='a' && str[i]<='z'))
            track=true;
        else if(str[i]>='0' && str[i]<='9')
            track=true;
        else if(str[i]=='_')
            track=true;
        else{
            track=false;
            break;
        }

    if(track==true) return true;
    else return false;

    }

}
int ifElse_stmt(string str){

    if(str=="if") return 13;
    else if(str=="else") return 26;
}

bool return_stmt(string str){

    if(str=="return") return true;
}

bool break_stmt(string str){

    if(str=="break") return true;
}

int main() {

     FILE *input_file, *output_file;
    char input_filename[10000], output_filename[10000];
    input_file = fopen("input.txt", "r");

    if (input_file == NULL)
    {
        cout << "Error: Could not open input file.\n";
        return 1;
    }
    output_file = fopen("sourcecode.txt", "w");

    if (output_file == NULL)
    {
        cout << "Error: Could not open output file.\n";
        return 1;
    }
   
    removeAllcomments(input_file, output_file);

    fclose(input_file);
    fclose(output_file);
    cout << "comments have been removed successfully.\n";

    string str = "";
    ifstream input;
    ofstream output;

    char ch;
    int token1 = 0;

    input.open("sourcecode.txt");
    output.open("TOKENS.txt");

    if(input.is_open()){

        cout<<"File is Opened which contains C source code\n";

        char prev_char='@';
        input.get(ch);

        while(true){
            if(ch=='\n' || ch==' ' || ch=='\t'){

                if(is_type_specifier(str)==true){

                   token[token1].name=str;
                    token[token1].type="is_type_specifier";

                     if(str=="int"){
                        token[token1].id=TYPE_INT;
                     }
                     else if(str=="float"){
                        token[token1].id=TYPE_FLOAT;
                     }
                     else if(str=="bool"){
                        token[token1].id=TYPE_BOOL;
                     }
                      else if (str == "double"){
                        token[token1].id = TYPE_DOUBLE;
                      }
                    token1++;
                    str="";
                    token1++;
                    input.get(ch);
                    break;
                }

                if(str[0]=='#' && str[str.size()-1]=='>'){

                    token[token1].name=str;
                    token[token1].type="Header";
                    token[token1].id=1;
                    token1++;
                }
                str="";

            }

            else{

                if(ch=='#'){
                    str+=(char)35;
                }
                else{
                    str+=ch;
                }
            }
            input.get(ch);
          }

        while(!input.eof()){

        if(ch==',' || ch==';' || ch==' ' || ch=='=' || ch=='\n' || ch=='\t' || ch=='('|| ch==')' || ch=='{'|| ch=='}'|| ch=='"'|| ch==']'|| ch=='['|| ch=='+'|| ch=='-'|| ch=='*'|| ch=='/'|| ch=='%'|| ch=='!'|| ch=='<'|| ch=='>'){

            if(is_type_specifier(str)==true){

                    token[token1].name=str;
                    token[token1].type="is_type_specifier";

                     if(str=="int"){
                        token[token1].id=TYPE_INT;
                     }
                     else if(str=="float"){
                        token[token1].id=TYPE_FLOAT;
                     }
                     else if(str=="bool"){
                        token[token1].id=TYPE_BOOL;
                     }
                      else if (str == "double"){
                        token[token1].id = TYPE_DOUBLE;
                      }
                    

                str="";
                token1++;
            }

            else if(str=="while"){

                token[token1].name=str;
                token[token1].type="loop_keyword";
                token[token1].id=KW_WHILE;
                str="";
                token1++;
            }
            else if(str=="for"){

                    token[token1].name=str;
                    token[token1].type="loop_keyword";
                    token[token1].id=KW_FOR;
                str="";
                token1++;
            }
            else if(str=="void"){

                    token[token1].name=str;
                    token[token1].type="is_type_specifier";
                    token[token1].id=TYPE_VOID;
                str="";
                token1++;
            }

            else if(break_stmt(str)==true){

                    token[token1].name=str;
                    token[token1].type="break_stmt";
                    token[token1].id=20;

                str="";
                token1++;
               }
            else if(ifElse_stmt(str)==13){

                    token[token1].name=str;
                    token[token1].type="if_stmt";
                    token[token1].id=22;

                str="";
                token1++;
            }
            else if(ifElse_stmt(str)==26){

                    token[token1].name=str;
                    token[token1].type="if_stmt";
                    token[token1].id=23;

                str="";
                token1++;
            }
            else if(is_valid_integer(str)==true){

                    token[token1].name=str;
                    token[token1].type="integer_literal";
                    token[token1].id=LIT_INT;
                str="";
                token1++;
               }
            else if(is_valid_bool(str)==true){

                    token[token1].name=str;
                    token[token1].type="bool_literal";
                    token[token1].id=LIT_BOOL;
                str="";
                token1++;
               }
            else if(is_valid_float(str)==true){

                    token[token1].name=str;
                    token[token1].type="float_literal";
                    token[token1].id=LIT_FLOAT;
                str="";
                token1++;
               }
            else if(return_stmt(str)==true){

                    token[token1].name=str;
                    token[token1].type="RETURN";
                    token[token1].id=30;

                str="";
                token1++;
               }
             else if (is_valid_identifier(str)==true)
                {
                    token[token1].name = str;
                    token[token1].type = "identifier";
                    token[token1].id = ID_IDENT;
                    str="";
                    token1++;
                }
            if(ch=='"'){

                str+='"';
                prev_char=ch;
                input.get(ch);
                  while(ch!='"'){
                    str=str+ch;
                    prev_char=ch;
                    input.get(ch);
                  }

                    token[token1].name=str;
                    token[token1].type="string_literal";
                    token[token1].id=LIT_STRING;
            }
            if(ch==';'){

                    token[token1].name=";";
                    token[token1].type="semicolon";
                    token[token1].id=PUNC_SEMICOLON;
                str="";
                token1++;

            }
            if(ch==','){

                    token[token1].name=",";
                    token[token1].type="comma";
                    token[token1].id=PUNC_COMMA;
                str="";
                token1++;
            }
            if(ch=='('){

                    token[token1].name="(";
                    token[token1].type="Round_Bracket_O";
                    token[token1].id=PUNC_OPEN_ROUNDBRAC;
                str="";
                token1++;
            }
            if(ch==')'){

                    token[token1].name = ")";
                token[token1].type = "Round_Bracket_C";
                token[token1].id = PUNC_CLOSE_ROUNDBRAC;
                str="";
                token1++;
            }
            if(ch=='{'){
                   token[token1].name = "{";
                token[token1].type = "Curly_Bracket_O";
                token[token1].id = PUNC_OPEN_CURLYBRAC;
                str="";
                token1++;
            }
            if(ch=='}'){
                token[token1].name = "}";
                token[token1].type = "Curly_Bracket_C";
                token[token1].id = PUNC_CLOSE_CURLYBRAC;
                str="";
                token1++;
            }
            if(ch=='['){
                   token[token1].name = "[";
                token[token1].type = "Square_Bracket_O";
                token[token1].id = PUNC_OPEN_SQUAREBRAC;
                str="";
                token1++;
            }
            if(ch==']'){
                     token[token1].name = "]";
                token[token1].type = "Square_Bracket_C";
                token[token1].id = PUNC_CLOSE_SQUAREBRAC;
                str="";
                token1++;
            }

            if(ch=='+'){
                    token[token1].name = "+";
                token[token1].type = "addition";
                token[token1].id = OP_ADDITION;
                str="";
                token1++;
            }
            if(ch=='-'){
                    token[token1].name = "-";
                token[token1].type = "substraction";
                token[token1].id = OP_SUBTRACTION;
                str="";
                token1++;
            }
             if (ch == '*')
            {
                token[token1].name = "*";
                token[token1].type = "multiplication";
                token[token1].id = OP_MULTIPLICATION;
                str="";
                token1++;
            }
             if (ch == '/')
            {
                token[token1].name = "/";
                token[token1].type = "division";
                token[token1].id = OP_DIVISION;
                str="";
                token1++;
            }

            if(ch=='<'){
                    token[token1].name="<";
                    token[token1].type="lesser";
                      token[token1].id = OP_LESSER;
                str="";
                token1++;
            }
            if(ch=='>'){
                    token[token1].name=">";
                    token[token1].type="greater";
                     token[token1].id = OP_GREATER;
                str="";
                token1++;
            }
            if(ch=='!'){
                    token[token1].name="!";
                    token[token1].type="NOT";
                    token[token1].id = OP_NOT;
                str="";
                token1++;
            }
        }
             else str=str+ch;

        prev_char=ch;
        input.get(ch);

        if(isNotkey(str)==true && ch=='('){
                    token[token1].name=str;
                    token[token1].type="func";
                    token[token1].id=FUN_FUNC;
                str="";
                token1++;
           }

        else if(prev_char=='=' && ch=='='){
                    token[token1].name="==";
                    token[token1].type="EQUAL";
                    token[token1].id=OP_EQUAL;
                str="";
                token1++;
           }
        else if(prev_char=='(' && ch=='"'){
                    token[token1].name="\"-----\"";
                    token[token1].type="STRING_LIT";
                    token[token1].id=21;
                str="";
                token1++;
           }
        else if(prev_char=='!' && ch=='='){
                    token[token1].name="!=";
                    token[token1].type="NOT_EQUAL";
                    token[token1].id=LIT_STRING;
                str="";
                token1++;
           }
        else if(prev_char=='>' && ch=='='){
                    token[token1].name=">=";
                    token[token1].type="GREATER_EQUAL";
                    token[token1].id=OP_GREATEREQUAL;
                str="";
                token1++;
           }
        else if(prev_char=='<' && ch=='='){
                    token[token1].name="<=";
                    token[token1].type= OP_LESSEQUAL;
                    token[token1].id=44;
                str="";
                token1++;
           }
        else if(prev_char=='=' && ch!='=' && token[token1-1].name!="==" && token[token1-1].type!="ASSIGNMENT"){
                    token[token1].name="=";
                    token[token1].type="ASSIGNMENT";
                    token[token1].id=OP_ASSIGNMENT;
                str="";
                token1++;
           }
        }
   }
    else{
    cout<<"Input File is not opened\n";
   }

   cout<<"Number of token1s: "<<token1-1<<"\n";
   cout<<"Tokenization is done successfully\n";

   input.close();
   output << std::left; // Align text to the left
output << std::setw(6) << "NO:" << std::setw(20) << "Token" << std::setw(30) << "Token_Type" << "Token_ID\n";
output << std::string(70, '~') << "\n"; // Separator line

int idx = 1; 
vector<int> tokens; 

for (int i = 0; i < token1; ++i)
{
    // Check for "int main"
    if (token[i].name == "int" && i + 1 < token1 && token[i + 1].name == "main")
    {
        output << std::setw(6) << idx 
               << std::setw(20) << "int main" 
               << std::setw(30) << "main_func" 
               << "9\n";
        i++; 
        idx++;
        tokens.push_back(9); 
        continue;
    }

   
    output << std::setw(6) << idx 
           << std::setw(20) << token[i].name 
           << std::setw(30) << token[i].type 
           << token[i].id << "\n";
    tokens.push_back(token[i].id); 
    idx++;
}


output.close();

return 0;
}
  
