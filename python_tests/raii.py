import time
import argparse

class Timer:
    def __init__(self):
        self.start = time.time()

    def __del__(self):
        self.end = time.time()
        print("Time elapsed:", self.end - self.start)

def test_timer(sleep_time):
    print('Test started')
    t = Timer()
        time.sleep(sleep_time)
    if True:
        t2 = Timer()
    print('Test ended')

parser = argparse.ArgumentParser(description = 'This tests the RAII functionality for a timer.')
parser.add_argument('--sleep', type=int, required=True, help='Time to sleep' )
args=parser.parse_args()
sleep_time=args.sleep

test_timer(sleep_time)



