# **_Simple Compiler_**

## **Description**

**_Compiler created for a C-like language in CS 442 Course_** <br/>
This project was created for a Computer Science course project at the University of Wiconsin - La Crosse. The course, called Structures of Compilers (CS 442) taught students the basics of the compilation process that takes place each time computer programs are executed. The compiler that was built in this class at UWL can process a simple C-like language and convert it to MIPS assembly code. The MIPS assembly code can be run in simulators such as Mars and Spim. A Mars4_5.jar file, which opens a simulator that can run the generated assembly code, is provided in this repository.

There are two main folders in this project repository: The "MARS-for-Testing-Compiler" folder and the "Compiler" folder. The "MARS-for-Testing-Compiler" contains the Mars4_5.jar file, which can be opened when double-clicked. The Mars simulator, where assembly code files can be run in, is opened as part of the Mars4_5.jar file.

The "Compiler" folder contains four subfolders: The "Entire-Compiler" folder, the "Homework3" folder, the "IO-Manager" folder, and the "Symbol-Table" folder. Though all folders can be accessed and modified, the folder that you should open and utilize if you wish to run the project is the "Entire-Compiler" folder. This "Entire-Compiler" folder contains pieces of information from all of the other folders listed in the project. An important file within the "Entire-Compiler" folder is a Makefile. The Makefile can be used on certain systems, such as macOS, to run the Compiler project and produce output. There is also a file called `compiler-testinfo.txt` contained within the **Notes** folder, which is inside of the **Entire-Compiler** folder. The file contains specific instructions on running the compiler. 

You can modify which files in the C-like language, contained within the "Tests" folder (which is contained inside of the "Entire-Compiler" project), are run by the compiler project. After you run the Makfile within the "Entire-Compiler" folder or manually enter the commands into the terminal, you can enter the following command:

