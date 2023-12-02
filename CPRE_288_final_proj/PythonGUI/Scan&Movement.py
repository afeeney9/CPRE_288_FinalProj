import tkinter as tk
from tkinter import Canvas
from winsound import PlaySound

# Serial library:  https://pyserial.readthedocs.io/en/latest/shortintro.html 
import serial
import math
import time # Time library   
# Socket library:  https://realpython.com/python-sockets/  
# See: Background, Socket API Overview, and TCP Sockets  
import socket    

import os  
import numpy as np
import matplotlib.pyplot as plt

absolute_path = os.path.dirname(__file__) # Absoult path to this python script
relative_path = "./"   # Path to sensor data file relative to this python script (./ means data file is in the same directory as this python script)
full_path = os.path.join(absolute_path, relative_path) # Full path to sensor data file
filename = 'sensor-scan.txt' # Name of file you want to store sensor data from your sensor scan command


#global vars x,y track cybots current pos and dir tracks direction cybot is currently facing 
#objId is equal to number of objects 
x=275
y=275

dir = 0

obj_list = {}


window = tk.Tk()
window.geometry("900x500")

frame_moveFoward = tk.Frame()
frame_one = tk.Frame()
frame_two = tk.Frame()
frame_three = tk.Frame()
frame_four = tk.Frame()

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

square_1.grid(column=0, row=3, sticky=tk.NW, padx=1, pady=1)
square_2.grid(column=1, row=3, sticky=tk.NW, padx=1, pady=1)
square_3.grid(column=2, row=3, sticky=tk.NW, padx=1, pady=1)
square_4.grid(column=3, row=3, sticky=tk.NW, padx=1, pady=1)
square_5.grid(column=4, row=3, sticky=tk.NW, padx=1, pady=1)
square_6.grid(column=5, row=3, sticky=tk.NW, padx=1, pady=1)
square_7.grid(column=6, row=3, sticky=tk.NW, padx=1, pady=1)

square_8.grid(column=0, row=2, sticky=tk.NW,  padx=1, pady=1)
square_9.grid(column=1, row=2, sticky=tk.NW,  padx=1, pady=1)
square_10.grid(column=2, row=2, sticky=tk.NW, padx=1, pady=1)
square_11.grid(column=3, row=2, sticky=tk.NW, padx=1, pady=1)
square_12.grid(column=4, row=2, sticky=tk.NW, padx=1, pady=1)
square_13.grid(column=5, row=2, sticky=tk.NW, padx=1, pady=1)
square_14.grid(column=6, row=2, sticky=tk.NW, padx=1, pady=1)

square_15.grid(column=0, row=1, sticky=tk.NW, padx=1, pady=1)
square_16.grid(column=1, row=1, sticky=tk.NW, padx=1, pady=1)
square_17.grid(column=2, row=1, sticky=tk.NW, padx=1, pady=1)
square_18.grid(column=3, row=1, sticky=tk.NW, padx=1, pady=1)
square_19.grid(column=4, row=1, sticky=tk.NW, padx=1, pady=1)
square_20.grid(column=5, row=1, sticky=tk.NW, padx=1, pady=1)
square_21.grid(column=6, row=1, sticky=tk.NW, padx=1, pady=1)

square_22.grid(column=0, row=0,sticky=tk.NW,  padx=1, pady=1)
square_23.grid(column=1, row=0, sticky=tk.NW, padx=1, pady=1)
square_24.grid(column=2, row=0, sticky=tk.NW, padx=1, pady=1)
square_25.grid(column=3, row=0, sticky=tk.NW, padx=1, pady=1)
square_26.grid(column=4, row=0, sticky=tk.NW, padx=1, pady=1)
square_27.grid(column=5, row=0, sticky=tk.NW, padx=1, pady=1)
square_28.grid(column=6, row=0, sticky=tk.NW, padx=1, pady=1)

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

btn_play = tk.Button(
    master= frame_three,
    text="Play Sound",
    width=15,
    height=1,
    bg="black",
    fg="white"
    )
cybot_pos = tk.Label(
    master = frame_four,
    text="Cybot is at: " + str(x) + ", " + str(y),
    width=80,
    height= 3,
    fg="black",
    bg="white"
)
object_list = tk.Label(
    master = frame_four,
    text="Objects located at:",
    fg="black",
    bg="white"
)

