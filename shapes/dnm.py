from classes import*
RADIUS=400

root=tk.Tk()
root.geometry("1500x1000") 



canvas=tk.Canvas(root,width=1500,height=800)
canvas.pack()

frame=tk.Frame(width=1500,height=200)
frame.pack()

slider=Slider(frame,[0,RADIUS],tk.HORIZONTAL,None)
slider.slider.pack()	

rect=Polygon(canvas)


	


def curve_shape(event):
	
	x1=100
	y1=100
	x2=500
	y2=500
	r=slider.item
	points = (x1+r, y1, x1+r, y1, x2-r, y1, x2-r, y1, x2, y1, x2, y1+r, x2, y1+r, x2, y2-r, x2, y2-r, x2, y2, x2-r, y2, x2-r, y2, x1+r, y2, x1+r, y2, x1, y2, x1, y2-r, x1, y2-r, x1, y1+r, x1, y1+r, x1, y1)
	
	rect.sweep(None)
	rect.display(None,points,fill="",outline="brown",width=5)
		
	

	
	
slider.slider.bind("<B1-Motion>",curve_shape)




def round_rectangle(x1, y1, x2, y2, r, **kwargs):    
    points = (x1+r, y1, x1+r, y1, x2-r, y1, x2-r, y1, x2, y1, x2, y1+r, x2, y1+r, x2, y2-r, x2, y2-r, x2, y2, x2-r, y2, x2-r, y2, x1+r, y2, x1+r, y2, x1, y2, x1, y2-r, x1, y2-r, x1, y1+r, x1, y1+r, x1, y1)
    return canvas.create_polygon(points, **kwargs, smooth=True)
   
#rect=round_rectangle(100,100,500,500,slider.slider.get(),fill="",outline="brown",width=5)   

root.mainloop()
   
   

