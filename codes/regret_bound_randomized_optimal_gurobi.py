# -*- coding: utf-8 -*-
"""
Created on Sun Jan 10 18:52:43 2016

@author: swaprava

This code finds the minimum worst absolute regret for a randomized, strategyproof and budget balanced mechanism - via optimization of the regret with constraints on strategyproofness and budget balance.

This is in principle any randomized strategyproof mechanism, using the WMON property enforced when the SCF is generated (we know that for convex type spaces this is a sufficient condition too). We enforce that the mechanism is budget balanced in the constraints.
"""

import numpy as np
from joblib import Parallel, delayed
import multiprocessing
import itertools as it
import matplotlib.pyplot as plt
from fractions import Decimal, Fraction
#import scipy.optimize as spopt
from gurobipy import *
#import random as rd
import time

print '\n=============================================='
print 'Code run on', time.strftime('%c')
print '==============================================\n'

num_cores = multiprocessing.cpu_count()
print("numCores = " + str(num_cores))

###############################################################
# THIS FUNCTION WILL UPDATE THE PROGRESS OF THE SOLVING PROCESS

def printGurobiVar(listOfGurobiVars):
    # this function is specific to this problem

    scfString = ''
    paymentString = ''
#    print listOfGurobiVars
    raw_input()

    for var in listOfGurobiVars:
#        print type(var), var.varName
#        print var.x
        if var.varName[:3] == 'scf':
            scfString += var.varName + '\t' + str(var.x) + '\n'
        elif var.varName[:7] == 'payment':
            paymentString += var.varName + '\t' + str(var.x) + '\n'
        else:
            k = var.varName + '\t' + str(var.x)

    print 'SCF:'
    print scfString
    print 'Payments:'
    print paymentString
    print 'Objective value:'
    print k

# Define my callback function

def mycallback(model, where):
    if where == GRB.Callback.POLLING:
        # Ignore polling callback
        print 'Polling callback: no idea what it does'
    elif where == GRB.Callback.PRESOLVE:
        # Presolve callback
        cdels = model.cbGet(GRB.Callback.PRE_COLDEL)
        rdels = model.cbGet(GRB.Callback.PRE_ROWDEL)
        if cdels or rdels:
            print('Presolve callback: %d columns and %d rows are removed' % (cdels, rdels))
    elif where == GRB.Callback.SIMPLEX:
        # Simplex callback
        itcnt = model.cbGet(GRB.Callback.SPX_ITRCNT)
        print('Simplex callback: iteration count %d' % itcnt)
        model._vars = model.getVars()
#        print 'variables'
#        printGurobiVar(model._vars) # doesn't work, gurobi doesn't let the variables print
        if itcnt - model._lastiter >= 100:
            print('Simplex callback: curr iterCount - last iterCount >= 100')
            model._lastiter = itcnt
            print('pretends the last iterCount to be curr iterCount')
            obj = model.cbGet(GRB.Callback.SPX_OBJVAL)
            ispert = model.cbGet(GRB.Callback.SPX_ISPERT)
            pinf = model.cbGet(GRB.Callback.SPX_PRIMINF)
            dinf = model.cbGet(GRB.Callback.SPX_DUALINF)

            if ispert == 0:
                ch = ' '
            elif ispert == 1:
                ch = 'S'
            else:
                ch = 'P'
            print('itcnt = %d, obj = %g, ch = %s, pinf = %g, dinf = %g' % (int(itcnt), obj, ch, pinf, dinf))
    elif where == GRB.Callback.MIP:
        # General MIP callback
        nodecnt = model.cbGet(GRB.Callback.MIP_NODCNT)
        objbst = model.cbGet(GRB.Callback.MIP_OBJBST)
        objbnd = model.cbGet(GRB.Callback.MIP_OBJBND)
        solcnt = model.cbGet(GRB.Callback.MIP_SOLCNT)
        if nodecnt - model._lastnode >= 100:
            model._lastnode = nodecnt
            actnodes = model.cbGet(GRB.Callback.MIP_NODLFT)
            itcnt = model.cbGet(GRB.Callback.MIP_ITRCNT)
            cutcnt = model.cbGet(GRB.Callback.MIP_CUTCNT)
            print('%d %d %d %g %g %d %d' % (nodecnt, actnodes, \
                  itcnt, objbst, objbnd, solcnt, cutcnt))
        if abs(objbst - objbnd) < 0.1 * (1.0 + abs(objbst)):
            print('Stop early - 10% gap achieved')
            model.terminate()
        if nodecnt >= 10000 and solcnt:
            print('Stop early - 10000 nodes explored')
            model.terminate()
    elif where == GRB.Callback.MIPSOL:
        # MIP solution callback
        nodecnt = model.cbGet(GRB.Callback.MIPSOL_NODCNT)
        obj = model.cbGet(GRB.Callback.MIPSOL_OBJ)
        solcnt = model.cbGet(GRB.Callback.MIPSOL_SOLCNT)
        x = model.cbGetSolution(model.getVars())
        print('**** New solution at node %d, obj %g, sol %d, ' \
              'x[0] = %g ****' % (nodecnt, obj, solcnt, x[0]))
    elif where == GRB.Callback.MIPNODE:
        # MIP node callback
        print('**** New node ****')
        if model.cbGet(GRB.Callback.MIPNODE_STATUS) == GRB.Status.OPTIMAL:
            x = model.cbGetNodeRel(model.getVars())
            model.cbSetSolution(model.getVars(), x)
    elif where == GRB.Callback.BARRIER:
        # Barrier callback
        print('Barrier callback: what does it do?')
        itcnt = model.cbGet(GRB.Callback.BARRIER_ITRCNT)
        primobj = model.cbGet(GRB.Callback.BARRIER_PRIMOBJ)
        dualobj = model.cbGet(GRB.Callback.BARRIER_DUALOBJ)
        priminf = model.cbGet(GRB.Callback.BARRIER_PRIMINF)
        dualinf = model.cbGet(GRB.Callback.BARRIER_DUALINF)
        cmpl = model.cbGet(GRB.Callback.BARRIER_COMPL)
        print('itcnt = %d, primobj = %g, dualobj = %g, priminf = %g, \
        dualinf = %g, cmpl = %g' % (itcnt, primobj, dualobj, priminf, dualinf, cmpl))
    elif where == GRB.Callback.MESSAGE:
        # Message callback
        msg = model.cbGet(GRB.Callback.MSG_STRING)
        print('Message callback: %s' % msg)
        model._logfile.write(msg)
##############################################################


def printMech(scf, payments):

    if len(scf) != numOfProfiles or len(payments) != numOfProfiles or len(scf) != len(payments):
        print 'SCF - profiles - payments length mismatch'
        return None

    print '\n The mechanism is the following:'
    print 'value profile \t\t SCF \t\t payments'
    for item in xrange(numOfProfiles):
        print valuationProfiles[item], '\t', scf[item], '\tsum =', sum(scf[item]), '\t', payments[item]


