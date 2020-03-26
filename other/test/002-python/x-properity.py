
class T:
    a = 1
    b = 2

    @property
    def c(self):
        return self.a * self.b


if __name__ == '__main__':
    a = T()
    print(a.c)
    a.a = 3
    print(a.c)
