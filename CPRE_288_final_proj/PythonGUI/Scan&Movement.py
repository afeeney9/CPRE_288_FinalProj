import tkinter as tk
from tkinter import Canvas

# Serial library:  https://pyserial.readthedocs.io/en/latest/shortintro.html 
import serial
import math
import time # Time library   
# Socket library:  https://realpython.com/python-sockets/  
# See: Background, Socket API Overview, and TCP Sockets  
import socket   

#global vars x,y track cybots current pos and dir tracks direction cybot is currently facing 
#objId is equal to number of objects 
x=0
y=0
dir = 'n'

obj_list = {}


window = tk.Tk()
window.geometry("750x500")

frame_moveFoward = tk.Frame()
frame_one = tk.Frame()
frame_two = tk.Frame()
frame_three = tk.Frame()
grid = tk.Frame()
init_color = 'blue' 
box_size = 61

square_1 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_2 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_3 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_4 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_5 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_6 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_7 = Canvas(grid, width=box_size, height=box_size, bg=init_color)

square_8 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_9 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_10 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_11 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_12 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_13 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_14 = Canvas(grid, width=box_size, height=box_size, bg=init_color)

square_15 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_16 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_17 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_18 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_19 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_20 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_21 = Canvas(grid, width=box_size, height=box_size, bg=init_color)

square_22 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_23 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_24 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_25 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_26 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_27 = Canvas(grid, width=box_size, height=box_size, bg=init_color)
square_28 = Canvas(grid, width=box_size, height=box_size, bg=init_color)

grid.columnconfigure(1, weight=1)
grid.columnconfigure(1, weight=3)
square_1.grid(column=0, row=0, sticky=tk.NW, padx=1, pady=1)
square_2.grid(column=1, row=0, sticky=tk.NW, padx=1, pady=1)
square_3.grid(column=2, row=0, sticky=tk.NW, padx=1, pady=1)
square_4.grid(column=3, row=0, sticky=tk.NW, padx=1, pady=1)
square_5.grid(column=4, row=0, sticky=tk.NW, padx=1, pady=1)
square_6.grid(column=5, row=0, sticky=tk.NW, padx=1, pady=1)
square_7.grid(column=6, row=0, sticky=tk.NW, padx=1, pady=1)

square_8.grid(column=0, row=1, sticky=tk.NW,  padx=1, pady=1)
square_9.grid(column=1, row=1, sticky=tk.NW,  padx=1, pady=1)
square_10.grid(column=2, row=1, sticky=tk.NW, padx=1, pady=1)
square_11.grid(column=3, row=1, sticky=tk.NW, padx=1, pady=1)
square_12.grid(column=4, row=1, sticky=tk.NW, padx=1, pady=1)
square_13.grid(column=5, row=1, sticky=tk.NW, padx=1, pady=1)
square_14.grid(column=6, row=1, sticky=tk.NW, padx=1, pady=1)

square_15.grid(column=0, row=2, sticky=tk.NW, padx=1, pady=1)
square_16.grid(column=1, row=2, sticky=tk.NW, padx=1, pady=1)
square_17.grid(column=2, row=2, sticky=tk.NW, padx=1, pady=1)
square_18.grid(column=3, row=2, sticky=tk.NW, padx=1, pady=1)
square_19.grid(column=4, row=2, sticky=tk.NW, padx=1, pady=1)
square_20.grid(column=5, row=2, sticky=tk.NW, padx=1, pady=1)
square_21.grid(column=6, row=2, sticky=tk.NW, padx=1, pady=1)

square_22.grid(column=0, row=3,sticky=tk.NW,  padx=1, pady=1)
square_23.grid(column=1, row=3, sticky=tk.NW, padx=1, pady=1)
square_24.grid(column=2, row=3, sticky=tk.NW, padx=1, pady=1)
square_25.grid(column=3, row=3, sticky=tk.NW, padx=1, pady=1)
square_26.grid(column=4, row=3, sticky=tk.NW, padx=1, pady=1)
square_27.grid(column=5, row=3, sticky=tk.NW, padx=1, pady=1)
square_28.grid(column=6, row=3, sticky=tk.NW, padx=1, pady=1)

forward_lable = tk.Label(
    master = frame_moveFoward,
    text="Enter Distance to travel",
    fg="black",
    bg="white"
)

entry = tk.Entry(
    master = frame_moveFoward,
    fg="black",
    bg="white", 
    width=50
)


btn_forward = tk.Button(
    master= frame_one,
    text="Forward",
    width=15,
    height=1,
    bg="black",
    fg="white"
    )

btn_left = tk.Button(
    master= frame_two,
    text="Turn Left",
    width=15,
    height=1,
    bg="black",
    fg="white"
    )

btn_right = tk.Button(
    master= frame_two,
    text="Turn Right",
    width=15,
    height=1,
    bg="black",
    fg="white"
    )

btn_back_OS = tk.Button(
    master= frame_three,
    text="Backward",
    width=15,
    height=1,
    bg="black",
    fg="white"
    )
