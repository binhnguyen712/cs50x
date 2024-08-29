while True:
    try:
        height = int(input("Height: "))
        if 0 < height <= 8:
             break
    except ValueError:
        print("Must be integer between 0 and 8.")

for i in range(height):
    print(" "*(height - i-1) + "#"*(i+1))
