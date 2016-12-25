#!/bin/python3

import sys

# Sorts the coordinates so that point1 is the bottom left and point2 the top right
def sortCoordinates(point1, point2):
    for i in range (0,2):
        if (point1[i] > point2[i]):
            tempPoint = point1[i];
            point1[i] = point2[i];
            point2[i] = tempPoint;
    return [point1, point2];

def intersection(r1, r2):
    # Create a new rectangle where each side is the tighter bound from either rectangle
    newRectangle = [[max(r1[0][0], r2[0][0]), max(r1[0][1], r2[0][1])], [min(r1[1][0], r2[1][0]), min(r1[1][1], r2[1][1])]];
    # If there is no overlap, make the rectangle a single point (so that all future combinations with this rectangle remain 0)
    if (newRectangle[0][1] > newRectangle[1][1] or newRectangle[0][0] > newRectangle[1][0]):
        newRectangle = [[0, 0], [0, 0]];
    return newRectangle;

# Finds the area between two rectangles
def findArea(r):
    return (r[1][0]-r[0][0]) * (r[1][1] - r[0][1]);

# This unholy line of code takes two points given as arguments to the program and turns it into a rectangle with two points: lower left and top right
def parseInput(arg1, arg2):
    return sortCoordinates([float(arg1.split(',')[0]), float(arg1.split(',')[1])], [float(arg2.split(',')[0]), float(arg2.split(',')[1])]); 

# Create the first rectangle from the first two arguments
newRectangle = parseInput(sys.argv[1], sys.argv[2]);
# Intersect all the proceeding rectangles
for i in range(3, len(sys.argv)):
    if (i % 2 == 1):
        newRectangle = intersection(parseInput(sys.argv[i], sys.argv[i+1]), newRectangle);

print(findArea(newRectangle));
