

def sort(a):
    l = len(a)
    for i in range(l):
        for j in range(i+1, l):
            if a[i] > a[j]:
                t = a[i]
                a[i] = a[j]
                a[j] = t
