#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKENS 10000

struct Token {
    char name[100];
    char type[100];
    int id;
};

enum NodeType {
    PROGRAM, DECL_LIST, FUNC_LIST, MAIN_FUNC, DECL, VAR_DECL, FUNC_DECL,
    PARAM_LIST, COMPOUND_STMT, LOCAL_DECLS, LOCAL_DECL, STMT_LIST, STMT,
    EXPR_STMT, IF_STMT, WHILE_STMT, FOR_STMT, RETURN_STMT, BREAK_STMT,
    PRINT_STMT, EXPR, TERM, FACTOR, FOR_EXPR, ARG_LIST, ELSE_STMT,
    SWITCH_STMT, CASE_STMT
};

struct TreeNode {
    NodeType type;
    Token token;
    TreeNode* child1;
    TreeNode* child2;
    TreeNode* child3;
    TreeNode* child4;
};

Token tokens[MAX_TOKENS];
int current = 0;
int token_count = 0;

// Function prototypes
Token get_current_token();
TreeNode* parse_program();
TreeNode* parse_decl_list();
TreeNode* parse_decl();
TreeNode* parse_var_decl();
TreeNode* parse_func_decl();
TreeNode* parse_param_list();
TreeNode* parse_compound_stmt();
TreeNode* parse_local_decls();
TreeNode* parse_local_decl();
TreeNode* parse_stmt_list();
TreeNode* parse_stmt();
TreeNode* parse_expr_stmt();
TreeNode* parse_if_stmt();
TreeNode* parse_while_stmt();
TreeNode* parse_for_stmt();
TreeNode* parse_for_expr();
TreeNode* parse_return_stmt();
TreeNode* parse_break_stmt();
TreeNode* parse_print_stmt();
TreeNode* parse_switch_stmt();
TreeNode* parse_case_stmt();
TreeNode* parse_expr();
TreeNode* parse_term();
TreeNode* parse_factor();
TreeNode* parse_func_list();
TreeNode* parse_main_func();
TreeNode* parse_arg_list();
void print_tree(TreeNode* node, int depth, char* prefix, int is_last);
void free_tree(TreeNode* node);
void read_tokens();

int is_type_specifier(int id) {
    return id == 81 || id == 82 || id == 83 || id == 84; // int, float, char, double
}

TreeNode* create_node(NodeType type, Token token) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->type = type;
    node->token = token;
    node->child1 = node->child2 = node->child3 = node->child4 = NULL;
    return node;
}

void error(const char* message) {
    int temp_current = current;
    const char* temp_message = message;
    char temp_str[100];
    
    printf("Parse error at token ");
    printf("%d", temp_current);
    printf(": ");
    printf("%s", temp_message);
    printf(" - Found '");
    
    {
        int condition = (temp_current < token_count);
        if (condition) {
            strcpy(temp_str, tokens[temp_current].name);
            printf("%s", temp_str);
            printf("' (");
            printf("%d", tokens[temp_current].id);
            printf(")\n");
        } else {
            printf("EOF");
            printf("' (");
            printf("%d", -1);
            printf(")\n");
        }
    }
    
    exit(1);
}

int match(int token_id) {
    int result = 0;
    int temp_current = current;
    int temp_count = token_count;
    int temp_id = token_id;
    
    {
        int condition1 = (temp_current >= temp_count);
        if (condition1) {
            const char* err_msg = "Unexpected end of input";
            error(err_msg);
        }
    }
    
    {
        int condition2 = (tokens[temp_current].id == temp_id);
        if (condition2) {
            current = current + 1;
            result = 1;
        } else {
            result = 0;
        }
    }
    
    return result;
}

Token get_current_token() {
    if (current >= token_count) {
        Token empty_token;
        strcpy(empty_token.name, "");
        strcpy(empty_token.type, "");
        empty_token.id = -1;
        return empty_token;
    }
    return tokens[current];
}

TreeNode* parse_arg_list() {
    if (current >= token_count || get_current_token().id == 39) return NULL;
    TreeNode* node = create_node(ARG_LIST, (Token){"arg_list", "ARG_LIST", 0});
    if (get_current_token().id == 6) { // STRING_LIT
        match(6);
        node->child1 = create_node(FACTOR, tokens[current-1]);
    } else {
        node->child1 = parse_expr();
    }
    if (match(37)) { // Comma
        node->child2 = parse_arg_list();
    }
    return node;
}

