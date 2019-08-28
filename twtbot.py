from selenium import webdriver
from selenium.webdriver.common.keys import Keys
import time
import tkinter as tk

#feed your username password below, the hashtag that you want to surf in, and the how many times to scroll down the page 
#for UI, uncomment some of the lines below
USERNAME=
PASSWORD=
HASHTAG=
SCROLL_RATE=3

class TwitBot:
	def __init__(self,username,password):
		self.username=username
		self.password=password
		self.driver=webdriver.Firefox()
		
	def closeBrowser(self):
		self.driver.close()
	def login(self):

		bot=self.driver
		bot.get("https://twitter.com/")
		time.sleep(2)
		"""
		login_button = self.driver.find_element_by_xpath("//a[@href'/accounts/login']")
		login_button.click()
		time.sleep(2)
		"""
		usernameElem=bot.find_element_by_xpath("/html/body/div[1]/div/div[1]/div[1]/div[1]/form/div[1]/input")
		usernameElem.clear()
		usernameElem.send_keys(self.username)
		
		passwordElem=bot.find_element_by_xpath("/html/body/div[1]/div/div[1]/div[1]/div[1]/form/div[2]/input")
		passwordElem.clear()
		passwordElem.send_keys(self.password)
		passwordElem.send_keys(Keys.RETURN)
		time.sleep(2)

	def likeTwit(self,hashtag):
		bot=self.driver
		bot.get("https://twitter.com/search?q="+hashtag+"&src=typed_query")
		
		time.sleep(10)
		for i in range(SCROLL_RATE):
			bot.execute_script("window.scrollTo(0,document.body.scrollHeight)")
			time.sleep(2)
		
		hrefs=bot.find_elements_by_tag_name("a")
		tweets=[]
			
		for elem in hrefs:
			tmp_href=elem.get_attribute("href")
			if "/status/" in tmp_href: tweets.append(tmp_href)		

		for tweet in tweets:
			bot.get(tweet)
			bot.execute_script("window.scrollTo(0,document.body.scrollHeight)")
			time.sleep(3)
			try:
				tmp_button=bot.find_element_by_xpath("//div[@data-testid='like']")
#				"/html/body/div/div/div/div/main/div/div/div/div[1]/div/div[2]/div/section/div/div/div/div[1]/div/article/div/div[7]/div[3]/div"
				tmp_button.click()
				
				time.sleep(2)	
				
			except Exception as e:
				print(e)
				time.sleep(2)


def clear_text(event):
		selfVar=event.widget
		selfVar.delete(0,"end")

def get_info():
	
#	USERNAME=entry1.get()
#	PASSWORD=entry2.get()	
	personalTwit=TwitBot(USERNAME,PASSWORD)
#	root.destroy()
	personalTwit.login()
	personalTwit.likeTwit(HASHTAG)


if __name__ == "__main__":
	get_info()
#UI window
"""
root=tk.Tk()
root.geometry("600x600")

strVar1=tk.StringVar()
strVar1.set("Write the username")
entry1=tk.Entry(root,textvariable=strVar1)
entry1.bind("<Button-1>",clear_text)
entry1.grid(row=1,column=2,padx=10,pady=10)

strVar2=tk.StringVar()
strVar2.set("Write the password")
entry2=tk.Entry(root,textvariable=strVar2)
entry2.bind("<Button-1>",clear_text)
entry2.grid(row=2,column=2,padx=10,pady=10)

label1=tk.Label(root,text="Username:")
label1.grid(row=1,column=1,padx=10,pady=10)

label2=tk.Label(root,text="Password:")
label2.grid(row=2,column=1,padx=10,pady=10)



button=tk.Button(root,text="Submit",width=10,height=2,command=get_info)
button.grid(row=3,column=2,padx=10,pady=10)

root.mainloop()
"""



