#include <bits/stdc++.h>
using namespace std;

struct Token {
    string name;
    string type;
    int id;
};

Token token[10000];
enum TokenID {
    HEADER = 1,          
    LIT_INT = 3,         
    LIT_FLOAT = 4,      
    LIT_BOOL = 5,       
    LIT_STRING = 6,     
    MAIN_FUNC = 9,       
    KW_WHILE = 14,     
    KW_FOR = 15,        
    KW_BREAK = 20,      
    KW_CONTINUE = 21,    
    KW_IF = 22,          
    KW_ELSE = 23,        
    KW_SWITCH = 24,     
    KW_DO = 25,          
    KW_CASE = 26,        
    KW_RETURN = 30,      
    ID_IDENT = 28,       
    PUNC_SEMICOLON = 36, 
    PUNC_COMMA = 37,    
    PUNC_OPEN_ROUNDBRAC = 38,  
    PUNC_CLOSE_ROUNDBRAC = 39, 
    PUNC_OPEN_CURLYBRAC = 40,  
    PUNC_CLOSE_CURLYBRAC = 41, 
    PUNC_OPEN_SQUAREBRAC = 42, 
    PUNC_CLOSE_SQUAREBRAC = 43,
    OP_ADDITION = 46,    
    OP_SUBTRACTION = 47, 
    OP_MULTIPLICATION = 48, 
    OP_DIVISION = 49,    
    OP_ASSIGNMENT = 50,  
    OP_GREATER = 51,     
    OP_LESSER = 52,      
    OP_NOT = 53,         
    OP_GREATEREQUAL = 54,
    OP_LESSEQUAL = 55,   
    OP_EQUAL = 56,       
    OP_NOTEQUAL = 57,    
    FUN_FUNC = 61,      
    TYPE_INT = 81,       
    TYPE_FLOAT = 82,     
    TYPE_BOOL = 83,      
    TYPE_VOID = 84,      
    TYPE_DOUBLE = 85,    
    TYPE_CHAR = 86       
};

void removeAllcomments(FILE *input_file, FILE *output_file) {
    char character, next_character;
    while ((character = fgetc(input_file)) != EOF) {
        if (character == '/') {
            next_character = fgetc(input_file);
            if (next_character == '/') {
                while ((character = fgetc(input_file)) != EOF && character != '\n') {}
                if (character == '\n') fputc(character, output_file);
            } else if (next_character == '*') {
                while ((character = fgetc(input_file)) != EOF) {
                    if (character == '*') {
                        next_character = fgetc(input_file);
                        if (next_character == '/') break;
                        else ungetc(next_character, input_file);
                    }
                }
            } else {
                fputc(character, output_file);
                fputc(next_character, output_file);
            }
        } else {
            fputc(character, output_file);
        }
    }
}

string keyword[10] = {"for", "while", "if", "else", "switch", "do", "case", "break", "continue", "return"};

int getKeywordTokenID(const string& str) {
    if (str == "for") 
    return KW_FOR;
    if (str == "while")
     return KW_WHILE;
    if (str == "if") 
    return KW_IF;
    if (str == "else") 
    return KW_ELSE;
    if (str == "switch") 
    return KW_SWITCH;
    if (str == "do") 
    return KW_DO;
    if (str == "case") 
    return KW_CASE;
    if (str == "break") 
    return KW_BREAK;
    if (str == "continue") 
    return KW_CONTINUE;
    if (str == "return")
     return KW_RETURN;
    return 0; // Not a keyword
}

bool is_type_specifier(string str) {
    string types[] = {"void", "int", "float", "double", "char", "bool", "short", "long"};
    for(string type : types) {
        if(str == type) return true;
    }
    return false;
}

bool is_valid_integer(string str) {
    if(str.empty())
     return false;
    for(int i = 0; i < str.size(); i++) {
        if(str[i] < '0' || str[i] > '9') return false;
    }
    return true;
}

