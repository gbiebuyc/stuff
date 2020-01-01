import struct, math
from math import sin

NB_CHANNELS = 1
NB_BYTES = 2
FREQ = 4410
SECONDS = 60
SIZE = FREQ * SECONDS

header = struct.pack('<4sI8sIHHIIHH4sI',
    b'RIFF', 36 + SIZE * NB_BYTES * NB_CHANNELS,
    b'WAVEfmt ', 16, 1, NB_CHANNELS, FREQ,
    FREQ * NB_CHANNELS * NB_BYTES,
    NB_CHANNELS * NB_BYTES, NB_BYTES * 8,
    b'data', SIZE * NB_BYTES * NB_CHANNELS
)

left = [0] * SIZE
#right = [0] * SIZE
Amp = 1.0
t = 0
dt = 1 / FREQ
f = 110 # 440
omega = 2 * math.pi * f

for i in range(SIZE):
    # left[i] += Amp * sin(omega*t)

    # for j in range(1, 7):
    #     left[i] = left[i] + Amp * sin(omega*t*j) / (j*(1+t**j))

    for j in range(1, 7):
        left[i] = left[i] + Amp / (j**2 * (1+t**j)) * (sin(j*omega*t) + sin(j*omega*pow(2, 4/12)*t) + sin(j*omega*pow(2, 7/12)*t))
    t += dt

max = 0
for i in range(SIZE):
    if abs(left[i]) > max: max = abs(left[i])
print(max)
max += .1

data = bytearray()
for i in range(SIZE):
    data += struct.pack('<h', int(left[i] / max * 0x8000))

with open('synth.wav', 'wb') as f:
    f.write(header + data)
