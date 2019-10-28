
import pickle


class T:
    def __init__(self):
        pass


def init(t):
    t.a = 'aaaa'
    t.b = 2222
    t.c = 'cccc'

def use(t):
    print(t.a, t.b, t.c)


def v_init():
    t = T()
    init(t)
    return pickle.dumps(t)

def v_use(tstr):
    #print("SD.py tstr:", tstr)
    t = pickle.loads(tstr)
    #use(t)


if __name__ == '__main__':
    tstr = v_init()
    v_use(tstr)
