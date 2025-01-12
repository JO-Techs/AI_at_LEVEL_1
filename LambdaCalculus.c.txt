#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Type of lambda calculus expressions
typedef enum {
    VAR,       // Variable
    LAMBDA,    // Lambda abstraction
    APP        // Function application
} ExprType;

// Lambda calculus expression structure
typedef struct Expr {
    ExprType type;
    char *var;            // Variable name (used for VAR and LAMBDA types)
    struct Expr *body;    // Function body (used for LAMBDA type)
    struct Expr *left;    // Left side of application (used for APP type)
    struct Expr *right;   // Right side of application (used for APP type)
} Expr;

// Create a variable expression
Expr *create_var(const char *var) {
    Expr *expr = (Expr *)malloc(sizeof(Expr));
    expr->type = VAR;
    expr->var = strdup(var);
    expr->body = NULL;
    expr->left = NULL;
    expr->right = NULL;
    return expr;
}

// Create a lambda abstraction
Expr *create_lambda(const char *var, Expr *body) {
    Expr *expr = (Expr *)malloc(sizeof(Expr));
    expr->type = LAMBDA;
    expr->var = strdup(var);
    expr->body = body;
    expr->left = NULL;
    expr->right = NULL;
    return expr;
}

// Create a function application
Expr *create_app(Expr *left, Expr *right) {
    Expr *expr = (Expr *)malloc(sizeof(Expr));
    expr->type = APP;
    expr->var = NULL;
    expr->body = NULL;
    expr->left = left;
    expr->right = right;
    return expr;
}

// Print lambda expression (for debugging)
void print_expr(Expr *expr) {
    if (!expr) return;
    switch (expr->type) {
        case VAR:
            printf("%s", expr->var);
            break;
        case LAMBDA:
            printf("(λ%s. ", expr->var);
            print_expr(expr->body);
            printf(")");
            break;
        case APP:
            printf("(");
            print_expr(expr->left);
            printf(" ");
            print_expr(expr->right);
            printf(")");
            break;
    }
}

// Free the memory of a lambda expression
void free_expr(Expr *expr) {
    if (!expr) return;
    if (expr->var) free(expr->var);
    free_expr(expr->body);
    free_expr(expr->left);
    free_expr(expr->right);
    free(expr);
}

// Example usage
int main() {
    // Create an example lambda expression: (λx. x x)
    Expr *var_x = create_var("x");
    Expr *lambda = create_lambda("x", create_app(var_x, var_x));

    // Print the expression
    printf("Lambda expression: ");
    print_expr(lambda);
    printf("\n");

    // Free memory
    free_expr(lambda);

    return 0;
}

