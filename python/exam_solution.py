from datetime import datetime as dt# use this module to deal with dates:  https://docs.python.org/3/library/datetime.html
from collections import defaultdict

class PostcardList: 
    def __init__(self):
        '''
        constructor
        '''
        self._file = list() #keep track of multiple file
        self._postcards = []
        self._date= {} #dict(str(date),list(indexes where data is))
        self._from= {}
        self._to= {}
#date are stored as string, because we are required to do so, otherwise it's even
 #possible to store them directly as dates
        
    def __delitem__(self):
        '''
        destructor
        '''
        del self._file
        del self._postcards
        del self._date #dict(str(date),list(indexes where data is))
        del self._from
        del self._to
    
    def clear(self): #Not sure: which is to be preferred?
        '''
        clear content of variable
        '''
        del self
        self=PostcardList()
        #self._file = list() #keep track of multiple file
        #self._postcards = []
        #self._date= {} #dict(str(date),list(indexes where data is))
        #self._from= {}
        #self._to= {}
    
    def getNumberOfPostcards(self):
        '''
        returns number of postcards in PostcardList
        '''
        return len(self._postcards)
    
    def parsePostcards(self,start=0):
        '''
        given the postcards inserted in self._postcards, it updates dictionaries of self._date,._from and ._to
        '''
        tmp=self._postcards[start:] #tmp is new postcards added
        for i,card in enumerate(tmp):
            card = card.split(";")
            card[0]=card[0].replace('date:','') #date: is deleted
            card[1]=card[1].replace(" from:","")
            card[2]=card[2].replace(" to:","")
            if card[0] not in self._date:
                self._date[card[0]] = []
            self._date[card[0]].append(start+i)   
            if card[1] not in self._from:
                self._from[card[1]] = []
            self._from[card[1]].append(start+i)   
            if card[2] not in self._to:
                self._to[card[2]] = []
            self._to[card[2]].append(start+i)   

    
    def readFile(self,filename):
        '''
        read postcards from formatted file and create new Postcardlist
        '''
        self.clear()
        self._file = [filename]
        with open(filename,'r') as f:
            for i in f:
                self._postcards.append(i)
        self.parsePostcards()

    def writeFile(self,filename):
        '''
        write a new file named "filename" with formatted content of self
        '''
        with open(filename,'w') as f:
            for i in self._postcards:
                print(i,file=f)
    
    def updateLists(self,newfilename):
        '''
        appends elements from a new or updated file to self
        '''
        self._file.append(newfilename)
        previous_size=len(self._postcards)
        with open(newfilename,'r') as f:
            for i in f:
                self._postcards.append(i)
        self.parsePostcards(previous_size)
        
        
        
    def updateFile(self,filename):
        '''
        Update a file named "filename" with the content of self
        '''
        with open(filename,'a+') as f:
            for i in self._postcards:
                print(i,file=f)
                
                
                
    #range methods            
                
    def getPostcardsByDateRange(self,date_range):  #data range assumed to be a list of strings
        '''
        takes date_range as list [lower_bound,upper_b] and return self._postcards with date in that range
        '''
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
        
