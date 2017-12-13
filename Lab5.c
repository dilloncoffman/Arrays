#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define INIT_SIZE 4
#define EPSILON 0.01

/*
 Struct for a vector of double.  It contains a pointer
 to a vector of double, an integer for allocated length
 of the vector and and integer for the count of double
 inserted.
 */
typedef struct
{
    double *vector;
    int count;
    int length;
} Vector;

// Prototypes
Vector create_vector(int length);
Vector empty_vector();
int insert(Vector *vec, double dbl);
void print_vec(Vector vec);
void delete_vector(Vector *vec);
Vector copy(Vector vec);
Vector copy_range(Vector vec, int from, int to);
void clear_vector(Vector *vec);
void zeros(Vector *vec);
void fill(Vector *vec, double dbl);
Vector read_from_file(char *filename);
int write_to_file(Vector vec, char *filename);
Vector get_from_con();
void add_from_con(Vector *vec);
void swap(Vector *vec, int i, int j);
void sort(Vector *vec);
void reverse(Vector *vec);
int dbl_equals(double d1, double d2);
int search(Vector vec, double dbl);
double sum(Vector vec);
double avg(Vector vec);
double var(Vector vec);
double stdv(Vector vec);
Vector add(Vector v1, Vector v2);
Vector sub(Vector v1, Vector v2);
Vector mul(Vector v1, Vector v2);
Vector divv(Vector v1, Vector v2);
double dot(Vector v1, Vector v2);
int equals(Vector v1, Vector v2);

// Main
int main()
{
    
    // Test create, insert and print
    printf("Test create, insert and print\n");
    Vector v1 = create_vector(2);
    insert(&v1, 1.0);
    insert(&v1, 2.0);
    insert(&v1, 3.0);
    insert(&v1, 4.0);
    insert(&v1, 5.0);
    print_vec(v1);
    printf("\n");
    
    // Test copy and copy range
    printf("Test copy and copy range\n");
    Vector v2 = copy(v1);
    print_vec(v2);
    Vector v3 = copy_range(v1, 1, 3);
    print_vec(v3);
    printf("\n");
    
    // Test zeros and fill
    printf("Test zeros and fill\n");
    zeros(&v3);
    print_vec(v3);
    fill(&v2, 1.0);
    print_vec(v2);
    printf("\n");
    
    // Test read and write
    printf("Test read and write\n");
    Vector v4 = read_from_file("/Users/dilloncoffman/Desktop/Fall_2017/Lab5/array_in.txt");
    print_vec(v4);
    write_to_file(v1, "/Users/dilloncoffman/Desktop/Fall_2017/Lab5/array_out.txt");
    printf("\n");
    
    // Test get from con and add from con
    Vector v5 = get_from_con();
    print_vec(v5);
    add_from_con(&v5);
    print_vec(v5);
    printf("\n");
    
    // Test swap, sort, reverse and search
    printf("Test swap, sort, reverse and search\n");
    swap(&v1, 0, 4);
    swap(&v1, 1, 3);
    print_vec(v1);
    sort(&v1);
    print_vec(v1);
    reverse(&v4);
    print_vec(v4);
    int i = search(v4, 6.0);
    printf("Found at %d\n\n", i);
    
    // Test sum, avg, var and stdv
    printf("Test sum, avg, var and stdv\n");
    printf("Sum = %f\n", sum(v4));
    printf("Avg = %f\n", avg(v4));
    printf("Var = %f\n", var(v4));
    printf("Stdv = %f\n\n", stdv(v4));
    
    // Test add, sub, mul, divv, dot and equals
    printf("Test add, sub, mul, divv, dot and equals\n");
    Vector v6 = add(v1, v4);
    print_vec(v6);
    Vector v7 = sub(v6, v4);
    print_vec(v7);
    Vector v8 = mul(v1, v4);
    print_vec(v8);
    Vector v9 = divv(v8, v4);
    print_vec(v9);
    
    double dbl = dot(v1, v4);
    printf("Dot = %f\n", dbl);
    
    i = equals(v1, v4);
    printf("Equals = %d\n", i);
    
    i = equals(v1, v1);
    printf("Equals = %d\n", i);
    
    // Free memory
    delete_vector(&v1);
    delete_vector(&v2);
    delete_vector(&v3);
    delete_vector(&v4);
    delete_vector(&v5);
    delete_vector(&v6);
    delete_vector(&v7);
    delete_vector(&v8);
    delete_vector(&v9);
    
    return 0;
}

