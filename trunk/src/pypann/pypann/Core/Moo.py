"""
Moo
"""

_moo_iter = 0

def moo():
    global _moo_iter

    if _moo_iter == 0:
        print """
        Moo 0
        """
    elif _moo_iter == 1:
        print """
        Moo 1
        """
    elif _moo_iter == 2:
        print """
        Moo 2
        """
    elif _moo_iter == 3:
        print """
        Moo 3
        """
    elif _moo_iter == 4:
        print """
        Moo 4
        """
    else:
        print """
        Moo 5
        """
    _moo_iter+=1

def test_Moo():
    for i in range(7):
        moo()

if __name__ == "__main__":
    test_Moo()

