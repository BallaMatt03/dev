import sys, math, random

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

# playerCount: the amount of players (2 to 4)
# myId: my player ID (0, 1, 2 or 3)
# zoneCount: the amount of zones on the map
# linkCount: the amount of links between all zones
playerCount, myId, zoneCount, linkCount = [int(i) for i in raw_input().split()]
zoneIds = list()
zoneResources = dict()
links = list()

for i in xrange(zoneCount):
    # zoneId: this zone's ID (between 0 and zoneCount-1)
    # platinumSource: the amount of Platinum this zone can provide per game turn
    zoneId, platinumSource = [int(i) for i in raw_input().split()]
    zoneIds.append(zoneId)
    zoneResources[zoneId] = platinumSource
    
for i in xrange(linkCount):
    zone1, zone2 = [int(i) for i in raw_input().split()]
    links.append([zone1,zone2])

# game loop
while 1:
    platinum = int(raw_input()) # my available Platinum
    
    for i in xrange(zoneCount):
        # zId: this zone's ID
        # ownerId: the player who owns this zone (-1 otherwise)
        # podsP0: player 0's PODs on this zone
        # podsP1: player 1's PODs on this zone
        # podsP2: player 2's PODs on this zone (always 0 for a two player game)
        # podsP3: player 3's PODs on this zone (always 0 for a two or three player game)
        zId, ownerId, podsP0, podsP1, podsP2, podsP3 = [int(i) for i in raw_input().split()]
    
    # Write an action using print
    # To debug: print >> sys.stderr, "Debug messages..."

    print "WAIT" # first line for movement commands, second line for POD purchase (see the protocol in the statement for details)
    
    #if(platinum >= 20):
    #    print "1 {}".format(zoneIds[random.randint(0,len(zoneIds)-1])
    #else:
    print "WAIT"