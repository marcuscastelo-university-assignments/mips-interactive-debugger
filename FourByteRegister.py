class FourByteRegister:
    def __init__(self):
        self.value = ['\0' for i in range(4)]
        self.isInt = False

    def setValue(self,value):
        value = str(value)
        if(value.isdigit()):
            if (value > 2**31-1 or value < -2**31):
                print("Numero fora do tamanho máximo")
                return []
            for i in range(1,5): 
                self.value[5-i] = value & 255
                value >> 8
            self.isInt = True
        else:
            if(len(value)>4):
                print("WARNING: Estão sendo passados mais bytes que o permitido no registrador. Apenas 4 bytes são permetidos")
            for i in range(1,5):
                self.value[5-i] = value[i]
            self.isInt = False

    def getValue(self):
        if(self.isInt):
            number = 0
            for i in range(0,4): 
                number |= self.value[i]
                number << 8
            return number
        else:
            stringVal = ""
            for i in range(1,5):
                stringVal += self.value[5-i]
            return stringVal


