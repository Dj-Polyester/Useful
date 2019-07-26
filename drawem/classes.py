import tkinter as tk
import tkinter.ttk as ttk

WIDTH=1500
HEIGHT=1000



class Line:
	def __init__(self,Canvas):
		self.exists=False
		self.canvas=Canvas
		
	def sweep(self,event):
		if self.exists:
			self.canvas.delete(self.line)
			self.exists=False
	def display(self,event,coo,**kwargs):
		if not self.exists:
			self.line=self.canvas.create_line(coo[0],coo[1],coo[2],coo[3],**kwargs)
			self.exists=True
class Box:
	def __init__(self,Canvas):
		self.exists=False
		self.canvas=Canvas
		
	def sweep(self,event):
		if self.exists:
			self.canvas.delete(self.box)
			self.exists=False
	def display(self,event,coo,**kwargs):
		if not self.exists:
			self.box=self.canvas.create_rectangle(coo[0],coo[1],coo[2],coo[3],**kwargs)
			self.exists=True

class Polygon:
	def __init__(self,Canvas):
		self.exists=False
		self.canvas=Canvas
		
	def sweep(self,event):
		if self.exists:
			self.canvas.delete(self.box)
			self.exists=False
	def display(self,event,coo,**kwargs):
		if not self.exists:
			self.box=self.canvas.create_polygon(coo,**kwargs)
			self.exists=True

###########FORM TOOLS#################################################################################################################
class Entry:
	
	def clear_text(self,event):
		self.entry.delete(0,"end")

	def __init__(self,frame,text,**kwargs):
		
		self.strVar=tk.StringVar()
		self.strVar.set(text)
		self.entry=tk.Entry(frame,textvariable=self.strVar,**kwargs)
		
		self.entry.bind("<Button-1>",self.clear_text)
	
	def modify_text(self,text):
		self.entry["text"]=text
	
	
class Combobox:
			
	def __init__(self,frame,Text,Values,**kwargs):

		self.combobox=ttk.Combobox(frame,values=Values,**kwargs)
		self.combobox.set(Text)
	
	def modify_text(self,text):
		self.combobox.set(text)
	

class Slider:
			
	def __init__(self,frame,interval,Orient,**kwargs):
		
		self.item=0
		self.slider=tk.Scale(frame,from_=interval[0],to=interval[1],orient=Orient,**kwargs)
		
		
		
		
		