TreeNode* parse_print_stmt() {
    TreeNode* node = create_node(PRINT_STMT, (Token){"print_stmt", "PRINT_STMT", 0});
    if (!match(61)) error("Expected print function");
    if (!match(38)) error("Expected (");
    node->child1 = parse_arg_list();
    if (!match(39)) error("Expected )");
    if (!match(36)) error("Expected ;");
    return node;
}

TreeNode* parse_factor() {
    TreeNode* node = create_node(FACTOR, (Token){"factor", "FACTOR", 0});
    int t = get_current_token().id;
    if (t == 61 && tokens[current + 1].id == 38) { 
        match(61);
        TreeNode* id_node = create_node(FACTOR, tokens[current-1]);
        match(38);
        node->child1 = id_node;
        node->child2 = parse_arg_list();
        if (!match(39)) error("Expected )");
    } else if (t == 28 || t == 3 || t == 4 || t == 6) { // IDENTIFIER, INTEGER, FLOAT, STRING
        match(t);
        node->child1 = create_node(FACTOR, tokens[current-1]);
    } else if (t == 38) { // Parenthesized expression
        match(38);
        node->child1 = parse_expr();
        if (!match(39)) error("Expected )");
    } else {
        error("Invalid factor");
    }
    return node;
}

TreeNode* parse_program() {
    TreeNode* node = create_node(PROGRAM, (Token){"program", "PROGRAM", 0});
    while (current < token_count && tokens[current].id == 1) current++; // headers
    node->child1 = parse_decl_list();
    node->child2 = parse_func_list();
    if (current < token_count && tokens[current].id == 9) {
        node->child3 = parse_main_func();
    } else {
        error("Expected main function");
    }
    node->child4 = parse_func_list();
    return node;
}

TreeNode* parse_main_func() {
    TreeNode* node = create_node(MAIN_FUNC, (Token){"main_func", "MAIN_FUNC", 9});
    if (!match(9)) error("Expected int main");
    if (!match(38)) error("Expected (");
    if (!match(39)) error("Expected )");
    node->child1 = parse_compound_stmt();
    return node;
}

TreeNode* parse_decl_list() {
    if (current >= token_count || !is_type_specifier(tokens[current].id)) return NULL;
    TreeNode* node = create_node(DECL_LIST, (Token){"decl_list", "DECL_LIST", 0});
    node->child1 = parse_decl();
    node->child2 = parse_decl_list();
    return node;
}

TreeNode* parse_decl() {
    if (!is_type_specifier(tokens[current].id)) error("Expected type specifier");
    if (current + 2 < token_count && (tokens[current + 1].id == 28 || tokens[current + 1].id == 61) && tokens[current + 2].id == 38) {
        return parse_func_decl();
    }
    return parse_var_decl();
}

TreeNode* parse_var_decl() {
    TreeNode* node = create_node(VAR_DECL, (Token){"var_decl", "VAR_DECL", 0});
    if (!match(81) && !match(82) && !match(83) && !match(84)) error("Expected type specifier");
    TreeNode* type_node = create_node(FACTOR, tokens[current-1]);
    if (!match(28)) error("Expected identifier");
    TreeNode* id_node = create_node(FACTOR, tokens[current-1]);
    node->child1 = type_node;
    node->child2 = id_node;
    if (!match(36)) error("Expected ;");
    return node;
}

TreeNode* parse_func_decl() {
    TreeNode* node = create_node(FUNC_DECL, (Token){"func_decl", "FUNC_DECL", 0});
    if (!match(81) && !match(82) && !match(83) && !match(84)) error("Expected type specifier");
    TreeNode* type_node = create_node(FACTOR, tokens[current-1]);
    if (!match(28) && !match(61)) error("Expected identifier or function name");
    TreeNode* id_node = create_node(FACTOR, tokens[current-1]);
    if (!match(38)) error("Expected (");
    node->child1 = type_node;
    node->child2 = id_node;
    node->child3 = parse_param_list();
    if (!match(39)) error("Expected )");
    node->child4 = parse_compound_stmt();
    return node;
}

