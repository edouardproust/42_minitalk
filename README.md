# Minitalk

**The purpose of this project is to code a small data exchange program
using UNIX signals.**

- **Subject:** [English](subject/en.subject.pdf) / [French](subject/fr.subject.pdf) / [Spanish](subject/es.subject.pdf)
- **Location:** 42 School Barcelona
- **Validation:** January 2025

## How to use

1. **Clone the Repository**

	```
	git clone https://github.com/leogaudin/minitalk.git
	```
2. **Compile the Code**

	Navigate to the project directory and compile using:
	```
	make
	```

3. **Run the Server**

	Start the server in one terminal:
	```
	./server
	```
	The server will display its process ID (PID).

4. **Run the Client**

	In another terminal, execute the client with the server's PID and your desired message:
	```
	./client <server_pid> <message>
	```

	For example:
	```
	./client 12345 "Hello"
	```

5. **Message Reception**

	The server will receive and print each character of the message as it is transmitted.
