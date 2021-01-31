# Using C++ 11 or later create 2 applications that talk to each other thru sockets to do the following

Application A

-At the moment of execution, it will receive an argument indicating the path to a txt file that will be used for logging-

Generate a list of 10 pseudorandom integers between 1 and 20

Sort the list in ascending order

Send the list of integers to application B thru a socket

If the communication fails then write to the log: "Transmission failed!"

If the communication succeeds then write to the log: "Transmission succeeded!, message from server: XXXXX"

Press any key (to close the app)

Write to the log the pressed key and close the app

Application B

-At the moment of execution, it will receive an argument indicating the path to a txt file that will be used for logging, same file as app A-

Listen to information from App A

After receiving information from A, notify back with a message XXXXX

Log the list of numbers received from A

Calculate the factorial of each number and log the result only if such result is less than 100,000,000,000

Press any key (to close the App)

Log the pressed key and close the app

Note: Indicate somehow inside the log file which app is the message coming from

Please send us the code and the compiled apps
