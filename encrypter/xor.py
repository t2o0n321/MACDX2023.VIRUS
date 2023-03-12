import sys, os

def byte_xor(ba1, ba2):
    return bytes([_a ^ _b for _a, _b in zip(ba1, ba2)])

while True:
    plainText = input('Enter Plain Text> ')
    result = ''
    for i in range(len(plainText)):
        xor_res = byte_xor(plainText[(i) % len(plainText)].encode(), chr(i).encode())
        result += '\\x' + xor_res.hex()
    print(result)