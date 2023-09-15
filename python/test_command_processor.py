import unittest
import time

# Import the test class you created
from test_module import TestCommandProcessor

# Create a TestSuite and add the test cases
test_suite = unittest.TestSuite()
test_suite.addTest(unittest.makeSuite(TestCommandProcessor))

# Create a TestRunner
test_runner = unittest.TextTestRunner()

# Get the start time
start_time = time.time()

# Run the tests
result = test_runner.run(test_suite)

# Get the stop time
stop_time = time.time()

# Calculate the elapsed time
elapsed_time = stop_time - start_time

# Print the test results
print(f"Ran {result.testsRun} tests in {elapsed_time} seconds.")
print(f"Errors: {len(result.errors)}, Failures: {len(result.failures)}")

if result.wasSuccessful():
    print("All tests passed!")
else:
    print("Some tests failed.")
