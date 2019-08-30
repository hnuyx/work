
import json

def serialize(pyobj):
    r = json.dumps(pyobj)
    return r.encode("utf-8")

def deserialize(str):
    pyobj = json.loads(str)
    return pyobj

if __name__ == '__main__':
    s = '{"a": 1}'
    deserialize(s)
