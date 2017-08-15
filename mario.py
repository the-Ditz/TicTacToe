import cs50

#define main
def main():
    height = getHeight()
    checkHeight(height)
    drawPyramid(height)

#get the height requested
def getHeight():
    print("Height: ", end="")
    return cs50.get_int()
    
#check the height value
def checkHeight(height):
    if height < 0 or height > 23:
        while True:
            print ("Height: ", end="")
            height = cs50.get_int()
            if height < 0 or height > 23:
                break
        return height
    elif height >= 0 and height < 24:
        return height
    return height
    
#take the height to draw pyramid    
def drawPyramid(height):
    layer = 0
    for layer in range(height):
        blocks = 1 + layer
        for n in range(height - 1 - layer):
            print(" ", end="")
        for o in range(blocks, 0, -1):
            print("#", end="")
        print ("  ", end="")
        for p in range(blocks, 0, -1):
            print("#", end="")
        print("")
        layer += 1
        
#call main
if __name__ == "__main__":
    main()