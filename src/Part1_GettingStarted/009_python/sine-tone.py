import numpy as np
from scipy.io.wavfile import write
freq = 400
x = np.sin(np.arange(0, np.pi * freq*2, (np.pi * freq * 2)/ 44100))
write('sine_400Hz.wav', 44100, x * 0.5)