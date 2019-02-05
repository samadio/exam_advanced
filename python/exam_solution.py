from datetime import datetime as dt# use this module to deal with dates:  https://docs.python.org/3/library/datetime.html
from collections import defaultdict

class PostcardList: 
    def __init__(self):
        self._file = list() #keep track of multiple file
        self._postcards = list()
        self._date= defaultdict(list) #dict(str(date),list(indexes where data is))
        self._from=defaultdict(list)
        self._to=defaultdict(list)
        self._size=0
#date are stored as string, because we are required to do so, otherwise it's even
 #possible to store them directly as dates
        
        
    def getNumberOfPostcards(self):
        return self._size
    
    def __len__(self):
        return self._size
    
    def parsePostcards(self,input_list):
        for i in input_list:
                i=i.split(";")
                i[0]=i[0].replace('date:','') #date: is deleted
                i[1]=i[1].replace(" from:","")
                i[2]=i[2].replace(" to:","")
                #if i[0] not in self._date:
                #    self._date[i[0]] = []
                #self._date[i[0]].append(self._size)   
                self._date[i[0]].append(self._size)
                self._from[i[1]].append(self._size)
                self._to[i[2]].append(self._size)
                self._size+=1
    
    
    def readFile(self,filename):
        ##delete everything
        self._file.append(filename)
        with open(filename,'r') as f:
            for i in f:
                self._postcards.append(i)
        self.parsePostcards(self._postcards)
    
    def writeFile(self,filename):
        with open(filename,'w') as f:
            for i in self._postcards:
                print(i,file=f)
    
    #updateLists(self,...): as read but appending to self._postcards
    def updateLists(self,newfilename):
        self._file.append(newfilename)
        with open(newfilename,'r') as f:
            tmp =list()
            for i in f:
                self._postcards.append(i)
                tmp.append(i) #list with all the newcontent
        self.parsePostcards(tmp)  
        
    def updateFile(self,filename):
        with open(filename,'a+') as f:
            for i in self._postcards:
                print(i,file=f)
                
                
                
    #range methods            
                
    def getPostcardsByDateRange(self,date_range):  #data range assumed to be a list of strings
        l=list()
        date_range=tuple(date_range)               #become const as tuple
    #    l_bound=dt.strptime(date_range[0], "%Y-%m-%d")
    #    u_bound=dt.strptime(date_range[1], "%Y-%m-%d")
    #    u_bound=datetime.date.fromisoformat(date_string[1])
    
        for i in (self._date).keys():  #cycle through the dictionary keys (date string)
            tmp=dt.strptime(i, "%Y-%m-%d")
            if (date_range[0]<=tmp<=date_range[1]):
                for j in self._date[i]:
                    l.append(   (self._postcards[j])   )
        return l
    
    
    
    def getPostcardsBySender(self, sender):
        '''
        returns a list with the postcards from a given sender
        '''
        l=list()
        for i in (self._from).keys():  #cycle through the dictionary keys (date string)
            if (i==sender):
                for j in self._from[i]:
                    l.append(   (self._postcards[j])   )
        return l
    
    
    def getPostcardsByReceiver(self, receiver):
        '''
        returns a list with the postcards from a given receiver
        '''
        l=list()
        for i in (self._to).keys():  #cycle through the dictionary keys (date string)
            if (i==receiver):
                for j in self._to[i]:
                    l.append(   (self._postcards[j])   )
        return l
        