# this function checks the strategyproofness of a given mechanism
def checkSP(scf, payments):
    # for the entire valuation profile
    debug = False

    packSizes = numOfValuations**np.arange(numOfagents)

    checkOFagent = numOfagents - 1

    for packsize in packSizes:
        print '\nchecking for agent =', checkOFagent

        listOfIndices = []
        # first split
        ySize = packsize * numOfValuations
        xSize = int(numOfProfiles / ySize)
        firstSplit = np.reshape(valProfIndices, (xSize,ySize))

        # second split
        for item in firstSplit:
            temp = np.reshape(item, (numOfValuations,packsize))
            for innerItem in temp.T:
                listOfIndices.append(innerItem)

        isSP = True

        for indices in listOfIndices:
            if debug:
                print 'indices for agent', checkOFagent, 'are', indices
                raw_input()

            for v_index in indices:
                for v_prime_index in indices:
                    value = np.dot(scf[v_index] - scf[v_prime_index], valuationProfiles[v_index][checkOFagent]) + payments[v_prime_index][checkOFagent] - payments[v_index][checkOFagent]

                    if value < 0 and abs(value) > 1e-7:
                        print 'not SP!'
                        print 'deviating agent =', checkOFagent
                        print 'relevant valuationProfiles and SCF'
        #                printSCF(outcomes, valuationProfiles[chunk * numOfValuations : (chunk+1) * numOfValuations,:])
                        print 'v_index =', v_index, 'v_prime_index =', v_prime_index
                        print 'scf[v_index] =', scf[v_index], ', scf[v_prime_index] =', scf[v_prime_index]
                        print 'valuationProfiles[v_index][checkOFagent] =', valuationProfiles[v_index][checkOFagent]
                        print 'payments[v_prime_index][checkOFagent] =', payments[v_prime_index][checkOFagent], 'payments[v_index][checkOFagent] =', payments[v_index][checkOFagent]
                        print 'value =', value
    #                    raw_input()

                        isSP = False

        checkOFagent -= 1

    return isSP


def findOptMech(debug=False):

    # define model
    m = Model('minRegret')

    # add variables
    scf = {} # will be populated as (numOfProfiles,numOfalts)
    payments = {} # will be populated as (numOfProfiles,numOfagents)

    if debug:
        print '\ncreating the variables - scf and payments'
    for valueProfileIndex in valProfIndices:
        for alt in xrange(numOfalts):
            scf[valueProfileIndex,alt] =  \
            m.addVar(lb = 0.0, ub = 1.0, vtype = GRB.CONTINUOUS, \
            name = 'scf_valprofile_'+str(valueProfileIndex)+'_alt_'+str(alt))

        for agent in xrange(numOfagents):
            payments[valueProfileIndex,agent] = \
            m.addVar(lb = -GRB.INFINITY, ub = GRB.INFINITY, vtype = GRB.CONTINUOUS, \
            name = \
            'payment_valprofile_'+str(valueProfileIndex)+'_agent_'+str(agent))

    if debug:
        print 'now creating the objective - k'
    k = m.addVar(vtype = GRB.CONTINUOUS, name = 'optimal_value')
    if debug:
        print 'variables creation complete'

    # model update
    m.update()

    # print the variables
    if debug:
        for v in m.getVars():
            print('%s' % v.varName)
        print '\nthese are just declared, not yet used in the optimization'

    # add constraints
    # part 1: strategyproofness constraints

    if debug:
        print '\nNow creating the constraints'

    constraints = {} # this is to save the dual variables

    packSizes = numOfValuations**np.arange(numOfagents)

    checkOFagent = numOfagents - 1

    for packsize in packSizes:
        if debug: print '\nPart 1: ensuring strategyproofness for agent =', checkOFagent

        listOfIndices = []
        # first split
        ySize = packsize * numOfValuations
        xSize = int(numOfProfiles / ySize)
        firstSplit = np.reshape(valProfIndices, (xSize,ySize))

        # second split
        for item in firstSplit:
            temp = np.reshape(item, (numOfValuations,packsize))
            for innerItem in temp.T:
                listOfIndices.append(innerItem)

        for indices in listOfIndices:
            if debug:
                print 'indices for agent', checkOFagent, 'are', indices
#                raw_input()

            for v_index in indices:
                for v_prime_index in indices:
                    expr = LinExpr()
                    for alt in xrange(numOfalts):
                        expr += (scf[v_index,alt] - scf[v_prime_index,alt]) * valuationProfiles[v_index][checkOFagent][alt]
                    expr += payments[v_prime_index,checkOFagent] - payments[v_index,checkOFagent]

                    indices_str = '_'.join(map(str,indices))
                    if debug:
                        print 'creating constraint for agent', checkOFagent, 'indices', indices_str, 'v_index', v_index, 'v_prime_index', v_prime_index

                    constraints[checkOFagent, indices_str, v_index, v_prime_index] = \
                    m.addConstr(expr, GRB.GREATER_EQUAL, 0.0, \
                    name = 'constraint_agent_' + str(checkOFagent) + '_indices_' + indices_str + '_v_index_' + str(v_index) + '_v_prime_index_' + str(v_prime_index))

        checkOFagent -= 1

    # part 2:
    # (a) scf summing to unity constraint
    # (b) payments summing to 0 = budget balance constraint
    # (c) k >= all regrets constraint

    if debug:
        print '\nPart 2:'
        print '(a) scf summing to unity constraint'
        print '(b) payments summing to 0 = budget balance constraint'
        print '(c) k >= all regrets constraint'

    for valueProfileIndex in valProfIndices:

        exprSCF = LinExpr()
        exprPayment = LinExpr()
        expr_k = LinExpr()

        for alt in xrange(numOfalts):
            exprSCF += scf[valueProfileIndex,alt]
            expr_k += sum(valuationProfiles[valueProfileIndex],0)[alt] * scf[valueProfileIndex,alt]

        if debug:
            print 'creating constraint for valuation profile', valueProfileIndex
            print 'for scf adding to 1'
            print 'payments summing to 0'
            print 'k >= all regrets'

        constraints[valueProfileIndex, 'scf'] = m.addConstr(exprSCF, GRB.EQUAL, 1.0, name = 'scf_v_index_' + str(valueProfileIndex))

        constraints[valueProfileIndex, 'k'] = m.addConstr(k - max(sum(valuationProfiles[valueProfileIndex],0)) + expr_k >= 0.0, name = 'k_v_index_' + str(valueProfileIndex))

        for agent in xrange(numOfagents):
            exprPayment += payments[valueProfileIndex,agent]
        constraints[valueProfileIndex, 'bb'] = m.addConstr(exprPayment, GRB.EQUAL, 0.0, name = 'budget_v_index_' + str(valueProfileIndex))


    if debug:
        print 'creating constraints complete'

    # set objectives
    if debug:
        print '\nSetting the objective function'
    m.setObjective(k, GRB.MINIMIZE)


    # optimize
    if debug: print '\nNow solving the optimization problem'
    m.setParam(GRB.Param.ScaleFlag, 2)
    m.optimize()
