import unittest
import hw1
import math


class TestFormula(unittest.TestCase):
    def testFormula(self):
        for n in range(1, 1026):
            logVal = math.log(n, 2)
            self.assertEqual(hw1.h(n), int(math.floor(logVal)))
            self.assertEqual(hw1.d(n), int(math.ceil(logVal)))

if __name__ == "__main__":
    unittest.main()
