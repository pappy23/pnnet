#
# Exception
#

class LogicException(Exception):
    pass

#
# Testing
#

import unittest

class ExceptionTestCase(unittest.TestCase):
    def runTest(self):
        try:
            raise LogicException("Test error occured")
        except LogicException as e:
            print e

#
# Main
#
if __name__ == "__main__":
    unittest.main()

