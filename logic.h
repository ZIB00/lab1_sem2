
typedef struct {
    size_t size;
    void (*input)(void* out);
    void (*print)(const void* in);
} TypeInfo;

typedef struct {
    int row;
    int column;
    TypeInfo* operation;
    void* data;
} Matrix;

void input_int(void* out);
void print_int(const void* in);
TypeInfo Operation_int = { sizeof(int), input_int, print_int };

void input_float(void* out);
void print_float(const void* in);
TypeInfo Operation_float = { sizeof(float), input_float, print_float };

Matrix* create_matrix(int r, int c, TypeInfo* operation);
void matrix_fill(Matrix* m);
void matrix_print(Matrix* m);
void matrix_del(Matrix* m);
void error_int(int *variable, int left_boarder, int right_boarder, char error_text[]);
void error_float(int *variable, int left_boarder, int right_boarder, char error_text[]);
int matrix_addition();
int matrix_multiplication();
int multiplication_by_a_scalar();
int adding_a_linear_combination();