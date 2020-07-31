from math import log2

def norm(p):
    sumnorm = 0
    for i in range(len(p)):
        sumnorm = sumnorm + p[i]
    return sumnorm - 1

def condneu1(p):
    a = p[0] + p[1]
    b = p[0] + p[1] + p[2] + p[3]
    c = p[4] + p[5]
    d = p[4] + p[5] + p[6] + p[7]
    return (a/b) - (c/d)

def condneu3(p):
    a = p[8] + p[9]
    b = p[8] + p[9] + p[10] + p[11]
    c = p[12] + p[13]
    d = p[12] + p[13] + p[14] + p[15]
    return (a/b) - (c/d)


def condneu12(p):
    a = p[0] + p[2]
    b = p[0] + p[1] + p[2] + p[3]
    c = p[8] + p[10]
    d = p[8] + p[9] + p[10] + p[11]
    return (a/b) - (c/d)


def condneu32(p):
    a = p[4] + p[6]
    b = p[4] + p[5] + p[6] + p[7]
    c = p[12] + p[14]
    d = p[12] + p[13] + p[14] + p[15]
    return (a/b) - (c/d)



def cond3nonpair0(p):
    b = 0
    d = 0
    a = p[0] + p[1] + p[4] + p[5]
    c = p[8] + p[9] + p[12] + p[13]
    for i in range(8):
        b = b + p[i]
        d = d + p[8+i]
    return abs((a/b)-(c/d))

def cond3nonpair01(p):
    b = 0
    d = 0
    f = 0
    h = 0
    a = p[0] + p[1] + p[4] + p[5]
    e = p[32] + p[33] + p[36] + p[37]
    for i in range(8):
        b = b + p[i]
        f = f + p[32+i]
    return abs((a/b)-(e/f))


def cond3nonpair02(p):
    b = 0
    h = 0
    a = p[0] + p[1] + p[4] + p[5]
    g = p[40] + p[41] + p[44] + p[45]
    for i in range(8):
        b = b + p[i]
        h = h + p[40 + i]
    return  abs((a/b)-(g/h))


def cond3nonpair1(p):
    b = 0
    d = 0
    a = p[16] + p[17] + p[20] + p[21]
    c = p[24] + p[25] + p[28] + p[29]
    for i in range(8):
        b = b + p[16 + i]
        d = d + p[24 +i]
    return abs((a/b)-(c/d))


def cond3nonpair11(p):
    b = 0
    f = 0
    a = p[16] + p[17] + p[20] + p[21]
    e = p[48] + p[49] + p[52] + p[53]
    for i in range(8):
        b = b + p[16 + i]
        f = f + p[48 +i]
    return abs((a/b)-(e/f))


def cond3nonpair12(p):
    b = 0
    h = 0
    a = p[16] + p[17] + p[20] + p[21]
    g = p[56] + p[57] + p[60] + p[61]
    for i in range(8):
        b = b + p[16 + i]
        h = h + p[56 + i]
    return abs((a/b)-(g/h))


def cond3nonpair2(p):
    b = 0
    d = 0
    f = 0
    h = 0
    a = p[0] + p[1] + p[2] + p[3]
    c = p[8] + p[9] + p[10] + p[11]
    e = p[16] + p[17] + p[18] + p[19]
    g = p[24] + p[25] + p[26] + p[27]
    for i in range(8):
        b = b + p[i]
        d = d + p[8+i]
        f = f + p[16+i]
        h = h + p[24 + i]
    return abs((a/b)-(c/d))


def cond3nonpair21(p):
    b = 0
    d = 0
    f = 0
    h = 0
    a = p[0] + p[1] + p[2] + p[3]
    c = p[8] + p[9] + p[10] + p[11]
    e = p[16] + p[17] + p[18] + p[19]
    g = p[24] + p[25] + p[26] + p[27]
    for i in range(8):
        b = b + p[i]
        d = d + p[8+i]
        f = f + p[16+i]
        h = h + p[24 + i]
    return abs((a/b)-(e/f))


def cond3nonpair22(p):
    b = 0
    d = 0
    f = 0
    h = 0
    a = p[0] + p[1] + p[2] + p[3]
    c = p[8] + p[9] + p[10] + p[11]
    e = p[16] + p[17] + p[18] + p[19]
    g = p[24] + p[25] + p[26] + p[27]
    for i in range(8):
        b = b + p[i]
        d = d + p[8+i]
        f = f + p[16+i]
        h = h + p[24 + i]
    return abs((a/b)-(g/h))


