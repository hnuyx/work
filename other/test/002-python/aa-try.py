
try:
    try:
        i = 5 / 0
    except IOError:
        print("io-error")
    except ZeroDivisionError:
        print("n/0 error")
        raise IOError("12345")
    except Exception:
        print("exception")
    else:
        print("correct")
    finally:
        print("finally")
except IOError as e:
    print("2-io-error", e)
except ZeroDivisionError:
    print("2-n/0 error")
except Exception:
    print("2-exception")
else:
    print("2-correct")
finally:
    print("2-finally")