/*
 
 Single vector functions
 
 */

/*
 Function to create a vector of double.  It accepts the
 integer length of the vector to be created and returns
 a Vector struct containing the length of the allocated
 vector, the count (initialized to zero) of doubles
 inserted, and the allocated vector.
 */
Vector create_vector(int length)
{
    Vector vec;
    vec.vector = (double *)malloc(sizeof(double) * length);
    if (vec.vector == NULL)
    { //check if vector exists
        empty_vector();
    }
    vec.count = 0;
    vec.length = length;
    return vec;
}

/*
 Create an empty vector with vector pointer set to NULL,
 length set to zero and count set to zero.  This is used
 when something fails during the creation of a Vector or
 other functions that return a Vector.
 */
Vector empty_vector()
{
    Vector vec;
    vec.vector = NULL;
    vec.count = 0;
    vec.length = 0;
    return vec;
}

/*
 Inserts a double into a vector of double.  If the
 vector is full (i.e. count == length), the length of
 the vector should be doubled and the data from the old
 vector should be copied and the old vector freed.  If
 the length is zero, use the defined initial size.
 You can use malloc, which requires you to manually copy
 and free the old vector or try realloc.
 */
int insert(Vector *vec, double dbl)
{
    if (vec->length == 0)
    { //get length of vector before inserting
        vec->length = INIT_SIZE;
    }
    //vec->vector = (double*)malloc(sizeof(double)*vec->length);
    if (vec->count == vec->length)
    { //if count equal to length
        vec->length *= 2;
        double *temp = (double *)malloc(sizeof(double) * vec->length); //reallocate double the space
        if (temp == NULL)
        {
            printf("Error reallocating!\n");
            exit(0); //error reallocating vector
        }
        int i = 0;
        for (i = 0; i < vec->length; i++)
        {
            temp[i] = vec->vector[i]; //put dbl to be inserted into reallocated array, should copy over already allocated values
        }
        double *temp2 = vec->vector; //temp copy address into other pointer
        vec->vector = temp;
        free(temp2); //free old vector;
    }
    vec->vector[vec->count] = dbl; //if there's enough space, just insert dbl
    (vec->count)++;
    return 1;
}

/*
 Prints the count, length and elements of a vector to
 screen.
 */
void print_vec(Vector vec)
{
    if (vec.vector == NULL)
    {
        printf("No vector to print!\n");
        exit(5);
    }
    int i = 0;
    printf("length =  %d\n", vec.length);
    printf("count = %d\n", vec.count);
    for (i = 0; i < vec.count; i++)
    {
        printf("%.2f ", vec.vector[i]);
    }
    printf("\n\n");
}

/*
 Frees the memory allocated for the vector, and sets
 the count and length to zero.  Make sure not the free
 an empty (NULL) vector.
 */
void delete_vector(Vector *vec)
{
    if (vec->vector == NULL)
    {                                   //if no vector to free
        printf("No vector to free!\n"); //throw message, exit program
        exit(1);
    }
    vec->count = 0; //set count and length to zero
    vec->length = 0;
    free(vec->vector); //free vector
}

/*
 Creates a new vector with equal count, length and
 elements and returns the vector.
 */
Vector copy(Vector vec)
{
    if (vec.vector == NULL)
    {                                   //if no vector to copy
        printf("No vector to copy!\n"); //throw message
        exit(6);
    }
    Vector newVec;
    newVec.vector = (double *)malloc(sizeof(double) * vec.length);
    for (int i = 0; i < vec.length; i++)
    { //copy over elements
        newVec.vector[i] = vec.vector[i];
    }
    newVec.count = vec.count;
    newVec.length = vec.length;
    return newVec;
}

/*
 Copies a range from a vector to a new vector and
 returns the new vector.  The count and length should
 be equal to the number of elements copied.  Remember
 to check for invalid operations:
 to less than from
 to less than zero
 from greater than or equal to count
 */