bool is_valid_float(string str) {
    int digit = 0, point = 0;
    for(int i = 0; i < str.size(); i++) {
        if(str[i] >= '0' && str[i] <= '9') digit = 1;
        else if(str[i] == '.') {
            point++;
            if(point > 1) return false;
        } else return false;
    }
    return (digit == 1 && point == 1);
}

bool is_valid_bool(string str) {
    string arr[2] = {"true", "false"};
    for(int i = 0; i < 2; i++) {
        if(str == arr[i]) return true;
    }
    return false;
}

bool is_valid_identifier(string str) {
    if(str.empty() || (str[0] >= '0' && str[0] <= '9')) return false;
    for(int i = 0; i < str.size(); i++) {
        if(!((str[i] >= 'A' && str[i] <= 'Z') || 
             (str[i] >= 'a' && str[i] <= 'z') ||
             (str[i] >= '0' && str[i] <= '9') ||
             str[i] == '_'))
            return false;
    }
    return true;
}

int main() {
   /* FILE *input_file = fopen("input.txt", "r");
    if (input_file == NULL) {
        cout << "Error: Could not open input file.\n";
        return 1;
    }
    
    FILE *output_file = fopen("sourcecode.txt", "w");
    if (output_file == NULL) {
        cout << "Error: Could not open output file.\n";
        fclose(input_file);
        return 1;
    }
    
    removeAllcomments(input_file, output_file);
    fclose(input_file);
    fclose(output_file);
    cout << "Comments have been removed successfully.\n";*/
    char inputFileName[100];

    
    cout << "Enter the input file name (e.g., input.txt): ";
    cin >> inputFileName;

    // Open the input file
    FILE *input_file = fopen(inputFileName, "r");
    if (input_file == NULL) {
        cout << "Error: Could not open input file '" << inputFileName << "'.\n";
        return 1;
    }

    // Open the output file
    FILE *output_file = fopen("sourcecode.txt", "w");
    if (output_file == NULL) {
        cout << "Error: Could not open output file 'sourcecode.txt'.\n";
        fclose(input_file); 
        return 1;
    }

   
    removeAllcomments(input_file, output_file);

   
    fclose(input_file);
    fclose(output_file);

    cout << "Comments have been removed successfully.\n";

    string str = "";
    ifstream input("sourcecode.txt");
    ofstream output("TOKENS.txt");

    if(!input.is_open()) {
        cout << "Input File is not opened\n";
        return 1;
    }

    cout << "File is Opened which contains C source code\n";
    char ch, prev_char = '@';
    int token1 = 0;
    bool afterType = false;

    input.get(ch);
    while(!input.eof()) {
        if(token1 >= 10000) {
            cout << "Error: Token array capacity exceeded\n";
            break;
        }

        if(ch == ' ' || ch == '\n' || ch == '\t') {
            if(!str.empty()) {
                int keywordID = getKeywordTokenID(str);
                if(keywordID != 0) {
                    token[token1].name = str;
                    if (keywordID == KW_IF || keywordID == KW_ELSE) {
                        token[token1].type = "if_stmt";
                    }
                    else if (keywordID == KW_FOR || keywordID == KW_WHILE || keywordID == KW_DO) {
                        token[token1].type = "loop_keyword";
                    }
                    else if (keywordID == KW_SWITCH || keywordID == KW_CASE) {
                        token[token1].type = "switch_stmt";
                    }
                    else if (keywordID == KW_BREAK || keywordID == KW_CONTINUE) {
                        token[token1].type = "control_stmt";
                    }
                    else {
                        token[token1].type = "RETURN";
                    }
                    token[token1].id = keywordID;
                    token1++;
                } else if(is_type_specifier(str)) {
                    string next_str = "";
                    char next_ch = input.get();
                    while(next_ch == ' ' || next_ch == '\t') {
                        next_ch = input.get();
                    }
                    while(next_ch != ' ' && next_ch != '\n' && next_ch != '\t' && 
                          next_ch != ',' && next_ch != ';' && next_ch != '=' && 
                          next_ch != '(' && next_ch != ')' && next_ch != '{' && 
                          next_ch != '}' && next_ch != '[' && next_ch != ']' && 
                          next_ch != '+' && next_ch != '-' && next_ch != '*' && 
                          next_ch != '/' && next_ch != '%' && next_ch != '!' && 
                          next_ch != '<' && next_ch != '>' && next_ch != EOF) {
                        next_str += next_ch;
                        next_ch = input.get();
                    }
                    if(str == "int" && next_str == "main") {
                        token[token1].name = "int_main";
                        token[token1].type = "main_func";
                        token[token1].id = MAIN_FUNC;
                        token1++;
                        str = "";
                        ch = next_ch;
                        prev_char = ch;
                        continue;
                    } else {
                        token[token1].name = str;
                        token[token1].type = "is_type_specifier";
                        if(str == "int") 
                        token[token1].id = TYPE_INT;
                        else if(str == "float")
                         token[token1].id = TYPE_FLOAT;
                        else if(str == "bool") 
                        token[token1].id = TYPE_BOOL;
                        else if(str == "double") 
                        token[token1].id = TYPE_DOUBLE;
                        else if(str == "void") 
                        token[token1].id = TYPE_VOID;
                        else if(str == "char")
                         token[token1].id = TYPE_CHAR;
                        token1++;
                        afterType = true;
                        str = next_str;
                        ch = next_ch;
                        prev_char = ch;
                        continue;
                    }
                } else if(is_valid_integer(str)) {
                    token[token1].name = str;
                    token[token1].type = "integer_literal";
                    token[token1].id = LIT_INT;
                    token1++;
                } else if(is_valid_float(str)) {
                    token[token1].name = str;
                    token[token1].type = "float_literal";
                    token[token1].id = LIT_FLOAT;
                    token1++;
                } else if(is_valid_bool(str)) {
                    token[token1].name = str;
                    token[token1].type = "bool_literal";
                    token[token1].id = LIT_BOOL;
                    token1++;
                } else if(is_valid_identifier(str)) {
                    token[token1].name = str;
                    token[token1].type = "identifier";
                    token[token1].id = ID_IDENT;
                    token1++;
                    afterType = false;
                }
            }
            str = "";
            prev_char = ch;
            input.get(ch);
            continue;
        }

        if(string(",;={}[]()+-*/<>!#").find(ch) != string::npos) {
            if(!str.empty()) {
                int keywordID = getKeywordTokenID(str);
                if(keywordID != 0) {
                    token[token1].name = str;
                    if (keywordID == KW_IF || keywordID == KW_ELSE) {
                        token[token1].type = "if_stmt";
                    }
                    else if (keywordID == KW_FOR || keywordID == KW_WHILE || keywordID == KW_DO) {
                        token[token1].type = "loop_keyword";
                    }
                    else if (keywordID == KW_SWITCH || keywordID == KW_CASE) {
                        token[token1].type = "switch_stmt";
                    }
                    else if (keywordID == KW_BREAK || keywordID == KW_CONTINUE) {
                        token[token1].type = "control_stmt";
                    }
                    else {
                        token[token1].type = "RETURN";
                    }
                    token[token1].id = keywordID;
                    token1++;
                } else if(is_type_specifier(str)) {
                    if(str == "int" && afterType == false) {
                        string next_str = "";
                        char next_ch = ch;
                        if(next_ch == ' ' || next_ch == '\t') {
                            while(next_ch == ' ' || next_ch == '\t') {
                                next_ch = input.get();
                            }
                        }
                        while(next_ch != ' ' && next_ch != '\n' && next_ch != '\t' && 
                              next_ch != ',' && next_ch != ';' && next_ch != '=' && 
                              next_ch != '(' && next_ch != ')' && next_ch != '{' && 
                              next_ch != '}' && next_ch != '[' && next_ch != ']' && 
                              next_ch != '+' && next_ch != '-' && next_ch != '*' && 
                              next_ch != '/' && next_ch != '%' && next_ch != '!' && 
                              next_ch != '<' && next_ch != '>' && next_ch != EOF) {
                            next_str += next_ch;
                            next_ch = input.get();
                        }
                        if(next_str == "main" && next_ch == '(') {
                            token[token1].name = "int_main";
                            token[token1].type = "main_func";
                            token[token1].id = MAIN_FUNC;
                            token1++;
                            str = "";
                            ch = next_ch;
                            prev_char = ch;
                            continue;
                        } else {
                            token[token1].name = str;
                            token[token1].type = "is_type_specifier";
                            token[token1].id = TYPE_INT;
                            token1++;
                            afterType = true;
                            str = next_str;
                            ch = next_ch;
                            prev_char = ch;
                            continue;
                        }
                    } else {
                        token[token1].name = str;
                        token[token1].type = "is_type_specifier";
                        if(str == "int") 
                        token[token1].id = TYPE_INT;
                        else if(str == "float")
                         token[token1].id = TYPE_FLOAT;
                        else if(str == "bool") 
                        token[token1].id = TYPE_BOOL;
                        else if(str == "double") 
                        token[token1].id = TYPE_DOUBLE;
                        else if(str == "void") 
                        token[token1].id = TYPE_VOID;
                        else if(str == "char") 
                        token[token1].id = TYPE_CHAR;
                        token1++;
                        afterType = true;
                    }
                } else if(is_valid_integer(str)) {
                    token[token1].name = str;
                    token[token1].type = "integer_literal";
                    token[token1].id = LIT_INT;
                    token1++;
                } else if(is_valid_float(str)) {
                    token[token1].name = str;
                    token[token1].type = "float_literal";
                    token[token1].id = LIT_FLOAT;
                    token1++;
                } else if(is_valid_bool(str)) {
                    token[token1].name = str;
                    token[token1].type = "bool_literal";
                    token[token1].id = LIT_BOOL;
                    token1++;
                } else if(is_valid_identifier(str) && ch == '(') {
                    token[token1].name = str;
                    token[token1].type = "func";
                    token[token1].id = FUN_FUNC;
                    token1++;
                } else if(is_valid_identifier(str)) {
                    token[token1].name = str;
                    token[token1].type = "identifier";
                    token[token1].id = ID_IDENT;
                    token1++;
                    afterType = false;
                }
            }

            if (ch == '#') {
                str = "#";
                while(ch != '\n' && !input.eof()) {
                    input.get(ch);
                    if(ch == '>') {
                        str += ch;
                        token[token1].name = str;
                        token[token1].type = "Header";
                        token[token1].id = HEADER;
                        token1++;
                        str = "";
                        break;
                    }
                    str += ch;
                }
            }
            else if (ch == '=') {
                if(prev_char == '=') {
                    token[token1-1].name = "==";
                    token[token1-1].type = "EQUAL";
                    token[token1-1].id = OP_EQUAL;
                } else {
                    token[token1].name = "=";
                    token[token1].type = "ASSIGNMENT";
                    token[token1].id = OP_ASSIGNMENT;
                    token1++;
                }
            }
            else if (ch == ';') {
                token[token1].name = ";";
                token[token1].type = "semicolon";
                token[token1].id = PUNC_SEMICOLON;
                token1++;
            }
            else if (ch == ',') {
                token[token1].name = ",";
                token[token1].type = "comma";
                token[token1].id = PUNC_COMMA;
                token1++;
            }
            else if (ch == '(') {
                token[token1].name = "(";
                token[token1].type = "Round_Bracket_O";
                token[token1].id = PUNC_OPEN_ROUNDBRAC;
                token1++;
            }
            else if (ch == ')') {
                token[token1].name = ")";
                token[token1].type = "Round_Bracket_C";
                token[token1].id = PUNC_CLOSE_ROUNDBRAC;
                token1++;
            }
            else if (ch == '{') {
                token[token1].name = "{";
                token[token1].type = "Curly_Bracket_O";
                token[token1].id = PUNC_OPEN_CURLYBRAC;
                token1++;
            }
            else if (ch == '}') {
                token[token1].name = "}";
                token[token1].type = "Curly_Bracket_C";
                token[token1].id = PUNC_CLOSE_CURLYBRAC;
                token1++;
            }
            else if (ch == '[') {
                token[token1].name = "[";
                token[token1].type = "Square_Bracket_O";
                token[token1].id = PUNC_OPEN_SQUAREBRAC;
                token1++;
            }
            else if (ch == ']') {
                token[token1].name = "]";
                token[token1].type = "Square_Bracket_C";
                token[token1].id = PUNC_CLOSE_SQUAREBRAC;
                token1++;
            }
            else if (ch == '+') {
                token[token1].name = "+";
                token[token1].type = "addition";
                token[token1].id = OP_ADDITION;
                token1++;
            }
            else if (ch == '-') {
                token[token1].name = "-";
                token[token1].type = "subtraction";
                token[token1].id = OP_SUBTRACTION;
                token1++;
            }
            else if (ch == '*') {
                token[token1].name = "*";
                token[token1].type = "multiplication";
                token[token1].id = OP_MULTIPLICATION;
                token1++;
            }
            else if (ch == '/') {
                token[token1].name = "/";
                token[token1].type = "division";
                token[token1].id = OP_DIVISION;
                token1++;
            }
            else if (ch == '<') {
                if(prev_char == '<' && token[token1-1].name != "<=") {
                    token[token1-1].name = "<=";
                    token[token1-1].type = "LESS_EQUAL";
                    token[token1-1].id = OP_LESSEQUAL;
                } else {
                    token[token1].name = "<";
                    token[token1].type = "lesser";
                    token[token1].id = OP_LESSER;
                    token1++;
                }
            }
            else if (ch == '>') {
                if(prev_char == '>' && token[token1-1].name != ">=") {
                    token[token1-1].name = ">=";
                    token[token1-1].type = "GREATER_EQUAL";
                    token[token1-1].id = OP_GREATEREQUAL;
                } else {
                    token[token1].name = ">";
                    token[token1].type = "greater";
                    token[token1].id = OP_GREATER;
                    token1++;
                }
            }
            else if (ch == '!') {
                if(prev_char == '!' && token[token1-1].name != "!=") {
                    token[token1-1].name = "!=";
                    token[token1-1].type = "NOT_EQUAL";
                    token[token1-1].id = OP_NOTEQUAL;
                } else {
                    token[token1].name = "!";
                    token[token1].type = "NOT";
                    token[token1].id = OP_NOT;
                    token1++;
                }
            }
            str = "";
        } else if(ch == '"') {
            str = "\"";
            input.get(ch);
            while(ch != '"' && !input.eof()) {
                str += ch;
                input.get(ch);
            }
            if(ch == '"') {
                str += "\"";
                token[token1].name = str;
                token[token1].type = "string_literal";
                token[token1].id = LIT_STRING;
                token1++;
            }
            str = "";
        } else {
            str += ch;
        }
        prev_char = ch;
        input.get(ch);
    }

    input.close();
    cout << "Number of tokens: " << token1 << "\n";
    cout << "Tokenization is done successfully\n";

    output << left << setw(6) << "NO:" << setw(20) << "Token" << setw(30) << "Token_Type" << "Token_ID\n";
    output << string(70, '~') << "\n";

    int idx = 1;
    for(int i = 0; i < token1; i++) {
        output << setw(6) << idx 
               << setw(20) << token[i].name 
               << setw(30) << token[i].type 
               << token[i].id << "\n";
        idx++;
    }
    output.close();

    return 0;
}