def cond3nonpair3(p):
    b = 0
    d = 0
    f = 0
    h = 0
    a = p[32] + p[33] + p[34] + p[35]
    c = p[40] + p[41] + p[42] + p[43]
    e = p[48] + p[49] + p[50] + p[51]
    g = p[56] + p[57] + p[58] + p[59]
    for i in range(8):
        b = b + p[32 + i]
        d = d + p[40 + i]
        f = f + p[48 + i]
        h = h + p[56 + i]
    return abs((a/b)-(c/d))

def cond3nonpair31(p):
    b = 0
    d = 0
    f = 0
    h = 0
    a = p[32] + p[33] + p[34] + p[35]
    c = p[40] + p[41] + p[42] + p[43]
    e = p[48] + p[49] + p[50] + p[51]
    g = p[56] + p[57] + p[58] + p[59]
    for i in range(8):
        b = b + p[32 + i]
        d = d + p[40 + i]
        f = f + p[48 + i]
        h = h + p[56 + i]
    return abs((a/b)-(e/f))


def cond3nonpair32(p):
    b = 0
    d = 0
    f = 0
    h = 0
    a = p[32] + p[33] + p[34] + p[35]
    c = p[40] + p[41] + p[42] + p[43]
    e = p[48] + p[49] + p[50] + p[51]
    g = p[56] + p[57] + p[58] + p[59]
    for i in range(8):
        b = b + p[32 + i]
        d = d + p[40 + i]
        f = f + p[48 + i]
        h = h + p[56 + i]
    return  abs((a/b)-(g/h))


def cond3nonpair4(p):
    b = 0
    d = 0
    f = 0
    h = 0
    a = p[0] + p[2] + p[4] + p[6]
    c = p[16] + p[18] + p[20] + p[22]
    e = p[32] + p[34] + p[36] + p[38]
    g = p[48] + p[50] + p[52] + p[54]
    for i in range(8):
        b = b + p[i]
        d = d + p[16 + i]
        f = f + p[32 + i]
        h = h + p[48 + i]
    return abs((a/b)-(c/d))


def cond3nonpair41(p):
    b = 0
    d = 0
    f = 0
    h = 0
    a = p[0] + p[2] + p[4] + p[6]
    c = p[16] + p[18] + p[20] + p[22]
    e = p[32] + p[34] + p[36] + p[38]
    g = p[48] + p[50] + p[52] + p[54]
    for i in range(8):
        b = b + p[i]
        d = d + p[16 + i]
        f = f + p[32 + i]
        h = h + p[48 + i]
    return abs((a/b)-(e/f))


def cond3nonpair42(p):
    b = 0
    d = 0
    f = 0
    h = 0
    a = p[0] + p[2] + p[4] + p[6]
    c = p[16] + p[18] + p[20] + p[22]
    e = p[32] + p[34] + p[36] + p[38]
    g = p[48] + p[50] + p[52] + p[54]
    for i in range(8):
        b = b + p[i]
        d = d + p[16 + i]
        f = f + p[32 + i]
        h = h + p[48 + i]
    return abs((a/b)-(g/h))


def cond3nonpair5(p):
    b = 0
    d = 0
    f = 0
    h = 0
    a = p[8] + p[10] + p[12] + p[14]
    c = p[24] + p[26] + p[28] + p[30]
    e = p[40] + p[42] + p[44] + p[46]
    g = p[56] + p[58] + p[60] + p[62]
    for i in range(8):
        b = b + p[8 + i]
        d = d + p[24 + i]
        f = f + p[40 + i]
        h = h + p[56 + i]
    return abs((a/b)-(c/d))


def cond3nonpair51(p):
    b = 0
    d = 0
    f = 0
    h = 0
    a = p[8] + p[10] + p[12] + p[14]
    c = p[24] + p[26] + p[28] + p[30]
    e = p[40] + p[42] + p[44] + p[46]
    g = p[56] + p[58] + p[60] + p[62]
    for i in range(8):
        b = b + p[8 + i]
        d = d + p[24 + i]
        f = f + p[40 + i]
        h = h + p[56 + i]
    return abs((a/b)-(e/f))


