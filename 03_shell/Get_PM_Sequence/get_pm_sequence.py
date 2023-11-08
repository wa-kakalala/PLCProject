import random

NUM_MAX = 65536
SEQUENCE_NUM = 1024
SEQUENCE_NEWLINE = 50

HALF_POST_P  = 1
P            = 2
M            = 3
HALF_FRONT_M = 4

PM_SEQUENCE = [
    HALF_POST_P,
    P,
    P,
    P,
    P,
    P,
    P,
    P,
    P,
    P,
    P,
    M,
    M,
    HALF_FRONT_M
]

random.seed(0)
p_sequence  = [ random.randint(1,NUM_MAX) for item in range(SEQUENCE_NUM) ]
m_sequence  = [ -item for item in p_sequence ]

En = 0
for p in p_sequence:
    En += p*P

pm_sequence = []
for seq in PM_SEQUENCE :
    if  seq == HALF_POST_P:
        pm_sequence += p_sequence[512:]
    elif seq == P:
        pm_sequence += p_sequence
    elif seq == M:
        pm_sequence += m_sequence
    elif seq == HALF_FRONT_M:
        pm_sequence += m_sequence[:512]
    else:
        print("err --> invalid seq !!!")

# write file to save
filename = "./pm_sequence.txt"
f = open(filename,'w')
f.write("P/M En:\n")
f.write("%d\n"%(En))

f.write("\n")
f.write("\n")

f.write("P Sequence: \n")
for p_index in range(len(p_sequence)):
    f.write("%d,\t"%(p_sequence[p_index]))
    if ( p_index + 1 ) % SEQUENCE_NEWLINE == 0:
        f.write("\n")

f.write("\n")
f.write("\n")

f.write("M Sequence: \n")
for m_index in range(len(m_sequence)):
    f.write("%d,\t"%(m_sequence[m_index]))
    if ( m_index + 1 ) % SEQUENCE_NEWLINE == 0:
        f.write("\n")

f.write("\n")
f.write("\n")

f.write("PM Sequence: \n")
for pm_index in range(len(pm_sequence)):
    f.write("%d,\t"%(pm_sequence[pm_index]))
    if ( pm_index + 1 ) % SEQUENCE_NEWLINE == 0:
        f.write("\n")

f.close()
