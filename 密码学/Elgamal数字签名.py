import random
def set_key():
    p = 19; g = 2; x = 9; y = 18    #x为私钥，y为公钥
    return p, g, x, y
def gcd(a, b):  #辗转相除求最大公因数
    t = a % b
    while (t):
        a = b
        b = t
        t = a % b
    return b
def exgcd(a, b):    #扩展欧几里得算法求乘法逆元
    x = 1; y = 0; g = a
    if b == 0: 
        return g, x, y
    else:
        g, x1, y1 = exgcd(b, a % b)
        x = y1
        y = x1 - a // b * y1
        return g, x, y
def get_hash(txt):  #获得文本摘要，字符串hash
    h = 0
    for i in txt:
        h = (h*131+ord(i))%1000000009
    return h
def get_rand(p):    #生成随机数k，其中(k, p-1) = 1
    k = random.randint(1, p-1)
    while (gcd(k, p-1) != 1):
        k = random.randint(1, p-1)
    return k
def ksm(a, b, mod): #快速幂
    t = 1
    while b:
        if (b & 1): t = t*a%mod
        b >>= 1
        a = a*a%mod
    return t
def sign(h, p, g, k, x):    #签名算法
    r = ksm(g, k, p)
    s = exgcd(k, p-1)[1] * (h - r*x) % (p-1)
    return r, s
def test(h, r, s, g, y, p): #验证算法
    a = ksm(y, r, p)
    b = ksm(r, s, p)
    if (a*b%p == ksm(g, h, p)):
        print('验证成功')
    else:
        print('验证失败')

p, g, x, y = set_key()
while 1:
    c = input('选择签名(S)或验证(T)：')
    if c == 'S':
        txt = input('请输入需要签名的文本：')
        h = get_hash(txt)
        print('该文本摘要为：', h)
        k = get_rand(p)
        r, s = sign(h, p, g, k, x)
        print('该文本的数字签名为：', h, r, s)
    elif c == 'T':
        h, r, s = map(int, input('请输入需要验证的签名：').split())
        test(h, r, s, g, y, p)
