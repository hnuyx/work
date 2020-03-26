

try:
    a = 1/0
except ZeroDivisionError:
    print("be here")
except:
    raise

print("hi, i'm end")
