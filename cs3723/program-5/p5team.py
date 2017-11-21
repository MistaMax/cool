#the object stores all the team data and the class stores all the teams
class Team:
    
    directTeams = {} #dictionary of all the teams 
    
    #initializes the team variable and then adds itself to the dictionary of the teams in the class
    def __init__(self, name, nicks):
        self.name = name
        self.nicks = nicks.split(", ")
        self.nicks.append(name)
        self.wins = 0
        self.losses = 0
        Team.directTeams[name] = self

    
    #displays the name, the wins, and the losses in a nice organized fashion
    def display(self):
        if len(self.name) >= 4:
            print("\t" + self.name, self.wins, "   ", self.losses)
        else:
            tmp = ""
            for i in range(3-len(self.name)):
                tmp += " "
            print("\t" + self.name, tmp, self.wins, "   ", self.losses)
    
    
    #increments the ammount of wins the team has
    def incrementWins(self):
        self.wins += 1
    
    
    #increments the ammount of losses the team has
    def incrementLosses(self):
        self.losses += 1
    
    
    #this method is not a part of the object, but is a part of the class that displays all the team's data stored in the dictionary
    @classmethod
    def displayAll(cls):
        print("\tTeam Wins Losses")
        for name, team in sorted(Team.directTeams.items()):
            team.display()
        print()
    
    
    #another class method that increments both the winning and loosing tally of the corresponding teams
    @classmethod
    def updateTally(cls, winner, losser):
        Team.directTeams[winner].incrementWins()
        Team.directTeams[losser].incrementLosses()
            