obj_ID = 1
def add_object(new_obj):
    s = object_list.cget("text")
    s += new_obj
    object_list.config(text = s)

def determind_box(x, y, color):
    tile_size = 550
    print("x is " + str(x) + " y is " + str(y))
    if(x <= tile_size and y <= tile_size):
        square_1.configure(bg=color)
    elif(x <= tile_size*2 and y <= tile_size):
        square_2.configure(bg=color)
    elif(x <= tile_size*3 and y <= tile_size):
        square_3.configure(bg=color)
    elif(x <= tile_size*4 and y <= tile_size):
        square_4.configure(bg=color)
    elif(x <= tile_size*5 and y <= tile_size):
        square_5.configure(bg=color)
    elif(x <= tile_size*6 and y <= tile_size):
        square_6.configure(bg=color)
    elif(x <= tile_size*7 and y <= tile_size):
        square_7.configure(bg=color)
    elif(x <= tile_size and y <= tile_size*2):
        square_8.configure(bg=color)
    elif(x <= tile_size*2 and y <= tile_size*2):
        square_9.configure(bg=color)
    elif(x <= tile_size*3 and y <= tile_size*2):
        square_10.configure(bg=color)
    elif(x <= tile_size*4 and y <= tile_size*2):
        square_11.configure(bg=color)
    elif(x <= tile_size*5 and y <= tile_size*2):
        square_12.configure(bg=color)
    elif(x <= tile_size*6 and y <= tile_size*2):
        square_13.configure(bg=color)
    elif(x <= tile_size*7 and y <= tile_size*2):
        square_14.configure(bg=color)
    elif(x <= tile_size and y <= tile_size*3):
        square_15.configure(bg=color)
    elif(x <= tile_size*2 and y <= tile_size*3):
        square_16.configure(bg=color)
    elif(x <= tile_size*3 and y <= tile_size*3):
        square_17.configure(bg=color)
    elif(x <= tile_size*4 and y <= tile_size*3):
        square_18.configure(bg=color)
    elif(x <= tile_size*5 and y <= tile_size*3):
        square_19.configure(bg=color)
    elif(x <= tile_size*6 and y <= tile_size*3):
        square_20.configure(bg=color)
    elif(x <= tile_size*7 and y <= tile_size*3):
        square_21.configure(bg=color)
    elif(x <= tile_size and y <= tile_size*4):
        square_22.configure(bg=color)
    elif(x <= tile_size*2 and y <= tile_size*4):
        square_23.configure(bg=color)
    elif(x <= tile_size*3 and y <= tile_size*4):
        square_24.configure(bg=color)
    elif(x <= tile_size*4 and y <= tile_size*4):
        square_25.configure(bg=color)
    elif(x <= tile_size*5 and y <= tile_size*4):
        square_26.configure(bg=color)
    elif(x <= tile_size*6 and y <= tile_size*4):
        square_27.configure(bg=color)
    elif(x <= tile_size*7 and y <= tile_size*4):
        square_28.configure(bg=color)
        

def update_pos(cybot):
    global obj_ID
    global dir
    global x 
    global y
    index = cybot.readline().decode()
    x = float(index)
    print("X pos " + str(index))
    index = cybot.readline().decode()
    y = float(index)
    #print("Y pos " + str(index))
    index = cybot.readline().decode()
    dir = index
    #print("Dir " + str(index))
    bumped = cybot.readline().decode()
    bumped = bumped.strip('\r').strip('\n').strip('\r')    
    print(bumped)
    if(bumped == 'y'):
        obj_list['OBJ'+ str(obj_ID)] = {'posX': x, 'posY': y, 'type': "crater"}
        obj_ID += 1
        determind_box(x, y, 'brown')
        add_object("\nOBJ" + str(obj_ID) + " at position x:" + str(x) + " , y:" + str(y) + " object is a crater")
    if(bumped == 'h'):
        obj_list['OBJ'+ str(obj_ID)] = {'posX': x, 'posY': y, 'type': "hole"}
        obj_ID += 1
        angle = int(dir)
        pos_x = int(math.cos(math.radians(angle)) * 150) + x
        pos_y = int(math.sin(math.radians(angle)) * 150) + y
        determind_box(pos_x, pos_y, 'black')
        add_object("\nOBJ" + str(obj_ID) + " at position x:" + str(pos_x) + " , y:" + str(pos_y) + " object is a hole" )
    cybot_pos.config(text = "Cybot is at: " + str(x) + ", " + str(y) + " direction: " + str(dir))
    cybot_pos.config(justify='center')
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
        send_message = int(entry.get())*0.9
        send_message = chr(int(send_message))
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
    print("right")                
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
    print("right")                
    update_pos(cybot)
    print("right")         
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
        send_message = int(entry.get())*0.9
        send_message = chr(send_message)
        cybot.write(int(send_message.encode()))
        entry.delete(0, tk.END)
    update_pos(cybot)
    time.sleep(2) # Sleep for 2 seconds
    cybot.close()         # Close file object associated with the socket or UART
    cybot_socket.close()  # Close the socket (NOTE: comment out if using UART interface, only use for network socket option)

