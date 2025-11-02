#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Token Definitions

// Keywords in C language
typedef enum//by tydef function we define a variable which minimise your work.
{
    KW_INT,
    KW_FLOAT,
    KW_DOUBLE,
    KW_CHAR,
    KW_VOID,
    KW_IF,
    KW_ELSE,
    KW_FOR,
    KW_WHILE,
    KW_DO,
    KW_SWITCH,
    KW_CASE,
    KW_DEFAULT,
    KW_BREAK,
    KW_CONTINUE,
    KW_RETURN,
    KW_GOTO,
    KW_CONST,
    KW_STATIC,
    KW_EXTERN,
    KW_TYPEDEF,
    KW_SIGNED,
    KW_UNSIGNED,
    KW_LONG,
    KW_SHORT,
    KW_STRUCT,
    KW_ENUM,
    KW_UNION,
    KW_SIZEOF,
    KW_PRINTF,
    KW_SCANF,
    KW_EXIT,
    KW_MAIN
} KeywordType;
// This enum defines all possible C keywords and some standard functions (like printf, scanf)

// Token Types
typedef enum
{
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_LITERAL,
    TOKEN_OPERATOR,
    TOKEN_SEPARATOR,
    TOKEN_PREPROCESSOR,
    TOKEN_UNKNOWN,
    // TOKEN_CONDITIONAL
} TokenType;
// This enum defines the types of tokens that lexer can produce

// Literals (constant values)
typedef enum
{
    LIT_INT,
    LIT_STRING,
    LIT_CHAR
} LiteralType;
// LiteralType enum defines the type of constant values

// Token struct
typedef struct
{
    TokenType type; // Type of token
    union
    {
        KeywordType keyword; // If token is a keyword
        char *identifier;    // If token is an identifier
        int intVal;          // If token is an integer literal
        char *stringVal;     // If token is a string literal
        char charVal;        // If token is a char literal
    } value;
} Token;
// Token struct stores token type and value (using union to save memory)

// Keyword lookup

// Table mapping keyword strings to their enum types
typedef struct
{
    const char *name;
    KeywordType type;
} KeywordEntry;

KeywordEntry keywordTable[] = {
    {"int", KW_INT}, {"float", KW_FLOAT}, {"double", KW_DOUBLE}, {"char", KW_CHAR}, {"void", KW_VOID}, {"if", KW_IF}, {"else", KW_ELSE}, {"for", KW_FOR}, {"while", KW_WHILE}, {"do", KW_DO}, {"switch", KW_SWITCH}, {"case", KW_CASE}, {"default", KW_DEFAULT}, {"break", KW_BREAK}, {"continue", KW_CONTINUE}, {"return", KW_RETURN}, {"goto", KW_GOTO}, {"const", KW_CONST}, {"static", KW_STATIC}, {"extern", KW_EXTERN}, {"typedef", KW_TYPEDEF}, {"signed", KW_SIGNED}, {"unsigned", KW_UNSIGNED}, {"long", KW_LONG}, {"short", KW_SHORT}, {"struct", KW_STRUCT}, {"enum", KW_ENUM}, {"union", KW_UNION}, {"sizeof", KW_SIZEOF}, {"printf", KW_PRINTF}, {"scanf", KW_SCANF}, {"exit", KW_EXIT}, {"main", KW_MAIN}};
// This table allows the lexer to identify keywords in the input code

// typedef ifelse{
    

// }

int keywordCount = sizeof(keywordTable) / sizeof(keywordTable[0]);

// Function to check if a word is a keyword
int lookupKeyword(const char *word, KeywordType *outType)
{
    for (int i = 0; i < keywordCount; i++)//In this we use for loop to use the loop for finding a keyword.
    {
        if (strcmp(word, keywordTable[i].name) == 0)
        {
            *outType = keywordTable[i].type;
            return 1; // Found keyword
        }
    }
    return 0; // Not a keyword
}

// Lexer Helpers


// Function to generate a number token
Token generate_number(int current, FILE *file)
{
    Token token;
    token.type = TOKEN_LITERAL;

    char buffer[64];//This is used to n=buffer the char intext.
    int i = 0;

    while (isdigit(current))
    { // Read all digits
        buffer[i++] = (char)current;
        current = fgetc(file);//This is used to get the file from the memorey.
    }
    buffer[i] = '\0';
    ungetc(current, file); // Put back the last non-digit character

    token.value.intVal = atoi(buffer); // Convert string to integer
    printf("FOUND INTEGER: %d\n", token.value.intVal);//This is used when we find the integer in the code.
    return token;
}

// Function to generate identifier or keyword token
Token generate_identifier(int current, FILE *file)
{
    Token token;
    char buffer[128];
    int i = 0;

    while (isalnum(current) || current == '_')
    { // Letters, digits, or underscore
        buffer[i++] = (char)current;
        current = fgetc(file);
    }
    buffer[i] = '\0';
    ungetc(current, file); // Put back the last non-alphanumeric character

    KeywordType kw;
    if (lookupKeyword(buffer, &kw))
    { // Check if identifier is keyword
        token.type = TOKEN_KEYWORD;
        token.value.keyword = kw;
        printf("FOUND KEYWORD: %s\n", buffer);
    }
    else
    {
        token.type = TOKEN_IDENTIFIER;
        token.value.identifier = strdup(buffer); // Allocate memory for identifier
        printf("FOUND IDENTIFIER: %s\n", buffer);
    }
    return token;
}

