import serial
import time 
import threading
from tkinter import *
from tkinter import ttk
from tkinter import messagebox
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg, 
NavigationToolbar2Tk)
import Fx

command_queue = []
plot_flag = False
starting_time = time.time()
figure_canvas = None
figure_canvas_window = None
plot_weight = None

weight_data = [list(),list()]

max_load = 100
just_one_buzzer_com = False
last_max_load_state = False

is_homed = False
get_data_flag = False
move_dir = 0
all_data = []

def Serial_thread():
    global command_queue,just_one_buzzer_com,last_max_load_state,is_homed,all_data
    with serial.Serial('COM3', 9600, timeout=10) as ser:
        while True:
            if(ser.inWaiting()):
                data = ser.readline().decode('utf-8')
                data = data.strip()
                print(data)
                if data.find("simple"):
                    print("get the first data")
                    break
            
        while True:
            if(ser.inWaiting()):
                raw_data = ser.readline().decode('utf-8')
                raw_data = raw_data.strip()
                if raw_data == "OK!":
                    continue
                elif raw_data == "Homed!":
                    canvas1.itemconfig(is_home_led, fill='green')
                    is_homed = True
                else:
                    data = raw_data.split()
                    plot_new_data(data)
                    load_loc_text.set(data[3].split(":")[1])
                    load_ang_text.set(data[0].split(":")[1])
                    pitch_ang_text.set(data[2].split(":")[1])
                    roll_ang_text.set(data[1].split(":")[1])

                    if float(data[4].split(":")[1]) > max_load:
                        if last_max_load_state == 'smaler':
                            just_one_buzzer_com = False
                        if not just_one_buzzer_com:
                            just_one_buzzer_com = True
                            last_max_load_state = 'bigger'
                            command_queue.append("M1 O1")
                            canvas1.itemconfig(max_load_buzzer, fill='green')
                    else:
                        if last_max_load_state == 'bigger':
                            just_one_buzzer_com = False
                        if not just_one_buzzer_com:
                            just_one_buzzer_com = True
                            last_max_load_state = 'smaler'
                            command_queue.append("M1 O0")
                            canvas1.itemconfig(max_load_buzzer, fill='red')


                    if get_data_flag:
                        all_data.append(raw_data + ' ' + 'movedir:' + str(move_dir) + '\r\n')

            
            if command_queue:
                ser.write(str(str(command_queue[0]) + str('\n\r')).encode('utf-8'))
                command_queue.pop(0)














x = threading.Thread(target=Serial_thread, args=(), daemon=True)
x.start()





def home():
    command_queue.append("G28")

def m50():
    command_queue.append("M50")
    canvas1.itemconfig(is_reset_scale, fill='green')
    messagebox.showerror(title="title", message="message")
    

def report_data():
    command_queue.append("M105 t100")
    # start_plot()


def start_pid():
    try:
        command_queue.append("G10 P%f"%(float(load_textbox.get())))
        canvas1.itemconfig(is_pid, fill='green')
    except Exception as e:
        messagebox.showerror(title="Error In Start PID",message=e)

def set_roll_pitch():
    try:
        command_queue.append("M51 P%f R%f"%(float(pitch_ang_textbox_new.get()),float(roll_ang_textbox_new.get())))
    except Exception as e:
        messagebox.showerror(title="Error In Set Roll Pitch",message=e)


def set_max_load():
    global max_load
    try:
        max_load = float(max_load_textbox_new.get())
        max_load_text.set(max_load)
    except Exception as e:
        messagebox.showerror(title="Error In Set Roll Pitch",message=e)





def do_fuck_behnam():
    global is_homed,get_data_flag,move_dir
    is_homed = False
    command_queue.append("G28")
    while not is_homed: pass
    command_queue.append("M50")
    time.sleep(2)
    get_data_flag = True
    command_queue.append("M105 T100")
    time.sleep(1)
    command_queue.append("G90")
    _file = open(str(str(filename_textbox.get())+'.csv'),'a')
    for i in range(10):
        command_queue.append("G1 X70")
        move_dir = 1
        time.sleep(15)
        command_queue.append("G1 X0")
        move_dir = -1
        time.sleep(15)
    get_data_flag = False
    for line in all_data:
        _file.write(line)
    _file.close()




def save_data():
    y = threading.Thread(target=do_fuck_behnam, args=(), daemon=True)
    y.start()



def start_plot():
    global plot_flag,figure_canvas,figure_canvas_window,plot_weight
    
    plot_flag = True

    fig = Figure(figsize = (5, 5),
                dpi = 100)
  
    plot_weight = fig.add_subplot(111)
    
    plot_weight.set_xlabel('Time') 
    plot_weight.set_ylabel('Force') 
    plot_weight.set_title("Force-Time plot")
  
    figure_canvas = FigureCanvasTkAgg(fig,
                               master = canvas1)  

    figure_canvas_window = canvas1.create_window(800, 200, anchor=NW, window=figure_canvas.get_tk_widget())
    figure_canvas.draw()


def plot_new_data(data):
    global plot_weight,figure_canvas,weight_data
    if plot_flag: 
            _data = data[4].split(":")
            # print(weight_data)
            plot_weight.cla() 
            # range(10), dpts, marker='o', color='orange')
            weight_data[0].append(time.time()-starting_time)
            weight_data[1].append(round(float(_data[1]),1))
            
            if len(weight_data[0]) > 100:
                weight_data[0].pop(0)
                weight_data[1].pop(0)

            plot_weight.plot(weight_data[0],weight_data[1], color='orange')
            figure_canvas.draw()