btn_scan = tk.Button(
    master= frame_three,
    text="Scan",
    width=15,
    height=1,
    bg="black",
    fg="white"
    )

obj_ID = 1

def determind_box(x, y, color):
    tile_size = 55
    if(x <= tile_size & y <= tile_size):
        square_1.configure(bg=color)
        square_1.create_oval(tile_size-x, tile_size-y, x+10, y+10, fill='red')
    elif(x <= tile_size*2 & y <= tile_size):
        square_2.configure(bg=color)
        square_2.create_oval(tile_size-x, tile_size-y, tile_size-x+10, tile_size-y+10, fill='red')
    elif(x <= tile_size*3 & y <= tile_size):
        square_3.configure(bg=color)
    elif(x <= tile_size*4 & y <= tile_size):
        square_4.configure(bg=color)
    elif(x <= tile_size*5 & y <= tile_size):
        square_5.configure(bg=color)
    elif(x <= tile_size*6 & y <= tile_size):
        square_6.configure(bg=color)
    elif(x <= tile_size*7 & y <= tile_size):
        square_7.configure(bg=color)
    elif(x <= tile_size & y <= tile_size*2):
        square_8.configure(bg=color)
    elif(x <= tile_size*2 & y <= tile_size*2):
        square_9.configure(bg=color)
    elif(x <= tile_size*3 & y <= tile_size*2):
        square_10.configure(bg=color)
    elif(x <= tile_size*4 & y <= tile_size*2):
        square_11.configure(bg=color)
    elif(x <= tile_size*5 & y <= tile_size*2):
        square_12.configure(bg=color)
    elif(x <= tile_size*6 & y <= tile_size*2):
        square_13.configure(bg=color)
    elif(x <= tile_size*7 & y <= tile_size*2):
        square_14.configure(bg=color)
    elif(x <= tile_size & y <= tile_size*3):
        square_15.configure(bg=color)
    elif(x <= tile_size*2 & y <= tile_size*3):
        square_16.configure(bg=color)
    elif(x <= tile_size*3 & y <= tile_size*3):
        square_17.configure(bg=color)
    elif(x <= tile_size*4 & y <= tile_size*3):
        square_18.configure(bg=color)
    elif(x <= tile_size*5 & y <= tile_size*3):
        square_19.configure(bg=color)
    elif(x <= tile_size*6 & y <= tile_size*3):
        square_20.configure(bg=color)
    elif(x <= tile_size*7 & y <= tile_size*3):
        square_21.configure(bg=color)
    elif(x <= tile_size & y <= tile_size*4):
        square_22.configure(bg=color)
    elif(x <= tile_size*2 & y <= tile_size*4):
        square_23.configure(bg=color)
    elif(x <= tile_size*3 & y <= tile_size*4):
        square_24.configure(bg=color)
    elif(x <= tile_size*4 & y <= tile_size*4):
        square_25.configure(bg=color)
    elif(x <= tile_size*5 & y <= tile_size*4):
        square_26.configure(bg=color)
    elif(x <= tile_size*6 & y <= tile_size*4):
        square_27.configure(bg=color)
    elif(x <= tile_size*7 & y <= tile_size*4):
        square_28.configure(bg=color)
        

def update_pos(cybot):
    global obj_ID
    index = cybot.readline().decode()
    x = int(index)
    #print("X pos " + str(index))
    index = cybot.readline().decode()
    y = int(index)
    #print("Y pos " + str(index))
    index = cybot.readline().decode()
    dir = index
    #print("Dir " + str(index))
    bumped = cybot.readline().decode()
    bumped = bumped.strip('\r').strip('\n').strip('\r')    
    if(bumped == 'y'):
        obj_list['OBJ'+ str(obj_ID)] = {'posX': x, 'posY': y, 'type': "crater"}
    if(bumped == 'c'):
        obj_list['OBJ'+ str(obj_ID)] = {'posX': x, 'posY': y, 'type': "crater"}
    obj_ID += 1
    print(obj_list)

def handle_forward(event):
    HOST = "192.168.1.1"  # The server's hostname or IP address
    PORT = 288        # The port used by the server
    cybot_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Create a socket object
    cybot_socket.connect((HOST, PORT))   # Connect to the socket  (Note: Server must first be running)
    cybot = cybot_socket.makefile("rbw", buffering=0)  # makefile creates a file object out of a socket:  https://pythontic.com/modules/socket/makefile
    if(entry.get() == ""):                    
        send_message = "f"
        cybot.write(send_message.encode()) # Convert String to bytes (i.e., encode), and send data to the server
    else:
        send_message = "w"
        cybot.write(send_message.encode())
        send_message = int(entry.get())
        send_message = chr(send_message)
        cybot.write(send_message.encode())
        entry.delete(0, tk.END)
    update_pos(cybot)    
    time.sleep(1) # Sleep for 2 seconds
    cybot.close()         # Close file object associated with the socket or UART
    cybot_socket.close()  # Close the socket (NOTE: comment out if using UART interface, only use for network socket option)


