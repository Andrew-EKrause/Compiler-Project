===================================================
            COMPILER PROJECT CHECKLIST
                  Andrew Krause
===================================================


PART 1: Integer Expressions (30 Points)
===================================================
[ x ] Integers, Literals, Variagles
[ x ] Variables must be declared before they are used (all declarations before other statements)
[ x ] Assignment Statement
[ x ] Arithmetic Operators
[ x ] +, - (binary subtraction), *, /, %, - (unary minus)
[ x ] ^ (exponentiation) You can assume the exponent is an expression whose value >= 0
[ x ] Relational Operators: <, <=, ==, >=, >, !=
[ x ] Boolean Operators: !, &&, ||
[ x ] All operators except ^ use the precedence and associativity rules of C. ^ is right 
      associative and has lower precedence than unary minus and higher precedence than all 
      the other operators. Parentheses are used to change order of operations.
[ x ] ANYTHING ELSE??? --> MAYBE LOOK AT THE CASE WHERE YOU HAVE -(5 + 1). SEE IF THAT WORKS!!!


PART 2: Integer I/O (30 Points) 
===================================================
[ x ] read(comma delimited list of variables): read(x, y, z)
[ x ] print(comma delimited list of expressions) --> MORE BELOW:
[ x ] print results on the current line
[ x ] print a space between values
[ x ] a newline is not printed
[ x ] print(2*x, x^3*(z*w), abc/xyz, c)
[ x ] printLines(expression) --> MORE BELOW:
[ x ] print expression number of newlines    
[ x ] printLines(2)
[ x ] printSpaces(expression) --> MORE BELOW:
[ x ] printSpaces(3*n)
[ x ] printString(“Literal String”)
[ x ] printString(“Enter one integer”);
[ x ] ANYTHING ELSE???


PART 3: Control Structures (30 Points) 
===================================================
[ x ] if statements including optional else
[ x ] while loops
[ x ] for loops --> I THINK THESE ARE OPTIONAL???
[ x ] Use C syntax and the C definition of true (non-zero) and false (zero). // --> CHECK THIS!!!
[ x ] ANYTHING ELSE???


PART 4: Arrays (20 Points)
===================================================
[ x ] Single Dimension Arrays
[ x ] Size of the array is declared at compile time
[ x ] Use C syntax
[ x ] Subscripts must be able to use constants and expressions. 
      For example nums[2*i] = z * nums[j-3*k
[ x ] ANYTHING ELSE???


// =================================================== \\
// -->  AT THIS POINT YOU WILL PASS THE PROJECT!!! <-- \\
// =================================================== \\


PART 5: 2D Arrays (30 Points)
===================================================
[ x ] Size of the array is declared at compile time
[ x ] Use C syntax
[ x ] Subscripts must be able to use constants and expressions.
[ x ] ANYTHING ELSE???


PART 6: Functions (40 Points)
===================================================
[   ] void and int functions
[   ] Parameters: Pass by value for integers
[   ] Parameters: Pass by reference for arrays
[   ] Local Variables
[   ] Recursion
[   ] Pass by reference for integers (bonus 5 points)
[   ] Pass by value for arrays (bonus 5 points)
[   ] ANYTHING ELSE???