#    m.optimize(mycallback) # WITH CALLBACK, not very useful, doesn't allow to see the variables

    # print solutions
    print '\nSolution:'
    scfSolution = []
    paymentSolution = []
    for valueProfileIndex in valProfIndices:
        temp = []
        for alt in xrange(numOfalts):
            temp.append(scf[valueProfileIndex,alt].getAttr('x'))
        scfSolution.append(temp)

        temp1 = []
        for agent in xrange(numOfagents):
            temp1.append(payments[valueProfileIndex,agent].getAttr('x'))
        paymentSolution.append(temp1)

    scfSolution = np.array(scfSolution)
    paymentSolution = np.array(paymentSolution)


    if debug:
        printMech(scfSolution, paymentSolution)

        print 'k =', k.getAttr('x')
        print('Obj: %g' % m.objVal)

#    print m.getConstr()
#
#    raw_input()

#    m.write('model.sol')

#    print m.MaxCoeff
#    raw_input()

#    print '\nPrinting dual variables (only non-zeros):'
##    print 'duals of 4 kinds'
##    print 'agent - indices - v_index - v_prime_index'
#
#    countPositive = 0
#    for index in constraints.keys():
#        if abs(constraints[index].pi) > 1e-7:
#            countPositive += 1
#            print constraints[index].constrName, '\t', constraints[index].pi
#
#    print '\ntotal number of constraints =', len(constraints.keys())
#    print 'non-zero dual variables =', countPositive
#
#    print 'cross check the dual optimal'
#    optValue = 0.0
#    for valueProfileIndex in valProfIndices:
#        optValue += constraints[valueProfileIndex, 'scf'].pi
#        optValue += max(sum(valuationProfiles[valueProfileIndex],0)) * constraints[valueProfileIndex, 'k'].pi
#
#    print 'dual optimal =', optValue
#    raw_input()

    # NEED TO UPDATE THE VARIABLES AND RETURN APPROPRIATELY
    return scfSolution, paymentSolution, m.objVal



def profileCreate(valProfile):

    return valProfile


def maxRegretProfile(scf):

    maxRegret = 0.0
#    maxRegretProfileIndex = 0
#    scfMaxRegretProfile = scf[0]

    for valueProfileIndex in valProfIndices:

        welfare = np.dot(scf[valueProfileIndex], sum(valuationProfiles[valueProfileIndex],0))
        currRegret = max(sum(valuationProfiles[valueProfileIndex],0)) - welfare

        if currRegret >= maxRegret:
            maxRegret = currRegret
            maxRegretProfileIndex = valueProfileIndex
            scfMaxRegretProfile = scf[valueProfileIndex]

    return maxRegret, maxRegretProfileIndex, scfMaxRegretProfile


def maxRegretProfileZeroPayment(scf,payments):

    maxRegret = 0.0
#    maxRegretProfileIndex = 0
#    scfMaxRegretProfile = scf[0]

    for valueProfileIndex in valProfIndices:

        welfare = np.dot(scf[valueProfileIndex], sum(valuationProfiles[valueProfileIndex],0))
        currRegret = max(sum(valuationProfiles[valueProfileIndex],0)) - welfare


        if (currRegret == maxRegret and np.array_equal(payments[valueProfileIndex], np.zeros(numOfagents))) or currRegret > maxRegret:
            maxRegret = currRegret
            maxRegretProfileIndex = valueProfileIndex
            scfMaxRegretProfile = scf[valueProfileIndex]

    return maxRegret, maxRegretProfileIndex, scfMaxRegretProfile

###################################################################
### similar functions for sink mechanisms

def printSinkMech(scf, sinkprobability):

    if len(scf) != numOfProfiles or len(sinkprobability) != numOfProfiles or len(scf) != len(sinkprobability):
        print 'SCF - profiles length mismatch'
        return None

    print '\n The mechanism is the following:'
    print 'value profile \t\t SCF \t\t sink probability'
    for item in xrange(numOfProfiles):
        print valuationProfiles[item], '\t', scf[item], '\tsum =', sum(scf[item]), '\t', sinkprobability[item]

# this function maps the sink probabilities into the probabilities over the alternatives
def sink2alt(valProfileIndex,sinkProbDist_oneprofile,kind='expr'):

#    print 'called with'
#    print 'valProfileIndex =',valProfileIndex, 'sinkProbDist_oneprofile =', sinkProbDist_oneprofile
    valuationProfile = valuationProfiles[valProfileIndex]

    if kind == 'expr':
        tempProb = np.array([LinExpr() for alt in xrange(numOfalts)])
    if kind == 'num':
        tempProb = np.zeros(numOfalts)

    for sink in xrange(numOfagents):
        others = list(set(range(numOfagents)) - set([sink]))
        valProf = np.array(valuationProfile)
        valProfOthers = valProf[others]
        outcome_wo_sink = np.argmax(sum(valProfOthers,0))
        tempProb[outcome_wo_sink] += sinkProbDist_oneprofile[sink]

#    print 'tempProb'
#    print tempProb
    return tempProb

def sinkPayment(valProfileIndex, sinkProbDist_oneprofile, kind='expr', debug=False):

    valuationProfile = valuationProfiles[valProfileIndex]
    if kind == 'expr':
        tempPayment = np.array([LinExpr() for alt in xrange(numOfagents)])
    if kind == 'num':
        tempPayment = np.zeros(numOfagents)

    if debug:
        print 'valuationProfile'
        print valuationProfile

    for sink in xrange(numOfagents):

        others = list(set(range(numOfagents)) - set([sink]))
        valProf = np.array(valuationProfile)
        valProfOthers = valProf[others]
        outcome_wo_sink = np.argmax(sum(valProfOthers,0))

        if debug:
            print '\nsink =', sink
            print 'outcome_wo_sink =', outcome_wo_sink

        paymentSink = 0.0
        for otheragent in others:

            otherotheragents = list(set(others) - set([otheragent]))

            if debug:
                print 'otheragent =', otheragent
                print 'otherotheragents =', otherotheragents

            if len(otherotheragents) == 0:
                currAgentPay = 0
            else:
                currAgentPay = max(sum(valProf[otherotheragents],0)) - sum(valProf[otherotheragents],0)[outcome_wo_sink]
                if debug:
                    print 'otheragent pays = max(sum(valProf[otherotheragents],0)) - sum(valProf[otherotheragents],0)[outcome_wo_sink] = ', max(sum(valProf[otherotheragents],0)), '-',  sum(valProf[otherotheragents],0)[outcome_wo_sink], '=', currAgentPay
            paymentSink += currAgentPay

