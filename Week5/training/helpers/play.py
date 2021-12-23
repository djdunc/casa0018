#!/usr/bin/python

# run as python3 play.py <folder>

# This helper script will sequentially work through a list of files in 
# the sub-directory specified in the the argument and if it is a .wav 
# file it will use the pydub library to play the audio.
# To install pydub > pip install pydub
# (note: i also had to "brew reinstall ffmpeg")


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
        time.sleep(2)
        continue
    else:
        continue