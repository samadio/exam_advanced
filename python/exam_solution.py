"""
File: exam_solution.py
Authors: Amadio Simone, Indri Patrick
Date: February 5, 2019

Contains the PostcardList class, solution to the exam request.
"""

from datetime import datetime as dt # Used to deal with dates.

class PostcardList: 
    """
    Class that reads/writes Postcard message from/to a properly formatted file.
    Each record is a Postcard.
    The Postcard format is "date:$(DATE); from:$(SENDER); to:$(RECEIVER);"

    Attributes
    ----------
    _file : list
        List of file names, to keep track of multiple files.
    _postcards : list
        List of postcards read from _file.
    _date : dict
        Dict where the key is the str date, and the value is a list of indices.
        Each index refers to the corresponding record.
    _from: dict
        Dict where the key is the str sender, and the value is a list of indices.
        Each index refers to the corresponding record.
    _to: dict
        Dict where the key is the str receiver, and the value is a list of indices.
        Each index refers to the corresponding record.

    Methods
    -------
    clear()
        Clears attributes, resetting the PostcardList to an empty one.
    getNumberOfPostcards()
        Returns the number of records.
    parsePostcards(start = 0)
        Parses the postcards in self._postcards.
        It updates the self._date, ._from and ._to dicts.
    readFile(filename)
        Reads and parses poscards from a file, overwriting the attributes.
    writeFile(filename)
        Writes to file the records in self._postcards.
    updateLists(newfilename)
        Reads records from file and appends to self._postcards.
        Then parses the newly added records, updating the dicts. 
    updateFile(filename)
        Appends to file the records in self._postcards.
    getPostcardsByDateRange(date_range)
        Takes date_range as list [l_bound, u_bount].
        Returns a list of the records in self._postcards within the date_range.
    getPostcardsBySender(sender)
        Returns a list of the records in self._postcards sent by sender.
    getPostcardsByReceiver(receiver)
        Returns a list of the records in self._postcards received by receiver.
    """


    def __init__(self):

        self.clear()

    def clear(self): #Not sure: which is to be preferred?
        """
        Clears attributes, resetting the PostcardList to an empty one.
        """
        self._file = []
        self._postcards = []
        self._date = {} # Dates will be stored as str, as requested.
                        # Alternatively, they can be stored as datetime.date
        self._from = {}
        self._to = {}
    
    def getNumberOfPostcards(self):
        """
        Returns the number of records.
        """

        return len(self._postcards)
    
    def parsePostcards(self,start=0):
        """
        Parses the postcards in self._postcards from the start record on.
        It updates the self._date, ._from and ._to dicts.

        Parameters
        ----------
        start : int
            The record from which the parsing should start.
        """
        

        for i,card in enumerate(self._postcards[start:]):   # Newly added records.
            card = card.split(";")

            # Cleaning entries correcting format.
            date = card[0].replace('date:','')
            sender = card[1].replace(" from:","")
            receiver = card[2].replace(" to:","")

            if date not in self._date:
                self._date[date] = []
            self._date[date].append(start+i)   
            if sender not in self._from:
                self._from[sender] = []
            self._from[sender].append(start+i)   
            if receiver not in self._to:
                self._to[receiver] = []
            self._to[receiver].append(start+i)   

    
    def readFile(self,filename):
        """
        Reads and parses poscards from a file, overwriting the attributes.

        Parameters
        ----------
        filename : str
            Name of the file from which records should be read.
        """

        self.clear()
        self._file = [filename]
        with open(filename,'r') as f:
            for i in f:
                self._postcards.append(i)
        self.parsePostcards()


    def writeFile(self,filename):
        """
        Writes to file the records in self._postcards.

        Parameters
        ----------
        filename : str
            Name of the file on which records should be written.
        """

        with open(filename,'w') as f:
            for i in self._postcards:
                print(i,file=f)
    

    def updateLists(self,newfilename):
        """
        Reads records from file and appends to self._postcards.
        Then parses the newly added records, updating the dicts. 

        Parameters
        ----------
        newfilename : str
            Name of the file from which records should be read.
        """

        self._file.append(newfilename)
        previous_size=len(self._postcards)
        with open(newfilename,'r') as f:
            for i in f:
                self._postcards.append(i)
        self.parsePostcards(previous_size)
        
        
        
    def updateFile(self,filename):
        """
        Appends to file the records in self._postcards.

        Parameters
        ----------
        filename : str
            Name of the file on which records should be appended.
        """

        with open(filename,'a+') as f:
            for i in self._postcards:
                print(i,file=f)
                

    def getPostcardsByDateRange(self,date_range):
        """
        Takes date_range as list [l_bound, u_bound].
        Returns a list of the records in self._postcards within the date_range.

        Parameters
        ----------
        date_range : list
        List containing [l_bound, u_bound], assumed to be a list of dates.
        """

        l = []    

        for i in (self._date).keys():  #cycle through the dict keys (date string)
            tmp=dt.strptime(i, "%Y-%m-%d")
            if (date_range[0]<=tmp<=date_range[1]):
                for j in self._date[i]:
                    l.append(   (self._postcards[j])   )

        return l
    
    
    def getPostcardsBySender(self, sender):
        """
        Returns a list of the records in self._postcards sent by sender.

        Parameters
        ---------
        sender : str
            The sender whose records should be returned.
        """

        return [self._postcards[i] for i in self._from.get(sender, [])]
    
    
    def getPostcardsByReceiver(self, receiver):
        """
        Returns a list of the records in self._postcards received by receiver.

        Parameters
        ----------
        receiver : str
            The receiver whose records should be returned.
        """

        return [self._postcards[i] for i in self._to.get(receiver, [])]
        
