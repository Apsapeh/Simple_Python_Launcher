import time
print("File Two")

with open("test.txt", "w") as r:
	r.write("Hello World!!!")
r.close()

while True:
	print(2)
	time.sleep(5)
