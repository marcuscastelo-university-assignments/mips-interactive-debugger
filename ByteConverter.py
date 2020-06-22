def from_string(value):
    l = [c for c in value]
    l.append('\0')
    l.reverse()
    return l

def from_int(value):
    if (value > 2**31-1 or value < -2**31): return []
    
    l = []
    for i in range(5):                
        l.append(value & 255)
        value >>= 8
    return l