```
$ ./compiler ./Tests/in1.txt listing.lst asmCode.asm
```
The **in1.txt** file name can be changed to any of the file names within the "Tests" folder of the project. For more details on running the project, see [Running / Viewing the Project](#running--viewing-the-project).

The other folders that were listed above can also be explored if you wish to gain a better understanding of how this particular compiler functions. Each folder contains a part of the compiler while, as mentioned above, the "Entire-Compiler" folder contains the compiler in its entirety. If you ever wish to make modifications to this project or want to use it to design your own compiler, you can use the code provided in this repository as a starting point. Enjoy exploring the project. 

## **Important Note:**
***
**If you are viewing this folder, I assume that you were granted special access given that this repository is private and restricted for the sake of academic integrity. Please do not share this code with students enrolled at the University of Wisconsin - La Crosse. If you are a student at UWL, please do not view or use this code.**
***


###### Picture of the Compiler Grammar (yacc/bison file)
<img width="774" alt="Screen Shot 2022-04-28 at 2 01 59 AM" src="https://user-images.githubusercontent.com/57727121/165695957-ebd3a3d0-20a0-4518-bfaa-781d0547f300.png">


**Resources for Project:**

- Lex (Windows): https://www.geeksforgeeks.org/how-to-install-flex-on-windows/
- Yacc (Windows): https://yacc.software.informer.com/0.4/
- Flex (Mac): https://ports.macports.org/port/flex/
- Bison (Mac): http://robupcraft.com/install-bison-mac/
- C
- Mars IDE (attached in project)
- W3Schools: https://www.w3schools.com/
- Stack Overflow: https://stackoverflow.com/

<p>&nbsp;</p>

## **Other Notes:**

Depending on the type of operating system that you run on your computer, you may need to download different technologies in order to properly run the compiler. For example, the majority of Windows users will need to use Lex and Yacc to run the project. 

## Windows:
Windows users can run commands to install lex and yacc. See the link for more details: https://stackoverflow.com/questions/5456011/how-to-compile-lex-yacc-files-on-windows.

On macOS systems, lex and yacc are referred to as flex and bison.

## Mac:
Mac user should already have flex and bison as part of their operating system. As a Mac user, you can check to see if flex and bison are installed by typing two commands in your command line prompt. To check if flex is installed, type: `flex --version`. To check if bison is installed, type: `bison --version`. Make sure you have the most up-to-date versions of these tools. If you do not already have flex and bison, see the information **below**.

Users with macOS will want to use Flex and Bison. To install lex/flex and yacc/bison, you can also run commands on your terminal to obtain these technologies. For macOS install lex/flex by running `brew install flex`. 

To install yacc/bison on macOS, run `brew install bison`. If you do not have homebrew, which makes the "brew" command possible, install homebrew here: https://www.digitalocean.com/community/tutorials/how-to-install-and-use-homebrew-on-macos.

<p>&nbsp;</p>

# Running / Viewing the Project

## Command Line and Mars Simulator
1. First, make sure that you have your terminal open. Information about your terminal can be found here:<br/>
   -Mac: https://support.apple.com/guide/terminal/open-or-quit-terminal-apd5265185d-f365-44cb-8b09-71a064a42125/mac<br/>
   -Windows: https://docs.microsoft.com/en-us/windows/terminal/
2. Next, make sure that you have Java installed in your system. Go to your settings/system preferences (do this on your computer and not in your terminal) and search for Java in your system. If you do not already have Java installed, follow the link below. You will be brought to a website for downloading Java. The website will give you the option to download Java for Mac or Windows. <br/>
   -Java Download: https://java.com/en/download/help/download_options.html
3. On this repository page, go to the "Code" button and click the "Download Zip" option.
4. Go to your "Downloads" section on your computer and place the zip file in a folder/location other than "Downloads".
5. Double click on the zip file to open or "unzip" it so you can access the file contents.
6. In your opened terminal, navigate to the location where you opened the downloaded zip file and make sure you are inside of the "Compiler-Project-master" folder. (If you are unsure of command line commands, see the resources provided bellow.)<br/>
   -Linux and Max: http://mally.stanford.edu/~sr/computing/basic-unix.html<br/>
   -Windows: https://blogs.umass.edu/Techbytes/2014/11/14/file-navigation-with-windows-command-prompt/
7. Inside the "Compiler-Project-master" folder on your terminal, navigate into the "Mars-for-Testing-Compiler" folder, and double click the `Mars_5.jar` to open the Mars simulator. 
8. After you have completed step 7, navigate to the "Entire-Compiler" folder within the "Compiler-Project-master" folder: **Compiler-Project-master &rarr;Entire-Compiler**. 
9. Run the **Makefile** within the "Entire-Compiler" folder: `make`. If you are a Windows user, you may have to do additional research on how to run makefiles on your computer.
10. After the Makefile command has been run, type the following command into your terminal:     
```
$ ./compiler ./Tests/in1.txt listing.lst asmCode.asm
```   
11. After the compiler finishes running, go back to the Mars simulator (the simulator that you should have opened by double-clicking on the "Mars4_5.jar") that should be open on your computer.
12. Inside of the Mars simulator, click on **File** and then on **Open**. Navigate to the "Compiler-Project-master" folder, and then to the "Entire-Compiler" folder. Open the **asmCode.asm** file in the Mars simulator.
13. In the Mars simulator, after you have opened the assembly file that was generated by the compiler, click on "Run" and then "Assemble".
14. Click on the green "Play" icon in the simulator to run the MIPS code in the **asmCode.asm** file. 
15. If you want to run different files, change the name of the "in1.txt" file in the run command above to any other test file name listed within the **Tests** and **finalTests** folders of the Compiler project.


<p>&nbsp;</p>

# Completed Parts of the Compiler Project
## PART 1: Integer Expressions

- [x] Integers, Literals, Variagles
- [x] Variables must be declared before they are used (all declarations before other statements)
- [x] Assignment Statement
- [x] Arithmetic Operators
- [x] +, - (binary subtraction), *, /, %, - (unary minus)
- [x] ^ (exponentiation) You can assume the exponent is an expression whose value >= 0
- [x] Relational Operators: <, <=, ==, >=, >, !=
- [x] Boolean Operators: !, &&, ||
- [x] All operators except ^ use the precedence and associativity rules of C. The "^" is right associative and has lower precedence than unary minus and higher precedence than all the other operators. Parentheses are used to change order of operations.
      
## PART 2: Integer I/O

- [x] read(comma delimited list of variables): read(x, y, z)
- [x] print(comma delimited list of expressions) --> MORE BELOW:
- [x] print results on the current line
- [x] print a space between values
- [x] a newline is not printed
- [x] print(2*x, x^3*(z*w), abc/xyz, c)
- [x] printLines(expression) --> MORE BELOW:
- [x] print expression number of newlines    
- [x] printLines(2)
- [x] printSpaces(expression) --> MORE BELOW:
- [x] printSpaces(3*n)
- [x] printString(“Literal String”)
- [x] printString(“Enter one integer”);

## PART 3: Control Structures

- [x] if statements including optional else
- [x] while loops
- [x] for loops (extra feature that I implemented)
- [x] Use C syntax and the C definition of true (non-zero) and false (zero).

## PART 4: Arrays

- [x] Single Dimension Arrays
- [x] Size of the array is declared at compile time
- [x] Use C syntax
- [x] Subscripts must be able to use constants and expressions. For example: nums[2*i] = z * nums[j - 3 * k]

## PART 5: 2D Arrays

- [x] Size of the array is declared at compile time
- [x] Use C syntax
- [x] Subscripts must be able to use constants and expressions.

## PART 6: Functions (incomplete)

- [ ] void and int functions
- [ ] Parameters: Pass by value for integers
- [ ] Parameters: Pass by reference for arrays
- [ ] Local Variables
- [ ] Recursion
- [ ] Pass by reference for integers (bonus 5 points)
- [ ] Pass by value for arrays (bonus 5 points)

<p>&nbsp;</p>

**Functionalities:**

- The compiler can recognize a C-like language, which is specified through the lex/flex and yacc/bison files, and convert it into MIPS assembly code. The MIPS assembly code that was generated as a result of the compilation process can be executed in the Mars Simulator that is attached in this project.
- **Note:** There is also a basic interpreter contained within a folder named "Homework3". This can also be run on the termninal. However, the interpreter does not generate any assembly code. Rather it displays the output to the terminal.
- The folders "IO-Manager" and "Symbol-Table" are also pieces of the compiler project. However, there is no need to attempt running the code contained within these folders. Copies of the IO-Manager file and the Symbol-Table file are included in the **"Entire-Compiler"** folder. This folder contains the main compiler project that can be run on the terminal.

<p>&nbsp;</p>

**Future Add-Ons:**

- The "Functions" component of the project was never fully completed due to time limits. In the future, the function implementation will be developed to completely satisfy the project requirements.
- If given time in future developments of this project, a graphical user interface (GUI) may be created to allow users to run the compiler with more ease. 
- Optimizations will be added to improve the runtime of the compilation process. Memory management will be also be updated in order to improve the machine performance.

<p>&nbsp;</p>

**Important Assumptions for Project:**

- This compiler was not designed for any commerical use, but rather for academic purposes. The machine is more complex compared to the vast majority of projects I have created, but can only be applied to the specified C-like language provided in the course by the instructor.
- This project was created with the intent to satisfy a number of requriements, which were listed above as [Completed Parts of the Compiler](#completed-parts-of-the-compiler). Optimization was not a large focus of this project. Therefore, the compiler is inefficient when executing certain processes.
- There is a significant amount of functionality in this compiler. Given time constraints, certian files are not organizes as efficiently as they could be. However, this is a minor organizational issue that may be resolved in the future.

<p>&nbsp;</p>

**_@Author: Andrew Krause_** <br/>
*LinkedIn:* https://www.linkedin.com/in/andrew-krause-b6aa21179/ <br/>
*Portfolio:* https://andrewkrause.dev/ <br/>
*Instagram:* https://www.instagram.com/aek.krause/ <br/>
*Facebook:* https://www.facebook.com/andrew.krause.35325 <br/>
