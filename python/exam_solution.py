from datetime import datetime as dt# use this module to deal with dates:  https://docs.python.org/3/library/datetime.html
from collections import defaultdict

class PostcardList: 
    def __init__(self):
        self._file = "" #keep track of multiple file
        self._postcards = []
        self._date= {} #dict(str(date),list(indexes where data is))
        self._from= {}
        self._to= {}
#date are stored as string, because we are required to do so, otherwise it's even
 #possible to store them directly as dates
        
        
    def getNumberOfPostcards(self):
        return len(self._postcards)
    
    def parsePostcards(self):
        #here I might need to reset all the dictionaries
        for i,card in enumerate(self._postcards):
            card = card.split(";")
            card[0]=card[0].replace('date:','') #date: is deleted
            card[1]=card[1].replace(" from:","")
            card[2]=card[2].replace(" to:","")
            if card[0] not in self._date:
                self._date[card[0]] = []
            self._date[card[0]].append(i)   
            if card[1] not in self._from:
                self._from[card[1]] = []
            self._from[card[1]].append(i)   
            if card[2] not in self._to:
                self._to[card[2]] = []
            self._to[card[2]].append(i)   

    
    def readFile(self,filename):
        self._postcards = [] ##delete everything?
        self._file = filename
        with open(filename,'r') as f:
            for i in f:
                self._postcards.append(i)
        self.parsePostcards()
    
    def writeFile(self,filename):
        with open(filename,'w') as f:
            for i in self._postcards:
                print(i,file=f)
    
    #updateLists(self,...): as read but appending to self._postcards
    def updateLists(self,newfilename):
        self._file = newfilename
        with open(newfilename,'r') as f:
            for i in f:
                self._postcards.append(i)
        #self.parsePostcards()  # this may couse trouble
        # if I want to do this, I need to reset all the dictionaries
        
    def updateFile(self,filename):
        with open(filename,'a+') as f:
            for i in self._postcards:
                print(i,file=f)
                
                
                
    #range methods            
                
    def getPostcardsByDateRange(self,date_range):  #data range assumed to be a list of strings
        l = []
    
        for i in (self._date).keys():  #cycle through the dict keys (date string)
            tmp=dt.strptime(i, "%Y-%m-%d")
            if (date_range[0]<=tmp<=date_range[1]):
                for j in self._date[i]:
                    l.append(   (self._postcards[j])   )
        return l
    
   # added list comprehension, more pythonic 
    
    def getPostcardsBySender(self, sender):
        '''
        returns a list with the postcards from a given sender
        '''
        return [self._postcards[i] for i in self._from.get(sender, [])]
    
    
    def getPostcardsByReceiver(self, receiver):
        '''
        returns a list with the postcards from a given receiver
        '''
        return [self._postcards[i] for i in self._to.get(receiver, [])]
        