def play_sound(event):
    HOST = "192.168.1.1"  # The server's hostname or IP address
    PORT = 288        # The port used by the server
    cybot_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Create a socket object
    cybot_socket.connect((HOST, PORT))   # Connect to the socket  (Note: Server must first be running)
    cybot = cybot_socket.makefile("rbw", buffering=0)  # makefile creates a file object out of a socket:  https://pythontic.com/modules/socket/makefile
    send_message = "g"
    cybot.write(send_message.encode()) # Convert String to bytes (i.e., encode), and send data to the server
    time.sleep(2) # Sleep for 2 seconds
    cybot.close()         # Close file object associated with the socket or UART
    cybot_socket.close()  # Close the socket (NOTE: comment out if using UART interface, only use for network socket option)


def handle_scan(event):
    global obj_ID
    global dir
    global x 
    global y
    HOST = "192.168.1.1"  # The server's hostname or IP address
    PORT = 288        # The port used by the server
    cybot_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Create a socket object
    cybot_socket.connect((HOST, PORT))   # Connect to the socket  (Note: Server must first be running)
    cybot = cybot_socket.makefile("rbw", buffering=0)  # makefile creates a file object out of a socket:  https://pythontic.com/modules/socket/makefile
                    
    send_message = "m"
    cybot.write(send_message.encode()) # Convert String to bytes (i.e., encode), and send data to the server
    i = 0
    file_object = open(full_path + filename,'w')
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
                
                # print("distance before " + str(distance))
                # if(angle > 90):
                #     distance = pow(distance, 2) + 169 - (2*distance*13*(math.cos(270-angle)))
                # else:
                #     distance = pow(distance, 2) + 169 - (2*distance*13*(math.cos(angle+90)))
                # distance = math.sqrt(distance)

                # angle=(pow(distance, 2) + 196 + pow(new_dist, 2))/(2 *13)
                print("distance " + str(distance))
                print(angle)
                print(dir)
                angle = angle + int(dir) - 90 -14
                print(angle)
                print("x = " + str(x) + "y = " + str(y))
                pos_x = int(math.cos(math.radians(angle)) * (distance*10)) + x
                pos_y = int(math.sin(math.radians(angle)) * (distance*10)) + y
                print("x = " + str(pos_x) + "y = " + str(pos_y))
                # is_new = True
                # for obj in obj_list:1

                #     if(pos_x < int(obj.posX)+10 & pos_x > int(obj.posX) -10 & pos_y < (int(obj.posY) +10) & pos_y > (int(obj.posY)-10)):
                #         is_new = False
                #         break
                    
                # if(is_new):
                #     if( width <= 6):
                #         obj_type = "rock"
                #         determind_box(pos_x, pos_y, 'grey')
                #     else:
                #         obj_type = "storm"
                #         determind_box(pos_x, pos_y, 'orange')
                #     obj_list['OBJ' + str(obj_ID)] = {'posX': pos_x, 'posY': pos_y, 'type': obj_type}
                #     add_object("\nOBJ" + str(obj_ID) + " at position x:" + str(pos_x) + " , y:" + str(pos_y) + " object is a " + obj_type )
                #     obj_ID +=1
               #width varies depending on bot
                if( width < 7):

                    obj_type = "rock"
                    determind_box(pos_x, pos_y, 'grey')
                else:
                    obj_type = "storm"
                    determind_box(pos_x, pos_y, 'orange')
                obj_list['OBJ' + str(obj_ID)] = {'posX': pos_x, 'posY': pos_y, 'type': obj_type}
                add_object("\nOBJ" + str(obj_ID) + " at position x:" + str(pos_x) + " , y:" + str(pos_y) + " object is a " + obj_type )
                obj_ID +=1
                index -= 1
                
        else:
            rx_message = cybot.readline()
            if(i>0):
                file_object.write(rx_message.decode())
            print(i)
            print(rx_message.decode().strip('/n'))
        i += 1
    time.sleep(2) # Sleep for 2 seconds
    file_object.close()

    angle_degrees = [] # Initially empty
    angle_radians = [] # Initially empty
    distance = []      # Initially empty
    # Open file containing CyBot sensor scan from 0 - 180 degrees
    print("-----------------")
    file_object = open(full_path + filename,'r') # Open the file: file_object is just a variable for the file "handler" returned by open()
    #file_header = file_object.readline() # Read and store the header row (i.e., 1st row) of the file into file_headerm
    file_data = file_object.readlines()  # Read the rest of the lines of the file into file_data
    file_object.close() # Important to close file one you are done with it!!
    # For each line of the file split into columns, and assign each column to a variable
    for line in file_data: 
            if not line.isspace():
                data = line.split()    # Split line into columns (by default delineates columns by whitespace)                       
                angle_degrees.append(float(data[0]))  # Column 0 holds the angle at which distance was measured
                distance.append(float(data[1]))       # Column 1 holds the distance that was measured at a given angle       
    # Convert python sequence (list of strings) into a numpy array
    angle_degrees = np.array(angle_degrees) # Avoid "TypeError: can't multiply sequence by non-int of type float"
                                            # Link for more info: https://www.freecodecamp.org/news/typeerror-cant-multiply-sequence-by-non-int-of-type-float-solved-python-error/                                      
    angle_radians = (np.pi/180) * angle_degrees # Convert degrees into radians
    # Create a polar plot
    fig, ax = plt.subplots(subplot_kw={'projection': 'polar'}) # One subplot of type polar
    ax.plot(angle_radians, distance, color='r', linewidth=4.0)  # Plot distance verse angle (in radians), using red, line width 4.0
    ax.set_xlabel('Distance (m)', fontsize = 14.0)  # Label x axis
    ax.set_ylabel('Angle (degrees)', fontsize = 14.0) # Label y axis
    ax.xaxis.set_label_coords(0.5, 0.15) # Modify location of x axis label (Typically do not need or want this)
    ax.tick_params(axis='both', which='major', labelsize=14) # set font size of tick labels
    ax.set_rmax(250)                    # Saturate distance at 2.5 meters
    ax.set_rticks([50, 100, 150, 200, 250])   # Set plot "distance" tick marks at .5, 1, 1.5, 2, and 2.5 meters
    ax.set_rlabel_position(-22.5)     # Adjust location of the radial labels
    ax.set_thetamax(180)              # Saturate angle to 180 degrees
    ax.set_xticks(np.arange(0,np.pi+.1,np.pi/4)) # Set plot "angle" tick marks to pi/4 radians (i.e., displayed at 45 degree) increments
                                            # Note: added .1 to pi to go just beyond pi (i.e., 180 degrees) so that 180 degrees is displayed
    ax.grid(True)                     # Show grid lines
    # Create title for plot (font size = 14pt, y & pad controls title vertical location)
    ax.set_title("Polar Plot of CyBot Sensor Scan from 0 to 180 Degrees", size=14, y=1.0, pad=-24) 
    plt.show()

    cybot.close()         # Close file object associated with the socket or UART
    cybot_socket.close()  # Close the socket (NOTE: comment out if using UART interface, only use for network socket option)


btn_play.pack()
btn_forward.pack()
btn_left.pack()
btn_right.pack()
btn_back_OS.pack()
btn_scan.pack()
forward_lable.pack()
entry.pack()
cybot_pos.pack()
object_list.pack()
frame_moveFoward.pack(fill=tk.X)
frame_one.pack(fill=tk.X)
frame_two.pack(fill=tk.X)
frame_three.pack(fill=tk.X)
grid.pack()
frame_four.pack(fill=tk.X)

btn_play.bind("<Button-1>", play_sound)
btn_forward.bind("<Button-1>", handle_forward)
btn_left.bind("<Button-1>", handle_left)
btn_right.bind("<Button-1>", handle_right)
btn_back_OS.bind("<Button-1>", handle_back)
btn_scan.bind("<Button-1>", handle_scan)

#run Tkinter event loop so that the program continiously listens for events
#like button clicks or key pressed
window.mainloop()