#            print sinkProbDist_oneprofile[sink] * currAgentPay, currAgentPay
            tempPayment[otheragent] += sinkProbDist_oneprofile[sink] * currAgentPay
        if debug:
            print 'sink receives =', paymentSink
            if paymentSink > 0:
                raw_input()
        tempPayment[sink] += - sinkProbDist_oneprofile[sink] * paymentSink

    if debug:
        print 'tempPayment'
        print tempPayment
#        raw_input()

    return tempPayment

# this function checks the strategyproofness of a given mechanism
def checkSinkSP(scf):
    # for the entire valuation profile
    debug = False

    packSizes = numOfValuations**np.arange(numOfagents)

    checkOFagent = numOfagents - 1

    for packsize in packSizes:
        print '\nchecking for agent =', checkOFagent

        listOfIndices = []
        # first split
        ySize = packsize * numOfValuations
        xSize = int(numOfProfiles / ySize)
        firstSplit = np.reshape(valProfIndices, (xSize,ySize))

        # second split
        for item in firstSplit:
            temp = np.reshape(item, (numOfValuations,packsize))
            for innerItem in temp.T:
                listOfIndices.append(innerItem)

        isSP = True

        for indices in listOfIndices:
            if debug:
                print 'indices for agent', checkOFagent, 'are', indices
                raw_input()

            for v_index in indices:
                for v_prime_index in indices:
                    value = np.dot(scf[v_index] - scf[v_prime_index], valuationProfiles[v_index][checkOFagent] - valuationProfiles[v_prime_index][checkOFagent])

                    if value < 0 and abs(value) > 1e-7:
                        print 'not SP!'
                        print 'deviating agent =', checkOFagent
                        print 'relevant valuationProfiles and SCF'
        #                printSCF(outcomes, valuationProfiles[chunk * numOfValuations : (chunk+1) * numOfValuations,:])
                        print 'v_index =', v_index, 'v_prime_index =', v_prime_index
                        print 'scf[v_index] =', scf[v_index], ', scf[v_prime_index] =', scf[v_prime_index]
                        print 'valuationProfiles[v_index][checkOFagent] =', valuationProfiles[v_index][checkOFagent], 'valuationProfiles[v_prime_index][checkOFagent] =', valuationProfiles[v_prime_index][checkOFagent]
                        print 'value =', value
    #                    raw_input()

                        isSP = False

        checkOFagent -= 1

    return isSP


def findOptSinkMech(debug=False):

    # define model
    m = Model('minRegretSink')

    # add variables
    sinkprob = {} # will be populated as (numOfProfiles,numOfagents)
#    payments = {} # will be populated as (numOfProfiles,numOfagents)

    if debug:
        print '\ncreating the variables - sinkprob and payments'
    for valueProfileIndex in valProfIndices:
#        for alt in xrange(numOfalts):
#            scf[valueProfileIndex,alt] =  \
#            m.addVar(lb = 0.0, ub = 1.0, vtype = GRB.CONTINUOUS, \
#            name = 'scf_valprofile_'+str(valueProfileIndex)+'_alt_'+str(alt))

        for agent in xrange(numOfagents):

            sinkprob[valueProfileIndex,agent] =  \
            m.addVar(lb = 0.0, ub = 1.0, vtype = GRB.CONTINUOUS, \
            name = 'sinkprob_valprofile_'+str(valueProfileIndex)+'_agent_'+str(agent))

#            payments[valueProfileIndex,agent] = \
#            m.addVar(vtype = GRB.CONTINUOUS, \
#            name = \
#            'payment_valprofile_'+str(valueProfileIndex)+'_agent_'+str(agent))

    if debug:
        print 'now creating the objective - k'
    k = m.addVar(vtype = GRB.CONTINUOUS, name = 'optimal_value')

    if debug:
        print 'variables creation complete'

    # model update
    m.update()

    # print the variables
    if debug:
        for v in m.getVars():
            print('%s' % v.varName)
        print '\nthese are just declared, not yet used in the optimization'

    # add constraints
    # part 1: strategyproofness constraints

    if debug:
        print '\nNow creating the constraints'
    packSizes = numOfValuations**np.arange(numOfagents)

    checkOFagent = numOfagents - 1

    for packsize in packSizes:
        if debug: print '\nPart 1: ensuring strategyproofness for agent =', checkOFagent

        listOfIndices = []
        # first split
        ySize = packsize * numOfValuations
        xSize = int(numOfProfiles / ySize)
        firstSplit = np.reshape(valProfIndices, (xSize,ySize))

        # second split
        for item in firstSplit:
            temp = np.reshape(item, (numOfValuations,packsize))
            for innerItem in temp.T:
                listOfIndices.append(innerItem)

        for indices in listOfIndices:
            if debug:
                print 'indices for agent', checkOFagent, 'are', indices
#                raw_input()

            for v_index in indices:
                for v_prime_index in indices:
                    expr = LinExpr()

                    sinkProbVector_v = []
                    sinkProbVector_v_prime = []
                    for agent in xrange(numOfagents):
                        sinkProbVector_v.append(sinkprob[v_index,agent])
                        sinkProbVector_v_prime.append(sinkprob[v_prime_index,agent])
                    currSCF_v = sink2alt(v_index,np.array(sinkProbVector_v))
                    currSCF_v_prime = sink2alt(v_prime_index,np.array(sinkProbVector_v_prime))

                    payments_v = sinkPayment(v_index,np.array(sinkProbVector_v))
                    payments_v_prime = sinkPayment(v_prime_index,np.array(sinkProbVector_v_prime))

#                    print "currSCF_v"
#                    print currSCF_v
#                    print "currSCF_v_prime"
#                    print currSCF_v_prime

                    for alt in xrange(numOfalts):
#                        expr += (currSCF_v[alt] - currSCF_v_prime[alt]) * (valuationProfiles[v_index][checkOFagent][alt] - valuationProfiles[v_prime_index][checkOFagent][alt]) # this is just a necessary condition, the WMON
                        expr += (currSCF_v[alt] - currSCF_v_prime[alt]) * valuationProfiles[v_index][checkOFagent][alt]
                    expr += payments_v_prime[checkOFagent] - payments_v[checkOFagent]
#                    print 'expr'
#                    print expr
#                    raw_input()

                    m.addConstr(expr, GRB.GREATER_EQUAL, 0.0)

        checkOFagent -= 1

    # part 2:
    # (a) scf summing to unity constraint
    # (b) payments summing to 0 = budget balance constraint
    # (c) k >= all regrets constraint

    if debug:
        print '\nPart 2:'
        print '(a) scf summing to unity constraint'
        print '(b) payments summing to 0 = budget balance constraint'
        print '(c) k >= all regrets constraint'

    for valueProfileIndex in valProfIndices:

        exprSinkProb = LinExpr()
