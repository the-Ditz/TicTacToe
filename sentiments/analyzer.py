import nltk  # http://www.nltk.org/
from nltk.tokenize import TweetTokenizer # http://www.nltk.org/api/nltk.tokenize.html

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        
        self.positives = list()
        self.negatives = list()
        
        #load in positive words
        with open(positives, "r") as lines:
            for line in lines:
                if line.startswith(";"):
                    #print("not added") #debug
                    continue
                else:
                    #print("{}".format(line.strip())) #debug
                    self.positives.append(line.strip())
                    
                    #print("{}".format(self.positives)) #debug
            
            
            #for word in self.positives:  #debug
                #print("{}".format(word))
                
        #load in negative words
        with open(negatives, "r") as lines:
            for line in lines:
                if (line.startswith(";") or line.startswith(" ")):
                    continue
                else:
                    self.negatives.append(line.strip())
        
        
    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        
        sentiment = 0
        
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
        
        for token in tokens:
            #print("{}".format(token)) #debug
            if token.lower() in self.positives:
                #print("yes") #debug
                sentiment += 1
            elif token.lower() in self.negatives:
                #print("yes") #debug
                sentiment -= 1
        
        #debug print("{}".format(token.lower())) 
        
        return sentiment

