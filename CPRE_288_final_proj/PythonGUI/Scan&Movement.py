import tkinter as tk
# Serial library:  https://pyserial.readthedocs.io/en/latest/shortintro.html 
import serial
import time # Time library   
# Socket library:  https://realpython.com/python-sockets/  
# See: Background, Socket API Overview, and TCP Sockets  
import socket   

window = tk.Tk()
frame_one = tk.Frame()
frame_two = tk.Frame()
frame_three = tk.Frame()

btnForward = tk.Button(
    master= frame_one,
    text="Forward",
    width=15,
    height=1,
    bg="black",
    fg="white"
    )

btnLeft = tk.Button(
    master= frame_two,
    text="Turn Left",
    width=15,
    height=1,
    bg="black",
    fg="white"
    )

btnRight = tk.Button(
    master= frame_two,
    text="Turn Right",
    width=15,
    height=1,
    bg="black",
    fg="white"
    )

btnBack = tk.Button(
    master= frame_three,
    text="Backward",
    width=15,
    height=1,
    bg="black",
    fg="white"
    )
btnScan = tk.Button(
    master= frame_three,
    text="Scan",
    width=15,
    height=1,
    bg="black",
    fg="white"
    )





def handle_forward(event):
    HOST = "192.168.1.1"  # The server's hostname or IP address
    PORT = 288        # The port used by the server
    cybot_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Create a socket object
    cybot_socket.connect((HOST, PORT))   # Connect to the socket  (Note: Server must first be running)
    cybot = cybot_socket.makefile("rbw", buffering=0)  # makefile creates a file object out of a socket:  https://pythontic.com/modules/socket/makefile                    
    send_message = "f"
    cybot.write(send_message.encode()) # Convert String to bytes (i.e., encode), and send data to the server

    time.sleep(1) # Sleep for 2 seconds
    cybot.close()         # Close file object associated with the socket or UART
    cybot_socket.close()  # Close the socket (NOTE: comment out if using UART interface, only use for network socket option)


def handle_left(event):
    HOST = "192.168.1.1"  # The server's hostname or IP address
    PORT = 288        # The port used by the server
    cybot_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Create a socket object
    cybot_socket.connect((HOST, PORT))   # Connect to the socket  (Note: Server must first be running)
    cybot = cybot_socket.makefile("rbw", buffering=0)  # makefile creates a file object out of a socket:  https://pythontic.com/modules/socket/makefile 

    send_message = "l"
    cybot.write(send_message.encode()) # Convert String to bytes (i.e., encode), and send data to the server
    time.sleep(2) # Sleep for 2 seconds
    cybot_socket.close()  # Close the socket (NOTE: comment out if using UART interface, only use for network socket option)



def handle_right(event):
    HOST = "192.168.1.1"  # The server's hostname or IP address
    PORT = 288        # The port used by the server
    cybot_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Create a socket object
    cybot_socket.connect((HOST, PORT))   # Connect to the socket  (Note: Server must first be running)
    cybot = cybot_socket.makefile("rbw", buffering=0)  # makefile creates a file object out of a socket:  https://pythontic.com/modules/socket/makefile
                    
    send_message = "r"
    cybot.write(send_message.encode()) # Convert String to bytes (i.e., encode), and send data to the server

    time.sleep(2) # Sleep for 2 seconds
    cybot.close()         # Close file object associated with the socket or UART
    cybot_socket.close()  # Close the socket (NOTE: comment out if using UART interface, only use for network socket option)

def handle_back(event):
    HOST = "192.168.1.1"  # The server's hostname or IP address
    PORT = 288        # The port used by the server
    cybot_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Create a socket object
    cybot_socket.connect((HOST, PORT))   # Connect to the socket  (Note: Server must first be running)
    cybot = cybot_socket.makefile("rbw", buffering=0)  # makefile creates a file object out of a socket:  https://pythontic.com/modules/socket/makefile
                    
    send_message = "b"
    cybot.write(send_message.encode()) # Convert String to bytes (i.e., encode), and send data to the server

    time.sleep(2) # Sleep for 2 seconds
    cybot.close()         # Close file object associated with the socket or UART
    cybot_socket.close()  # Close the socket (NOTE: comment out if using UART interface, only use for network socket option)

def handle_scan(event):
    HOST = "192.168.1.1"  # The server's hostname or IP address
    PORT = 288        # The port used by the server
    cybot_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Create a socket object
    cybot_socket.connect((HOST, PORT))   # Connect to the socket  (Note: Server must first be running)
    cybot = cybot_socket.makefile("rbw", buffering=0)  # makefile creates a file object out of a socket:  https://pythontic.com/modules/socket/makefile
                    
    send_message = "m"
    cybot.write(send_message.encode()) # Convert String to bytes (i.e., encode), and send data to the server
    i = 0
    while(i < 93):
        if(i == 92):
            index = cybot.readline().decode()
            index = int(index.strip('/r'))
            print("Number of objects "+ str(index))
            while(index >= 0):
                rx_message = cybot.readline()
                print(rx_message.decode())
                index -= 1
        else:
            rx_message = cybot.readline()
            print(rx_message.decode())
        i += 1
    time.sleep(2) # Sleep for 2 seconds
    cybot.close()         # Close file object associated with the socket or UART
    cybot_socket.close()  # Close the socket (NOTE: comment out if using UART interface, only use for network socket option)


btnForward.pack()
btnLeft.pack()
btnRight.pack()
btnBack.pack()
btnScan.pack()
frame_one.pack(fill=tk.X)
frame_two.pack(fill=tk.X)
frame_three.pack(fill=tk.X)

btnForward.bind("<Button-1>", handle_forward)
btnLeft.bind("<Button-1>", handle_left)
btnRight.bind("<Button-1>", handle_right)
btnBack.bind("<Button-1>", handle_back)
btnScan.bind("<Button-1>", handle_scan)
#run Tkinter event loop so that the program continiously listens for events
#like button clicks or key pressed
window.mainloop()
