#include <iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<unordered_map>
#include<algorithm>
using namespace std;

struct line //store the info of each line
{
    string wholeString;

    string label;
    string mnemonic;
    string operand;

    int location;
    string myOPCODE;

    string nixbpe;

    int byteSize;

};

struct reg
{
    string name;
    int num;
};

struct symbolNode //store the info of the symbol and its address
{
    string symbol;
    int address;
};

int hexToDec(string s)//string to int
{
    int total = 0;
    int mul = 1;
    int len = strlen(s.c_str());
    for(int i = len-1; i >= 0; i--)//reverse order to get each digit(from least digit)
    {
        int t;
        if(s[i] >= '0' && s[i] <= '9')//number
        {
            t = s[i] - '0';
        }
        else//alphabet
        {
            t = (s[i]-'A'+10);
        }
        total += t*mul;
        mul*=16;
    }
    return total;
}

int dec_atoi(string s)//string to int
{
    int total = 0;
    int mul = 1;
    int len = strlen(s.c_str());
    for(int i = len-1; i >= 0; i--)//reverse order to get each digit(from least digit)
    {
        total += (s[i] - '0')*mul;
        mul*=10;
    }
    return total;
}

string decToHex(int num)//turn the decimal to hexadecimal(int to string)
{
    string s = "";
    while(num > 0)
    {
        int t = num % 16;
        if(t <= 9)//0~9 turn to number
        {
            s += (char)('0'+t);
        }
        else//10~15turn to alphabet
        {
            s += (char)('A'+(t-10));
        }
        num /= 16;
    }
    string rev_s = "";
    int len = strlen(s.c_str());
    for(int i = len-1; i >= 0; i--)//the reverse order is the correct answer
    {
        rev_s += s[i];
    }
    return rev_s;
}

string decToHex_four(int num)//turn the decimal to hexadecimal(int to string)(four digit,purpose of creating 4 digit location)
{
    string s = "";
    while(num > 0)
    {
        int t = num % 16;
        if(t <= 9)//0~9 turn to number
        {
            s += (char)('0'+t);
        }
        else//10~15turn to alphabet
        {
            s += (char)('A'+(t-10));
        }
        num /= 16;
    }
    string rev_s = "";
    int len = strlen(s.c_str());
    if(len  < 4)
    {
        for(int i = 0; i < (4-len); i++)//the reverse order is the correct answer
        {
            rev_s += "0";
        }
    }
    for(int i = len-1; i >= 0; i--)//the reverse order is the correct answer
    {
        rev_s += s[i];
    }
    return rev_s;
}

string decToHex_three(int num)//turn the decimal to hexadecimal(int to string)(four digit,purpose of creating 3 digit opcode)
{
    if(num >= 0)
    {
        string s = "";
        while(num > 0)
        {
            int t = num % 16;
            if(t <= 9)//0~9 turn to number
            {
                s += (char)('0'+t);
            }
            else//10~15turn to alphabet
            {
                s += (char)('A'+(t-10));
            }
            num /= 16;
        }
        string rev_s = "";
        int len = strlen(s.c_str());
        if(len  < 3)
        {
            for(int i = 0; i < (3-len); i++)//the reverse order is the correct answer
            {
                rev_s += "0";
            }
        }
        for(int i = len-1; i >= 0; i--)//the reverse order is the correct answer
        {
            rev_s += s[i];
        }
        return rev_s;
    }
    else //if the number is negative , use right shift &1 to get the bits
    {

        string s = "";
        for(int i = 0; i < 12; i++)
        {
            s += (char)('0'+(num&1));
            num = num >> 1;
        }
        reverse(s.begin(), s.end());

        string hex_string = "";

        int d1 = 0;
        if(s[0] == '1')
        {
            d1 += 8;
        }
        if(s[1] == '1')
        {
            d1 += 4;
        }
        if(s[2] == '1')
        {
            d1 += 2;
        }
        if(s[3] == '1')
        {
            d1 += 1;
        }


        int d2 = 0;
        if(s[4] == '1')
        {
            d2 += 8;
        }
        if(s[5] == '1')
        {
            d2 += 4;
        }
        if(s[6] == '1')
        {
            d2 += 2;
        }
        if(s[7] == '1')
        {
            d2 += 1;
        }

        int d3 = 0;
        if(s[8] == '1')
        {
            d3 += 8;
        }
        if(s[9] == '1')
        {
            d3 += 4;
        }
        if(s[10] == '1')
        {
            d3 += 2;
        }
        if(s[11] == '1')
        {
            d3 += 1;
        }

        if(d1 <= 9)//0~9 turn to number
        {
            hex_string += (char)('0'+d1);
        }
        else//10~15turn to alphabet
        {
            hex_string += (char)('A'+(d1-10));
        }

        if(d2 <= 9)//0~9 turn to number
        {
            hex_string += (char)('0'+d2);
        }
        else//10~15turn to alphabet
        {
            hex_string += (char)('A'+(d2-10));
        }

        if(d3 <= 9)//0~9 turn to number
        {
            hex_string += (char)('0'+d3);
        }
        else//10~15turn to alphabet
        {
            hex_string += (char)('A'+(d3-10));
        }

        return hex_string;
    }

}