#        exprPayment = LinExpr()
        expr_k = LinExpr()

        sinkProbVector_v = []
        for agent in xrange(numOfagents):
            exprSinkProb += sinkprob[valueProfileIndex,agent]
            sinkProbVector_v.append(sinkprob[valueProfileIndex,agent])
        currSCF_v = sink2alt(valueProfileIndex,np.array(sinkProbVector_v))

        for alt in xrange(numOfalts):
            expr_k += sum(valuationProfiles[valueProfileIndex],0)[alt] * currSCF_v[alt]
        m.addConstr(exprSinkProb, GRB.EQUAL, 1.0)
        m.addConstr(k - max(sum(valuationProfiles[valueProfileIndex],0)) + expr_k >= 0.0)

#        for agent in xrange(numOfagents):
#            exprPayment += payments[valueProfileIndex,agent]
#        m.addConstr(exprPayment, GRB.EQUAL, 0.0)


    if debug:
        print 'creating constraints complete'

    # set objectives
    if debug:
        print '\nSetting the objective function'
    m.setObjective(k, GRB.MINIMIZE)


    # optimize
    if debug: print '\nNow solving the optimization problem'
    m.setParam(GRB.Param.ScaleFlag, 2)
    m.optimize()
#    m.optimize(mycallback) # WITH CALLBACK, not very useful, doesn't allow to see the variables

    # print solutions
    print '\nSolution:'
    scfSolution = []
    sinkProbSolution = []
#    paymentSolution = []
    for valueProfileIndex in valProfIndices:
        temp = []
        for agent in xrange(numOfagents):
            temp.append(sinkprob[valueProfileIndex,agent].getAttr('x'))

        tempSCF = sink2alt(valueProfileIndex,np.array(temp),kind='num')

        sinkProbSolution.append(temp)
        scfSolution.append(tempSCF)

#        temp1 = []
#        for agent in xrange(numOfagents):
#            temp1.append(payments[valueProfileIndex,agent].getAttr('x'))
#        paymentSolution.append(temp1)

    sinkProbSolution = np.array(sinkProbSolution)
    scfSolution = np.array(scfSolution)

#    paymentSolution = np.array(paymentSolution)


    if debug:
        printSinkMech(scfSolution, sinkProbSolution)

        print 'k =', k.getAttr('x')
        print('Obj: %g' % m.objVal)

    # NEED TO UPDATE THE VARIABLES AND RETURN APPROPRIATELY
    return scfSolution, sinkProbSolution, m.objVal



###################################################################



###### MAIN CODE STARTS ############

###### PART 1: GLOBALLY OPTIMAL MECHANISM FINDING ###################

'''
#### ITERATING OVER THE NUMBER OF AGENTS AND LEVELS
M = 1.0
#numOfagents = 3
numOfalts = 2

numOfLevels = np.arange(2,5)
numOfAgentsSet = np.arange(2,5)

levelRepeat = 1 # max regret over these many repeats

for levels in numOfLevels:

    minOptRegretVector = []

    for numOfagents in numOfAgentsSet:

        print '=================='
        print 'SIMULATION STARTS'
        print '=================='
        print 'number of levels =', levels

        print 'numOfagents =', numOfagents, 'numOfalts =', numOfalts

        minOptRegret = 0.0

        for levelrepeatInstance in xrange(levelRepeat):

#            values = np.random.uniform(-M/2,M/2,levels)
            values = np.linspace(-M/2,M/2,levels)
#            values = [-M/2,-0.1,0.0,0.1,M/2] # can be made finer, but the complexity will be worse
            #values = [-np.sqrt(np.pi)/4,-np.pi/8,0.0,np.sqrt(np.pi)/4,M/2]

            valuationAgent = [val for val in it.product(*([values] * numOfalts))]

            print '\ncreating valuation profiles ...'
            valuationProfiles = Parallel(n_jobs=num_cores)(delayed(profileCreate)(val) for val in it.product(*([valuationAgent] * numOfagents)))
            valuationProfiles = np.array(valuationProfiles)
            print 'valuation profile creation complete'

            valProfIndices = range(len(valuationProfiles))
            # we can refer to any valuation profile and the corresponding randomized mechanism simultaneously in this way


            numOfProfiles = len(valuationProfiles)
            print '\nnumber of valuation profiles =', numOfProfiles
            numOfValuations = len(valuationAgent)
            print 'number of valuations of each agent =', numOfValuations


            print '\nbeginning to find the optimal mechanism'
            scf, payments, optRegret = findOptMech(debug=False)
            print 'optimal mechanism finding complete'
#            raw_input()

            print '\nTHE OPTIMAL MECHANISM:'
#            printMech(scf,payments)
            print '\nRegret =', optRegret
            print 'Valuation granularity =', values
            print 'Number of valuation levels =', len(values)
#            raw_input()

            print '\ncheck strategyproofness'
            print checkSP(scf,payments)

            if optRegret > minOptRegret:
                print 'minOptRegret updated'
                minOptRegret = optRegret

        minOptRegretVector.append(minOptRegret)

    minOptRegretVector = (1.0 / M) * np.array(minOptRegretVector)
    plt.plot(numOfAgentsSet, minOptRegretVector, 'o-', label='Num of levels = '+str(levels))

boundUniformSink = (1.0/numOfAgentsSet)*np.ceil(numOfAgentsSet/2.0)
#print boundUniformSink

plt.plot(numOfAgentsSet, boundUniformSink, 'rx-.', label=r'Uniform sink bound $\frac{1}{n} \left \lceil \frac{n}{2} \right \rceil$', markeredgewidth=2, markersize=5)
plt.xlabel(r'$n$',fontsize=20)
plt.ylabel('Expected sample regret')
plt.title('Regret plot for best randomized SP, BB mechanism')
plt.xticks(numOfAgentsSet)
plt.yticks(np.linspace(0.0,1.0,11))
xmin = min(numOfAgentsSet) - 0.25
xmax = max(numOfAgentsSet) + 0.25
ymin = 0.0
ymax = 1.0
plt.axis([xmin, xmax, ymin, ymax])
plt.legend(loc='best')
plt.grid()
plt.show()
'''