TreeNode* parse_param_list() {
    if (current >= token_count || !is_type_specifier(tokens[current].id)) return NULL;
    TreeNode* node = create_node(PARAM_LIST, (Token){"param_list", "PARAM_LIST", 0});
    if (!match(81) && !match(82) && !match(83) && !match(84)) error("Expected type specifier");
    TreeNode* type_node = create_node(FACTOR, tokens[current-1]);
    if (!match(28)) error("Expected identifier");
    TreeNode* id_node = create_node(FACTOR, tokens[current-1]);
    node->child1 = type_node;
    node->child2 = id_node;
    if (match(37)) node->child3 = parse_param_list();
    return node;
}

TreeNode* parse_compound_stmt() {
    TreeNode* node = create_node(COMPOUND_STMT, (Token){"compound_stmt", "COMPOUND_STMT", 0});
    if (!match(40)) error("Expected {");
    node->child1 = parse_local_decls();
    node->child2 = parse_stmt_list();
    if (!match(41)) error("Expected }");
    return node;
}

TreeNode* parse_local_decls() {
    if (current >= token_count || !is_type_specifier(tokens[current].id)) return NULL;
    TreeNode* node = create_node(LOCAL_DECLS, (Token){"local_decls", "LOCAL_DECLS", 0});
    node->child1 = parse_local_decl();
    node->child2 = parse_local_decls();
    return node;
}

TreeNode* parse_local_decl() {
    TreeNode* node = create_node(LOCAL_DECL, (Token){"local_decl", "LOCAL_DECL", 0});
    if (!match(81) && !match(82) && !match(83) && !match(84)) error("Expected type specifier");
    TreeNode* type_node = create_node(FACTOR, tokens[current-1]);
    if (!match(28)) error("Expected identifier");
    TreeNode* id_node = create_node(FACTOR, tokens[current-1]);
    node->child1 = type_node;
    node->child2 = id_node;
    if (!match(36)) error("Expected ;");
    return node;
}

TreeNode* parse_stmt_list() {
    if (current >= token_count || tokens[current].id == 41) return NULL;
    TreeNode* node = create_node(STMT_LIST, (Token){"stmt_list", "STMT_LIST", 0});
    node->child1 = parse_stmt();
    node->child2 = parse_stmt_list();
    return node;
}

TreeNode* parse_stmt() {
    int t = get_current_token().id;
    if (t == 22) return parse_if_stmt();
    if (t == 14) return parse_while_stmt();
    if (t == 15) return parse_for_stmt();
    if (t == 24) return parse_switch_stmt();
    if (t == 30) return parse_return_stmt();
    if (t == 20) return parse_break_stmt();
    if (t == 61) return parse_print_stmt();
    if (is_type_specifier(t)) return parse_local_decl();
    if (t == 28 && tokens[current + 1].id == 50) return parse_expr_stmt();
    error("Invalid statement");
    return NULL;
}

TreeNode* parse_expr_stmt() {
    TreeNode* node = create_node(EXPR_STMT, (Token){"expr_stmt", "EXPR_STMT", 0});
    if (!match(28)) error("Expected identifier");
    TreeNode* id_node = create_node(FACTOR, tokens[current-1]);
    if (!match(50)) error("Expected =");
    node->child1 = id_node;
    node->child2 = parse_expr();
    if (!match(36)) error("Expected ;");
    return node;
}

TreeNode* parse_if_stmt() {
    TreeNode* node = create_node(IF_STMT, (Token){"if_stmt", "IF_STMT", 0});
    if (!match(22)) error("Expected if");
    if (!match(38)) error("Expected (");
    node->child1 = parse_expr();
    if (!match(39)) error("Expected )");
    node->child2 = parse_compound_stmt();
    if (get_current_token().id == 23) { // KW_ELSE = 23
        match(23);
        TreeNode* else_node = create_node(ELSE_STMT, (Token){"else_stmt", "ELSE_STMT", 0});
        else_node->child1 = parse_compound_stmt();
        node->child3 = else_node;
    }
    return node;
}

TreeNode* parse_while_stmt() {
    TreeNode* node = create_node(WHILE_STMT, (Token){"while_stmt", "WHILE_STMT", 0});
    if (!match(14)) error("Expected while");
    if (!match(38)) error("Expected (");
    node->child1 = parse_expr();
    if (!match(39)) error("Expected )");
    node->child2 = parse_compound_stmt();
    return node;
}