Vector copy_range(Vector vec, int from, int to)
{
    if (vec.vector == NULL)
    {                                            //if no vector top copy range of
        printf("No vector to copy range of!\n"); //throw message
        exit(5);                                 //exit program
    }
    int i = 0;
    Vector newVec;
    newVec.length = (to - from) + 1;
    newVec.count = (to - from) + 1;
    newVec.vector = (double *)malloc(sizeof(double) * newVec.length);
    if (newVec.vector == NULL)
    {
        printf("Error allocating space for new vector.\n");
        exit(5);
    }
    if (to < from || to < 0)
    {
        printf("Invalid range!\n");
        exit(3);
    }
    if (from >= vec.count)
    {
        printf("Invalid range!\n");
        exit(3);
    }
    for (i = 0; i <= to; i++)
    {
        newVec.vector[i] = vec.vector[from];
        from++; //advance position of original vector to be copied into new vector
    }
    return newVec;
}

/*
 Writes zeros to the elements of a vector and sets
 the count to zero.
 */
void clear_vector(Vector *vec)
{
    int i = 0;
    for (i = 0; i < vec->length; i++)
    {
        vec->vector[i] = 0; //sets all elements of vector = 0
    }
    vec->count = 0;
}

/*
 Writes zeros to a vector's elements.
 */
void zeros(Vector *vec)
{
    int i = 0;
    for (i = 0; i < vec->length; i++)
    {
        vec->vector[i] = 0; //sets all elements of vector = 0
    }
}

/*
 Fills a vector's elements with the value in dbl.
 */
void fill(Vector *vec, double dbl)
{
    int i = 0;
    for (i = 0; i < vec->length; i++)
    {
        vec->vector[i] = dbl; //fills all elements of vector with specified dbl value
    }
}

/*
 Reads a vector from a file with one double on
 each line in the file and returns the vector.
 Remember that scanf returns a -1 after reading
 the last element in a file.
 */
Vector read_from_file(char *filename)
{
    Vector vec = create_vector(0); //vector to put read in elements in, create_vector() checks if vector was created, no need to check here then
    FILE *myFile;
    myFile = fopen(filename, "r");
    if (!myFile)
    { //if file does not exist, throw error
        fputs("Error: File not found.\n", stderr);
        exit(4);
    }
    int i = 0;
    int j = 0;
    double dbl;
    while (vec.vector[j] != EOF)
    {
        i = fscanf(myFile, "%lf", &dbl);
        if (i != 1)
        {
            break;
        }
        insert(&vec, dbl);
        j++;
    }
    //subtract null off
    printf("\n");
    return vec;
}

/*
 Writes a vector's elements to a file.
 */
int write_to_file(Vector vec, char *filename)
{
    FILE *myFile;
    myFile = fopen(filename, "w");
    if (myFile == NULL)
    { //if no file, throw error, exit program
        printf("Error: File not opened.\n");
        exit(4);
    }
    if (vec.vector == NULL)
    {                                            //if no vector to write to file
        printf("No vector to write to file!\n"); //throw message, exit program
        exit(2);
    }
    if (vec.length == 0 || vec.count == 0)
    { //if there are no elements in the vector
        printf("Error: Empty vector! No elements to write to file.\n");
        exit(5);
    }
    int i = 0;
    for (i = 0; i < vec.count; i++)
    { //for each element in vec, write that element to file
        fprintf(myFile, "%.2lf ", vec.vector[i]);
    }
    
    return 1; //successfully written vector to file
}

/*
 Creates a new vector and gets the elements from
 keyboard input.  Accepts and inserts doubles into
 the vector until Enter is pressed (without any other
 chars).  Remember that scanf will not work unless a
 required data type is entered.  You should use gets
 and check for '\0', when Enter only is pressed.
 */
Vector get_from_con()
{
    Vector vec = create_vector(0); //checks if vector was created, creates vector
    double dbl = 0.0;
    char *str = NULL;
    str = (char *)malloc(sizeof(char) * 2); //carve out area in memory to start storing values in str using gets()
    int i = 0;                              //counter for str values
    //get elements from user, insert them into newly defined vector
    while (1)
    {
        printf("Enter a double (press enter to stop): ");
        gets(&str[i]);
        if (str[i] == '\0')
        {
            return vec;
        }
        if ((str[i] > 47) && (str[i] < 58))
        {                                  //as long as value entered is a number..
            sscanf(&str[i], "%lf", &dbl);  //convert str[i] to double value
            str = (char *)realloc(str, i); //realloc size of str as i increments, making it dynamic
            insert(&vec, dbl);             //insert dbl value into created vector
            i++;                           //increment i
        }
        else
        { //if value entered is other char, continue with loop, prompting user to enter number
            continue;
        }
    }
}