'''

### ITERATING OVER THE NUMBER OF LEVELS FOR 2 AGENTS
M = 1.0
#numOfagents = 2
numOfalts = 2


setOfAgents = np.array([2])
markers = ['ko-', 'bx-']
agentIndices = range(len(setOfAgents))

setOfLevels = np.arange(2,4)

for agentIndex in agentIndices:

    numOfagents = setOfAgents[agentIndex]

    optRegretVector = []

    for levels in setOfLevels:
        print '=================='
        print 'SIMULATION STARTS'
        print '=================='
        print 'number of levels =', levels

        print 'numOfagents =', numOfagents, 'numOfalts =', numOfalts

        values = np.linspace(-M/2,M/2,levels)
    #    values = [-M/2,-0.1,0.0,0.1,M/2] # can be made finer, but the complexity will be worse
    #    values = [-np.sqrt(np.pi)/4,-np.pi/8,0.0,np.sqrt(np.pi)/4,M/2]

        valuationAgent = [val for val in it.product(*([values] * numOfalts))]

        print '\ncreating valuation profiles ...'
        valuationProfiles = Parallel(n_jobs=num_cores)(delayed(profileCreate)(val) for val in it.product(*([valuationAgent] * numOfagents)))
        valuationProfiles = np.array(valuationProfiles)
        print 'valuation profile creation complete'

        valProfIndices = range(len(valuationProfiles))
        # we can refer to any valuation profile and the corresponding randomized mechanism simultaneously in this way


        numOfProfiles = len(valuationProfiles)
        print '\nnumber of valuation profiles =', numOfProfiles
        numOfValuations = len(valuationAgent)
        print 'number of valuations of each agent =', numOfValuations


        print '\nbeginning to find the optimal mechanism'
        scf, payments, optRegret = findOptMech(debug=False)
        print 'optimal mechanism finding complete'
    #            raw_input()

        print '\nTHE OPTIMAL MECHANISM:'
    #            printMech(scf,payments)
        print '\nRegret =', optRegret
        print 'Valuation granularity =', values
        print 'Number of valuation levels =', len(values)
    #            raw_input()

        print '\ncheck strategyproofness'
        print checkSP(scf,payments)

        optRegretVector.append(optRegret)

    optRegretVector = (1.0 / M) * np.array(optRegretVector)

    boundUniformSink = (1.0/numOfagents)*np.ceil(numOfagents/2.0)

    optRegretVectorRatio = optRegretVector / boundUniformSink

    plt.plot(setOfLevels, optRegretVectorRatio, markers[agentIndex], label='Number of agents = ' + str(numOfagents), markeredgewidth=2, markersize=5, linewidth=2)

#    plt.plot(setOfLevels, optRegretVector, markers[agentIndex], label='Number of agents = ' + str(numOfagents), markeredgewidth=2, markersize=5, linewidth=2)



#plt.plot(setOfLevels, boundUniformSink*np.ones(len(setOfLevels)), 'r--', label=r'Uniform sink bound $\frac{1}{n} \left \lceil \frac{n}{2} \right \rceil$', linewidth=2)

plt.xlabel('Number of valuation levels', fontsize=14)
plt.ylabel(r'$\frac{r_n(f_{\tt OPT})}{r_n(f_{\tt UniSink})}$', fontsize=20)
#plt.ylabel(r'$r_n(f_{OPT})$', fontsize=20)
plt.title('Regret ratio plot for best randomized SP, BB mechanism\nNumber of alternatives = ' + str(numOfalts))
#plt.title('Regret plot for best randomized SP, BB mechanism\nNumber of alternatives = ' + str(numOfalts))
plt.xticks(setOfLevels)
plt.yticks(np.linspace(0.0,1.0,11))
xmin = min(setOfLevels) - 0.15
xmax = max(setOfLevels) + 0.15
ymin = 0.0
ymax = 1.0
plt.axis([xmin, xmax, ymin, ymax])
plt.legend(loc='best')
plt.grid()
plt.show()

'''

#'''

### THE SOLUTION MORE CLOSELY FOR A SPECIFIC NUMBER OF AGENTS AND ALTERNATIVES AND LEVELS
M = 1.0
numOfagents = 2
numOfalts = 2
levels = 3

print '\n===================================='
print 'SIMULATION STARTS FOR GENERAL'
print '===================================='
print 'number of levels =', levels

print 'numOfagents =', numOfagents, 'numOfalts =', numOfalts

values = np.linspace(-M/2,M/2,levels)
#    values = [-M/2,-0.1,0.0,0.1,M/2] # can be made finer, but the complexity will be worse
#    values = [-np.sqrt(np.pi)/4,-np.pi/8,0.0,np.sqrt(np.pi)/4,M/2]

valuationAgent = [val for val in it.product(*([values] * numOfalts))]

print '\ncreating valuation profiles ...'
valuationProfiles = Parallel(n_jobs=num_cores)(delayed(profileCreate)(val) for val in it.product(*([valuationAgent] * numOfagents)))
valuationProfiles = np.array(valuationProfiles)
print 'valuation profile creation complete'

valProfIndices = range(len(valuationProfiles))
# we can refer to any valuation profile and the corresponding randomized mechanism simultaneously in this way


numOfProfiles = len(valuationProfiles)
print '\nnumber of valuation profiles =', numOfProfiles
numOfValuations = len(valuationAgent)
print 'number of valuations of each agent =', numOfValuations


print '\nbeginning to find the optimal mechanism'
scf, payments, optRegret = findOptMech(debug=False)
print 'optimal mechanism finding complete'
#            raw_input()

print '\nTHE OPTIMAL MECHANISM:'
#printMech(scf,payments)
print 'Length of the SCF =', len(scf)
print '\nRegret =', optRegret
print 'Valuation granularity =', values
print 'Number of valuation levels =', len(values)
print '\nCross checking for the solution mechanism:'
maxRegret, maxRegretProfileIndex, scfMaxRegretProfile = maxRegretProfile(scf)
print 'maxRegret =', maxRegret, '=', Fraction( Decimal(maxRegret) ).limit_denominator(100)
print 'maxRegretProfile \t\t SCF \t\t\t payment'
print valuationProfiles[maxRegretProfileIndex], '\t\t', scfMaxRegretProfile, '\t', payments[maxRegretProfileIndex]
#            raw_input()

print '\ncheck strategyproofness'
print checkSP(scf,payments)

#'''
#raw_input()

