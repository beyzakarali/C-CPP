The documents that are sent to the printer are buffered in the queue of the printer. The PC sends the documents
to be printer to the queue buffer and the printer prints out the documents in an ordered fashion. You are required
to implement a circular buffer for this process. You can find the requirements of the project below.
● The printer can at most buffer 20 documents in its queue (you may be asked to change this value during
the evaluation of your project ).
● The PC can insert a document in to the buffer at anytime and at any rate. The printer should work in first in
and first out (FIFO) manner.
● When the queue is full PC can not insert new documents to the buffer and the user receives a warning.
● It should be possible to query the current status of the queue. E.g. How many documents there are in the
queue.
● The documents shall be printed in the order they are sent.
● You are required to change the source code during the evaluation process.
● Insertion and printing of the documents shall be simulated via modules added to your project.
○ Insertion can be simulated via imaginary documents whose properties kept in a file. The rate at
which the documents are sent to the printer shall be adjustable.
○ Printing of the documents shall be simulated via a parameter where the printing time is calculated
via deviding the printing speed to the number of pages the document contains. For example, if the
printer can print 100 pages in a minute, a 10 pages document shall take 6 seconds to print.