#include <iostream>

#include <string>

#include <fstream>

#include <stack>

using namespace std;

int skip_pos(string expr) ///need work
{
  int pos = 0, pos1 = 0;
  stack < char > s;

  while (isspace(expr[pos1])) {
    pos1++;
  }

  pos = pos1;

  for (int i = pos1; i < expr.length(); i++) {
    pos++;
    if (expr[i] == '(') {
      // Push the element in the stack 
      s.push(expr[i]);
      continue;
    }

    // IF current current character is not opening 
    // bracket, then it must be closing. So stack 
    // cannot be empty at this point. 

    if (expr[i] == ')') {
      if (!s.empty())
        s.pop();
    }

    if (s.empty())
      return pos;

  }
  return 0;
}

int main() {
  stack < char > st;
  int Statements = 0;
  int Comments = 0;
  int Blank_Lines = 0;
  int Macro_def = 0;
  int Variables = 0;
  int Fun_Def = 0;
  int Fun_Dec = 0;
  int line_no = 0; //Total number of line......
  int semicount = 0; //keep track of semicolumn
  fstream newfile;
  newfile.open("input.txt", ios:: in );
  string str;
  int i = 0, p, k, j;
  int length; //length of string
  int spaceCount;
  bool commentsOn = 0; //variable to check multiline commenting started or not
  bool function_possibility = 0; //variable to check possibility function declaration,variable declaration,function defination
  bool open_bracket = 0; //variable to check open braket is present 
  bool close_bracket = 0; //variable to check close bracket is present
  bool variable_possibility = 0;
  bool macro_on = 0; //variable to check possibility of variable declaration
  bool function_on = 0;
  bool got_a_var = 0;
  bool printscanf_on = 0;
  bool string_on = 0;
  string mystr = "";

  // newfile.open("parthtime1",ios::in); //open a file to perform read operation using file object

  if (newfile.is_open()) { //checking whether the file is open/*

    while (getline(newfile, str)) {
      macro_on = 0;
      line_no++;
      Statements++;
      length = str.length();
      semicount = 0;
      for (j = 0; j < length; ++j) {
        if (str[j] == ';') {
          semicount++;
        }
      }
      if (semicount > 1) {
        Statements = Statements + semicount - 1;

      }

      for (j = 0; j < length;) {

        if (str[j] == '"') {
          p = j;
          for (k = p + 1; str[k] != '"'; ++k) {
            if (str[k] == ';')
              Statements--;
            // if(k>=length)
            // break;
          }
          j = k + 1;
        } else {
          j = j + 1;
        }

      }

      spaceCount = 0;
      while (isspace(str[spaceCount])) //////counting spaces
        spaceCount++;

      if (str[spaceCount] == '\0') //empty lines or lines containg only white spaces considered as empty line.
      {
        Blank_Lines++;

        continue;
      }

      for (i = spaceCount; i < length; i++) //iterating from space count to end of the string
      {

        mystr = "";
        if (string_on == 1) {

          if (str.find(';', p + 1) != std::string::npos) {
            j = str.find(';', p + 1);
          } else {
            p = -1;
            break;
          }

          i = j + 1;
          string_on = 0;
          p = 0;
          j = 0;
        } else if (printscanf_on == 1) ////printf end in the order ");
        {
          if (p != -1) {
            p = str.find('"', p);
            p = str.find('"', p + 1);
          }
          if (k != -1) {
            if (str.find(')', p + 1) != std::string::npos) {
              k = str.find(')', p + 1);
            } else {
              p = -1;
              break;
            }
          }

          if (str.find(';', k + 1) != std::string::npos) {
            j = str.find(';', k + 1);
          } else {
            k = -1;
            p = -1;
            break;
          }

          i = j + 1;
          printscanf_on = 0;
          p = 0;
          j = 0;
          k = 0;

        } else if (commentsOn == 1) //To check multi line comments are on
        {
          while (str[i] != '*') {
            i++; //Verfied                          //Keeps track of the characters of the string
            if (str[i] == '\0')
              break;
          }
          if (str[i] == '*' && str[i + 1] == '/') //Comments finished
          {
            i++; //Verified
            i++;
            commentsOn = 0;
          }
        } else if (variable_possibility == 1) {
          while (isspace(str[i]) || str[i] == '*')
            i++;

          if (str[i] == '\0')
            break;
          if (got_a_var == 0) {
            if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))) {
              variable_possibility = 0;
              function_possibility = 0; //check for printf......
              cout << "error in line number  " << line_no << "   '" << str << "'" << endl;
              cout << "starting from next line" << endl;
              break;
            } else {
              got_a_var = 1;
            }

          }

          while (str[i] != ';') {
            if(str[i]==',')
                Variables++;
            if (str[i] == '(') {
              function_possibility = 1;
              variable_possibility = 0;
              got_a_var = 0;
              break;
            }
            if (str[i] == '\'') {
              if (str.find('\'', i + 1) != std::string::npos) //case      char i=';';
                i = str.find('\'', i + 1);
            }
            if (str[i] == '"') //assume char aa[30]="ytyr;;;;;;;;;;;;yrr";
            {
              if (str.find('"', i + 1) != std::string::npos)
                i = str.find('"', i + 1);
            }
            if (str[i] == '\0') ///line ends but C allows .....int a=5 \n ;
            {
              break;
            }

            i++;
          }
          if (str[i] == ';') {
            Variables++;
            got_a_var = 0;
            variable_possibility = 0;
            function_possibility = 0; ///////////function_possibility=0
            i++;
          }
        } ///need to work here ...it should be if not else if

        if (function_on == 1) //cant define or declare function inside another function..
          function_possibility = 0;

        if (function_possibility == 1) //to check possibility function declaration,variable declaration,function defination
        {
          variable_possibility = 0;

          if (open_bracket == 0) //if no open bracket detected already
          {
            while (str[i] != '(') {
              
              if (str[i] == ';') {
                function_possibility = 0;
                // cout<<"error in line "<<line_no<<" "<<endl;
                break;
              }
              if (str[i] == '\0') {
                break;
              }
              if ((str[i] == '{') || (str[i] == ')')) //assume struct node {  },assumr if(a==b)
              {
                function_possibility = 0;
                break;
              }

              i++;

            }
            if (str[i] == '(') {
              open_bracket = 1;
            }
          }

          if (close_bracket == 1) {
            while (str[i] != ';') {
              if (str[i] == '\0') {
                break;
              }
              if (str[i] == '{') {
                open_bracket = 0;
                close_bracket = 0;
                function_possibility = 0;
                Fun_Def++;
                function_on = 1; ////////*********
                st.push(str[i]);
                i++;
                break;
              }
              if (str[i] == ')') {
                open_bracket = 0;
                close_bracket = 0;
                function_possibility = 0;
                break;
              }

              i++;

            }

            if (str[i] == ';') {
              open_bracket = 0;
              close_bracket = 0;
              function_possibility = 0;
              Fun_Dec++;
              i++;

            }
          }

          if (open_bracket == 1) {
            while (str[i] != ')') {
              if (str[i] == ';') {
                cout << "error in line " << line_no << endl;
                open_bracket = 0; //open bracket =0
                function_possibility = 0;
                break;
                // i=length;//hello
              }
              if (str[i] == '\0') {
                break;
              }
              i++;

            }

            if (str[i] == ')') {
              close_bracket = 1;

            }
          }
          //now checking for Fun_Def_or Fun_Dec

        }

        if ((commentsOn == 0) && (function_possibility == 0) && (variable_possibility == 0) && (string_on == 0) && (printscanf_on == 0)) {
          switch (str[i]) {
          case '#':
            {
              Macro_def++;
              macro_on = 1;
              break;
            }
          case '{':
            {
              st.push(str[i]);
              break;
            }
          case '}':
            {
              if (!st.empty())
                st.pop();
              if (st.empty()) {
                function_on = 0;
              }
              break;
            }
          case '"':
            {
              cout << "   i    " << i << "    " << line_no << endl;
              p = str.find('"', i + 1);
              if (p == -1)
                p = i;
              string_on = 1;
              break;
            }
          case '/':
            {
              if ((str[i + 1]) == '/') {
                Comments++;
                i = length;
              } else if (str[i + 1] == '*') {
                Comments++;
                commentsOn = 1;
                i++;

              } //need work..
              else {
                cout << "unidentified character at line " << line_no << " " << endl;
              }

              break;
            }
          default:
            {
              if (macro_on == 0)
                if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
                  while (isalnum(str[i])) {
                    mystr = mystr + str[i];
                    i++; //Verified
                  }
                  i--;
                  if ((mystr == "if") || (mystr == "while")) {
                    j = length - i - 1;
                    i = i + skip_pos(str.substr(i + 1, j));
                  } else if ((mystr == "printf") || (mystr == "scanf")) {
                    printscanf_on = 1;
                    p = i;
                    j = 0;
                    k = 0;
                  } else if ((mystr == "int") || (mystr == "float") || (mystr == "char") || (mystr == "long") || (mystr == "short") || (mystr == "double") || (mystr == "void") || (mystr == "extern") || (mystr == "static") || (mystr == "auto") || (mystr == "const") || (mystr == "signed") || (mystr == "unsigned")) {
                    i++;
                    variable_possibility = 1;

                  } else { //these c keywords never appear in variable declaration,function declaration and function definition

                    if ((mystr != "break") && (mystr != "case") && (mystr != "continue") && (mystr != "default") && (mystr != "do") && (mystr != "else") && (mystr != "enum") && (mystr != "for") && (mystr != "register") && (mystr != "return") && (mystr != "sizeof") && (mystr != "struct") && (mystr != "switch") && (mystr != "typedef") && (mystr != "union") && (mystr != "volatile")) {
                      function_possibility = 1; //function_possibility.

                    }
                  }
                  ///if line line contain for then 2 semi_column(or statements) should remove
                  if (mystr == "for") {
                    Statements = Statements - 1;
                  }
                }
              break;
            }
          }
        }
      }
    }
    newfile.close(); //close the file object.
  }

  cout << "1)Source code statements\t: " << Statements << endl;
  cout << "2)Comments\t: " << Comments << endl;
  cout << "3)Blank Lines\t: " << Blank_Lines << endl;
  cout << "4)Macro Definitions\t: " << Macro_def << endl;
  cout << "5)Variable Declarations\t: " << Variables << endl;
  cout << "6)Function Declarations\t: " << Fun_Dec << endl;
  cout << "7)Function Definitions\t: " << Fun_Def << endl;
}
