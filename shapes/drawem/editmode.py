from classes import*
from tkinter import messagebox
"""
###############################################################
from tkinter import *

class Editmode(object):

	DEFAULT_PEN_SIZE = 5.0
	DEFAULT_COLOR = 'black'


	def __init__(self):	
		self.master = Tk()	

		self.draw_zone = Canvas(self.master,HEIGHT,WIDTH,bg='white')
		self.draw_zone.pack()

		self.frame=Frame(self.master)
		self.frame.pack(side=LEFT)

		
		self.line_button = Button(self.frame, text='Line',command=self.set_tool_line)
		self.line_button.pack(side=LEFT)

		self.circle_button = Button(self.frame, text='Circle',command= self.set_tool_circle)
		self.circle_button.pack(side=LEFT)

		self.point_button = Button(self.frame, text='Point',command = self.set_tool_point)
		self.point_button.pack(side=LEFT)
		
		combobox=Combobox(frame,"choose a shape",["line","box"],tk.LEFT)
		
		self.menubar = Menu(self.master)
		self.menu1 = Menu(self.menubar, tearoff=0)
		self.menu1.add_command(label="Nouveau", command=self.alert)
		self.menu1.add_command(label="Ouvrir", command=self.alert)
		self.menu1.add_separator()
		self.menu1.add_command(label="Quitter", command=self.master.destroy)
		self.menubar.add_cascade(label="Fichier", menu=self.menu1)
		self.menu2 = Menu(self.menubar, tearoff=0)
		self.menu2.add_command(label="Undo", command=self.undo)

		self.menu2.add_command(label="Redo", command=self.alert)
		self.menubar.add_cascade(label="Editer", menu=self.menu2)

		self.master.config(menu=self.menubar)
		self.master.title('UI')

		self.setup()
		self.master.mainloop()	

	def setup(self):
		self.line_start_x = None
		self.line_start_y = None

		self.circle_start_x = None
		self.circle_start_y = None

		self.tool_option = 'line'

		self.Line_objects = []
		self.Circle_objects = []
		self.Point_objects = []
		self.stack = []	

		self.draw_zone.bind('<Button-1>', self.draw_start)
		self.draw_zone.bind('<B1-Motion>',self.draw_motion)
		self.draw_zone.bind('<ButtonRelease-1>',self.draw_end)


	def line_start(self,event):
		self.line_start_x=event.x
		self.line_start_y=event.y
	def line_motion(self,event):
		self.draw_zone.delete('temp_line_objects')
		self.draw_zone.create_line(self.line_start_x,self.line_start_y,event.x,event.y,fill=self.DEFAULT_COLOR,smooth=1,tags='temp_line_objects')
	def line_end(self,event):
		x=self.draw_zone.create_line(self.line_start_x,self.line_start_y,event.x,event.y,fill=self.DEFAULT_COLOR,smooth=1)
		self.Line_objects.append(x)
		self.stack.append(x)

	def circle_start(self,event):
		self.circle_start_x = event.x
		self.circle_start_y = event.y
	def circle_motion(self,event):
		self.draw_zone.delete('temp_circle_objects')   #sym de circle_end par rapport a circle_start
		#self.draw_zone.create_oval(event.x,event.y,(2*self.circle_start_x-event.x),(2*self.circle_start_y-event.y),tags='temp_circle_objects')
		self.draw_zone.create_oval((self.circle_start_x),(self.circle_start_y),event.x,event.y,fill=self.DEFAULT_COLOR,tags='temp_circle_objects')
	def circle_end(self,event):
		#x=self.draw_zone.create_oval(event.x,event.y,(2*self.circle_start_x-event.x),(2*self.circle_start_y-event.y))
		x=self.draw_zone.create_oval((self.circle_start_x),(self.circle_start_y),event.x,event.y,fill=self.DEFAULT_COLOR)
		self.Circle_objects.append(x)
		self.stack.append(x)

	def point_start(self,event):
		x = self.draw_zone.create_line(event.x,event.y,event.x+1,event.y+1)
		self.Point_objects.append(x)

	def set_tool_line(self):
		self.tool_option = 'line'
	def set_tool_circle(self):
		self.tool_option = 'circle'
	def set_tool_point(self):
		self.tool_option = 'point'

	def draw_start(self,event):
		if self.tool_option=='line':
			self.line_start(event)
		elif self.tool_option == 'circle':
			self.circle_start(event)
		elif self.tool_option=='point':
			self.point_start(event)

	def draw_motion(self,event):
		if self.tool_option=='line':
			self.line_motion(event)
		elif self.tool_option == 'circle':
			self.circle_motion(event)
	def draw_end(self,event):
		if self.tool_option=='line':
			self.line_end(event)
		elif self.tool_option == 'circle':
			self.circle_end(event)

	def undo(self):
		x = self.stack.pop()
		self.draw_zone.delete(x)		

	def alert(self):
		print('yo')

if __name__ == '__main__':
	ge = Editmode()
	
	
	
#################################################################
"""
from classes import*
import elements as el

