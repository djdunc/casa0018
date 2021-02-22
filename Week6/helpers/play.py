#!/usr/bin/python

# run as python play.py <folder>



from pydub import AudioSegment
from pydub.playback import play
import os
import sys
import time

directory = os.path.dirname(os.path.realpath(__file__))
print(directory)
directory = os.path.join(directory, str(sys.argv[1]))
print(directory)


for filename in os.listdir(directory):
    if filename.endswith(".wav"):
        song = AudioSegment.from_wav(os.path.join(directory, filename))
        play(song)
        time.sleep(10)
        continue
    else:
        continue