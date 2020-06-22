import ByteConverter

class Stack:
    def __init__(self, size):
        self.stack = []
        self.sp = size-1

    def insert_int(self, value):
        bl = ByteConverter.from_int(value)
        for i in range(len(bl)):
            self.stack[self.sp+i] = bl[i]
    
    def insert_string(self, value):
        bl = ByteConverter.from_string(value)
        for i in range(len(bl)):
            self.stack[self.sp+i] = bl[i]

    def insert_bytes(self, bArr):
        for i in range(len(bArr)):
            self.stack[self.sp+i] = bArr[i]