def handle_left(event):
    HOST = "192.168.1.1"  # The server's hostname or IP address
    PORT = 288        # The port used by the server
    cybot_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Create a socket object
    cybot_socket.connect((HOST, PORT))   # Connect to the socket  (Note: Server must first be running)
    cybot = cybot_socket.makefile("rbw", buffering=0)  # makefile creates a file object out of a socket:  https://pythontic.com/modules/socket/makefile 
    if(entry.get() == ""):                    
        send_message = "l"
        cybot.write(send_message.encode()) # Convert String to bytes (i.e., encode), and send data to the server
    else:
        send_message = "a"
        cybot.write(send_message.encode())
        send_message = int(entry.get())
        send_message = chr(send_message)
        cybot.write(send_message.encode())
        entry.delete(0, tk.END)
    update_pos(cybot)
    time.sleep(2) # Sleep for 2 seconds
    cybot_socket.close()  # Close the socket (NOTE: comment out if using UART interface, only use for network socket option)



def handle_right(event):
    HOST = "192.168.1.1"  # The server's hostname or IP address
    PORT = 288        # The port used by the server
    cybot_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Create a socket object
    cybot_socket.connect((HOST, PORT))   # Connect to the socket  (Note: Server must first be running)
    cybot = cybot_socket.makefile("rbw", buffering=0)  # makefile creates a file object out of a socket:  https://pythontic.com/modules/socket/makefile
                    
    if(entry.get() == ""):                    
        send_message = "r"
        cybot.write(send_message.encode()) # Convert String to bytes (i.e., encode), and send data to the server
    else:
        send_message = "d"
        cybot.write(send_message.encode())
        send_message = int(entry.get())
        send_message = chr(send_message)
        cybot.write(send_message.encode())
        entry.delete(0, tk.END)
    update_pos(cybot)
    time.sleep(2) # Sleep for 2 seconds
    cybot.close()         # Close file object associated with the socket or UART
    cybot_socket.close()  # Close the socket (NOTE: comment out if using UART interface, only use for network socket option)

def handle_back(event):
    HOST = "192.168.1.1"  # The server's hostname or IP address
    PORT = 288        # The port used by the server
    cybot_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Create a socket object
    cybot_socket.connect((HOST, PORT))   # Connect to the socket  (Note: Server must first be running)
    cybot = cybot_socket.makefile("rbw", buffering=0)  # makefile creates a file object out of a socket:  https://pythontic.com/modules/socket/makefile
                    
    if(entry.get() == ""):                    
        send_message = "b"
        cybot.write(send_message.encode()) # Convert String to bytes (i.e., encode), and send data to the server
    else:
        send_message = "s"
        cybot.write(send_message.encode())
        send_message = int(entry.get())
        send_message = chr(send_message)
        cybot.write(send_message.encode())
        entry.delete(0, tk.END)
    update_pos(cybot)
    time.sleep(2) # Sleep for 2 seconds
    cybot.close()         # Close file object associated with the socket or UART
    cybot_socket.close()  # Close the socket (NOTE: comment out if using UART interface, only use for network socket option)

def handle_scan(event):
    global obj_ID
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
            rx_message = cybot.readline()
            print(rx_message.decode())
            while(index > 0):
                rx_message = cybot.readline()
                print(rx_message.decode())
                angle = cybot.readline().decode()
                angle = int(angle.strip('/r'))
                distance = cybot.readline().decode()
                distance = int(distance.strip('/r'))
                width =cybot.readline().decode()
                width = int(width.strip('/r'))
                if(angle > 90):
                    angle -=90
                else:
                    angle = 90 -angle
                pos_x = int(x + math.sin(math.radians(angle)) * distance)
                pos_y = int(y + math.cos(math.radians(angle)) * distance)
                if( width <= 6):
                    obj_type = "rock"
                    determind_box(pos_x, pos_y, 'grey')
                else:
                    obj_type = "storm"
                    determind_box(pos_x, pos_y, 'orange')
                obj_list['OBJ' + str(obj_ID)] = {'posX': pos_x, 'posY': pos_y, 'type': obj_type}
                obj_ID +=1
                index -= 1
        else:
            rx_message = cybot.readline()
            print(rx_message.decode())
        i += 1
    time.sleep(2) # Sleep for 2 seconds
    cybot.close()         # Close file object associated with the socket or UART
    cybot_socket.close()  # Close the socket (NOTE: comment out if using UART interface, only use for network socket option)


btn_forward.pack()
btn_left.pack()
btn_right.pack()
btn_back_OS.pack()
btn_scan.pack()
forward_lable.pack()
entry.pack()
frame_moveFoward.pack(fill=tk.X)
frame_one.pack(fill=tk.X)
frame_two.pack(fill=tk.X)
frame_three.pack(fill=tk.X)
grid.pack()

btn_forward.bind("<Button-1>", handle_forward)
btn_left.bind("<Button-1>", handle_left)
btn_right.bind("<Button-1>", handle_right)
btn_back_OS.bind("<Button-1>", handle_back)
btn_scan.bind("<Button-1>", handle_scan)

#run Tkinter event loop so that the program continiously listens for events
#like button clicks or key pressed
window.mainloop()