def create_circle(x, y, r, canvasName):
    x0 = x - r
    y0 = y - r
    x1 = x + r
    y1 = y + r
    return canvasName.create_oval(x0, y0, x1, y1)



if __name__ == '__main__':
    main = Tk()
    main.attributes("-fullscreen", TRUE)



    screen_height = main.winfo_screenheight()
    screen_width = main.winfo_screenwidth()

    print(screen_height,screen_width)


    canvas1 = Canvas(main,width=screen_width, height=screen_height)
    canvas1.pack()
    canvas1.place(x=-1,y=-1)




    exit_btn = Button(canvas1, text='exit', width=10,
                height=2, bd='10', command=main.destroy)
    exit_btn_window = canvas1.create_window(1250, 10, anchor=NW, window=exit_btn)


    home_btn = Button(canvas1, text='home', width=10,
                height=2, bd='10', command=home)
    home_btn_window = canvas1.create_window(10, 10, anchor=NW, window=home_btn)
    
    reset_sacle_btn = Button(canvas1, text='reset scale', width=10,
                height=2, bd='10', command=m50)
    reset_sacle_btn_window = canvas1.create_window(10, 70, anchor=NW, window=reset_sacle_btn)

    

    
    canvas1.create_text(170,35,text="Is Home:")
    is_home_led = create_circle(230,35,15,canvas1)
    canvas1.itemconfig(is_home_led, fill='red')


    canvas1.create_text(170,100,text="Is Reset:")
    is_reset_scale = create_circle(230,100,15,canvas1)
    canvas1.itemconfig(is_reset_scale, fill='red')



    canvas1.create_text(40,170,text="Load")
    load_textbox = ttk.Entry(canvas1,width = 3) 
    canvas1.create_window(70, 170, window=load_textbox)
    canvas1.create_text(95,170,text="g")



    data_btn = Button(canvas1, text='start report data', width=15,
                height=2, bd='10', command=report_data)
    data_btn_window = canvas1.create_window(10, 200, anchor=NW, window=data_btn)
    
    pid_btn = Button(canvas1, text='start pid', width=15,
                height=2, bd='10', command=start_pid)
    pid_btn_window = canvas1.create_window(10, 260, anchor=NW, window=pid_btn)

    is_pid = create_circle(230,285,15,canvas1)
    canvas1.itemconfig(is_pid, fill='red')


    load_loc_text = StringVar()
    canvas1.create_text(60,340,text="weight location:")
    load_loc_textbox = ttk.Entry(canvas1,width = 5,state='readonly',textvariable=load_loc_text) 
    canvas1.create_window(130, 340, window=load_loc_textbox)
    
    load_ang_text = StringVar()
    canvas1.create_text(60,380,text="link angle:")
    load_ang_textbox = ttk.Entry(canvas1,width = 5,state='readonly',textvariable=load_ang_text) 
    canvas1.create_window(130, 380, window=load_ang_textbox)
    


    
    pitch_ang_text = StringVar()
    canvas1.create_text(490,340,text="pitch:")
    pitch_ang_textbox = ttk.Entry(canvas1,width = 5,state='readonly',textvariable=pitch_ang_text) 
    canvas1.create_window(530, 340, window=pitch_ang_textbox)
    pitch_ang_textbox_new = ttk.Entry(canvas1,width = 5) 
    canvas1.create_window(580, 340, window=pitch_ang_textbox_new)


    
    roll_ang_text = StringVar()
    canvas1.create_text(490,380,text="roll:")
    roll_ang_textbox = ttk.Entry(canvas1,width = 5,state='readonly',textvariable=roll_ang_text) 
    canvas1.create_window(530, 380, window=roll_ang_textbox)
    roll_ang_textbox_new = ttk.Entry(canvas1,width = 5) 
    canvas1.create_window(580, 380, window=roll_ang_textbox_new)


    set_btn = Button(canvas1, text='Set', width=5,
                height=1,bd="5", command=set_roll_pitch)
    set_btn_window = canvas1.create_window(615, 345, anchor=NW, window=set_btn)





    
    max_load_text = StringVar()    
    canvas1.create_text(480,440,text="max load:")
    max_load_textbox_new = ttk.Entry(canvas1,width = 5) 
    max_load_textbox = ttk.Entry(canvas1,width = 5,state='readonly',textvariable=max_load_text) 
    canvas1.create_window(530, 440, window=max_load_textbox)
    canvas1.create_window(580, 440, window=max_load_textbox_new)
    max_load_text.set("100")


    max_load_set_btn = Button(canvas1, text='Set', width=5,
                height=1,bd="5", command=set_max_load)
    max_load_set_btn_window = canvas1.create_window(615, 425, anchor=NW, window=max_load_set_btn)


    max_load_buzzer = create_circle(700,440,15,canvas1)
    canvas1.itemconfig(max_load_buzzer, fill='red')


    canvas1.create_text(580,550,text="file name:") 
    filename_textbox = ttk.Entry(canvas1,width = 10) 
    canvas1.create_window(650, 550, window=filename_textbox)


    save_btn = Button(canvas1, text='Save', width=10,
                height=1,bd="5", command=save_data)
    save_btn_window = canvas1.create_window(580, 580, anchor=NW, window=save_btn)



    start_plot()

    main.mainloop()