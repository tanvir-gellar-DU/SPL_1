#include <bits/stdc++.h>
using namespace std;
struct Token
{
    string name;
    string type;
    int id;
};
Token token[10000];
enum TokenID
{
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
string keyword[11] = {"for", "while", "if", "else", "switch", "do", "case", "break", "continue", "return", "struct"};

bool isNotkey(string str)
{
    int count = 0;
    for (int i = 0; i < 10; i++)
    {
        if (str == keyword[i])
        {
            count = 1;
            break;
        }
    }
    if (count == 0)
        return true;
    else
        return false;
}
bool is_valid_integer(string str) // digit string
{
    bool flag = false;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
            return true;
        else
        {
            flag = false;
            break;
        }
    }
    if (flag == true)
        return true;
    else
        return false;
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
bool is_valid_bool(string str)
{
    string arr[2] = {"true", "false"};
    for (int i = 0; i < 2; i++)
    {
        if (str == arr[i])
            return true;
        else
            return false;
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
    bool flag = false;
    if (str[0] >= '0' && str[0] <= '9')
        return false;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z' || str[i] >= 'a' && str[i] <= 'z')

            flag = true;
        if (str[i] >= '0' && str[i] <= '9' || str[i] == '_')
            flag = true;
        else
        {
            flag = false;
            break;
        }
    }

    if (flag)
        return true;
    else
        return false;
}
bool is_loop_keyword(string str)
{
    if (str == "for" || str == "while" || str == "do")
        return true;
    else
        return false;
}
bool is_conditional_keyword(string str)
{
    if (str == "if" || str == "else" || str == "switch" || str == "case")
        return true;
    else
        return false;
}
bool is_control_keyword(string str)
{
    if (str == "break" || str == "continue" || str == "return")
        return true;
    else
        return false;
}
char *str_repeat(char c, int count)
{
    char *result = new char[count + 1]; // Allocate memory
    for (int i = 0; i < count; ++i)
    {
        result[i] = c;
    }
    result[count] = '\0'; // Null-terminate the string
    return result;
}
int main()
{
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
    if (input.is_open())
{
    char prev_char = '\0';
    while (input.get(ch))
    {
        if (isspace(ch))
        {
            if (!str.empty())
            {
               
                if (is_type_specifier(str))
                {
                    token[token1].name = str;
                    token[token1].type = "type_specifier";
                    if (str == "int")
                        token[token1].id = TYPE_INT;
                    else if (str == "float")
                        token[token1].id = TYPE_FLOAT;
                    else if (str == "bool")
                        token[token1].id = TYPE_BOOL;
                    else if (str == "void")
                        token[token1].id = TYPE_VOID;
                    else if (str == "double")
                        token[token1].id = TYPE_DOUBLE;
                    token1++;
                }
                else if (is_loop_keyword(str))
                {
                    token[token1].name = str;
                    token[token1].type = "loop_keyword";
                      if (str == "for")
                        token[token1].id = KW_FOR;
                    else if (str == "while")
                        token[token1].id = KW_WHILE;
                    else if (str == "do")
                        token[token1].id = KW_DO;
                    token1++;
                }
                else if (is_control_keyword(str))
                {
                    token[token1].name = str;
                    token[token1].type = "control_keyword";
                    if (str == "break")
                        token[token1].id = KW_BREAK;
                    else if (str == "continue")
                        token[token1].id = KW_CONTINUE;
                    else if (str == "return")
                        token[token1].id = KW_RETURN;
                    token1++;
                }
                else if (is_conditional_keyword(str))
                {
                    token[token1].name = str;
                    token[token1].type = "conditional_keyword";
                    if (str == "if")
                        token[token1].id = KW_IF;
                    else if (str == "else")
                        token[token1].id = KW_ELSE;
                    else if (str == "switch")
                        token[token1].id = KW_SWITCH;
                    else if (str == "case")
                        token[token1].id = KW_CASE;
                    token1++;
                }
                else if (is_valid_integer(str))
                {
                    token[token1].name = str;
                    token[token1].type = "integer_literal";
                    token[token1].id = LIT_INT;
                    token1++;
                }
                else if (is_valid_float(str))
                {
                    token[token1].name = str;
                    token[token1].type = "float_literal";
                    token[token1].id = LIT_FLOAT;
                    token1++;
                }
                else if (is_valid_identifier(str))
                {
                    token[token1].name = str;
                    token[token1].type = "identifier";
                    token[token1].id = ID_IDENT;
                    token1++;
                }
                else if (str[0] == '#' && str.find('<') != string::npos && str.back() == '>')
                {
                    // Process headers
                    token[token1].name = str;
                    token[token1].type = "header";
                    token[token1].id = 1; 
                    token1++;
                }
                str.clear(); // Clear buffer after processing
            }
        }
        else if (ispunct(ch)) 
        {
            if (!str.empty())
            {
                // Process the buffer before handling the punctuation
                if (is_valid_identifier(str))
                {
                    token[token1].name = str;
                    token[token1].type = "identifier";
                    token[token1].id = ID_IDENT;
                    token1++;
                }
                str.clear();
            }
            // Handle operators and punctuations
            if (ch == '=' && prev_char == '=')
            {
                token[token1].name = "==";
                token[token1].type = "equal_operator";
                token[token1].id = OP_EQUAL;
                token1++;
            }
            else if (ch == '=')
            {
                token[token1].name = "=";
                token[token1].type = "assignment_operator";
                token[token1].id = OP_ASSIGNMENT;
                token1++;
            }
            else if (ch == ';')
            {
                token[token1].name = ";";
                token[token1].type = "semicolon";
                token[token1].id = PUNC_SEMICOLON;
                token1++;
            }
            else if (ch == '+')
            {
                token[token1].name = "+";
                token[token1].type = "addition_operator";
                token[token1].id = OP_ADDITION;
                token1++;
            }
            if (ch == ',')
            {
                token[token1].name = ",";
                token[token1].type = "comma";
                token[token1].id = PUNC_COMMA;
    
                token1++;
            }
            if (ch == '(')
            {
                token[token1].name = "(";
                token[token1].type = "Round_Bracket_O";
                token[token1].id = PUNC_OPEN_ROUNDBRAC;
            
                token1++;
            }
            if (ch == ')')
            {
                token[token1].name = ")";
                token[token1].type = "Round_Bracket_C";
                token[token1].id = PUNC_CLOSE_ROUNDBRAC;
                
                token1++;
            }
            if (ch == '{')
            {
                token[token1].name = "{";
                token[token1].type = "Curly_Bracket_O";
                token[token1].id = PUNC_OPEN_CURLYBRAC;
        
                token1++;
            }
            if (ch == '}')
            {
                token[token1].name = "}";
                token[token1].type = "Curly_Bracket_C";
                token[token1].id = PUNC_CLOSE_CURLYBRAC;
        
                token1++;
            }
            if (ch == '[')
            {
                token[token1].name = "[";
                token[token1].type = "Square_Bracket_O";
                token[token1].id = PUNC_OPEN_SQUAREBRAC;
           
                token1++;
            }
            if (ch == ']')
            {
                token[token1].name = "]";
                token[token1].type = "Square_Bracket_C";
                token[token1].id = PUNC_CLOSE_SQUAREBRAC;
   
                token1++;
            }
            if (ch == '+')
            {
                token[token1].name = "+";
                token[token1].type = "addition";
                token[token1].id = OP_ADDITION;
       
                token1++;
            }
            if (ch == '-')
            {
                token[token1].name = "-";
                token[token1].type = "substraction";
                token[token1].id = OP_SUBTRACTION;

                token1++;
            }
            if (ch == '*')
            {
                token[token1].name = "*";
                token[token1].type = "multiplication";
                token[token1].id = OP_MULTIPLICATION;

                token1++;
            }
            if (ch == '/')
            {
                token[token1].name = "/";
                token[token1].type = "division";
                token[token1].id = OP_DIVISION;

                token1++;
            }
            if (ch == '>')
            {
                token[token1].name = ">";
                token[token1].type = "greater";
                token[token1].id = OP_GREATER;
      
                token1++;
            }
            if (ch == '<')
            {
                token[token1].name = "<";
                token[token1].type = "lesser";
                token[token1].id = OP_LESSER;
       
                token1++;
            }
            if (ch == '!')
            {
                token[token1].name = "!";
                token[token1].type = "NOT";
                token[token1].id = OP_NOT;
      
                token1++;
            }
                prev_char = ch;
    input.get(ch);

    // Multi-character token handling
    if (!str.empty() && isNotkey(str) && ch == '(')
    {
        token[token1].name = str;
        token[token1].type = "func";
        token[token1].id = 61;
        str.clear();
        token1++;
    }
    else if (prev_char == '=' && ch == '=')
    {
        token[token1].name = "==";
        token[token1].type = "EQUAL";
        token[token1].id = OP_EQUAL;
        str.clear();
        token1++;
    }
    else if (prev_char == '!' && ch == '=')
    {
        token[token1].name = "!=";
        token[token1].type = "NOT_EQUAL";
        token[token1].id = OP_NOTEQUAL;
        str.clear();
        token1++;
    }
    else if (prev_char == '>' && ch == '=')
    {
        token[token1].name = ">=";
        token[token1].type = "GREATER_EQUAL";
        token[token1].id = OP_GREATEREQUAL;
        str.clear();
        token1++;
    }
    else if (prev_char == '<' && ch == '=')
    {
        token[token1].name = "<=";
        token[token1].type = "LESS_EQUAL";
        token[token1].id = OP_LESSEQUAL;
        str.clear();
        token1++;
    }
    else if (prev_char == '=' && ch != '=' && (token1 == 0 || (token1 > 0 && token[token1 - 1].name != "==")))
    {
        token[token1].name = "=";
        token[token1].type = "ASSIGNMENT";
        token[token1].id = OP_ASSIGNMENT;
        str.clear();
        token1++;
    }
    else if (prev_char == '(' && ch == '"')
    {
        token[token1].name = "\"-----\"";
        token[token1].type = "STRING_LIT";
        token[token1].id = LIT_STRING;
        str.clear();
        token1++;
    }
            // Add cases for other operators and punctuation as needed
        }
        else
        {
            // Accumulate characters into `str`
            str += ch;
        }
        prev_char = ch;
    }

    // Final flush for any remaining buffer
    if (!str.empty())
    {
        if (is_valid_identifier(str))
        {
            token[token1].name = str;
            token[token1].type = "identifier";
            token[token1].id = ID_IDENT;
            token1++;
        }
        else if (str[0] == '#' && str.find('<') != string::npos && str.back() == '>')
        {
            // Handle remaining header
            token[token1].name = str;
            token[token1].type = "header";
            token[token1].id = 1; 
            token1++;
        }
    }

    input.close();
}
else
{
    cout << "Input file could not be opened." << endl;
}
  cout << "Number of Tokens: " << token1 - 1 << "\n";
    cout << "Tokenization is done successfully\n";

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
  
