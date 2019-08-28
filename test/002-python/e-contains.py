

class A:
    def __contains__(self, key):
        return True

if __name__ == '__main__':
    t = A()
    if "123" in t:
        print("be here")
