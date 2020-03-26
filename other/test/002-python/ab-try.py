
for i in range(10):
    try:
        a = 5/1
        continue
    except Exception as e:
        print(e)
    finally:
        print(i, "finally")