/*
 Adds elements to a vector and gets the elements from
 keyboard input.  Accepts and inserts doubles into
 the vector until Enter is pressed (without any other
 chars).  Remember that scanf will not work unless a
 required data type is entered.  You should use gets
 and check for '\0', when Enter only is pressed.
 //  */
void add_from_con(Vector *vec)
{
    if (vec->vector == NULL)
    { //make sure there is vector to add values to
        printf("No vector to add values to!\n");
        exit(3);
    }
    double dbl = 0.0;
    char *str = NULL;
    str = (char *)malloc(sizeof(char) * vec->count); //carve out area in memory to start storing values in str using gets()
    int i = 0;
    while (i < vec->count)
    {
        i++; //sets i to appropriate index of current vector (the end) to be added to
    }
    //get elements from user, insert them into newly defined vector
    while (1)
    {
        printf("Enter a double (press enter to stop): ");
        gets(&str[i]);
        if (str[i] == '\0')
        {
            free(str); //free the string, is good practice in general before program exits
            return;    //stop adding values to current vector
        }
        if ((str[i] > 47) && (str[i] < 58))
        {                                  //as long as value entered is a number..
            sscanf(&str[i], "%lf", &dbl);  //convert str[i] to double value
            str = (char *)realloc(str, i); //realloc size of str as i increments, making it dynamic
            insert(vec, dbl);              //insert dbl value into created vector
            i++;                           //increment i
        }
        else
        { //if value entered is other char, continue with loop, prompting user to enter number
            continue;
        }
    }
}

/*
 Swaps two elements in a vector.
 */
void swap(Vector *vec, int i, int j)
{
    if (vec->vector == NULL)
    {
        printf("No vector to perform a swap on!\n");
        exit(3);
    }
    double temp;
    temp = vec->vector[i];
    vec->vector[i] = vec->vector[j];
    vec->vector[j] = temp;
}

/*
 Sorts a vector.  Can use selection or bubble
 sort.
 */
void sort(Vector *vec)
{
    if (vec->vector == NULL)
    {
        printf("No vector to perform a sort on!\n");
        exit(3);
    }
    int i, j;
    for (i = 0; i < (vec->length - 1); i++)
    {
        int position = i;
        for (j = i + 1; j < vec->length - 3; j++)
        { //
            if (vec->vector[position] > vec->vector[j])
            {
                position = j;
            }
        }
        if (position != i)
        {
            swap(vec, position, i);
        }
    }
}

/*
 Reverses the elements of a vector.
 */
void reverse(Vector *vec)
{
    if (vec->vector == NULL)
    {
        printf("No vector to perform a reversal of elements on!\n");
        exit(3);
    }
    int j = 0, i = 0;
    j = vec->count - 1;
    
    while (i < j)
    {
        double temp = vec->vector[i];
        vec->vector[i] = vec->vector[j];
        vec->vector[j] = temp;
        i++;
        j--;
    }
}

/*
 Checks if two doubles are equal given the defined
 EPSILON.  Remember that there should be a threshold
 for which two do floating point values are considered
 equal due to computation of arithmetic operations.
 */