TreeNode* parse_for_stmt() {
    TreeNode* node = create_node(FOR_STMT, (Token){"for_stmt", "FOR_STMT", 0});
    if (!match(15)) error("Expected for");
    if (!match(38)) error("Expected (");
    node->child1 = parse_for_expr();
    if (!match(36)) error("Expected ;");
    node->child2 = parse_for_expr();
    if (!match(36)) error("Expected ;");
    node->child3 = parse_for_expr();
    if (!match(39)) error("Expected )");
    node->child4 = parse_compound_stmt();
    return node;
}

TreeNode* parse_switch_stmt() {
    TreeNode* node = create_node(SWITCH_STMT, (Token){"switch_stmt", "SWITCH_STMT", 0});
    if (!match(24)) error("Expected switch");
    if (!match(38)) error("Expected (");
    node->child1 = parse_expr();
    if (!match(39)) error("Expected )");
    if (!match(40)) error("Expected {");
    node->child2 = parse_case_stmt();
    if (!match(41)) error("Expected }");
    return node;
}

TreeNode* parse_case_stmt() {
    if (current >= token_count || get_current_token().id == 41) return NULL;
    TreeNode* node = create_node(CASE_STMT, (Token){"case_stmt", "CASE_STMT", 0});
    if (get_current_token().id == 26) {
        match(26);
        node->child1 = parse_expr();
        if (!match(36)) error("Expected ;");
        node->child2 = parse_stmt_list();
        node->child3 = parse_case_stmt();
    }
    return node;
}

TreeNode* parse_for_expr() {
    if (get_current_token().id == 36 || get_current_token().id == 39) return NULL;
    return parse_expr();
}

TreeNode* parse_return_stmt() {
    TreeNode* node = create_node(RETURN_STMT, (Token){"return_stmt", "RETURN_STMT", 0});
    if (!match(30)) error("Expected return");
    if (get_current_token().id != 36) {
        node->child1 = parse_expr();
    }
    if (!match(36)) error("Expected ;");
    return node;
}

TreeNode* parse_break_stmt() {
    TreeNode* node = create_node(BREAK_STMT, (Token){"break_stmt", "BREAK_STMT", 0});
    if (!match(20)) error("Expected break");
    if (!match(36)) error("Expected ;");
    return node;
}

TreeNode* parse_expr() {
    TreeNode* node = create_node(EXPR, (Token){"expr", "EXPR", 0});
    if (get_current_token().id == 28 && tokens[current + 1].id == 50) {
        if (!match(28)) error("Expected identifier");
        TreeNode* id_node = create_node(FACTOR, tokens[current-1]);
        if (!match(50)) error("Expected =");
        node->child1 = id_node;
        node->child2 = parse_expr();
    } else {
        node->child1 = parse_term();
        int t = get_current_token().id;
        if (t == 46 || t == 47 || t == 51 || t == 52 || t == 56) {
            if (match(46) || match(47) || match(51) || match(52) || match(56)) {
                TreeNode* op_node = create_node(TERM, tokens[current-1]);
                op_node->child1 = node->child1;
                op_node->child2 = parse_expr();
                node->child1 = op_node;
            }
        }
    }
    return node;
}

TreeNode* parse_term() {
    TreeNode* node = create_node(TERM, (Token){"term", "TERM", 0});
    node->child1 = parse_factor();
    int t = get_current_token().id;
    if (t == 48 || t == 49) {
        if (match(48) || match(49)) {
            TreeNode* op_node = create_node(TERM, tokens[current-1]);
            op_node->child1 = node->child1;
            op_node->child2 = parse_term();
            node->child1 = op_node;
        }
    }
    return node;
}

TreeNode* parse_func_list() {
    if (current >= token_count || !is_type_specifier(tokens[current].id) || tokens[current].id == 9) return NULL;
    TreeNode* node = create_node(FUNC_LIST, (Token){"func_list", "FUNC_LIST", 0});
    node->child1 = parse_func_decl();
    node->child2 = parse_func_list();
    return node;
}

