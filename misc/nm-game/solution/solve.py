#!/usr/bin/env python3
from pwn import *

s = remote('localhost', 40001)

for i in range(15):
    s.recvuntil('...\n')
    while True:
        nums = list(map(lambda x: int(x), s.recvline(False).decode('ascii').split(' ')))
        grundy = 0
        for num in nums:
            grundy ^= num % 4
        for index, num in enumerate(nums):
            choice = (num - (num^grundy)) % 4
            if num - choice >= 0:
                break
        if i > 0:
            s.sendlineafter(b']: ', bytes(f'{index}', 'ascii'))
        s.sendlineafter(b']: ', bytes(f'{choice}', 'ascii'))
        res = s.recvline(False)
        if res == b'Won!':
            s.recvline()
            break;

s.interactive()