'''
####### check for an alternative swapped version of this mechanism for 2 alternatives

print '\nNeutrality: alternative permutated'
def indexInProfile(valProfile):

    for valueProfIndex in valProfIndices:
        if np.array_equal(valuationProfiles[valueProfIndex],valProfile):
            return valueProfIndex

    # at least one of the valueProfile must match, otherwise something is wrong
    print 'something is wrong!'

# this part of the code swaps the scf for the alternatives
swappedSCF_n = np.zeros((numOfProfiles,numOfalts))
swappedPayments_n = np.zeros((numOfProfiles,numOfagents))


altPerm = [1, 0] # this means alternatives are permuted in this manner

for valueProfIndex in valProfIndices:
    permutedValProfile = valuationProfiles[valueProfIndex][:,altPerm]
    indexOriginalProfile = indexInProfile(permutedValProfile)
    swappedSCF_n[indexOriginalProfile] = scf[valueProfIndex][altPerm] # alternatives swap
    swappedPayments_n[indexOriginalProfile] = payments[valueProfIndex]

#print '\nThe swapped mechanism is:'
#printMech(swappedSCF_n,swappedPayments_n)

print '\ncheck strategyproofness of swapped mechanism'
print checkSP(swappedSCF_n,swappedPayments_n)

maxRegret, maxRegretProfileIndex, scfMaxRegretProfile = maxRegretProfile(swappedSCF_n)
print 'maxRegret of swapped =', maxRegret

####### check over

#raw_input()

####### check for an agent swapped version of this mechanism for 2 agents

print '\nAnonymity: agent permutated'

# this part of the code swaps the scf for the alternatives
swappedSCF_a = np.zeros((numOfProfiles,numOfalts))
swappedPayments_a = np.zeros((numOfProfiles,numOfagents))


agentPerm = [1, 0] # this means agents are permuted in this manner

for valueProfIndex in valProfIndices:
    permutedValProfile = valuationProfiles[valueProfIndex][agentPerm,:]
    indexOriginalProfile = indexInProfile(permutedValProfile)
    swappedSCF_a[indexOriginalProfile] = scf[valueProfIndex]
    swappedPayments_a[indexOriginalProfile] = payments[valueProfIndex][agentPerm] # agent swap

#print '\nThe swapped mechanism is:'
#printMech(swappedSCF_a,swappedPayments_a)

print '\ncheck strategyproofness of swapped mechanism'
print checkSP(swappedSCF_a,swappedPayments_a)

maxRegret, maxRegretProfileIndex, scfMaxRegretProfile = maxRegretProfile(swappedSCF_a)
print 'maxRegret of swapped =', maxRegret

####### check over

#raw_input()

####### check for an agent swapped version of this mechanism for 2 agents

print '\nAnonymity and neutrality: agent and alternatives permutated'

# this part of the code swaps the scf for the alternatives
swappedSCF_na = np.zeros((numOfProfiles,numOfalts))
swappedPayments_na = np.zeros((numOfProfiles,numOfagents))

altPerm = [1, 0] # this means alternatives are permuted in this manner
agentPerm = [1, 0] # this means agents are permuted in this manner

for valueProfIndex in valProfIndices:
    permutedValProfile = valuationProfiles[valueProfIndex][agentPerm,:][:,altPerm]
    indexOriginalProfile = indexInProfile(permutedValProfile)
    swappedSCF_na[indexOriginalProfile] = scf[valueProfIndex][altPerm]
    swappedPayments_na[indexOriginalProfile] = payments[valueProfIndex][agentPerm]


#print '\nThe swapped mechanism is:'
#printMech(swappedSCF_na,swappedPayments_na)

print '\ncheck strategyproofness of swapped mechanism'
print checkSP(swappedSCF_na,swappedPayments_na)

maxRegret, maxRegretProfileIndex, scfMaxRegretProfile = maxRegretProfile(swappedSCF_na)
print 'maxRegret of swapped =', maxRegret

####### check over

#raw_input()

### what about the centroid of all these mechanisms?

scf_center = (scf + swappedSCF_n + swappedSCF_a + swappedSCF_na) / 4.0
payment_center = (payments + swappedPayments_n + swappedPayments_a + swappedPayments_na) / 4.0

#print '\nThe centroid mechanism is:'
#printMech(scf_center,payment_center)

print '\ncheck strategyproofness of swapped mechanism'
print checkSP(scf_center,payment_center)

#maxRegret, maxRegretProfileIndex, scfMaxRegretProfile = maxRegretProfile(scf_center)
maxRegret, maxRegretProfileIndex, scfMaxRegretProfile = maxRegretProfileZeroPayment(scf_center,payment_center)
print 'maxRegret of swapped =', maxRegret
print 'maxRegretProfile \t\t SCF \t\t\t payment'
print valuationProfiles[maxRegretProfileIndex], '\t\t', scf_center[maxRegretProfileIndex], '\t', payment_center[maxRegretProfileIndex]

raw_input()

print '\nPrint only independent pieces'

indeptValProfiles = []
indeptValProfileIndices = []

for valueProfIndex in valProfIndices:

#    print 'current indeptValProfiles'
#    print np.array(indeptValProfiles)

    currValProfile = valuationProfiles[valueProfIndex]

#    print 'currValProfile'
#    print currValProfile

#    print 'does this (or its permutation) already exist in the list?'
    exists = False

    for index in xrange(len(indeptValProfiles)):
        perm0 = currValProfile
        perm1 = currValProfile[agentPerm,:]
        perm2 = currValProfile[:,altPerm]
        perm3 = currValProfile[agentPerm,:][:,altPerm]

        if np.array_equal(indeptValProfiles[index], perm0) or \
            np.array_equal(indeptValProfiles[index], perm1) or \
            np.array_equal(indeptValProfiles[index], perm2) or \
            np.array_equal(indeptValProfiles[index], perm3):
#                print 'yes, it does!'
                exists = True

    if not exists:
#        print 'no it does not! Hence add'
        indeptValProfiles.append(currValProfile)
        indeptValProfileIndices.append(valueProfIndex)

#    raw_input()

print '\nNow printing the independent pieces of the valuation profile'
print 'valueprofile \t\t\t SCF \t\t\t payment'
for index in xrange(len(indeptValProfileIndices)):
    print indeptValProfiles[index], '\t\t', scf_center[indeptValProfileIndices[index]], '\t', payment_center[indeptValProfileIndices[index]]

print '\nlength of reduced SCF =', len(indeptValProfileIndices)

'''

#raw_input()
#'''

'''

######### PART 2: OPTIMAL GENERALIZED SINK MECHANISM FINDING ###########
# this code looks perfect, need to inspect the earlier code: not really, the WMON check was merely a necessary condition, that can't guarantee strategyproofness - this is now fixed

### THE SOLUTION MORE CLOSELY FOR A SPECIFIC NUMBER OF AGENTS AND ALTERNATIVES AND LEVELS
M = 1.0
numOfagents = 4
numOfalts = 2
levels = 3

print '\n===================================='
print 'SIMULATION STARTS FOR SINK MECHANISMS'
print '===================================='
print 'number of levels =', levels

print 'numOfagents =', numOfagents, 'numOfalts =', numOfalts

values = np.linspace(-M/2,M/2,levels)
#    values = [-M/2,-0.1,0.0,0.1,M/2] # can be made finer, but the complexity will be worse
#values = [-0.5,-0.49999,0.4999,0.5]

valuationAgent = [val for val in it.product(*([values] * numOfalts))]

print '\ncreating valuation profiles ...'
valuationProfiles = Parallel(n_jobs=num_cores)(delayed(profileCreate)(val) for val in it.product(*([valuationAgent] * numOfagents)))
valuationProfiles = np.array(valuationProfiles)
print 'valuation profile creation complete'

valProfIndices = range(len(valuationProfiles))
# we can refer to any valuation profile and the corresponding randomized mechanism simultaneously in this way


numOfProfiles = len(valuationProfiles)
print '\nnumber of valuation profiles =', numOfProfiles
numOfValuations = len(valuationAgent)
print 'number of valuations of each agent =', numOfValuations


print '\nbeginning to find the optimal sink mechanism'
scf, sinkProb, optRegret = findOptSinkMech(debug=False)
print 'optimal sink mechanism finding complete'
#            raw_input()

print '\nTHE OPTIMAL MECHANISM:'
printSinkMech(scf,sinkProb)
print 'Length of the SCF =', len(scf)
print '\nRegret =', optRegret
print 'Valuation granularity =', values
print 'Number of valuation levels =', len(values)
print '\nCross checking for the solution mechanism:'
maxRegret, maxRegretProfileIndex, scfMaxRegretProfile = maxRegretProfile(scf)
print 'maxRegret =', maxRegret
print 'maxRegretProfile \t\t SCF \t sink probabilities'
print valuationProfiles[maxRegretProfileIndex], '\t\t', scfMaxRegretProfile, '\t', sinkProb[maxRegretProfileIndex]
print '\npayments (final payment vector may repeat twice):'
print sinkPayment(maxRegretProfileIndex, np.array(sinkProb[maxRegretProfileIndex]), kind='num', debug=True)
#            raw_input()

print '\ncheck strategyproofness'
print checkSinkSP(scf)

'''

