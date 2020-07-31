import numpy as np
import itertools
import conditions
from scipy.optimize import minimize
from random import *

def sigmoid(x):
    return 1/(1 + np.exp(x))

def randomvector(n):
    d = np.array([])
    for x in range(n):
        x = randint(0, 6000000)
        d = np.append(d, x)
    u = np.sum(d)
    d = d / u
    return d
#
def iterate(r, W,p, write,  nodes, lst, informint, num_steps, beta_start, beta_diff):
    path = write
    output = open(path +'.txt', 'w')
    if informint:
        output2 = open(path + 'intinf.txt', 'w' )
    for iterat in range(num_steps):
        print("beta",( beta_start+ beta_diff*iterat))
        r1 = 1
        statesx = 2**nodes
        statesxy = 2**(2*nodes)
        while r1 > r:
            q = np.zeros(statesxy)
            for i in range(statesxy):
                q[i] = p[i // statesx]
            it = 0
            summ = 0
            for reali in lst:
                for i in range(nodes):
                    exponent = 0.0
                    for j in range(nodes):
                        exponent = exponent + W[i][j] * reali[j] * reali[nodes + i]
                    p1 = sigmoid(-2 * (beta_start+ beta_diff * iterat) * exponent)
                    q[it] = q[it] * p1
                summ = summ + q[it]
                it = it + 1
            py = np.zeros(statesx)
            for j in range(statesxy):
                py[j % statesx] = py[j % statesx] + q[j]
            r1 = conditions.kl(p, py)
            p = np.copy(py)
        # only necessary for the Integrated Information measure defined using the Cond. Ind. Statements
        if informint and nodes == 2:
            cons = [{'type': 'eq', 'fun': conditions.condneu1}, {'type': 'eq', 'fun': conditions.condneu3},
                    {'type': 'eq', 'fun': conditions.condneu12}, {'type': 'eq', 'fun': conditions.condneu32},
                    {'type': 'eq', 'fun': conditions.norm}]
            bnds = ([0, 1], [0, 1], [0, 1], [0, 1], [0, 1], [0, 1], [0, 1], [0, 1],
                    [0, 1], [0, 1], [0, 1], [0, 1], [0, 1], [0, 1], [0, 1], [0, 1])
            def kl(p):
                return conditions.kl(q, p)
            min = 100
            for m in range(9):
                x = randomvector(16)
                minp = minimize(kl, x, constraints=cons, method='SLSQP', bounds=bnds,
                                options={'maxiter': 500, 'ftol': 1e-16, 'disp': False, 'iprint': 1,
                                         'eps': 1.4901161193847656e-08})
                # print(minp)
                if minp.fun < min: min = minp.fun
            minp = minimize(kl, q, constraints=cons, method='SLSQP', bounds=bnds,
                            options={'maxiter': 500, 'ftol': 1e-16, 'disp': False, 'iprint': 1,
                                     'eps': 1.4901161193847656e-08})
            if minp.fun < min: min = minp.fun
            print(min, ",")
            output2.write(str(min))
            output2.write(',')
        if informint and nodes == 3:
            def kl(p):
                return conditions.kl(q, p)
            cons1 = [{'type': 'eq', 'fun': conditions.norm}, {'type': 'eq', 'fun': conditions.cond3nonpair1},
                     {'type': 'eq', 'fun': conditions.cond3nonpair11},
                     {'type': 'eq', 'fun': conditions.cond3nonpair12}, {'type': 'eq', 'fun': conditions.cond3nonpair01},
                     {'type': 'eq', 'fun': conditions.cond3nonpair02},
                     {'type': 'eq', 'fun': conditions.cond3nonpair2}, {'type': 'eq', 'fun': conditions.cond3nonpair21},
                     {'type': 'eq', 'fun': conditions.cond3nonpair22},
                     {'type': 'eq', 'fun': conditions.cond3nonpair0}, {'type': 'eq', 'fun': conditions.cond3nonpair3},
                     {'type': 'eq', 'fun': conditions.cond3nonpair4},
                     {'type': 'eq', 'fun': conditions.cond3nonpair5}, {'type': 'eq', 'fun': conditions.cond3nonpair32},
                     {'type': 'eq', 'fun': conditions.cond3nonpair42},
                     {'type': 'eq', 'fun': conditions.cond3nonpair52}, {'type': 'eq', 'fun': conditions.cond3nonpair31},
                     {'type': 'eq', 'fun': conditions.cond3nonpair41}, {'type': 'eq', 'fun': conditions.cond3nonpair51}]
            bnds = ((0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1),
                    (0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1),
                    (0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1),
                    (0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1),
                    (0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1),
                    (0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1),
                    (0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1),
                    (0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1), (0, 1))
            min = 100
            for m in range(6):
                x = randomvector(64)
                minp = minimize(kl, x, method='trust-constr', hess=lambda x: np.zeros((64, 64)),
                                hessp=lambda x: np.zeros((64, 64)), bounds=bnds, constraints=cons1,
                                options={'maxiter': 2000,
                                         'disp': True, 'xtol': 1e-16, 'gtol': 1e-16})
                print(minp. success)
                if minp.success & (minp.fun < min): min = minp.fun
            minp = minimize(kl, q, method='trust-constr', hess=lambda x: np.zeros((64, 64)),
                            hessp=lambda x: np.zeros((64, 64)), bounds=bnds, constraints=cons1,
                            options={'maxiter': 2000,
                                     'disp': True, 'xtol': 1e-16, 'gtol': 1e-16})
            if minp.success & (minp.fun < min): min = minp.fun
            print(min, ",")
            output2.write(str(min))
            output2.write(',')
        my_string = ','.join(map(str, q))
        #print(my_string)
        output.write(my_string)
        output.write(' # ')
    output.write(';')
    output.close()
    if informint: output2.close()

def randomW(nodes):
    W = np.zeros(nodes)
    for i in range(nodes):
        b = 2* np.random.beta(1,2,(nodes,))-1
#     print(b)
        W = np.vstack([W , b])
    W = np.delete(W , 0 , 0)
    return W

def main():
    # number of nodes
    nodes = 3
    # list of possible states
    lst = [list(i) for i in itertools.product([-1, 1], repeat=2*nodes)]
    # random initial distribution
    p = randomvector(2**nodes)
    # random matrix, here you can define a fixed one
    W = randomW(nodes)
    print(W)
    # path where the result is going to be saved
    path = '/home/carlotta/Documents/Tests/BoltzWnegbetabeta2'
    # 0.00000001 = difference between two distributions (stopping condition),
    # informint = set this to true if you want to directly calculate the Int. INf measure, but it only works well for n=2
    # if n=2 this might take a (long ) while, if you find a better way to optimize this measure, please let me know,
    # 200 = number of steps, beta gets increased with 0.02 each step.
    r = 0.00000001
    informint = False
    num_steps = 200
    beta_start = 0.02
    beta_diff = 0.02
    iterate(r, W,p, path,  nodes, lst, informint, num_steps, beta_start, beta_diff)
    # print("summ" , summ)
    # print(q)

main()

