CC = g++
CFLAGS = -Wall -g

# Define object files
OBJ = main.o doctor.o patient.o appointment.o user.o 

# Default target
CAS: $(OBJ)
	$(CC) $(CFLAGS) -o CAS $(OBJ)

# Compile source files
main.o: main.cpp doctor.h patient.h appointment.h
	$(CC) $(CFLAGS) -c main.cpp

doctor.o: doctor.cpp doctor.h user.h
	$(CC) $(CFLAGS) -c doctor.cpp

patient.o: patient.cpp patient.h user.h doctor.h appointment.h 
	$(CC) $(CFLAGS) -c patient.cpp

appointment.o: appointment.cpp appointment.h
	$(CC) $(CFLAGS) -c appointment.cpp

user.o: user.cpp user.h appointment.h helpers.h
	$(CC) $(CFLAGS) -c user.cpp

# Clean target to remove object files and executables
clean:
	rm -f *.o CAS