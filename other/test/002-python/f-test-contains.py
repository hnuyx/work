

class T:
    def __init__(self):
        pass
    def __contains__(self, key):
        return True


t = T()
a = 'a'
if a in t:
    print("be here")