void print_tree(TreeNode* node, int depth, char* prefix, int is_last) {
    if (!node) return;
    printf("%s", prefix);
    if (depth > 0) {
        if (is_last) {
            printf("└── ");
        } else {
            printf("├── ");
        }
    }
    if (node->type == FACTOR || node->type == TERM || (node->type == EXPR && node->child1 && !node->child1->child1)) {
        printf("%s: %s\n", node->token.type, node->token.name);
    } else {
        if (node->type == PROGRAM) {
            printf("PROGRAM\n");
        } else if (node->type == DECL_LIST) {
            printf("DECL_LIST\n");
        } else if (node->type == FUNC_LIST) {
            printf("FUNC_LIST\n");
        } else if (node->type == MAIN_FUNC) {
            printf("MAIN_FUNC\n");
        } else if (node->type == DECL) {
            printf("DECL\n");
        } else if (node->type == VAR_DECL) {
            printf("VAR_DECL\n");
        } else if (node->type == FUNC_DECL) {
            printf("FUNC_DECL\n");
        } else if (node->type == PARAM_LIST) {
            printf("PARAM_LIST\n");
        } else if (node->type == COMPOUND_STMT) {
            printf("COMPOUND_STMT\n");
        } else if (node->type == LOCAL_DECLS) {
            printf("LOCAL_DECLS\n");
        } else if (node->type == LOCAL_DECL) {
            printf("LOCAL_DECL\n");
        } else if (node->type == STMT_LIST) {
            printf("STMT_LIST\n");
        } else if (node->type == STMT) {
            printf("STMT\n");
        } else if (node->type == EXPR_STMT) {
            printf("EXPR_STMT\n");
        } else if (node->type == IF_STMT) {
            printf("IF_STMT\n");
        } else if (node->type == WHILE_STMT) {
            printf("WHILE_STMT\n");
        } else if (node->type == FOR_STMT) {
            printf("FOR_STMT\n");
        } else if (node->type == RETURN_STMT) {
            printf("RETURN_STMT\n");
        } else if (node->type == BREAK_STMT) {
            printf("BREAK_STMT\n");
        } else if (node->type == PRINT_STMT) {
            printf("PRINT_STMT\n");
        } else if (node->type == EXPR) {
            printf("EXPR\n");
        } else if (node->type == TERM) {
            printf("TERM\n");
        } else if (node->type == FACTOR) {
            printf("FACTOR\n");
        } else if (node->type == FOR_EXPR) {
            printf("FOR_EXPR\n");
        } else if (node->type == ARG_LIST) {
            printf("ARG_LIST\n");
        } else if (node->type == ELSE_STMT) {
            printf("ELSE_STMT\n");
        } else if (node->type == SWITCH_STMT) {
            printf("SWITCH_STMT\n");
        } else if (node->type == CASE_STMT) {
            printf("CASE_STMT\n");
        } else {
            printf("UNKNOWN: %s\n", node->token.name);
        }
    }
    char new_prefix[1000];
    strcpy(new_prefix, prefix);
    if (depth > 0) {
        if (is_last) {
            strcat(new_prefix, "    ");
        } else {
            strcat(new_prefix, "│   ");
        }
    }
    if (node->child1) print_tree(node->child1, depth + 1, new_prefix, node->child2 == NULL && node->child3 == NULL && node->child4 == NULL);
    if (node->child2) print_tree(node->child2, depth + 1, new_prefix, node->child3 == NULL && node->child4 == NULL);
    if (node->child3) print_tree(node->child3, depth + 1, new_prefix, node->child4 == NULL);
    if (node->child4) print_tree(node->child4, depth + 1, new_prefix, 1);
}

void free_tree(TreeNode* node) {
    if (!node) return;
    free_tree(node->child1);
    free_tree(node->child2);
    free_tree(node->child3);
    free_tree(node->child4);
    free(node);
}

void read_tokens() {
    FILE* file = fopen("TOKENS.txt", "r");
    if (!file) {
        printf("Error: Could not open TOKENS.txt\n");
        exit(1);
    }
    char line[256];
    token_count = 0;
    while (fgets(line, sizeof(line), file) && token_count < MAX_TOKENS) {
        int no, token_id;
        char token_name[100] = "", token_type[100] = "";
        if (sscanf(line, "%d %99[^ ] %99[^ ] %d", &no, token_name, token_type, &token_id) == 4) {
            strcpy(tokens[token_count].name, token_name);
            strcpy(tokens[token_count].type, token_type);
            tokens[token_count].id = token_id;
            token_count++;
        } else {
            printf("Skipping malformed line: %s", line);
        }
    }
    fclose(file);
}

int main() {
    read_tokens();
    TreeNode* ast = parse_program();
    printf("Abstract Syntax Tree:\n");
    printf("--------------------\n");
    print_tree(ast, 0, "", 1);
    printf("--------------------\n");
    printf("Parsing completed successfully\n");
    free_tree(ast);
    return 0;
}
