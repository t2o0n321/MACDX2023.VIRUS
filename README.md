# MACDX2023.VIRUS
## Table of Contents
- [MACDX2023.VIRUS](#macdx2023virus)
    - [Table of Contents](#table-of-contents)
- [Client](#client)
    - [功能](#功能)
    - [字串加解密](#字串加解密)
- [Server](#server)
    - [介紹](#介紹)
    - [密訊加密](#密訊加密)
---
# Client
## 功能
- 自我複製
-  於註冊表註冊為開機啟動
- 做鍵盤側錄
- 接收C2指令
    - 傳送檔案(側錄檔)
    - 殭屍
## 字串加解密
- xor </br>
    ```python
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
    ```
- xor2 </br>
    ```python
    def byte_xor(ba1, ba2):
        return bytes([_a ^ _b for _a, _b in zip(ba1, ba2)])

    def doXor2(plainText, key):
        result = ''
        for i in range(len(plainText)):
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
    ```

# Server
我真的懶的規劃再寫了，所以 Code 很混亂，請見諒 哈哈
## 介紹
Linux-based 的簡單 C2 Server，可以監聽連線，功能如下: </br>
- 下載 Client 端做的 KeyLog
- 對 Client 端口下指令
## 密訊加密
- 使用 RC4