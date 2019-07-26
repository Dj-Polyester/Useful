import elements as el
import tkinter.colorchooser as tkc
from tkinter import messagebox
from PIL import Image, ImageTk 
from classes import*

class Artmode(object):

	def __init__(self):	
		
		self.master = tk.Tk()
		self.master.configure(background='black')
		
		self.frame_top=tk.Frame(self.master)
		self.frame_top.pack(fill=tk.X)
		
		self.draw_zone = tk.Canvas(self.master,height=el.HEIGHT,width=el.WIDTH,bg='white')
		self.draw_zone.pack()

		self.frame_bottom=tk.Frame(self.master,relief=tk.RAISED)
		self.frame_bottom.pack(fill=tk.X,side=tk.BOTTOM)

		self.combobox=Combobox(self.frame_top,"Choose a brush",el.COMBOBOX_ITEMS)
		self.combobox.combobox.pack(side=tk.LEFT,padx=10,pady=10)
		
		self.thickness_slider=Slider(self.frame_bottom,[0,10],tk.HORIZONTAL)
		self.sliderx1=Slider(self.frame_bottom,[0,WIDTH],tk.HORIZONTAL)
		self.slidery1=Slider(self.frame_bottom,[0,HEIGHT],tk.VERTICAL)
		self.sliderx2=Slider(self.frame_bottom,[0,WIDTH],tk.HORIZONTAL)
		self.slidery2=Slider(self.frame_bottom,[0,HEIGHT],tk.VERTICAL)
		
		self.thickness_slider.slider.pack(side=tk.LEFT,padx=5,pady=5)
		self.sliderx1.slider.pack(side=tk.LEFT)
		self.slidery1.slider.pack(side=tk.LEFT)
		self.sliderx2.slider.pack(side=tk.LEFT)
		self.slidery2.slider.pack(side=tk.LEFT)
		
		
		self.history_combobox=Combobox(self.frame_top,"History",[])
		self.history_combobox.combobox.pack(side=tk.RIGHT,padx=5,pady=5)
		
		self.colorButton1=tk.Button(self.frame_top, command=self.getFillColor)
		self.ph_im1 = Image.open('circle_fill.png')
		self.ph_im1=self.ph_im1.resize(el.MINI_BUTTON_SIZE)
		self.ph_im1 = ImageTk.PhotoImage(self.ph_im1)
		self.colorButton1.config(image=self.ph_im1)
		self.colorButton1.pack(side=tk.LEFT,padx=10)
		
		self.colorButton2=tk.Button(self.frame_top, command=self.getOutlineColor)
		self.ph_im2 = Image.open('circle_outline.png')
		self.ph_im2=self.ph_im2.resize(el.MINI_BUTTON_SIZE)
		self.ph_im2 = ImageTk.PhotoImage(self.ph_im2)
		self.colorButton2.config(image=self.ph_im2)
		self.colorButton2.pack(side=tk.LEFT,padx=5)
		
		self.undoButton=tk.Button(self.frame_top, command=self.undo)
		self.ph_im3 = Image.open('undo.png')
		self.ph_im3=self.ph_im3.resize(el.MINI_BUTTON_SIZE)
		self.ph_im3 = ImageTk.PhotoImage(self.ph_im3)
		self.undoButton.config(image=self.ph_im3)
		self.undoButton.pack(side=tk.LEFT,padx=10)
		
		self.redoButton=tk.Button(self.frame_top, command=self.redo)
		self.ph_im4 = Image.open('redo.png')
		self.ph_im4=self.ph_im4.resize(el.MINI_BUTTON_SIZE)
		self.ph_im4 = ImageTk.PhotoImage(self.ph_im4)
		self.redoButton.config(image=self.ph_im4)
		self.redoButton.pack(side=tk.LEFT,padx=5)
		
		self.shapeButton=tk.Button(self.frame_top, command=self.submit_shape)
		self.ph_im5 = Image.open('submit_shape.png')
		self.ph_im5=self.ph_im5.resize(el.MINI_BUTTON_SIZE)
		self.ph_im5 = ImageTk.PhotoImage(self.ph_im5)
		self.shapeButton.config(image=self.ph_im5)
		self.shapeButton.pack(side=tk.LEFT,padx=5)
		
		self.menubar = tk.Menu(self.master)
		
		self.menu1 = tk.Menu(self.menubar, tearoff=0)
		self.menubar.add_cascade(label="File", menu=self.menu1)
		self.menu1.add_command(label="New", command=self.clear_all)
		self.menu1.add_command(label="Open", command=self.redo)
		self.menu1.add_separator()
		self.menu1.add_command(label="Quit", command=self.master.destroy)
		
		self.menu2 = tk.Menu(self.menubar, tearoff=0)
		self.menubar.add_cascade(label="Editor", menu=self.menu2)
		self.menu2.add_command(label="Undo", command=self.undo)
		self.menu2.add_command(label="Redo", command=self.redo)
		self.menu2.add_separator()
		self.menu2.add_command(label="Clear all", command=self.delete_all)
		
		self.master.config(menu=self.menubar)
		self.master.title('Draw\'em')

		self.setup()
		self.master.mainloop()

	def setup(self):
		self.tag_current=None
		self.COUNTER=1
		self.backup=None
		self.thickness=0
		self.coo_enabled(False)
		
		self.fillColor=""
		self.outlineColor=""
		
		self.line_start_x = None
		self.line_start_y = None

		self.circle_start_x = None
		self.circle_start_y = None

		self.redo_objects = []
		self.undo_objects = []
		
		self.undo_stack = []
		self.redo_stack = []
		
		self.history = []
		
		self.shapeButton.config(state="disabled")
		
		self.draw_zone.bind('<Button-1>', self.draw_start)
		self.draw_zone.bind('<B1-Motion>',self.draw_motion)
		self.draw_zone.bind('<ButtonRelease-1>',self.draw_end)
		
		self.history_combobox.combobox.bind("<<ComboboxSelected>>",self.behave_object)
		self.combobox.combobox.bind("<<ComboboxSelected>>",self.combobox_choose)
		
		self.thickness_slider.slider.bind("<Button-1>",self.set_width)
		self.thickness_slider.slider.bind("<B1-Motion>",self.set_width)
		self.thickness_slider.slider.bind("<ButtonRelease-1>",self.set_width)
		
		self.sliderx1.slider.bind("<Button-1>",self.coo_set)
		self.sliderx1.slider.bind("<B1-Motion>",self.coo_set)
		self.sliderx1.slider.bind("<ButtonRelease-1>",self.coo_set)
		
		self.slidery1.slider.bind("<Button-1>",self.coo_set)
		self.slidery1.slider.bind("<B1-Motion>",self.coo_set)
		self.slidery1.slider.bind("<ButtonRelease-1>",self.coo_set)
		
		self.sliderx2.slider.bind("<Button-1>",self.coo_set)
		self.sliderx2.slider.bind("<B1-Motion>",self.coo_set)
		self.sliderx2.slider.bind("<ButtonRelease-1>",self.coo_set)
		
		self.slidery2.slider.bind("<Button-1>",self.coo_set)
		self.slidery2.slider.bind("<B1-Motion>",self.coo_set)
		self.slidery2.slider.bind("<ButtonRelease-1>",self.coo_set)
	
	
	def submit_shape(self):
		self.coo_enabled(False)
		self.shapeButton.config(state="disabled")
	
	def coo_enabled(self,State):
		if State==True:
			self.sliderx1.slider.configure(state="normal")
			self.slidery1.slider.configure(state="normal")
			self.sliderx2.slider.configure(state="normal")
			self.slidery2.slider.configure(state="normal")
		else:
			self.sliderx1.slider.configure(state="disabled")
			self.slidery1.slider.configure(state="disabled")
			self.sliderx2.slider.configure(state="disabled")
			self.slidery2.slider.configure(state="disabled")
	
	def set_width(self,event):
		self.thickness=self.thickness_slider.slider.get()
		
		if self.shapeButton["state"]=="normal":
			self.draw_zone.delete(self.tag_current)
			if self.combobox_chosen=='line':
				self.draw_zone.create_line(self.x1,self.y1,self.x2,self.y2,tags=self.tag_current,fill=self.fillColor,width=self.thickness)
			elif self.combobox_chosen == 'circle':
				self.draw_zone.create_oval(self.x1,self.y1,self.x2,self.y2,tags=self.tag_current,fill=self.fillColor,outline=self.outlineColor,width=self.thickness)
			elif self.combobox_chosen=='box':
				self.draw_zone.create_rectangle(self.x1,self.y1,self.x2,self.y2,tags=self.tag_current,fill=self.fillColor,outline=self.outlineColor,width=self.thickness)
	def coo_set_default(self):
		self.sliderx1.slider.set(self.x1)
		self.slidery1.slider.set(self.y1)
		self.sliderx2.slider.set(self.x2)
		self.slidery2.slider.set(self.y2)
	
		
	def coo_set(self,event):
		self.x1=self.sliderx1.slider.get()
		self.y1=self.slidery1.slider.get()
		self.x2=self.sliderx2.slider.get()
		self.y2=self.slidery2.slider.get()
		
		if self.shapeButton["state"]=="normal":
			self.draw_zone.delete(self.tag_current)
			if self.combobox_chosen=='line':
				self.draw_zone.create_line(self.x1,self.y1,self.x2,self.y2,tags=self.tag_current,fill=self.fillColor,width=self.thickness)
			elif self.combobox_chosen == 'circle':
				self.draw_zone.create_oval(self.x1,self.y1,self.x2,self.y2,tags=self.tag_current,fill=self.fillColor,outline=self.outlineColor,width=self.thickness)
			elif self.combobox_chosen=='box':
				self.draw_zone.create_rectangle(self.x1,self.y1,self.x2,self.y2,tags=self.tag_current,fill=self.fillColor,outline=self.outlineColor,width=self.thickness)
		
	def clear_all(self):
		self.draw_zone.delete("all")
		
		setup(self)
		"""
		self.undo_stack=[]
		self.redo_stack=[]
		self.undo_objects=[]
		self.redo_objects=[]
		self.history=[]
			 
		self.history_combobox.combobox["values"]=self.history
		self.history_combobox.modify_text("History")
		
		self.shapeButton["state"]="disabled"
		coo_enabled(False)
		
		self.fillColor=""
		self.outlineColor=""
		"""
	
	def delete_all(self):
		self.draw_zone.delete("all")
		
		self.interval=range(len(undo_stack))
		for i in self.interval:
			self.tag_current=self.undo_stack.pop()
			self.redo_stack.append(self.tag_current)
			self.redo_objects.append(self.undo_objects.pop())
			
			self.tmp=str(self.COUNTER)+")"+self.tag_current+"-destroyed"
			self.history.append(self.tmp)
			
			self.COUNTER+=1

		self.history_combobox.combobox["values"]=tuple(self.history)
		self.history_combobox.modify_text("History")
		
		self.shapeButton.config(state="disabled")
		coo_enabled(False)
		
		
	
	def getFillColor(self):
		self.color = tkc.askcolor() 
		self.fillColor=self.color[1]

		if self.shapeButton["state"]=="normal":
			self.draw_zone.delete(self.tag_current)
			if self.combobox_chosen=='line': self.draw_zone.create_line(self.x1,self.y1,self.x2,self.y2,tags=self.tag_current,fill=self.fillColor,width=self.thickness)		
			elif self.combobox_chosen == 'circle': self.draw_zone.create_oval(self.x1,self.y1,self.x2,self.y2,tags=self.tag_current,fill=self.fillColor,outline=self.outlineColor,width=self.thickness)
			elif self.combobox_chosen=='box': self.draw_zone.create_rectangle(self.x1,self.y1,self.x2,self.y2,tags=self.tag_current,fill=self.fillColor,outline=self.outlineColor,width=self.thickness)   
    		
	def getOutlineColor(self):
		self.color = tkc.askcolor() 
		self.outlineColor=self.color[1]
    		
		if self.shapeButton["state"]=="normal":
			self.draw_zone.delete(self.tag_current)
			if self.combobox_chosen=='line': self.draw_zone.create_line(self.x1,self.y1,self.x2,self.y2,tags=self.tag_current,fill=self.fillColor,width=self.thickness)
			elif self.combobox_chosen == 'circle': self.draw_zone.create_oval(self.x1,self.y1,self.x2,self.y2,tags=self.tag_current,fill=self.fillColor,outline=self.outlineColor,width=self.thickness)
			elif self.combobox_chosen=='box': self.draw_zone.create_rectangle(self.x1,self.y1,self.x2,self.y2,tags=self.tag_current,fill=self.fillColor,outline=self.outlineColor,width=self.thickness)
	
	def combobox_choose(self,event):
		self.combobox_chosen=self.combobox.combobox.get()
		if self.shapeButton["state"]=="normal":
			self.draw_zone.delete(self.tag_current)
			if self.combobox_chosen=='line': self.draw_zone.create_line(self.x1,self.y1,self.x2,self.y2,tags=self.tag_current,fill=self.fillColor,width=self.thickness)		
			elif self.combobox_chosen == 'circle': self.draw_zone.create_oval(self.x1,self.y1,self.x2,self.y2,tags=self.tag_current,fill=self.fillColor,outline=self.outlineColor,width=self.thickness)
			elif self.combobox_chosen=='box': self.draw_zone.create_rectangle(self.x1,self.y1,self.x2,self.y2,tags=self.tag_current,fill=self.fillColor,outline=self.outlineColor,width=self.thickness)		
		
	def behave_object(self,event):
		#get tag_current
		self.tmp=self.history_combobox.combobox.get()
		self.index=self.tmp.find("-")
		self.tag_current=self.tmp[2:self.index]
		
		if self.tmp[self.index:]=="-created":
			self.undo(None)
		else:
			self.redo(None)		
		
	
	def line_start(self,event):
		self.line_start_x=event.x
		self.line_start_y=event.y
	def line_motion(self,event):
		self.draw_zone.delete('temp_line_objects')
		self.draw_zone.create_line(self.line_start_x,self.line_start_y,event.x,event.y,tags='temp_line_objects',fill=self.fillColor,width=self.thickness)
		
	def line_end(self,event):
		self.draw_zone.delete('temp_line_objects')
		self.tag_current="line("+str(self.COUNTER)+")"
		self.draw_zone.create_line(self.line_start_x,self.line_start_y,event.x,event.y,tags=self.tag_current,fill=self.fillColor,width=self.thickness)
		
		self.tmp=[self.line_start_x,self.line_start_y,event.x,event.y,self.fillColor,self.thickness]
		self.undo_objects.append(self.tmp)
		
		self.undo_stack.append(self.tag_current)
		self.line_end_x=event.x
		self.line_end_y=event.y
		
		self.coo_enabled(True)
		self.x1=self.line_start_x
		self.y1=self.line_start_y
		self.x2=self.line_end_x
		self.y2=self.line_end_y
		self.coo_set_default()

	def circle_start(self,event):
		self.circle_start_x = event.x
		self.circle_start_y = event.y
	
	def circle_motion(self,event):
		self.draw_zone.delete('temp_circle_objects')
		self.draw_zone.create_oval(self.circle_start_x,self.circle_start_y,event.x,event.y,tags='temp_circle_objects',fill=self.fillColor,outline=self.outlineColor,width=self.thickness)
	
	def circle_end(self,event):
		self.draw_zone.delete('temp_circle_objects')
		self.tag_current="circle("+str(self.COUNTER)+")"
		self.draw_zone.create_oval(self.circle_start_x,self.circle_start_y,event.x,event.y,tags=self.tag_current,fill=self.fillColor,outline=self.outlineColor,width=self.thickness)
		
		self.tmp=[self.circle_start_x,self.circle_start_y,event.x,event.y,self.fillColor,self.outlineColor,self.thickness]
		self.undo_objects.append(self.tmp)
		
		self.undo_stack.append(self.tag_current)
		self.circle_end_x=event.x
		self.circle_end_y=event.y
		
		self.coo_enabled(True)
		self.x1=self.circle_start_x
		self.y1=self.circle_start_y
		self.x2=self.circle_end_x
		self.y2=self.circle_end_y
		self.coo_set_default()
	
	def box_start(self,event):
		self.box_start_x = event.x
		self.box_start_y = event.y
	
	def box_motion(self,event):
		self.draw_zone.delete('temp_box_objects')  
		self.draw_zone.create_rectangle(self.box_start_x,self.box_start_y,event.x,event.y,tags='temp_box_objects',fill=self.fillColor,outline=self.outlineColor,width=self.thickness)		

	def box_end(self,event):
		self.draw_zone.delete('temp_box_objects')
		self.tag_current="box("+str(self.COUNTER)+")"
		self.draw_zone.create_rectangle(self.box_start_x,self.box_start_y,event.x,event.y,tags=self.tag_current,fill=self.fillColor,outline=self.outlineColor,width=self.thickness)
		
		self.tmp=[self.box_start_x,self.box_start_y,event.x,event.y,self.fillColor,self.outlineColor,self.thickness]
		self.undo_objects.append(self.tmp)
		
		self.undo_stack.append(self.tag_current)
		self.box_end_x=event.x
		self.box_end_y=event.y
		
		self.coo_enabled(True)
		self.x1=self.box_start_x
		self.y1=self.box_start_y
		self.x2=self.box_end_x
		self.y2=self.box_end_y
		self.coo_set_default()
		
		

	def point_start(self,event):
		x = self.draw_zone.create_line(event.x,event.y,event.x+1,event.y+1)
		self.Point_objects.append(x)

	def draw_start(self,event):

		if self.combobox_chosen=='line': self.line_start(event)

		elif self.combobox_chosen == 'circle': self.circle_start(event)
			
		elif self.combobox_chosen=='box': self.box_start(event)
			
		elif self.combobox_chosen=='point': self.point_start(event)
			
		else: messagebox.showinfo("No brush chosen", "Please choose a brush")
		
	def draw_motion(self,event):
		
		if self.combobox_chosen=='line':
			self.line_motion(event)
		elif self.combobox_chosen == 'circle':
			self.circle_motion(event)
		elif self.combobox_chosen == 'box':
			self.box_motion(event)
		
			
	def draw_end(self,event):
		
		if self.combobox_chosen=='line':
			self.line_end(event)
		elif self.combobox_chosen == 'circle':
			self.circle_end(event)
		elif self.combobox_chosen == 'box':
			self.box_end(event)
		
		self.tmp=str(self.COUNTER)+")"+self.tag_current+"-created"
		self.history.append(self.tmp)
		
		self.history_combobox.combobox["values"]=tuple(self.history)
		self.history_combobox.modify_text("History")
		
		self.COUNTER+=1
		
		self.shapeButton.config(state="normal")
		
		
		
	
		
	def undo(self,*args):
		if(self.undo_stack==[]): return
		
		if(args==()):
			self.tag_current=self.undo_stack.pop()
			
		self.object_current=self.undo_objects.pop()
		self.draw_zone.delete(self.tag_current)
	
		self.redo_stack.append(self.tag_current)
		self.redo_objects.append(self.object_current)
		
		self.tmp=str(self.COUNTER)+")"+self.tag_current+"-destroyed"
		self.history.append(self.tmp)
		
		self.history_combobox.combobox["values"]=tuple(self.history)
		self.history_combobox.modify_text("History")
		
		self.COUNTER+=1
		
		
		
	def redo(self,*args):
		
		if(self.redo_stack==[]): return
		
		if(args==()):
			
			self.tag_current=self.redo_stack.pop()
		
		print(self.tag_current)
		
		self.object_current=self.redo_objects.pop()
		if self.tag_current[:4]=="line":
			self.draw_zone.create_line(self.object_current[0],self.object_current[1],self.object_current[2],self.object_current[3],tags=self.tag_current,fill=self.object_current[4],width=self.object_current[5])
			
		elif self.tag_current[:6]=="circle":
			self.draw_zone.create_oval(self.object_current[0],self.object_current[1],self.object_current[2],self.object_current[3],tags=self.tag_current,fill=self.object_current[4],outline=self.object_current[5],width=self.object_current[6])
			
		elif self.tag_current[:3]=="box":
			self.draw_zone.create_rectangle(self.object_current[0],self.object_current[1],self.object_current[2],self.object_current[3],tags=self.tag_current,fill=self.object_current[4],outline=self.object_current[5],width=self.object_current[6])
			
		self.undo_stack.append(self.tag_current)
		self.undo_objects.append(self.object_current)
		
		self.tmp=str(self.COUNTER)+")"+self.tag_current+"-created"
		self.history.append(self.tmp)
		
		self.history_combobox.combobox["values"]=tuple(self.history)
		self.history_combobox.modify_text("History")
		
		self.COUNTER+=1
		
		

if __name__ == '__main__':
	ge = Artmode()