int dbl_equals(double d1, double d2)
{
    double difference = 0.0;
    if (d1 > d2)
    {
        difference = d1 - d2;
        if (difference <= EPSILON)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    if (d2 > d1)
    {
        difference = d2 - d1;
        if (difference <= EPSILON)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

/*
 Perform a binary search on a sorted vector and return
 the index of the element if found and -1 if not found.
 */
int search(Vector vec, double dbl)
{
    //sort(&vec); //sort the vector to be searched
    
    int first = 0;
    int last = vec.count;
    int middle = (first + last) / 2; //assign middle to middle element
    
    while (first <= last) //while first is less than or equal to last
    {
        if (vec.vector[middle] < dbl) //if middle is less than the element being serached for
            first = middle + 1; //make first index 1 plus middle value
        else if (vec.vector[middle] == dbl) //if middle is equal to elemtn being searched for
        {
            return middle + 1; //return that index which the element is at
            break;
        }
        else //otherwise set last equal to middle minus one
            last = middle - 1;
        
        middle = (first + last) / 2; //update middle value to be in the middle of newly assigned first and last elements
    }
    if (first > last) //if everything was searched and element wasn't found
        printf("%.2lf was not found within the sorted vector.\n", dbl); //throw message saying element wasn't found
    return -1; //something went wrong
}

/*
 Calculate and return the sum of the elements in
 a vector.
 */
double sum(Vector vec)
{
    int i = 0;
    double sum = 0;
    for (i = 0; i < vec.count; i++)
    {
        sum += vec.vector[i]; //add all elements in vector together into sum
    }
    return sum;
}

/*
 Calculate and return the average of the elements in
 a vector.
 */
double avg(Vector vec)
{
    int i;
    double sum = 0.0, avg = 0.0;
    for (i = 0; i < vec.count; i++)
    {
        sum += vec.vector[i];
        avg = (sum) / (vec.count);
    }
    return avg;
}

/*
 Calculate and return the variance of the elements in
 a vector.
 */
double var(Vector vec)
{
    double mean = avg(vec);
    double sum = 0;
    for (int i = 0; i < vec.count; i++)
    {
        sum += ((vec.vector[i] - mean) * (vec.vector[i] - mean));
    }
    return (sum) / (vec.count);
}

/*
 Calculate and return the standard deviation of the
 elements in a vector.
 */
double stdv(Vector vec)
{
    int i;
    double sum = 0.0, var = 0.0;
    for (i = 0; i < vec.count; i++)
    {
        sum = sum + pow((vec.vector[i] - avg(vec)), 2);
    }
    return var = sqrt(sum / vec.count);
}

/*
 
 Multiple vector functions
 
 */

/*
 Perform an element by element addition of two vectors,
 where v3[i] = v1[i] + v2[i] and return the resulting
 vector.
 */
Vector add(Vector v1, Vector v2)
{
    Vector v3;
    v3.count = v1.count;
    v3.length = v1.length;
    v3.vector = (double *)malloc(sizeof(double) * v1.length);
    for (int i = 0; i < v1.length; i++)
    {
        v3.vector[i] = (v2.vector[i] + v1.vector[i]);
    }
    return v3;
}

/*
 Perform an element by element subtraction of one vector from
 another, where v3[i] = v1[i] - v2[i] and return the resulting
 vector.
 */
Vector sub(Vector v1, Vector v2)
{
    Vector v3;
    v3.count = v1.count;
    v3.length = v1.length;
    v3.vector = (double *)malloc(sizeof(double) * v1.length);
    for (int i = 0; i < v2.length; i++)
    {
        v3.vector[i] = (v1.vector[i] - v2.vector[i]);
    }
    return v3;
}

/*
 Perform an element by element multiplication of two vectors,
 where v3[i] = v1[i] * v2[i] and return the resulting
 vector.
 */
Vector mul(Vector v1, Vector v2)
{
    Vector v3;
    v3.count = v1.count;
    v3.length = v1.length;
    v3.vector = (double *)malloc(sizeof(double) * v1.length);
    for (int i = 0; i < v1.length; i++)
    {
        v3.vector[i] = (v2.vector[i] * v1.vector[i]);
    }
    return v3;
}

/*
 Perform an element by element division of two vectors,
 where v3[i] = v1[i] / v2[i] and return the resulting
 vector.
 */
Vector divv(Vector v1, Vector v2)
{
    Vector v3;
    v3.count = v1.count;
    v3.length = v1.length;
    v3.vector = (double *)malloc(sizeof(double) * v1.length);
    for (int i = 0; i < v1.length; i++)
    {
        v3.vector[i] = ((v1.vector[i]) / (v2.vector[i]));
    }
    return v3;
}

/*
 Perform the calculation of the dot product of two vectors,
 where dbl += v1[i] * v2[i] and return the resulting
 double.
 */
double dot(Vector v1, Vector v2)
{
    double result = 0.0;
    for (int i = 0; i < v1.count; i++)
    {
        result += v1.vector[i] * v2.vector[i];
    }
    return result;
}

/*
 Perform an element by element comparison of two vectors.
 If for every i, v1[i] == v2[i], and the count is equal
 return 1, otherwise zero.
 */
int equals(Vector v1, Vector v2)
{
    sort(&v1); //sort both arrays
    sort(&v2);
    if (v1.count != v2.count)
    { //if count isn't equal return 0
        return 0;
    }
    for (int i = 0; i < v1.length; i++)
        if (v1.vector[i] != v2.vector[i])
            return 0;
    return 1;
}
