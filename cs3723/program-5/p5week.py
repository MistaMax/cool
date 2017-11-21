import re
from p5team import Team

#Containts all the dictionary terms for wins (1) and losses(0)
trans = {"BEAT": 1, "BEATS": 1
            , "DEFEAT": 1, "DEFEATS": 1, "DEFEATED": 1
            , "SLAUGHTER": 1, "SLAUGHTERS": 1, "SLAUGHTERED": 1
            , "WHIP": 1, "WHIPS": 1, "WHIPPED": 1
            , "TOP": 1, "TOPS": 1, "TOPPED": 1
            , "UPSET":1, "UPSETS": 1
            , "SHUT": 1, "SHUTS": 1, "SHUTS OUT": 1
            , "EAT": 1, "EATS": 1
            , "DESTROY": 1, "DESTROYS": 1, "DESTROYED": 1
            , "SOAR": 1, "SOARS": 1, "SOAR OVER": 1, "SOARS OVER": 1
            
            , "LOSES TO": 0, "LOST TO": 0
            , "BEAT BY": 0, "BEATEN BY": 0
            , "DEFEATED BY": 0
            , "SLAUGHTERED BY": 0
            , "WHIPPED BY": 0
            , "TOPPED BY": 0
            , "UPSET BY": 0
            , "EATEN BY": 0
            , "DESTROYED BY": 0}
#recGame
#takes in the game data and processes it to tally up the scores with the correlating teams
def recGame(outcomeStr, scoreStr):
    #
    #Parse nicknames from outcomeStr
    b = 0 #keeps track of how many nicknames found
    for name, team in Team.directTeams.items():
        for nick in sorted(team.nicks, key = len, reverse = True):
            if nick in outcomeStr and b == 0:   #found one nickname
                nName1 = nick
                teamObj1 = team
                b = 1
                break
            elif nick in outcomeStr:    #found second one
                nName2 = nick
                teamObj2 = team
                b = 2
                break
        if b == 2:
            break
#changes the string to a number
    outcomeRE = re.compile(r'('+nName1+'|'+nName2+') (.*) ('+nName1+'|'+nName2+')\s*')
    scoreRE = re.compile(r'(\d+) .* (\d+)')
    outcomeObj = outcomeRE.search(outcomeStr)
    scoreObj = scoreRE.search(scoreStr)
    
    nName1 = outcomeObj.group(1)
    verb = outcomeObj.group(2)
    nName2 = outcomeObj.group(3)
#looks for team names
    if nName1 in teamObj1.nicks:
        team1 = teamObj1.name
        team2 = teamObj2.name
    else:
        team1 = teamObj2.name
        team2 = teamObj1.name
#
#translateVerb to see who won
    if trans.get(verb) != None:
        team1Win = trans[verb]
    else:
        team1Win = 1
#find scores and make things more readable+
    if team1Win == 1:
        winningTeam = team1
        lossingTeam = team2
        if int(scoreObj.group(1)) > int(scoreObj.group(2)):
            winningScore = scoreObj.group(1) 
            lossingScore = scoreObj.group(2)
        else:
            winningScore = scoreObj.group(2)
            lossingScore = scoreObj.group(1)
    else:
        winningTeam = team2
        lossingTeam = team1
        if int(scoreObj.group(1)) < int(scoreObj.group(2)):
            lossingScore = scoreObj.group(1) 
            winningScore = scoreObj.group(2)
        else:
            lossingScore = scoreObj.group(2)
            winningScore = scoreObj.group(1)
#update the team data with wins and losses accordingly
    Team.updateTally(winningTeam, lossingTeam)
    print("\t" + winningTeam, lossingTeam, winningScore, lossingScore) 
