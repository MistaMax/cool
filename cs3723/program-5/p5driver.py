import sys
import re
from p5team import Team
from p5week import recGame
if len(sys.argv) < 2:
    print("input filename needed as input")
    sys.exit(1)

file = open(sys.argv[1], "r")
formGame = re.compile(r'([\w\s]*),? (\d+ .* \d+)')
formWeek = re.compile(r'WEEK (\d+)')
#state list, 0=Initialization state, 1=Initializing team objects, 2=Processing game data
state = 0

while True:
    inputLine = file.readline()
    if inputLine == "":
        break
    inputLine = inputLine.rstrip('\n')
    
    #sets the state depending on the input
    if inputLine == "TEAMS":
        state = 1
    elif inputLine == "ENDTEAMS":
        state = 2
        print("Initial")
        Team.displayAll()
    elif inputLine == "END":
        break
    
    #create the team objects from the input
    elif state == 1:
        tmp = inputLine.split(" ", 1)
        Team(tmp[0], tmp[1])
    
    #process all the game data using functions from week
    elif state == 2:
        if formWeek.match(inputLine):
            weekNum = formWeek.match(inputLine).group(1)
        elif inputLine == "ENDWEEK":
            print("Week", weekNum)
            Team.displayAll()
        else:
            gameObj = formGame.search(inputLine)
            recGame(gameObj.group(1), gameObj.group(2))
file.close()
