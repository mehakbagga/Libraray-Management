OBJS =  Book.o IssueRecord.o Student.o Library.o AppRunner.o

Library: $(OBJS)
	g++ -o Library $(OBJS)
	rm -f $(OBJS)

Book.o:
	g++ -c Book.cpp

IssueRecord.o:
	g++ -c IssueRecord.cpp

Student.o:
	g++ -c Student.cpp

Library.o:
	g++ -c Library.cpp

AppRunner.o:
	g++ -c AppRunner.cpp

clean:
	rm -f core Library $(OBJS)