def cond3nonpair52(p):
    b = 0
    d = 0
    f = 0
    h = 0
    a = p[8] + p[10] + p[12] + p[14]
    c = p[24] + p[26] + p[28] + p[30]
    e = p[40] + p[42] + p[44] + p[46]
    g = p[56] + p[58] + p[60] + p[62]
    for i in range(8):
        b = b + p[8 + i]
        d = d + p[24 + i]
        f = f + p[40 + i]
        h = h + p[56 + i]
    return abs((a/b)-(g/h))


def kl(y,x):
    sumkl = 0.0
    for i in range(len(y)):
        if y[i] > 0:
            if x[i] > 0:
                sumkl = sumkl + y[i] * (log2(y[i]) - log2(x[i]))
            else:
                sumkl = sumkl +  100
    return sumkl


def cond1(p):
    res = [0, 0, 0, 0, 0, 0, 0, 0]
    k = 0
    for j in range(4):
        for i in [0, 2]:
            m = [0, 4, 8, 12]
            l = [1, 4, 8, 12]
            a = (p[i + m[j]] + p[i + 1 + m[j]]) / (p[i + m[j]] + p[i + 1 + m[j]] + p[((i + 2) % 4) + m[j]]
                                                    + p[((i + 3) % 4)+ m[j]])
            c = (p[i + (l[j] // 8) * 8] + p[i + 1 + (l[j] // 8) * 8] + p[(i + 4) + (l[j] // 8) * 8] + p[
                i + 5 + (l[j] // 8) * 8])
            d = (p[(i % 8) + (l[j] // 8) * 8] + p[((i + 1) % 8) + (l[j] // 8) * 8] + p[((i + 2) % 8) + (l[j] // 8) * 8]
                 + p[((i + 3) % 8) + (l[j] // 8) * 8] + p[((i + 4) % 8) + (l[j] // 8) * 8] + p[((i + 5) % 8) +
                 (l[j] // 8) * 8] + p[((i + 6) % 8) + (l[j] // 8) * 8] + p[((i + 7) % 8) + (l[j] // 8) * 8])
            b = (c / d)
            res[k] = (a - b)
            k = k + 1
    return res


def test_smallcond(p, tol):
    if smallcond1(p) > tol :
        print("1 wrong 1")
        print(smallcond1(p))
    if smallcond2(p) > tol :
        print("1 wrong 2")
        print(smallcond2(p))
    if smallcond3(p) > tol :
        print("1 wrong 3" )
        print(smallcond3(p))
    if smallcond4(p) > tol :
        print("1 wrong 4")
        print(smallcond4(p))
    if smallcond5(p) > tol :
        print("1 wrong 5")
        print(smallcond5(p))
    if smallcond6(p) > tol :
        print("1 wrong 6")
        print(smallcond6(p))
    if smallcond7(p) > tol :
        print("1 wrong 7")
        print(smallcond7(p))
    if smallcond8(p) > tol :
        print("1 wrong 8")
        print(smallcond8(p))
    if smallcond9(p) > tol :
        print("1 wrong 9")
        print(smallcond9(p))
    if smallcond10(p) > tol :
        print("1 wrong 10")
        print(smallcond10(p))
    if smallcond11(p) > tol :
        print("1 wrong 11" )
        print(smallcond11(p))
    if smallcond12(p) > tol :
        print("1 wrong 12")
        print(smallcond12(p))
    if smallcond13(p) > tol :
        print("1 wrong 13")
        print(smallcond13(p))
    if smallcond14(p) > tol :
        print("1 wrong 14")
        print(smallcond14(p))
    if smallcond15(p) > tol :
        print("1 wrong 15")
        print(smallcond15(p))
    if smallcond16(p) > tol :
        print("1 wrong 16")
        print(smallcond16(p))


def test_condneu(p, tol):
    if condneu1(p) > tol :
        print("wrong 1")
        print(condneu1(p))
    if condneu2(p) > tol :
        print("wrong 2")
        print(condneu2(p))
    if condneu3(p) > tol :
        print("wrong 3")
        print(condneu3(p))
    if condneu4(p) > tol :
        print("wrong 4")
        print(condneu4(p))
    if condneu12(p) > tol :
        print("wrong 5")
        print(condneu12(p))
    if condneu22(p) > tol :
        print("wrong 6")
        print(condneu22(p))
    if condneu32(p) > tol :
        print("wrong 7")
        print(condneu32(p))
    if condneu42(p) > tol :
        print("wrong 8")
        print(condneu42(p))


def test_margsum(p) :
    sumx = [p[0] + p[1] + p[2] + p[3], p[4] + p[5] + p[6] + p[7], p[8] + p[9] + p[10] + p[11],
            p[12] + p[13] + p[14] + p[15]]
    sumy1cx = [(p[0] + p[1])/ sumx[0], (p[2] + p[3])/sumx[0],(p[4] + p[5])/ sumx[1], (p[6] + p[7])/sumx[1],
               (p[8] + p[9])/ sumx[2], (p[10] + p[11])/sumx[2], (p[12] + p[13])/ sumx[3], (p[14] + p[15])/sumx[3]]
    sumy2cx = [(p[0] + p[2])/ sumx[0], (p[1] + p[3])/sumx[0],(p[4] + p[6])/ sumx[1], (p[5] + p[7])/sumx[1],
               (p[8] + p[10])/ sumx[2], (p[9] + p[11])/sumx[2], (p[12] + p[14])/ sumx[3], (p[13] + p[15])/sumx[3]]
    sumy1cxy = [p[0]/(p[0] + p[2]), p[1]/(p[1] + p[3]), p[2]/(p[2] + p[0]), p[3]/(p[1] + p[3]),
                p[4]/(p[4] + p[6]), p[5]/(p[5] + p[7]), p[6]/(p[4] + p[6]), p[7]/(p[5] + p[7]),
                p[8] / (p[8] + p[10]) , p[9] / (p[11] + p[9]) , p[10] / (p[10] + p[8]) , p[11] / (p[9] + p[11]) ,
                p[12] / (p[12] + p[14]) , p[13] / (p[15] + p[13]) , p[14] / (p[14] + p[12]) , p[15] / (p[13] + p[15])]
    sumy2cxy = [p[0]/(p[0] + p[1]), p[1]/(p[0] + p[1]), p[2]/(p[2] + p[3]), p[3]/(p[2] + p[3]),
                p[4]/(p[4] + p[5]), p[5]/(p[4] + p[5]), p[6]/(p[6] + p[7]), p[7]/(p[6] + p[7]),
                p[8] / (p[8] + p[9]) , p[9] / (p[8] + p[9]) , p[10] / (p[10] + p[11]) , p[11] / (p[10] + p[11]) ,
                p[12] / (p[12] + p[13]) , p[13] / (p[12] + p[13]) , p[14] / (p[14] + p[15]), p[15] / (p[14] + p[15])]
    sumy1cx1 = [(p[0] + p[1] + p[4] + p[5]) / (sumx[0] + sumx[1]) , (p[2] + p[3] + p[6] + p[7]) / (sumx[0] + sumx[1]) ,
                (p[8] + p[9] + p[12] + p[13]) / (sumx[2] + sumx[3]) ,
                (p[10] + p[11] + p[14] + p[15]) / (sumx[3] + sumx[2])]
    sumy2cx2 = [(p[0] + p[2] + p[8] + p[10]) / (sumx[0] + sumx[2]) ,
                (p[1] + p[3] + p[9] + p[11]) / (sumx[0] + sumx[2]) ,
                (p[4] + p[6] + p[12] + p[14]) / (sumx[1] + sumx[3]) ,
                (p[5] + p[7] + p[13] + p[15]) / (sumx[3] + sumx[1])]
    sumy  =  [p[0] + p[4] + p[8] + p[12], p[1] + p[5] + p[9] + p[13], p[2] + p[6] + p[10] + p[14],
            p[3] + p[7] + p[11] + p[15]]
    sumy1 =  [p[0] + p[4] + p[8] + p[12] + p[1] + p[5] + p[9] + p[13], p[2] + p[6] + p[10] + p[14] +
            p[3] + p[7] + p[11] + p[15]]
    sumy2 =  [p[0] + p[2] + p[4] + p[6] + p[8] + p[10] + p[12] + p[14], p[1] + p[3] + p[5] + p[7] +
            p[9] + p[11] + p[13] + p[15]]
    return sumx, sumy1cx, sumy2cx, sumy1cxy, sumy2cxy, sumy1cx1 ,sumy2cx2, sumy, sumy1, sumy2

x = [0.333327,
1.12781e-29,
1.28814e-30,
6.4e-11,
0.166665,
3.36481e-06,
3.00216e-31,
3.99994e-06,
0.166666,
2.12901e-30,
3.24396e-06,
3.99994e-06,
0.0833338,
6.35186e-07,
7.56041e-07,
0.249992]
