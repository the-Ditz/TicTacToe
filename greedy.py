import cs50

def main():
    value = getValue()
    checkValue(value)
    makeChange(value)
    
def getValue():
    print("O hai! How much change is owed?")
    value = cs50.cs50.get_float()
    return value

def checkValue(value):
    while value < 0:
        print("How much change is owed?")
        value = cs50.get_float()
    return value

def makeChange(value):
    cents = (round(value * 100))
    #print("{}".format(cents))
    coinTotal = 0
    coinTotal = coinTotal + coinOut(cents, 25)
    cents = cents % 25
    coinTotal = coinTotal + coinOut(cents, 10)
    cents = cents % 10
    coinTotal = coinTotal + coinOut(cents, 5)
    cents = cents % 5
    coinTotal = coinTotal + coinOut(cents, 1)
    print("{}".format(coinTotal))

def coinOut(cents, increment): 
    coinCounter = 0
    while cents >= increment:
        coinCounter += 1
        cents -= increment
    return coinCounter
    
#call main
if __name__ == "__main__":
    main()