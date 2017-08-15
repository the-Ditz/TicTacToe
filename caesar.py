import cs50
import sys


def main():
    keyValue = 0;
    if len(sys.argv) != 2:
        print("Usage: ./caesar k\n")
        exit(1)
    else:
        keyValue = len(sys.argv[1])
    oText = promptText(); #sets phrase to be decrypted
    messageLength = len(oText)
    cipherText(oText, messageLength, keyValue)
    exit(0)

# prompts for code to be encrypted, verifies != None and then returns it 
def promptText(): 
    print("plaintext: ", end="")
    oText = cs50.get_string()
    if (oText == None):
        return "FAILURE - NO VALUE"
    else:
        return oText

#encrypt using ceasar
def cipherText(oText, messageLength, keyValue): #take chars from string and change according to key passed in from console
    newText = ("")
    for k in range(messageLength):
        if (ord(oText[k]) > 123 or (ord(oText[k])  < 64) or (ord(oText[k]) >= 91 and ord(oText[k]) <= 96)):  #58:00 in lecture
            newText += oText[k]; #going to try building string iteratively as suggested here: https://stackoverflow.com/questions/10631473/str-object-does-not-support-item-assignment-in-python... this really makes sense given the immutable quality of strings in python as discussed in lecture
        elif int(keyValue + ord(oText[k])) > 122:
            newText += (((ord(oText[k]) + keyValue) % 122) + 96) 
        elif ((ord(oText[k]) < 91) and ((keyValue + ord(oText[k])) > 91)):
            newText += ((ord((oText[k]) + keyValue) % 91) + 65)
        else:
            newText += chr(ord(oText[k]) + keyValue)  
    print("ciphertext: {}".format(newText))
    return oText;

#call main
if __name__ == "__main__":
    main()