root=tk.Tk()
canvas=tk.Canvas(root,width=WIDTH,height=HEIGHT,bg="white")
canvas.pack()

frame=tk.Frame(root)
frame.pack()

box=Box(canvas)
line=Line(canvas)

combobox=Combobox(frame,"choose a shape",["line","box"],tk.LEFT)

sliderx1=Slider(frame,[0,WIDTH],tk.HORIZONTAL,tk.LEFT)
slidery1=Slider(frame,[0,HEIGHT],tk.VERTICAL,tk.LEFT)
sliderx2=Slider(frame,[0,WIDTH],tk.HORIZONTAL,tk.LEFT)
slidery2=Slider(frame,[0,HEIGHT],tk.VERTICAL,tk.LEFT)

entry=Entry(frame,"write a color",tk.LEFT)

def sweep():
	if combobox.item=="box": box.sweep(None)
			
	elif combobox.item=="line": line.sweep(None)
		

def init_shape(event):
	coo=[sliderx1.item,slidery1.item,sliderx2.item,slidery2.item]
	
	entry.item=entry.strVar.get()
	
	if entry.item not in el.COLORS and entry.item is not "": messagebox.showinfo("Invalid color", "Please choose a valid type")
	
	if combobox.item=="box":
		
		box.sweep(None)
		box.display(None,coo,fill=entry.item)	
	elif combobox.item=="line":
		
		line.sweep(None)
		line.display(None,coo,fill=entry.item)
		
	else: messagebox.showinfo("Invalid shape", "Please choose  a shape")
	
	
def move_shape(event):
	
	
	combobox.item=combobox.combobox.get()
	sliderx1.item=sliderx1.slider.get()
	slidery1.item=slidery1.slider.get()
	sliderx2.item=sliderx2.slider.get()
	slidery2.item=slidery2.slider.get()
	
	if combobox.item=="box":
		
		coo=[sliderx2.item,slidery2.item,sliderx1.item,slidery1.item]
		box.sweep(None)
		box.display(None,coo,fill=entry.item)
			
	elif combobox.item=="line":
		
		coo=[sliderx1.item,slidery1.item,sliderx2.item,slidery2.item]
		line.sweep(None)
		line.display(None,coo,fill=entry.item)
		
	else: messagebox.showinfo("Invalid shape", "Please choose  a shape")
		
def delete_all():
	canvas.delete("all")
#bindings
clear_button=tk.Button(frame,text="clear",command=sweep)
clear_button.pack(side=tk.LEFT)
clearAll_button=tk.Button(frame,text="clear all",command=delete_all)
clearAll_button.pack(side=tk.LEFT)


combobox.combobox.bind("<<ComboboxSelected>>",move_shape)

sliderx1.slider.bind("<B1-Motion>",move_shape)
slidery1.slider.bind("<B1-Motion>",move_shape)
sliderx2.slider.bind("<B1-Motion>",move_shape)
slidery2.slider.bind("<B1-Motion>",move_shape)

entry.entry.bind("<Return>",init_shape)			
	
		
root.mainloop()