string decToHex_five(int num)//turn the decimal to hexadecimal(int to string)(four digit,purpose of creating 5 digits opcode)
{
    string s = "";
    while(num > 0)
    {
        int t = num % 16;
        if(t <= 9)//0~9 turn to number
        {
            s += (char)('0'+t);
        }
        else//10~15turn to alphabet
        {
            s += (char)('A'+(t-10));
        }
        num /= 16;
    }
    string rev_s = "";
    int len = strlen(s.c_str());
    if(len  < 5)
    {
        for(int i = 0; i < (5-len); i++)//the reverse order is the correct answer
        {
            rev_s += "0";
        }
    }
    for(int i = len-1; i >= 0; i--)//the reverse order is the correct answer
    {
        rev_s += s[i];
    }
    return rev_s;
}

int main()
{
    unordered_map<string,string> opTable;
    unordered_map<string,int> symTable;

    int symbolCount = 0;
    symbolNode symbolTable[1000];//set the maximum symbol to 1000
    int lineCount = 0;
    line lineTable[1000];//set the maximum line to 1000

    reg registerTable[9];//register table

    registerTable[0].name = "A";
    registerTable[0].num = 0;

    registerTable[1].name = "X";
    registerTable[1].num = 1;

    registerTable[2].name = "L";
    registerTable[2].num = 2;

    registerTable[3].name = "B";
    registerTable[3].num = 3;

    registerTable[4].name = "S";
    registerTable[4].num = 4;

    registerTable[5].name = "T";
    registerTable[5].num = 5;

    registerTable[6].name = "F";
    registerTable[6].num = 6;

    registerTable[7].name = "PC";
    registerTable[7].num = 8;

    registerTable[8].name = "SW";
    registerTable[8].num = 9;

    int baseValue = 0;

    fstream inputFile;
    inputFile.open("SICXEsource.txt",ios::in); //read the SICXEsource.txt

    fstream opcodeFile;
    opcodeFile.open("opcode.txt",ios::in); //read the opcode.txt

    string s;
    string codeNum;
    while(opcodeFile >> s)//put the opcode to opTable
    {
        opcodeFile >> codeNum;
        opTable[s] = codeNum;
    }
    opcodeFile.close();

    //==================================pass_1==================================
    getline(inputFile,s); // get first line

    line firstLine;
    firstLine.wholeString = s;
    unsigned int index = 0;//point the char from the first line
    firstLine.myOPCODE = "";
    firstLine.label = "";
    while(true)//construct the label name till meet tab
    {
        if(s[index] == ' ')//skip space
        {
            index++;
            continue;
        }
        if(s[index] == '\t')
        {
            index++;
            break;
        }
        firstLine.label += s[index];
        index++;
    }

    firstLine.mnemonic = "";
    while(true)//construct the mnemonic name till meet tab
    {
        if(s[index] == ' ')//skip space
        {
            index++;
            continue;
        }
        if(s[index] == '\t')
        {
            index++;
            break;
        }
        firstLine.mnemonic += s[index];
        index++;
    }

    firstLine.operand = "";
    while(index < strlen(s.c_str()))//construct the operand till the end
    {
        if(s[index] == ' ')
        {
            index++;
            continue;
        }
        firstLine.operand += s[index];
        index++;
    }

    firstLine.location = hexToDec(firstLine.operand); //the start location is the operand itself

    int pc = firstLine.location; //set the program counter

    while(getline(inputFile,s))//get other lines
    {
        line temp;
        temp.wholeString = s;
        temp.location = pc;//set the location to pc
        unsigned int i = 0;
        if(s[0] != '\t')//have label(the first character is not tab)
        {
            temp.label = "";
            while(true)
            {
                if(s[i] == ' ')//skip space
                {
                    i++;
                    continue;
                }
                if(s[i] == '\t')//construct the label name till meet tab
                {
                    i++;
                    break;
                }
                temp.label += s[i];
                i++;
            }

            symbolNode newSymbol; //create new symbol object
            newSymbol.symbol = temp.label;
            newSymbol.address = pc;

            symbolTable[symbolCount] = newSymbol; //insert the new symbol to symbol table(this one is for the output)
            symTable[newSymbol.symbol] = newSymbol.address; //insert the new symbol to symbol table(the one i really use,using hashmap)
            symbolCount++;
        }
        else
        {
            temp.label = "";
            i++;
        }

        temp.mnemonic = "";
        while(i < strlen(s.c_str()))//construct the mnemonic name till meet tab
        {
            if(s[i] == ' ')//skip space
            {
                i++;
                continue;
            }
            if(s[i] == '\t')
            {
                i++;
                break;
            }
            temp.mnemonic += s[i];
            i++;
        }

        temp.operand = "";
        while(i < strlen(s.c_str()))//construct the operand till the end
        {
            if(s[i] == ' ')
            {
                i++;
                continue;
            }
            temp.operand += s[i];
            i++;
        }

        //add the program counter
        if(temp.mnemonic == "BASE")
        {
            //pc won't add , just skip
        }
        else if(temp.mnemonic == "WORD")
        {
            pc += 3;
        }
        else if(temp.mnemonic == "RESW")
        {
            pc += 3*(dec_atoi(temp.operand));
        }
        else if(temp.mnemonic == "RESB")
        {
            pc += dec_atoi(temp.operand);
        }
        else if(temp.mnemonic == "BYTE")
        {
            if((temp.operand)[0] == 'C')
            {
                pc += strlen((temp.operand).c_str()) - 3;//calculate how many character in the operand
            }
            else//X' ' , one byte
            {
                pc += 1;
            }
        }
        else//normal instruction
        {
            if((temp.mnemonic)[0] == '+')//format_4
            {
                pc += 4;
                temp.byteSize = 4;
            }
            else
            {
                //to check whether its format2 or format3
                unsigned int operandLen = strlen(temp.operand.c_str());//to check if comma exist in operand
                string s1 = "";//for the string left of comma
                string s2 = "";//for the string right of comma
                bool haveComma = false;
                unsigned int j = 0;
                for( ; j < operandLen; j++)
                {
                    if((temp.operand)[j] == '@' || (temp.operand)[j] == '#')//do not put in s1
                    {
                        continue;
                    }

                    if((temp.operand)[j] == ',')
                    {
                        haveComma = true;
                        j++;
                        break;
                    }
                    else
                    {
                        s1 += (temp.operand)[j];
                    }
                }
                if(haveComma == true)//2 register or index addressing
                {
                    for( ; j < operandLen; j++)//construct another string s2
                    {
                        s2 += (temp.operand)[j];
                    }
                    bool isReg_1 = false;
                    for(int k = 0; k < 9; k++)
                    {
                        if(s1 == registerTable[k].name)
                        {
                            isReg_1 = true;
                            break;
                        }
                    }

                    bool isReg_2 = false;
                    for(int k = 0; k < 9; k++)
                    {
                        if(s2 == registerTable[k].name)
                        {
                            isReg_2 = true;
                            break;
                        }
                    }

                    if(isReg_1 == true && isReg_2 == true)//if two operands are all register
                    {
                        pc += 2;
                        temp.byteSize = 2;
                    }
                    else//index addressing -> ???,x
                    {
                        pc += 3;
                        temp.byteSize = 3;
                    }
                }
                else//one operand
                {
                    bool isReg = false;
                    for(int k = 0; k < 9; k++)
                    {
                        if(s1 == registerTable[k].name)
                        {
                            isReg = true;
                            break;
                        }
                    }

                    if(isReg == true)//if the operand is register
                    {
                        pc += 2;
                        temp.byteSize = 2;
                    }
                    else//normal instruction(including no operand)
                    {
                        pc += 3;
                        temp.byteSize = 3;
                    }
                }

            }
        }

        lineTable[lineCount] = temp;
        lineCount++;

    }
    //write the locationAndSource.txt
    fstream locationAndSource;
    locationAndSource.open("pass1_locationAndSource.txt",ios::out);
    locationAndSource << "Loc\t" << "Source statement" << endl;
    locationAndSource << decToHex_four(firstLine.location) << "\t" << firstLine.wholeString << endl;
    for(int i = 0; i < lineCount-1; i++)
    {
        if(lineTable[i].mnemonic == "BASE")//base don't output location
        {
            locationAndSource << "\t" << lineTable[i].wholeString << endl;
        }
        else
        {
            locationAndSource << decToHex_four(lineTable[i].location) << "\t" << lineTable[i].wholeString << endl;
        }

    }
    locationAndSource << "\t" << lineTable[lineCount-1].wholeString << endl;
    locationAndSource.close();
    cout << "Pass 1 : " << endl << endl;
    cout << "write the location of each source code to pass1_locationAndSource.txt!" << endl << endl;

    //write the symbolTable.txt
    fstream symbolTableFile;
    symbolTableFile.open("pass1_symbolTable.txt",ios::out);
    symbolTableFile << "Name\t" << "Address" << endl;
    for(int i = 0; i < symbolCount; i++)
    {
        symbolTableFile << symbolTable[i].symbol << "\t" << decToHex_four(symbolTable[i].address) << endl;
    }
    symbolTableFile.close();
    cout << "write the symbol table to pass1_symbolTable.txt!" << endl << endl;
    //==================================pass_1==================================


    //==================================pass_2==================================
    for(int i = 0; i < lineCount-1; i++)
    {
        if(lineTable[i].mnemonic == "BASE")//set the value of base
        {
            baseValue = symTable[lineTable[i].operand];
        }
        else if(lineTable[i].mnemonic == "RESW" || lineTable[i].mnemonic == "RESB")
        {
            lineTable[i].myOPCODE = "";
            continue;
        }
        else
        {
            if(lineTable[i].mnemonic == "WORD")
            {
                string opcode = "";
                string s1 = decToHex(dec_atoi(lineTable[i].operand));
                for(unsigned int j = 0; j < (6-strlen(s1.c_str())); j++)//fill 0 to length 6
                {
                    opcode += "0";
                }
                opcode += s1;
                lineTable[i].myOPCODE = opcode;
            }
            else if(lineTable[i].mnemonic == "BYTE")
            {
                if((lineTable[i].operand)[0] == 'C')//C''
                {
                    string opcode = "";
                    for(unsigned int j = 2; j < (strlen((lineTable[i].operand).c_str())-1); j++)//concatenate each character
                    {
                        string t = decToHex((int)((lineTable[i].operand)[j]));
                        if(strlen(t.c_str()) == 1)
                        {
                            opcode += "0";
                        }
                        opcode += t;
                    }
                    lineTable[i].myOPCODE = opcode;
                }
                else//X''
                {
                    int len = strlen((lineTable[i].operand).c_str());
                    string opcode = "";
                    for(int j = 2; j < len-1; j++)
                    {
                        opcode += (lineTable[i].operand)[j];
                    }
                    lineTable[i].myOPCODE = opcode;
                }
            }
            else//normal instruction
            {
                if((lineTable[i].mnemonic)[0] == '+')//format_4
                {
                    if(lineTable[i].operand == "")//no operand , fill 5 zero
                    {
                        string realMneminic = "";
                        for(unsigned int j = 1; j < strlen((lineTable[i].mnemonic).c_str()); j++)
                        {
                            realMneminic += (lineTable[i].mnemonic)[j];
                        }

                        lineTable[i].nixbpe = "110001";
                        string opcode = decToHex(hexToDec(opTable[realMneminic])+3);//use optable to get opcode
                        if(strlen(opcode.c_str()) == 1)
                        {
                            opcode = "0" + opcode;
                        }
                        opcode += "1";//xbpe
                        opcode += "00000";
                        lineTable[i].myOPCODE = opcode;
                    }
                    else//have operand
                    {

                        if((lineTable[i].operand)[0] == '@')//xbp = 0
                        {
                            string realMneminic = "";
                            for(unsigned int j = 1; j < strlen((lineTable[i].mnemonic).c_str()); j++)//get mnemonic without +
                            {
                                realMneminic += (lineTable[i].mnemonic)[j];
                            }

                            string opcode;
                            lineTable[i].nixbpe = "100001";
                            opcode = decToHex(hexToDec(opTable[realMneminic])+2);
                            if(strlen(opcode.c_str()) == 1)
                            {
                                opcode = "0" + opcode;
                            }

                            opcode += "1";//xbpe

                            string realOperand = "";

                            for(unsigned int j = 1; j < strlen((lineTable[i].operand).c_str()); j++)//get operand without @
                            {
                                realOperand += (lineTable[i].operand)[j];

                            }

                            opcode += decToHex_five(symTable[realOperand]);

                            lineTable[i].myOPCODE = opcode;


                        }
                        else if((lineTable[i].operand)[0] == '#')//xbp = 0
                        {
                            string realMneminic = "";
                            for(unsigned int j = 1; j < strlen((lineTable[i].mnemonic).c_str()); j++)//get mnemonic without +
                            {
                                realMneminic += (lineTable[i].mnemonic)[j];
                            }

                            string opcode;
                            lineTable[i].nixbpe = "010001";
                            opcode = decToHex(hexToDec(opTable[realMneminic])+1);
                            if(strlen(opcode.c_str()) == 1)
                            {
                                opcode = "0" + opcode;
                            }
                            opcode += "1";//xbpe

                            string realOperand = "";
                            bool allNumber = true;
                            for(unsigned int j = 1; j < strlen((lineTable[i].operand).c_str()); j++)//get operand without # , and check if the operand is number
                            {
                                realOperand += (lineTable[i].operand)[j];
                                if(!((lineTable[i].operand)[j] >= '0' && (lineTable[i].operand)[j] <= '9'))
                                {
                                    allNumber = false;
                                }
                            }

                            if(allNumber == true)//operand is number
                            {
                                string myNum = decToHex(dec_atoi(realOperand));
                                for(unsigned int k = 0; k < (5-strlen(myNum.c_str())); k++)//fill 0 to length 5
                                {
                                    opcode += "0";
                                }
                                opcode += myNum;
                            }
                            else//operand is symbol
                            {
                                opcode += decToHex_five(symTable[realOperand]);
                            }

                            lineTable[i].myOPCODE = opcode;

                        }
                        else
                        {
                            //check if it's index addressing
                            int x = -1;
                            for(unsigned int j = 0; j < strlen((lineTable[i].operand).c_str()); j++)//if x !+ -1 , we find cooma ,means that it's index addressing
                            {
                                if((lineTable[i].operand)[j] == ',')//indexed addressing
                                {
                                    x = j;
                                    break;
                                }
                            }

                            if(x == -1)//normal addressing
                            {
                                string realMneminic = "";
                                for(unsigned int j = 1; j < strlen((lineTable[i].mnemonic).c_str()); j++)//get mnemonic without +
                                {
                                    realMneminic += (lineTable[i].mnemonic)[j];
                                }

                                string opcode;
                                lineTable[i].nixbpe = "110001";
                                opcode = decToHex(hexToDec(opTable[realMneminic])+3);
                                if(strlen(opcode.c_str()) == 1)
                                {
                                    opcode = "0" + opcode;
                                }

                                opcode += "1";//xbpe

                                opcode += decToHex_five(symTable[lineTable[i].operand]);

                                lineTable[i].myOPCODE = opcode;



                            }
                            else//indexed addressing
                            {
                                string realMneminic = "";
                                for(unsigned int j = 1; j < strlen((lineTable[i].mnemonic).c_str()); j++)//get mnemonic without +
                                {
                                    realMneminic += (lineTable[i].mnemonic)[j];
                                }

                                string opcode;
                                lineTable[i].nixbpe = "111001";

                                opcode = decToHex(hexToDec(opTable[realMneminic])+3);
                                if(strlen(opcode.c_str()) == 1)
                                {
                                    opcode = "0" + opcode;
                                }

                                opcode += "9";//xbpe

                                string realOperand = "";//to get the real operand without ',X'
                                for(int j = 0; j < x; j++)
                                {
                                    realOperand += (lineTable[i].operand)[j];
                                }

                                opcode += decToHex_five(symTable[realOperand]);

                                lineTable[i].myOPCODE = opcode;

                            }


                        }
                    }
                }
                else//format2 or format3
                {

                    if(lineTable[i].operand == "")//no operand , fill with 3 zeros
                    {
                        lineTable[i].nixbpe = "110000";
                        string opcode = decToHex(hexToDec(opTable[lineTable[i].mnemonic])+3);//use optable to get opcode
                        if(strlen(opcode.c_str()) == 1)
                        {
                            opcode = "0" + opcode;
                        }
                        opcode += "0";
                        opcode += "000";
                        lineTable[i].myOPCODE = opcode;

                    }
                    else//have operand
                    {
                        if((lineTable[i].operand)[0] == '@')//format3
                        {
                            string opcode;
                            string realOperand = "";
                            for(unsigned int j = 1; j < strlen((lineTable[i].operand).c_str()); j++)//get the operand without @
                            {
                                realOperand += (lineTable[i].operand)[j];
                            }
                            int TA = symTable[realOperand];
                            int PC = lineTable[i+1].location;

                            if(TA-PC >= -2048 && TA-PC <= 2047)//pc relative
                            {
                                lineTable[i].nixbpe = "100010";
                                opcode = decToHex(hexToDec(opTable[lineTable[i].mnemonic])+2);
                                if(strlen(opcode.c_str()) == 1)
                                {
                                    opcode = "0" + opcode;
                                }
                                opcode += "2";//xbpe
                                opcode += decToHex_three(TA-PC);
                                lineTable[i].myOPCODE = opcode;

                            }
                            else//base relative
                            {
                                lineTable[i].nixbpe = "100100";
                                opcode = decToHex(hexToDec(opTable[lineTable[i].mnemonic])+2);
                                if(strlen(opcode.c_str()) == 1)
                                {
                                    opcode = "0" + opcode;
                                }
                                opcode += "4";//xbpe

                                opcode += decToHex_three(TA-baseValue);
                                lineTable[i].myOPCODE = opcode;

                            }
                        }
                        else if((lineTable[i].operand)[0] == '#')//format3
                        {
                            string opcode;
                            string realOperand = "";
                            bool allNumber = true;
                            for(unsigned int j = 1; j < strlen((lineTable[i].operand).c_str()); j++)//get the operand without # , and check if the operand is number
                            {
                                realOperand += (lineTable[i].operand)[j];
                                if(!((lineTable[i].operand)[j] >= '0' && (lineTable[i].operand)[j] <= '9'))
                                {
                                    allNumber = false;
                                }
                            }

                            if(allNumber == true)//the operand is number
                            {
                                lineTable[i].nixbpe = "010000";
                                opcode = decToHex(hexToDec(opTable[lineTable[i].mnemonic])+1);
                                if(strlen(opcode.c_str()) == 1)
                                {
                                    opcode = "0" + opcode;
                                }
                                opcode += "0";//xbpe

                                string myNum = decToHex(dec_atoi(realOperand));
                                for(unsigned int k = 0; k < (3-strlen(myNum.c_str())); k++)//fill 0 to length 3
                                {
                                    opcode += "0";
                                }
                                opcode += myNum;

                                lineTable[i].myOPCODE = opcode;

                            }
                            else//the operand is symbol
                            {
                                int TA = symTable[realOperand];
                                int PC = lineTable[i+1].location;

                                if(TA-PC >= -2048 && TA-PC <= 2047)//pc relative
                                {
                                    lineTable[i].nixbpe = "010010";
                                    opcode = decToHex(hexToDec(opTable[lineTable[i].mnemonic])+1);
                                    if(strlen(opcode.c_str()) == 1)
                                    {
                                        opcode = "0" + opcode;
                                    }
                                    opcode += "2";//xbpe
                                    opcode += decToHex_three(TA-PC);
                                    lineTable[i].myOPCODE = opcode;

                                }
                                else//base relative
                                {
                                    lineTable[i].nixbpe = "010100";
                                    opcode = decToHex(hexToDec(opTable[lineTable[i].mnemonic])+1);
                                    if(strlen(opcode.c_str()) == 1)
                                    {
                                        opcode = "0" + opcode;
                                    }
                                    opcode += "4";//xbpe

                                    opcode += decToHex_three(TA-baseValue);
                                    lineTable[i].myOPCODE = opcode;

                                }
                            }



                        }
                        else//format3(normal or index addressing) or format2(1 or 2 Register)
                        {

                            unsigned int operandLen = strlen(lineTable[i].operand.c_str());
                            bool haveComma = false;
                            unsigned int j = 0;
                            string s1 = "";
                            string s2 = "";
                            for( ; j < operandLen; j++)//check if there is a comma, if comma exist , it could be format_3 index addressing or format_2
                            {
                                if((lineTable[i].operand)[j] == ',')
                                {
                                    haveComma = true;
                                    j++;
                                    break;
                                }
                                else
                                {
                                    s1 += (lineTable[i].operand)[j];
                                }
                            }
                            if(haveComma == true)//2 register or index addressing
                            {
                                for( ; j < operandLen; j++)//construct another string s2
                                {
                                    s2 += (lineTable[i].operand)[j];
                                }
                                bool isReg_1 = false;
                                for(int k = 0; k < 9; k++)
                                {
                                    if(s1 == registerTable[k].name)
                                    {
                                        isReg_1 = true;
                                        break;
                                    }
                                }

                                bool isReg_2 = false;
                                for(int k = 0; k < 9; k++)
                                {
                                    if(s2 == registerTable[k].name)
                                    {
                                        isReg_2 = true;
                                        break;
                                    }
                                }

                                if(isReg_1 == true && isReg_2 == true)//if two operand are all register, format_2
                                {
                                    string opcode;
                                    opcode = opTable[lineTable[i].mnemonic];
                                    for(int k = 0; k < 9; k++)
                                    {
                                        if(s1 == registerTable[k].name)
                                        {
                                            opcode += (char)('0' + registerTable[k].num);
                                            break;
                                        }
                                    }
                                    for(int k = 0; k < 9; k++)
                                    {
                                        if(s2 == registerTable[k].name)
                                        {
                                            opcode += (char)('0' + registerTable[k].num);
                                            break;
                                        }
                                    }
                                    lineTable[i].myOPCODE = opcode;

                                }
                                else//index addressing
                                {
                                    //real operand = s1

                                    string opcode;
                                    int TA = symTable[s1];
                                    int PC = lineTable[i+1].location;

                                    if(TA-PC >= -2048 && TA-PC <= 2047)//pc relative
                                    {
                                        lineTable[i].nixbpe = "111010";
                                        opcode = decToHex(hexToDec(opTable[lineTable[i].mnemonic])+3);
                                        if(strlen(opcode.c_str()) == 1)
                                        {
                                            opcode = "0" + opcode;
                                        }
                                        opcode += "A";//xbpe
                                        opcode += decToHex_three(TA-PC);
                                        lineTable[i].myOPCODE = opcode;


                                    }
                                    else//base relative
                                    {
                                        lineTable[i].nixbpe = "111100";
                                        opcode = decToHex(hexToDec(opTable[lineTable[i].mnemonic])+3);
                                        if(strlen(opcode.c_str()) == 1)
                                        {
                                            opcode = "0" + opcode;
                                        }
                                        opcode += "C";//xbpe

                                        opcode += decToHex_three(TA-baseValue);
                                        lineTable[i].myOPCODE = opcode;

                                    }

                                }
                            }
                            else//one operand
                            {
                                bool isReg = false;
                                for(int k = 0; k < 9; k++)
                                {
                                    if(lineTable[i].operand == registerTable[k].name)
                                    {
                                        isReg = true;
                                        break;
                                    }
                                }

                                if(isReg == true)//if the operand is register
                                {
                                    string opcode;
                                    opcode = opTable[lineTable[i].mnemonic];
                                    for(int k = 0; k < 9; k++)
                                    {
                                        if(lineTable[i].operand == registerTable[k].name)
                                        {
                                            opcode += (char)('0' + registerTable[k].num);
                                            break;
                                        }
                                    }
                                    opcode += "0";
                                    lineTable[i].myOPCODE = opcode;

                                }
                                else//normal instruction(PC or B)
                                {
                                    string opcode;
                                    int TA = symTable[lineTable[i].operand];
                                    int PC = lineTable[i+1].location;

                                    if(TA-PC >= -2048 && TA-PC <= 2047)//pc relative
                                    {
                                        lineTable[i].nixbpe = "110010";
                                        opcode = decToHex(hexToDec(opTable[lineTable[i].mnemonic])+3);
                                        if(strlen(opcode.c_str()) == 1)
                                        {
                                            opcode = "0" + opcode;
                                        }
                                        opcode += "2";//xbpe
                                        opcode += decToHex_three(TA-PC);
                                        lineTable[i].myOPCODE = opcode;

                                    }
                                    else//base relative
                                    {
                                        lineTable[i].nixbpe = "110100";
                                        opcode = decToHex(hexToDec(opTable[lineTable[i].mnemonic])+3);
                                        if(strlen(opcode.c_str()) == 1)
                                        {
                                            opcode = "0" + opcode;
                                        }
                                        opcode += "4";//xbpe

                                        opcode += decToHex_three(TA-baseValue);
                                        lineTable[i].myOPCODE = opcode;

                                    }
                                }
                            }

                        }

                    }


                }
            }

        }
    }

    cout << "Pass_2 : " << endl << endl;
    //write the source with location and objectcode to pass2_source_LocObj.txt
    fstream source_LocObj;
    source_LocObj.open("pass2_source_LocObj.txt",ios::out);
    source_LocObj << decToHex_four(firstLine.location) << "\t" << firstLine.wholeString << endl;
    for(int i = 0; i < lineCount-1; i++)
    {
        if(lineTable[i].mnemonic == "BASE")
        {
            source_LocObj << "\t" << lineTable[i].wholeString << endl;
        }
        else if(strlen(lineTable[i].operand.c_str()) >= 8)
        {
            source_LocObj << decToHex_four(lineTable[i].location) << "\t" << lineTable[i].wholeString << "\t" << lineTable[i].myOPCODE << endl;
        }
        else if(lineTable[i].operand == "")
        {
            source_LocObj << decToHex_four(lineTable[i].location) << "\t" << lineTable[i].wholeString << "\t\t\t" << lineTable[i].myOPCODE << endl;
        }
        else
        {
            source_LocObj << decToHex_four(lineTable[i].location) << "\t" << lineTable[i].wholeString << "\t\t" << lineTable[i].myOPCODE << endl;
        }
    }
    source_LocObj << "\t" << lineTable[lineCount-1].wholeString << endl;
    source_LocObj.close();
    cout << "write the source with location and objectcode to pass2_source_LocObj.txt!" << endl << endl;

    //write the text record to pass2_textRecord.txt
    fstream pass2_textRecord;
    pass2_textRecord.open("pass2_textRecord.txt",ios::out);
    //out format of first line
    pass2_textRecord << 'H';
    pass2_textRecord << firstLine.label;
    for(unsigned int i = 0; i < 6-strlen(firstLine.label.c_str()); i++)//fill space
    {
        pass2_textRecord << ' ';
    }
    pass2_textRecord << "00" << decToHex_four(firstLine.location) << "00" << decToHex_four(lineTable[lineCount-1].location - firstLine.location) << endl;

    for(int i = 0; i < lineCount-1; )
    {
        string opcodeBuffer = "";
        int recordLen = 0;
        bool first = true;
        int byteCount = 0;
        int startAddress;
        while(i < lineCount-1)
        {
            if(lineTable[i].mnemonic == "BASE")//meet BASE just skip
            {
                i++;
                continue;
            }
            if(lineTable[i].mnemonic == "RESW" || lineTable[i].mnemonic == "RESB")//meet RESW RESB to change line
            {
                while(i < lineCount-1 && (lineTable[i].mnemonic == "RESW" || lineTable[i].mnemonic == "RESB" || lineTable[i].mnemonic == "BASE"))
                {
                    i++;
                }
                break;
            }
            if(recordLen + strlen(lineTable[i].myOPCODE.c_str()) > 60)//above limit
            {
                break;
            }
            if(first == true)//we need to get the first line location to know the start address
            {
                startAddress = lineTable[i].location;
                first = false;
            }

            if(lineTable[i].mnemonic == "BYTE")
            {
                if((lineTable[i].operand)[0] == 'C')
                {
                    byteCount += strlen(lineTable[i].operand.c_str()) - 3;
                }
                else
                {
                    byteCount += 1;
                }
            }
            else
            {
                byteCount += lineTable[i].byteSize;
            }

            recordLen += strlen(lineTable[i].myOPCODE.c_str());
            opcodeBuffer += lineTable[i].myOPCODE;
            i++;
        }
        pass2_textRecord << "T00" << decToHex_four(startAddress);
        string lineLen = decToHex(byteCount);
        if(strlen(lineLen.c_str()) == 1)
        {
            pass2_textRecord << '0';
        }
        pass2_textRecord << lineLen;
        pass2_textRecord << opcodeBuffer;
        pass2_textRecord << endl;

    }

    for(int i = 0; i < lineCount-1; i++)//to get format 4 and write modification record
    {
        if((lineTable[i].mnemonic)[0] == '+')//format_4(format_4 can't use index addressing)
        {
            if(lineTable[i].operand != "")
            {
                if((lineTable[i].operand)[0] == '#')//to check if the operand is number
                {
                    bool allNumber = true;
                    for(unsigned int j = 1; j < strlen(lineTable[i].operand.c_str()); j++)
                    {
                        if(!((lineTable[i].operand)[j] >= '0' && (lineTable[i].operand)[j] <= '9'))
                        {
                            allNumber = false;
                        }
                    }
                    if(allNumber == false)//not number we need to modify
                    {
                        pass2_textRecord << 'M';
                        pass2_textRecord << "00" << decToHex_four(lineTable[i].location+1) << "05" << endl;
                    }
                }
                else
                {
                    pass2_textRecord << 'M';
                    pass2_textRecord << "00" << decToHex_four(lineTable[i].location+1) << "05" << endl;
                }
            }
            else
            {
                pass2_textRecord << 'M';
                pass2_textRecord << "00" << decToHex_four(lineTable[i].location+1) << "05" << endl;
            }
        }
    }

    pass2_textRecord << "E00" << decToHex_four(firstLine.location);
    pass2_textRecord.close();
    cout << "write the text record to pass2_textRecord.txt!" << endl << endl;

    //==================================pass_2==================================




}