'''

######### PART 3: COMPARE GENERALIZED SINK AND GENERAL SP + BB MECHANISMS  ###########

### ITERATING OVER THE NUMBER OF LEVELS FOR 2 AGENTS
M = 1.0
numOfagents = 2
numOfalts = 2

#markers = ['ko-', 'bx-']
#agentIndices = range(len(setOfAgents))

setOfLevels = np.arange(2,16)

print '\nThis simulation compares the sample regret for the global optimal vs. the optimal sink mechanism for a varying number of valuation levels'

optRegretVector = []
optSinkRegretVector = []

for levels in setOfLevels:
    print '=================='
    print 'SIMULATION STARTS'
    print '=================='
    print 'number of levels =', levels

    print 'numOfagents =', numOfagents, 'numOfalts =', numOfalts

    values = np.linspace(-M/2,M/2,levels)
#    values = [-M/2,-0.1,0.0,0.1,M/2] # can be made finer, but the complexity will be worse
#    values = [-np.sqrt(np.pi)/4,-np.pi/8,0.0,np.sqrt(np.pi)/4,M/2]

    valuationAgent = [val for val in it.product(*([values] * numOfalts))]

    print '\ncreating valuation profiles ...'
    valuationProfiles = Parallel(n_jobs=num_cores)(delayed(profileCreate)(val) for val in it.product(*([valuationAgent] * numOfagents)))
    valuationProfiles = np.array(valuationProfiles)
    print 'valuation profile creation complete'

    valProfIndices = range(len(valuationProfiles))
    # we can refer to any valuation profile and the corresponding randomized mechanism simultaneously in this way


    numOfProfiles = len(valuationProfiles)
    print '\nnumber of valuation profiles =', numOfProfiles
    numOfValuations = len(valuationAgent)
    print 'number of valuations of each agent =', numOfValuations


    print '\nbeginning to find the optimal mechanism'
    scf, payments, optRegret = findOptMech(debug=False)
    print 'optimal mechanism finding complete'
#            raw_input()

    print '\nTHE OPTIMAL MECHANISM:'
#            printMech(scf,payments)
    print '\nRegret =', optRegret
    print 'Valuation granularity =', values
    print 'Number of valuation levels =', len(values)
#            raw_input()

    print '\ncheck strategyproofness'
    print checkSP(scf,payments)

#    raw_input()
#
#    print '\nbeginning to find the optimal sink mechanism'
#    scfSink, sinkProb, optSinkRegret = findOptSinkMech(debug=False)
#    print 'optimal sink mechanism finding complete'
#
#
#    print '\nTHE OPTIMAL SINK MECHANISM:'
##    printSinkMech(scf,sinkProb)
##    print 'Length of the SCF =', len(scf)
#    print '\nRegret =', optSinkRegret
#    print 'Valuation granularity =', values
#    print 'Number of valuation levels =', len(values)
##    print '\nCross checking for the solution mechanism:'
##    maxRegret, maxRegretProfileIndex, scfMaxRegretProfile = maxRegretProfile(scf)
##    print 'maxRegret =', maxRegret
##    print 'maxRegretProfile \t\t SCF \t sink probabilities'
##    print valuationProfiles[maxRegretProfileIndex], '\t\t', scfMaxRegretProfile, '\t', sinkProb[maxRegretProfileIndex]
##    print 'payments (final payment vector may repeat twice):'
##    print sinkPayment(maxRegretProfileIndex, np.array(sinkProb[maxRegretProfileIndex]), kind='num', debug=True)
#
#
#    print '\ncheck strategyproofness'
#    print checkSinkSP(scfSink)

#    raw_input()

    optRegretVector.append(optRegret)
#    optSinkRegretVector.append(optSinkRegret)

optRegretVector = (1.0 / M) * np.array(optRegretVector)
#optSinkRegretVector = (1.0 / M) * np.array(optSinkRegretVector)

#boundUniformSink = (1.0/numOfagents)*np.ceil(numOfagents/2.0)
#
#optRegretVectorRatio = optRegretVector / boundUniformSink
#
#plt.plot(setOfLevels, optRegretVectorRatio, markers[agentIndex], label='Number of agents = ' + str(numOfagents), markeredgewidth=2, markersize=5, linewidth=2)



#plt.plot(setOfLevels, optSinkRegretVector, 'rx-', markeredgewidth=2, markersize=5, linewidth=2, label=r'$n r_n(f_{\tt SINK-OPT})$')

plt.plot(setOfLevels, np.ones(len(setOfLevels)), 'r--', markeredgewidth=2, markersize=5, linewidth=2, label='lower bound for deterministic')
plt.plot(setOfLevels, 0.5 * np.ones(len(setOfLevels)), 'k-.', markeredgewidth=2, markersize=5, linewidth=3, label='lower bound for generalized sink')
plt.plot(setOfLevels, optRegretVector, 'bo-', markeredgewidth=2, markersize=5, linewidth=2, label='lower bound for optimal randomized')


#plt.plot(setOfLevels, boundUniformSink*np.ones(len(setOfLevels)), 'r--', label=r'Uniform sink bound $\frac{1}{n} \left \lceil \frac{n}{2} \right \rceil$', linewidth=2)

plt.xlabel('Number of valuation levels', fontsize=14)
#plt.ylabel(r'$\frac{r_n(f_{\tt OPT})}{r_n(f_{\tt UniSink})}$', fontsize=20)
plt.ylabel(r'$n r_n^M(f)$', fontsize=20)
plt.title('Inefficiency ratio for the best randomized, strategyproof,\nbudget-balanced mechanism, m = ' + str(numOfalts) + ', n = ' + str(numOfagents) + ', M = ' + str(M))
#plt.title('Regret plot for best randomized SP, BB mechanism\nNumber of alternatives = ' + str(numOfalts))
plt.xticks(setOfLevels)
plt.yticks(np.linspace(0.0,1.0,11))
xmin = min(setOfLevels) - 0.15
xmax = max(setOfLevels) + 0.15
ymin = 0.0
ymax = 1.05
plt.axis([xmin, xmax, ymin, ymax])
plt.legend(loc = 'lower left', bbox_to_anchor = (0.2, 0.6))
plt.grid()
plt.show()

'''