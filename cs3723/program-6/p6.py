import sys
import re

#----------- Exception Handling -----------#
class FunctionError(Exception):
    def __init__(self, value):
        self.parameter = value

class PrefixSyntax(Exception):
    def __init__(self, value):
        self.parameter = value
#global variables here
global pos
pos = 0
inFile = open(sys.argv[1], 'r')
opperands = {'+','-','*','/','>','<',"and","or"}
#checks for errors in syntax
def checkForError(tokArr):
    pos = 0
    openParCnt = 0
    closeParCnt = 0
    opCnt = 0
    numCnt = 0
    for i in range(-1,len(tokArr)):
        if tokArr[i] in opperands:
            opCnt = opCnt + 1
        elif tokArr[i] is '(':
            openParCnt = openParCnt + 1
        elif tokArr[i] is ')':
            closeParCnt = closeParCnt + 1
        elif tokArr[i].isdigit():
            numCnt = numCnt + 1
        else:
            raise FunctionError("Function Error: Not an operator "+tokArr[i])

    if openParCnt is closeParCnt:
        raise PrefixSyntax("Prefix Syntax: Missing parentheses")
        
#evalutates commands
def evalOps(tokArr):
    global pos
    oper = str(tokArr[pos])
    pos = pos + 1
    val1 = prefixEval(tokArr)
    pos = pos + 1
    val2 = prefixEval(tokArr)
    if tokArr[pos+1].isdigit():
        raise FunctionError("Function Error: Too many digits for opperand")
    try:
        return eval(val1+' '+oper+' '+val2)
    except TypeError:
        raise FunctionError("Function Error: Wont Eval")
#runs prefix eval
def prefixEval(tokArr):
    global pos
    if pos == len(tokArr):
        raise FunctionError("Function Error: Incorrect Number of Operands")
        return None
    #checks for the parentheses
    if tokArr[pos] == '(':
        pos = pos + 1
    elif tokArr[pos] == ')':
        pos = pos + 1
        return prefixEval(tokArr)
    #checks for operands or digits
    if pos is not 0:
        if tokArr[pos].isdigit():
            return str(tokArr[pos])
        elif tokArr[pos] in opperands:
            if tokArr[pos - 1] is '(':
                return str(evalOps(tokArr))
#runs code through line
def prefixReader(line):
    global pos
    regex = re.compile(r'(\w+|>|<|\(|\)|\+|\-|\*|\/)')
    par = {'(',')'}
    pos = 0
    new = regex.findall(line)
    line = line.rstrip('\n')
    print("> "+line)
    try:
        checkForError(new)
        res = prefixEval(new)
        if len(new) > pos+2:
            if new[pos+1] is ')' and new[pos+2] is '(':
                raise FunctionError("Function Error: Too many arguments")
        if res is not None:
            print(res)
            print()
    except (FunctionError,PrefixSyntax) as p:
        print(p)
#for loop for code
for line in inFile:
    prefixReader(line)