// Function to generate string literal token
Token generate_string(FILE *file)
{
    Token token;
    token.type = TOKEN_LITERAL;

    char buffer[256];
    int i = 0;
    int current = fgetc(file);

    while (current != '"' && current != EOF)
    { // Until closing quote
        buffer[i++] = (char)current;
        current = fgetc(file);
    }
    buffer[i] = '\0';

    token.value.stringVal = strdup(buffer); // Allocate memory for string literal
    printf("FOUND STRING: \"%s\"\n", token.value.stringVal);
    return token;
}

// Function to generate character literal token
Token generate_char(FILE *file)
{
    Token token;
    token.type = TOKEN_LITERAL;

    int current = fgetc(file);
    token.value.charVal = (char)current;

    if (fgetc(file) != '\'')
    { // Check closing quote
        printf("Error: invalid char literal\n");
    }

    printf("FOUND CHAR: '%c'\n", token.value.charVal);
    return token;
}

// Function to generate separators (like ; , () {})
void generate_separator(int current)
{
    switch (current)
    {
    case ';':
        printf("FOUND SEMICOLON\n");
        break;
    case ',':
        printf("FOUND COMMA\n");
        break;
    case '(':
        printf("FOUND OPEN PAREN\n");
        break;
    case ')':
        printf("FOUND CLOSE PAREN\n");
        break;
    case '{':
        printf("FOUND OPEN BRACE\n");
        break;
    case '}':
        printf("FOUND CLOSE BRACE\n");
        break;
    default:
        break;
    }
}

// Function to handle operators and comments
void generate_operator_or_comment(int current, FILE *file)
{
    int next = fgetc(file);

    // Handle single-line comment
    if (current == '/' && next == '/')
    {
        while ((current = fgetc(file)) != '\n' && current != EOF)
            ;
        printf("FOUND COMMENT (single-line)\n");
        return;
    }

    // Handle multi-line comment
    if (current == '/' && next == '*')
    {
        int prev = 0;
        while ((current = fgetc(file)) != EOF)
        {
            if (prev == '*' && current == '/')
                break;
            prev = current;
        }
        printf("FOUND COMMENT (multi-line)\n");
        return;
    }

    // Two-character operators
    if (current == '=' && next == '=')
    {
        printf("FOUND OPERATOR: ==\n");
        return;
    }
    if (current == '!' && next == '=')
    {
        printf("FOUND OPERATOR: !=\n");
        return;
    }
    if (current == '<' && next == '=')
    {
        printf("FOUND OPERATOR: <=\n");
        return;
    }
    if (current == '>' && next == '=')
    {
        printf("FOUND OPERATOR: >=\n");
        return;
    }
    if (current == '+' && next == '+')
    {
        printf("FOUND OPERATOR: ++\n");
        return;
    }
    if (current == '-' && next == '-')
    {
        printf("FOUND OPERATOR: --\n");
        return;
    }
    if (current == '&' && next == '&')
    {
        printf("FOUND OPERATOR: &&\n");
        return;
    }
    if (current == '|' && next == '|')
    {
        printf("FOUND OPERATOR: ||\n");
        return;
    }

    // Single-character operators
    ungetc(next, file); // If not two-character operator, put back
    //In this we use 
    //We define this term to found the operator.
    switch (current)
    {
    case '=':
        printf("FOUND OPERATOR: =\n");
        break;
    case '+':
        printf("FOUND OPERATOR: +\n");
        break;
    case '-':
        printf("FOUND OPERATOR: -\n");
        break;
    case '*':
        printf("FOUND OPERATOR: *\n");
        break;
    case '/':
        printf("FOUND OPERATOR: /\n");
        break;
    case '%':
        printf("FOUND OPERATOR: %%\n");
        break;
    case '<':
        printf("FOUND OPERATOR: <\n");
        break;
    case '>':
        printf("FOUND OPERATOR: >\n");
        break;
    case '!':
        printf("FOUND OPERATOR: !\n");
        break;
    }
}

// Function to handle preprocessor directives
void generate_preprocessor(FILE *file)
{
    char buffer[128];
    int i = 0, current = fgetc(file);

    while (!isspace(current) && current != EOF)
    { // Read until space or EOF
        buffer[i++] = (char)current;
        current = fgetc(file);
    }
    buffer[i] = '\0';
    printf("FOUND PREPROCESSOR: #%s\n", buffer);
}

// Main Lexer
void lexer(FILE *file)//This is used tp get file from the memory and interpret in the identifier to get the exact ketyword.
{
    int current = fgetc(file);
    while (current != EOF)
    {
        if (isspace(current))
        { // Skip whitespaces
            current = fgetc(file);
            continue;
        }
        if (current == '#')
        {
            generate_preprocessor(file);
        }
        else if (isdigit(current))
        {
            generate_number(current, file);
        }
        else if (isalpha(current) || current == '_')
        {
            generate_identifier(current, file);
        }
        else if (current == '"')
        {
            generate_string(file);
        }
        else if (current == '\'')
        {
            generate_char(file);
        }
        else if (strchr(";,(){}", current))
        {
            generate_separator(current);
        }
        else if (strchr("=+-*/!<>%&|", current))
        {
            generate_operator_or_comment(current, file);
        }
        else
        {
            printf("UNKNOWN CHARACTER: %c\n", current);
        }
        current = fgetc(file); // Move to next character
    }
}

// Main Function
int main()
{
    FILE *file = fopen("main.c", "r"); // Open source file to lex
    if (!file)
    {
        printf("Error: could not open file\n");
        return 1;
    }
    lexer(file);  // Call lexer to tokenize the file
    fclose(file); // Close file
    return 0;
}
