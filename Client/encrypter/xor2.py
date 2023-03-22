def byte_xor(ba1, ba2):
    return bytes([_a ^ _b for _a, _b in zip(ba1, ba2)])

def doXor2(plainText, key):
    result = ''
    for i in range(len(plainText)):
        # c[i] = (p[i] ^ k[indx]) + 1
        indx = i
        if i > (len(key) - 1):
            indx = i % len(key)
        c = ord(byte_xor(plainText[i].encode(), key[indx].encode())) + 1
        result += '\\x' + c.to_bytes().hex() 
    
    p = ''
    for i in range(len(plainText)):
        p += '\\x' + plainText[i].encode().hex()
        
    k = ''
    for i in range(len(key)):
        k += '\\x' + key[i].encode().hex()
    
    print('PlainText> ' + p)
    print('\nKey> ' + k)
    print('\nResult> ' + result)
    print('---------------------------------------------------------')

if __name__ == '__main__':
    while True:
        plainText = input('Enter Plain Text> ')
        key = input('Enter Key> ')
        doXor2(plainText, key)
        
        # ThisIsAnUncrackableKey