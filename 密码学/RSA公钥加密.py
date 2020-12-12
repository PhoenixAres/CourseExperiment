'''扩展欧几里得算法求乘法逆元'''
def exgcd(a, b):    
    x = 1; y = 0; g = a
    if b == 0: 
        return g, x, y
    else:
        g, x1, y1 = exgcd(b, a % b)
        x = y1
        y = x1 - a // b * y1
        return g, x, y
'''设置公钥'''
def set_public_key():
    p = 1000000009
    q = 1610612741
    n = p * q
    m = (p-1) * (q-1)
    return 65537, m, n
'''获取私钥'''
def get_private_key(e, m):
    return exgcd(e, m)[1]
'''快速幂'''
def ksm(a, k, mod):
    ret = 1; a = a%mod
    while k:
        if k & 1: ret = ret*a%mod
        a = a*a%mod
        k = k >> 1
    return ret

def setD():
    D = {}
    for i in range(26):
        j = chr(ord('a')+i)
        D[j] = str(i+10)
    for i in range(10):
        D[str(i)] = str(i+36)
    D[' '] = '46'
    return D

def setD_inv(D):
    D_inv = {}
    for i in D.items():
        D_inv[i[1]] = i[0]
    return D_inv

e, m, n = set_public_key()
d = get_private_key(e, m)
D = setD()
D_inv = setD_inv(D)
while 1:
    c = input('选择加密（E）或解密（D）：')
    if c == 'E':
        s = input('请输入明文：')
        ans = x = ''
        for i in range(len(s)):
            x += D[s[i]]
            '''每8位加密一次,并设置分隔符'''
            if ((i+1)%8 == 0):
                ans += str(ksm(eval(x), e, n))
                ans += '#'
                x = ''
        if (x != ''):
            ans += str(ksm(eval(x), e, n))
            ans += '#'
        print('密文：', ans)
    elif c == 'D':
        s = input('请输入密文：')
        ans = x = ''
        for i in s:
            if (i == '#'):
                ans += str(ksm(eval(x), d, n))
                x = ''
            else: x += i
        if (x != ''):
            ans += str(ksm(eval(x), d, n))
        y = ''
        for i in range(len(ans)//2):
            y += D_inv[ans[i*2:(i+1)*2]]
        print('明文：', y)